
/*
* Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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
* guillotpierre6@gmail.com
*/

#include "hoa.delay~.h"

int main(void)
{
	delayObj_classinit();
	delay_ui_classinit();
	
	return 0;
}

void delayObj_classinit(void)
{
	t_class *c;

	c = class_new("hoa.delay~", (method)delayObj_new, (method)delayObj_free, (short)sizeof(t_delayObj), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)delayObj_dsp64,			"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)delayObj_dsp,			"dsp",			A_CANT,	0);
	
	class_addmethod(c, (method)delayObj_dblclick,		"dblclick",		A_CANT, 0);
	class_addmethod(c, (method)delayObj_assist,			"assist",		A_CANT,	0);
	class_addmethod(c, (method)delayObj_notify,			"notify",		A_CANT,	0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	delayObj_class = c;

	post("hoa.delay~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *delayObj_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	t_delayObj *x = NULL;
	
	if (x = (t_delayObj *)object_alloc((t_class *)delayObj_class)) 
	{
		x->f_sr = sys_getsr();
		x->f_order = 1;
		
		if(atom_gettype(argv) == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1)
			x->f_order = 1;
		
		x->f_harmonics = 2 * x->f_order + 1;
		
		
		delay_setup(&x->f_delay, 10000., x->f_sr);

		dsp_setup((t_pxobject *)x, 1);
		for(i = 0; i < x->f_harmonics; i++)
			outlet_new((t_pxobject *)x, "signal");
		
		x->f_oncolor.red = 1.;
		x->f_oncolor.green = 1.;
		x->f_oncolor.blue = 1.;
		x->f_oncolor.alpha = 1.;
		
		x->f_oncolor.red = 0.;
		x->f_oncolor.green = 0.;
		x->f_oncolor.blue = 0.;
		x->f_oncolor.alpha = 1.;
		
		attr_args_process(x, argc, argv);
	}
	
	return x;
}			

void delayObj_dsp64(t_delayObj *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_sr = samplerate;
	delay_resize(&x->f_delay, x->f_sr);
	object_method(dsp64, gensym("dsp_add64"), x, delayObj_perform64, 0, NULL);
}

void delayObj_perform64(t_delayObj *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	for(i = 0; i < sampleframes; i++)
	{ 
		delay_write(&x->f_delay, ins[0][i]);
		outs[0][i] = delay_read_ms_quadra(&x->f_delay, ins[1][i]);		
	}
}

void delayObj_free(t_delayObj *x)
{
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);
	if (x->f_patcher)
		object_free(x->f_patcher);

}

void delayObj_assist(t_delayObj *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		if(a == 0)
			sprintf(s,"(Signal) Input");
		else
			sprintf(s,"(Int, Float or Signal) Transposition %i", (int)a);
	}
	else 
	{
		sprintf(s,"(Signal) Delayed signal %i", (int)a);
	}
}

