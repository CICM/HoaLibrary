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
	
	long		inlet_num;
	t_symbol*	parent_mode;
	long		parent_patcher_index;
	
	void*		out;
	
} t_hoa_in;

t_class *hoa_in_class;

void *hoa_in_new(t_symbol *s, short argc, t_atom *argv);
void hoa_in_free(t_hoa_in *x);
void hoa_in_assist(t_hoa_in *x, void *b, long m, long a, char *s);

void hoa_in_bang(t_hoa_in *x);
void hoa_in_int(t_hoa_in *x, long n);
void hoa_in_float(t_hoa_in *x, double f);
void hoa_in_list(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv);
void hoa_in_anything(t_hoa_in *x, t_symbol *s, short argc, t_atom *argv);

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
    
	class_register(CLASS_BOX, c);
	hoa_in_class = c;
	return 0;
}

void hoa_in_free(t_hoa_in *x)
{
	;
}

void *hoa_in_new(t_symbol *s, short argc, t_atom *argv)
{
    t_hoa_in *x = (t_hoa_in *)object_alloc(hoa_in_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();

    x->out = outlet_new((t_object *)x, NULL);
	
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->parent_mode = HoaProcessor_Get_Mode(hoaprocessor_parent);
	
	if (x->parent_mode == gensym("post") || x->parent_mode == gensym("out"))
	{
		x->inlet_num = x->parent_patcher_index;
	}
	else if (x->parent_mode == gensym("no"))
	{
		x->inlet_num = 1;
	}
	
    return (x);
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
		sprintf(s,"Input %i", 1);
}