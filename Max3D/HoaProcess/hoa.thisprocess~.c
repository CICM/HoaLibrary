/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamic.this~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"
#include "hoa.process~.h"

typedef struct _hoa_thisprocess
{
    t_object x_obj;
	
	// outlets
	void *out_index, *out_harmonicBand, *out_harmonicArgument, *out_order, *out_mode, *out_mute, *out_patcherArgs, *out_patcherAttr;
	
	long index;
	
	void *hoaProcessor_parent;
	Hoa3D::Ambisonic   *f_ambisonic;
	
	t_args_struct object_args;
	long object_nAttrs;
	t_attr_struct *object_attrs;
	
} t_hoa_thisprocess;

t_class *hoa_thisprocess_class;

void *hoa_thisprocess_new(t_symbol *s, short argc, t_atom *argv);
void hoa_thisprocess_free(t_hoa_thisprocess *x);
void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_thisprocess_loadbang(t_hoa_thisprocess *x);
void hoa_thisprocess_bang(t_hoa_thisprocess *x);
void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s);

long hoa_get_number_of_attributes(long ac, t_atom *av);
void hoa_args_setup(short ac, t_atom *av, long *nAttr, t_args_struct *args, t_attr_struct **attrs);
void hoa_init_args(t_hoa_thisprocess *x, short argc, t_atom *argv);


int C74_EXPORT main(void)
{
	t_class* c;
    c = class_new("hoa.thisprocess~", (method)hoa_thisprocess_new, (method)hoa_thisprocess_free, sizeof(t_hoa_thisprocess), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)NULL);
	
	class_addmethod(c, (method)hoa_thisprocess_assist,			"assist",	A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_loadbang,		"loadbang", A_CANT, 0);
	class_addmethod(c, (method)hoa_thisprocess_mute,			"mute",		A_GIMME, 0);
	class_addmethod(c, (method)hoa_thisprocess_bang,			"bang",		0);
	
	class_register(CLASS_BOX, c);
	hoa_thisprocess_class = c;
	return 0;
}


void *hoa_thisprocess_new(t_symbol *s, short argc, t_atom *argv)
{
	int order;
    t_hoa_thisprocess *x = (t_hoa_thisprocess *) object_alloc(hoa_thisprocess_class);
    
	x->out_patcherAttr		= outlet_new(x, NULL);
	x->out_patcherArgs		= outlet_new(x, NULL);
	x->out_mute				= intout(x);
	x->out_mode				= outlet_new(x, NULL);
	x->out_order			= intout(x);
	x->out_harmonicArgument = intout(x);
	x->out_harmonicBand		= intout(x);
    x->out_index			= intout(x);
	
	x->hoaProcessor_parent = Get_HoaProcessor_Object();
	order = HoaProcessor_Get_Ambisonic_Order(x->hoaProcessor_parent);
	x->index = Get_HoaProcessor_Patch_Index(x->hoaProcessor_parent);
	
	x->f_ambisonic = new Hoa3D::Ambisonic(order);
	
	hoa_args_setup(argc, argv, &x->object_nAttrs, &x->object_args, &x->object_attrs);
	
	return (x);
}

void hoa_args_setup(short ac, t_atom *av, long *nAttr, t_args_struct *args, t_attr_struct **attrs)
{
	long attrOffset = 0, attrNumberOfArg = 0;
	attrOffset = attr_args_offset(ac, av);
	char *attrName = NULL;
	t_symbol *tempsym;
	
	nAttr[0] = hoa_get_number_of_attributes(ac, av);
	
	args[0].argc = attrOffset;
	
	// init arguments
	if (attrOffset > 0)
	{
		args[0].argv = (t_atom *) malloc( attrOffset * sizeof(t_atom));
		for (int i = 0; i < attrOffset; i++)
			args[0].argv[i] = av[i];
	}
	
	// init attributes
	if (nAttr[0] > 0)
	{
		attrs[0] = (t_attr_struct*) malloc(nAttr[0] * sizeof(t_attr_struct));
		
		av += attrOffset;
		ac -= attrOffset;
		
		for (int i = 0; i < nAttr[0]; i++)
		{
			//postatom(av);
			attrName = atom_string(av);
			
			if (attrName[0] == '@')
			{
				attrName++;						// remove '@' char
				tempsym = gensym(attrName);
				atom_setsym(av, tempsym);		// to check next offset
				attrs[0][i].msg = tempsym;
			}
			
			attrNumberOfArg = attr_args_offset(ac, av);
			
			attrs[0][i].argc = attrNumberOfArg-1;
			attrs[0][i].argv = (t_atom*) malloc( attrNumberOfArg * sizeof(t_atom));
			
			for (int j = 1; j < attrNumberOfArg; j++) {
				attrs[0][i].argv[j-1] = av[j];
				//postatom(attrs[0][i].argv+j);
			}
			
			av += attrNumberOfArg;
			ac -= attrNumberOfArg;
		}
	}
}

void hoa_thisprocess_free(t_hoa_thisprocess *x)
{
	free(x->object_args.argv);
	
	if (x->object_nAttrs > 0)
	{
		for (int i = 0; i < x->object_nAttrs; i++)
			free(x->object_attrs[i].argv);
		
		free(x->object_attrs);
	}
}

