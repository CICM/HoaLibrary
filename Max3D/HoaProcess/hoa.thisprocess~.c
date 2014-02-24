/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.this~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "hoa.process~.h"

typedef struct _hoa_thisprocess
{
    t_object x_obj;
	
	// outlets
	void *out_index, *out_harmonicBand, *out_harmonicArgument, *out_order, *out_mute;
	
	long index;
	
	void *hoaProcessor_parent;
	Hoa3D::Ambisonic*	f_ambisonic;
	
} t_hoa_thisprocess;

t_class *hoa_thisprocess_class;

void *hoa_thisprocess_new(t_symbol *s, short argc, t_atom *argv);
void hoa_thisprocess_free(t_hoa_thisprocess *x);
void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_thisprocess_loadbang(t_hoa_thisprocess *x);
void hoa_thisprocess_bang(t_hoa_thisprocess *x);
void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s);


int C74_EXPORT main(void)
{
	t_class* c;
    c = class_new("hoa.thisprocess~", (method)hoa_thisprocess_new, (method)hoa_thisprocess_free, sizeof(t_hoa_thisprocess), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
	
	class_addmethod(c, (method)hoa_thisprocess_assist,			"assist",	A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_loadbang,		"loadbang", A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_mute,			"mute",		A_GIMME, 0);
	class_addmethod(c, (method)hoa_thisprocess_bang,			"bang",		0);
	
	class_register(CLASS_BOX, c);
	hoa_thisprocess_class = c;
	return 0;
}


void *hoa_thisprocess_new(t_symbol *s, short argc, t_atom *argv)
{
	int order;
    t_hoa_thisprocess *x = (t_hoa_thisprocess *) object_alloc(hoa_thisprocess_class);
    
	x->out_mute				= intout(x);
	x->out_order			= intout(x);
	x->out_harmonicArgument = intout(x);
	x->out_harmonicBand		= intout(x);
    x->out_index			= intout(x);
	
	x->hoaProcessor_parent = Get_HoaProcessor_Object();
	order = HoaProcessor_Get_Ambisonic_Order(x->hoaProcessor_parent);
	x->index = Get_HoaProcessor_Patch_Index(x->hoaProcessor_parent);
	
	x->f_ambisonic = new Hoa3D::Ambisonic(order);
	
	return (x);
}

void hoa_thisprocess_free(t_hoa_thisprocess *x)
{
	;
}

void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv)
{	
	long arg_val;
	
	if (!argc)
		return;
	
	arg_val = atom_getlong(argv);
	
	HoaProcessor_Set_Patch_On (x->hoaProcessor_parent, x->index, !arg_val);
	outlet_int(x->out_mute, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
}

void hoa_thisprocess_loadbang(t_hoa_thisprocess *x)
{
	hoa_thisprocess_bang(x);
}

void hoa_thisprocess_bang(t_hoa_thisprocess *x)
{
	if (x->hoaProcessor_parent)
	{
		if (x->index > 0)
		{
			outlet_int(x->out_mute, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
			outlet_int(x->out_order, HoaProcessor_Get_Ambisonic_Order (x->hoaProcessor_parent));
			outlet_int(x->out_harmonicArgument, x->f_ambisonic->getHarmonicArgument(x->index-1));
			outlet_int(x->out_harmonicBand, x->f_ambisonic->getHarmonicBand(x->index-1));
			outlet_int (x->out_index, x->index);
		}
	}
}

void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_OUTLET) 
	{
		switch (a)
		{
			case 0:
				sprintf(s,"Index");
				break;
			case 1:
				sprintf(s,"Harmonic Band");
				break;
			case 2:
				sprintf(s,"Harmonic Argument");
				break;
			case 3:
				sprintf(s,"Ambisonic Order");
				break;
			case 4:
				sprintf(s,"Mute Status");
				break;
		}
	}
    else 
	{
		sprintf(s,"Set Mute, Bang for Report");
    }
}