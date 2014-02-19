/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jucebox_wrapper.h"

MaxOpenGlComponent::MaxOpenGlComponent()
{
    setBounds(-10, -10, 1, 1);
    m_context = new OpenGLContext();
    m_context->setComponentPaintingEnabled(false);

    m_context->attachTo(*this);
    m_context->setContinuousRepainting(false);
    setInterceptsMouseClicks(false, false);
}

Image MaxOpenGlComponent::makeScreenshot(t_object* x, double width, double height)
{
    Image img;
    float scale = m_context->getRenderingScale();

    if(!m_context->isActive())
        return img;
    setBounds(-width, -height, width, height);
    img = Image(OpenGLImageType().create(Image::ARGB, roundToInt(width * scale), roundToInt(height * scale), true));
    OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(img);
   
    buffer->makeCurrentAndClear();
    
    (object_getmethod(x, gensym("jucebox_paint")))(x, width * scale, height * scale);
    buffer->releaseAsRenderingTarget();
    return img;
}

void jucebox_initclass(t_class* c, method paint)
{
    assert(paint != NULL);
	class_addmethod(c, (method)jucebox_paint, "paint", A_CANT, 0);
    class_addmethod(c, (method)paint, "jucebox_paint", A_CANT, 0);
}

void jucebox_new(t_jucebox* x)
{
    x->z_component = new MaxOpenGlComponent();
	x->z_component->setOpaque(false);
	x->z_component->setVisible(true);
    x->z_component->addToDesktop(0);
    x->z_component->setActive();
}

void jucebox_free(t_jucebox* x)
{
	x->z_component->removeFromDesktop();
    delete x->z_component;
}

void jucebox_paint(t_jucebox* x, t_object *patcherview)
{
    t_rect rect, srcRect, destRect;
    int width, height, imgStride;
    unsigned char* data;
    
    //x->z_component->setVisible(true);
    if(x->z_component->isOnDesktop())
    {
        x->z_component->setActive();
        if(x->z_component->isContextOk())
        {
            jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
            t_jgraphics *g = (t_jgraphics *)patcherview_get_jgraphics(patcherview);
            if(g)
            {
                juce::Image openGLSnap = x->z_component->makeScreenshot((t_object *)x, rect.width, rect.height);
                
                juce::Image::BitmapData* snapBitmap = new juce::Image::BitmapData(openGLSnap, juce::Image::BitmapData::ReadWriteMode::readOnly);
                data = snapBitmap->data;
                width = openGLSnap.getWidth();
                height = openGLSnap.getHeight();
                imgStride = snapBitmap->lineStride;
                
                srcRect     = {0, 0, (double)openGLSnap.getWidth(), (double)openGLSnap.getHeight()};
                destRect    = {0, 0, rect.width, rect.height};
                
                t_jsurface* surface = jgraphics_image_surface_create_for_data(data, JGRAPHICS_FORMAT_ARGB32, width, height, imgStride, NULL, NULL);
                jgraphics_image_surface_draw(g, surface, srcRect, destRect);
                jgraphics_surface_destroy(surface);
            }
        }
        
    }
    //x->z_component->setVisible(false);
}



