/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"

#include "../hoa.max.h"

typedef struct _hoa_dac
{
	t_pxobject			f_ob;
    t_object*			f_dac;
	int					f_number_of_channels;
} t_hoa_dac;

t_class *hoa_dac_class;

void *hoa_dac_new(t_symbol *s, int argc, t_atom *argv);
void hoa_dac_assist(t_hoa_dac *x, void *b, long m, long a, char *s);
void hoa_dac_dsp64(t_hoa_dac *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_dac_int(t_hoa_dac *x, long l);
void hoa_dac_list(t_hoa_dac *x, t_symbol *s, long argc, t_atom *argv);
void hoa_dac_set(t_hoa_dac *x, t_symbol *s, long argc, t_atom *argv);
void hoa_dac_anything(t_hoa_dac *x, t_symbol *s, long argc, t_atom *argv);
void hoa_dac_dblclick(t_hoa_dac *x);

void hoa_dac_start(t_hoa_dac *x);
void hoa_dac_stop(t_hoa_dac *x);
void hoa_dac_startwindow(t_hoa_dac *x);
void hoa_dac_open(t_hoa_dac *x);
void hoa_dac_wclose(t_hoa_dac *x);

t_hoa_err hoa_getinfos(t_hoa_dac* x, t_hoa_boxinfos* boxinfos);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.dac~", (method)hoa_dac_new, (method)NULL, (short)sizeof(t_hoa_dac), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_dac_dsp64,		"dsp64",		A_CANT,  0);
	class_addmethod(c, (method)hoa_dac_assist,		"assist",		A_CANT,	 0);
	class_addmethod(c, (method)hoa_dac_dblclick,	"dblclick",		A_CANT,  0);
	class_addmethod(c, (method)hoa_dac_int,			"int",			A_LONG,  0);
	class_addmethod(c, (method)hoa_dac_list,		"list",			A_GIMME, 0);
	class_addmethod(c, (method)hoa_dac_set,			"set",			A_GIMME, 0);
    
	class_addmethod(c, (method)hoa_dac_start,		"start",		A_NOTHING,  0);
	class_addmethod(c, (method)hoa_dac_stop,		"stop",			A_NOTHING,  0);
	class_addmethod(c, (method)hoa_dac_startwindow,	"startwindow",	A_NOTHING,  0);
	class_addmethod(c, (method)hoa_dac_open,		"open",			A_NOTHING,  0);
	class_addmethod(c, (method)hoa_dac_wclose,		"wclose",		A_NOTHING,  0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_dac_class = c;
	return 0;
}

void *hoa_dac_new(t_symbol *s, int argc, t_atom *argv)
{
	int i, j, count = 0;
	t_hoa_dac *x;
	t_atom channels[512];
	int min, max;
    int symPrepend = 0;

    x = (t_hoa_dac *)object_alloc(hoa_dac_class);
    
    if (argc && atom_gettype(argv) == A_SYM)
    {
        char *dac_bus_name = atom_getsym(argv)->s_name;
        if (isalpha(dac_bus_name[0])) // only works if the first letter isn't a number
        {
            symPrepend = 1;
            atom_setsym(channels, atom_getsym(argv));
        }
    }
    
	for(i = 0; i < (argc-symPrepend); i++)
	{
		if(atom_gettype(argv+i+symPrepend) == A_SYM)
		{
			min = atoi(atom_getsym(argv+i+symPrepend)->s_name);
			if (min < 10)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+2);
			else if (min < 100)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+3);
			else if (min < 1000)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+4);
			else
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+5);
			if (max > min) 
			{
				for(j = min; j <= max; j++)
				{
					atom_setlong(channels + symPrepend + count++, j);
				}
			}
			else 
			{
				for(j = min; j >= max; j--)
				{
					atom_setlong(channels + symPrepend + count++, j);
				}
			}
		}	
		else if(atom_gettype(argv + symPrepend + i) == A_LONG)
		{
            atom_setlong(channels + symPrepend + count++, atom_getlong(argv + symPrepend + i));
		}
	}
	x->f_number_of_channels = count;
    dsp_setup((t_pxobject *)x, x->f_number_of_channels);
	x->f_dac = (t_object *)object_new_typed(CLASS_BOX, gensym("dac~"), count + symPrepend, channels);
	
	return x;
}

t_hoa_err hoa_getinfos(t_hoa_dac* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = x->f_number_of_channels;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_dac_dsp64(t_hoa_dac *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method((t_object *)x->f_dac, gensym("dsp64"), dsp64, count, samplerate, maxvectorsize, flags);
}

void hoa_dac_start(t_hoa_dac *x)
{
	object_method(x->f_dac, gensym("start"), NULL, NULL);
}
void hoa_dac_stop(t_hoa_dac *x)
{
	object_method(x->f_dac, gensym("stop"), NULL, NULL);
}
void hoa_dac_startwindow(t_hoa_dac *x)
{
	object_method(x->f_dac, gensym("startwindow"), NULL, NULL);
}
void hoa_dac_open(t_hoa_dac *x)
{
	object_method(x->f_dac, gensym("open"), NULL, NULL);
}
void hoa_dac_wclose(t_hoa_dac *x)
{
	object_method(x->f_dac, gensym("wclose"), NULL, NULL);
}

void hoa_dac_int(t_hoa_dac *x, long l)
{
	object_method(x->f_dac, l == 1 ? gensym("start") : gensym("stop"), NULL, NULL);
}

void hoa_dac_list(t_hoa_dac *x, t_symbol *s, long argc, t_atom *argv)
{
	object_method_typed(x->f_dac, gensym("list"), argc, argv, NULL);
}

void hoa_dac_set(t_hoa_dac *x, t_symbol *s, long argc, t_atom *argv)
{
	object_method_typed(x->f_dac, gensym("set"), argc, argv, NULL);
}

void hoa_dac_assist(t_hoa_dac *x, void *b, long m, long a, char *s)
{
	object_method(x->f_dac, gensym("assist"), b, m, a, s);
}

void hoa_dac_dblclick(t_hoa_dac *x)
{
    object_method(x->f_dac, gensym("dblclick"), 0, NULL);
}


