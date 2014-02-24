/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.out~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "AH_VectorOps.h"
#include "hoa.process~.h"

typedef struct _hoa_out
{
    t_pxobject x_obj;
	
	void ***outptrs_ptr;
	long declared_sig_outs;
	
	long outlet_num;
	long parent_patcher_index;
	
} t_hoa_out;

t_class *hoa_out_class;

void hoa_out_free(t_hoa_out *x);
void *hoa_out_new(long outlet_num);
void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s);
void hoa_out_int(t_hoa_out *x, long intin);

void hoa_out_dsp64 (t_hoa_out *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_out_perform_scalar64 (t_hoa_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);
#ifdef VECTOR_F64_128BIT
void hoa_out_perform64 (t_hoa_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);
#endif


int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.out~", (method) hoa_out_new, (method)hoa_out_free, sizeof(t_hoa_out), NULL, A_DEFLONG, 0);
	
	hoa_initclass(c, (method)NULL);
	class_addmethod(c, (method)hoa_out_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)hoa_out_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)hoa_out_int, "int", A_LONG, 0);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_out_class = c;
	return 0;
}

void *hoa_out_new(long outlet_num)
{
    t_hoa_out *x = (t_hoa_out *)object_alloc(hoa_out_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();

    dsp_setup((t_pxobject *)x, 1);
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->outlet_num = (outlet_num > 0) ? outlet_num : x->parent_patcher_index;
	
	x->outptrs_ptr = HoaProcessor_Get_Outptrs_Ptr(hoaprocessor_parent, Get_HoaProcessor_Patch_Index(hoaprocessor_parent));
	x->declared_sig_outs = HoaProcessor_Get_Declared_Sigouts(hoaprocessor_parent);
		
    return (x);
}

void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(signal) Signal Output %ld of Patcher / (int) Outlet Number", x->outlet_num);
}

void hoa_out_int (t_hoa_out *x, long intin)
{
	x->outlet_num = intin;
}

void hoa_out_dsp64(t_hoa_out *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
#ifdef VECTOR_F64_128BIT
	if (maxvectorsize >= 8 && SSE2_check())
		object_method(dsp64, gensym("dsp_add64"), x, hoa_out_perform64, 0, NULL);				// aligned vector 
else
#endif
		object_method(dsp64, gensym("dsp_add64"), x, hoa_out_perform_scalar64, 0, NULL);		// scalar routine
}

// Perform Routine for misaligned vectors or small vector sizes (done in scalar code) 64 Bit

void hoa_out_perform_scalar64(t_hoa_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
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


#ifdef VECTOR_F64_128BIT

// Aligned SIMD Perform Routine 64 Bit

void hoa_out_perform64(t_hoa_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
{	
    vDouble *in1 = (vDouble *) ins[0];	
	vDouble *io_pointer;
	
	double ***outptrs_ptr = (double ***) x->outptrs_ptr;
	double **out_ptrs;
	
	long declared_sig_outs = x->declared_sig_outs;
	long outlet_num = x->outlet_num;
	long i;
	
	if (outptrs_ptr)
	{
		out_ptrs = *outptrs_ptr;
		if (out_ptrs && outlet_num > 0 && outlet_num <= declared_sig_outs)
		{
			io_pointer = (vDouble *) out_ptrs[outlet_num - 1];
			if (io_pointer)
			{
				for (i = 0; i < vec_size >> 1; i++)
				{
					*io_pointer = F64_VEC_ADD_OP (*io_pointer, *in1++);
					io_pointer++;
				}
			}
		}
	}
}

#endif

void hoa_out_free(t_hoa_out *x)
{
	dsp_free(&x->x_obj);
}
