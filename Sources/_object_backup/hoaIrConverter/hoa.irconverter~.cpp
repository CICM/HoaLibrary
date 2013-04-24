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
#include "cicmTools.h"
#include "ambisonicRecomposer.h"

#define MAX_SIZE 256
extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
	#include "buffer.h"
	#include "ext_globalsymbol.h"
}

typedef struct _HoaConvolve 
{
	t_pxobject			f_ob;			
	ambisonicRecomposer* f_ambiRecomposer;
	void*				f_bang_out;
	t_symbol*			f_name[MAX_SIZE];
	t_buffer*			f_buffer[MAX_SIZE];
	long				f_channel[MAX_SIZE];
	float				f_angle[MAX_SIZE];
    double*             f_coeffs;
	long				f_numberOfHarmonics;
	long				f_numberOfChannels;
	
} t_HoaConvolve;

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv);
void HoaConvolve_free(t_HoaConvolve *x);
void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s);

void HoaConvolve_compute(t_HoaConvolve *x);
t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err angle_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);

void *HoaConvolve_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.irconverter~", (method)HoaConvolve_new, (method)HoaConvolve_free, (long)sizeof(t_HoaConvolve), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaConvolve_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaConvolve_compute,		"bang",		0);

	CLASS_ATTR_SYM_VARSIZE		(c, "buffers", 0, t_HoaConvolve, f_name, f_numberOfChannels, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "buffers", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffers", 0, "buffer~ Objects Names");
	CLASS_ATTR_ORDER			(c, "buffers", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffers", NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffers", 0, "");
	CLASS_ATTR_SAVE				(c, "buffers", 1);

	CLASS_ATTR_LONG_VARSIZE		(c, "channels", 0, t_HoaConvolve, f_channel, f_numberOfChannels, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "channels", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channels", 0, "buffer~ Objects Channels");
	CLASS_ATTR_ORDER			(c, "channels", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channels", NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channels", 0, "0");
	CLASS_ATTR_SAVE				(c, "channels", 1);

	CLASS_ATTR_FLOAT_VARSIZE	(c, "angles", 0, t_HoaConvolve, f_angle, f_numberOfChannels, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "angles", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles");
	CLASS_ATTR_ORDER			(c, "angles", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angle_set);
	CLASS_ATTR_DEFAULT			(c, "angles", 0, "0");
	CLASS_ATTR_SAVE				(c, "angles", 1);

	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaConvolve_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaConvolve *x = NULL;

	long order = 4, numberOfChannels = 10;
    x = (t_HoaConvolve *)object_alloc((t_class*)HoaConvolve_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			numberOfChannels	= atom_getlong(argv+1);

		order = Tools::clip_min(order, (long)1);
		numberOfChannels = Tools::clip_min(numberOfChannels, 2 * order + 1);

		x->f_ambiRecomposer	= new ambisonicRecomposer(order, numberOfChannels);
		x->f_numberOfHarmonics	= 2 * order + 1;
		x->f_numberOfChannels	= numberOfChannels;

		for (int i = 0; i < x->f_numberOfChannels; i++)
		{
			x->f_buffer[i] = NULL;
		}

        double* myReverbForm = new double[x->f_numberOfHarmonics +1];
        x->f_coeffs = new double[x->f_numberOfHarmonics];
        
        for(int i = 0; i < (x->f_numberOfHarmonics + 1) / 2; i++)
        {
            myReverbForm[i] = 0.3 * ((double)i / ((x->f_numberOfHarmonics + 1) / 2)) + 0.7;
            myReverbForm[(x->f_numberOfHarmonics + 1) / 2 - 1 - i] = 0.3 * ((double)(i - 0.25)/ ((x->f_numberOfHarmonics + 1) / 2)) + 0.7;
        }
        x->f_ambiRecomposer->process(myReverbForm, x->f_coeffs);
        double factor = 0;
        for(int i = 0; i < x->f_numberOfHarmonics; i++)
        {
            if(x->f_coeffs[i] < 0)
            {
                x->f_coeffs[i-1] -= x->f_coeffs[i];
                x->f_coeffs[i] = 0.;
            }
            if (fabs(x->f_coeffs[i]) > factor)
            {
                factor = fabs(x->f_coeffs[i]);
            }
        }
        for(int i = 0; i < x->f_numberOfHarmonics; i++)
        {
            x->f_coeffs[i] = order * x->f_coeffs[i] / factor;
            post("%f", x->f_coeffs[i]);
        }
        
		dsp_setup((t_pxobject *)x, 1);
		x->f_bang_out = bangout(x);
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_OUTLET)
		sprintf(s,"(Bang) Done");
	else
		sprintf(s,"(Messages or bang ) Compute");
}

void HoaConvolve_free(t_HoaConvolve *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiRecomposer;
}


t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	t_buffer *b;
	t_symbol *name;
	t_atom channel[2];
	if(atom_gettype(argv) == A_SYM)
	{
		if(atom_getsym(argv) == gensym("all"))
		{
			for(int i = 0; i < x->f_numberOfChannels; i++)
			{
				char bufferName[256];
				name = atom_getsym(argv+1);
				sprintf(bufferName, "%s.%i",  name->s_name, i+1);
				name = gensym(bufferName);
				if(x->f_name[i] != name)
				{

					if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~")) 
					{
						if(x->f_name && x->f_buffer[i] != NULL)
						{
							globalsymbol_dereference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						}
						x->f_name[i] = name;
						x->f_buffer[i] = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						atom_setlong(channel, i);
						atom_setlong(channel, x->f_channel[i]);
						channel_set(x, attr, 2, channel);
					}
					else
					{
						x->f_buffer[i] = NULL;
						x->f_name[i] = gensym("none");
					}
				}
			}
		}
		else if(argc > 0)
		{
			if(argc > x->f_numberOfChannels)
			argc = x->f_numberOfChannels;

			for(int i = 0; i < argc; i++)
			{
				name = atom_getsym(argv+i);
				if(x->f_name[i] != name)
				{

					if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~")) 
					{
						if(x->f_name && x->f_buffer[i] != NULL)
						{
							globalsymbol_dereference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						}
						x->f_name[i] = name;
						x->f_buffer[i] = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						atom_setlong(channel, i);
						atom_setlong(channel, x->f_channel[i]);
						channel_set(x, attr, 2, channel);
					}
					else
					{
						x->f_buffer[i] = NULL;
						x->f_name[i] = gensym("none");
					}
				}
			}
		}
	}
	return 0;
}

t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc == 2 && atom_gettype(argv) == A_SYM && atom_gettype(argv+1) == A_LONG)
	{
		for(int i = 0; i < x->f_numberOfChannels; i++)
		{
			if(x->f_buffer[i] == NULL)
			{
				if(atom_getlong(argv+1) >= 1)
					x->f_channel[i] = atom_getlong(argv+1);
			}
			else
			{
				if(atom_getlong(argv+1) > 1 && x->f_channel[i] <= x->f_buffer[i]->b_nchans)
					x->f_channel[i] = atom_getlong(argv+1);
				else if(atom_getlong(argv+1) <= 1)
					x->f_channel[i] = 1;
				else
					x->f_channel[i] = x->f_buffer[i]->b_nchans;
			}
		}
	}
	else if(argc > 0)
	{
		if(argc > x->f_numberOfChannels)
			argc = x->f_numberOfChannels;
		for(int i = 0; i < argc; i++)
		{
			if(x->f_buffer[i] == NULL)
			{
				if(atom_getlong(argv) >= 1)
					x->f_channel[i] = atom_getlong(argv+i);
			}
			else
			{
				if(atom_getlong(argv+i) > 1 && x->f_channel[i] <= x->f_buffer[i]->b_nchans)
					x->f_channel[i] = atom_getlong(argv+i);
				else if(atom_getlong(argv+i) <= 1)
					x->f_channel[i] = 1;
				else
					x->f_channel[i] = x->f_buffer[i]->b_nchans;
			}
		}
	}
	return 0;
}

t_max_err angle_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM && atom_getsym(argv)== gensym("default"))
	{
		for(int i = 0; i < x->f_numberOfChannels; i++)
		{
			x->f_angle[i] = (float)i * 360. / (float)x->f_numberOfChannels;
		}
	}
	else if(argc > 0)
	{
		if(argc > x->f_numberOfChannels)
			argc = x->f_numberOfChannels;
		for(int i = 0; i < argc; i++)
		{
			if(atom_gettype(argv+i) == A_LONG)
				x->f_angle[i] = atom_getlong(argv+i);
			else if(atom_gettype(argv+i) == A_FLOAT)
				x->f_angle[i] = atom_getfloat(argv+i);
		}
	}
	for(int i = 0; i < x->f_numberOfChannels; i++)
	{
		x->f_angle[i] = fmod(x->f_angle[i] + 360., 360.);
	}
	//x->f_ambiRecomposer->setAngles(x->f_angle);
	return 0;
}

void HoaConvolve_compute(t_HoaConvolve *x)
{
	int bufferUsed = 0;
	for(int j = 0; j < x->f_numberOfChannels; j++)
	{
		if(x->f_buffer[j] == NULL)
			bufferUsed = 1;
	}
	if(!bufferUsed)
	{
        post("hi");
		for(int j = 0; j < x->f_numberOfChannels; j++)
		{
			ATOMIC_INCREMENT(&x->f_buffer[j]->b_inuse);
			if (!x->f_buffer[j]->b_valid) 
			{
				ATOMIC_DECREMENT(&x->f_buffer[j]->b_inuse);
				bufferUsed = 1;
			}
		}
		if(!bufferUsed)
		{
			long size = x->f_buffer[0]->b_frames;
			for(int j = 1; j < x->f_numberOfChannels; j++)
			{
				if(x->f_buffer[j]->b_frames > size)
				{
					size = x->f_buffer[j]->b_frames;
				}
			}
			double** datas = new double*[x->f_numberOfChannels];
            for(int i = 0; i < x->f_numberOfChannels; i++)
            {
                datas[i] = new double[size];
            }
			for(int j = 0; j < x->f_numberOfChannels; j++)
			{
				for(long i = 0; i < size; i++)
                {
                    if(i < x->f_buffer[j]->b_frames)
                        datas[j][i] = x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] * 2. / x->f_numberOfChannels;
                    else
                        datas[j][i] = 0.;
                }
            }
            //x->f_ambiRecomposer->setFishEyeFactor(1.);
            //x->f_ambiRecomposer->setVectorSize(size);
            //x->f_ambiRecomposer->process(datas, datas);
            for(int j = 0; j < x->f_numberOfChannels; j++)
				ATOMIC_DECREMENT(&x->f_buffer[j]->b_inuse);
            int resizeOk = 1;
            for(int i = 0; i < x->f_numberOfChannels; i++)
            {
                object_method(x->f_buffer[i], gensym("sizeinsamps"), size);
                if(x->f_buffer[i]->b_frames != size)
                    resizeOk = 0;
            }
            if(resizeOk)
            {
                long offset;
                for(int j = 0; j < x->f_numberOfChannels; j++)
                    ATOMIC_INCREMENT(&x->f_buffer[j]->b_inuse);
                for(int j = 0; j < x->f_numberOfHarmonics; j++)
                {
                    offset = x->f_coeffs[j] * x->f_buffer[j]->b_msr * 100.;
                    post("%f", offset);
                    if(offset > 0)
                    {
                        for(long i = 0; i < size; i++)
                        {/*
                            if(i > offset)
                                x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] = 0.;
                            else*/
                            {
                                for(int k = 0; k < x->f_numberOfChannels; k++)
                                    x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] += datas[k][i];
                            }
                        }
                    }
                    else
                    {
                        for(long i = 0; i < size; i++)
                        {
                            if(i < abs(offset))
                                x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] = 0.;
                            else
                            {
                                for(int k = 0; k < x->f_numberOfChannels; k++)
                                    x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] += datas[k][i];
                            }
                        }
                    }
                }
            }
			for(int j = 0; j < x->f_numberOfChannels; j++)
				ATOMIC_DECREMENT(&x->f_buffer[j]->b_inuse);

			free(datas);
			outlet_bang(x->f_bang_out);
		}
	}
}