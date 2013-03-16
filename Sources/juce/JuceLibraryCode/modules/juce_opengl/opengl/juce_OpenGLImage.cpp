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

class OpenGLFrameBufferImage   : public ImagePixelData
{
public:
    OpenGLFrameBufferImage (OpenGLContext& context_, int width, int height)
        : ImagePixelData (Image::ARGB, width, height),
          context (context_),
          pixelStride (4),
          lineStride (width * pixelStride)
    {
    }

    bool initialise()
    {
        return frameBuffer.initialise (context, width, height);
    }

    LowLevelGraphicsContext* createLowLevelContext()
    {
        return createOpenGLGraphicsContext (context, frameBuffer);
    }

    ImageType* createType() const     { return new OpenGLImageType(); }

    ImagePixelData* clone()
    {
        OpenGLFrameBufferImage* im = new OpenGLFrameBufferImage (context, width, height);
        im->incReferenceCount();

        {
            Image newImage (im);
            Graphics g (newImage);
            g.drawImageAt (Image (this), 0, 0, false);
        }

        im->resetReferenceCount();
        return im;
    }

    void initialiseBitmapData (Image::BitmapData& bitmapData, int x, int y, Image::BitmapData::ReadWriteMode mode)
    {
        bitmapData.pixelFormat = pixelFormat;
        bitmapData.lineStride  = lineStride;
        bitmapData.pixelStride = pixelStride;

        switch (mode)
        {
            case Image::BitmapData::writeOnly:  DataReleaser<Dummy,  Writer>::initialise (frameBuffer, bitmapData, x, y); break;
            case Image::BitmapData::readOnly:   DataReleaser<Reader, Dummy> ::initialise (frameBuffer, bitmapData, x, y); break;
            case Image::BitmapData::readWrite:  DataReleaser<Reader, Writer>::initialise (frameBuffer, bitmapData, x, y); break;
            default:                            jassertfalse; break;
        }
    }

    OpenGLContext& context;
    OpenGLFrameBuffer frameBuffer;

private:
    int pixelStride, lineStride;

    struct Dummy
    {
        Dummy (OpenGLFrameBuffer&, int, int, int, int) noexcept {}
        static void read (OpenGLFrameBuffer&, Image::BitmapData& , int, int) noexcept {}
        static void write (const PixelARGB*) noexcept {}
    };

    struct Reader
    {
        static void read (OpenGLFrameBuffer& frameBuffer, Image::BitmapData& bitmapData, int x, int y)
        {
            frameBuffer.readPixels ((PixelARGB*) bitmapData.data,
                                    Rectangle<int> (x, frameBuffer.getHeight() - (y + bitmapData.height), bitmapData.width, bitmapData.height));

            verticalRowFlip ((PixelARGB*) bitmapData.data, bitmapData.width, bitmapData.height);
        }

        static void verticalRowFlip (PixelARGB* const data, const int w, const int h)
        {
            HeapBlock<PixelARGB> tempRow (w);
            const int rowSize = sizeof (PixelARGB) * w;

            for (int y = 0; y < h / 2; ++y)
            {
                PixelARGB* const row1 = data + y * w;
                PixelARGB* const row2 = data + (h - 1 - y) * w;
                memcpy (tempRow, row1, rowSize);
                memcpy (row1, row2, rowSize);
                memcpy (row2, tempRow, rowSize);
            }
        }
    };

    struct Writer
    {
        Writer (OpenGLFrameBuffer& frameBuffer_, int x, int y, int w, int h) noexcept
            : frameBuffer (frameBuffer_), area (x, y, w, h)
        {}

        void write (const PixelARGB* const data) const noexcept
        {
            HeapBlock<PixelARGB> invertedCopy (area.getWidth() * area.getHeight());
            const int rowSize = sizeof (PixelARGB) * area.getWidth();

            for (int y = 0; y < area.getHeight(); ++y)
                memcpy (invertedCopy + area.getWidth() * y,
                        data + area.getWidth() * (area.getHeight() - 1 - y), rowSize);

            frameBuffer.writePixels (invertedCopy, area);
        }

        OpenGLFrameBuffer& frameBuffer;
        const Rectangle<int> area;

        JUCE_DECLARE_NON_COPYABLE (Writer)
    };

    template <class ReaderType, class WriterType>
    struct DataReleaser  : public Image::BitmapData::BitmapDataReleaser
    {
        DataReleaser (OpenGLFrameBuffer& fb, int x, int y, int w, int h)
            : data (w * h),
              writer (fb, x, y, w, h)
        {}

        ~DataReleaser()
        {
            writer.write (data);
        }

        static void initialise (OpenGLFrameBuffer& frameBuffer, Image::BitmapData& bitmapData, int x, int y)
        {
            DataReleaser* r = new DataReleaser (frameBuffer, x, y, bitmapData.width, bitmapData.height);
            bitmapData.dataReleaser = r;
            bitmapData.data = (uint8*) (r->data + (x + y * bitmapData.width));

            ReaderType::read (frameBuffer, bitmapData, x, y);
        }

        HeapBlock<PixelARGB> data;
        WriterType writer;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLFrameBufferImage)
};


//==============================================================================
OpenGLImageType::OpenGLImageType() {}
OpenGLImageType::~OpenGLImageType() {}

int OpenGLImageType::getTypeID() const
{
    return 3;
}

ImagePixelData::Ptr OpenGLImageType::create (Image::PixelFormat, int width, int height, bool /*shouldClearImage*/) const
{
    OpenGLContext* currentContext = OpenGLContext::getCurrentContext();
    jassert (currentContext != nullptr); // an OpenGL image can only be created when a valid context is active!

    ScopedPointer<OpenGLFrameBufferImage> im (new OpenGLFrameBufferImage (*currentContext, width, height));

    if (! im->initialise())
        return nullptr;

    im->frameBuffer.clear (Colours::transparentBlack);
    return im.release();
}

OpenGLFrameBuffer* OpenGLImageType::getFrameBufferFrom (const Image& image)
{
    OpenGLFrameBufferImage* const glImage = dynamic_cast<OpenGLFrameBufferImage*> (image.getPixelData());

    return glImage != nullptr ? &(glImage->frameBuffer) : nullptr;
}
