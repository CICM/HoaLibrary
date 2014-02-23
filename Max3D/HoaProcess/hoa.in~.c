/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.in~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "hoa.process~.h"

typedef struct _hoa_in
{
    t_pxobject x_obj;
	
	long declared_sig_ins;
	double **sig_ins;
	
	long valid;
	long inlet_num;
	
} t_hoa_in;

t_class *hoa_in_class;

void hoa_in_free(t_hoa_in *x);
void *hoa_in_new(long inlet_num);
void hoa_in_assist(t_hoa_in *x, void *b, long m, long a, char *s);
void hoa_in_int(t_hoa_in *x, long inlet_num);
void hoa_in_dsp64(t_hoa_in *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_in_perform64(t_hoa_in *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.in~", (method)hoa_in_new, (method)hoa_in_free, sizeof(t_hoa_in), NULL, A_DEFLONG, 0);
    
	hoa_initclass(c, (method)NULL);
	
	class_addmethod(c, (method)hoa_in_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)hoa_in_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)hoa_in_int, "int", A_LONG, 0);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_in_class = c;
	return 0;
}

void hoa_in_free(t_hoa_in *x)
{
	dsp_free(&x->x_obj);
}

void *hoa_in_new(long inlet_num)
{
    t_hoa_in *x = (t_hoa_in *)object_alloc(hoa_in_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();
	long declared_sig_ins;

    dsp_setup((t_pxobject *)x, 1);
    outlet_new((t_object *)x,"signal");
	
	x->inlet_num = inlet_num;
	x->valid = 0;
	
	hoaprocessor_parent = Get_HoaProcessor_Object();
	declared_sig_ins = HoaProcessor_Get_Declared_Sigins(hoaprocessor_parent);

	x->sig_ins = (double**) HoaProcessor_Get_Sigins(hoaprocessor_parent);
	
	if (inlet_num <= declared_sig_ins && inlet_num >= 1)
		x->valid = 1;
		
	x->declared_sig_ins = declared_sig_ins;
	
    return (x);
}

void hoa_in_int(t_hoa_in *x, long inlet_num)
{
	x->valid = 0;
	x->inlet_num = inlet_num;
	
	if (inlet_num >= 1 && inlet_num <= x->declared_sig_ins)
		x->valid = 1;
	else
		x->valid = 0;
}

void hoa_in_assist(t_hoa_in *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_OUTLET)
		sprintf(s,"(signal) Signal Input %ld of Patcher", x->inlet_num);
    else 
		sprintf(s,"(int) Inlet Number");
}

void hoa_in_dsp64(t_hoa_in *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoa_in_perform64, 0, NULL);		// scalar routine
}

void hoa_in_perform64(t_hoa_in *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
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
