use strict;
use warnings;

use Getopt::Std;

my $static = 0;
my %opts;
getopts("sc:", \%opts);
# -s -- generate wrappers for static methods
if (exists($opts{s})) {
# I forgot about static modifier during preprocessing of Doxygen
# so now have to invent a flag
  $static = 1;
}

my $f = $ARGV[0];

my ($c, $m, $rest) = split /\^|\./, $f;
my $num = "";
if ($m =~ /(\w+)#(\d+)/) {
  $m = $1;
  $num = $2;
}

# -c <ReturnType> -- override return type of the constructor wrapper
my $retctor = $c;
if (exists($opts{c})) {
  $retctor = $opts{c};
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
if ($ctor) {
  $fullname = $m;
}
else {
  $fullname = $c.ucfirst($m);
}
my $cname = "ql" . ucfirst($fullname) . $num;
if ($num) {
  $hname .= "'" x $num;
}
my $fname = "c_$hname";

my $hret = "";
my $fret = "";
my $cret = "";

my @args = ();
my $retcast = "";

my $implCtor = 0; # "implicit constructor" i.e. how to return an object

# parse description
for (@dec) {
  chomp;
  if (/^-- \^/) { # argument name or enum member comment
    $args[-1]{name} = $_;
  }
  elsif (/^-- /) { # function comment
    push @hs, $_;
  }
  elsif (/^->(.*)$/) { # return type
    if ($1 eq '') {
      if ($ctor) {
	my $tmp;
	($cret, $fret, $hret, $tmp, $retcast, $implCtor) = type($retctor, 0);
      }
      else {
	die 'Missing return type';
      }
    }
    else {
      my $tmp;
      ($cret, $fret, $hret, $tmp, $retcast, $implCtor) = type($1, 0);
    }
  }
  elsif (/^::(.+)$/) { # argument type
    my %arg = ();
    $arg{type} = $1;
    push @args, \%arg;
  }
  elsif (/^=(.+)$/) { # default value
    $args[-1]{default} = $1;
  }
}

my $cargs = "";
my $fargs = "";
my $hargs = "";
my @cnames = ();
my $ocall = "";

sub substPercent {
  my $where = shift;
  my $what = shift;

  my $last = -1;
  my $res = '';
  my $pos = index($where, '%');
  while ($pos > -1) {
    $res .= substr($where, $last+1, $pos - $last - 1).$what;
    $last = $pos;
    $pos = index($where, '%', $pos+1);
  }
  $res = $res.substr($where, $last+1);
  return $res;
}

if ($static) {
  $ocall .= "${c}::";
}
elsif (not $ctor) {
  my $cast = '';
  ($cargs, $fargs, $hargs, $cast) = type($c, 0);
  $hargs .= "\n";
  push @cnames, "o";
  $cargs .= " $cnames[-1]";

  $ocall = substPercent($cast, $cnames[-1]).'->';
}

# iterate over parsed arguments to form declarations and calls
my $call = "";
my $i = 0;
for (@args) {
  my ($carg, $farg, $harg, $cast, $r_, $c_, $extra) = type($$_{type}, exists $$_{default});
  if ($cargs) {
    $cargs .= ', ';
    $fargs .= ' -> ';
    $hargs .= '  -> ';
  }
  if ($i > 0) {
    $call  .= ', ';
  }
  $fargs .= $farg;
  $hargs .= $harg;
  if (exists $$_{name} and $$_{name} =~ m!^-- \^(\w+)$!) {
    push @cnames, $1;
    $hargs .= " $$_{name}";
  }
  else {
    push @cnames, "x".($#cnames+1);
  }

  if ($extra) { 
    $cargs .= substPercent($extra, $cnames[-1]);
    $cargs .= ', ';
  }
  $cargs .= $carg;
  $cargs .= " $cnames[-1]";
  $hargs .= "\n";
  $call .= substPercent($cast, $cnames[-1]);
  $i++;
}

if (index($fret, ' ') > -1)
{
  $fret = "($fret)";
}
push @hs, "$hname :: $hargs  -> IO $hret";
if ($ctor or $implCtor) {
  push @hs, "$hname = \$(ffiCall '$hname) $fname"
}
else {
  push @hs, "$hname = \$(ffiCallX '$hname) $fname"
}
push @hsffi, "foreign import ccall safe \"ql.h $cname\"";
push @hsffi, "  $fname :: $fargs -> Ptr CString -> IO $fret\n";
push @h, "  $cret DLLEXPORT $cname($cargs, char **e);";
push @cpp, "$cret $cname($cargs, char **e) {";
push @cpp, "  try {";
shift @cnames;

$call = "$ocall$m($call)";
$call = substPercent($retcast, $call);
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
print O "\n";
close O;

open O, ">$base.hs_exp";
print O "  , $hname\n";
close O;

sub type {
  my $t = shift;
  my $def = shift;
  my $h = ($t =~ m!Handle!);
  $t =~ s/^(const\s+Handle\s*<\s*)([^& ]+)(\s*>\s*&\s*)/$2/;
  $t =~ s/^((const\s+)?boost::shared_ptr\s*<\s*)([^& ]+)(\s*>\s*&?\s*)/$3/;
  $t =~ s/^(const\s+)?([^& ]+)(\s*&\s*)?/$2/;

  my $opt = ($t =~ m!boost::optional!);
  $t =~ s/^(boost::optional<\s*)([^> ]+)(\s*>\s*)$/$2/;
  my $vect = ($t =~ m!std::vector!);
  $t =~ s/^((const\s+)?std::vector<\s*)([^> ]+)(\s*>\s*&?\s*)$/$3/;

  if ($t ~~ ['Rate', 'Real', 'Double', 'Spread', 'Volatility', 'DiscountFactor']) {
    if (not $vect) {
      return ('double', 'CDouble', 'Double', '%', '%', 0, '');
    }
    else {
      return ('double*', 'CUInt -> Ptr CDouble', '[Double]', 'std::vector<double>(%, %+%Len)', '???', 0, 'unsigned %Len');
    }
  }
  elsif ($t eq 'Array') {
    return ('double*', 'CUInt -> Ptr CDouble', '[Double]', 'Array(%, %+%Len)', '???', 0, 'unsigned %Len');
  }
  elsif ($t ~~ ['Natural', 'Size']) {
    if (not $vect) {
      return ('unsigned', 'CUInt', 'Word', '%', '%', 0, '');
    }
    else {
      return ('unsigned*', 'CUInt -> Ptr CUInt', '[Word]', 'std::vector<unsigned>(%, %+%Len)', '???', 0, 'unsigned %Len');
    }
  }
  elsif ($t ~~ ['Integer', 'BigInteger', 'Day', 'Year']) {
    return ('int', 'CInt', 'Int', '%', '%', 0, '');
  }
  elsif ($t eq 'Date') {
    if (not $def) {
      if (not $vect) {
	return ('int', 'CDate', 'Day', 'Date(%)', '(%).serialNumber()', 0, '');
      }
      else {
	return ('int*', 'CUInt -> Ptr CDate', '[Day]', 'qlDateVector(%, %Len)', '???', 0, 'unsigned %Len');
      }
    }
    else {
        return ('int', 'CDate', 'Maybe Day', 'qlNullableDate(%)', '', 0, '');
    }
  }
  elsif ($t eq 'Time') {
    if (not $vect) {
      return ('double', 'CYearFraction', 'YearFraction', '%', '%', 0, '');
    }
    else {
      return ('double *', 'CUInt -> Ptr CYearFraction', '[YearFraction]', 'std::vector<double>(%, %+%Len)', '???', 0, 'unsigned %Len');
    }
  }
  elsif ($t eq 'bool') {
    if ($opt) {
      return ('int', 'CInt', 'Maybe Bool', 'qlOptBool(%)', 'qlOptBool(%)', 0, '');
    }
    else {
      if ($vect) {
	return ('int *', 'CUInt -> Ptr CInt', '[Bool]', 'std::vector<bool>(%, %+%Len)', '', 0, 'unsigned %Len');
      }
      else {
	return ('int', 'CInt', 'Bool', '%', '%', 0, '');
      }
    }
  }
  elsif ($t eq 'void') {
    return ('void', '()', '()', '', '', 0, '');
  }
  elsif ($t ~~ ['Compounding', 'Frequency', 'Position::Type', 'TimeUnit',
      'DateGeneration::Rule', 'BusinessDayConvention', 'Weekday', 'Month',
      'Seniority', 'Exercise::Type', 'Option::Type', 'OvernightIndexedSwap::Type',
      'VanillaSwap::Type', 'PriceType', 'SettlementType',
      'JointCalendarRule', 'Duration::Type', 'Discretization']) {
    my ($carg, $farg, $cast) = ('int', 'CInt', "($t)%");
    $t =~ s/://g;
    return ($carg, $farg, $t, $cast, '%', 0, '');
  }
  elsif ($t eq 'std::string') {
    return ("char*", "CString", "String", 'std::string(arg(%))', "DUP((%).c_str())", 0, '');
  }
  elsif ($t eq 'discretization') {
    return ("char* ", "CString", "ProcessDiscretization", 'createDiscretization(arg(%))', "???", 0, '');
  }
  elsif ($t ~~ ['Calendar', 'DayCounter', 'Currency', 'Leg', 'Schedule', 'Period',
      'InterestRate', 'FittedBondDiscountCurveFittingMethod', 'Rounding']) {
    if (not $vect) {
      return ("$t*", "Ptr C$t", $t, '(*arg(%))', "ret(new $t(%))", 1, '');
    }
    else {
      return ("$t**", "CUInt -> Ptr (Ptr C$t)", "[$t]", 'qlBuildVector(%, %Len)', '???', 1, 'unsigned %Len');
    }
  }
  else {
    $t =~ s/^(\w)/\u$1/;
    my ($carg, $farg, $ret) = ("Ql$t*", "Ptr C$t", "ret(new Ql$t(alloc(new %)))");
    if (not $h) {
      if (not $vect) {
	return ($carg, $farg, $t, '(*arg(%))', $ret, 1);
      }
      else {
	return ("$carg*", "CUInt -> Ptr ($farg)", "[$t]", 'qlBuildVector(%, %Len)', '???', 1, 'unsigned %Len');
      }
    }
    else {
      if (not $def) {
	return ($carg, $farg, $t, "Handle<$t>(*arg(%))", $ret, 1, '');
      }
      else {
	return ($carg, $farg, "Maybe $t", "qlNullableHandle(arg(%))", $ret, 1, '');
      }
    }
  }
}

# std::vector<Date, Real...> as return value
# ? const std::vector<boost::shared_ptr<typename Traits::helper> >&
# vim: set ft=perl sw=2 ts=8 st=2:
