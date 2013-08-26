/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../MaxHoa.h"

int postons = 0;

typedef struct _HoaEncode 
{
	t_pxobject			f_ob;
    t_ambisonic         f_hoa;
	AmbisonicEncoder    *f_ambiEncoder;

} t_HoaEncode;


void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncode_free(t_HoaEncode *x);
void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s);

void HoaEncode_float(t_HoaEncode *x, double f);
void HoaEncode_int(t_HoaEncode *x, long n);

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64_offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err HoaEncode_notify(t_HoaEncode *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

t_class *HoaEncode_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.encoder~", (method)HoaEncode_new, (method)HoaEncode_free, (long)sizeof(t_HoaEncode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaEncode_float,		"float",	A_FLOAT,0);
	class_addmethod(c, (method)HoaEncode_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaEncode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaEncode_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)HoaEncode_notify,    "notify",   A_CANT, 0);    

	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaEncode_class = c;
    
    if(!postons)
    {
        post("hoa.library (version 1.3) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
        postons = 1;
    }

	return 0;
}

void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv)
{
    t_HoaEncode *x = (t_HoaEncode *)object_alloc(HoaEncode_class);
	if (x)
	{		
		ambisonic_new((t_object *)x, &x->f_hoa, argc, argv);
		x->f_ambiEncoder = new AmbisonicEncoder(x->f_hoa.order, Hoa_Basic, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiEncoder->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiEncoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        
		x->f_ob.z_misc = Z_NO_INPLACE;
	}

	return (x);
}

void HoaEncode_float(t_HoaEncode *x, double f)
{
	x->f_ambiEncoder->setAngle(f);
}

void HoaEncode_int(t_HoaEncode *x, long n)
{
	x->f_ambiEncoder->setAngle(n);
}

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiEncoder->setVectorSize(maxvectorsize);
	x->f_ambiEncoder->setSamplingRate(samplerate);
    
    if(count[x->f_ambiEncoder->getNumberOfInputs() - 1])
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64_offset, 0, NULL);
}

void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs, ins[1]);
}

void HoaEncode_perform64_offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs);
}

void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
        if(a == 0)
            sprintf(s,"(Signal) Input");
        else
            sprintf(s,"(Signal or float) Angle");
	} 
	else 
	{
		sprintf(s,"(Signal) %s", x->f_ambiEncoder->getHarmonicsName(a).c_str());
	}
}

t_max_err HoaEncode_notify(t_HoaEncode *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if(msg == gensym("attr_modified"))
	{
		t_symbol* attr_name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
        if(attr_name == gensym("order"))
        {
            if(object_attr_getlong(x, gensym("order")) != x->f_ambiEncoder->getOrder())
            {
                t_atom* state = CicmMax::dsp_stop((t_object *)x);
                delete(x->f_ambiEncoder);
                x->f_ambiEncoder = new AmbisonicEncoder(object_attr_getlong(x, gensym("order")), Hoa_Basic, sys_getblksize());
                
                                if(atom_gettype(x->f_hoa.argv) == A_LONG || atom_gettype(x->f_hoa.argv) == A_FLOAT)
                    atom_setlong(x->f_hoa.argv, (long)x->f_ambiEncoder->getOrder());
                
                CicmMax::resize_outlet((t_object *)x, x->f_ambiEncoder->getNumberOfOutputs());
                ambisonic_rename_object((t_object *)x, x->f_hoa.argc, x->f_hoa.argv);
                if(object_attr_getlong(x, gensym("autoconnect")))
                {
                    ambisonic_connect_outlet((t_object *)x);
                    ambisonic_color_outlet((t_object *)x);
                }
                
                object_attr_setlong(x, gensym("order"), x->f_ambiEncoder->getOrder());
                CicmMax::dsp_start(state);
            }
        }
        else if(attr_name == gensym("poscolor") || attr_name == gensym("negcolor"))
        {
            ambisonic_color_outlet((t_object *)x);
        }        
    }
    ambisonic_notify((t_object *)x, &x->f_hoa, msg, sender, data);

    return MAX_ERR_NONE;
}

void HoaEncode_free(t_HoaEncode *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiEncoder);
    ambisonic_free((t_object *)x, &x->f_hoa);
}

