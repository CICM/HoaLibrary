/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// based on dynamicdsp~ Copyright 2010 Alex Harker. All rights reserved.

#include "../HoaCommon.max.h"
#include "hoa.process~.h"

t_class *hoa_processor_class;

#define SIG_SIZE sizeof(double)
#define MAX_NUM_PATCHES 4096
#define MAX_ARGS 50

////////////////////////////// Structure for patch and related data //////////////////////////////

typedef struct _patchspace
{
	t_patcher*			the_patch;
	struct _dspchain*	the_dspchain;
	t_symbol*			patch_name_in;
	char				patch_name[256];
	short				patch_path;
	
	short				x_argc;				// Arguments (stored in case of reload / update)
	t_atom				x_argv[MAX_ARGS];
	
	double**			out_ptrs;			// Pointer to Audio Out Buffers
	
	char				patch_valid;
	char				patch_on;
		
} t_patchspace;

////////////////////////////////////// ins/outs ////////////////////////////////////////////////

typedef void *t_outvoid;

typedef struct _inout
{
	t_object	s_obj;
	long		s_index;
	void*		s_outlet;
	
} t_inout;

typedef struct _io_infos
{
	long sig_ins;
	long sig_outs;
	long ins;
	long outs;
	
	long sig_ins_maxindex;
	long sig_outs_maxindex;
	long ins_maxindex;
	long outs_maxindex;
	
	long extra_sig_ins;
	long extra_sig_outs;
	long extra_ins;
	long extra_outs;
	
	long extra_sig_ins_maxindex;
	long extra_sig_outs_maxindex;
	long extra_ins_maxindex;
	long extra_outs_maxindex;
	
} t_io_infos;

////////////////////////////////////// The object structure //////////////////////////////////////

typedef struct _hoa_processor
{
    t_pxobject x_obj;
    
	t_patcher *parent_patch;
	
	// Patch Data and Variables 
	
	t_patchspace *patch_space_ptrs[MAX_NUM_PATCHES];
	long patch_spaces_allocated;
	
	t_int32_atomic patch_is_loading;
	
	long target_index;
	
	long last_vec_size;
	long last_samp_rate;
	
	// IO Variables
	
	long mode_default_numins;
	long mode_default_numouts;
	
	long instance_sig_ins;
	long instance_sig_outs;
	long instance_ins;
	long instance_outs;
	
	long extra_sig_ins;
	long extra_sig_outs;
	long extra_ins;
	long extra_outs;
	
	long declared_sig_ins;
	long declared_sig_outs;
	long declared_ins;
	long declared_outs;
	
	void **sig_ins;
	void **sig_outs;
	
	t_outvoid *in_table;			// table of non-signal inlets
	t_outvoid *out_table;			// table of non-signal outlets
	long num_proxies;				// number of proxies
	
	// Hoa stuff
	Hoa2D::Ambisonic*   f_ambi2D;
	Hoa3D::Ambisonic*   f_ambi3D;
	long				f_order;
	t_symbol*			f_mode;
	e_hoa_object_type	f_object_type;
} t_hoa_processor;


void *hoa_processor_new(t_symbol *s, short argc, t_atom *argv);
void hoa_processor_free(t_hoa_processor *x);

t_symbol* get_extra_comment(t_patcher* p, int extra_index, t_symbol* object_class);
void hoa_processor_assist(t_hoa_processor *x, void *b, long m, long a, char *s);

void hoa_processor_loadexit(t_hoa_processor *x, long replace_symbol_pointers, void *previous, void *previousindex);
t_hoa_err hoa_processor_loadpatch(t_hoa_processor *x, long index, t_symbol *patch_name_in, short argc, t_atom *argv);

