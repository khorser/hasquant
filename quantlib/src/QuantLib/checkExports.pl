use strict;
use warnings;

my %all = ();

for my $f (glob('*.hs */*.hs'))
{
  open I, "<$f";

  my %e = ();
  my %d = ();
  while (<I>)
  {
    if (/^  [, ] ([a-zA-Z0-9']+)\s*$/)
    {
      $e{$1} = 1;
      push @{$all{$1}}, $f;
    }
    elsif (/^([a-zA-Z0-9']+).*=/ and not ($1 eq "data"))
    {
      $d{$1} = 1;
    }
  }
  close I;
  print "$f\n";
  for (keys %d)
  {
    if (not exists $e{$_})
    {
      print "  $_\n";
    }
  }
}

print "\n*** Duplicate names:\n";
for (sort keys %all) {
  if (scalar(@{$all{$_}}) > 1) {
    print "$_: ".join(', ', @{$all{$_}})."\n";
  }
}
# vim: set ft=perl ts=8 sts=2 sw=2:
