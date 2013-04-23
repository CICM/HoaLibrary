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

class SVGState
{
public:
    //==============================================================================
    SVGState (const XmlElement* const topLevel)
        : topLevelXml (topLevel),
          elementX (0), elementY (0),
          width (512), height (512),
          viewBoxW (0), viewBoxH (0)
    {
    }

    //==============================================================================
    Drawable* parseSVGElement (const XmlElement& xml)
    {
        if (! xml.hasTagName ("svg"))
            return nullptr;

        DrawableComposite* const drawable = new DrawableComposite();

        drawable->setName (xml.getStringAttribute ("id"));

        SVGState newState (*this);

        if (xml.hasAttribute ("transform"))
            newState.addTransform (xml);

        newState.elementX = getCoordLength (xml.getStringAttribute ("x",      String (newState.elementX)), viewBoxW);
        newState.elementY = getCoordLength (xml.getStringAttribute ("y",      String (newState.elementY)), viewBoxH);
        newState.width    = getCoordLength (xml.getStringAttribute ("width",  String (newState.width)),    viewBoxW);
        newState.height   = getCoordLength (xml.getStringAttribute ("height", String (newState.height)),   viewBoxH);

        if (newState.width  <= 0) newState.width  = 100;
        if (newState.height <= 0) newState.height = 100;

        if (xml.hasAttribute ("viewBox"))
        {
            const String viewBoxAtt (xml.getStringAttribute ("viewBox"));
            String::CharPointerType viewParams (viewBoxAtt.getCharPointer());
            Point<float> vxy, vwh;

            if (parseCoords (viewParams, vxy, true)
                 && parseCoords (viewParams, vwh, true)
                 && vwh.x > 0
                 && vwh.y > 0)
            {
                newState.viewBoxW = vwh.x;
                newState.viewBoxH = vwh.y;

                int placementFlags = 0;

                const String aspect (xml.getStringAttribute ("preserveAspectRatio"));

                if (aspect.containsIgnoreCase ("none"))
                {
                    placementFlags = RectanglePlacement::stretchToFit;
                }
                else
                {
                    if (aspect.containsIgnoreCase ("slice"))        placementFlags |= RectanglePlacement::fillDestination;

                    if (aspect.containsIgnoreCase ("xMin"))         placementFlags |= RectanglePlacement::xLeft;
                    else if (aspect.containsIgnoreCase ("xMax"))    placementFlags |= RectanglePlacement::xRight;
                    else                                            placementFlags |= RectanglePlacement::xMid;

                    if (aspect.containsIgnoreCase ("yMin"))         placementFlags |= RectanglePlacement::yTop;
                    else if (aspect.containsIgnoreCase ("yMax"))    placementFlags |= RectanglePlacement::yBottom;
                    else                                            placementFlags |= RectanglePlacement::yMid;
                }

                newState.transform = RectanglePlacement (placementFlags)
                                        .getTransformToFit (Rectangle<float> (vxy.x, vxy.y, vwh.x, vwh.y),
                                                            Rectangle<float> (newState.width, newState.height))
                                        .followedBy (newState.transform);
            }
        }
        else
        {
            if (viewBoxW == 0)  newState.viewBoxW = newState.width;
            if (viewBoxH == 0)  newState.viewBoxH = newState.height;
        }

        newState.parseSubElements (xml, drawable);

        drawable->setContentArea (RelativeRectangle (Rectangle<float> (newState.viewBoxW, newState.viewBoxH)));
        drawable->resetBoundingBoxToContentArea();

        return drawable;
    }

private:
    //==============================================================================
    const XmlElement* const topLevelXml;
    float elementX, elementY, width, height, viewBoxW, viewBoxH;
    AffineTransform transform;
    String cssStyleText;

    //==============================================================================
    void parseSubElements (const XmlElement& xml, DrawableComposite* const parentDrawable)
    {
        forEachXmlChildElement (xml, e)
        {
            Drawable* d = nullptr;

            if (e->hasTagName ("g"))                d = parseGroupElement (*e);
            else if (e->hasTagName ("svg"))         d = parseSVGElement (*e);
            else if (e->hasTagName ("path"))        d = parsePath (*e);
            else if (e->hasTagName ("rect"))        d = parseRect (*e);
            else if (e->hasTagName ("circle"))      d = parseCircle (*e);
            else if (e->hasTagName ("ellipse"))     d = parseEllipse (*e);
            else if (e->hasTagName ("line"))        d = parseLine (*e);
            else if (e->hasTagName ("polyline"))    d = parsePolygon (*e, true);
            else if (e->hasTagName ("polygon"))     d = parsePolygon (*e, false);
            else if (e->hasTagName ("text"))        d = parseText (*e);
            else if (e->hasTagName ("switch"))      d = parseSwitch (*e);
            else if (e->hasTagName ("style"))       parseCSSStyle (*e);

            parentDrawable->addAndMakeVisible (d);
        }
    }

