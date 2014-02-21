/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "ext.h"
#include "ext_obex.h"
#include "jgraphics.h"
#include "../hoa.max.h"

#define CONNECT_MAX_TAB 100

typedef struct  _connect
{
	t_object	f_ob;
	
	t_object*	f_patcher;
	t_object*	f_patcherview;
	
	t_object*	f_object[CONNECT_MAX_TAB];
	Hoa3D::Ambisonic* ambi3D;
	
	t_jrgba		f_colorZero;
	t_jrgba		f_colorPositiv;
	t_jrgba		f_colorNegativ;
	t_jrgba		f_colorPlane;
	
	int			f_nbSelected;
} t_connect;

static t_class *connect_class;

void *connect_new(t_symbol *s, long argc, t_atom *argv);
void connect_free(t_connect *x);
void connect_bang(t_connect *x);
void connect_assist(t_connect *x, void *b, long m, long a, char *s);
void connect_attach(t_connect *x);
void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

t_max_err connect_setattr_zerocolor(t_connect *x, void *attr, long argc, t_atom *argv);
t_max_err connect_setattr_poscolor(t_connect *x, void *attr, long argc, t_atom *argv);
t_max_err connect_setattr_negcolor(t_connect *x, void *attr, long argc, t_atom *argv);
t_max_err connect_setattr_planecolor(t_connect *x, void *attr, long argc, t_atom *argv);

int is_box_hoa(t_object *box);
void make_patchline(t_connect *x);
void color_patchline(t_connect *x);
void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.connect3D", (method)connect_new, (method)connect_free, sizeof(t_connect), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
	
	class_addmethod(c, (method)connect_notify,	"notify",	A_CANT, 0);
	class_addmethod(c, (method)connect_bang,	"bang",		A_CANT,	0);
    class_addmethod(c, (method)connect_assist,	"assist",	A_CANT,	0);
	
	CLASS_STICKY_ATTR		(c, "category", 0, "Behavior");
	CLASS_ATTR_RGBA			(c, "zerocolor", 0, t_connect, f_colorZero);
	CLASS_ATTR_ACCESSORS	(c, "zerocolor", NULL, connect_setattr_zerocolor);
	CLASS_ATTR_SAVE			(c, "zerocolor", 1);
	
	CLASS_ATTR_RGBA			(c, "poscolor", 0, t_connect, f_colorPositiv);
	CLASS_ATTR_ACCESSORS	(c, "poscolor", NULL, connect_setattr_poscolor);
	CLASS_ATTR_SAVE			(c, "poscolor", 1);
    CLASS_ATTR_ATTR_PARSE   (c, "poscolor","style",    USESYM(symbol), 0,"rgba");
    
	CLASS_ATTR_RGBA			(c, "negcolor", 0, t_connect, f_colorNegativ);
	CLASS_ATTR_ACCESSORS	(c, "negcolor", NULL, connect_setattr_negcolor);
	CLASS_ATTR_SAVE			(c, "negcolor", 1);
	
	CLASS_ATTR_RGBA			(c, "planecolor", 0, t_connect, f_colorPlane);
	CLASS_ATTR_ACCESSORS	(c, "planecolor", NULL, connect_setattr_planecolor);
	CLASS_ATTR_SAVE			(c, "planecolor", 1);
    
	CLASS_STICKY_ATTR_CLEAR	(c, "category");
	
	class_register(CLASS_BOX, c);
	connect_class = c;
	hoa_print_credit();
	return 0;
}

void *connect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_connect *x = NULL;

	x = (t_connect *)object_alloc((t_class *)connect_class);
	if (x)
	{
		x->ambi3D = new Hoa3D::Ambisonic(100);
		
		// colors setup
		x->f_colorZero.green = x->f_colorPositiv.red = x->f_colorNegativ.blue = 1.;
		x->f_colorPlane.red = x->f_colorPlane.green = x->f_colorPlane.blue = 1.;
		x->f_colorZero.red = x->f_colorZero.green = x->f_colorZero.blue = 0.2;
		x->f_colorZero.alpha = x->f_colorPositiv.alpha = x->f_colorNegativ.alpha = x->f_colorPlane.alpha = 1.;
		
		x->f_nbSelected = 0;
		defer_low(x, (method)connect_attach, NULL, 0, NULL);
	}
	
	return x;
}	

void connect_free(t_connect *x)
{
	if(x->f_patcherview)
		object_detach_byptr(x, x->f_patcherview);
}

void connect_attach(t_connect *x)
{
	object_obex_lookup(x, gensym("#P"), &x->f_patcher);
	x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
}

void connect_assist(t_connect *x, void *b, long m, long a, char *s)
{
    sprintf(s, "(bang) Select objects you want to connect, then bang me to connect them");
}

// custom attr setter to change patchlines colors
t_max_err connect_setattr_zerocolor(t_connect *x, void *attr, long argc, t_atom *argv)
{
	if (argc >= 4 && argv)
	{
		x->f_colorZero.red = atom_getfloat(argv);
		x->f_colorZero.green = atom_getfloat(argv + 1);
		x->f_colorZero.blue = atom_getfloat(argv + 2);
		x->f_colorZero.alpha = atom_getfloat(argv + 3);
	}
	return MAX_ERR_NONE;
}
t_max_err connect_setattr_poscolor(t_connect *x, void *attr, long argc, t_atom *argv)
{
	if (argc >= 4 && argv)
	{
		x->f_colorPositiv.red = atom_getfloat(argv);
		x->f_colorPositiv.green = atom_getfloat(argv + 1);
		x->f_colorPositiv.blue = atom_getfloat(argv + 2);
		x->f_colorPositiv.alpha = atom_getfloat(argv + 3);
	}
	return MAX_ERR_NONE;
}
t_max_err connect_setattr_negcolor(t_connect *x, void *attr, long argc, t_atom *argv)
{
	if (argc >= 4 && argv)
	{
		x->f_colorNegativ.red = atom_getfloat(argv);
		x->f_colorNegativ.green = atom_getfloat(argv + 1);
		x->f_colorNegativ.blue = atom_getfloat(argv + 2);
		x->f_colorNegativ.alpha = atom_getfloat(argv + 3);
	}
	return MAX_ERR_NONE;
}
t_max_err connect_setattr_planecolor(t_connect *x, void *attr, long argc, t_atom *argv)
{
	if (argc >= 4 && argv)
	{
		x->f_colorPlane.red = atom_getfloat(argv);
		x->f_colorPlane.green = atom_getfloat(argv + 1);
		x->f_colorPlane.blue = atom_getfloat(argv + 2);
		x->f_colorPlane.alpha = atom_getfloat(argv + 3);
	}
	return MAX_ERR_NONE;
}

void connect_bang(t_connect *x)
{
	make_patchline(x);
	color_patchline(x);
}

void make_patchline(t_connect *x)
{
	int connexions, valid_objects, i, j;
	valid_objects = 0;
	t_hoa_err err[2];
	t_hoa_boxinfos* startobj_infos;
	t_hoa_boxinfos* endobj_infos;
	
	if (x->f_nbSelected > 1)
	{
		for (i = 0; i < x->f_nbSelected; i++)
		{
			if(is_box_hoa(x->f_object[i]))
				x->f_object[valid_objects++] = x->f_object[i]; // ! store BOX objects
		}
		
		if (valid_objects > 1)
		{
			startobj_infos = (t_hoa_boxinfos*) malloc( sizeof(t_hoa_boxinfos));
			endobj_infos = (t_hoa_boxinfos*) malloc( sizeof(t_hoa_boxinfos));
			
			for(i = 1; i < valid_objects; i++)
			{
				hoa_boxinfos_init(startobj_infos);
				hoa_boxinfos_init(endobj_infos);
				err[0] = (t_hoa_err) object_method(jbox_get_object(x->f_object[i-1]), gensym("hoa_getinfos"), startobj_infos, NULL);
				err[1] = (t_hoa_err) object_method(jbox_get_object(x->f_object[ i ]), gensym("hoa_getinfos"), endobj_infos, NULL);
				
				// if objects are connectables :
				if (err[0] == HOA_ERR_NONE && err[1] == HOA_ERR_NONE)
				{
					// if we try to connect two 2D or 3D object type together :
					if (startobj_infos->object_type == endobj_infos->object_type)
					{
						connexions = MIN(startobj_infos->autoconnect_outputs, endobj_infos->autoconnect_inputs);
						for(j = 0; j < connexions; j++)
							connect_connect(x->f_patcher, x->f_object[i-1], j, x->f_object[i], j);
					}
				}
			}
			
			free(startobj_infos);
			free(endobj_infos);
		}
		
		for(i = 0; i < CONNECT_MAX_TAB; i++)
			x->f_object[i] = NULL;
		
		jpatcher_set_dirty(x->f_patcherview, true);
	}
	x->f_nbSelected = 0;
}

void color_patchline(t_connect *x)
{
	t_object *line, *startobj, *endobj;
	t_hoa_err err[2];
	t_jrgba* linecolor = NULL;
	t_hoa_boxinfos* startobj_infos = (t_hoa_boxinfos*) malloc( sizeof(t_hoa_boxinfos));
	t_hoa_boxinfos* endobj_infos = (t_hoa_boxinfos*) malloc( sizeof(t_hoa_boxinfos));
	line = jpatcher_get_firstline(x->f_patcher);
	
	while (line)
	{
		startobj = jbox_get_object(jpatchline_get_box1(line));
		endobj = jbox_get_object(jpatchline_get_box2(line));
		
		if(object_is_hoa(startobj) && object_is_hoa(endobj))
		{
			hoa_boxinfos_init(startobj_infos);
			hoa_boxinfos_init(endobj_infos);
			err[0] = (t_hoa_err) object_method(startobj, gensym("hoa_getinfos"), startobj_infos, NULL);
			err[1] = (t_hoa_err) object_method(endobj, gensym("hoa_getinfos"), endobj_infos, NULL);
			
			if (err[0] == HOA_ERR_NONE && err[1] == HOA_ERR_NONE)
			{
				// does nothing (ex: hoa.decoder~ => hoa.dac~)
				if (startobj_infos->autoconnect_outputs_type == HOA_CONNECT_TYPE_STANDARD &&
					endobj_infos->autoconnect_inputs_type == HOA_CONNECT_TYPE_STANDARD)
				{
					;
				}
				// ambonics colors (zero | neg | pos) (ex: hoa.encoder~ => hoa.optim~)
				else if (startobj_infos->autoconnect_outputs_type == HOA_CONNECT_TYPE_AMBISONICS &&
						 endobj_infos->autoconnect_inputs_type == HOA_CONNECT_TYPE_AMBISONICS)
				{
					int num = jpatchline_get_inletnum(line);
					if (startobj_infos->object_type == HOA_OBJECT_2D)
					{
						linecolor = (num % 2 == 1) ? &x->f_colorNegativ : &x->f_colorPositiv;
						jpatchline_set_color(line, linecolor);
					}
					else if (startobj_infos->object_type == HOA_OBJECT_3D)
					{
						int sign = x->ambi3D->getHarmonicArgument(num);
						if (num == 0 || sign > 0)
							linecolor = &x->f_colorPositiv;
						else if (sign < 0)
							linecolor = &x->f_colorNegativ;
						else
							linecolor = &x->f_colorZero;
						
						jpatchline_set_color(line, linecolor);
					}
				}
				// planewave color (ex: hoa.projector~ => hoa.recomposer~)
				else if (startobj_infos->autoconnect_outputs_type == HOA_CONNECT_TYPE_PLANEWAVES &&
						 endobj_infos->autoconnect_inputs_type == HOA_CONNECT_TYPE_PLANEWAVES)
				{
					jpatchline_set_color(line, &x->f_colorPlane);
				}
			}
		}
		
		line = jpatchline_get_nextline(line);
	}
	
	free(startobj_infos);
	free(endobj_infos);
}

void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	t_atom msg[4];
	t_atom rv;

	atom_setobj(msg, send);
	atom_setlong(msg + 1, outlet);
	atom_setobj(msg + 2, receive);
	atom_setlong(msg + 3, inlet);

	object_method_typed(x , gensym("connect"), 4, msg, &rv);
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	
	int i, j, k, tabcheck;
	if (msg == gensym("attr_modified") && sender == x->f_patcherview) 
	{
		t_symbol *attrname;
		attrname = (t_symbol *)object_method(data, gensym("getname"));
			
		if (attrname == gensym("selectedboxes")) {
			t_atom *av = NULL;
			long current_nb_selected = 0;
			
			object_attr_getvalueof(sender, attrname, &current_nb_selected, &av);
			if (current_nb_selected && av)
			{				
				// on supprime tous les objets du tableau qui ne sont plus dans la selection
				if(x->f_nbSelected < 0)
					x->f_nbSelected = 0;
				if(current_nb_selected < x->f_nbSelected)
				{
					for(i = 0 ; i < current_nb_selected ; i++)
					{
						tabcheck = 0;
						for(j = 0; j < x->f_nbSelected; j++)
						{
							if (atom_gettype(av+i) == A_OBJ && x->f_object[j] == (t_object*)atom_getobj(av+i)) 
							{	
								tabcheck = 1;
								break;
							}
						}
						
						if (!tabcheck)
							x->f_object[j] = NULL;
					}
				
					// puis on retrie le tableau
					for(i = 0; i < x->f_nbSelected; i++)
					{
						if (x->f_object[i] == NULL)
						{
							for(k = i; k < x->f_nbSelected; k++)
								x->f_object[k] = x->f_object[k+1];
							
							x->f_nbSelected--;
							break;
						}
					}
				}
				else if(current_nb_selected > x->f_nbSelected)
				{
					for(i = 0 ; i < current_nb_selected ; i++)
					{
						tabcheck = 0;
						for(j = 0; j < x->f_nbSelected; j++)
						{
							if (atom_gettype(av+i) == A_OBJ && x->f_object[j] == (t_object*)atom_getobj(av+i)) 
							{	
								tabcheck = 1;
							}
						}
						
						if (!tabcheck)
							x->f_object[x->f_nbSelected] = (t_object*)atom_getobj(av+i);
					}
					x->f_nbSelected++;
				}
				/*
				for(i = 0; i < x->f_nbSelected; i++)
					post("selected %ld : %s", i, jbox_get_maxclass(x->f_object[i])->s_name);
				*/
			}
			freebytes(av, sizeof(t_atom) * current_nb_selected);
		}			
	}


	if (msg == gensym("startdrag"))
	{
		if (jkeyboard_getcurrentmodifiers() != 18) // shift key
		{
			for(i = 0; i < CONNECT_MAX_TAB; i++)
				x->f_object[i] = NULL;
			
			x->f_nbSelected = 0;
		}
	}
	/*
	else if (msg == gensym("enddrag"))
	{
	}
	*/
}

int is_box_hoa(t_object *box)
{
	return object_is_hoa(jbox_get_object(box));
}
