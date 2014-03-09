/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaCommon.max.h"

typedef struct _pi 
{	
	t_object    f_ob;
	double      f_value;	
	void*       f_outlet;
    t_atom_long f_loadbang;
    
} t_pi;

void pi_bang(t_pi *x);
void pi_loadbang(t_pi *x);
void pi_int(t_pi *x, long n);
void pi_float(t_pi *x, double n) ;
void pi_assist(t_pi *x, void *b, long m, long a, char *s);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

t_class *pi_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.pi", (method)pi_new, (method)NULL, sizeof(t_pi), 0L, A_GIMME, 0);
	
	hoa_initclass(c, NULL);
	
    class_addmethod(c, (method)pi_bang,		"bang",		0);	
    class_addmethod(c, (method)pi_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)pi_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)pi_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)pi_bang,		"dblclick",	A_CANT, 0);
	class_addmethod(c, (method)pi_loadbang,	"loadbang",	A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "outonload",  0, t_pi, f_loadbang);
	CLASS_ATTR_CATEGORY			(c, "outonload",  0, "Behavior");
    CLASS_ATTR_STYLE_LABEL      (c, "outonload",  0, "onoff", "Output value on load");
	CLASS_ATTR_ORDER			(c, "outonload",  0, "1");
	CLASS_ATTR_DEFAULT			(c, "outonload",  0, "0");
	CLASS_ATTR_SAVE				(c, "outonload",  1);
	
	class_register(CLASS_BOX, c);
	pi_class = c;
	return 0;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
	t_pi *x = NULL;
    x = (t_pi *)object_alloc(pi_class);
    if (x)
	{
        x->f_value = 1.;
        x->f_loadbang = 0;
        if (atom_gettype(argv) == A_LONG)
            x->f_value = atom_getlong(argv);
        else if (atom_gettype(argv) == A_FLOAT)
            x->f_value = atom_getfloat(argv);
        
        x->f_outlet = floatout(x);

        attr_args_process(x, argc, argv);
    }
	
	return(x);
}

void pi_loadbang(t_pi *x)
{
	if (x->f_loadbang)
		pi_bang(x);
}

void pi_assist(t_pi *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"(int/float/bang) Compute");
	else
		sprintf(s,"(float) \u03C0 * %.2f", x->f_value);
}

void pi_bang(t_pi *x) 
{
	outlet_float(x->f_outlet, PI * x->f_value);
}


void pi_int(t_pi *x, long n)
{
	x->f_value = n;
	pi_bang(x);
}


void pi_float(t_pi *x, double n) 
{
	x->f_value = n;
	pi_bang(x);
}


