@l = <>;
$c = shift @l;
chomp $c;

$in = "";
$inside = 0;
$name = "";
@def = ();
@names = ();

sub w
{
  if ($name)
  {
    open O, ">$in/$c^$name.txt";
    for (@def)
    {
      print O "$_\n";
    }
    $name = "";
    @def = ();
    close O;
  }
}

for (@l)
{
  chomp;
  if (/^ -(f|v)-/)
  {
    $in = $1;
    w();
    $inside = 0;
    next;
  }
  elsif (/^   /)
  {
    $inside = 1;
    push @def, $_;
  }
  elsif (/^  \S+/)
  {
    if ($inside)
    {
      w();
      $inside = 0;
    }
    if (/^  (\w+)/)
    {
      $name = $1;
    }
    else
    {
      push @def, $_;
    }
  }
}
w();

# vim: set sw=2 sts=2 ts=8:
