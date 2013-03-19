/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_TYPEFACE_JUCEHEADER__
#define __JUCE_TYPEFACE_JUCEHEADER__

class Path;
class Font;
class EdgeTable;
class AffineTransform;


//==============================================================================
/**
    A typeface represents a size-independent font.

    This base class is abstract, but calling createSystemTypefaceFor() will return
    a platform-specific subclass that can be used.

    The CustomTypeface subclass allow you to build your own typeface, and to
    load and save it in the Juce typeface format.

    Normally you should never need to deal directly with Typeface objects - the Font
    class does everything you typically need for rendering text.

    @see CustomTypeface, Font
*/
class JUCE_API  Typeface  : public ReferenceCountedObject
{
public:
    //==============================================================================
    /** A handy typedef for a pointer to a typeface. */
    typedef ReferenceCountedObjectPtr <Typeface> Ptr;

    //==============================================================================
    /** Returns the font family of the typeface.
        @see Font::getTypefaceName
    */
    const String& getName() const noexcept      { return name; }

    //==============================================================================
    /** Returns the font style of the typeface.
        @see Font::getTypefaceStyle
    */
    const String& getStyle() const noexcept     { return style; }

    //==============================================================================
    /** Creates a new system typeface. */
    static Ptr createSystemTypefaceFor (const Font& font);

    //==============================================================================
    /** Destructor. */
    virtual ~Typeface();

    /** Returns true if this typeface can be used to render the specified font.
        When called, the font will already have been checked to make sure that its name and
        style flags match the typeface.
    */
    virtual bool isSuitableForFont (const Font&) const          { return true; }

    /** Returns the ascent of the font, as a proportion of its height.
        The height is considered to always be normalised as 1.0, so this will be a
        value less that 1.0, indicating the proportion of the font that lies above
        its baseline.
    */
    virtual float getAscent() const = 0;

    /** Returns the descent of the font, as a proportion of its height.
        The height is considered to always be normalised as 1.0, so this will be a
        value less that 1.0, indicating the proportion of the font that lies below
        its baseline.
    */
    virtual float getDescent() const = 0;

    /** Returns the value by which you should multiply a juce font-height value to
        convert it to the equivalent point-size.
    */
    virtual float getHeightToPointsFactor() const = 0;

    /** Measures the width of a line of text.
        The distance returned is based on the font having an normalised height of 1.0.
        You should never need to call this directly! Use Font::getStringWidth() instead!
    */
    virtual float getStringWidth (const String& text) = 0;

    /** Converts a line of text into its glyph numbers and their positions.
        The distances returned are based on the font having an normalised height of 1.0.
        You should never need to call this directly! Use Font::getGlyphPositions() instead!
    */
    virtual void getGlyphPositions (const String& text, Array <int>& glyphs, Array<float>& xOffsets) = 0;

    /** Returns the outline for a glyph.
        The path returned will be normalised to a font height of 1.0.
    */
    virtual bool getOutlineForGlyph (int glyphNumber, Path& path) = 0;

    /** Returns a new EdgeTable that contains the path for the givem glyph, with the specified transform applied. */
    virtual EdgeTable* getEdgeTableForGlyph (int glyphNumber, const AffineTransform& transform);

    /** Returns true if the typeface uses hinting. */
    virtual bool isHinted() const                           { return false; }

    //==============================================================================
    /** Changes the number of fonts that are cached in memory. */
    static void setTypefaceCacheSize (int numFontsToCache);

    /** Clears any fonts that are currently cached in memory. */
    static void clearTypefaceCache();

protected:
    //==============================================================================
    String name, style;

    Typeface (const String& name, const String& style) noexcept;

    static Ptr getFallbackTypeface();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Typeface)
};


#endif   // __JUCE_TYPEFACE_JUCEHEADER__
