/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.out~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "../HoaProcess/hoa.process~.h"

typedef struct _hoa_out
{
    t_object x_obj;
	
	long declared_sig_outs;
	
	long outlet_num;
	long parent_patcher_index;
	
} t_hoa_out;

t_class *hoa_out_class;

void *hoa_out_new(t_symbol *s, short argc, t_atom *argv);
void hoa_out_free(t_hoa_out *x);
void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s);

void hoa_out_bang(t_hoa_out *x);
void hoa_out_int(t_hoa_out *x, long n);
void hoa_out_float(t_hoa_out *x, double f);
void hoa_out_list(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv);
void hoa_out_anything(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.out", (method) hoa_out_new, (method)hoa_out_free, sizeof(t_hoa_out), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
    class_addmethod(c, (method)hoa_out_assist,			"assist",			A_CANT,	 0);
	class_addmethod(c, (method)hoa_out_bang,			"bang",						 0);
	class_addmethod(c, (method)hoa_out_int,				"int",				A_LONG,	 0);
	class_addmethod(c, (method)hoa_out_float,			"float",			A_FLOAT, 0);
	class_addmethod(c, (method)hoa_out_list,			"list",				A_GIMME, 0);
	class_addmethod(c, (method)hoa_out_anything,		"anything",			A_GIMME, 0);
    
	class_register(CLASS_BOX, c);
	hoa_out_class = c;
	return 0;
}

void *hoa_out_new(t_symbol *s, short argc, t_atom *argv)
{
    t_hoa_out *x = (t_hoa_out *)object_alloc(hoa_out_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->outlet_num = x->parent_patcher_index;
			
    return (x);
}

void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s)
{
    sprintf(s,"Send Messages Out of a hoa.process~ Patcher");
}

void hoa_out_bang(t_hoa_out *x)
{
	;
}

void hoa_out_int(t_hoa_out *x, long n)
{
	;
}

void hoa_out_float(t_hoa_out *x, double f)
{
	;
}

void hoa_out_list(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv)
{
	;
}

void hoa_out_anything(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv)
{
	;
}

void hoa_out_free(t_hoa_out *x)
{
	;
}
