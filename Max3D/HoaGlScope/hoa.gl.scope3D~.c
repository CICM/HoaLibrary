/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "hoa.gl.scope3D~.h"

void *_hoa_gl_scope_class;

t_jit_err hoa_gl_scope_init(void);
t_hoa_gl_scope *hoa_gl_scope_new(t_symbol * dest_name, t_max_hoa_gl_scope* _maxobj);
void hoa_gl_scope_free(t_hoa_gl_scope *x);

t_jit_err hoa_gl_scope_draw(t_hoa_gl_scope *x);
t_jit_err hoa_gl_scope_dest_closing(t_hoa_gl_scope *x);
t_jit_err hoa_gl_scope_dest_changed(t_hoa_gl_scope *x);
t_jit_err build_simple_chunk(t_hoa_gl_scope *x);

void hoa_gl_scope_set_index(t_hoa_gl_scope *x, long i);


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
	jit_class_addmethod(_hoa_gl_scope_class, (method)hoa_gl_scope_draw, "ob3d_draw", A_CANT, 0L);
	
	jit_class_addmethod(_hoa_gl_scope_class, (method)hoa_gl_scope_set_index, "set_index", A_LONG, 0L);
	
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

void hoa_gl_scope_set_index(t_hoa_gl_scope *x, long i)
{
	post("method index");
}


//t_hoa_gl_scope *hoa_gl_scope_new(t_symbol * dest_name)
t_hoa_gl_scope *hoa_gl_scope_new(t_symbol * dest_name, t_max_hoa_gl_scope* _maxobj)
{
	t_hoa_gl_scope *x;

	// make jit object
	if ((x = (t_hoa_gl_scope *)jit_object_alloc(_hoa_gl_scope_class)))
	{
		// create and attach ob3d
		jit_ob3d_new(x, dest_name);
		x->mx = _maxobj;
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
	
	int nbRows, nbColumns;
	float value;
    float one, two;
	t_jrgb red  = {1.,0.,0.};
	t_jrgb blue = {0.,0.,1.};
	nbRows = x->mx->f_scope->getNumberOfRows();
	nbColumns = x->mx->f_scope->getNumberOfColumns();
	
	x->mx->f_scope->process(x->mx->f_signals + x->mx->f_index * x->mx->f_scope->getNumberOfHarmonics());
	
	glPointSize(1.0f);
	//glBegin(GL_TRIANGLE_FAN);
	glBegin(GL_LINE_LOOP);
	
	for(int i = 0; i < nbRows; i++)
    {
        one  =   0;
        two = (double)i / (double)(nbRows - 1) * CICM_PI;
        value = x->mx->f_scope->getValue(i, 0);
        if(value < 0)
        {
            CICM_GL::setColor(blue);
            value= -value;
        }
        else
            CICM_GL::setColor(red);

		CICM_GL::lineto(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int j = 1; j < nbColumns; j++)
        {
            one  =   (double)j / (double)nbColumns * CICM_2PI;
            value = x->mx->f_scope->getValue(i, j);
            if(value < 0)
            {
                CICM_GL::setColor(blue);
                value= -value;
            }
            else
                CICM_GL::setColor(red);
			
            CICM_GL::lineto(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
        
        one  =   0;
        value = x->mx->f_scope->getValue(i, 0);
        if(value < 0)
        {
            CICM_GL::setColor(blue);
            value = -value;
        }
        else
            CICM_GL::setColor(red);
        
        CICM_GL::lineto(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
    }
	
	for(int j = 0; j < nbColumns; j++)
    {
        one  =   (double)j / (double)nbColumns * CICM_2PI;
        two  = 0.;
        value = x->mx->f_scope->getValue(0, j);
        if(value < 0)
        {
            CICM_GL::setColor(blue);
            value= -value;
        }
        else
            CICM_GL::setColor(red);
		
		CICM_GL::lineto(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int i = 1; i < nbRows; i++)
        {
            two = (double)i / (double)(nbRows - 1) * CICM_PI;
            value = x->mx->f_scope->getValue(i, j);
            if(value < 0)
            {
                CICM_GL::setColor(blue);
                value= -value;
            }
            else
                CICM_GL::setColor(red);
			
            CICM_GL::lineto(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
    }
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


