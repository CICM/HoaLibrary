/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef MAXBOXCOMPONENT_H_INCLUDED
#define MAXBOXCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../Sources/HoaOpenGL/OpenGLTools.h"

class EditorComponent : public juce::Component,
private OpenGLRenderer
{
public:
	EditorComponent()
	{
		setSize(200, 200);
		openGLContext.setComponentPaintingEnabled(false);
        openGLContext.setRenderer (this);
        openGLContext.attachTo (*this);
        openGLContext.setContinuousRepainting (false);
		m_shouldDrawVectors = true;
		camX = camY = camZ = 0.0f;
		
		setInterceptsMouseClicks(false, false);
	}
    
	~EditorComponent()
	{
        openGLContext.detach();
		deleteAllChildren();
	}
	
	void shouldDrawVectors(bool draw)
	{
		m_shouldDrawVectors = draw;
	}
	
	void setCamera(double* camVector)
	{
		camX = camVector[0];
		camY = camVector[1];
		camZ = camVector[2];
	}
    
    void colourChanged()
    {
        //repaint();
    }
    
    void newOpenGLContextCreated()
    {
		
    }
	
    void openGLContextClosing()
    {
        
    }
	
	// return the openGL drawings as an image.
	Image makeScreenshot()
	{
		const float desktopScale = (float) openGLContext.getRenderingScale();
		Image snapshotImage = Image (OpenGLImageType().create (Image::ARGB, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()), true));
		OpenGLFrameBuffer* buffer = OpenGLImageType::getFrameBufferFrom(snapshotImage);
		
		//buffer->clear( findColour(EditorComponent::backgroundColourId) );
		buffer->makeCurrentRenderingTarget();
		
		customRender();
		
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
		
		CicmLookAt(3,3,2,0,0,0,0,0,1);
		
		glRotated(camX,1,0,0);
		glRotated(camY,0,1,0);
		glRotated(camZ,0,0,1);
	}
	
	void customRender()
    {
		renderInit();
		
		// vectors if enabled :
		if (m_shouldDrawVectors)
			drawCartVectors();
		
		drawSphere();
		
		//drawMeters();
		
		// outside sphere :
		//OpenGLHelpers::setColour (  findColour(EditorComponent::sphereColourId) );
		glLineWidth(1);
    }
	
    // This is a virtual method in OpenGLRenderer, and is called when it's time
    // to do your GL rendering.
    void renderOpenGL()
    {
		customRender();
    }
	
	void drawSphere()
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(1,1,0);
		glVertex3f(0,1,1);
		glEnd();
	}
	
	void drawCartVectors()
	{
		// vector Z
		glColor3ub(255,0,0);
		glRotated(90,0,1,0);
		//gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		//gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(-90,0,-1,0);
		
		// vector X
		glColor3ub(0, 0, 255);
		glRotated(-90,1,0,0);
		//gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		//gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(90,-1,0,0);
		
		// vector Y
		glColor3ub(0, 255, 0);
		//gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		//gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		
		// center shere (cosmetic)
		//OpenGLHelpers::setColour (  findColour(EditorComponent::sphereColourId) );
		//gluSphere(params, 0.1, 10, 10);
	}
	
private:
    OpenGLContext openGLContext;
	double camX, camY, camZ;
	bool m_shouldDrawVectors;
};

juce::Component* createMaxBoxComponent()
{
    return new EditorComponent();
}

#endif