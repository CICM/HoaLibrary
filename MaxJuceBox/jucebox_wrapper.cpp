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

MaxOpenGlComponent::~MaxOpenGlComponent()
{
    m_context->detach();
    delete m_context;
}

void jucebox_initclass(t_class* c, method paint, long flags)
{
    jbox_initclass(c, flags);
	class_addmethod(c, (method)jucebox_paint, "paint", A_CANT, 0);
    class_addmethod(c, (method)paint, "jucebox_paint", A_CANT, 0);
}

void jucebox_new(t_jucebox* x)
{
    x->j_component = new MaxOpenGlComponent();
	x->j_component->setOpaque(false);
	x->j_component->setVisible(true);
    x->j_component->addToDesktop(0);
    x->j_component->setActive();
}

void jucebox_free(t_jucebox* x)
{
    jbox_free((t_jbox *)x);
	x->j_component->removeFromDesktop();
    delete x->j_component;
}

void jucebox_paint(t_jucebox* x, t_object *patcherview)
{
    t_rect rect, srcRect, destRect;
    int width, height, imgStride;
    unsigned char* data;
    
    //x->j_component->setVisible(true);
    if(x->j_component->isOnDesktop())
    {
        x->j_component->setActive();
        if(x->j_component->isContextOk())
        {
            jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
            t_jgraphics *g = (t_jgraphics *)patcherview_get_jgraphics(patcherview);
            if(g)
            {
                juce::Image openGLSnap = x->j_component->makeScreenshot((t_object *)x, rect.width, rect.height);
                
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
    //x->j_component->setVisible(false);
}



