/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_JUCEBOX_WRAPPER
#define DEF_JUCEBOX_WRAPPER

extern "C"
{
#include <ext.h>
#include <ext_obex.h>
#include <jpatcher_api.h>
#include <jgraphics.h>
#include <z_dsp.h>
}

#include "../JuceLibraryCode/JuceHeader.h"
#include <OpenGL/gl.h>

extern void initialiseMac();
extern void hideWindow (void* comp);

class MaxOpenGlComponent : public juce::Component, public OpenGLRenderer
{
private:
    OpenGLContext*      m_context;
	float m_scale;
public:
	MaxOpenGlComponent();
	Image makeScreenshot(t_object* x, double width, double height);
	
    void setActive(){ m_context->makeActive();}
    inline char isActive() const { return (char)m_context->isActive(); }
    inline char isContextOk() const { return (char)(m_context == m_context->getCurrentContext()); }
	
	void newOpenGLContextCreated(){};
    void renderOpenGL(){m_scale = m_context->getRenderingScale();};
	void openGLContextClosing(){};
    ~MaxOpenGlComponent();
};

typedef struct _jucebox
{
	t_pxjbox                j_box;
	MaxOpenGlComponent*     j_component;
} t_jucebox;

void jucebox_initclass(t_class* c, method paint, long flags);
void jucebox_new(t_jucebox* x);
void jucebox_free(t_jucebox* x);
void jucebox_paint(t_jucebox* x, t_object *patcherview);

#endif