void hoa_processor_bang(t_hoa_processor *x);
void hoa_processor_int(t_hoa_processor *x, long n);
void hoa_processor_float(t_hoa_processor *x, double f);
void hoa_processor_list(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_anything(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_target(t_hoa_processor *x, long target_index, long index, t_symbol *msg, short argc, t_atom *argv);
short hoa_processor_targetinlets(t_patcher *p, t_args_struct *args);
void hoa_processor_user_target(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);

void hoa_processor_dsp64(t_hoa_processor *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_processor_dsp_internal (t_patchspace *patch_space_ptrs, long vec_size, long samp_rate);
void hoa_processor_perform64(t_hoa_processor *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);

short hoa_processor_linkinlets(t_patcher *p, t_hoa_processor *x);
short hoa_processor_unlinkinlets(t_patcher *p, t_hoa_processor *x);

void hoa_processor_init_io_infos(t_io_infos* io_infos);
short hoa_processor_get_patch_io_context(t_patcher *p, t_io_infos* io_infos);
t_hoa_err hoa_processor_get_patch_filename_io_context(t_hoa_processor *x, t_symbol *patch_name_in, t_io_infos* io_infos);

void hoa_processor_dblclick(t_hoa_processor *x);
void hoa_processor_open(t_hoa_processor *x, long index);
void hoa_processor_doopen(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_pclose(t_hoa_processor *x);
void hoa_processor_wclose(t_hoa_processor *x, long index);
void hoa_processor_dowclose(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);

short hoa_processor_patcher_descend(t_patcher *p, t_intmethod fn, void *arg, t_hoa_processor *x);
short hoa_processor_setsubassoc(t_patcher *p, t_hoa_processor *x);
void hoa_processor_pupdate(t_hoa_processor *x, void *b, t_patcher *p);
void *hoa_processor_subpatcher(t_hoa_processor *x, long index, void *arg);
void hoa_processor_parentpatcher(t_hoa_processor *x, t_patcher **parent);

void hoa_processor_init_patch_space (t_patchspace *patch_space_ptrs);
t_patchspace *hoa_processor_new_patch_space(t_hoa_processor *x,long index);
void hoa_processor_free_patch_and_dsp (t_hoa_processor *x, t_patchspace *patch_space_ptrs);

void *hoa_processor_query_declared_sigins(t_hoa_processor *x);
void *hoa_processor_query_declared_sigouts(t_hoa_processor *x);
void *hoa_processor_query_sigins(t_hoa_processor *x);
void *hoa_processor_query_outptrs_ptr(t_hoa_processor *x, long index);
void *hoa_processor_client_get_patch_on (t_hoa_processor *x, long index);
void hoa_processor_client_set_patch_on (t_hoa_processor *x, long index, long state);

t_hoa_err hoa_getinfos(t_hoa_processor* x, t_hoa_boxinfos* boxinfos);
void *hoa_processor_query_ambisonic_order(t_hoa_processor *x);
void *hoa_processor_query_mode(t_hoa_processor *x);
void *hoa_processor_query_is_2D(t_hoa_processor *x);
void *hoa_processor_query_number_of_instances(t_hoa_processor *x);
t_hoa_err hoa_processor_query_patcherargs(t_hoa_processor *x, long index, long *argc, t_atom **argv);

void hoa_processor_out_message(t_hoa_processor *x, t_args_struct *args);
void hoa_processor_output_typed_message(void* outletptr, t_args_struct *args);

void* hoa_processor_query_io_index(t_hoa_processor *x, long patchIndex, t_object* io);

// ========================================================================================================================================== //
// Main
// ========================================================================================================================================== //

int C74_EXPORT main(void)
{
	t_class* c;

	c = class_new("hoa.process~", (method)hoa_processor_new,  (method)hoa_processor_free, sizeof(t_hoa_processor), NULL, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_processor_dsp64,						"dsp64",				A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_assist,					"assist",				A_CANT, 0);

	class_addmethod(c, (method)hoa_processor_open,						"open",					A_DEFLONG, 0);
	class_addmethod(c, (method)hoa_processor_dblclick,					"dblclick",				A_CANT,	   0);
	class_addmethod(c, (method)hoa_processor_wclose,					"wclose",				A_DEFLONG, 0);
	
	class_addmethod(c, (method)hoa_processor_pupdate,					"pupdate",				A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_subpatcher,				"subpatcher",			A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_parentpatcher,				"parentpatcher",		A_CANT, 0);
	
	class_addmethod(c, (method)hoa_processor_bang,						"bang",							 0);
	class_addmethod(c, (method)hoa_processor_int,						"int",					A_LONG,  0);
	class_addmethod(c, (method)hoa_processor_float,						"float",				A_FLOAT, 0);
	class_addmethod(c, (method)hoa_processor_list,						"list",					A_GIMME, 0);
	class_addmethod(c, (method)hoa_processor_anything,					"anything",				A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_processor_user_target,				"target",				A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_processor_query_mode,				"get_mode",				A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_is_2D,				"is_2D",				A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_patcherargs,			"get_patcherargs",		A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_number_of_instances,	"get_number_of_instance", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_ambisonic_order,		"get_ambisonic_order",	A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_declared_sigins,		"get_declared_sigins",	A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_declared_sigouts,	"get_declared_sigouts", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_sigins,				"get_sigins",			A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_outptrs_ptr,			"get_outptrs_ptr",		A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_get_patch_on,		"get_patch_on",			A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_set_patch_on,		"set_patch_on",			A_CANT, 0);
	
	class_addmethod(c, (method)hoa_processor_out_message,				"out_message",			A_CANT, 0); // used to receive a message from a hoa.out object
	class_addmethod(c, (method)hoa_processor_query_io_index,			"get_io_index",			A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_processor_class = c;
	return 0;
}


// ========================================================================================================================================== //
// Object Creation / Freeing / Assisstance
// ========================================================================================================================================== //


void *hoa_processor_new(t_symbol *s, short argc, t_atom *argv)
{	
	t_hoa_processor *x = (t_hoa_processor*)object_alloc(hoa_processor_class);
	
	t_symbol *patch_name_entered = NULL;
	t_symbol *tempsym;
	long i;
	int first_int = 1;
	x->f_mode = hoa_sym_ambisonics;
	short ac = 0;
	t_atom av[MAX_ARGS];
	long number_of_instances_to_load = 0;
	
	x->patch_spaces_allocated = 0;
	x->target_index = 0;
	
	x->last_vec_size = 64;
	x->last_samp_rate = 44100;
	
	x->in_table = x->out_table = 0;
	
	x->patch_is_loading = 0;
	
	x->declared_sig_ins = x->declared_ins = x->instance_ins = x->instance_sig_ins = x->extra_ins = x->extra_sig_ins = x->mode_default_numins = 0;
	x->declared_sig_outs = x->declared_outs = x->instance_outs = x->instance_sig_outs = x->extra_outs = x->extra_sig_outs = x->mode_default_numouts = 0;
	
	// check 2D or 3D context
	
	x->f_object_type = HOA_OBJECT_2D;
	if (s == gensym("hoa.3d.process~"))
		x->f_object_type = HOA_OBJECT_3D;
	else if (s == gensym("hoa.plug~"))
		object_error((t_object*)x, "hoa.plug~ is deprecated please take a look at the hoa.process~ object");

	// Check the order or the number of instances :
	if (argc && atom_gettype(argv) == A_LONG)
	{
		first_int = atom_getlong(argv);
		argc--; argv++;
	}
	
	// Check if there is a patch name given to load
	if (argc && atom_gettype(argv) == A_SYM)
	{
		patch_name_entered = atom_getsym(argv);
		argc--; argv++;
	}
	
	// Check the mode
	if (argc && atom_gettype(argv) == A_SYM)
	{
		tempsym = atom_getsym(argv);
		if (tempsym == hoa_sym_planewaves)
			x->f_mode = tempsym;
		argc--; argv++;
	}
	
	// Get arguments to patch that is being loaded if there are any
	if (argc && atom_gettype(argv) == A_SYM) 
	{
		tempsym = atom_getsym(argv);
		argc--; argv++;
		if (tempsym == hoa_sym_args) 
		{				
			ac = argc;
			if (ac > MAX_ARGS)
				ac = MAX_ARGS;
			for (i = 0; i < ac; i++, argv++)
				av[i] = *argv;
			ac = i;
		}
	}
	
	x->f_order = first_int;
	x->f_ambi3D = new Hoa3D::Ambisonic(first_int);
	x->f_ambi2D = new Hoa2D::Ambisonic(first_int);
	
	// Initialise patcher symbol
	
	object_obex_lookup(x, gensym("#P"), &x->parent_patch);									// store reference to parent patcher
	
	// load a single instance to query io informations
	
	t_io_infos io_infos;
	t_hoa_err loaded_patch_err = hoa_processor_get_patch_filename_io_context(x, patch_name_entered, &io_infos);
	
	if (loaded_patch_err != HOA_ERR_NONE)
		return x;
	
	
	// default io config depends on object type (2d/3d) and mode :
	
	if (x->f_mode == hoa_sym_ambisonics)
	{
		if (x->f_object_type == HOA_OBJECT_2D)
			x->mode_default_numins = x->mode_default_numouts = x->f_ambi2D->getNumberOfHarmonics();
		else if (x->f_object_type == HOA_OBJECT_3D)
			x->mode_default_numins = x->mode_default_numouts = x->f_ambi3D->getNumberOfHarmonics();
	}
	else if (x->f_mode == hoa_sym_planewaves)
	{
		x->mode_default_numins = x->mode_default_numouts = first_int;
	}
	
	// Set object io depending on contextual io of the current patcher
	
	if (io_infos.sig_ins > 0)
		x->instance_sig_ins = x->declared_sig_ins = x->mode_default_numins;
	
	if (io_infos.sig_outs > 0)
		x->instance_sig_outs = x->declared_sig_outs = x->mode_default_numouts;
		
	if (io_infos.ins > 0)
		x->instance_ins = x->declared_ins = x->mode_default_numins;
	
	if (io_infos.outs > 0)
		x->instance_outs = x->declared_outs = x->mode_default_numouts;
	
	// --- add extra ins and outs (if necessary)
	
	x->extra_sig_ins	= io_infos.extra_sig_ins_maxindex;
	x->extra_sig_outs	= io_infos.extra_sig_outs_maxindex;
	x->extra_ins		= io_infos.extra_ins_maxindex;
	x->extra_outs		= io_infos.extra_outs_maxindex;
	
	x->declared_sig_ins		+= x->extra_sig_ins;
	x->declared_sig_outs	+= x->extra_sig_outs;
	x->declared_ins			+= x->extra_ins;
	x->declared_outs		+= x->extra_outs;
	
	// --- Create signal in/out buffers and zero
	
	x->num_proxies = max(x->instance_sig_ins, x->instance_ins) + max(x->extra_sig_ins, x->extra_ins);
	
	x->declared_sig_ins = x->declared_ins = x->num_proxies;
	
	x->sig_ins	= (void **) malloc(x->declared_sig_ins * sizeof(void *));
	x->sig_outs = (void **) malloc(x->declared_sig_outs * sizeof(void *));
	
	for (i = 0; i < x->declared_sig_ins; i++)
		x->sig_ins[i] = 0;
	for (i = 0; i < x->declared_sig_outs; i++)
		x->sig_outs[i] = 0;
	
	
	// io schema :
	// ins : instance in (mixed sig/ctrl) -- extra (mixed sig/ctrl)
	// outs : instance sig outs -- extra sig -- instance ctrl outs -- extra ctrl
	
	// Make non-signal inlets
	
	if (x->declared_ins)
	{
		x->in_table = (t_outvoid *)t_getbytes(x->declared_ins * sizeof(t_outvoid));
		for (i = 0; i < x->declared_ins; i++)
			x->in_table[i] = outlet_new(0L, 0L);											// make generic unowned inlets
	}
	
	// Make signal ins
	
	dsp_setup((t_pxobject *) x, x->num_proxies);
	x->x_obj.z_misc = Z_NO_INPLACE;															// due to output zeroing!!
	
	// Make non-signal instance and extra outlets
	
	if (x->declared_outs)
	{
		x->out_table = (t_outvoid *) t_getbytes(x->declared_outs * sizeof(t_outvoid));
		
		// non-signal extra outlets
		if (x->extra_outs)
			for (i = x->declared_outs - 1; i >= (x->declared_outs - x->extra_outs); i--)
				x->out_table[i] = outlet_new((t_object *)x, 0);
		
		// non-signal instance outlets
		for (i = x->declared_outs - x->extra_outs - 1; i >= 0; i--)
			x->out_table[i] = outlet_new((t_object *)x, 0);
	}
	
	// Make signal extra outlets
	
	for (i = 0; i < x->declared_sig_outs; i++)
		outlet_new((t_object *)x, "signal");
	
	// Load patches and initialise all instances
	
	if (patch_name_entered && loaded_patch_err == HOA_ERR_NONE)
	{
		if (x->f_mode == hoa_sym_ambisonics)
		{
			if (x->f_object_type == HOA_OBJECT_2D)
				number_of_instances_to_load = x->f_ambi2D->getNumberOfHarmonics();
			else if (x->f_object_type == HOA_OBJECT_3D)
				number_of_instances_to_load = x->f_ambi3D->getNumberOfHarmonics();
		}
		else if (x->f_mode == hoa_sym_planewaves)
		{
			number_of_instances_to_load = first_int;
		}
		
		for (i = 0; i < number_of_instances_to_load; i++)
		{
			hoa_processor_loadpatch(x, i, patch_name_entered, ac, av);
		}
	}
	
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_processor* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = x->f_object_type;
	
	if (x->f_mode == hoa_sym_ambisonics)
	{
		boxinfos->autoconnect_inputs = (long) max(x->instance_sig_ins, x->instance_ins);
		boxinfos->autoconnect_outputs = (long) max(x->instance_sig_ins, x->instance_ins);
		
		boxinfos->autoconnect_inputs_type = boxinfos->autoconnect_inputs ? HOA_CONNECT_TYPE_AMBISONICS : HOA_CONNECT_TYPE_STANDARD;
		boxinfos->autoconnect_outputs_type = boxinfos->autoconnect_outputs ? HOA_CONNECT_TYPE_AMBISONICS : HOA_CONNECT_TYPE_STANDARD;
	}
	else if (x->f_mode == hoa_sym_planewaves)
	{
		boxinfos->autoconnect_inputs = (long) max(x->instance_sig_ins, x->instance_ins);
		boxinfos->autoconnect_outputs = (long) max(x->instance_sig_ins, x->instance_ins);
		
		boxinfos->autoconnect_inputs_type = boxinfos->autoconnect_inputs ? HOA_CONNECT_TYPE_PLANEWAVES : HOA_CONNECT_TYPE_STANDARD;
		boxinfos->autoconnect_outputs_type = boxinfos->autoconnect_outputs ? HOA_CONNECT_TYPE_PLANEWAVES : HOA_CONNECT_TYPE_STANDARD;
	}
	return HOA_ERR_NONE;
}

void hoa_processor_free(t_hoa_processor *x)
{
	t_patchspace *patch_space_ptr;
	long i;
	
	dsp_free((t_pxobject *)x);
	
	// Free patches
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		hoa_processor_free_patch_and_dsp (x, patch_space_ptr);
		
		if (patch_space_ptr)
			freebytes((char *) patch_space_ptr, sizeof(t_patchspace));
	}
	
	if (x->declared_sig_ins)
		free(x->sig_ins);
	
	if (x->declared_sig_outs)
		free(x->sig_outs);
	
	for (i = 0; i < x->declared_ins; i++)
		object_free((t_object*)x->in_table[i]);
	
	if (x->in_table)
		freebytes(x->in_table, x->declared_ins * sizeof(t_outvoid));
	
	if (x->out_table)
		freebytes(x->out_table, x->declared_outs * sizeof(t_outvoid));
	
	delete x->f_ambi2D;
	delete x->f_ambi3D;
}

t_symbol* get_extra_comment(t_patcher* p, int extra_index, t_symbol* object_class)
{
	t_box *b;
	t_object *io;
	t_symbol* comment = hoa_sym_nothing;
	int extra_index_exist = 0;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))
	{
		if (jbox_get_maxclass(b) == object_class)
		{
			io = jbox_get_object(b);
			
			if (extra_index == object_attr_getlong(io, hoa_sym_extra))
			{
				extra_index_exist = 1;
				
				comment = object_attr_getsym(io, hoa_sym_comment);
				
				if (comment != hoa_sym_nothing)
					break;
			}
		}
    }
	
	if (!extra_index_exist)
		comment = gensym("does nothing");
	
	return comment;
}

void hoa_processor_assist(t_hoa_processor *x, void *b, long m, long a, char *s)
{
	long		inlet = a + 1;
	int			extra_index = 0;
	int			is_extra_sig, is_extra_ctrl, is_instance_sig, is_instance_ctrl;
	
	char		sig_basis_text[50];
	char		ctrl_basis_text[50];
	t_symbol*	sig_extra_comment = hoa_sym_nothing;
	t_symbol*	ctrl_extra_comment = hoa_sym_nothing;
	
	
	is_extra_sig = is_extra_ctrl = is_instance_sig = is_instance_ctrl = 0;
	
	// check if "a" match an extra io + check if io is sig or/and ctrl
	
	if ( m == ASSIST_INLET && (x->extra_ins || x->extra_sig_ins))
	{
		int max_instance = max(x->instance_ins, x->instance_sig_ins);
		
		if (inlet > max_instance)
		{
			extra_index = inlet - max_instance;
			
			if (inlet <= x->instance_ins + x->extra_ins)
			{
				is_extra_ctrl = 1;
				sprintf(ctrl_basis_text,"Extra %i", extra_index);
			}
			if (inlet <= x->instance_sig_ins + x->extra_sig_ins)
			{
				is_extra_sig = 1;
				sprintf(sig_basis_text,"Extra %i", extra_index);
			}
		}
	}
	else if ( m == ASSIST_OUTLET && (x->extra_outs || x->extra_sig_outs))
	{
		if (inlet > x->instance_sig_outs && inlet <= x->declared_sig_outs)
		{
			is_extra_sig = 1;
			extra_index = inlet - x->instance_sig_outs;
			sprintf(sig_basis_text,"Extra %i", extra_index);
		}
		
		if ( inlet > x->declared_sig_outs + x->instance_outs)
		{
			is_extra_ctrl = 1;
			extra_index = inlet - (x->declared_sig_outs + x->instance_outs);
			sprintf(ctrl_basis_text,"Extra %i", extra_index);
		}
	}
	
	// check if "a" match an instance io + check if io is sig or/and ctrl
	
	if (!is_extra_ctrl || !is_extra_sig)
	{
		// instance in
		if ( m == ASSIST_INLET && !is_extra_ctrl && (inlet <= x->instance_ins))
		{
			is_instance_ctrl = 1;
			
			if (x->f_mode == hoa_sym_ambisonics)
			{
				if (x->f_object_type == HOA_OBJECT_2D)
					sprintf(ctrl_basis_text,"%s", x->f_ambi2D->getHarmonicsName( a ).c_str());
				else if (x->f_object_type == HOA_OBJECT_3D)
					sprintf(ctrl_basis_text,"%s", x->f_ambi3D->getHarmonicsName( a ).c_str());
			}
			else
			{
				sprintf(ctrl_basis_text,"Channel %ld", inlet);
			}
		}
		
		// instance out
		if ( m == ASSIST_OUTLET && !is_extra_ctrl && (inlet > x->declared_sig_outs))
		{
			is_instance_ctrl = 1;
			
			if (x->f_mode == hoa_sym_ambisonics)
			{
				if (x->f_object_type == HOA_OBJECT_2D)
					sprintf(ctrl_basis_text,"%s", x->f_ambi2D->getHarmonicsName( a - x->declared_sig_outs ).c_str());
				else if (x->f_object_type == HOA_OBJECT_3D)
					sprintf(ctrl_basis_text,"%s", x->f_ambi3D->getHarmonicsName( a - x->declared_sig_outs ).c_str());
			}
			else
			{
				sprintf(ctrl_basis_text,"Channel %ld", inlet - x->declared_sig_outs);
			}
		}
		
		// instance sig in
		if ( m == ASSIST_INLET && !is_extra_sig && (inlet <= x->instance_sig_ins))
		{
			is_instance_sig = 1;
			
			if (x->f_mode == hoa_sym_ambisonics)
			{
				if (x->f_object_type == HOA_OBJECT_2D)
					sprintf(sig_basis_text,"%s", x->f_ambi2D->getHarmonicsName( a ).c_str());
				else if (x->f_object_type == HOA_OBJECT_3D)
					sprintf(sig_basis_text,"%s", x->f_ambi3D->getHarmonicsName( a ).c_str());
			}
			else
			{
				sprintf(sig_basis_text,"Channel %ld", inlet);
			}
		}
		
		// instance sig out
		if ( m == ASSIST_OUTLET && !is_extra_sig && (inlet <= x->instance_sig_outs))
		{
			is_instance_sig = 1;
			
			if (x->f_mode == hoa_sym_ambisonics)
			{
				if (x->f_object_type == HOA_OBJECT_2D)
					sprintf(sig_basis_text,"%s", x->f_ambi2D->getHarmonicsName( a ).c_str());
				else if (x->f_object_type == HOA_OBJECT_3D)
					sprintf(sig_basis_text,"%s", x->f_ambi3D->getHarmonicsName( a ).c_str());
			}
			else
			{
				sprintf(sig_basis_text,"Channel %ld", inlet);
			}
		}
	}
	
	// check if there is an extra comment
	
	if (is_extra_ctrl)
	{
		ctrl_extra_comment = get_extra_comment(x->patch_space_ptrs[0]->the_patch, extra_index, (m == ASSIST_INLET) ? hoa_sym_in : hoa_sym_out);
		
		// if extra doesn't match explicitly an inlet/outlet in the patch
		if (ctrl_extra_comment == gensym("does nothing"))
			is_extra_ctrl = 0;
	}
	
	if (is_extra_sig)
	{
		sig_extra_comment = get_extra_comment(x->patch_space_ptrs[0]->the_patch, extra_index, (m == ASSIST_INLET) ? hoa_sym_sigin : hoa_sym_sigout);
		
		// if extra doesn't match explicitly an inlet/outlet in the patch
		if (sig_extra_comment == gensym("does nothing"))
			is_extra_sig = 0;
	}
	
	// enough, it's time to construct our assist string !
	
	if ( (is_instance_sig && is_instance_ctrl) || (is_extra_sig && is_extra_ctrl) )
	{
		if (sig_extra_comment == hoa_sym_nothing && ctrl_extra_comment == hoa_sym_nothing)
			sprintf(s,"(signal, messages) %s", sig_basis_text);
		else if (sig_extra_comment == ctrl_extra_comment)
			sprintf(s,"(signal, messages) %s : %s", sig_basis_text, sig_extra_comment->s_name);
		else if (sig_extra_comment != hoa_sym_nothing && ctrl_extra_comment != hoa_sym_nothing)
			sprintf(s,"(signal) %s : %s, (messages) %s : %s", sig_basis_text, sig_extra_comment->s_name, ctrl_basis_text, ctrl_extra_comment->s_name);
		else if (sig_extra_comment != hoa_sym_nothing && ctrl_extra_comment == hoa_sym_nothing)
			sprintf(s,"(signal) %s : %s, (messages) %s", sig_basis_text, sig_extra_comment->s_name, ctrl_basis_text);
		else if (sig_extra_comment == hoa_sym_nothing && ctrl_extra_comment != hoa_sym_nothing)
			sprintf(s,"(signal) %s, (messages) %s : %s", sig_basis_text, ctrl_basis_text, ctrl_extra_comment->s_name);
	}
	else if ( (is_instance_sig || is_extra_sig) && !is_instance_ctrl && !is_extra_ctrl)
	{
		if (sig_extra_comment == hoa_sym_nothing)
			sprintf(s,"(signal) %s", sig_basis_text);
		else
			sprintf(s,"(signal) %s, %s", sig_basis_text, sig_extra_comment->s_name);
	}
	else if ( (is_instance_ctrl || is_extra_ctrl) && !is_instance_sig && !is_extra_sig)
	{
		if (ctrl_extra_comment == hoa_sym_nothing)
			sprintf(s,"(messages) %s", ctrl_basis_text);
		else
			sprintf(s,"(messages) %s, %s", ctrl_basis_text, ctrl_extra_comment->s_name);
	}
	else
	{
		sprintf(s,"nothing here !");
	}
/*
	post("inlet %ld : instance_sig = %ld, instance_ctrl = %ld, extra_sig = %ld, extra_ctrl = %ld", inlet, is_instance_sig, is_instance_ctrl, is_extra_sig, is_extra_ctrl);
*/
}

// ========================================================================================================================================== //
// Patcher Loading / Deleting
// ========================================================================================================================================== //

void hoa_processor_loadexit(t_hoa_processor *x, long replace_symbol_pointers, void *previous, void *previousindex)
{
	if (replace_symbol_pointers)
	{
		hoa_sym_HoaProcessor->s_thing = (struct object*)previous;
		hoa_sym_HoaProcessorPatchIndex->s_thing = (struct object*)previousindex;
	}
	ATOMIC_DECREMENT_BARRIER(&x->patch_is_loading);
}

t_hoa_err hoa_processor_loadpatch(t_hoa_processor *x, long index, t_symbol *patch_name_in, short argc, t_atom *argv)
{
	t_patchspace *patch_space_ptr = 0;
	t_object *previous;
	t_object *previousindex;
	t_fourcc type;
	t_fourcc filetypelist = 'JSON';
	long patch_spaces_allocated = x->patch_spaces_allocated;
	long harmonic_band, harmonic_argument;
	long i;
	
	short patch_path;
	short saveloadupdate;
	char filename[MAX_FILENAME_CHARS];
	char windowname[280];
	t_patcher *p;

	// Check that this object is not loading in another thread
	
	if (ATOMIC_INCREMENT_BARRIER(&x->patch_is_loading) > 1)
	{
		object_error((t_object*)x, "patch is loading in another thread");
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FAIL;
	}
	
	// Find a free patch if no index is given
	
	if (index < 0)
	{
		for (index = 0; index < patch_spaces_allocated; index++)
			if (x->patch_space_ptrs[index]->the_patch == 0) 
				break;
	}
	
	// Check that the index is valid
	
	if (index >= MAX_NUM_PATCHES) 
	{
		object_error((t_object*)x, "max number of patcher loaded exceeded");
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FAIL;
	}
		
	// Create patchspaces up until the last allocated index (if necessary) and store the pointer
	
	for (i = patch_spaces_allocated; i < index + 1; i++)
		hoa_processor_new_patch_space (x, i);
	
	patch_space_ptr = x->patch_space_ptrs[index];
	
	// Free the old patch - the new patch is not yet valid, but we switch it on so it can be switched off at loadbang time
	
	patch_space_ptr->patch_valid = 0;
	hoa_processor_free_patch_and_dsp(x, patch_space_ptr);
	hoa_processor_init_patch_space(patch_space_ptr);
	patch_space_ptr->patch_on = 1;
	
	// Bind to the loading symbols and store the old symbols
	
	previous = hoa_sym_HoaProcessor->s_thing;
	previousindex = hoa_sym_HoaProcessorPatchIndex->s_thing;
	
	hoa_sym_HoaProcessor->s_thing = (t_object *) x;										
	hoa_sym_HoaProcessorPatchIndex->s_thing = (t_object *) (index + 1);						
	
	// Try to locate a file of the given name that is of the correct type
	
	strncpy_zero(filename, patch_name_in->s_name, MAX_FILENAME_CHARS);
	
	// if filetype does not exists
	if (locatefile_extended(filename, &patch_path, &type, &filetypelist, 1))
	{
		object_error((t_object*)x, "patcher \"%s\" not found !", filename);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return HOA_ERR_FILE_NOT_FOUND;
	}
	
	// Check the number of rarguments (only up to 16 allowed right now)
	
	if (argc > MAX_ARGS)
		argc = MAX_ARGS;
	
	// Load the patch (don't interrupt dsp)
	
	saveloadupdate = dsp_setloadupdate(false);
	p = (t_patcher*) intload(filename, patch_path, 0 , argc, argv, false);
	dsp_setloadupdate(saveloadupdate);
	
	// Check something has loaded
	
	if (!p) 
	{
		object_error((t_object*)x, "error loading %s", filename);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return HOA_ERR_FAIL;
	}
	
	// Check that it is a patcher that has loaded
	
	if (!ispatcher((t_object*)p))
	{
		object_error((t_object*)x, "%s is not a patcher file", filename);
		object_free((t_object *)p);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return HOA_ERR_FAIL;
	}
	
	// Change the window name to : "patchname (index) [band arg]" (if mode no or post)
	
	if (x->f_mode == hoa_sym_ambisonics)
	{
		if (x->f_object_type == HOA_OBJECT_2D)
		{
			harmonic_band = x->f_ambi2D->getHarmonicBand(index);
			harmonic_argument = x->f_ambi2D->getHarmonicArgument(index);
			snprintf(windowname, 256, "%s (%ld) [%ld %ld]", patch_name_in->s_name, index+1, harmonic_band, harmonic_argument);
		}
		else if (x->f_object_type == HOA_OBJECT_3D)
		{
			harmonic_band = x->f_ambi3D->getHarmonicBand(index);
			harmonic_argument = x->f_ambi3D->getHarmonicArgument(index);
			snprintf(windowname, 256, "%s (%ld) [%ld %ld]", patch_name_in->s_name, index+1, harmonic_band, harmonic_argument);
		}
	}
	else
	{
		snprintf(windowname, 256, "%s (%ld)", patch_name_in->s_name, index+1);
	}
	
	jpatcher_set_title(p, gensym(windowname));
	
	// Set the relevant associations
	hoa_processor_patcher_descend((t_patcher *)p, (t_intmethod) hoa_processor_setsubassoc, x, x);
	
	// Link inlets and outlets
	if (x->declared_ins) 
		hoa_processor_patcher_descend((t_patcher *)p, (t_intmethod) hoa_processor_linkinlets, x, x);
	
	// Copy all the relevant data into the patch space
	
	patch_space_ptr->the_patch = (t_patcher*)p;
	patch_space_ptr->patch_name_in = patch_name_in;
	
	strcpy(patch_space_ptr->patch_name, filename);
	patch_space_ptr->patch_path = patch_path;	
	
	patch_space_ptr->x_argc = argc;
	for (i = 0; i < argc; i++)
		patch_space_ptr->x_argv[i] = argv[i];
	
	// Compile the dspchain in case dsp is on
	
	hoa_processor_dsp_internal (patch_space_ptr, x->last_vec_size, x->last_samp_rate);
	
	// The patch is valid and ready to go
	
	patch_space_ptr->patch_valid = 1;
	
	// Return to previous state
		
	hoa_processor_loadexit(x, 1, previous, previousindex);
	
	return HOA_ERR_NONE;
}

// ========================================================================================================================================== //
// Messages in passed on to the patcher via the "in" objects / Voice targeting
// ========================================================================================================================================== //


void hoa_processor_bang(t_hoa_processor *x)
{	
	long index = proxy_getinlet((t_object *)x);	
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
	{
		return;
	}

	if (target_index)
	{
		hoa_processor_target(x, target_index, index, hoa_sym_bang, 0, 0);
		//post("hoa_processor_target target_index = %ld", target_index);
	}
	else
	{
		outlet_bang(x->in_table[index]);
		//post("outlet_bang");
	}
}

void hoa_processor_int(t_hoa_processor *x, long n)
{
	long index = proxy_getinlet((t_object *)x);	// proxy index
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
		return;		
	
	if (target_index)
	{
		t_atom n_atom; 
		atom_setlong (&n_atom, n);
		hoa_processor_target(x, target_index, index, hoa_sym_int, 1, &n_atom);
	}
	else
		outlet_int(x->in_table[index], n);
}

void hoa_processor_float(t_hoa_processor *x, double f)
{
	long index = proxy_getinlet((t_object *)x);	// proxy index
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
		return;
	
	if (target_index)
	{
		t_atom f_atom;
		atom_setfloat(&f_atom, f);
		hoa_processor_target(x, target_index, index, hoa_sym_float, 1, &f_atom);
	}
	else
		outlet_float(x->in_table[index], f);
}

void hoa_processor_list(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	long index = proxy_getinlet((t_object *)x);	// proxy index
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
		return;
	
	if (target_index)
		hoa_processor_target(x, target_index, index, hoa_sym_list, argc, argv);
	else
		outlet_list(x->in_table[index], hoa_sym_list, argc, argv);
}

void hoa_processor_anything(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	long index = proxy_getinlet((t_object *)x);	// proxy index
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
		return;		
	
	if (target_index)
		hoa_processor_target(x, target_index, index, s, argc, argv);
	else
		outlet_anything(x->in_table[index], s, argc, argv);
}

void hoa_processor_target(t_hoa_processor *x, long target_index, long index, t_symbol *msg, short argc, t_atom *argv)
{	
	t_args_struct pass_args;
	
	pass_args.msg = msg;
	pass_args.argc = argc;
	pass_args.argv = argv;
	pass_args.index = index + 1;
	
	if (target_index >= 1 && target_index <= x->patch_spaces_allocated)
	{
		t_patcher *p = x->patch_space_ptrs[target_index - 1]->the_patch;
		
		if (x->patch_space_ptrs[target_index - 1]->patch_valid)
			hoa_processor_patcher_descend(p, (t_intmethod) hoa_processor_targetinlets, &pass_args, x);
	}
}

// - inlet and outlet linking using the in and out objects
short hoa_processor_targetinlets(t_patcher *p, t_args_struct *args)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b)) 
	{
		if (jbox_get_maxclass(b) == hoa_sym_in) 
		{
			io = (t_inout *) jbox_get_object(b);
			
			//post("hoa_processor_targetinlets io->s_index = %ld, args->index = %ld", io->s_index, args->index);
			
			if (io->s_index == args->index)
				hoa_processor_output_typed_message(io->s_obj.o_outlet, args);
		}
    }
	return (0);
}

