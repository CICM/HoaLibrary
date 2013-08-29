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
 *  - Redistributions in binary form must reproduce the above copyright notice,
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

#include "MaxRotate.h"

typedef struct _HoaRotate 
{
	t_pxobject          f_ob;
	AmbisonicRotate*    f_ambi_rotate;
    MaxRotate*          f_ambi_max;
    
} t_hoa_rotate;

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv);
void hoa_rotate_free(t_hoa_rotate *x);
void hoa_rotate_assist(t_hoa_rotate *x, void *b, long m, long a, char *s);
void hoa_rotate_float(t_hoa_rotate *x, double f);
void hoa_rotate_int(t_hoa_rotate *x, long n);
void hoa_rotate_attach(t_hoa_rotate *x);
void hoa_rotate_connect(t_hoa_rotate *x, t_symbol *s, long argc, t_atom* argv);
t_max_err hoa_rotate_notify(t_hoa_rotate *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void hoa_rotate_dsp64(t_hoa_rotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_rotate_perform64(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64Offset(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* hoa_rotate_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.rotate~", (method)hoa_rotate_new, (method)hoa_rotate_free, (long)sizeof(t_hoa_rotate), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_rotate_float,	"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_rotate_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_rotate_dsp64,	"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_rotate_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)hoa_rotate_notify,   "notify",   A_CANT, 0);
    class_addmethod(c, (method)hoa_rotate_connect,  "connect",  A_GIMME, 0);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_rotate_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_rotate *x = (t_hoa_rotate *)object_alloc(hoa_rotate_class);
    
	if (x)
	{
		x->f_ambi_max   = new MaxRotate((t_hoa_object *)x, argc, argv);
		x->f_ambi_rotate = new AmbisonicRotate(atom_getfloat(argv), sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambi_rotate->getNumberOfInputs());
		for (int i = 0; i < x->f_ambi_rotate->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
        defer_low(x, (method)hoa_rotate_attach, NULL, NULL, NULL);
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        t_dictionary* d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void hoa_rotate_attach(t_hoa_rotate *x)
{
	x->f_ambi_max->attach_to_notification();
}

void hoa_rotate_float(t_hoa_rotate *x, double f)
{
	x->f_ambi_rotate->setAzimuth(f);
}

void hoa_rotate_int(t_hoa_rotate *x, long n)
{
	x->f_ambi_rotate->setAzimuth(n);
}

void hoa_rotate_dsp64(t_hoa_rotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_rotate->setVectorSize(maxvectorsize);
	if(count[x->f_ambi_rotate->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64Offset, 0, NULL);
}

void hoa_rotate_perform64(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambi_rotate->process(ins, outs, ins[x->f_ambi_rotate->getNumberOfInputs() - 1]);
}

void hoa_rotate_perform64Offset(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambi_rotate->process(ins, outs);
}
								  
void hoa_rotate_assist(t_hoa_rotate *x, void *b, long m, long a, char *s)
{
	if (a != x->f_ambi_rotate->getNumberOfInputs()-1 )
		sprintf(s,"(Signal) %s", x->f_ambi_rotate->getHarmonicsName(a).c_str());
	else
		sprintf(s,"(Signal or float) Azimuth"); 	
}

void hoa_rotate_connect(t_hoa_rotate *x, t_symbol *s, long argc, t_atom* argv)
{
    if(!argc)
    {
        x->f_ambi_max->connect_outlets();
        x->f_ambi_max->color_outlets();
        x->f_ambi_max->connect_inlets();
        x->f_ambi_max->color_inlets();
    }
    else if(argc == 2 && atom_gettype(argv) == A_OBJ)
    {
        if(atom_getsym(argv+1) == gensym("outlet"))
        {
            x->f_ambi_max->connect_outlets_with_line((t_object *)atom_getobj(argv));
            x->f_ambi_max->color_outlets();
        }
        else if(atom_getsym(argv+1) == gensym("inlet"))
        {
            x->f_ambi_max->connect_inlets_with_line((t_object *)atom_getobj(argv));
            x->f_ambi_max->color_inlets();
        }
        
    }
}

t_max_err hoa_rotate_notify(t_hoa_rotate *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    return x->f_ambi_max->notify(s, msg, sender, data);
}

void hoa_rotate_free(t_hoa_rotate *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambi_rotate;
    delete x->f_ambi_max;
}

