/*
 *
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

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

//#include <AmbisonicBinaural.h>

typedef struct _HoaBinaural 
{
	t_pxobject					f_ob;			
	//AmbisonicBinaural			*f_ambiBinaural;
	
	int							f_n;
	int							f_sr;
	
	long						f_inputNumber;
	long						f_outputNumber;
	long						f_order;
	long						f_harmonics;
	//std::vector<double>			f_computedOuput;
	
	double						*f_inputSig;
} t_HoaBinaural;


void *HoaBinaural_new(t_symbol *s, long argc, t_atom *argv);
void HoaBinaural_free(t_HoaBinaural *x);
void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s);

void HoaBinaural_float(t_HoaBinaural *x, double f);
void HoaBinaural_int(t_HoaBinaural *x, long n);
void HoaBinaural_open(t_HoaBinaural *x);
void HoaBinaural_doopen(t_HoaBinaural *x);
;
void HoaBinaural_dsp(t_HoaBinaural *x, t_signal **sp, short *count);
t_int *HoaBinaural_perform(t_int *w);

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaBinaural_perform64(t_HoaBinaural *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaBinaural_class;
    

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.binaural~", (method)HoaBinaural_new, (method)HoaBinaural_free, (long)sizeof(t_HoaBinaural), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaBinaural_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaBinaural_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaBinaural_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaBinaural_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaBinaural_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaBinaural_open,		"open",		A_DEFSYM, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaBinaural_class = c;
	
	return 0;
}

void *HoaBinaural_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaBinaural *x = NULL;
	
	if (x = (t_HoaBinaural *)object_alloc((t_class *)HoaBinaural_class)) 
	{
		x->f_order = 4;
		if(argv[0].a_type == A_LONG)
			x->f_order = atom_getlong(argv);
	
		if(x->f_order >= 35)
		{
			x->f_order = 35;
			post("hoa.binaural~ : Maximum order avaible is 35");
		}
		
		x->f_harmonics = 2 * x->f_order + 1;
		
			
		x->f_inputNumber = x->f_harmonics;
		x->f_outputNumber = 2;
		
		//x->f_ambiBinaural = new AmbisonicBinaural(x->f_order);
		
		dsp_setup((t_pxobject *)x, x->f_inputNumber);
		for (int i = 0; i < x->f_outputNumber; i++) 
			outlet_new(x, "signal");
	
		
	}
	return (x);
}

void HoaBinaural_float(t_HoaBinaural *x, double f)
{
	;
}

void HoaBinaural_int(t_HoaBinaural *x, long n)
{
	;
}

void HoaBinaural_open(t_HoaBinaural *x)
{
	defer((t_object *)x, (method)HoaBinaural_doopen, 0, 0, NULL);
}

void HoaBinaural_doopen(t_HoaBinaural *x)
{
	char filename[MAX_PATH_CHARS];
	char file[MAX_PATH_CHARS];
	short path;
	long type;


	filename[0] = 0;
	open_dialog(filename, &path, &type, 0L, 0);
	path_topotentialname(path, filename, file, false);
	path_nameconform(file, filename, PATH_STYLE_MAX_PLAT, PATH_TYPE_BOOT);
	
	post("file %s", file);
	post("filename %s", filename);
}

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_n	= maxvectorsize;
	x->f_sr	= samplerate;
	
	object_method(dsp64, gensym("dsp_add64"), x, HoaBinaural_perform64, 0, NULL);
}

void HoaBinaural_perform64(t_HoaBinaural *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		;
	}
}

void HoaBinaural_dsp(t_HoaBinaural *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_n	= (int)sp[0]->s_n;
	x->f_sr	= (int)sp[0]->s_sr;
	
	pointer_count = x->f_outputNumber + x->f_inputNumber + 2;
	x->f_inputSig = (double *)getbytes(x->f_harmonics * sizeof(double));
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaBinaural_perform, pointer_count, (void **)sigvec);

	free(sigvec);
	
}

t_int *HoaBinaural_perform(t_int *w)
{
	t_HoaBinaural *x			= (t_HoaBinaural *)(w[1]);
	int			n			= (int)(w[2]);
	//t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{	
		;
	}
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}


void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s)
{
	
	if (m == ASSIST_INLET) 
	{
		int harmonicIndex = 0;
		if (a == 0)
			harmonicIndex = 0;
		else {
			harmonicIndex = (int)floor((a-1)/2) + 1;
			if (a%2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %i", harmonicIndex);
	} 
	else 
	{
		if (a == 0)
			sprintf(s,"(Signal) Left headphone");
		else
			sprintf(s,"(Signal) Right headphone");
	}
}


void HoaBinaural_free(t_HoaBinaural *x) 
{
	dsp_free((t_pxobject *)x);
}

