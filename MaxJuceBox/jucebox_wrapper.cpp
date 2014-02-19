/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jucebox_wrapper.h"

void jucebox_classinit(t_class* c, method paint)
{
	class_addmethod(c, (method)jucebox_paint, "paint", A_CANT, 0);

	if(paint)
		class_addmethod(c, paint, "jucebox_paint", A_CANT, 0);
}

void jucebox_new(t_jucebox* x)
{
    t_rect rect;
	jbox_get_patching_rect((t_object *)x, &rect);
    x->z_component = new MaxOpenGlComponent();
	x->z_component->setBounds(0, 0, rect.width, rect.height);
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
    
    if(x->z_component->isOnDesktop())
    {
        x->z_component->setActive();
        if(x->z_component->isContextOk())
        {
            jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
            t_jgraphics *g = (t_jgraphics *)patcherview_get_jgraphics(patcherview);
            if(g)
            {
                x->z_component->setBounds(-rect.width - 10, -rect.height - 10, rect.width, rect.height);
                juce::Image openGLSnap = x->z_component->makeScreenshot((t_object *)x);
                
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
}



