/*
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

#include "ambisonicDecode.h"


typedef struct _HoaDecode 
{
	t_pxobject				f_ob;			
	ambisonicDecode			*f_ambisonicDecoder;

	int						f_ninput;
	int						f_noutput;

} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_scheme(t_HoaDecode *x, t_symbol *s, long argc, t_atom *argv);
void HoaDecode_optim(t_HoaDecode *x, t_symbol *s, long argc, t_atom *argv);

void HoaDecode_dsp(t_HoaDecode *x, t_signal **sp, short *count);
t_int *HoaDecode_perform(t_int *w);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.decoder~", (method)HoaDecode_new, (method)dsp_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_scheme,	"scheme",	A_GIMME, 0);
	class_addmethod(c, (method)HoaDecode_optim,		"optim",	A_GIMME, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDecode_class = c;
	
	return 0;
}

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDecode *x = NULL;
	int order = 4, outputs = 9;
	if (x = (t_HoaDecode *)object_alloc((t_class*)HoaDecode_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			outputs	= atom_getlong(argv+1);
		
		x->f_ambisonicDecoder	= new ambisonicDecode(order, outputs, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambisonicDecoder->getParameters("numberOfInputs"));
		for (int i = 0; i < x->f_ambisonicDecoder->getParameters("numberOfOutputs"); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambisonicDecoder->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaDecode_perform64, 0, NULL);
}

void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambisonicDecoder->process(ins, outs);
}

void HoaDecode_dsp(t_HoaDecode *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_ambisonicDecoder->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_ambisonicDecoder->getParameters("numberOfInputs");
	x->f_noutput = x->f_ambisonicDecoder->getParameters("numberOfOutputs");
	pointer_count = x->f_ambisonicDecoder->getParameters("numberOfInputs") + x->f_ambisonicDecoder->getParameters("numberOfOutputs") + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaDecode_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaDecode_perform(t_int *w)
{
	t_HoaDecode *x			= (t_HoaDecode *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_ambisonicDecoder->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
}

void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		long harmonicIndex = 0;
	
		if (a != 0) 
		{
			harmonicIndex = floor((a - 1) / 2) + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
	}
	else 
		sprintf(s,"(Signal) Speaker %ld", a);			
}

void HoaDecode_scheme(t_HoaDecode *x, t_symbol *s, long argc, t_atom *argv)
{
	double value[argc];
	for(int i = 0; i < argc; i++)
	{
		
		if(atom_gettype(argv+i) == A_FLOAT)
		{
			value[i] = atom_getfloat(argv+i) * 3.14159265 / 180 ;
			post(" scheme %i, %f", i, atom_getfloat(argv+i));
		}
		else if (atom_gettype(argv+i) == A_LONG)
		{
			value[i] = (float)atom_getlong(argv+i) * 3.14159265 / 180 ;
			post(" scheme %i, %f", i, (float)atom_getlong(argv+i));
		}
		
	}
	x->f_ambisonicDecoder->setSpkrsAngles(value, (int)argc);
}

void HoaDecode_optim(t_HoaDecode *x, t_symbol *s, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM)
	{
		std::string decodingId = atom_getsym(argv)->s_name;
		x->f_ambisonicDecoder->setOptimMode(decodingId);
	}
}

void HoaDecode_free(t_HoaDecode *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambisonicDecoder);
}

