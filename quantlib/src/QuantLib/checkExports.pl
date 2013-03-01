use strict;
use warnings;

for my $f (glob('*.hs */*.hs'))
{
  open I, "<$f";

  my %e = ();
  my %d = ();
  while (<I>)
  {
    if (/^  [, ] ([a-zA-Z0-9']+)$/)
    {
      $e{$1} = 1;
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
  # print join ",", keys(%e);
}
# vim: set ft=perl ts=8 sts=2 sw=2:
