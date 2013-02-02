for $f (glob("*.xml"))
{
    open I, "<$f";
    @l = <I>;
    close I;
    open O, ">$f";
    @text = ();
    $skip = 0;
    $inmem = 0;
    for (@l)
    {
	if (m!<memberdef!)
	{
	    @text = ();
	    push @text, $_;
	    $inmem = 1;
	}
	elsif ($inmem)
	{
	    if (m!<reimplements!)
	    {
		$skip = 1;
	    }
	    elsif (!$skip)
	    {
		push @text, $_;
	    }
	    if (m!</memberdef>!)
	    {
		if (!$skip)
		{
		    for (@text)
		    {
			print O $_;
		    }
		}
		$skip = 0;
		$inmem = 0;
	    }
	}
	else
	{
	    print O;
	}
    }
    close O;
}
