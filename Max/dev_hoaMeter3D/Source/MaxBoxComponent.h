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
        openGLContext.setRenderer (this);
        openGLContext.attachTo (*this);
        openGLContext.setContinuousRepainting (true);
		angleZ = angleX = 0;
		speed = 1;
		
		setInterceptsMouseClicks(false, false);
	}
    
	~EditorComponent()
	{
        openGLContext.detach();
		deleteAllChildren();
	}
    
	void paint (Graphics& g)
	{
        //g.fillAll (findColour(EditorComponent::backgroundColourId));
	}

	// openGL component mouseDown function
	void mouseDown(const MouseEvent& e)
	{
		speed += 1;
	}
    
    void colourChanged	()
    {
        //repaint();
    }
    
    void newOpenGLContextCreated()
    {
		params = gluNewQuadric();
    }

    void openGLContextClosing()
    {
        gluDeleteQuadric(params);
    }

    // This is a virtual method in OpenGLRenderer, and is called when it's time
    // to do your GL rendering.
    void renderOpenGL()
    {
        jassert (OpenGLHelpers::isContextActive());

        const float desktopScale = (float) openGLContext.getRenderingScale();
		//OpenGLHelpers::clear ( Colour ((uint8) 100, (uint8) 100, (uint8) 100, (uint8) 100) );
		OpenGLHelpers::clear ( findColour(EditorComponent::backgroundColourId) );
		
		glEnable (GL_DEPTH_TEST); // active le z-buffer
		glDepthFunc (GL_LESS);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// Enable lighting
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		// enable color with lighting
		glEnable(GL_COLOR_MATERIAL);
		
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		OpenGLHelpers::setPerspective(70,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()),1,1000);
		//gluPerspective(70,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()),1,1000);
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
		gluLookAt(3,4,2,0,0,0,0,0,1);
		
		glRotated(angleZ,0,0,1);
		glRotated(angleX,1,0,0);
		
		glColor3ub(255,255,255); // white
		gluQuadricDrawStyle( params, GLU_LINE);
		// gluSphere(GLUquadric*, nbHoriz, nbVertic)
		gluSphere(params,2, 20, 20);
		
		drawCartVectors();
		
		glFlush();
		
		angleZ += speed;
		angleX += speed;

        glViewport (0, 0, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()));
    }
	
	void drawCartVectors()
	{
		gluQuadricDrawStyle( params, GLU_FILL);
		
		// verctor Z
		glColor3ub(0,0,255);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 5, 5);
		glTranslated(0,0,-2.5);

		// verctor X
		glColor3ub(255,0,0);
		glRotated(90,0,1,0);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 5, 5);
		glTranslated(0,0,-2.5);
		glRotated(-90,0,-1,0);
		

		glColor3ub(0, 255, 0);
		glRotated(-90,1,0,0);
		gluCylinder(params, 0.05, 0.05, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.1, 0., 0.3, 5, 5);
		glTranslated(0,0,-2.5);
		glRotated(90,-1,0,0);
		
		// center shere (cosmetic)
		glColor3ub(150, 150, 150);
		gluSphere(params, 0.2, 10, 10);
	}
	
	void drawCube()
	{
		glBegin(GL_QUADS);
		
		glColor3ub(255,0,0); //face rouge
		glVertex3d(1,1,1);
		glVertex3d(1,1,-1);
		glVertex3d(-1,1,-1);
		glVertex3d(-1,1,1);
		
		glColor3ub(0,255,0); //face verte
		glVertex3d(1,-1,1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,1,-1);
		glVertex3d(1,1,1);
		
		glColor3ub(0,0,255); //face bleue
		glVertex3d(-1,-1,1);
		glVertex3d(-1,-1,-1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,-1,1);
		
		glColor3ub(255,255,0); //face jaune
		glVertex3d(-1,1,1);
		glVertex3d(-1,1,-1);
		glVertex3d(-1,-1,-1);
		glVertex3d(-1,-1,1);
		
		glColor3ub(0,255,255); //face cyan
		glVertex3d(1,1,-1);
		glVertex3d(1,-1,-1);
		glVertex3d(-1,-1,-1);
		glVertex3d(-1,1,-1);
		
		glColor3ub(255,0,255); //face magenta
		glVertex3d(1,-1,1);
		glVertex3d(1,1,1);
		glVertex3d(-1,1,1);
		glVertex3d(-1,-1,1);
		
		glEnd();
	}

private:
    OpenGLContext openGLContext;
	double angleZ, angleX, speed;
	GLUquadric* params;
};

juce::Component* createMaxBoxComponent()
{
    return new EditorComponent();
}

#endif