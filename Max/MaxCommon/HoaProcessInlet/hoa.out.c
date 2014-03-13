/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.out~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "../HoaProcess/hoa.process~.h"

typedef struct _hoa_out
{
    t_object x_obj;
	
	t_object *parent_processor;
	long outlet_num;
	long parent_patcher_index;
	long s_index;
} t_hoa_out;

t_class *hoa_out_class;

void *hoa_out_new(t_symbol *s, short argc, t_atom *argv);
void hoa_out_free(t_hoa_out *x);
void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s);

void hoa_out_bang(t_hoa_out *x);
void hoa_out_int(t_hoa_out *x, long n);
void hoa_out_float(t_hoa_out *x, double f);
void hoa_out_list(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv);
void hoa_out_anything(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class* c;
	c = class_new("hoa.out", (method) hoa_out_new, (method)hoa_out_free, sizeof(t_hoa_out), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
    class_addmethod(c, (method)hoa_out_assist,			"assist",			A_CANT,	 0);
	class_addmethod(c, (method)hoa_out_bang,			"bang",						 0);
	class_addmethod(c, (method)hoa_out_int,				"int",				A_LONG,	 0);
	class_addmethod(c, (method)hoa_out_float,			"float",			A_FLOAT, 0);
	class_addmethod(c, (method)hoa_out_list,			"list",				A_GIMME, 0);
	class_addmethod(c, (method)hoa_out_anything,		"anything",			A_GIMME, 0);
    
	class_register(CLASS_BOX, c);
	hoa_out_class = c;
	return 0;
}

void *hoa_out_new(t_symbol *s, short argc, t_atom *argv)
{
    t_hoa_out *x = (t_hoa_out *)object_alloc(hoa_out_class);
	void *hoaprocessor_parent = Get_HoaProcessor_Object();
	
	x->parent_processor = (t_object*)hoaprocessor_parent;
	x->parent_patcher_index = Get_HoaProcessor_Patch_Index(hoaprocessor_parent);
	x->outlet_num = x->parent_patcher_index;
	x->s_index = 1;
    return (x);
}

void hoa_out_assist(t_hoa_out *x, void *b, long m, long a, char *s)
{
    sprintf(s,"Send Messages Out of a hoa.process~ Patcher");
}

void hoa_out_bang(t_hoa_out *x)
{
	t_args_struct args;
	args.msg = gensym("bang");
	args.index = x->parent_patcher_index;
	args.argc = 0;
	args.argv = NULL;
	object_method(x->parent_processor, gensym("out_message"), &args);
}

void hoa_out_int(t_hoa_out *x, long n)
{
	t_args_struct args;
	args.msg = gensym("int");
	args.index = x->parent_patcher_index;
	args.argc = 1;
	args.argv = (t_atom*) malloc(sizeof(t_atom));
	atom_setfloat(args.argv, n);
	object_method(x->parent_processor, gensym("out_message"), &args);
}

void hoa_out_float(t_hoa_out *x, double f)
{
	t_args_struct args;
	args.msg = gensym("float");
	args.index = x->parent_patcher_index;
	args.argc = 1;
	args.argv = (t_atom*) malloc(sizeof(t_atom));
	atom_setfloat(args.argv, f);
	object_method(x->parent_processor, gensym("out_message"), &args);
}

void hoa_out_list(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv)
{
	t_args_struct args;
	args.msg = gensym("list");
	args.index = x->parent_patcher_index;
	args.argc = argc;
	args.argv = argv;
	object_method(x->parent_processor, gensym("out_message"), &args);
}

void hoa_out_anything(t_hoa_out *x, t_symbol *s, short argc, t_atom *argv)
{
	t_args_struct args;
	args.msg = s;
	args.index = x->parent_patcher_index;
	args.argc = argc;
	args.argv = argv;
	object_method(x->parent_processor, gensym("out_message"), &args);
}

void hoa_out_free(t_hoa_out *x)
{
	;
}
