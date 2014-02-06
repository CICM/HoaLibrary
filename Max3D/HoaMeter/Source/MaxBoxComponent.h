/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2014 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MAXBOXCOMPONENT_H_INCLUDED
#define MAXBOXCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <OpenGL/glu.h>

//==============================================================================
/**
 A three-coordinate vector.
 */
template <typename Type>
class Triangle3D
{
public:
    Triangle3D() noexcept  : p1(), p2(), p3() {}
    Triangle3D (const Vector3D<Type>& vec1, const Vector3D<Type>& vec2, const Vector3D<Type>& vec3) noexcept  : p1 (vec1), p2 (vec2), p3 (vec3) {}
    Triangle3D (const Triangle3D& other) noexcept  : p1 (other.p1), p2 (other.p2), p3 (other.p3) {}
    Triangle3D& operator= (const Triangle3D& other) noexcept     { p1 = other.p1;  p2 = other.p2;  p3 = other.p3;  return *this; }
	
    Triangle3D& operator+= (const Triangle3D& other) noexcept        { p1 += other.p1;  p2 += other.p2;  p3 += other.p3;  return *this; }
    Triangle3D& operator-= (const Triangle3D& other) noexcept        { p1 -= other.p1;  p2 -= other.p2;  p3 -= other.p3;  return *this; }
    Triangle3D& operator*= (const Type& scaleFactor) noexcept      { p1 *= scaleFactor;  p2 *= scaleFactor;  p3 *= scaleFactor;  return *this; }
    Triangle3D& operator/= (const Type& scaleFactor) noexcept      { p1 /= scaleFactor;  p2 /= scaleFactor;  p3 /= scaleFactor;  return *this; }
	
    Vector3D<Type> p1, p2, p3;
};

//typedef struct {
//	double x,y,z;
//} XYZ;
//typedef struct {
//	XYZ p1,p2,p3;
//} FACET3;
typedef struct {
	double x,y,z;
} XYZ;
typedef struct {
	Vector3D<double> p1,p2,p3;
} t_facet3;
#define DTOR 0.0174532925

XYZ MidPoint(XYZ,XYZ);
void Normalise(XYZ *);


