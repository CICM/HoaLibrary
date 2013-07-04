<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:strip-space elements="*"/>
  
<!-- hoa custom markups -->

  <xsl:preserve-space elements="a"/>
  
  <xsl:variable name="lang" select="/chapter/hoa_custom/@lang"/>

    <xsl:template match="hoa_custom">
      <xsl:param name="lang"/>
      <xsl:param name="tutoname"/>
      <div id="hoa-top">
        <xsl:if test="@tutoname">
          <div id="hoa-top-langselect">
            <xsl:element name="a">
              <xsl:attribute name="href"><xsl:value-of select="@tutoname"/>.maxtut.xml</xsl:attribute>
              <xsl:if test="@lang='en'">
                <xsl:attribute name="class">current</xsl:attribute>
              </xsl:if>
              <xsl:value-of select="'EN'"/>
            </xsl:element>
            <span> | </span>
            <xsl:element name="a">
              <xsl:attribute name="href"><xsl:value-of select="@tutoname"/>.fr.maxtut.xml</xsl:attribute>
              <xsl:if test="@lang='fr'">
                <xsl:attribute name="class">current</xsl:attribute>
              </xsl:if>
              <xsl:value-of select="'FR'"/>
            </xsl:element>
          </div>
        </xsl:if>
        <div id="hoa_top_icon">        
          <a href="http://www.mshparisnord.fr/hoalibrary/">
            <img src="images/hoa-icon.png" width="80px" alt="hoaLibrary" style="padding:2px;"/>
          </a>
        </div>
      </div>
    </xsl:template>

    <xsl:template match="hoa_block">
      <div class="hoa-block">
        <xsl:apply-templates />
      </div>
    </xsl:template>

    <xsl:template match="hoa_h2">
      <h2 class="hoa-h2">
        <span class="borderleft"></span>
          <xsl:apply-templates />
      </h2>
    </xsl:template>

<!-- stylesheet -->
    <xsl:template match="hoa_style">        
      <style type="text/css">
        @import url("hoa_tut_style.css");
      </style>
    </xsl:template>


<!-- 
      See Also
      -->
  <xsl:template match="hoa_seealsolist">
    <div id="seealso_section">
      <xsl:choose>
        <xsl:when test="$lang='fr'">
          <h2>Voir aussi</h2>
        </xsl:when>
        <xsl:otherwise>
          <h2>See also</h2>
        </xsl:otherwise>
      </xsl:choose>
      <table>
        <tr>
          <th class="name">Name</th>
          <th class="description">Description</th>
        </tr>
        <xsl:for-each select="seealso">
          <tr>
            <td>
              <xsl:choose>
                <xsl:when test="@type='hoa-tut'">
                  <xsl:element name="a">
                    <xsl:choose>
                      <xsl:when test="$lang='fr'">
                        <xsl:attribute name="href"><xsl:value-of select="@name"/>.fr.maxtut.xml</xsl:attribute>
                      </xsl:when>
                      <xsl:otherwise>
                        <xsl:attribute name="href"><xsl:value-of select="@name"/>.maxtut.xml</xsl:attribute>
                      </xsl:otherwise>
                    </xsl:choose>
                    <xsl:value-of select="@name"/>
                  </xsl:element>
                </xsl:when>
                <xsl:when test="@type='hoa-object'">
                  <xsl:element name="a">
                    <xsl:choose>
                      <xsl:when test="$lang='fr'">
                        <xsl:attribute name="href"><xsl:value-of select="concat('../../refpages/hoa-ref/', @name)"/>.maxref.xml</xsl:attribute>
                      </xsl:when>
                      <xsl:otherwise>
                        <xsl:attribute name="href"><xsl:value-of select="@name"/>.maxref.xml</xsl:attribute>
                      </xsl:otherwise>
                    </xsl:choose>
                    <xsl:value-of select="@name"/>
                  </xsl:element>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:call-template name="handle_link">
                    <xsl:with-param name="linkname" select="@name" />
                    <xsl:with-param name="linktype" select="@type" />
                    <xsl:with-param name="linkmodule" select="@module" />
                    <xsl:with-param name="linkanchor" select="@anchor" />
                    <xsl:with-param name="linkdisplay" />
                  </xsl:call-template>
                </xsl:otherwise>
              </xsl:choose>
            </td>
            <td class="description">
              <xsl:apply-templates />
            </td>
          </tr>
        </xsl:for-each>
      </table>
    </div>
<!-- id="seealso_section" -->
  </xsl:template>


</xsl:stylesheet>
