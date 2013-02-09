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
my $hname;
my $ctor = ($c eq $m); # constructor
if ($ctor)
{
  $hname = lcfirst($m);
}
else
{
  $hname = lcfirst($c).ucfirst($m);
}
my $cname = "ql" . ucfirst($hname) . $num;
if ($num)
{
  $hname .= "'" x $num;
}
my $hret = "";
my $fret = "";
my $cret = "";

my $args = "";
for (@dec)
{
  chomp;
  if (/^-- \^/) # argument name or enum member comment
  {
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
	($cret, $fret, $hret) = type($c);
      }
      else
      {
	die 'Missing return type';
      }
    }
    else
    {
      ($cret, $fret, $hret) = type($1);
    }
  }
  elsif (/^::(.+)$/) # argument type
  {
  }
  elsif (/^=(.+)$/) # default value
  {
  }
}

#    push @hs, "$hname :: ";
#    push @hsffi, "foreign import ccall safe \"ql.h $cname\"";
#    push @hsffi, "c_$hname :: ";
#    push @h, "$cret $cname(";
#    push @cpp, "$cret DLLEXPORT $cname(";
#    if (not $ctor)
#    {
#      ($carg, $farg, $harg) = type($c);
#      push @hs, harg;
#      push @hsffi, farg;
#      push @cargs, carg;
#    }

push @hs, "$hret";
push @hsffi, "$fret";
push @h, ");";
push @cpp, "}";

print join("\n", @hs);
print "\n";
print join("\n", @hsffi);

sub type
{
  my $t = shift;
  if ($t ~~ ['Rate', 'Real', 'Double', 'Spread', 'Volatility'])
  {
    return ('double', 'CDouble', 'Double');
  }
  elsif ($t ~~ ['Natural', 'Size'])
  {
    return ('unsigned', 'CUInt', 'Word');
  }
  elsif ($t ~~ ['BigInteger'])
  {
    return ('int', 'CInt', 'Int');
  }
  elsif ($t ~~ ['Date'])
  {
    return ('int', 'CDate', 'Day');
  }
  elsif ($t eq 'void')
  {
    return ('void', '()', '()');
  }
  else
  {
    return ("Ql$t", "Ptr C$t", "$t");
  }

# const Date &
# const Handle< Quote,YieldTermStructure > &
# const DayCounter,Calendar,Currency,Leg,Schedule,Period &
# Compounding
# Frequency
# Position::Type
# Period
# TimeUnit
# DateGeneration::Rule
# const boost::shared_ptr< Bond,FixedRateBond,IborIndex > &
# const std::vector< Real,Rate,Date,Period > &
# const std::vector< Handle< Quote > > &
# ? const std::vector<boost::shared_ptr<typename Traits::helper> >&
}
# vim: set ft=perl sw=2 ts=8 st=2:
