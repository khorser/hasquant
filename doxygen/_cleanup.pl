for $f (glob("*.xml"))
{
    $skip = "";
    open I, "<$f";
    @l = <I>;
    close I;
    open O, ">$f";
    for (@l)
    {
	if ($skip)
	{
	    if (m!$skip!)
	    {
		$skip = 0;
	    }
	}
	else
	{
	    if (m!<inheritancegraph>!)
	    {
		$skip = "</inheritancegraph>";
	    }
	    elsif (m!<collaborationgraph>!)
	    {
		$skip = "</collaborationgraph>";
	    }
	    elsif (m!<listofallmembers>!)
	    {
		$skip = "</listofallmembers>";
	    }
	    elsif (m!<sectiondef kind="private-attrib">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="private-func">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="protected-attrib">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="protected-func">!)
	    {
		$skip = "</sectiondef>";
	    }
	    else
	    {
		print O "$_";
	    }
	}
    }
    close O;
}

# extra cleanup in Vim:
# :silent! argdo %s/^\s*<\(.*\)>\n\s*<\/\1>/
# :silent! argdo g/^$/delete
# :silent! argdo g/^\s*<\(derivedcompoundref\|reimplementedby\|basecompoundref\)/delete
# :silent! xa

