use strict;
use warnings;

if ($#ARGV<2)
{
  die "Usage: $0 descriptionFile haskellModule haskellType";
}
my $file = $ARGV[0];
my $hmod = $ARGV[1];
my $hname = $ARGV[2];

open I, "$file" or die "Cannot open input file";

my ($c, $e) = split /\^|#/, $file;
open C, ">>qlEnumerations.cpp";
open H, ">$hmod.hs";

my $ee = lcfirst $e;
print C "static const int ${ee}Values[] = {\n";
my $first = 1;
while (<I>)
{
  my $suppress = 0;
  my $Cpre = "  , ";
  my $Hpre = "  | ";
  if ($first)
  {
    $first = 0;
    if (/^-- \|/)
    {
      print H "$_";
      $suppress = 1;
    }
    print H "data $hname =\n";
    $Cpre = "    ";
    $Hpre = "    ";
  }
  if (not $suppress)
  {
    if (/-- \^/)
    {
      print H "$_";
    }
    else
    {
      print C "${Cpre}${c}::$_";
      print H "${Hpre}$_";
    }
  }
}
print C "};\n";
print C "\n";
print C "  {\"$hmod\",\n";
print C "    LENGTH($ee), $ee},\n";
print H "  deriving (Show, Eq, Enum)\n";
print H "instance QLEnum $hname\n";

close H;
close C;
close I;

# vim: set ft=perl sw=2 ts=8 st=2:
