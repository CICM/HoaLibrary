/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jit.common.h"
#include "jit.gl.h"

typedef struct _hoa_gl_scope 
{
	// Max object
	t_object			ob;			
	// 3d object extension.  This is what all objects in the GL group have in common.
	void				*ob3d;
} t_hoa_gl_scope;

void *_hoa_gl_scope_class;

t_jit_err hoa_gl_scope_init(void);
t_hoa_gl_scope *hoa_gl_scope_new(t_symbol * dest_name);
void hoa_gl_scope_free(t_hoa_gl_scope *x);

t_jit_err hoa_gl_scope_draw(t_hoa_gl_scope *x);
t_jit_err hoa_gl_scope_dest_closing(t_hoa_gl_scope *x);
t_jit_err hoa_gl_scope_dest_changed(t_hoa_gl_scope *x);
t_jit_err build_simple_chunk(t_hoa_gl_scope *x);


// --------------------------------------------------------------------------------

t_jit_err hoa_gl_scope_init(void) 
{
	long ob3d_flags = JIT_OB3D_NO_MATRIXOUTPUT; // no matrix output
	void *ob3d;
	
	_hoa_gl_scope_class = jit_class_new("hoa_gl_scope", 
		(method)hoa_gl_scope_new, (method)hoa_gl_scope_free,
		sizeof(t_hoa_gl_scope),A_DEFSYM,0L);
	
	// set up object extension for 3d object, customized with flags
	ob3d = jit_ob3d_setup(_hoa_gl_scope_class, 
				calcoffset(t_hoa_gl_scope, ob3d), 
				ob3d_flags);
	
	// define our OB3D draw method.  called in automatic mode by 
	// jit.gl.render or otherwise through ob3d when banged. this 
	// method is A_CANT because our draw setup needs to happen 
	// in the ob3d beforehand to initialize OpenGL state 
	jit_class_addmethod(_hoa_gl_scope_class, 
		(method)hoa_gl_scope_draw, "ob3d_draw", A_CANT, 0L);
	
	// define our dest_closing and dest_changed methods. 
	// these methods are called by jit.gl.render when the 
	// destination context closes or changes: for example, when 
	// the user moves the window from one monitor to another. Any 
	// resources your object keeps in the OpenGL machine 
	// (e.g. textures, display lists, vertex shaders, etc.) 
	// will need to be freed when closing, and rebuilt when it has 
	// changed. In this object, these functions do nothing, and 
	// could be omitted.
	jit_class_addmethod(_hoa_gl_scope_class, 
		(method)hoa_gl_scope_dest_closing, "dest_closing", A_CANT, 0L);
	jit_class_addmethod(_hoa_gl_scope_class, 
		(method)hoa_gl_scope_dest_changed, "dest_changed", A_CANT, 0L);

	// must register for ob3d use
	jit_class_addmethod(_hoa_gl_scope_class, 
		(method)jit_object_register, "register", A_CANT, 0L);

	jit_class_register(_hoa_gl_scope_class);

	return JIT_ERR_NONE;
}


t_hoa_gl_scope *hoa_gl_scope_new(t_symbol * dest_name)
{
	t_hoa_gl_scope *x;

	// make jit object
	if ((x = (t_hoa_gl_scope *)jit_object_alloc(_hoa_gl_scope_class)))
	{
		// create and attach ob3d
		jit_ob3d_new(x, dest_name);
	} 
	else 
	{
		x = NULL;
	}	
	return x;
}


void hoa_gl_scope_free(t_hoa_gl_scope *x)
{
	// free our ob3d data 
	jit_ob3d_free(x);
}


t_jit_err hoa_gl_scope_draw(t_hoa_gl_scope *x)
{
	t_jit_err result = JIT_ERR_NONE;
	
	// draw our OpenGL geometry. 
	glBegin(GL_QUADS);
	glVertex3f(-0.5,-1,0);
	glVertex3f(-1,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1,-1,0);
	glEnd();
	
	return result;
}

t_jit_err hoa_gl_scope_dest_closing(t_hoa_gl_scope *x)
{
	// nothing in this object to free. 
	return JIT_ERR_NONE;
}

t_jit_err hoa_gl_scope_dest_changed(t_hoa_gl_scope *x)
{
	// nothing in this object to update. 
	return JIT_ERR_NONE;
}