void hoa_thisprocess_mute(t_hoa_thisprocess *x, t_symbol *msg, short argc, t_atom *argv)
{	
	long arg_val;
	
	if (!argc)
		return;
	
	arg_val = atom_getlong(argv);
	
	HoaProcessor_Set_Patch_On (x->hoaProcessor_parent, x->index, !arg_val);
	outlet_int(x->out_mute, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
}

void hoa_thisprocess_loadbang(t_hoa_thisprocess *x)
{
	hoa_thisprocess_bang(x);
}

long hoa_get_number_of_attributes(long ac, t_atom *av)
{
	long nAttrs = 0;
	char *attrName = NULL;
	if (ac > 0 && av)
	{
		for (int i=0; i<ac; i++)
		{
			if (atom_gettype(av+i) == A_SYM)
			{
				attrName = atom_string(av + i);
				if (attrName[0] == '@')
					nAttrs++;
			}
		}
	}
	
	return nAttrs;
}

void hoa_process_attrs(t_hoa_thisprocess *x, long patcher_nAttrs, t_attr_struct *attrs_patcher, long *nAttr, t_attr_struct **attrs_processed)
{
	int i, j;
	long number_of_attrs = x->object_nAttrs + patcher_nAttrs;
	
	// check the real number of attr (! does not check duplicate symbol in object or patcher)
	for (i = 0; i < patcher_nAttrs; i++)
		for (j = 0; j < x->object_nAttrs; j++)
			if ( attrs_patcher[i].msg == x->object_attrs[j].msg )
				number_of_attrs--;
	
	nAttr[0] = number_of_attrs;
	
	attrs_processed[0] = (t_attr_struct*) malloc( number_of_attrs * sizeof(t_attr_struct));
	
	
	
	for (i = 0; i < patcher_nAttrs; i++)
	{
		for (j = 0; j < x->object_nAttrs; j++)
		{
			if ( attrs_patcher[i].msg == x->object_attrs[j].msg )
			{
				number_of_attrs--;
			}
		}
	}
}

void hoa_thisprocess_bang(t_hoa_thisprocess *x)
{
	if (x->hoaProcessor_parent)
	{
		if (x->index > 0)
		{
			long ac = 0;
			t_atom *av = NULL;
			t_hoa_err err = HoaProcessor_Get_PatcherArgs(x->hoaProcessor_parent, x->index, &ac, &av);
			if (ac && av && err == HOA_ERR_NONE)
			{
				int i;
				long patcher_nAttrs = 0;
				t_args_struct patcher_args;
				t_attr_struct *patcher_attrs;
				
				hoa_args_setup(ac, av, &patcher_nAttrs, &patcher_args, &patcher_attrs);
				
				if (patcher_nAttrs > 0)
				{
					long nAttrs_processed = 0;
					t_attr_struct *attrs_processed;
					//hoa_process_attrs(x, patcher_nAttrs, patcher_attrs, &nAttrs_processed, &attrs_processed);
					
					if (nAttrs_processed > 0)
					{
						for (i = 0; i < nAttrs_processed; i++)
							outlet_anything(x->out_patcherAttr, attrs_processed[i].msg, attrs_processed[i].argc, attrs_processed[i].argv);
					}
					
					// output done message to indicate that the attributes have been processed
					
					outlet_anything(x->out_patcherAttr, gensym("done"), 0, NULL);
					
					// free patcher_attrs
					for (int i = 0; i < patcher_nAttrs; i++)
						free(patcher_attrs[i].argv);
					free(patcher_attrs);
					
					// free attrs_processed
					for (int i = 0; i < nAttrs_processed; i++)
						free(attrs_processed[i].argv);
					free(attrs_processed);
				}
								
				// output arguments
				if (patcher_args.argc > 0 || x->object_args.argc > 0)
				{
					t_args_struct args_processed;
					args_processed.argc = MAX(patcher_args.argc, x->object_args.argc);
					args_processed.argv = (t_atom*) malloc(args_processed.argc * sizeof(t_atom));
					
					for (i = 0; i < args_processed.argc; i++)
						args_processed.argv[i] = ( i < patcher_args.argc) ? patcher_args.argv[i] : x->object_args.argv[i];
					
					outlet_list(x->out_patcherArgs, gensym("list"), args_processed.argc, args_processed.argv);
					
					// free patcher_args
					free(patcher_args.argv);
					
					// free args_processed
					free(args_processed.argv);
				}

				free(av);
			}
			
			outlet_int(x->out_mute, !HoaProcessor_Get_Patch_On (x->hoaProcessor_parent, x->index));
			outlet_anything(x->out_mode, HoaProcessor_Get_Mode(x->hoaProcessor_parent), 0, NULL);
			outlet_int(x->out_order, HoaProcessor_Get_Ambisonic_Order (x->hoaProcessor_parent));
			outlet_int(x->out_harmonicArgument, x->f_ambisonic->getHarmonicArgument(x->index-1));
			outlet_int(x->out_harmonicBand, x->f_ambisonic->getHarmonicBand(x->index-1));
			outlet_int(x->out_index, x->index);
		}
	}
}

void hoa_thisprocess_assist(t_hoa_thisprocess *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_OUTLET) 
	{
		switch (a)
		{
			case 0:
				sprintf(s,"Index");
				break;
			case 1:
				sprintf(s,"Harmonic Band");
				break;
			case 2:
				sprintf(s,"Harmonic Argument");
				break;
			case 3:
				sprintf(s,"Ambisonic Order");
				break;
			case 4:
				sprintf(s,"Mode (no, post, out)");
				break;
			case 5:
				sprintf(s,"Mute Status");
				break;
			case 6:
				sprintf(s,"Patcher Arguments");
				break;
			case 7:
				sprintf(s,"Patcher Attributs");
				break;
		}
	}
    else 
	{
		sprintf(s,"Set Mute, Bang for Report");
    }
}