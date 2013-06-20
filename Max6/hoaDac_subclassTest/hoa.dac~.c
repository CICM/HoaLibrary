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


#include "ext.h"

#include "ext_obex.h"
//#include "ext_common.h"
#include "z_dsp.h"

typedef struct _dac
{
	t_pxobject p_ob;
} t_dac;

void *dac_new(t_symbol *s, int argc, t_atom *argv);
void dac_assist(t_dac *x, void *b, long m, long a, char *s);

void *dac_class;

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.dac~", (method)dac_new, (method)dsp_free, (short)sizeof(t_dac), 0L, A_GIMME, 0);
    //c = class_new("hoa.dac~", (method)NULL, (method)NULL, (short)sizeof(t_dac), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)dac_assist,	"assist",	A_CANT, 0);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	dac_class = c;
    
    class_subclass(class_findbyname(CLASS_BOX, gensym("dac~")), c);
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void *dac_new(t_symbol *s, int argc, t_atom *argv)
{
    //t_dac *x = (t_dac *)object_alloc(dac_class);
	int i, j, count;
	t_atom channels[10000];
	int min, max;
	count = 0;
	for(i = 0; i < argc; i++)
	{
		if(atom_gettype(argv+i) == A_SYM)
		{
			min = atoi(atom_getsym(argv+i)->s_name);
			if (min < 10)
				max = atoi(atom_getsym(argv+i)->s_name+2);
			else if (min < 100)
				max = atoi(atom_getsym(argv+i)->s_name+3);
			else if (min < 1000)
				max = atoi(atom_getsym(argv+i)->s_name+4);
			else
				max = atoi(atom_getsym(argv+i)->s_name+5);
			if (max > min) 
			{
				for(j = min; j <= max; j++)
				{
					atom_setlong(channels+count++, j);
				}
			}
			else 
			{
				for(j = min; j >= max; j--)
				{
					atom_setlong(channels+count++, j);
				}
			}

		}	
		else if(atom_gettype(argv+i) == A_LONG)
		{
			channels[count++] = argv[i];
		}
	}
    
    //t_dac *x = (t_dac *)class_super_construct(dac_class, count, channels);
    t_dac *x = (t_dac *)class_super_construct((t_class *)dac_class, argc, argv);
    //t_dac *x = (t_dac *)class_super_construct(dac_class, count, channels);
    
    //object_super_method((t_object *)x, gensym("set"), count, channels);
    
    //object_method(x, gensym("set"), count, channels);
    
    
	//x = (t_object *)object_new_typed(CLASS_BOX, gensym("dac~"), count, channels);
	
	return x;
}

void dac_assist(t_dac *x, void *b, long m, long a, char *s)
{
    //object_super_method(x, gensym("assist"), b, m, a, s);
    /*
	if (m == ASSIST_OUTLET)
		sprintf(s,"input channel %ld", a);
    */
}


