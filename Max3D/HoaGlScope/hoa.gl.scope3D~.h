/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */


#ifndef DEF_HOA_GLSCOPE
#define DEF_HOA_GLSCOPE

#include "../hoa.max.h"
#include "../hoa.maxgl.h"

typedef struct _max_hoa_gl_scope
{
	t_pxobject		ob;
	void*			obex;
	double*         f_signals;
    Hoa3D::Scope*   f_scope;
    int             f_index;
} t_max_hoa_gl_scope;

typedef struct _hoa_gl_scope
{
	// Max object
	t_object			ob;
	// 3d object extension.  This is what all objects in the GL group have in common.
	void*				ob3d;
	// reference to the Max Object
	t_max_hoa_gl_scope* mx;
} t_hoa_gl_scope;

#endif
