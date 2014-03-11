/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_OPENGLTOOLS
#define DEF_HOA_OPENGLTOOLS

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"
}

#include "../JuceLibraryCode/JuceHeader.h"

// convert t_jrgba to juce::Colour
Colour jrgbaToColour(t_jrgba* jrgbaColor)
{
	return Colour(uint8(255 * jrgbaColor->red),
				  uint8(255 * jrgbaColor->green),
				  uint8(255 * jrgbaColor->blue),
				  float(jrgbaColor->alpha));
}

// to perform cross product between 2 vectors in CicmLookAt
void CrossProd(float x1, float y1, float z1, float x2, float y2, float z2, float res[3])
{
	res[0] = y1*z2 - y2*z1;
	res[1] = x2*z1 - x1*z2;
	res[2] = x1*y2 - x2*y1;
}

// my own implementation
void CicmLookAt(float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ)
{
	// i am not using here proper implementation for vectors.
	// if you want, you can replace the arrays with your own
	// vector types
	float f[3];
	
	// calculating the viewing vector
	f[0] = lookAtX - eyeX;
	f[1] = lookAtY - eyeY;
	f[2] = lookAtZ - eyeZ;
	
	
	float fMag, upMag;
	fMag = sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]);
	upMag = sqrt(upX*upX + upY*upY + upZ*upZ);
	
	// normalizing the viewing vector
	if( fMag != 0)
	{
		f[0] = f[0]/fMag;
		f[1] = f[1]/fMag;
		f[2] = f[2]/fMag;
	}
	
	// normalising the up vector. no need for this here if you have your
	// up vector already normalised, which is mostly the case.
	if( upMag != 0 )
	{
		upX = upX/upMag;
		upY = upY/upMag;
		upZ = upZ/upMag;
	}
	
	float s[3], u[3];
	
	CrossProd(f[0], f[1], f[2], upX, upY, upZ, s);
	CrossProd(s[0], s[1], s[2], f[0], f[1], f[2], u);
	
	float M[]=
	{
		s[0], u[0], -f[0], 0,
		s[1], u[1], -f[1], 0,
		s[2], u[2], -f[2], 0,
		0, 0, 0, 1
	};
	
	glMultMatrixf(M);
	glTranslatef (-eyeX, -eyeY, -eyeZ);
}

#endif