void delayObj_dsp(t_delayObj *x, t_signal **sp, short *count)
{
	x->f_sr = (double)sp[0]->s_sr;
	delay_resize(&x->f_delay, x->f_sr);

	dsp_add(delayObj_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *delayObj_perform(t_int *w)
{/*
	int i, index, indexTwo;

	t_delay *x		= (t_delay *)(w[1]);
    float		 *in	= (float *)(w[2]);
	float		*out	= (float *)(w[3]);
	int n				= (int)w[4];

	double sigDelayOne, sigDelayTwo, ratio;
	double delayOne, delayTwo;
	double windoOne, windoTwo;

	if(x->f_ob.z_disabled) return w + 5;

	for(i = 0; i < n; i++)
	{
		delay_write(&x->f_delay, (double)in[i]);

		index = x->f_inc;
		indexTwo = x->f_inc + WINSIZE / 2;
		if(indexTwo >= WINSIZE)
			indexTwo -= WINSIZE;
		ratio = x->f_inc - index;

		delayOne = (x->f_delayVec[index + 1] * ratio +  x->f_delayVec[index] * (1. - ratio)) * x->f_value * 2.;
		delayTwo = (x->f_delayVec[indexTwo + 1] * ratio +  x->f_delayVec[indexTwo] * (1. - ratio)) * x->f_value * 2.;

		sigDelayOne = delay_read_ms(&x->f_delay, delayOne);
		sigDelayTwo = delay_read_ms(&x->f_delay, delayTwo);

		windoOne = (x->f_window[index + 1] * ratio +  x->f_window[index] * (1. - ratio));
		windoTwo =	(x->f_window[indexTwo + 1] * ratio +  x->f_window[indexTwo] * (1. - ratio));
		sigDelayOne *= windoOne;
		sigDelayTwo *= windoTwo;
		out[i] = (float)(sigDelayOne + sigDelayTwo);

		x->f_inc += x->f_grain;
		if(x->f_inc >= WINSIZE)
			x->f_inc = 0;
	}
	*/
	return w + 5;
}

void delayObj_dblclick(t_delayObj *x)
{
	if (x->f_patcher) 
		object_method(x->f_patcher, gensym("vis"));
	else 
	{
		t_dictionary *d = dictionary_new();
		char	parsebuf[256];
		t_atom	a;
		long	ac = 0;
		t_atom	*av = NULL;
		long	size;
		t_atom msg[4], rv;
		size = x->f_harmonics * 70;
		
		sprintf(parsebuf,"@defrect 0 0 %ld 200 @title hoa.delay~ @enablehscroll 0 @enablevscroll 0 @presentation 1 @toolbarid \"\"", size);
		atom_setparse(&ac,&av,parsebuf);
		attr_args_dictionary(d,ac,av);
		atom_setobj(&a,d);
		sysmem_freeptr(av); 
		x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
		freeobject((t_object *)d);
		
		object_method(x->f_patcher,gensym("vis"));
		/*
		x->f_ui = newobject_sprintf(x->f_patcher, "@maxclass delay_ui @patching_rect 0 0 %ld 200 @oncolor %.2f %.2f %.2f %.2f @offcolor %.2f %.2f %.2f %.2f",
									size, x->f_oncolor.red, x->f_oncolor.green, x->f_oncolor.blue, x->f_oncolor.alpha, x->f_offcolor.red, x->f_offcolor.green, x->f_offcolor.blue, x->f_offcolor.alpha);
		
		*/
		x->f_ui = newobject_sprintf(x->f_patcher, "@maxclass flonum @patching_rect 10 10 50 20 @presentation 1");
		
		/*
		atom_setobj(msg, x->f_ui); 
		atom_setlong(msg + 1, 0); 
		atom_setobj(msg + 2, x); 
		atom_setlong(msg + 3, 0);
		object_method_typed(x->f_patcher, gensym("connect"), 4, msg, &rv);
		*/
		object_attach_byptr_register(x, x->f_ui, CLASS_BOX);
		object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
	}
}

t_max_err delayObj_notify(t_delayObj *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *attrname;
	
	if (msg == gensym("attr_modified")) 
	{	
		attrname = (t_symbol *)object_method((t_object *)data, gensym("getname"));	
		object_post((t_object *)x, "changed attr name is %s",attrname->s_name);
	}
		
	//post("notify object %s", s->s_name );
	//post("notify message %s", msg->s_name);
		
	if (msg == gensym("free")) 
	{
		if (sender == x->f_patcher)
			x->f_patcher = NULL;
	} 
	else if (msg == gensym("cellclicked")) 
	{
		if (sender == x->f_ui) {
			t_atom argv[3];
			t_celldesc *desc;
			desc = (t_celldesc *)data;
			/*
			atom_setlong(argv, desc->row);
			atom_setlong(argv + 1, desc->col);
			atom_setlong(argv + 2, desc->state);
			outlet_list(x->f_out, NULL, 3, argv);
			 */
		}
	}
	return 0;
}

