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
	
	void *a_outlet;
	void *b_outlet;
	void *c_outlet;
	void *m_clock;
	
	long index;
	
	void *hoaProcessor_parent;
	
} t_hoa_thisprocess;

t_class *hoa_thisprocess_class;
t_symbol *ps_deletepatch; 


void *hoa_thisprocess_new(long on);
void hoa_thisprocess_free(t_hoa_thisprocess *x);
void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_thisprocess_flags(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_thisprocess_loadbang(t_hoa_thisprocess *x);
void hoa_thisprocess_bang(t_hoa_thisprocess *x);
void hoa_thisprocess_delete(t_hoa_thisprocess *x);
void clock_delete(t_hoa_thisprocess *x);
void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s);


int C74_EXPORT main(void)
{
	t_class* c;
    c = class_new("hoa.thisprocess~", (method)hoa_thisprocess_new, (method)hoa_thisprocess_free, sizeof(t_hoa_thisprocess), NULL, A_DEFLONG, 0);
	
	hoa_initclass(c, (method)NULL);
	
	class_addmethod(c, (method)hoa_thisprocess_assist,			"assist",	A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_loadbang,		"loadbang", A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_delete,			"delete",			0);
	class_addmethod(c, (method)hoa_thisprocess_mute,			"mute",		A_GIMME, 0);
	class_addmethod(c, (method)hoa_thisprocess_flags,			"flags",	A_GIMME, 0);
	class_addmethod(c, (method)hoa_thisprocess_bang,			"bang",		0);
	
	class_register(CLASS_BOX, c);
	
	ps_deletepatch = gensym("deletepatch");
	
	hoa_thisprocess_class = c;
	
	return 0;
}


void *hoa_thisprocess_new(long on)
{
    t_hoa_thisprocess *x = (t_hoa_thisprocess *) object_alloc(hoa_thisprocess_class);
    
	x->b_outlet = intout(x);
    x->a_outlet = intout(x);
	x->m_clock = clock_new(x, (method)*clock_delete);
	
	x->hoaProcessor_parent = Get_HoaProcessor_Object();
	x->index = Get_HoaProcessor_Patch_Index(x->hoaProcessor_parent);

	HoaProcessor_Set_Patch_On (x->hoaProcessor_parent, x->index, on);
	
	return (x);
}

void hoa_thisprocess_free(t_hoa_thisprocess *x)
{
	freeobject((t_object *)x->m_clock);
}

void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv)
{	
	long arg_val;
	
	if (!argc)
		return;
	
	arg_val = atom_getlong(argv);
	
	HoaProcessor_Set_Patch_On (x->hoaProcessor_parent, x->index, !arg_val);
	outlet_int(x->b_outlet, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
}

void hoa_thisprocess_flags(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv)
{	
	long arg_val;
	
	if (!argc)
		return;
	
	arg_val = atom_getlong(argv);
	
	HoaProcessor_Set_Patch_On (x->hoaProcessor_parent, x->index, arg_val);
	outlet_int(x->b_outlet, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
}

void hoa_thisprocess_loadbang(t_hoa_thisprocess *x)
{
	hoa_thisprocess_bang(x);
}

void hoa_thisprocess_bang(t_hoa_thisprocess *x)
{
	outlet_int(x->b_outlet, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
	if (x->index)
		outlet_int (x->a_outlet, x->index);
}

void hoa_thisprocess_delete(t_hoa_thisprocess *x)
{
	clock_set(x->m_clock, 0L);
}

void clock_delete(t_hoa_thisprocess *x)
{
	t_atom arg;
	
	atom_setlong(&arg, x->index);
	
	if (x->hoaProcessor_parent)
		typedmess(((t_object *)x->hoaProcessor_parent), ps_deletepatch, 1, &arg);
}

void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_OUTLET) 
	{
		switch (a)
		{
			case 0:
				sprintf(s,"Patch Index");
				break;
			case 1:
				sprintf(s,"Mute Status");
				break;
			case 2:
				sprintf(s,"Busy Status");
				break;
		}
	}
    else 
	{
		sprintf(s,"Set Mute / Busy / Flags, Bang for Report");
    }
}