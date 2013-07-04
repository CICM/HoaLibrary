<?xml version="1.0"?>

<!--
  Copyright (c) 2012 Cycling '74

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
  and associated documentation files (the "Software"), to deal in the Software without restriction, 
  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies 
  or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:strip-space elements="*"/>

  <xsl:include href="../_c74_vig_common.xsl"/> <!-- must come first - defines platform-specific stuff -->
  <xsl:include href="../../_c74_common.xsl"/>

  <xsl:template match="thesaurus">
    <table class="basestyle noframe" width="100%" border="0">
      <xsl:apply-templates />
    </table>
  </xsl:template>
  
  <xsl:template match="thesaurusentrygroup">
      <xsl:apply-templates />
  </xsl:template>
  
  <xsl:template match="thesaurusheader">
    <tr><th class="theader" width="100%" colspan="2" align="left">
      <xsl:apply-templates />
    </th></tr>
  </xsl:template>
  
  <xsl:template match="thesaurusentry">
    <tr>
      <xsl:apply-templates />
    </tr>
  </xsl:template>
  
  <xsl:template match="thesauruskey">
    <td class="tentry" width="35%">
      <xsl:apply-templates />
    </td>
  </xsl:template>
  
  <xsl:template match="thesaurusobjectlist">
    <xsl:variable name="objcount"><xsl:value-of select="count(./thesaurusobject)"/></xsl:variable>
    <xsl:if test="$objcount > 0">
      <td class="tentry">
        <xsl:for-each select="thesaurusobject">
          <xsl:apply-templates />
          <xsl:if test="position() != $objcount">, </xsl:if>
        </xsl:for-each>
      </td>
    </xsl:if>
  </xsl:template>
  
</xsl:stylesheet>

