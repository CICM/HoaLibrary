/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_JUCEBOX_STRUCT
#define DEF_JUCEBOX_STRUCT

#include "../JuceLibraryCode/JuceHeader.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"
}

#include "../JuceLibraryCode/JuceHeader.h"

class MaxOpenGlComponent : public juce::Component
{
	
private:
    OpenGLContext*      m_context;
public:
	MaxOpenGlComponent()
	{
		setSize(200, 200);
        m_context = new OpenGLContext();
		m_context->setComponentPaintingEnabled(false);
        m_context->setRenderer((OpenGLRenderer* )this);
        m_context->attachTo(*this);
        m_context->setContinuousRepainting(false);
		setInterceptsMouseClicks(false, false);
	}
    
	~MaxOpenGlComponent(){ m_context->detach(); }
    void setActive(){ m_context->makeActive();}
    inline char isActive() const { return (char)m_context->isActive(); }
    inline char isContextOk() const { return (char)(m_context == m_context->getCurrentContext()); }
    
	Image makeScreenshot(t_object* x)
	{
        Image img;
        if(!m_context->isActive())
            return img;
        
        img = Image(OpenGLImageType().create (Image::ARGB, roundToInt (1 * getWidth()), roundToInt (1 * getHeight()), true));
        OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(img);
		
		buffer->makeCurrentAndClear();
        object_method(x, gensym("jucebox_paint"));
		buffer->releaseAsRenderingTarget();
        return img;
	}
};

typedef struct _jucebox
{
	t_pxjbox                z_box;
	MaxOpenGlComponent*     z_component;
} t_jucebox;

void jucebox_classinit(t_class* c, method paint);
void jucebox_new(t_jucebox* x);
void jucebox_free(t_jucebox* x);
void jucebox_paint(t_jucebox* x, t_object *patcherview);

#endif