void hoa_processor_user_target(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	long target_index = argc ? atom_getlong(argv) : 0;
	x->target_index = target_index;
}

void hoa_processor_out_message(t_hoa_processor *x, t_args_struct *args)
{
	long index = args->index;
	if (args->index > 0 && args->index <= x->declared_outs)
		hoa_processor_output_typed_message(x->out_table[index-1], args);
}

void hoa_processor_output_typed_message(void* outletptr, t_args_struct *args)
{
	if (outletptr)
	{
		if (args->msg == hoa_sym_bang)
			outlet_bang(outletptr);
		else if (args->msg == hoa_sym_int)
			outlet_int(outletptr, atom_getlong(args->argv));
		else if (args->msg == hoa_sym_float)
			outlet_float(outletptr, atom_getfloat(args->argv));
		else if (args->msg == hoa_sym_list)
			outlet_list(outletptr, 0L, args->argc, args->argv);
		else
			outlet_anything (outletptr, args->msg, args->argc, args->argv);
	}
}

// ========================================================================================================================================== //
// Perform and DSP Routines
// ========================================================================================================================================== //

void hoa_processor_perform64 (t_hoa_processor *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
{
	for (int i = 0; i < x->declared_sig_ins; i++)
		x->sig_ins[i] = ins[i];
	
	// Zero Outputs
	for (int i = 0; i < x->declared_sig_outs; i++)
		memset(outs[i], 0, SIG_SIZE * vec_size);
	
	if (x->x_obj.z_disabled)
		return;
		
	t_patchspace **patch_space_ptrs = x->patch_space_ptrs;
	t_patchspace *next_patch_space_ptr = 0;
	
	t_dspchain *next_dspchain = 0;
	
	long patch_spaces_allocated = x->patch_spaces_allocated;
	long index = 0;
	
	for (int i = 0; i < patch_spaces_allocated; i++)
	{
		if (++index >= patch_spaces_allocated)
			index -= patch_spaces_allocated;
		
		next_patch_space_ptr = patch_space_ptrs[index];
		next_dspchain = next_patch_space_ptr->the_dspchain;
		
		if (next_patch_space_ptr->patch_valid && next_patch_space_ptr->patch_on && next_dspchain)
		{
			next_patch_space_ptr->out_ptrs = outs;
			dspchain_tick(next_dspchain);
		}
	}
}

void hoa_processor_dsp64 (t_hoa_processor *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	t_patchspace *patch_space_ptr;
	
	// Do internal dsp compile (for each valid patch)
	
	for (int i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		if (patch_space_ptr->patch_valid)
			hoa_processor_dsp_internal (patch_space_ptr, maxvectorsize, samplerate);
	}
	
	x->last_vec_size = maxvectorsize;
	x->last_samp_rate = samplerate;
	
	object_method(dsp64, gensym("dsp_add64"), x, hoa_processor_perform64, 0, NULL);
}

void hoa_processor_dsp_internal (t_patchspace *patch_space_ptr, long vec_size, long samp_rate)
{
	// Free the old dspchain
		
	if (patch_space_ptr->the_dspchain)
		object_free((t_object *)patch_space_ptr->the_dspchain);
	
	// Recompile 
	
	patch_space_ptr->the_dspchain = dspchain_compile(patch_space_ptr->the_patch, vec_size, samp_rate);	
}


// ========================================================================================================================================== //
// Patcher Link Inlets / Outlets
// ========================================================================================================================================== //

void hoa_processor_init_io_infos(t_io_infos* io_infos)
{
	io_infos->sig_ins = 0;
	io_infos->sig_outs = 0;
	io_infos->ins = 0;
	io_infos->outs = 0;
	
	io_infos->sig_ins_maxindex = 0;
	io_infos->sig_outs_maxindex = 0;
	io_infos->ins_maxindex = 0;
	io_infos->outs_maxindex = 0;
	
	io_infos->extra_sig_ins = 0;
	io_infos->extra_sig_outs = 0;
	io_infos->extra_ins = 0;
	io_infos->extra_outs = 0;
	
	io_infos->extra_sig_ins_maxindex = 0;
	io_infos->extra_sig_outs_maxindex = 0;
	io_infos->extra_ins_maxindex = 0;
	io_infos->extra_outs_maxindex = 0;
}

t_hoa_err hoa_processor_get_patch_filename_io_context(t_hoa_processor *x, t_symbol *patch_name_in, t_io_infos* io_infos)
{
	t_fourcc type;
	t_fourcc filetypelist = 'JSON';
	
	short patch_path;
	char filename[MAX_FILENAME_CHARS];
	t_patcher *p;
	
	hoa_processor_init_io_infos(io_infos);
	
	if (!patch_name_in)
	{
		//object_warn((t_object*)x, "no patch name entered");
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FILE_NOT_FOUND;
	}
	
	// Check that this object is not loading in another thread
	
	if (ATOMIC_INCREMENT_BARRIER(&x->patch_is_loading) > 1)
	{
		object_error((t_object*)x, "patch is loading in another thread");
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FAIL;
	}
	
	// Try to locate a file of the given name that is of the correct type
	
	strncpy_zero(filename, patch_name_in->s_name, MAX_FILENAME_CHARS);
	
	// if filetype does not exists
	if (locatefile_extended(filename, &patch_path, &type, &filetypelist, 1))
	{
		object_error((t_object*)x, "patcher \"%s\" not found !", filename);
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FILE_NOT_FOUND;
	}
	
	// Load the patch
	p = (t_patcher*) intload(filename, patch_path, 0, 0, NULL, false);
	
	// Check something has loaded
	
	if (!p)
	{
		object_error((t_object*)x, "error loading %s", filename);
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FAIL;
	}
	
	// Check that it is a patcher that has loaded
	
	if (!ispatcher((t_object*)p))
	{
		object_error((t_object*)x, "%s is not a patcher file", filename);
		object_free((t_object *)p);
		hoa_processor_loadexit(x, 0, 0, 0);
		return HOA_ERR_FAIL;
	}
	
	// no error, so we can check our IO context
	
	hoa_processor_get_patch_io_context(p, io_infos);
	
	object_free((t_object *)p);
	
	hoa_processor_loadexit(x, 0, 0, 0);
	return HOA_ERR_NONE;
}

short hoa_processor_get_patch_io_context(t_patcher *p, t_io_infos* io_infos)
{
	t_box *b;
	t_object *io;
	t_symbol* objclassname;
	long extra;
	
	hoa_processor_init_io_infos(io_infos);
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))
	{
		objclassname = jbox_get_maxclass(b);
		
		if (objclassname == hoa_sym_sigin || objclassname == hoa_sym_in ||
			objclassname == hoa_sym_sigout || objclassname == hoa_sym_out)
		{
			extra = 0;
			io = jbox_get_object(b);
			
			extra = object_attr_getlong(io, hoa_sym_extra);
			
			if (objclassname == hoa_sym_sigin)
			{
				if (extra > 0) io_infos->extra_sig_ins++;
				else io_infos->sig_ins++;
				
				io_infos->extra_sig_ins_maxindex = max(extra, io_infos->extra_sig_ins_maxindex);
			}
			else if (objclassname == hoa_sym_in)
			{
				if (extra > 0) io_infos->extra_ins++;
				else io_infos->ins++;
				
				io_infos->extra_ins_maxindex = max(extra, io_infos->extra_ins_maxindex);
			}
			else if (objclassname == hoa_sym_sigout)
			{
				if (extra > 0) io_infos->extra_sig_outs++;
				else io_infos->sig_outs++;
				
				io_infos->extra_sig_outs_maxindex = max(extra, io_infos->extra_sig_outs_maxindex);
			}
			else if (objclassname == hoa_sym_out)
			{
				if (extra > 0) io_infos->extra_outs++;
				else io_infos->outs++;
				
				io_infos->extra_outs_maxindex = max(extra, io_infos->extra_outs_maxindex);
			}
		}
    }
	
	return 0;
}

// - inlet linking and removal using hoa.in object

short hoa_processor_linkinlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))
	{
		if (jbox_get_maxclass(b) == hoa_sym_in) 
		{
			io = (t_inout *) jbox_get_object(b);
						
			if (io->s_index <= x->declared_ins)
				outlet_add(x->in_table[io->s_index - 1], (struct inlet *)io->s_obj.o_outlet);
		}
    }
	return 0;
}

short hoa_processor_unlinkinlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b)) 
	{
		if (jbox_get_maxclass(b) == hoa_sym_in) 
		{
			io = (t_inout *) jbox_get_object(b);
			
			if (io->s_index <= x->declared_ins)
			{
				outlet_rm(x->in_table[io->s_index - 1], (struct inlet *)io->s_obj.o_outlet);
			}
		}
    }
	return (0);
}

// ========================================================================================================================================== //
// Patcher Window stuff
// ========================================================================================================================================== //


void hoa_processor_dblclick(t_hoa_processor *x)
{
	long i;
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
	{
		if (x->patch_space_ptrs[i]->the_patch)
		{
			hoa_processor_open(x, i + 1);
			break;
		}
	}
}

void hoa_processor_open(t_hoa_processor *x, long index)
{
	t_atom a;
	atom_setlong (&a, index - 1);
	
	if (index < 1) return;
	if (index > x->patch_spaces_allocated) return;
	if (!x->patch_space_ptrs[index - 1]->patch_valid) return;
	
	defer(x,(method)hoa_processor_doopen, 0L, 1, &a);
}