    DrawableComposite* parseSwitch (const XmlElement& xml)
    {
        if (const XmlElement* const group = xml.getChildByName ("g"))
            return parseGroupElement (*group);

        return nullptr;
    }

    DrawableComposite* parseGroupElement (const XmlElement& xml)
    {
        DrawableComposite* const drawable = new DrawableComposite();

        drawable->setName (xml.getStringAttribute ("id"));

        if (xml.hasAttribute ("transform"))
        {
            SVGState newState (*this);
            newState.addTransform (xml);

            newState.parseSubElements (xml, drawable);
        }
        else
        {
            parseSubElements (xml, drawable);
        }

        drawable->resetContentAreaAndBoundingBoxToFitChildren();
        return drawable;
    }

    //==============================================================================
    Drawable* parsePath (const XmlElement& xml) const
    {
        const String dAttribute (xml.getStringAttribute ("d").trimStart());
        String::CharPointerType d (dAttribute.getCharPointer());
        Path path;

        if (getStyleAttribute (&xml, "fill-rule").trim().equalsIgnoreCase ("evenodd"))
            path.setUsingNonZeroWinding (false);

        Point<float> subpathStart, last, last2, p1, p2, p3;
        juce_wchar lastCommandChar = 0;
        bool isRelative = true;
        bool carryOn = true;

        const CharPointer_ASCII validCommandChars ("MmLlHhVvCcSsQqTtAaZz");

        while (! d.isEmpty())
        {
            if (validCommandChars.indexOf (*d) >= 0)
            {
                lastCommandChar = d.getAndAdvance();
                isRelative = (lastCommandChar >= 'a' && lastCommandChar <= 'z');
            }

            switch (lastCommandChar)
            {
            case 'M':
            case 'm':
            case 'L':
            case 'l':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    if (isRelative)
                        p1 += last;

                    if (lastCommandChar == 'M' || lastCommandChar == 'm')
                    {
                        subpathStart = p1;
                        path.startNewSubPath (p1);
                        lastCommandChar = 'l';
                    }
                    else
                        path.lineTo (p1);

                    last2 = last;
                    last = p1;
                }
                break;

            case 'H':
            case 'h':
                if (parseCoord (d, p1.x, false, true))
                {
                    if (isRelative)
                        p1.x += last.x;

                    path.lineTo (p1.x, last.y);

                    last2.x = last.x;
                    last.x = p1.x;
                }
                else
                {
                    ++d;
                }
                break;

            case 'V':
            case 'v':
                if (parseCoord (d, p1.y, false, false))
                {
                    if (isRelative)
                        p1.y += last.y;

                    path.lineTo (last.x, p1.y);

                    last2.y = last.y;
                    last.y = p1.y;
                }
                else
                {
                    ++d;
                }
                break;

            case 'C':
            case 'c':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p2, false)
                     && parseCoordsOrSkip (d, p3, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p2 += last;
                        p3 += last;
                    }

                    path.cubicTo (p1, p2, p3);

                    last2 = p2;
                    last = p3;
                }
                break;

            case 'S':
            case 's':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p3, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p3 += last;
                    }

                    p2 = last + (last - last2);
                    path.cubicTo (p2, p1, p3);

                    last2 = p1;
                    last = p3;
                }
                break;

            case 'Q':
            case 'q':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p2, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p2 += last;
                    }

                    path.quadraticTo (p1, p2);

                    last2 = p1;
                    last = p2;
                }
                break;

            case 'T':
            case 't':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    if (isRelative)
                        p1 += last;

                    p2 = last + (last - last2);
                    path.quadraticTo (p2, p1);

                    last2 = p2;
                    last = p1;
                }
                break;

            case 'A':
            case 'a':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    String num;

                    if (parseNextNumber (d, num, false))
                    {
                        const float angle = num.getFloatValue() * (180.0f / float_Pi);

                        if (parseNextNumber (d, num, false))
                        {
                            const bool largeArc = num.getIntValue() != 0;

                            if (parseNextNumber (d, num, false))
                            {
                                const bool sweep = num.getIntValue() != 0;

                                if (parseCoordsOrSkip (d, p2, false))
                                {
                                    if (isRelative)
                                        p2 += last;

                                    if (last != p2)
                                    {
                                        double centreX, centreY, startAngle, deltaAngle;
                                        double rx = p1.x, ry = p1.y;

                                        endpointToCentreParameters (last.x, last.y, p2.x, p2.y,
                                                                    angle, largeArc, sweep,
                                                                    rx, ry, centreX, centreY,
                                                                    startAngle, deltaAngle);

                                        path.addCentredArc ((float) centreX, (float) centreY,
                                                            (float) rx, (float) ry,
                                                            angle, (float) startAngle, (float) (startAngle + deltaAngle),
                                                            false);

                                        path.lineTo (p2);
                                    }

                                    last2 = last;
                                    last = p2;
                                }
                            }
                        }
                    }
                }

                break;

            case 'Z':
            case 'z':
                path.closeSubPath();
                last = last2 = subpathStart;
                d = d.findEndOfWhitespace();
                lastCommandChar = 'M';
                break;

            default:
                carryOn = false;
                break;
            }

            if (! carryOn)
                break;
        }

        return parseShape (xml, path);
    }

    Drawable* parseRect (const XmlElement& xml) const
    {
        Path rect;

        const bool hasRX = xml.hasAttribute ("rx");
        const bool hasRY = xml.hasAttribute ("ry");

        if (hasRX || hasRY)
        {
            float rx = getCoordLength (xml.getStringAttribute ("rx"), viewBoxW);
            float ry = getCoordLength (xml.getStringAttribute ("ry"), viewBoxH);

            if (! hasRX)
                rx = ry;
            else if (! hasRY)
                ry = rx;

            rect.addRoundedRectangle (getCoordLength (xml.getStringAttribute ("x"), viewBoxW),
                                      getCoordLength (xml.getStringAttribute ("y"), viewBoxH),
                                      getCoordLength (xml.getStringAttribute ("width"), viewBoxW),
                                      getCoordLength (xml.getStringAttribute ("height"), viewBoxH),
                                      rx, ry);
        }
        else
        {
            rect.addRectangle (getCoordLength (xml.getStringAttribute ("x"), viewBoxW),
                               getCoordLength (xml.getStringAttribute ("y"), viewBoxH),
                               getCoordLength (xml.getStringAttribute ("width"), viewBoxW),
                               getCoordLength (xml.getStringAttribute ("height"), viewBoxH));
        }

        return parseShape (xml, rect);
    }

    Drawable* parseCircle (const XmlElement& xml) const
    {
        Path circle;

        const float cx = getCoordLength (xml.getStringAttribute ("cx"), viewBoxW);
        const float cy = getCoordLength (xml.getStringAttribute ("cy"), viewBoxH);
        const float radius = getCoordLength (xml.getStringAttribute ("r"), viewBoxW);

        circle.addEllipse (cx - radius, cy - radius, radius * 2.0f, radius * 2.0f);

        return parseShape (xml, circle);
    }

    Drawable* parseEllipse (const XmlElement& xml) const
    {
        Path ellipse;

        const float cx      = getCoordLength (xml.getStringAttribute ("cx"), viewBoxW);
        const float cy      = getCoordLength (xml.getStringAttribute ("cy"), viewBoxH);
        const float radiusX = getCoordLength (xml.getStringAttribute ("rx"), viewBoxW);
        const float radiusY = getCoordLength (xml.getStringAttribute ("ry"), viewBoxH);

        ellipse.addEllipse (cx - radiusX, cy - radiusY, radiusX * 2.0f, radiusY * 2.0f);

        return parseShape (xml, ellipse);
    }

    Drawable* parseLine (const XmlElement& xml) const
    {
        Path line;

        const float x1 = getCoordLength (xml.getStringAttribute ("x1"), viewBoxW);
        const float y1 = getCoordLength (xml.getStringAttribute ("y1"), viewBoxH);
        const float x2 = getCoordLength (xml.getStringAttribute ("x2"), viewBoxW);
        const float y2 = getCoordLength (xml.getStringAttribute ("y2"), viewBoxH);

        line.startNewSubPath (x1, y1);
        line.lineTo (x2, y2);

        return parseShape (xml, line);
    }

    Drawable* parsePolygon (const XmlElement& xml, const bool isPolyline) const
    {
        const String pointsAtt (xml.getStringAttribute ("points"));
        String::CharPointerType points (pointsAtt.getCharPointer());
        Path path;
        Point<float> p;

        if (parseCoords (points, p, true))
        {
            Point<float> first (p), last;

            path.startNewSubPath (first);

            while (parseCoords (points, p, true))
            {
                last = p;
                path.lineTo (p);
            }

            if ((! isPolyline) || first == last)
                path.closeSubPath();
        }

        return parseShape (xml, path);
    }

    //==============================================================================
    Drawable* parseShape (const XmlElement& xml, Path& path,
                          const bool shouldParseTransform = true) const
    {
        if (shouldParseTransform && xml.hasAttribute ("transform"))
        {
            SVGState newState (*this);
            newState.addTransform (xml);

            return newState.parseShape (xml, path, false);
        }

        DrawablePath* dp = new DrawablePath();
        dp->setName (xml.getStringAttribute ("id"));
        dp->setFill (Colours::transparentBlack);

        path.applyTransform (transform);
        dp->setPath (path);

        Path::Iterator iter (path);

        bool containsClosedSubPath = false;
        while (iter.next())
        {
            if (iter.elementType == Path::Iterator::closePath)
            {
                containsClosedSubPath = true;
                break;
            }
        }

        dp->setFill (getPathFillType (path,
                                      getStyleAttribute (&xml, "fill"),
                                      getStyleAttribute (&xml, "fill-opacity"),
                                      getStyleAttribute (&xml, "opacity"),
                                      containsClosedSubPath ? Colours::black
                                                            : Colours::transparentBlack));

        const String strokeType (getStyleAttribute (&xml, "stroke"));

        if (strokeType.isNotEmpty() && ! strokeType.equalsIgnoreCase ("none"))
        {
            dp->setStrokeFill (getPathFillType (path, strokeType,
                                                getStyleAttribute (&xml, "stroke-opacity"),
                                                getStyleAttribute (&xml, "opacity"),
                                                Colours::transparentBlack));

            dp->setStrokeType (getStrokeFor (&xml));
        }

        return dp;
    }

    const XmlElement* findLinkedElement (const XmlElement* e) const
    {
        const String id (e->getStringAttribute ("xlink:href"));

        if (! id.startsWithChar ('#'))
            return nullptr;

        return findElementForId (topLevelXml, id.substring (1));
    }

    void addGradientStopsIn (ColourGradient& cg, const XmlElement* const fillXml) const
    {
        if (fillXml != nullptr)
        {
            forEachXmlChildElementWithTagName (*fillXml, e, "stop")
            {
                int index = 0;
                Colour col (parseColour (getStyleAttribute  (e, "stop-color"), index, Colours::black));

                const String opacity (getStyleAttribute (e, "stop-opacity", "1"));
                col = col.withMultipliedAlpha (jlimit (0.0f, 1.0f, opacity.getFloatValue()));

                double offset = e->getDoubleAttribute ("offset");

                if (e->getStringAttribute ("offset").containsChar ('%'))
                    offset *= 0.01;

                cg.addColour (jlimit (0.0, 1.0, offset), col);
            }
        }
    }

    FillType getGradientFillType (const XmlElement* fillXml,
                                  const Path& path,
                                  const float opacity) const
    {
        ColourGradient gradient;

        addGradientStopsIn (gradient, findLinkedElement (fillXml));
        addGradientStopsIn (gradient, fillXml);

        if (gradient.getNumColours() > 0)
        {
            gradient.addColour (0.0, gradient.getColour (0));
            gradient.addColour (1.0, gradient.getColour (gradient.getNumColours() - 1));
        }
        else
        {
            gradient.addColour (0.0, Colours::black);
            gradient.addColour (1.0, Colours::black);
        }

        if (opacity < 1.0f)
            gradient.multiplyOpacity (opacity);

        jassert (gradient.getNumColours() > 0);

        gradient.isRadial = fillXml->hasTagName ("radialGradient");

        float gradientWidth = viewBoxW;
        float gradientHeight = viewBoxH;
        float dx = 0.0f;
        float dy = 0.0f;

        const bool userSpace = fillXml->getStringAttribute ("gradientUnits").equalsIgnoreCase ("userSpaceOnUse");

        if (! userSpace)
        {
            const Rectangle<float> bounds (path.getBounds());
            dx = bounds.getX();
            dy = bounds.getY();
            gradientWidth = bounds.getWidth();
            gradientHeight = bounds.getHeight();
        }

        if (gradient.isRadial)
        {
            if (userSpace)
                gradient.point1.setXY (dx + getCoordLength (fillXml->getStringAttribute ("cx", "50%"), gradientWidth),
                                       dy + getCoordLength (fillXml->getStringAttribute ("cy", "50%"), gradientHeight));
            else
                gradient.point1.setXY (dx + gradientWidth  * getCoordLength (fillXml->getStringAttribute ("cx", "50%"), 1.0f),
                                       dy + gradientHeight * getCoordLength (fillXml->getStringAttribute ("cy", "50%"), 1.0f));

            const float radius = getCoordLength (fillXml->getStringAttribute ("r", "50%"), gradientWidth);
            gradient.point2 = gradient.point1 + Point<float> (radius, 0.0f);

            //xxx (the fx, fy focal point isn't handled properly here..)
        }
        else
        {
            if (userSpace)
            {
                gradient.point1.setXY (dx + getCoordLength (fillXml->getStringAttribute ("x1", "0%"), gradientWidth),
                                       dy + getCoordLength (fillXml->getStringAttribute ("y1", "0%"), gradientHeight));

                gradient.point2.setXY (dx + getCoordLength (fillXml->getStringAttribute ("x2", "100%"), gradientWidth),
                                       dy + getCoordLength (fillXml->getStringAttribute ("y2", "0%"), gradientHeight));
            }
            else
            {
                gradient.point1.setXY (dx + gradientWidth * getCoordLength (fillXml->getStringAttribute ("x1", "0%"), 1.0f),
                                       dy + gradientHeight * getCoordLength (fillXml->getStringAttribute ("y1", "0%"), 1.0f));

                gradient.point2.setXY (dx + gradientWidth * getCoordLength (fillXml->getStringAttribute ("x2", "100%"), 1.0f),
                                       dy + gradientHeight * getCoordLength (fillXml->getStringAttribute ("y2", "0%"), 1.0f));
            }

            if (gradient.point1 == gradient.point2)
                return Colour (gradient.getColour (gradient.getNumColours() - 1));
        }

        FillType type (gradient);
        type.transform = parseTransform (fillXml->getStringAttribute ("gradientTransform"))
                           .followedBy (transform);
        return type;
    }

    FillType getPathFillType (const Path& path,
                              const String& fill,
                              const String& fillOpacity,
                              const String& overallOpacity,
                              const Colour& defaultColour) const
    {
        float opacity = 1.0f;

        if (overallOpacity.isNotEmpty())
            opacity = jlimit (0.0f, 1.0f, overallOpacity.getFloatValue());

        if (fillOpacity.isNotEmpty())
            opacity *= (jlimit (0.0f, 1.0f, fillOpacity.getFloatValue()));

        if (fill.startsWithIgnoreCase ("url"))
        {
            const String id (fill.fromFirstOccurrenceOf ("#", false, false)
                                 .upToLastOccurrenceOf (")", false, false).trim());

            if (const XmlElement* const fillXml = findElementForId (topLevelXml, id))
                if (fillXml->hasTagName ("linearGradient") || fillXml->hasTagName ("radialGradient"))
                    return getGradientFillType (fillXml, path, opacity);
        }

        if (fill.equalsIgnoreCase ("none"))
            return Colours::transparentBlack;

        int i = 0;
        return parseColour (fill, i, defaultColour).withMultipliedAlpha (opacity);
    }

    PathStrokeType getStrokeFor (const XmlElement* const xml) const
    {
        const String strokeWidth (getStyleAttribute (xml, "stroke-width"));
        const String cap (getStyleAttribute (xml, "stroke-linecap"));
        const String join (getStyleAttribute (xml, "stroke-linejoin"));

        //const String mitreLimit (getStyleAttribute (xml, "stroke-miterlimit"));
        //const String dashArray (getStyleAttribute (xml, "stroke-dasharray"));
        //const String dashOffset (getStyleAttribute (xml, "stroke-dashoffset"));

        PathStrokeType::JointStyle joinStyle = PathStrokeType::mitered;
        PathStrokeType::EndCapStyle capStyle = PathStrokeType::butt;

        if (join.equalsIgnoreCase ("round"))
            joinStyle = PathStrokeType::curved;
        else if (join.equalsIgnoreCase ("bevel"))
            joinStyle = PathStrokeType::beveled;

        if (cap.equalsIgnoreCase ("round"))
            capStyle = PathStrokeType::rounded;
        else if (cap.equalsIgnoreCase ("square"))
            capStyle = PathStrokeType::square;

        float ox = 0.0f, oy = 0.0f;
        float x = getCoordLength (strokeWidth, viewBoxW), y = 0.0f;
        transform.transformPoints (ox, oy, x, y);

        return PathStrokeType (strokeWidth.isNotEmpty() ? juce_hypot (x - ox, y - oy) : 1.0f,
                               joinStyle, capStyle);
    }

    //==============================================================================
    Drawable* parseText (const XmlElement& xml)
    {
        Array <float> xCoords, yCoords, dxCoords, dyCoords;

        getCoordList (xCoords, getInheritedAttribute (&xml, "x"), true, true);
        getCoordList (yCoords, getInheritedAttribute (&xml, "y"), true, false);
        getCoordList (dxCoords, getInheritedAttribute (&xml, "dx"), true, true);
        getCoordList (dyCoords, getInheritedAttribute (&xml, "dy"), true, false);


        //xxx not done text yet!


        forEachXmlChildElement (xml, e)
        {
            if (e->isTextElement())
            {
                const String text (e->getText());

                Path path;
                Drawable* s = parseShape (*e, path);
                delete s;  // xxx not finished!
            }
            else if (e->hasTagName ("tspan"))
            {
                Drawable* s = parseText (*e);
                delete s;  // xxx not finished!
            }
        }

        return nullptr;
    }

    //==============================================================================
    void addTransform (const XmlElement& xml)
    {
        transform = parseTransform (xml.getStringAttribute ("transform"))
                        .followedBy (transform);
    }

    //==============================================================================
    bool parseCoord (String::CharPointerType& s, float& value, const bool allowUnits, const bool isX) const
    {
        String number;

        if (! parseNextNumber (s, number, allowUnits))
        {
            value = 0;
            return false;
        }

        value = getCoordLength (number, isX ? viewBoxW : viewBoxH);
        return true;
    }

    bool parseCoords (String::CharPointerType& s, Point<float>& p, const bool allowUnits) const
    {
        return parseCoord (s, p.x, allowUnits, true)
            && parseCoord (s, p.y, allowUnits, false);
    }

    bool parseCoordsOrSkip (String::CharPointerType& s, Point<float>& p, const bool allowUnits) const
    {
        const bool b = parseCoords (s, p, allowUnits);
        if (! b)
            ++s;

        return b;
    }

    float getCoordLength (const String& s, const float sizeForProportions) const
    {
        float n = s.getFloatValue();
        const int len = s.length();

        if (len > 2)
        {
            const float dpi = 96.0f;

            const juce_wchar n1 = s [len - 2];
            const juce_wchar n2 = s [len - 1];

            if (n1 == 'i' && n2 == 'n')         n *= dpi;
            else if (n1 == 'm' && n2 == 'm')    n *= dpi / 25.4f;
            else if (n1 == 'c' && n2 == 'm')    n *= dpi / 2.54f;
            else if (n1 == 'p' && n2 == 'c')    n *= 15.0f;
            else if (n2 == '%')                 n *= 0.01f * sizeForProportions;
        }

        return n;
    }

    void getCoordList (Array <float>& coords, const String& list,
                       const bool allowUnits, const bool isX) const
    {
        String::CharPointerType text (list.getCharPointer());
        float value;

        while (parseCoord (text, value, allowUnits, isX))
            coords.add (value);
    }

    //==============================================================================
    void parseCSSStyle (const XmlElement& xml)
    {
        cssStyleText = xml.getAllSubText() + "\n" + cssStyleText;
    }

    String getStyleAttribute (const XmlElement* xml, const String& attributeName,
                              const String& defaultValue = String::empty) const
    {
        if (xml->hasAttribute (attributeName))
            return xml->getStringAttribute (attributeName, defaultValue);

        const String styleAtt (xml->getStringAttribute ("style"));

        if (styleAtt.isNotEmpty())
        {
            const String value (getAttributeFromStyleList (styleAtt, attributeName, String::empty));

            if (value.isNotEmpty())
                return value;
        }
        else if (xml->hasAttribute ("class"))
        {
            const String className ("." + xml->getStringAttribute ("class"));

            int index = cssStyleText.indexOfIgnoreCase (className + " ");

            if (index < 0)
                index = cssStyleText.indexOfIgnoreCase (className + "{");

            if (index >= 0)
            {
                const int openBracket = cssStyleText.indexOfChar (index, '{');

                if (openBracket > index)
                {
                    const int closeBracket = cssStyleText.indexOfChar (openBracket, '}');

                    if (closeBracket > openBracket)
                    {
                        const String value (getAttributeFromStyleList (cssStyleText.substring (openBracket + 1, closeBracket), attributeName, defaultValue));

                        if (value.isNotEmpty())
                            return value;
                    }
                }
            }
        }

        xml = const_cast <XmlElement*> (topLevelXml)->findParentElementOf (xml);

        if (xml != nullptr)
            return getStyleAttribute (xml, attributeName, defaultValue);

        return defaultValue;
    }

    String getInheritedAttribute (const XmlElement* xml, const String& attributeName) const
    {
        if (xml->hasAttribute (attributeName))
            return xml->getStringAttribute (attributeName);

        xml = const_cast <XmlElement*> (topLevelXml)->findParentElementOf (xml);

        if (xml != nullptr)
            return getInheritedAttribute  (xml, attributeName);

        return String::empty;
    }

    //==============================================================================
    static bool isIdentifierChar (const juce_wchar c)
    {
        return CharacterFunctions::isLetter (c) || c == '-';
    }

    static String getAttributeFromStyleList (const String& list, const String& attributeName, const String& defaultValue)
    {
        int i = 0;

        for (;;)
        {
            i = list.indexOf (i, attributeName);

            if (i < 0)
                break;

            if ((i == 0 || (i > 0 && ! isIdentifierChar (list [i - 1])))
                 && ! isIdentifierChar (list [i + attributeName.length()]))
            {
                i = list.indexOfChar (i, ':');

                if (i < 0)
                    break;

                int end = list.indexOfChar (i, ';');

                if (end < 0)
                    end = 0x7ffff;

                return list.substring (i + 1, end).trim();
            }

            ++i;
        }

        return defaultValue;
    }

    //==============================================================================
    static bool parseNextNumber (String::CharPointerType& s, String& value, const bool allowUnits)
    {
        while (s.isWhitespace() || *s == ',')
            ++s;

        String::CharPointerType start (s);
        int numChars = 0;

        if (s.isDigit() || *s == '.' || *s == '-')
        {
            ++numChars;
            ++s;
        }

        while (s.isDigit() || *s == '.')
        {
            ++numChars;
            ++s;
        }

        if ((*s == 'e' || *s == 'E')
             && ((s + 1).isDigit() || s[1] == '-' || s[1] == '+'))
        {
            s += 2;
            numChars += 2;

            while (s.isDigit())
            {
                ++numChars;
                ++s;
            }
        }

        if (allowUnits)
        {
            while (s.isLetter())
            {
                ++numChars;
                ++s;
            }
        }

        if (numChars == 0)
            return false;

        value = String (start, (size_t) numChars);

        while (s.isWhitespace() || *s == ',')
            ++s;

        return true;
    }

    //==============================================================================
    static Colour parseColour (const String& s, int& index, const Colour& defaultColour)
    {
        if (s [index] == '#')
        {
            uint32 hex[6] = { 0 };
            int numChars = 0;

            for (int i = 6; --i >= 0;)
            {
                const int hexValue = CharacterFunctions::getHexDigitValue (s [++index]);

                if (hexValue >= 0)
                    hex [numChars++] = (uint32) hexValue;
                else
                    break;
            }

            if (numChars <= 3)
                return Colour ((uint8) (hex [0] * 0x11),
                               (uint8) (hex [1] * 0x11),
                               (uint8) (hex [2] * 0x11));

            return Colour ((uint8) ((hex [0] << 4) + hex [1]),
                           (uint8) ((hex [2] << 4) + hex [3]),
                           (uint8) ((hex [4] << 4) + hex [5]));
        }
        else if (s [index] == 'r'
                  && s [index + 1] == 'g'
                  && s [index + 2] == 'b')
        {
            const int openBracket = s.indexOfChar (index, '(');
            const int closeBracket = s.indexOfChar (openBracket, ')');

            if (openBracket >= 3 && closeBracket > openBracket)
            {
                index = closeBracket;

                StringArray tokens;
                tokens.addTokens (s.substring (openBracket + 1, closeBracket), ",", "");
                tokens.trim();
                tokens.removeEmptyStrings();

                if (tokens[0].containsChar ('%'))
                    return Colour ((uint8) roundToInt (2.55 * tokens[0].getDoubleValue()),
                                   (uint8) roundToInt (2.55 * tokens[1].getDoubleValue()),
                                   (uint8) roundToInt (2.55 * tokens[2].getDoubleValue()));
                else
                    return Colour ((uint8) tokens[0].getIntValue(),
                                   (uint8) tokens[1].getIntValue(),
                                   (uint8) tokens[2].getIntValue());
            }
        }

        return Colours::findColourForName (s, defaultColour);
    }

    static const AffineTransform parseTransform (String t)
    {
        AffineTransform result;

        while (t.isNotEmpty())
        {
            StringArray tokens;
            tokens.addTokens (t.fromFirstOccurrenceOf ("(", false, false)
                               .upToFirstOccurrenceOf (")", false, false),
                              ", ", String::empty);

            tokens.removeEmptyStrings (true);

            float numbers [6];

            for (int i = 0; i < 6; ++i)
                numbers[i] = tokens[i].getFloatValue();

            AffineTransform trans;

            if (t.startsWithIgnoreCase ("matrix"))
            {
                trans = AffineTransform (numbers[0], numbers[2], numbers[4],
                                         numbers[1], numbers[3], numbers[5]);
            }
            else if (t.startsWithIgnoreCase ("translate"))
            {
                jassert (tokens.size() == 2);
                trans = AffineTransform::translation (numbers[0], numbers[1]);
            }
            else if (t.startsWithIgnoreCase ("scale"))
            {
                if (tokens.size() == 1)
                    trans = AffineTransform::scale (numbers[0]);
                else
                    trans = AffineTransform::scale (numbers[0], numbers[1]);
            }
            else if (t.startsWithIgnoreCase ("rotate"))
            {
                if (tokens.size() != 3)
                    trans = AffineTransform::rotation (numbers[0] / (180.0f / float_Pi));
                else
                    trans = AffineTransform::rotation (numbers[0] / (180.0f / float_Pi),
                                                       numbers[1], numbers[2]);
            }
            else if (t.startsWithIgnoreCase ("skewX"))
            {
                trans = AffineTransform (1.0f, std::tan (numbers[0] * (float_Pi / 180.0f)), 0.0f,
                                         0.0f, 1.0f, 0.0f);
            }
            else if (t.startsWithIgnoreCase ("skewY"))
            {
                trans = AffineTransform (1.0f, 0.0f, 0.0f,
                                         std::tan (numbers[0] * (float_Pi / 180.0f)), 1.0f, 0.0f);
            }

            result = trans.followedBy (result);
            t = t.fromFirstOccurrenceOf (")", false, false).trimStart();
        }

        return result;
    }

    static void endpointToCentreParameters (const double x1, const double y1,
                                            const double x2, const double y2,
                                            const double angle,
                                            const bool largeArc, const bool sweep,
                                            double& rx, double& ry,
                                            double& centreX, double& centreY,
                                            double& startAngle, double& deltaAngle)
    {
        const double midX = (x1 - x2) * 0.5;
        const double midY = (y1 - y2) * 0.5;

        const double cosAngle = cos (angle);
        const double sinAngle = sin (angle);
        const double xp = cosAngle * midX + sinAngle * midY;
        const double yp = cosAngle * midY - sinAngle * midX;
        const double xp2 = xp * xp;
        const double yp2 = yp * yp;

        double rx2 = rx * rx;
        double ry2 = ry * ry;

        const double s = (xp2 / rx2) + (yp2 / ry2);
        double c;

        if (s <= 1.0)
        {
            c = std::sqrt (jmax (0.0, ((rx2 * ry2) - (rx2 * yp2) - (ry2 * xp2))
                                         / (( rx2 * yp2) + (ry2 * xp2))));

            if (largeArc == sweep)
                c = -c;
        }
        else
        {
            const double s2 = std::sqrt (s);
            rx *= s2;
            ry *= s2;
            rx2 = rx * rx;
            ry2 = ry * ry;
            c = 0;
        }

        const double cpx = ((rx * yp) / ry) * c;
        const double cpy = ((-ry * xp) / rx) * c;

        centreX = ((x1 + x2) * 0.5) + (cosAngle * cpx) - (sinAngle * cpy);
        centreY = ((y1 + y2) * 0.5) + (sinAngle * cpx) + (cosAngle * cpy);

        const double ux = (xp - cpx) / rx;
        const double uy = (yp - cpy) / ry;
        const double vx = (-xp - cpx) / rx;
        const double vy = (-yp - cpy) / ry;

        const double length = juce_hypot (ux, uy);

        startAngle = acos (jlimit (-1.0, 1.0, ux / length));

        if (uy < 0)
            startAngle = -startAngle;

        startAngle += double_Pi * 0.5;

        deltaAngle = acos (jlimit (-1.0, 1.0, ((ux * vx) + (uy * vy))
                                                / (length * juce_hypot (vx, vy))));

        if ((ux * vy) - (uy * vx) < 0)
            deltaAngle = -deltaAngle;

        if (sweep)
        {
            if (deltaAngle < 0)
                deltaAngle += double_Pi * 2.0;
        }
        else
        {
            if (deltaAngle > 0)
                deltaAngle -= double_Pi * 2.0;
        }

        deltaAngle = fmod (deltaAngle, double_Pi * 2.0);
    }

    static const XmlElement* findElementForId (const XmlElement* const parent, const String& id)
    {
        forEachXmlChildElement (*parent, e)
        {
            if (e->compareAttribute ("id", id))
                return e;

            if (const XmlElement* const found = findElementForId (e, id))
                return found;
        }

        return nullptr;
    }

    SVGState& operator= (const SVGState&);
};


//==============================================================================
Drawable* Drawable::createFromSVG (const XmlElement& svgDocument)
{
    SVGState state (&svgDocument);
    return state.parseSVGElement (svgDocument);
}
