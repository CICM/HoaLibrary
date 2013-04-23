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

#ifndef __JUCE_TEXTLAYOUT_JUCEHEADER__
#define __JUCE_TEXTLAYOUT_JUCEHEADER__

#include "juce_Font.h"
#include "../placement/juce_Justification.h"
class Graphics;

//==============================================================================
/**
    A Pre-formatted piece of text, which may contain multiple fonts and colours.

    A TextLayout is created from an AttributedString, and once created can be
    quickly drawn into a Graphics context.

    @see AttributedString
*/
class JUCE_API  TextLayout
{
public:
    /** Creates an empty layout.
        Having created a TextLayout, you can populate it using createLayout() or
        createLayoutWithBalancedLineLengths().
    */
    TextLayout();
    TextLayout (const TextLayout&);
    TextLayout& operator= (const TextLayout&);
   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
    TextLayout (TextLayout&& other) noexcept;
    TextLayout& operator= (TextLayout&&) noexcept;
   #endif

    /** Destructor. */
    ~TextLayout();

    //==============================================================================
    /** Creates a layout from the given attributed string.
        This will replace any data that is currently stored in the layout.
    */
    void createLayout (const AttributedString& text, float maxWidth);

    /** Creates a layout, attempting to choose a width which results in lines
        of a similar length.

        This will be slower than the normal createLayout method, but produces a
        tidier result.
    */
    void createLayoutWithBalancedLineLengths (const AttributedString& text, float maxWidth);

    /** Draws the layout within the specified area.
        The position of the text within the rectangle is controlled by the justification
        flags set in the original AttributedString that was used to create this layout.
    */
    void draw (Graphics& g, const Rectangle<float>& area) const;

    //==============================================================================
    /** A positioned glyph. */
    class JUCE_API  Glyph
    {
    public:
        Glyph (int glyphCode, const Point<float>& anchor, float width) noexcept;
        Glyph (const Glyph&) noexcept;
        Glyph& operator= (const Glyph&) noexcept;
        ~Glyph() noexcept;

        /** The code number of this glyph. */
        int glyphCode;

        /** The glyph's anchor point - this is relative to the line's origin.
            @see TextLayout::Line::lineOrigin
        */
        Point<float> anchor;

        float width;

    private:
        JUCE_LEAK_DETECTOR (Glyph)
    };

    //==============================================================================
    /** A sequence of glyphs with a common font and colour. */
    class JUCE_API  Run
    {
    public:
        Run() noexcept;
        Run (const Run&);
        Run (const Range<int>& stringRange, int numGlyphsToPreallocate);
        ~Run() noexcept;

        Font font;              /**< The run's font. */
        Colour colour;          /**< The run's colour. */
        Array<Glyph> glyphs;    /**< The glyphs in this run. */
        Range<int> stringRange; /**< The character range that this run represents in the
                                     original string that was used to create it. */
    private:
        Run& operator= (const Run&);
        JUCE_LEAK_DETECTOR (Run)
    };

    //==============================================================================
    /** A line containing a sequence of glyph-runs. */
    class JUCE_API  Line
    {
    public:
        Line() noexcept;
        Line (const Line&);
        Line (const Range<int>& stringRange, const Point<float>& lineOrigin,
              float ascent, float descent, float leading, int numRunsToPreallocate);
        ~Line() noexcept;

        /** Returns the X position range which contains all the glyphs in this line. */
        Range<float> getLineBoundsX() const noexcept;

        OwnedArray<Run> runs;           /**< The glyph-runs in this line. */
        Range<int> stringRange;         /**< The character range that this line represents in the
                                             original string that was used to create it. */
        Point<float> lineOrigin;        /**< The line's baseline origin. */
        float ascent, descent, leading;

    private:
        Line& operator= (const Line&);
        JUCE_LEAK_DETECTOR (Line)
    };

    //==============================================================================
    /** Returns the maximum width of the content. */
    float getWidth() const noexcept     { return width; }

    /** Returns the maximum height of the content. */
    float getHeight() const noexcept;

    /** Returns the number of lines in the layout. */
    int getNumLines() const noexcept    { return lines.size(); }

    /** Returns one of the lines. */
    Line& getLine (int index) const;

    /** Adds a line to the layout. The layout will take ownership of this line object
        and will delete it when it is no longer needed. */
    void addLine (Line* line);

    /** Pre-allocates space for the specified number of lines. */
    void ensureStorageAllocated (int numLinesNeeded);

private:
    OwnedArray<Line> lines;
    float width;
    Justification justification;

    void createStandardLayout (const AttributedString&);
    bool createNativeLayout (const AttributedString&);
    void recalculateWidth (const AttributedString&);

    JUCE_LEAK_DETECTOR (TextLayout)
};

#endif   // __JUCE_TEXTLAYOUT_JUCEHEADER__
