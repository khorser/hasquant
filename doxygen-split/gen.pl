use strict;
use warnings;

my $f = $ARGV[0];

my ($c, $m, $rest) = split /\^|\./, $f;
my $num = "";
if ($m =~ /(\w+)#(\d+)/)
{
  $m = $1;
  $num = $2;
}

open F, "<$f";
my @dec = <F>;
close F;

my @hs = ();
my @hsffi = ();
my @h = ();
my @cpp = ();
my $hname = lcfirst($m);
my $ctor = ($c eq $m); # constructor
my $fullname;
if ($ctor)
{
  $fullname = $m;
}
else
{
  $fullname = $c.ucfirst($m);
}
my $cname = "ql" . ucfirst($fullname) . $num;
if ($num)
{
  $hname .= "'" x $num;
}
my $fname = "c_$hname";

my $hret = "";
my $fret = "";
my $cret = "";

my @args = ();
my $retcast = "";

my $implCtor = 0;

# parse description
for (@dec)
{
  chomp;
  if (/^-- \^/) # argument name or enum member comment
  {
    $args[-1]{name} = $_;
  }
  elsif (/^-- /) # function comment
  {
    push @hs, $_;
  }
  elsif (/^->(.*)$/) # return type
  {
    if ($1 eq '')
    {
      if ($ctor)
      {
	my $tmp;
	($cret, $fret, $hret, $tmp, $retcast, $implCtor) = type($c, 0);
      }
      else
      {
	die 'Missing return type';
      }
    }
    else
    {
      my $tmp;
      ($cret, $fret, $hret, $tmp, $retcast, $implCtor) = type($1, 0);
    }
  }
  elsif (/^::(.+)$/) # argument type
  {
    my %arg = ();
    $arg{type} = $1;
    push @args, \%arg;
  }
  elsif (/^=(.+)$/) # default value
  {
    $args[-1]{default} = $1;
  }
}

my $cargs = "";
my $fargs = "";
my $hargs = "";
my @cnames = ();
my $ocall = "";

if (not $ctor)
{
  my $cast = '';
  ($cargs, $fargs, $hargs, $cast) = type($c, 0);
  $hargs .= "\n";
  push @cnames, "o";
  $cargs .= " $cnames[-1]";

  my $pos = index($cast, '%');
  my $argcall;
  if ($pos > -1)
  {
    $ocall = substr($cast, 0, $pos).$cnames[-1].substr($cast, $pos+1);
  }
  else
  {
    $ocall = $cnames[-1];
  }
  $ocall .= '->';
}

# iterate over parsed arguments to form declarations and calls
my $call = "";
my $i = 0;
for (@args)
{
  my ($carg, $farg, $harg, $cast) = type($$_{type}, exists $$_{default});
  if ($cargs)
  {
    $cargs .= ', ';
    $fargs .= ' -> ';
    $hargs .= '  -> ';
  }
  if ($i > 0)
  {
    $call  .= ', ';
  }
  $cargs .= $carg;
  $fargs .= $farg;
  $hargs .= $harg;
  if (exists $$_{name} and $$_{name} =~ m!^-- \^(\w+)$!)
  {
    push @cnames, $1;
    $hargs .= " $$_{name}";
  }
  else
  {
    push @cnames, "x".$#cnames;
  }
  $cargs .= " $cnames[-1]";
  $hargs .= "\n";
  my $pos = index($cast, '%');
  my $argcall;
  if ($pos > -1)
  {
    $argcall = substr($cast, 0, $pos).$cnames[-1].substr($cast, $pos+1);
  }
  else
  {
    $argcall = $cnames[-1];
  }
  $call .= "$argcall";
  $i++;
}

if (index($fret, ' ') > -1)
{
  $fret = "($fret)";
}
push @hs, "$hname :: $hargs  -> IO $hret";
if ($ctor or $implCtor)
{
  push @hs, "$hname = \$(ffiConstruct '$hname) $fname"
}
else
{
  push @hs, "$hname = \$(ffiCallX '$hname) $fname"
}
push @hsffi, "foreign import ccall safe \"ql.h $cname\"";
push @hsffi, "  $fname :: $fargs -> Ptr CString -> IO $fret\n";
push @h, "  $cret DLLEXPORT $cname($cargs, char **e);";
push @cpp, "$cret $cname($cargs, char **e) {";
push @cpp, "  try {";
shift @cnames;

$call = "$ocall$m($call)";
my $pos = index($retcast, '%');
if ($pos > -1)
{
  $call = substr($retcast, 0, $pos).$call.substr($retcast, $pos+1);
}
push @cpp, "    return $call;";
push @cpp, "  } catch (std::exception& er) {";
push @cpp, "    return handleException<$cret>(e, er);";
push @cpp, "  }";
push @cpp, "}";

print join("\n", @hs);
print "\n\n";
print join("\n", @hsffi);
print "\n";
print join("\n", @h);
print "\n";
print join("\n", @cpp);

my $base = $ARGV[0];
$base =~ s/\.txt$//;

open O, ">$base.cpp";
print O join("\n", @cpp);
print O "\n";
close O;

open O, ">$base.h";
print O join("\n", @h);
print O "\n";
close O;

open O, ">$base.hs";
print O join("\n", @hs);
print O "\n\n";
print O join("\n", @hsffi);
close O;

sub type
{
  my $t = shift;
  my $def = shift;
  my $h = ($t =~ m!Handle!);
  $t =~ s/^(const\s+Handle\s*<\s*)([^& ]+)(\s*>\s*&\s*)/$2/;
  $t =~ s/^(const\s+boost::shared_ptr\s*<\s*)([^& ]+)(\s*>\s*&\s*)/$2/;
  $t =~ s/^(const\s+)?([^& ]+)(\s*&\s*)?/$2/;
  if ($t ~~ ['Rate', 'Real', 'Double', 'Spread', 'Volatility', 'DiscountFactor'])
  {
    return ('double', 'CDouble', 'Double', '', '', 0);
  }
  elsif ($t ~~ ['Natural', 'Size'])
  {
    return ('unsigned', 'CUInt', 'Word', '', '', 0);
  }
  elsif ($t ~~ ['BigInteger', 'Day', 'Year'])
  {
    return ('int', 'CInt', 'Int', '', '', 0);
  }
  elsif ($t eq 'Date')
  {
    if (not $def)
    {
      return ('int', 'CDate', 'Day', 'Date(%)', '(%).serialNumber()', 0);
    }
    else
    {
      return ('int', 'CDate', 'Maybe Day', 'qlNullableDate(%)', '', 0);
    }
  }
  elsif ($t eq 'Time')
  {
    return ('double', 'CYearFraction', 'YearFraction', '', '', 0);
  }
  elsif ($t eq 'bool')
  {
    return ('int', 'CInt', 'Bool', '', '', 0);
  }
  elsif ($t eq 'void')
  {
    return ('void', '()', '()', '', '', 0);
  }
  elsif ($t ~~ ['Compounding', 'Frequency', 'Position::Type', 'TimeUnit',
      'DateGeneration::Rule', 'BusinessDayConvention', 'Weekday', 'Month',
      'Seniority', 'Exercise::Type', 'Option::Type', 'OvernightIndexedSwap::Type',
      'VanillaSwap::Type, PriceType', 'SensitivityAnalysis', 'SeetlementType',
      'JointCalendarRule', 'Duration::Type'])
  {
    my ($carg, $farg, $cast) = ('int', 'CInt', "($t)%");
    $t =~ s/://g;
    return ($carg, $farg, $t, $cast, '', 0);
  }
  elsif ($t eq 'std::string')
  {
    return ("char*", "CString", "String", 'std::string(arg(%))', "DUP((%).c_str())", 0);
  }
  elsif ($t ~~ ['Calendar', 'DayCounter', 'Currency', 'Leg', 'Schedule', 'Period', 'InterestRate'])
  {
    return ("$t*", "Ptr C$t", $t, '(*arg(%))', "ret(new $t(%))", 1);
  }
  else
  {
    my ($carg, $farg, $ret) = ("Ql$t*", "Ptr C$t", "ret(new Ql$t(alloc(new %)))");
    if (not $h)
    {
      return ($carg, $farg, $t, '(*arg(%))', $ret, 1);
    }
    else
    {
      if (not $def)
      {
	return ($carg, $farg, $t, "Handle<$t>(*arg(%))", $ret, 1);
      }
      else
      {
	return ($carg, $farg, "Maybe $t", "qlNullableHandle(arg(%))", $ret, 1);
      }
    }
  }
}

# const std::vector< Real,Rate,Date,Period > &
# const std::vector< Handle< Quote > > &
# ? const std::vector<boost::shared_ptr<typename Traits::helper> >&
# boost::optional< BusinessDayConvention >
# vim: set ft=perl sw=2 ts=8 st=2:
