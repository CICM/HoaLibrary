/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_MAXGL
#define DEF_HOA_MAXGL

#include "jit.common.h"
#include "jit.gl.h"

class CICM_GL {
public:
	static inline void setColor(t_jrgb color)
	{
		glColor3d(color.red, color.green, color.blue);
	}
	
	static inline void lineto(double x, double y, double z)
	{
		glVertex3d(x,y,z);
	}
};

#endif



