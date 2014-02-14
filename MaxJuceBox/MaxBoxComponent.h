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
		//const float desktopScale = (float) openGLContext.getRenderingScale();
		const float desktopScale = 1;
		Image snapshotImage = Image (OpenGLImageType().create (Image::ARGB, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()), true));
		OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(snapshotImage);
		
		buffer->makeCurrentAndClear();
		
		// openGL draw method to implement
		if (jucebox->isInitialised) {
			//object_method((t_object*)jucebox, gensym("jucebox_paint"), &openGLContext);
			object_method((t_object*)jucebox, gensym("jucebox_paint"));
		}
		
		buffer->releaseAsRenderingTarget();
		
		return snapshotImage;
	}
	
	float getScale()
	{
		return (float) openGLContext.getRenderingScale();
	}

    // This is a virtual method in OpenGLRenderer, and is called when it's time
    // to do your GL rendering.
    void renderOpenGL() {}
	
private:
    OpenGLContext openGLContext;
	t_jucebox* jucebox;
};

#endif