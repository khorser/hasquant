# create dirs f, v, e
# and run with `for f in *.txt ; do perl split.pl $f ; done'

@l = <>;
$c = shift @l;
chomp $c;
$c =~ tr/<:>/[_]/;
$c =~ tr/ //;

$in = "";
$inside = 0;
$name = "";
@def = ();
%names = ();

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
  if (/^ -(f|v|e)-/)
  {
    w();
    $in = $1;
    $inside = 0;
    next;
  }
  elsif (/^   (.*)/)
  {
    $inside = 1;
    push @def, $1;
  }
  elsif (/^  (\S.*)/)
  {
    if ($inside)
    {
      w();
      $inside = 0;
    }
    if (/^  (\w+)/)
    {
      $name = $1;
      $i = 0;
      while (exists $names{uc($name)})
      {
	  $i++;
	  $name = "$1#$i";
      }
      $names{uc($name)} = 1;
    }
    else
    {
      push @def, $1;
    }
  }
}
w();

# vim: set sw=2 sts=2 ts=8:
