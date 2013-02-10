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
	($cret, $fret, $hret, $tmp, $retcast) = type($c, 0);
      }
      else
      {
	die 'Missing return type';
      }
    }
    else
    {
      my $tmp;
      ($cret, $fret, $hret, $tmp, $retcast) = type($1, 0);
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

push @hs, "$hname :: $hargs  -> IO $hret";
if ($ctor)
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
push @cpp, "try {";
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
print "\n";
print join("\n", @hsffi);
print "\n";
print join("\n", @h);
print "\n";
print join("\n", @cpp);

my $base = $ARGV[0];
$base =~ s/\.txt$//;

open O, ">$base.cpp";
print O join("\n", @cpp);
close O;

open O, ">$base.h";
print O join("\n", @h);
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
  $t =~ s/^(const\s+)?([^& ]+)(\s*&\s*)?/$2/;
  if ($t ~~ ['Rate', 'Real', 'Double', 'Spread', 'Volatility'])
  {
    return ('double', 'CDouble', 'Double', '', '');
  }
  elsif ($t ~~ ['Natural', 'Size'])
  {
    return ('unsigned', 'CUInt', 'Word', '', '');
  }
  elsif ($t ~~ ['BigInteger'])
  {
    return ('int', 'CInt', 'Int', '', '');
  }
  elsif ($t ~~ ['Date'])
  {
    if (not $def)
    {
      return ('int', 'CDate', 'Day', 'Date(%)', '(%).serialNumber()');
    }
    else
    {
      return ('int', 'CDate', 'Maybe Day', 'qlNullableDate(%)', '');
    }
  }
  elsif ($t eq 'bool')
  {
    return ('int', 'CInt', 'Bool', '', '');
  }
  elsif ($t eq 'void')
  {
    return ('void', '()', '()', '', '');
  }
  elsif ($t ~~ ['Compounding', 'Frequency', 'Position::Type', 'Period', 'TimeUnit', 'DateGeneration::Rule'])
  {
    my ($carg, $farg, $harg) = ('int', 'CInt', $t);
    $t =~ s/://g;
    return ($carg, $farg, $harg, "($t)%", '');
  }
  elsif ($t ~~ ['Calendar', 'DayCounter', 'Currency', 'Leg', 'Schedule', 'Period'])
  {
    return ("$t*", "Ptr C$t", "$t", '(*arg(%))', '');
  }
  else
  {
    return ("Ql$t*", "Ptr C$t", "$t", '(*arg(%))', '');
  }

# const Handle< Quote,YieldTermStructure > &
# const boost::shared_ptr< Bond,FixedRateBond,IborIndex > &
# const std::vector< Real,Rate,Date,Period > &
# const std::vector< Handle< Quote > > &
# ? const std::vector<boost::shared_ptr<typename Traits::helper> >&
}
# vim: set ft=perl sw=2 ts=8 st=2:
