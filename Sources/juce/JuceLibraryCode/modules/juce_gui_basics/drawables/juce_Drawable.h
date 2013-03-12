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

#ifndef __JUCE_DRAWABLE_JUCEHEADER__
#define __JUCE_DRAWABLE_JUCEHEADER__

#include "../components/juce_Component.h"
#include "../positioning/juce_RelativeCoordinate.h"
#include "../positioning/juce_RelativeCoordinatePositioner.h"
#include "../layout/juce_ComponentBuilder.h"
class DrawableComposite;


//==============================================================================
/**
    The base class for objects which can draw themselves, e.g. polygons, images, etc.

    @see DrawableComposite, DrawableImage, DrawablePath, DrawableText
*/
class JUCE_API  Drawable  : public Component
{
protected:
    //==============================================================================
    /** The base class can't be instantiated directly.

        @see DrawableComposite, DrawableImage, DrawablePath, DrawableText
    */
    Drawable();

public:
    /** Destructor. */
    virtual ~Drawable();

    //==============================================================================
    /** Creates a deep copy of this Drawable object.

        Use this to create a new copy of this and any sub-objects in the tree.
    */
    virtual Drawable* createCopy() const = 0;

    //==============================================================================
    /** Renders this Drawable object.

        Note that the preferred way to render a drawable in future is by using it
        as a component and adding it to a parent, so you might want to consider that
        before using this method.

        @see drawWithin
    */
    void draw (Graphics& g, float opacity,
               const AffineTransform& transform = AffineTransform::identity) const;

    /** Renders the Drawable at a given offset within the Graphics context.

        The co-ordinates passed-in are used to translate the object relative to its own
        origin before drawing it - this is basically a quick way of saying:

        @code
        draw (g, AffineTransform::translation (x, y)).
        @endcode

        Note that the preferred way to render a drawable in future is by using it
        as a component and adding it to a parent, so you might want to consider that
        before using this method.
    */
    void drawAt (Graphics& g, float x, float y, float opacity) const;

    /** Renders the Drawable within a rectangle, scaling it to fit neatly inside without
        changing its aspect-ratio.

        The object can placed arbitrarily within the rectangle based on a Justification type,
        and can either be made as big as possible, or just reduced to fit.

        Note that the preferred way to render a drawable in future is by using it
        as a component and adding it to a parent, so you might want to consider that
        before using this method.

        @param g                        the graphics context to render onto
        @param destArea                 the target rectangle to fit the drawable into
        @param placement                defines the alignment and rescaling to use to fit
                                        this object within the target rectangle.
        @param opacity                  the opacity to use, in the range 0 to 1.0
    */
    void drawWithin (Graphics& g,
                     const Rectangle<float>& destArea,
                     const RectanglePlacement& placement,
                     float opacity) const;


    //==============================================================================
    /** Resets any transformations on this drawable, and positions its origin within
        its parent component.
    */
    void setOriginWithOriginalSize (const Point<float>& originWithinParent);

    /** Sets a transform for this drawable that will position it within the specified
        area of its parent component.
    */
    void setTransformToFit (const Rectangle<float>& areaInParent, const RectanglePlacement& placement);

    /** Returns the DrawableComposite that contains this object, if there is one. */
    DrawableComposite* getParent() const;

    //==============================================================================
    /** Tries to turn some kind of image file into a drawable.

        The data could be an image that the ImageFileFormat class understands, or it
        could be SVG.
    */
    static Drawable* createFromImageData (const void* data, size_t numBytes);

    /** Tries to turn a stream containing some kind of image data into a drawable.

        The data could be an image that the ImageFileFormat class understands, or it
        could be SVG.
    */
    static Drawable* createFromImageDataStream (InputStream& dataSource);

    /** Tries to turn a file containing some kind of image data into a drawable.

        The data could be an image that the ImageFileFormat class understands, or it
        could be SVG.
    */
    static Drawable* createFromImageFile (const File& file);

    /** Attempts to parse an SVG (Scalable Vector Graphics) document, and to turn this
        into a Drawable tree.

        The object returned must be deleted by the caller. If something goes wrong
        while parsing, it may return 0.

        SVG is a pretty large and complex spec, and this doesn't aim to be a full
        implementation, but it can return the basic vector objects.
    */
    static Drawable* createFromSVG (const XmlElement& svgDocument);

    //==============================================================================
    /** Tries to create a Drawable from a previously-saved ValueTree.
        The ValueTree must have been created by the createValueTree() method.
        If there are any images used within the drawable, you'll need to provide a valid
        ImageProvider object that can be used to retrieve these images from whatever type
        of identifier is used to represent them.
        Internally, this uses a ComponentBuilder, and registerDrawableTypeHandlers().
    */
    static Drawable* createFromValueTree (const ValueTree& tree, ComponentBuilder::ImageProvider* imageProvider);

    /** Creates a ValueTree to represent this Drawable.
        The ValueTree that is returned can be turned back into a Drawable with createFromValueTree().
        If there are any images used in this drawable, you'll need to provide a valid ImageProvider
        object that can be used to create storable representations of them.
    */
    virtual ValueTree createValueTree (ComponentBuilder::ImageProvider* imageProvider) const = 0;

    /** Returns the area that this drawble covers.
        The result is expressed in this drawable's own coordinate space, and does not take
        into account any transforms that may be applied to the component.
    */
    virtual Rectangle<float> getDrawableBounds() const = 0;

    //==============================================================================
    /** Internal class used to manage ValueTrees that represent Drawables. */
    class ValueTreeWrapperBase
    {
    public:
        ValueTreeWrapperBase (const ValueTree& state);

        ValueTree& getState() noexcept          { return state; }

        String getID() const;
        void setID (const String& newID);

        ValueTree state;
    };

    //==============================================================================
    /** Registers a set of ComponentBuilder::TypeHandler objects that can be used to
        load all the different Drawable types from a saved state.
        @see ComponentBuilder::registerTypeHandler()
    */
    static void registerDrawableTypeHandlers (ComponentBuilder& componentBuilder);

protected:
    //==============================================================================
    friend class DrawableComposite;
    friend class DrawableShape;

    /** @internal */
    void transformContextToCorrectOrigin (Graphics&);
    /** @internal */
    void parentHierarchyChanged();
    /** @internal */
    void setBoundsToEnclose (const Rectangle<float>&);

    Point<int> originRelativeToComponent;

  #ifndef DOXYGEN
    /** Internal utility class used by Drawables. */
    template <class DrawableType>
    class Positioner  : public RelativeCoordinatePositionerBase
    {
    public:
        Positioner (DrawableType& c)
            : RelativeCoordinatePositionerBase (c),
              owner (c)
        {}

        bool registerCoordinates()      { return owner.registerCoordinates (*this); }
        void applyToComponentBounds()
        {
            ComponentScope scope (getComponent());
            owner.recalculateCoordinates (&scope);
        }

        void applyNewBounds (const Rectangle<int>&)
        {
            jassertfalse; // drawables can't be resized directly!
        }

    private:
        DrawableType& owner;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Positioner)
    };

    Drawable (const Drawable&);
  #endif

private:
    void nonConstDraw (Graphics& g, float opacity, const AffineTransform& transform);

    Drawable& operator= (const Drawable&);
    JUCE_LEAK_DETECTOR (Drawable)
};


#endif   // __JUCE_DRAWABLE_JUCEHEADER__
