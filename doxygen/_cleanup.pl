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
	    elsif (m!<sectiondef kind="private-static-attrib">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="private-static-func">!)
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
	    elsif (m!<sectiondef kind="protected-static-attrib">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="protected-static-func">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="private-type">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="protected-type">!)
	    {
		$skip = "</sectiondef>";
	    }
	    elsif (m!<sectiondef kind="friend">!)
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
# :silent! argdo g/^\s*<\(derivedcompoundref\|reimplementedby\|basecompoundref\)/delete
# :silent! argdo g/^\s*<innerclass refid=.* prot="protected">/delete
# :silent! argdo g/^\s*<innerclass refid=.* prot="private">/delete
# :silent! argdo %s!C:/Develop/QuantLib-1.2.1/ql!!g
# :silent! argdo %s!class_quant_lib_1_1_\?!!g
# :silent! argdo %s!struct_quant_lib_1_1_\?!!g
# :silent! argdo %s!<ref refid="[^"]\+" kindref="compound">\([^<]\+\)</ref>!\1!g
#:silent! argdo %s/^\s*<sectiondef.*\n\s*<header.*\n\s*<description.*\n\s*<\/sectiondef>//
#:silent! argdo %s/^\s*<sectiondef.*\n.*\/sectiondef>//
#:silent! argdo %s/^\s*<sectiondef.*\n\/sectiondef>//
#:silent! argdo %s/^\s*<sectiondef.*\n\s*<header.*\n.*\/sectiondef>//
# :g/^\s*<sectiondef.*\n\s*<header.*\n.*\/sectiondef>/e
# :silent! argdo g/^$/delete
# :silent! xa
