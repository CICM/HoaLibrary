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

static inline void blurDataTriplets (uint8* d, int num, const int delta) noexcept
{
    uint32 last = d[0];
    d[0] = (uint8) ((d[0] + d[delta] + 1) / 3);
    d += delta;

    num -= 2;

    do
    {
        const uint32 newLast = d[0];
        d[0] = (uint8) ((last + d[0] + d[delta] + 1) / 3);
        d += delta;
        last = newLast;
    }
    while (--num > 0);

    d[0] = (uint8) ((last + d[0] + 1) / 3);
}

static void blurSingleChannelImage (uint8* const data, const int width, const int height,
                                    const int lineStride, const int repetitions) noexcept
{
    jassert (width > 2 && height > 2);

    for (int y = 0; y < height; ++y)
        for (int i = repetitions; --i >= 0;)
            blurDataTriplets (data + lineStride * y, width, 1);

    for (int x = 0; x < width; ++x)
        for (int i = repetitions; --i >= 0;)
            blurDataTriplets (data + x, height, lineStride);
}

static void blurSingleChannelImage (Image& image, int radius)
{
    const Image::BitmapData bm (image, Image::BitmapData::readWrite);
    blurSingleChannelImage (bm.data, bm.width, bm.height, bm.lineStride, 2 * radius);
}

//==============================================================================
DropShadow::DropShadow() noexcept
    : colour (0x90000000), radius (4)
{
}

DropShadow::DropShadow (const Colour& shadowColour, const int r, const Point<int>& o) noexcept
    : colour (shadowColour), radius (r), offset (o)
{
    jassert (radius > 0);
}

void DropShadow::drawForImage (Graphics& g, const Image& srcImage) const
{
    jassert (radius > 0);

    if (srcImage.isValid())
    {
        Image shadowImage (srcImage.convertedToFormat (Image::SingleChannel));
        shadowImage.duplicateIfShared();

        blurSingleChannelImage (shadowImage, radius);

        g.setColour (colour);
        g.drawImageAt (shadowImage, offset.x, offset.y, true);
    }
}

void DropShadow::drawForPath (Graphics& g, const Path& path) const
{
    jassert (radius > 0);

    const Rectangle<int> area ((path.getBounds().getSmallestIntegerContainer() + offset)
                                   .expanded (radius + 1)
                                   .getIntersection (g.getClipBounds().expanded (radius + 1)));

    if (area.getWidth() > 2 && area.getHeight() > 2)
    {
        Image renderedPath (Image::SingleChannel, area.getWidth(), area.getHeight(), true);

        {
            Graphics g2 (renderedPath);
            g2.setColour (Colours::white);
            g2.fillPath (path, AffineTransform::translation ((float) (offset.x - area.getX()),
                                                             (float) (offset.y - area.getY())));
        }

        blurSingleChannelImage (renderedPath, radius);

        g.setColour (colour);
        g.drawImageAt (renderedPath, area.getX(), area.getY(), true);
    }
}

//==============================================================================
DropShadowEffect::DropShadowEffect() {}
DropShadowEffect::~DropShadowEffect() {}

void DropShadowEffect::setShadowProperties (const DropShadow& newShadow)
{
    shadow = newShadow;
}

void DropShadowEffect::applyEffect (Image& image, Graphics& g, float scaleFactor, float alpha)
{
    DropShadow s (shadow);
    s.radius = roundToInt (s.radius * scaleFactor);
    s.colour = s.colour.withMultipliedAlpha (alpha);
    s.offset.x = roundToInt (s.offset.x * scaleFactor);
    s.offset.y = roundToInt (s.offset.y * scaleFactor);

    s.drawForImage (g, image);

    g.setOpacity (alpha);
    g.drawImageAt (image, 0, 0);
}
