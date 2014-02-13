/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jucebox_struct.h"

void jucebox_class_new(t_class* c, method paint, method notify)
{
	class_addmethod(c, (method)jucebox_paint,				"paint", A_CANT, 0);
	class_addmethod(c, (method)jucebox_notify,				"notify", A_CANT, 0);
	class_addmethod(c, (method)jucebox_patcherview_vis,		"patcherview_vis",		A_CANT, 0);
    class_addmethod(c, (method)jucebox_patcherview_invis,	"patcherview_invis",	A_CANT, 0);
	
	if (paint)
	{
		class_addmethod(c, paint, "jucebox_paint", A_CANT, 0);
	}
	if (notify)
	{
		class_addmethod(c, notify, "jucebox_notify", A_CANT, 0);
	}
}

void jucebox_new(t_jucebox* x)
{
	jucebox_addjucecomponents(x);
}

void jucebox_free(t_jucebox* x)
{
	x->juceWindowComp->removeFromDesktop();
	delete x->juceWindowComp;
}

EditorComponent* getOGLComponent(t_jucebox *x)
{
	return dynamic_cast <EditorComponent*> (x->juceEditorComp);
}

void jucebox_paint(t_jucebox* x, t_object *patcherview)
{
	post("jucebox Paint method called");
	
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(patcherview);
	jbox_get_rect_for_view((t_object *)x, patcherview, &x->box_rect);
    
    int locked = ((patcherview_get_locked(x->mPatcherview)) != 0);
	
    if( locked )
    {
        if(!x->juceWindowComp) jucebox_addjucecomponents(x);
        x->juceWindowComp->calcAndSetBounds();
	}
	
	juce::Image openGLSnap = getOGLComponent(x)->makeScreenshot();
	juce::Image::BitmapData* snapBitmap = new juce::Image::BitmapData(openGLSnap, juce::Image::BitmapData::ReadWriteMode::readOnly);
	
	unsigned char* data = snapBitmap->data;
	int width, height, imgStride;
	width = openGLSnap.getWidth();
	height = openGLSnap.getHeight();
	imgStride = snapBitmap->lineStride;
	t_rect srcRect = {0,0, (double)openGLSnap.getWidth(), (double)openGLSnap.getHeight()};
	t_rect destRect = {0,0, x->box_rect.width, x->box_rect.height};
	
	t_jsurface* surface = jgraphics_image_surface_create_for_data (data, JGRAPHICS_FORMAT_ARGB32, width, height, imgStride, NULL, NULL);
	jgraphics_image_surface_draw(g, surface, srcRect, destRect);
	jgraphics_surface_destroy (surface);
}

void jucebox_addjucecomponents(t_jucebox* x)
{
	x->juceEditorComp = (juce::Component*) new EditorComponent(x);
	x->juceEditorComp->setBounds(0, 0, x->box_rect.width, x->box_rect.height);
	
	x->juceEditorComp->setOpaque (true);
	x->juceEditorComp->setVisible (true);
	
	x->juceWindowComp = new EditorComponentHolder(x->juceEditorComp, x);
	x->juceWindowComp->calcAndSetBounds();
}

t_max_err jucebox_notify(t_jucebox *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{
	object_method((t_object*)x, gensym("jucebox_notify"), s, m, sender, data);
	return MAX_ERR_NONE;
}

void jucebox_patcherview_vis(t_jucebox* x, t_object *patcherview)
{
    x->mPatcherview = patcherview;
    object_attach_byptr_register(x, x->mPatcherview, CLASS_NOBOX);
	
    if (!x->isInitialised)
    {
		x->juceWindowComp->addToDesktop(0);
        x->isInitialised = 1;
    }
}

void jucebox_patcherview_invis(t_jucebox* x, t_object *patcherview)
{
    object_detach_byptr(x, x->mPatcherview);
    x->mPatcherview = NULL;
}