/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jucebox_wrapper.h"

MaxOpenGlComponent::MaxOpenGlComponent()
{
    setBounds(-1000, -1000, 1, 1);
    m_context = new OpenGLContext();
    m_context->setComponentPaintingEnabled(false);

	m_context->setRenderer(this); // we need this to set m_scale
    m_context->attachTo(*this);
    m_context->setContinuousRepainting(false);
    setInterceptsMouseClicks(false, false);
}

Image MaxOpenGlComponent::makeScreenshot(t_object* x, double width, double height)
{
    Image img;

    if(!m_context->isActive())
        return img;
	
    setBounds(-width, -height, width, height);
    img = Image(OpenGLImageType().create(Image::ARGB, roundToInt(width * m_scale), roundToInt(height * m_scale), true));
    OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(img);
   
    buffer->makeCurrentAndClear();

    (object_getmethod(x, gensym("jucebox_paint")))(x, width * m_scale, height * m_scale);
	
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
	
	if(gensym("hoa_scope_newwindow")->s_thing == NULL)
	{
		MaxOpenGlComponent *wm = new MaxOpenGlComponent();
		wm->setOpaque(true);
		wm->setVisible(true);
		wm->setActive();
		wm->addToDesktop(0, 0);
		gensym("hoa_scope_newwindow")->s_thing = (t_object *)wm;
	}
}

void jucebox_new(t_jucebox* x)
{
    x->j_component = (MaxOpenGlComponent *)gensym("hoa_scope_newwindow")->s_thing;
}

void jucebox_free(t_jucebox* x)
{
    jbox_free((t_jbox *)x);
	//x->j_component->removeFromDesktop();
    //delete x->j_component;
}

int test = 0;

void jucebox_paint(t_jucebox* x, t_object *patcherview)
{
    t_rect rect, srcRect, destRect;
    int width, height, imgStride;
    unsigned char* data;
    
	//x->j_component->addToDesktop(ComponentPeer::windowIsTemporary, 0);
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
               
                juce::Image::BitmapData* snapBitmap = new juce::Image::BitmapData(openGLSnap, juce::Image::BitmapData::readOnly);
                data = snapBitmap->data;
                width = openGLSnap.getWidth();
                height = openGLSnap.getHeight();
                imgStride = snapBitmap->lineStride;
                
                srcRect.x = 0;
                destRect.x = 0;
                srcRect.y = 0;
                destRect.y = 0;
                srcRect.width = openGLSnap.getWidth();
                srcRect.height = openGLSnap.getHeight();
                destRect.width = rect.width;
                destRect.height = rect.height;
                
                t_jsurface* surface = jgraphics_image_surface_create_for_data(data, JGRAPHICS_FORMAT_ARGB32, width, height, imgStride, NULL, NULL);
                jgraphics_image_surface_draw(g, surface, srcRect, destRect);
                jgraphics_surface_destroy(surface);
            }
        }
    }
	//x->j_component->removeFromDesktop();
}



