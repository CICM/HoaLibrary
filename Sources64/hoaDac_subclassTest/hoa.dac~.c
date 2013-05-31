/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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