void hoa_processor_doopen(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	long index = atom_getlong(argv);
	
	if (x->patch_space_ptrs[index]->the_patch)
		mess0((t_object *)x->patch_space_ptrs[index]->the_patch, hoa_sym_front);		// this will always do the right thing
}

void hoa_processor_wclose(t_hoa_processor *x, long index)
{
	t_atom a;
	atom_setlong (&a, index - 1);
	
	defer(x,(method)hoa_processor_dowclose, 0L, 1, &a);
}

void hoa_processor_dowclose(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	long index = atom_getlong(argv);
	
	if (index < 0) return;
	if (index >= x->patch_spaces_allocated) return;
	if (!x->patch_space_ptrs[index]->patch_valid) return;
	
	if (x->patch_space_ptrs[index]->the_patch)
	object_method(x->patch_space_ptrs[index]->the_patch, gensym("wclose"), x);
}


// ========================================================================================================================================== //
// Patcher Utilities (these deal with various updating and necessary behind the scens state stuff)
// ========================================================================================================================================== //


short hoa_processor_patcher_descend(t_patcher *p, t_intmethod fn, void *arg, t_hoa_processor *x)
{
	t_box *b;
	t_patcher *p2;
	long index;
	t_object *assoc = NULL;
	object_method(p, hoa_sym_getassoc, &assoc);				// Avoid recursion into a poly / pfft / hoa.process~
	if (assoc && (t_hoa_processor *) assoc != x) 
		return 0;

	// CHANGED - DO NOT PASS x AS ARG
	if ((*fn)(p, arg))
		return (1);

	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))  
	{
		if (b) 
		{
			index = 0;
			while ((p2 = (t_patcher*)object_subpatcher(jbox_get_object(b), &index, arg)))
				if (hoa_processor_patcher_descend(p2, fn, arg, x))
					return 1;
		}
	}
	
	return (0);
}

