/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "../HoaCommon.max.h"
#include "../HoaProcess/hoa.process~.h"

typedef struct _hoa_in
{
    t_object	x_obj;
	long		inlet_num;  // ! must be the second item of the struct
	t_symbol*	parent_mode;
	long		parent_patcher_index;
	void*		out;
	t_symbol*	comment;
	long		extra;
	
} t_hoa_in;

t_class *hoa_in_class;

void *hoa_in_new(t_symbol *s, short ac, t_atom *av);
void hoa_in_free(t_hoa_in *x);
void hoa_in_assist(t_hoa_in *x, void *b, long m, long a, char *s);

void hoa_in_bang(t_hoa_in *x);
void hoa_in_int(t_hoa_in *x, long n);
void hoa_in_float(t_hoa_in *x, double f);
void hoa_in_list(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv);
void hoa_in_anything(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv);

t_max_err hoa_in_setattr_extra(t_hoa_in *x, void *attr, long ac, t_atom *av);
t_max_err hoa_in_setattr_comment(t_hoa_in *x, void *attr, long ac, t_atom *av);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.in", (method)hoa_in_new, (method)hoa_in_free, sizeof(t_hoa_in), NULL, A_GIMME, 0);
    
	hoa_initclass(c, (method)NULL);
	
    class_addmethod(c, (method)hoa_in_assist,		"assist",			A_CANT, 0);
	class_addmethod(c, (method)hoa_in_bang,			"bang",				A_CANT, 0);
	class_addmethod(c, (method)hoa_in_int,			"int",				A_CANT, 0);
	class_addmethod(c, (method)hoa_in_float,		"float",			A_CANT, 0);
	class_addmethod(c, (method)hoa_in_list,			"list",				A_CANT, 0);
	class_addmethod(c, (method)hoa_in_anything,		"anything",			A_CANT, 0);
	
	CLASS_ATTR_LONG		(c, "extra", 0, t_hoa_in, extra);
	CLASS_ATTR_ACCESSORS(c, "extra", 0, hoa_in_setattr_extra);
	CLASS_ATTR_LABEL	(c, "extra", 0, "extra index");
	CLASS_ATTR_INVISIBLE(c, "extra", 1);
	CLASS_ATTR_SAVE		(c, "extra", 0);
	
	CLASS_ATTR_SYM		(c, "comment", 0, t_hoa_in, comment);
	CLASS_ATTR_ACCESSORS(c, "comment", 0, hoa_in_setattr_comment);
	CLASS_ATTR_LABEL	(c, "comment", 0, "Description");
	CLASS_ATTR_SAVE		(c, "comment", 1);
    
	class_register(CLASS_BOX, c);
	hoa_in_class = c;
	return 0;
}

void hoa_in_free(t_hoa_in *x)
{
	;
}

void *hoa_in_new(t_symbol *s, short ac, t_atom *av)
{
    t_hoa_in *x = (t_hoa_in *)object_alloc(hoa_in_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();

    x->out = outlet_new((t_object *)x, NULL);
	
	x->inlet_num = 1;
	
	x->extra = 0;
	x->comment = gensym("");
	
	attr_args_process(x, ac, av);
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->parent_mode = HoaProcessor_Get_Mode(hoaprocessor_parent);
	
	long in = HoaProcessor_Get_IO_Index(hoaprocessor_parent, x->parent_patcher_index, (t_object*)x);
		
	if (in > 0)
		x->inlet_num = in;
	
    return (x);
}

t_max_err hoa_in_setattr_extra(t_hoa_in *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_LONG)
	{
		x->extra = atom_getlong(av);
		if (x->extra < 0) x->extra = 0;
	}
	return MAX_ERR_NONE;
}

t_max_err hoa_in_setattr_comment(t_hoa_in *x, void *attr, long ac, t_atom *av)
{
	if (ac && av && atom_gettype(av) == A_SYM)
	{
		x->comment = atom_getsym(av);
	}
	return MAX_ERR_NONE;
}

void hoa_in_bang(t_hoa_in *x)
{
	outlet_bang(x->out);
}

void hoa_in_int(t_hoa_in *x, long n)
{
	outlet_int(x->out, n);
}

void hoa_in_float(t_hoa_in *x, double f)
{
	outlet_float(x->out, f);
}

void hoa_in_list(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv)
{
	outlet_list(x->out, s, argc, argv);
}

void hoa_in_anything(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv)
{
	outlet_anything(x->out, s, argc, argv);
}

void hoa_in_assist(t_hoa_in *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET)
		sprintf(s,"Dummy");
    else
	{
		if (x->extra > 0)
		{
			if (x->comment != hoa_sym_nothing)
				sprintf(s,"(messages) hoa.process~ extra input, %s", x->comment->s_name);
			else
				sprintf(s,"(messages) hoa.process~ extra input");
		}
		else
		{
			sprintf(s,"(messages) hoa.process~ instance input");
		}
	}
}