class EditorComponent : public juce::Component,
private OpenGLRenderer
{
public:
    
    enum ColourIds
    {
        backgroundColourId          = 0x1001300,  /**< A colour to use to fill the slider's background. */
		sphereColourId              = 0x1001301
    };
    
	EditorComponent()
	{
		setSize(200, 200);
		openGLContext.setComponentPaintingEnabled(false);
        openGLContext.setRenderer (this);
        openGLContext.attachTo (*this);
        openGLContext.setContinuousRepainting (false);
		m_shouldDrawVectors = true;
		camX = camY = camZ = 0.0f;
		
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
	
	void setCamera(double* camVector)
	{
		camX = camVector[0];
		camY = camVector[1];
		camZ = camVector[2];
	}
	
	// openGL component mouseDown function

    
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

	void renderInit()
    {
		jassert (OpenGLHelpers::isContextActive());
		
        const float desktopScale = getScale();
		OpenGLHelpers::clear ( findColour(EditorComponent::backgroundColourId) );
		
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		//OpenGLHelpers::setPerspective(70,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()), 1,1000);
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
		
		//gluLookAt(3,4,2,0,0,0,0,0,1);
		gluLookAt(3,3,2,0,0,0,0,0,1);
		
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
		
		drawMeters();
		
		// outside sphere :
		OpenGLHelpers::setColour (  findColour(EditorComponent::sphereColourId) );
		glLineWidth(1);
		//gluQuadricDrawStyle( params, GLU_FILL);
		gluQuadricDrawStyle( params, GLU_LINE);
		gluSphere(params,2, 40, 40);
		
		glFlush();
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
		
		// vector Z
		glColor3ub(255,0,0);
		glRotated(90,0,1,0);
		gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(-90,0,-1,0);
		
		// vector X
		glColor3ub(0, 0, 255);
		glRotated(-90,1,0,0);
		gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		glRotated(90,-1,0,0);
		
		// vector Y
		glColor3ub(0, 255, 0);
		gluCylinder(params, 0.02, 0.02, 2.5, 5, 5);
		glTranslated(0,0,2.5);
		gluCylinder(params, 0.05, 0., 0.2, 10, 10);
		glTranslated(0,0,-2.5);
		
		// center shere (cosmetic)
		OpenGLHelpers::setColour (  findColour(EditorComponent::sphereColourId) );
		gluSphere(params, 0.1, 10, 10);
	}

	void drawMeters()
	{
//		OpenGLHelpers::setColour ( Colours::chocolate );
//		gluQuadricDrawStyle( params, GLU_FILL);
//		gluDisk(params, 0., 0.5, 20, 20);
		
		int i,j;
		int n = 0, nstart;
		int iterations = 2;
		//FACET3 *f = NULL;
		//double theta[3] = {0.0,35.0,80.0}, phi[3] = {10.0,15.0,80.0}; // corner in polar coordinates
		//XYZ p1, p2, p3;
		double theta[3] = {0.0,0.35,0.8}, phi[3] = {0.1,0.15,0.8}; // corner in polar coordinates
		
		Array<Triangle3D<double>> f;
		Vector3D<double> p1, p2, p3;
				
		// Start with the vertices of the triangle
		f.resize(1);
		p1.x = cos(phi[0]*DTOR) * cos(theta[0]*DTOR);
		p1.y = cos(phi[0]*DTOR) * sin(theta[0]*DTOR);
		p1.z = sin(phi[0]*DTOR);
		p2.x = cos(phi[1]*DTOR) * cos(theta[1]*DTOR);
		p2.y = cos(phi[1]*DTOR) * sin(theta[1]*DTOR);
		p2.z = sin(phi[1]*DTOR);
		p3.x = cos(phi[2]*DTOR) * cos(theta[2]*DTOR);
		p3.y = cos(phi[2]*DTOR) * sin(theta[2]*DTOR);
		p3.z = sin(phi[2]*DTOR);
		f[0].p1 = p1;
		f[0].p2 = p2;
		f[0].p3 = p3;
		
		n = 1;
		
		for (i=1;i<iterations;i++) {
			nstart = n;
			
			for (j=0;j<nstart;j++) {
				//f = realloc(f,(n+3)*sizeof(FACET3));
				f.resize(n+3);
				
				// Create initially copies for the new facets
				f[n  ] = f[j];
				f[n+1] = f[j];
				f[n+2] = f[j];
				
				p1 = (f[j].p1 + f[j].p2) * 0.5;
				p1 = p1.normalised();
				p2 = (f[j].p2 + f[j].p3) * 0.5;
				p2 = p2.normalised();
				p3 = (f[j].p3 + f[j].p1) * 0.5;
				p3 = p3.normalised();
				
				// Replace the current facet
				f[j].p2 = p1;
				f[j].p3 = p3;
				
				// Create the changed vertices in the new facets
				f[n  ].p1 = p1;
				f[n  ].p3 = p2;
				f[n+1].p1 = p3;
				f[n+1].p2 = p2;
				f[n+2].p1 = p1;
				f[n+2].p2 = p2;
				f[n+2].p3 = p3;
				n += 3;
			}
		}
		
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		for (i=0;i<n;i++) {
			glVertex3f(f[i].p1.x,f[i].p1.y,f[i].p1.z);
			glVertex3f(f[i].p2.x,f[i].p2.y,f[i].p2.z);
			glVertex3f(f[i].p3.x,f[i].p3.y,f[i].p3.z);
		}
		glEnd();
		
		
		
		fprintf(stderr,"%d facets generated\n",n);
		
		// Save as STL, for simplicity only
		printf("solid\n");
		for (i=0;i<n;i++) {
			printf("facet normal 0 0 1\n");
			printf("outer loop\n");
			printf("vertex %g %g %g\n",f[i].p1.x,f[i].p1.y,f[i].p1.z);
			printf("vertex %g %g %g\n",f[i].p2.x,f[i].p2.y,f[i].p2.z);
			printf("vertex %g %g %g\n",f[i].p3.x,f[i].p3.y,f[i].p3.z);
			printf("endloop\n");
			printf("endfacet\n");
		}
		printf("endsolid");
	}
	
	/*
	 Return the midpoint between two vectors
	 */
	XYZ MidPoint(XYZ p1,XYZ p2)
	{
		XYZ p;
		
		p.x = (p1.x + p2.x) / 2;
		p.y = (p1.y + p2.y) / 2;
		p.z = (p1.z + p2.z) / 2;
		
		return(p);
	}
	
	/*
	 Normalise a vector
	 */
	void Normalise(XYZ *p)
	{
		double length;
		
		length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
		if (length != 0) {
			p->x /= length;
			p->y /= length;
			p->z /= length;
		} else {
			p->x = 0;
			p->y = 0;
			p->z = 0;
		}
	}
	
	
	
private:
    OpenGLContext openGLContext;
	double camX, camY, camZ;
	GLUquadric* params;
	bool m_shouldDrawVectors;
};

juce::Component* createMaxBoxComponent()
{
    return new EditorComponent();
}

#endif