short hoa_processor_setsubassoc(t_patcher *p, t_hoa_processor *x)
{
	t_object *assoc;
	object_method(p, hoa_sym_getassoc, &assoc);
	if (!assoc)
		object_method(p, hoa_sym_setassoc, x);
	object_method(p, hoa_sym_noedit, 1);
	
	return 0;
}

void hoa_processor_pupdate(t_hoa_processor *x, void *b, t_patcher *p)
{
	t_patchspace *patch_space_ptr;
	
	// Reload the patcher when it's updated
	
	for (int i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		if (patch_space_ptr->the_patch == p)
			hoa_processor_loadpatch (x, i, patch_space_ptr->patch_name_in, patch_space_ptr->x_argc, patch_space_ptr->x_argv);
	}
}

void *hoa_processor_subpatcher(t_hoa_processor *x, long index, void *arg)
{
	if (arg && (long) arg != 1)
		if (!OB_INVALID(arg))										// arg might be good but not a valid object pointer
			if (object_classname(arg) == hoa_sym_dspchain)				// don't report subpatchers to dspchain
				return 0;
	
	if (index < x->patch_spaces_allocated)
		if (x->patch_space_ptrs[index]->patch_valid) return x->patch_space_ptrs[index]->the_patch;		// the indexed patcher

	return 0;
}

