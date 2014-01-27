#ifndef MAXBOXCOMPONENT_H_INCLUDED
#define MAXBOXCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <OpenGL/glu.h>

class EditorComponent : public juce::Component,
                        private OpenGLRenderer
{
public:
    
    enum ColourIds
    {
        backgroundColourId          = 0x1001300  /**< A colour to use to fill the slider's background. */
    };
    
	EditorComponent()
	{
		setSize(200, 200);
		openGLContext.setComponentPaintingEnabled(false);
        openGLContext.setRenderer (this);
        openGLContext.attachTo (*this);
        openGLContext.setContinuousRepainting (false);
		m_shouldDrawVectors = true;
		angleZ = angleX = 0;
		speed = 1;
		
		params = gluNewQuadric();
		
		setInterceptsMouseClicks(false, false);
	}
    
	~EditorComponent()
	{
		gluDeleteQuadric(params);
        openGLContext.detach();
		deleteAllChildren();
	}
	
	void shouldDrawVectors(bool draw)
	{
		m_shouldDrawVectors = draw;
	}

	// openGL component mouseDown function
	void mouseDown(const MouseEvent& e)
	{
		speed += 1;
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
		
		buffer->clear( findColour(EditorComponent::backgroundColourId) );
		buffer->makeCurrentRenderingTarget();
		
		customRender();
		
		buffer->releaseAsRenderingTarget();
		
		return snapshotImage;
	}
	
	float getScale()
	{
		return (float) openGLContext.getRenderingScale();
	}

	void customRender()
    {
        jassert (OpenGLHelpers::isContextActive());
		
        const float desktopScale = getScale();
		OpenGLHelpers::clear ( findColour(EditorComponent::backgroundColourId) );
		
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();
		OpenGLHelpers::setPerspective(70,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()), 1,1000);
		//gluPerspective(70,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()),1,1000);
		
		glEnable (GL_DEPTH_TEST); // active le z-buffer
		glClearDepth(1.0f);
		glDepthFunc (GL_LESS);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		
		// Enable lighting
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		// enable color with lighting
		glEnable(GL_COLOR_MATERIAL);
		
		// smooth
		glShadeModel(GL_SMOOTH);
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
		gluLookAt(3,4,2,0,0,0,0,0,1);
		
		glRotated(angleZ,0,0,1);
		glRotated(angleX,1,0,0);
		
		if (m_shouldDrawVectors)
			drawCartVectors();
		
		glColor3ub(255,255,255); // white
		gluQuadricDrawStyle( params, GLU_LINE);
		// gluSphere(GLUquadric*, nbHoriz, nbVertic)
		gluSphere(params,2, 20, 20);
		

		
//		glFlush();
		
		angleZ += speed;
		angleX += speed;
		
        //glViewport (0, 0, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()));
    }

    // This is a virtual method in OpenGLRenderer, and is called when it's time
    // to do your GL rendering.
    void renderOpenGL()
    {
		customRender();
    }
	
	void drawCartVectors()
	{
		gluQuadricDrawStyle( params, GLU_FILL);
		
		// verctor Z
		glColor3ub(0,0,255);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 10, 10);
		glTranslated(0,0,-2.5);

		// verctor X
		glColor3ub(255,0,0);
		glRotated(90,0,1,0);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(-90,0,-1,0);
		

		glColor3ub(0, 255, 0);
		glRotated(-90,1,0,0);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(90,-1,0,0);
		
		// center shere (cosmetic)
		glColor3ub(150, 150, 150);
		gluSphere(params, 0.2, 10, 10);
	}

private:
    OpenGLContext openGLContext;
	double angleZ, angleX, speed;
	GLUquadric* params;
	bool m_shouldDrawVectors;
};

juce::Component* createMaxBoxComponent()
{
    return new EditorComponent();
}

#endif