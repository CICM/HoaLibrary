/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_MAXBOXCOMPONENT
#define DEF_MAXBOXCOMPONENT

#include "../JuceLibraryCode/JuceHeader.h"

class EditorComponent : public juce::Component,
private juce::OpenGLRenderer
{
public:
	EditorComponent(t_jucebox* x) : jucebox(x)
	{
		setSize(200, 200);
		openGLContext.setComponentPaintingEnabled(false);
        openGLContext.setRenderer (this);
        openGLContext.attachTo (*this);
        openGLContext.setContinuousRepainting (false);
		setInterceptsMouseClicks(false, false);
	}
    
	~EditorComponent()
	{
        openGLContext.detach();
		deleteAllChildren();
	}
    void newOpenGLContextCreated() {}
	
    void openGLContextClosing() {}
	
	// return the openGL drawings as an image.
	Image makeScreenshot()
	{
		const float desktopScale = (float) openGLContext.getRenderingScale();
		Image snapshotImage = Image (OpenGLImageType().create (Image::ARGB, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()), true));
		OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(snapshotImage);
		
		//buffer->clear( findColour(EditorComponent::backgroundColourId) );
		buffer->makeCurrentRenderingTarget();
		
		// openGL draw method to implement
		//customRender();
		object_method((t_object*)jucebox, gensym("jucebox_paint"));
		
		buffer->releaseAsRenderingTarget();
		
		return snapshotImage;
	}
	
	float getScale()
	{
		return (float) openGLContext.getRenderingScale();
	}
	
	void renderInit()
    {
		jassert (OpenGLHelpers::isContextActive());
		
        const float desktopScale = getScale();
		//OpenGLHelpers::clear ( findColour(EditorComponent::backgroundColourId) );
		
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		OpenGLHelpers::setPerspective(60,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()), 1,1000);
		
		// active z-buffer
		glEnable (GL_DEPTH_TEST);
		glDepthFunc (GL_LESS);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// Enable lightings
		glAlphaFunc(GL_LESS, 1);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		
		// smooth
		glShadeModel(GL_SMOOTH);
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
		//CicmLookAt(3,3,2,0,0,0,0,0,1);
	}
	
	void customRender()
    {
		renderInit();
    }
	
    // This is a virtual method in OpenGLRenderer, and is called when it's time
    // to do your GL rendering.
    void renderOpenGL()
    {
		customRender();
    }
	
private:
    OpenGLContext openGLContext;
	t_jucebox* jucebox;
};

#endif