void hoa_processor_parentpatcher(t_hoa_processor *x, t_patcher **parent)
{
	*parent = x->parent_patch;
}

// ========================================================================================================================================== //
// Patchspace Utilities
// ========================================================================================================================================== //

// Make a new patchspace

t_patchspace *hoa_processor_new_patch_space (t_hoa_processor *x,long index)
{
	t_patchspace *patch_space_ptr;
	
	x->patch_space_ptrs[index] = patch_space_ptr = (t_patchspace *)t_getbytes(sizeof(t_patchspace));
	
	hoa_processor_init_patch_space (patch_space_ptr);
	x->patch_spaces_allocated++;
	
	return patch_space_ptr;
}


// Initialise a patchspace 

void hoa_processor_init_patch_space (t_patchspace *patch_space_ptr)
{		
	patch_space_ptr->the_patch = 0;
	patch_space_ptr->patch_name_in = 0;
	patch_space_ptr->patch_path = 0;
	patch_space_ptr->patch_valid = 0;
	patch_space_ptr->patch_on = 0;
	patch_space_ptr->the_dspchain = 0;
	patch_space_ptr->x_argc = 0;
	patch_space_ptr->out_ptrs = 0;
}

// Free the patch and dspchain

void hoa_processor_free_patch_and_dsp (t_hoa_processor *x, t_patchspace *patch_space_ptr)
{
	// free old patch and dspchain
	
	if (patch_space_ptr->the_dspchain)
		object_free((t_object *)patch_space_ptr->the_dspchain);
	
	if (patch_space_ptr->the_patch)
	{
		
		if (x->declared_ins)
			hoa_processor_patcher_descend(patch_space_ptr->the_patch, (t_intmethod) hoa_processor_unlinkinlets, x, x);
		
		object_free((t_object *)patch_space_ptr->the_patch);
	}
}


