/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.in~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "hoa.process~.h"

typedef struct _hoa_sig_in
{
    t_pxobject	x_obj;
	
	long		declared_sig_ins;
	double		**sig_ins;
	
	long		valid;
	long		inlet_num;
	t_symbol*	parent_mode;
	long		parent_patcher_index;
	
	t_symbol*	comment;
	long		extra;
	
} t_hoa_sig_in;

t_class *hoa_sig_in_class;

void *hoa_sig_in_new(t_symbol *s, long ac, t_atom *av);
void hoa_sig_in_free(t_hoa_sig_in *x);
void hoa_sig_in_assist(t_hoa_sig_in *x, void *b, long m, long a, char *s);
void hoa_sig_in_int(t_hoa_sig_in *x, long inlet_num);
void hoa_sig_in_dsp64(t_hoa_sig_in *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_sig_in_perform64(t_hoa_sig_in *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);

t_max_err hoa_sig_in_setattr_extra(t_hoa_sig_in *x, void *attr, long ac, t_atom *av);
t_max_err hoa_sig_in_setattr_comment(t_hoa_sig_in *x, void *attr, long ac, t_atom *av);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.in~", (method)hoa_sig_in_new, (method)hoa_sig_in_free, sizeof(t_hoa_sig_in), NULL, A_GIMME, 0);
    
	hoa_initclass(c, NULL);
	
	class_addmethod(c, (method)hoa_sig_in_dsp64,	"dsp64",	A_CANT, 0);
    class_addmethod(c, (method)hoa_sig_in_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)hoa_sig_in_int,		"int",		A_LONG, 0);
	
	CLASS_ATTR_LONG		(c, "extra", 0, t_hoa_sig_in, extra);
	CLASS_ATTR_ACCESSORS(c, "extra", 0, hoa_sig_in_setattr_extra);
	CLASS_ATTR_LABEL	(c, "extra", 0, "param index");
	
	CLASS_ATTR_SYM		(c, "comment", 0, t_hoa_sig_in, comment);
	CLASS_ATTR_ACCESSORS(c, "comment", 0, hoa_sig_in_setattr_comment);
	CLASS_ATTR_LABEL	(c, "comment", 0, "Description");
	CLASS_ATTR_SAVE		(c, "comment", 1);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_sig_in_class = c;
	return 0;
}

void hoa_sig_in_free(t_hoa_sig_in *x)
{
	dsp_free(&x->x_obj);
}

void *hoa_sig_in_new(t_symbol *s, long ac, t_atom *av)
{
    t_hoa_sig_in *x = (t_hoa_sig_in *)object_alloc(hoa_sig_in_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();
	long declared_sig_ins;
	long inlet_num = 0;

    dsp_setup((t_pxobject *)x, 1);
    outlet_new((t_object *)x,"signal");
	
	if (ac && av && atom_gettype(av) == A_LONG)
		inlet_num = atom_getlong(av);
	
	x->extra = 0;
	x->comment = gensym("");
	
	attr_args_process(x, ac, av);
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->parent_mode = HoaProcessor_Get_Mode(hoaprocessor_parent);
	
	if (x->parent_mode == gensym("post") || x->parent_mode == gensym("out"))
	{
		x->inlet_num = (inlet_num > 0) ? inlet_num : x->parent_patcher_index;
	}
	else if (x->parent_mode == gensym("no"))
	{
		x->inlet_num = (inlet_num > 0) ? inlet_num : 1;
	}
	
	x->valid = 0;
	
	declared_sig_ins = HoaProcessor_Get_Declared_Sigins(hoaprocessor_parent);
	x->sig_ins = (double**) HoaProcessor_Get_Sigins(hoaprocessor_parent);
	
	if (x->inlet_num <= declared_sig_ins && x->inlet_num >= 1)
		x->valid = 1;
		
	x->declared_sig_ins = declared_sig_ins;
	
    return (x);
}

t_max_err hoa_sig_in_setattr_extra(t_hoa_sig_in *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_LONG)
	{
		x->extra = atom_getlong(av);
		if (x->extra < 0) x->extra = 0;
	}
	return MAX_ERR_NONE;
}

t_max_err hoa_sig_in_setattr_comment(t_hoa_sig_in *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_SYM)
	{
		x->comment = atom_getsym(av);
	}
	return MAX_ERR_NONE;
}

void hoa_sig_in_int(t_hoa_sig_in *x, long inlet_num)
{
	x->valid = 0;
	x->inlet_num = inlet_num;
	
	if (inlet_num >= 1 && inlet_num <= x->declared_sig_ins)
		x->valid = 1;
	else
		x->valid = 0;
}

void hoa_sig_in_assist(t_hoa_sig_in *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_OUTLET)
		sprintf(s,"(signal) Input %ld, %s", x->inlet_num, x->comment->s_name);
    else 
		sprintf(s,"(int) Inlet Number");
}

void hoa_sig_in_dsp64(t_hoa_sig_in *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoa_sig_in_perform64, 0, NULL);		// scalar routine
}

void hoa_sig_in_perform64(t_hoa_sig_in *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
{	
    double *from, *out1;
	long i;
	
    out1 = outs[0];
	
	if (x->valid)
	{
		from = x->sig_ins[x->inlet_num - 1];
		for (i = 0; i < vec_size; i++)				
			*out1++ = *from++;
	}
	else
	{
		for (i = 0; i < vec_size; i++)
			*out1++ = 0;
	}
}
