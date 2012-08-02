/*
* Copyright (C) 2012 Pierre Guillot & Julien Colafransceco, Universite Paris 8
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

#include "hoa.plug~.h"

int main(void)
{
	t_class *c;

	c = class_new("hoa.plug~", (method)plug_new, (method)plug_free, (short)sizeof(t_plug), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)plug_anything,		"anything",		A_GIMME, 0);
	class_addmethod(c, (method)plug_list,			"list",			A_GIMME, 0);
	class_addmethod(c, (method)plug_int,			"int",			A_LONG, 0);
	class_addmethod(c, (method)plug_float,			"float",		A_FLOAT, 0);
	class_addmethod(c, (method)plug_bang,			"bang",			A_CANT,	0);
	
	class_addmethod(c, (method)plug_dsp64,			"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)plug_dsp,			"dsp",			A_CANT,	0);
	
	class_addmethod(c, (method)plug_assist,			"assist",		A_CANT,	0);
	class_addmethod(c, (method)plug_dblclick,		"dblclick",		A_CANT, 0);
	class_addmethod(c, (method)plug_notify,			"notify",		A_CANT, 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	plug_class = c;

	post("hoa.plug~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *plug_new(t_symbol *s, int argc, t_atom *argv)
{
	t_plug *x = NULL;
	t_symbol *name = NULL;
	
	if (x = (t_plug *)object_alloc((t_class *)plug_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1)
			x->f_order = 1;
		
		x->f_harmonics = 2 * x->f_order + 1;
		
		if(atom_gettype(argv+1) == A_SYM)
			name = atom_getsym(argv+1);
		post_containers(x);
		plug_patchers(x, name);
		
		outlet_new((t_pxobject *)x, "signal");
		dsp_setup((t_pxobject *)x, 1);
		attr_args_process(x, argc, argv);
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	
	return x;
}			

void plug_free(t_plug *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_patchers[i], gensym("free"));
	
	freebytes(x->f_patchers, x->f_harmonics * sizeof(t_patcher *));
	freebytes(x->f_ins, x->f_harmonics * sizeof(t_object *));
	freebytes(x->f_instilde, x->f_harmonics * sizeof(t_object *));
}

void plug_assist(t_plug *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"Dummy");
	}
	else 
	{
		sprintf(s,"(Signal) Output signal");
	}
}

void plug_dblclick(t_plug *x)
{	
	if(x->f_patchers[0])
	{
		object_method(x->f_patchers[0], gensym("vis"));
	}
}

void post_containers(t_plug *x)
{
	t_max_err err;
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&x->f_mypatcher);
}

void plug_patchers(t_plug *x, t_symbol *s)
{
	// Un patcher a 181 methods arfff //
	int i;
	t_class *patcherclass;
	t_messlist *methodlist;
	
	whosyourdaddy_bang(x);
	
	x->f_methods = (t_method_object **)getbytes(x->f_harmonics * sizeof(t_method_object *));
	patcherclass = class_findbyname(CLASS_NOBOX, gensym("jpatcher"));
	x->f_methods[0] = class_getmethod_object(patcherclass, gensym("free"));
	methodlist = method_object_getmesslist(x->f_methods[0]);
	//post("methode name: %s", method_object_getname(x->f_methods[0]));
	//post("methode name: %s", methodlist->m_sym[0]);
	
	//char name[512];
	x->f_patchers = (t_patcher **)getbytes(x->f_harmonics * sizeof(t_patcher *));
	x->f_ins = (t_object **)getbytes(x->f_harmonics * sizeof(t_object *));
	x->f_instilde = (t_object **)getbytes(x->f_harmonics * sizeof(t_object *));
	x->f_outstilde = (t_object **)getbytes(x->f_harmonics * sizeof(t_object *));

	for(i = 0; i < x->f_harmonics; i++)
	{
		x->f_patchers[i] = (t_patcher *)object_new(gensym("jpatcher"),  CLASS_NOBOX);
		//x->f_patchers[i] = (t_patcher *)newinstance(gensym("volume~"), 0, NULL);
		object_attach_byptr_register(x, x->f_patchers[i], CLASS_NOBOX);
		//object_attach_byptr_register(x->f_mypatcher, x->f_patchers[i], CLASS_NOBOX);
		object_obex_storeflags(x->f_patchers[i], gensym("#P"), (t_object *)x, OBJ_FLAG_REF);
		plug_getinput(x, x->f_patchers[i], i);
		
		object_method(x->f_patchers[i],  gensym("settitle"), gensym("volume"));
	}
	
	for(i = 0; i < 181; i++)
	{
		//post("methodes name: %s", x->f_patchers[0]->o_messlist[i].m_sym[0]);
		//post("methodes name2: %s", x->f_patchers[0]->o_messlist[i].m_sym[1]);

		//post("methodes name3: %s", x->f_patchers[0]->o_messlist[i].m_sym[2]);
	}
}

t_max_err plug_notify(t_plug *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	
	if (msg == gensym("free")) 
	{
		if (sender == x->f_patchers[0])
			x->f_patchers[0] = NULL;
	} 
	return 0;
}

void plug_getinput(t_plug *x, t_object *patcher, int index)
{
	t_object *box, *obj;
	
	for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) 
	{		
		obj = jbox_get_object(box);
		
		if(object_classname(obj) == gensym("hoa.in"))
			x->f_ins[index] = obj;
		else if(object_classname(obj) == gensym("hoa.in~"))
			x->f_instilde[index] = obj;
		else if(object_classname(obj) == gensym("hoa.out~"))
			x->f_outstilde[index] = obj;
	}
}


void plug_bang(t_plug *x)
{
	int i;
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_ins[i],  gensym("bang"));
}

void plug_int(t_plug *x, long n)
{
	int i;
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_ins[i],  gensym("int"), n);
}

void plug_float(t_plug *x, double f)
{
	int i;
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_ins[i],  gensym("float"), f);
}

void plug_list(t_plug *x, t_symbol *s, long argc, t_atom *argv)
{
	int i;
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_ins[i],  gensym("list"), s, argc, argv);
}

void plug_anything(t_plug *x, t_symbol *s, long argc, t_atom *argv)
{
	int i;
	for(i = 0; i < x->f_harmonics; i++)
		object_method(x->f_ins[i],  gensym("anything"), s, argc, argv);
}

void plug_dsp(t_plug *x, t_signal **sp, short *count)
{
	t_dspchain *mydspChain;
	t_in *cibleIn = (t_in *)x->f_instilde[0];
	t_in *cibleOut = (t_in *)x->f_outstilde[0];
	x->f_vectorIn = (t_sample *)getbytes(sp[0]->s_n * sizeof(t_sample *));
	x->f_vectorOut = (t_sample *)getbytes(sp[0]->s_n * sizeof(t_sample *));
	cibleIn->f_vector = sp[0]->s_vec;
	cibleOut->f_vector = sp[1]->s_vec;
	
	//mydspChain = (t_dspchain *)object_method(x->f_patchers[0], gensym("setdspchain"));
	
	//mydspChain = (t_dspchain *)object_method(x->f_patchers[0], gensym("getdspchain"));
	//post("sb : %ld", (long)mydspChain->c_bs);
	//post("chain size : %ld", (long)mydspChain->c_chainsize);
	//typedmess(x->f_instilde[0], gensym("dsp"), sp, count);
	//getfn(x->f_instilde[0], gensym("dsp"));
	//object_method(x->f_instilde[0], gensym("dsp"), sp, count);
	//dsp_add(plug_perform, 4, x, sp[0]->s_vec, cibleIn->f_vector, sp[0]->s_n);
	//cibleOut->f_vector = sp[1]->s_vec;
	//object_method(x->f_outstilde[0], gensym("dsp"), sp, count);
		
}

t_int *plug_perform(t_int *w)
{
	t_plug	 *x = (t_plug *)(w[1]);
	t_sample *in = (t_sample *)(w[2]);
	t_sample *out = (t_sample *)(w[3]);
    int sampleframes = (int)(w[4]);
	int i;
	
	for(i = 0; i < sampleframes; i++)
	{ 
		x->f_vectorIn[i] = in[i];
		out[i] = x->f_vectorOut[i];
	}
	
	return w + 5;
}

void plug_dsp64(t_plug *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	
	t_in *cibleIn = (t_in *)x->f_instilde[0];
	t_in *cibleOut = (t_in *)x->f_outstilde[0];
	x->f_vectorIn = (t_sample *)getbytes(maxvectorsize * sizeof(t_sample *));
	x->f_vectorOut = (t_sample *)getbytes(maxvectorsize * sizeof(t_sample *));
	cibleIn->f_vector = x->f_vectorIn;
	cibleOut->f_vector = x->f_vectorOut;
	
	//object_getmethod(x->f_instilde[0], gensym("dsp"));
	//object_method(dsp64, gensym("dsp_add64"), x, plug_perform64, 0, NULL);
}

void plug_perform64(t_plug *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	for(i = 0; i < sampleframes; i++)
	{ 
		x->f_vectorIn[i] = ins[0][i];	
		outs[0][i] = x->f_vectorOut[i];
	}
}

void whosyourdaddy_bang(t_plug *x)
{
	t_object *jp;
	t_object *jbx;
	t_object *o;
	t_max_err err;
	
	// get the object's parent patcher
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;
	else {
		post("daddy");
	}

	
	// some kind of patcher in a box
	if (jbx = jpatcher_get_box(jp)) 
	{
		t_symbol *filepath = object_attr_getsym((t_object *)jp, gensym("filepath"));
		
		//		post("object_classname(jbx): %s, object_classname(o): %s, filepath: %s", object_classname(jbx)->s_name, object_classname(jbox_get_object(jbx))->s_name, filepath->s_name);
		if (object_classname(jbx) == gensym("bpatcher")) 
		{
			post("bpatcher");
		}
		else 
		{
			if (filepath && filepath != gensym("")) 
			{
				post("abstraction");
			} 
			else 
			{
				post("subpatcher");
			}
		}
	} 
	else 
	{
		t_object *p2;
		t_object *target;
		t_object *nextbox;
		method m;
		
		object_method(jp, gensym("getassoc"), &target);
		if (target) 
		{
			if (m = zgetfn(target, gensym("parentpatcher")))
				(*m)(target, &p2);
			if (p2) 
			{
				nextbox = jpatcher_get_firstobject(p2);
				while (nextbox) 
				{
					o = jbox_get_object(nextbox);
					if (o == target) 
					{
						post("%s", object_classname(o)->s_name);
						return;
					}
					nextbox = jbox_get_nextobject(nextbox);
				}
			}
		}
	}
}