// ========================================================================================================================================== //
// Parent / Child Communication - Routines for owned objects to query the parent
// ========================================================================================================================================== //


// Note that objects wishing to query the parent hoa.process~ object should call the functions in hoa.process.h.
// These act as suitable wrappers to send the appropriate message to the parent object and returns values as appropriate


////////////////////////////////////////////////// Signal IO Queries //////////////////////////////////////////////////


void *hoa_processor_query_declared_sigins(t_hoa_processor *x)
{
	return (void *) x->declared_sig_ins;
}

void *hoa_processor_query_declared_sigouts(t_hoa_processor *x)
{
	return (void *) x->declared_sig_outs;
}

void *hoa_processor_query_sigins(t_hoa_processor *x)
{
	return (void *) x->sig_ins;
}

void *hoa_processor_query_outptrs_ptr(t_hoa_processor *x, long index)
{
	if (index <= x->patch_spaces_allocated)
		return &x->patch_space_ptrs[index - 1]->out_ptrs;
	else
		return 0;
}

void* hoa_processor_query_io_index(t_hoa_processor *x, long patchIndex, t_object* io)
{
	long io_index = -1;
	long extra;
	
	t_symbol* objclassname = object_classname(io);
	
	if (objclassname == hoa_sym_in || (objclassname == hoa_sym_out) ||
		(objclassname == hoa_sym_sigin) || (objclassname == hoa_sym_sigout))
	{
		extra = object_attr_getlong(io, hoa_sym_extra);
		
		//post("query ins -- patchIndex = %ld, extra = %ld", patchIndex, extra);
		
		if (objclassname == hoa_sym_in)
		{
			if ( extra > 0 && extra <= x->extra_ins)
			{
				if (x->instance_ins >= x->instance_sig_ins)
					io_index = x->instance_ins + extra;
				else if (x->instance_ins < x->instance_sig_ins)
					io_index = x->instance_sig_ins + extra;
			}
			else
				io_index = patchIndex;
			
			if (io_index < 1 || io_index > x->declared_ins)
				io_index = -1;
		}
		else if (objclassname == hoa_sym_out)
		{
			if ( extra > 0 && extra <= x->extra_outs)
				io_index = x->instance_outs + extra;
			else
				io_index = patchIndex;
			
			if (io_index < 1 || io_index > x->declared_outs)
				io_index = -1;
		}
		else if(objclassname == hoa_sym_sigin)
		{
			if ( extra > 0 && extra <= x->extra_sig_ins)
			{
				if (x->instance_sig_ins >= x->instance_ins)
					io_index = x->instance_sig_ins + extra;
				else if (x->instance_sig_ins < x->instance_ins)
					io_index = x->instance_ins + extra;
			}
			else
				io_index = patchIndex;
		}
		else if(objclassname == hoa_sym_sigout)
		{
			if ( extra > 0 && extra <= x->extra_sig_outs)
			{
				io_index = x->instance_sig_outs + extra;
			}
			else
				io_index = patchIndex;
			
			if (io_index < 1 || io_index > x->declared_sig_outs)
				io_index = -1;
		}
		
		//object_post((t_object*)io,"query ins -- io_index = %ld", io_index);
	}
	
	return (void*) io_index;
}

//////////////////////////////////////////////////// State Queries ////////////////////////////////////////////////////

void hoa_processor_client_set_patch_on (t_hoa_processor *x, long index, long state)
{
	if (state) state = 1;
	if (index <= x->patch_spaces_allocated)
		x->patch_space_ptrs[index - 1]->patch_on = state;
}

void *hoa_processor_query_ambisonic_order(t_hoa_processor *x)
{
	long order = x->f_ambi2D->getOrder();
	return (void *) order;
}

void *hoa_processor_query_mode(t_hoa_processor *x)
{
	return (void *) x->f_mode;
}

void *hoa_processor_query_number_of_instances(t_hoa_processor *x)
{
	return (void *) (x->patch_spaces_allocated);
}

void *hoa_processor_query_is_2D(t_hoa_processor *x)
{
	return (void *) (x->f_object_type == HOA_OBJECT_2D);
}

t_hoa_err hoa_processor_query_patcherargs(t_hoa_processor *x, long index, long *argc, t_atom **argv)
{
	argc[0] = 0;
	argv[0] = NULL;
	if (index > 0 && index <= x->patch_spaces_allocated)
	{
		long ac = x->patch_space_ptrs[index - 1]->x_argc;
		argc[0] = ac;
		argv[0] = (t_atom *) malloc(ac * sizeof(t_atom) );
		for (int i = 0; i < ac; i++)
			argv[0][i] = x->patch_space_ptrs[index - 1]->x_argv[i];
		
		return HOA_ERR_NONE;
	}
	
	return HOA_ERR_OUT_OF_MEMORY;
}

void *hoa_processor_client_get_patch_on (t_hoa_processor *x, long index)
{
	if (index <= x->patch_spaces_allocated)
		return (void *) (long) x->patch_space_ptrs[index - 1]->patch_on;
	
	return 0;
}