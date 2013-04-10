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

class ImageCache::Pimpl     : private Timer,
                              private DeletedAtShutdown
{
public:
    Pimpl()
        : cacheTimeout (5000)
    {
    }

    ~Pimpl()
    {
        clearSingletonInstance();
    }

    Image getFromHashCode (const int64 hashCode)
    {
        const ScopedLock sl (lock);

        for (int i = images.size(); --i >= 0;)
        {
            Item* const item = images.getUnchecked(i);

            if (item->hashCode == hashCode)
                return item->image;
        }

        return Image::null;
    }

    void addImageToCache (const Image& image, const int64 hashCode)
    {
        if (image.isValid())
        {
            if (! isTimerRunning())
                startTimer (2000);

            Item* const item = new Item();
            item->hashCode = hashCode;
            item->image = image;
            item->lastUseTime = Time::getApproximateMillisecondCounter();

            const ScopedLock sl (lock);
            images.add (item);
        }
    }

    void timerCallback()
    {
        const uint32 now = Time::getApproximateMillisecondCounter();

        const ScopedLock sl (lock);

        for (int i = images.size(); --i >= 0;)
        {
            Item* const item = images.getUnchecked(i);

            if (item->image.getReferenceCount() <= 1)
            {
                if (now > item->lastUseTime + cacheTimeout || now < item->lastUseTime - 1000)
                    images.remove (i);
            }
            else
            {
                item->lastUseTime = now; // multiply-referenced, so this image is still in use.
            }
        }

        if (images.size() == 0)
            stopTimer();
    }

    struct Item
    {
        Image image;
        int64 hashCode;
        uint32 lastUseTime;
    };

    unsigned int cacheTimeout;

    juce_DeclareSingleton_SingleThreaded_Minimal (ImageCache::Pimpl);

private:
    OwnedArray<Item> images;
    CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE (Pimpl)
};

juce_ImplementSingleton_SingleThreaded (ImageCache::Pimpl);


//==============================================================================
Image ImageCache::getFromHashCode (const int64 hashCode)
{
    if (Pimpl::getInstanceWithoutCreating() != nullptr)
        return Pimpl::getInstanceWithoutCreating()->getFromHashCode (hashCode);

    return Image::null;
}

void ImageCache::addImageToCache (const Image& image, const int64 hashCode)
{
    Pimpl::getInstance()->addImageToCache (image, hashCode);
}

Image ImageCache::getFromFile (const File& file)
{
    const int64 hashCode = file.hashCode64();
    Image image (getFromHashCode (hashCode));

    if (image.isNull())
    {
        image = ImageFileFormat::loadFrom (file);
        addImageToCache (image, hashCode);
    }

    return image;
}

Image ImageCache::getFromMemory (const void* imageData, const int dataSize)
{
    const int64 hashCode = (int64) (pointer_sized_int) imageData;
    Image image (getFromHashCode (hashCode));

    if (image.isNull())
    {
        image = ImageFileFormat::loadFrom (imageData, (size_t) dataSize);
        addImageToCache (image, hashCode);
    }

    return image;
}

void ImageCache::setCacheTimeout (const int millisecs)
{
    jassert (millisecs >= 0);
    Pimpl::getInstance()->cacheTimeout = (unsigned int) millisecs;
}
