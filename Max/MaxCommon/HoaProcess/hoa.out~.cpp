/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.out~ Copyright 2010 Alex Harker. All rights reserved.

#include "../HoaCommon.max.h"
#include "hoa.process~.h"

typedef struct _hoa_sig_out
{
    t_pxobject x_obj;
	
	void ***outptrs_ptr;
	long declared_sig_outs;
	
	long outlet_num;
	long parent_patcher_index;
	
	t_symbol*	comment;
	long		extra;
	
} t_hoa_sig_out;

t_class *hoa_sig_out_class;

void *hoa_sig_out_new(t_symbol *s, long ac, t_atom *av);
void hoa_sig_out_free(t_hoa_sig_out *x);
void hoa_sig_out_assist(t_hoa_sig_out *x, void *b, long m, long a, char *s);
void hoa_sig_out_int(t_hoa_sig_out *x, long intin);

void hoa_sig_out_dsp64 (t_hoa_sig_out *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_sig_out_perform64 (t_hoa_sig_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userextra);

t_max_err hoa_sig_in_setattr_extra(t_hoa_sig_out *x, void *attr, long ac, t_atom *av);
t_max_err hoa_sig_in_setattr_comment(t_hoa_sig_out *x, void *attr, long ac, t_atom *av);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.out~", (method) hoa_sig_out_new, (method)hoa_sig_out_free, sizeof(t_hoa_sig_out), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
	class_addmethod(c, (method)hoa_sig_out_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)hoa_sig_out_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)hoa_sig_out_int, "int", A_LONG, 0);
    
	CLASS_ATTR_LONG		(c, "extra", 0, t_hoa_sig_out, extra);
	CLASS_ATTR_ACCESSORS(c, "extra", 0, hoa_sig_in_setattr_extra);
	CLASS_ATTR_LABEL	(c, "extra", 0, "extra index");
	
	CLASS_ATTR_SYM		(c, "comment", 0, t_hoa_sig_out, comment);
	CLASS_ATTR_ACCESSORS(c, "comment", 0, hoa_sig_in_setattr_comment);
	CLASS_ATTR_LABEL	(c, "comment", 0, "Description");
	CLASS_ATTR_SAVE		(c, "comment", 1);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_sig_out_class = c;
	return 0;
}

void *hoa_sig_out_new(t_symbol *s, long ac, t_atom *av)
{
    t_hoa_sig_out *x = (t_hoa_sig_out *)object_alloc(hoa_sig_out_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();
	
	long outlet_num = 0;
	if (ac && av && atom_gettype(av) == A_LONG)
		outlet_num = atom_getlong(av);

	x->extra = 0;
	x->comment = gensym("");
	
	attr_args_process(x, ac, av);
	
    dsp_setup((t_pxobject *)x, 1);
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	
	//x->outlet_num = (outlet_num > 0) ? outlet_num : x->parent_patcher_index;
	
	x->outlet_num = HoaProcessor_Get_Sigout_Index(hoaprocessor_parent, x->parent_patcher_index, outlet_num, x->extra);
	
	object_post((t_object*)x, "inlet_real_index = %ld", x->outlet_num);
	
	x->outptrs_ptr = HoaProcessor_Get_Outptrs_Ptr(hoaprocessor_parent, Get_HoaProcessor_Patch_Index(hoaprocessor_parent));
	x->declared_sig_outs = HoaProcessor_Get_Declared_Sigouts(hoaprocessor_parent);
		
    return (x);
}

t_max_err hoa_sig_in_setattr_extra(t_hoa_sig_out *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_LONG)
	{
		x->extra = atom_getlong(av);
		if (x->extra < 0) x->extra = 0;
	}
	return MAX_ERR_NONE;
}

t_max_err hoa_sig_in_setattr_comment(t_hoa_sig_out *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_SYM)
	{
		x->comment = atom_getsym(av);
	}
	return MAX_ERR_NONE;
}

void hoa_sig_out_assist(t_hoa_sig_out *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(signal) Output %ld of hoa.process, %s", x->outlet_num, x->comment->s_name);
}

void hoa_sig_out_int (t_hoa_sig_out *x, long intin)
{
	x->outlet_num = intin;
}

void hoa_sig_out_dsp64(t_hoa_sig_out *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoa_sig_out_perform64, 0, NULL);		// scalar routine
}

// Perform Routine for misaligned vectors or small vector sizes (done in scalar code) 64 Bit

void hoa_sig_out_perform64(t_hoa_sig_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userextra)
{	
    double *in1 = ins[0];	
	double *io_pointer;
	double ***outptrs_ptr = (double ***) x->outptrs_ptr;
	double **out_ptrs;
	
	long outlet_num = x->outlet_num;
	long declared_sig_outs = x->declared_sig_outs;
	long i;
	
	if (outptrs_ptr)
	{
		out_ptrs = *outptrs_ptr;
		if (out_ptrs && outlet_num > 0 && outlet_num <= declared_sig_outs)
		{
			io_pointer = out_ptrs[outlet_num - 1];
			for (i = 0; i < vec_size; i++)
			{
				*io_pointer += *in1++; 
				io_pointer++;
			}
		}
	}
}

void hoa_sig_out_free(t_hoa_sig_out *x)
{
	dsp_free(&x->x_obj);
}
