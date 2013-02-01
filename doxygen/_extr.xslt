<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="text"/>

<xsl:template match="/doxygen">
    <xsl:for-each select="compounddef">
	<xsl:call-template name="compounddef"/>
    </xsl:for-each>
</xsl:template>

<xsl:template name="compounddef">
    <xsl:value-of select="compoundname"/>
    <xsl:if test="briefdescription">
	<xsl:text>&#xa;</xsl:text>
	<xsl:value-of select="briefdescription"/>
    </xsl:if>
    <xsl:if test="detaileddescription">
	<xsl:text>&#xa;</xsl:text>
	<xsl:value-of select="detaileddescription"/>
    </xsl:if>
    <xsl:text>&#xa;</xsl:text>
    <xsl:for-each select="sectiondef">
	<xsl:call-template name="section"/>
    </xsl:for-each>
</xsl:template>


<xsl:template name="section">
    <xsl:for-each select="memberdef[@kind='function']">
	<xsl:text>&#xa;MN  </xsl:text>
	<xsl:value-of select="name"/>
	<xsl:if test="type">
	    <xsl:text>&#xa;MT  </xsl:text>
	    <xsl:value-of select="type"/>
	</xsl:if>
	<xsl:if test="briefdescription">
	    <xsl:text>&#xa;</xsl:text>
	    <xsl:value-of select="briefdescription"/>
	</xsl:if>
	<xsl:if test="detaileddescription">
	    <xsl:text>&#xa;</xsl:text>
	    <xsl:value-of select="detaileddescription"/>
	</xsl:if>
	<xsl:for-each select="param">
	    <xsl:text>&#xa;AT    </xsl:text>
	    <xsl:value-of select="type"/>
	    <xsl:text>&#xa;AN    </xsl:text>
	    <xsl:value-of select="declname"/>
	    <xsl:if test="defval">
		<xsl:text>&#xa;AD    </xsl:text>
		<xsl:value-of select="defval"/>
	    </xsl:if>
	    <xsl:if test="briefdescription">
		<xsl:text>&#xa;</xsl:text>
		<xsl:value-of select="briefdescription"/>
	    </xsl:if>
	    <xsl:if test="detaileddescription">
		<xsl:text>&#xa;</xsl:text>
		<xsl:value-of select="detaileddescription"/>
	    </xsl:if>
	</xsl:for-each>
    </xsl:for-each>

    <xsl:for-each select="memberdef[@kind='enum']">
	<xsl:text>&#xa;EN  </xsl:text>
	<xsl:value-of select="name"/>
	<xsl:if test="briefdescription">
	    <xsl:text>&#xa;</xsl:text>
	    <xsl:value-of select="briefdescription"/>
	</xsl:if>
	<xsl:if test="detaileddescription">
	    <xsl:text>&#xa;</xsl:text>
	    <xsl:value-of select="detaileddescription"/>
	</xsl:if>
	<xsl:text>&#xa;</xsl:text>
	<xsl:for-each select="enumvalue">
	    <xsl:text>&#xa;EV    </xsl:text>
	    <xsl:value-of select="name"/>
	    <xsl:text>&#xa;</xsl:text>
	    <xsl:if test="briefdescription">
		<xsl:text>&#xa;</xsl:text>
		<xsl:value-of select="briefdescription"/>
	    </xsl:if>
	    <xsl:if test="detaileddescription">
		<xsl:text>&#xa;</xsl:text>
		<xsl:value-of select="detaileddescription"/>
	    </xsl:if>
	</xsl:for-each>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
