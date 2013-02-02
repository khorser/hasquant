<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:str="http://exslt.org/strings" extension-element-prefixes="str">
<xsl:output method="text"/>

<xsl:template match="/doxygen">
    <xsl:for-each select="compounddef[(@kind='class' and @prot='public') or @kind='namespace']">
	<xsl:call-template name="compounddef"/>
    </xsl:for-each>
</xsl:template>

<xsl:template name="compounddef">
    <xsl:value-of select="compoundname"/>
    <xsl:call-template name="doc">
	<xsl:with-param name="level" select="1"/>
	<xsl:with-param name="prefix" select="'|'"/>
    </xsl:call-template>
    <xsl:text>&#xa;</xsl:text>
    <xsl:for-each select="sectiondef">
	<xsl:call-template name="section"/>
    </xsl:for-each>
</xsl:template>

<xsl:variable name='nl'><xsl:text>&#xa;</xsl:text></xsl:variable>

<xsl:template name="doc">
    <xsl:param name="level"/>
    <xsl:param name="prefix"/>
    <xsl:if test="str:replace(str:replace(briefdescription, $nl, ' '), ' ','')!=''">
	<xsl:call-template name="newline">
	    <xsl:with-param name="level" select="$level"/>
	    <xsl:with-param name="leading">
		<xsl:text>-- </xsl:text>
		<xsl:value-of select="$prefix"/>
	    </xsl:with-param>
	    <xsl:with-param name="select" select="normalize-space(str:replace(briefdescription, $nl, ' '))"/>
	</xsl:call-template>
    </xsl:if>
    <xsl:if test="str:replace(str:replace(detaileddescription, $nl, ' '), ' ','')!=''">
	<xsl:call-template name="newline">
	    <xsl:with-param name="level" select="$level"/>
	    <xsl:with-param name="leading">
		<xsl:text>-- </xsl:text>
		<xsl:value-of select="$prefix"/>
	    </xsl:with-param>
	    <xsl:with-param name="select" select="normalize-space(str:replace(detaileddescription, $nl, ' '))"/>
	</xsl:call-template>
    </xsl:if>
</xsl:template>

<xsl:template name="newline">
    <xsl:param name="level"/>
    <xsl:param name="leading"/>
    <xsl:param name="select"/>
    <xsl:value-of select="$nl"/>
    <xsl:value-of select="str:padding($level, ' ')"/>
    <xsl:value-of select="$leading"/>
    <xsl:if test="$select!=''">
	<xsl:value-of select="$select"/>
    </xsl:if>
</xsl:template>

<xsl:template name="section">
    <xsl:for-each select="memberdef[@kind='function' and @prot='public']">
	<xsl:call-template name="doc">
	    <xsl:with-param name="level" select="2"/>
	    <xsl:with-param name="prefix" select="'|'"/>
	</xsl:call-template>

	<xsl:call-template name="newline">
	    <xsl:with-param name="level" select="2"/>
	    <xsl:with-param name="select" select="name"/>
	</xsl:call-template>

	<xsl:call-template name="newline">
	    <xsl:with-param name="level" select="3"/>
	    <xsl:with-param name="leading" select="'->'"/>
	    <xsl:with-param name="select" select="type"/>
	</xsl:call-template>

	<xsl:for-each select="param">
	    <xsl:call-template name="newline">
		<xsl:with-param name="level" select="3"/>
		<xsl:with-param name="leading" select="'::'"/>
		<xsl:with-param name="select" select="type"/>
	    </xsl:call-template>

	    <xsl:if test="defval!=''">
		<xsl:call-template name="newline">
		    <xsl:with-param name="level" select="3"/>
		    <xsl:with-param name="leading" select="'='"/>
		    <xsl:with-param name="select" select="defval"/>
		</xsl:call-template>
	    </xsl:if>

	    <xsl:call-template name="newline">
		<xsl:with-param name="level" select="3"/>
		<xsl:with-param name="leading">
		    <xsl:text>-- ^</xsl:text>
		</xsl:with-param>
		<xsl:with-param name="select" select="declname"/>
	    </xsl:call-template>

	    <xsl:call-template name="doc">
		<xsl:with-param name="level" select="3"/>
		<xsl:with-param name="prefix" select="'^'"/>
	    </xsl:call-template>
	</xsl:for-each>
    </xsl:for-each>

    <xsl:for-each select="memberdef[@kind='enum']">
	<xsl:call-template name="doc">
	    <xsl:with-param name="level" select="2"/>
	    <xsl:with-param name="prefix" select="'|'"/>
	</xsl:call-template>
	<xsl:call-template name="newline">
	    <xsl:with-param name="level" select="2"/>
	    <xsl:with-param name="select" select="name"/>
	</xsl:call-template>
	<xsl:for-each select="enumvalue">
	    <xsl:call-template name="newline">
		<xsl:with-param name="level" select="3"/>
		<xsl:with-param name="select" select="name"/>
	    </xsl:call-template>

	    <xsl:call-template name="doc">
		<xsl:with-param name="level" select="3"/>
		<xsl:with-param name="prefix" select="'^'"/>
	    </xsl:call-template>
	</xsl:for-each>
    </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
