/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// based on dynamicdsp~ Copyright 2010 Alex Harker. All rights reserved.

#include "../hoa.max.h"

#ifdef __APPLE__
#include <pthread.h>
#include <mach/semaphore.h>
#include <mach/task.h>
#else
#include <Windows.h>
#define snprintf _snprintf
#endif 

#include "AH_Headers.h" // concatenated AH headers
#include "hoa.process~.h"

// ========================================================================================================================================== //
// Global Varibles and defines
// ========================================================================================================================================== //

t_class *hoa_processor_class;

static long processor_num_actual_threads;

#define SIG_SIZE sizeof(double)
#define MAX_NUM_PATCHES 4096
#define MAX_ARGS 16

// ========================================================================================================================================== //
// Structures and typedefs
// ========================================================================================================================================== //

/////////////////////////////////// Generic in/out void pointer //////////////////////////////////

typedef void *t_outvoid;

///////////////////////////// Generic stureture for an in/out object /////////////////////////////

typedef struct _inout
{
	t_object s_obj;
	
	long s_index;
	void *s_outlet;
	
} t_inout;

////////// Structure for passing arguments to patchers when targeting particular patches /////////

typedef struct _args_struct
{
	t_symbol *msg;
	short argc; 
	t_atom *argv;
	
	long index;
	
} t_args_struct;

////////////////////////////// Structure for patch and related data //////////////////////////////

typedef struct _patchspace
{
	// Patch and dspchain
	
	t_patcher *the_patch;
	struct _dspchain *the_dspchain;
	
	// Patch Variables 
	
	t_symbol *patch_name_in;
	
	char patch_name[256];
	
	short patch_path;
	
	// Arguments (stored in case of reload / update)
	
	short x_argc;
	t_atom x_argv[MAX_ARGS];
	
	// Pointer to Audio Out Buffers (which are thread dependent)
	
	void **out_ptrs;
	
	// Flags
	
	char patch_valid;
	char patch_on;
	char patch_busy;
	
	t_int32_atomic processed_flag;	
	
	// Threading Variables
	
	long thread_current;
	long thread_request;
	
	// Temporary Memory Variables
	
	long required_temp_mem_size;
	void *temp_mem_ptr;
		
} t_patchspace;


////////////////////////////// Structure for thread and related data /////////////////////////////

typedef struct thread_space {
	
	// Thread and Semaphores
	
#ifdef __APPLE__
	pthread_t pth;
#else
	HANDLE pth;
	long exiting;
#endif

	t_int32_atomic processed;
	
	// Internal Buffer Pointer
	
	void **thread_temp_buffer;
	
	// Temporary Memory For Objects Within Patch
	
	long temp_mem_size;
	void *temp_mem_ptr;
	
	void *first_thread_space;
	
	// Variables
	
	void *hoa_processor_parent;
	
	long thread_num;
	long vec_size;
	
} t_threadspace;


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
	
	long declared_sig_ins;
	long declared_sig_outs;
	long declared_ins;
	long declared_outs;
	
	void **sig_ins;
	void **sig_outs;
	
	t_outvoid *in_table;			// table of non-signal inlets
	t_outvoid *out_table;			// table of non-signal outlets
	long num_proxies;				// number of proxies = MAX(declared_sig_ins, declared_ins)
	
	// Multithreading Variables
	
	long multithread_flag;
	
	long request_num_active_threads;
	long num_active_threads;
	
	long request_manual_threading;
	long manual_threading;
	long update_thread_map;
	
	long max_obj_threads;
	
#ifdef __APPLE__
	task_t the_task;
	semaphore_t tick_semaphore;	
#else
	HANDLE tick_semaphore;
#endif
	
	// Thread Data
	
	t_threadspace *thread_space_ptr; 
	
	long thread_temp_buffer_size;

	// Temporary Memory Variables
	
	t_safe_mem_swap temp_mem;
	
	// Hoa stuff
	Hoa3D::Ambisonic*   f_ambisonic;
	
} t_hoa_processor;

// ========================================================================================================================================== //
// Function Prototypes
// ========================================================================================================================================== //


void *hoa_processor_new(t_symbol *s, short argc, t_atom *argv);
void hoa_processor_free(t_hoa_processor *x);
void hoa_processor_assist(t_hoa_processor *x, void *b, long m, long a, char *s);

void hoa_processor_deletepatch (t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_processor_deletepatch_internal (t_hoa_processor *x, long index);
void hoa_processor_cleanpatch(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_loadexit(t_hoa_processor *x, long replace_symbol_pointers, void *previous, void *previousindex);
void hoa_processor_loadpatch (t_hoa_processor *x, long index, long thread_request,  t_symbol *patch_name_in, short argc, t_atom *argv);
void hoa_processor_user_clear (t_hoa_processor *x);
void hoa_processor_user_loadpatch (t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);

void hoa_processor_bang(t_hoa_processor *x);
void hoa_processor_int(t_hoa_processor *x, long n);
void hoa_processor_float(t_hoa_processor *x, double f);
void hoa_processor_list(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_anything(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_target(t_hoa_processor *x, long target_index, long index, t_symbol *msg, short argc, t_atom *argv);
short hoa_processor_targetinlets(t_patcher *p, t_args_struct *args);
void hoa_processor_user_target(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_processor_user_target_free(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);

void hoa_processor_autoloadbalance(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_processor_multithread(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_processor_activethreads(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);
void hoa_processor_threadmap(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv);

void hoa_processor_free_temp_memory(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv);
void hoa_processor_perform_common(t_hoa_processor *x, void **sig_outs, long vec_size);
t_int *hoa_processor_perform(t_int *w);
void hoa_processor_perform64 (t_hoa_processor *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam);
void hoa_processor_sum_float(t_threadspace *thread_space_ptr, void **sig_outs, long declared_sig_outs, long vec_size, long num_active_threads);
void hoa_processor_sum_double(t_threadspace *thread_space_ptr, void **sig_outs, long declared_sig_outs, long vec_size, long num_active_threads);
__inline void hoa_processor_multithread_perform(t_hoa_processor *x, void **sig_outs, long declared_sig_outs, long vec_size, long num_active_threads);
#ifdef __APPLE__
void *hoa_processor_threadwait(void *arg);
#else
DWORD WINAPI hoa_processor_threadwait (LPVOID arg);
#endif
__inline void hoa_processor_threadprocess(t_hoa_processor *x, void **sig_outs, void *temp_mem_ptr, long temp_mem_size, long vec_size, long thread_num, long threads_running);

long hoa_processor_dsp_common(t_hoa_processor *x, long vec_size, long samp_rate);
void hoa_processor_dsp64 (t_hoa_processor *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_processor_dsp_internal (t_patchspace *patch_space_ptrs, long vec_size, long samp_rate);

short hoa_processor_linkinlets(t_patcher *p, t_hoa_processor *x);
short hoa_processor_linkoutlets(t_patcher *p, t_hoa_processor *x);
short hoa_processor_unlinkinlets(t_patcher *p, t_hoa_processor *x);
short hoa_processor_unlinkoutlets(t_patcher *p, t_hoa_processor *x);

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
void *hoa_processor_client_get_patch_busy (t_hoa_processor *x, long index);
void hoa_processor_client_set_patch_on (t_hoa_processor *x, long index, long state);
void hoa_processor_client_set_patch_busy (t_hoa_processor *x, long index, long state);
void *hoa_processor_query_temp_mem (t_hoa_processor *x, long index);
void *hoa_processor_client_temp_mem_resize (t_hoa_processor *x, long index, long size);

t_hoa_err hoa_getinfos(t_hoa_processor* x, t_hoa_boxinfos* boxinfos);

// ========================================================================================================================================== //
// Symbols
// ========================================================================================================================================== //


t_symbol *ps_HoaProcessor;
t_symbol *ps_HoaProcessorPatchIndex;
t_symbol *ps_dspchain;
t_symbol *ps_sigin;
t_symbol *ps_sigout;
t_symbol *ps_bpatcher;
t_symbol *ps_patcher;
t_symbol *ps_front;
t_symbol *ps_in;
t_symbol *ps_out;
t_symbol *ps_bang;
t_symbol *ps_int;
t_symbol *ps_float;
t_symbol *ps_list;
t_symbol *ps_args;

t_symbol *ps_getassoc;
t_symbol *ps_setassoc;
t_symbol *ps_noedit;


// ========================================================================================================================================== //
// Main
// ========================================================================================================================================== //

int C74_EXPORT main(void)
{
#ifdef __APPLE__
	processor_num_actual_threads = 1;
	//processor_num_actual_threads = MPProcessors(); // harker version
	//Gestalt(gestaltCountOfCPUs, &processor_num_actual_threads);
	//#include "omx.h"
	//omp_get_max_threads
#else
	SYSTEM_INFO sysinfo;
	GetSystemInfo( &sysinfo );
	processor_num_actual_threads = sysinfo.dwNumberOfProcessors;
#endif
	
	t_class* c;

	c = class_new("hoa.process~", (method)hoa_processor_new,  (method)hoa_processor_free, sizeof(t_hoa_processor), NULL, A_GIMME, 0);
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_processor_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_open, "open", A_DEFLONG, 0);
	class_addmethod(c, (method)hoa_processor_dblclick, "dblclick", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_wclose, "wclose", A_DEFLONG, 0);
	
	class_addmethod(c, (method)hoa_processor_pupdate, "pupdate", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_subpatcher, "subpatcher", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_parentpatcher, "parentpatcher", A_CANT, 0);
	
	class_addmethod(c, (method)hoa_processor_bang, "bang", 0);
	class_addmethod(c, (method)hoa_processor_int, "int", A_LONG, 0);
	class_addmethod(c, (method)hoa_processor_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)hoa_processor_list, "list", A_GIMME, 0);
	class_addmethod(c, (method)hoa_processor_anything, "anything", A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_processor_autoloadbalance, "autoloadbalance", A_GIMME, 0);				// MUST FIX TO GIMME FOR NOW
	class_addmethod(c, (method)hoa_processor_multithread, "multithread", A_GIMME, 0);						// MUST FIX TO GIMME FOR NOW
	class_addmethod(c, (method)hoa_processor_activethreads, "activethreads", A_GIMME, 0);					// MUST FIX TO GIMME FOR NOW
	class_addmethod(c, (method)hoa_processor_threadmap, "threadmap", A_GIMME, 0);							// MUST FIX TO GIMME FOR NOW
	
	class_addmethod(c, (method)hoa_processor_user_clear, "clear", 0);
	class_addmethod(c, (method)hoa_processor_user_loadpatch, "loadpatch", A_GIMME, 0);
	class_addmethod(c, (method)hoa_processor_deletepatch, "deletepatch", A_GIMME, 0);						// MUST FIX TO GIMME FOR NOW
	class_addmethod(c, (method)hoa_processor_user_target, "target", A_GIMME, 0);							// MUST FIX TO GIMME FOR NOW
	class_addmethod(c, (method)hoa_processor_user_target_free, "targetfree", A_GIMME, 0);					// MUST FIX TO GIMME FOR NOW
	
	class_addmethod(c, (method)hoa_processor_query_declared_sigins, "get_declared_sigins", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_declared_sigouts, "get_declared_sigouts", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_sigins, "get_sigins", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_outptrs_ptr, "get_outptrs_ptr", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_get_patch_on, "get_patch_on", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_get_patch_busy, "get_patch_busy", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_set_patch_on, "set_patch_on", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_set_patch_busy, "set_patch_busy", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_query_temp_mem, "get_temp_mem", A_CANT, 0);
	class_addmethod(c, (method)hoa_processor_client_temp_mem_resize, "temp_mem_resize", A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_processor_class = c;
	
	ps_getassoc = gensym("getassoc");
	ps_setassoc = gensym("setassoc");
	ps_noedit = gensym("noedit");
	
	ps_HoaProcessor = gensym("___HoaProcessor~___");						// Capitals must stay here
	ps_HoaProcessorPatchIndex = gensym("___HoaProcessorPatchIndex___");		// Capitals must stay here
	ps_dspchain = gensym("dspchain");	
	ps_sigin = gensym("in~");
	ps_sigout = gensym("out~");
	ps_bpatcher = gensym("bpatcher");
	ps_patcher = gensym("patcher");
	ps_front = gensym("front");
	ps_in = gensym("in");
	ps_out = gensym("out");
	ps_bang = gensym("bang");
	ps_int = gensym("int");
	ps_float = gensym("float");
	ps_list = gensym("list");
	ps_args = gensym("args");
	
	return 0;
}


// ========================================================================================================================================== //
// Object Creation / Freeing / Assisstance
// ========================================================================================================================================== //


void *hoa_processor_new(t_symbol *s, short argc, t_atom *argv)
{	
	t_hoa_processor *x = (t_hoa_processor*)object_alloc (hoa_processor_class);
	
	t_symbol *patch_name_entered = 0;
	t_symbol *tempsym;
	int ambisonicOrder = 1;
	
	short ac = 0;
	t_atom av[MAX_ARGS];						
	
	x->max_obj_threads = processor_num_actual_threads;
	
#ifdef __APPLE__
	pthread_attr_t tattr;
	struct sched_param param;
	int newprio = 63;		
#endif

	long i, j;
	
	// Check if there is a patch name given to load
	if (argc && atom_gettype(argv) == A_LONG)
	{
		ambisonicOrder = atom_getlong(argv);
		argc--; argv++;
	}
	
	// Check if there is a patch name given to load
	if (argc && atom_gettype(argv) == A_SYM)
	{
		patch_name_entered = atom_getsym(argv);
		argc--; argv++;
	}
	
	// Get arguments to patch that is being loaded if there are any
	if (argc && atom_gettype(argv) == A_SYM) 
	{
		tempsym = atom_getsym(argv);
		argc--; argv++;
		if (tempsym == ps_args) 
		{				
			ac = argc;
			if (ac > MAX_ARGS)
				ac = MAX_ARGS;
			for (i = 0; i < ac; i++, argv++)
				av[i] = *argv;
			ac = i;
		}
	}
	
	// Set other variables to defaults
	
	x->f_ambisonic = new Hoa3D::Ambisonic(ambisonicOrder);
	x->declared_sig_ins = x->declared_sig_outs = x->f_ambisonic->getNumberOfHarmonics();
	x->declared_ins = 0;
	x->declared_outs = 0;
	
	x->patch_spaces_allocated = 0;
	x->update_thread_map = 0;
	x->target_index = 0;
	
	x->last_vec_size = 64;
	x->last_samp_rate = 44100;
	
	x->in_table = 0;
	x->out_table = 0;
	
	x->patch_is_loading = 0;
	
	// Create signal in/out buffers and zero
	
	x->sig_ins = (void **) ALIGNED_MALLOC (x->declared_sig_ins * sizeof(void *));
	x->sig_outs = (void **) ALIGNED_MALLOC (x->declared_sig_outs * sizeof(void *));
	
	for (i = 0; i < x->declared_sig_ins; i++)
		x->sig_ins[i] = 0;
	for (i = 0; i < x->declared_sig_outs; i++)
		x->sig_outs[i] = 0;
	
	// Make non-signal outlets first
	
	if (x->declared_outs)
	{
		x->out_table = (t_outvoid *) t_getbytes(x->declared_outs * sizeof(t_outvoid));
		for (i = x->declared_outs - 1; i >= 0; i--)
			x->out_table[i] = outlet_new((t_object *)x, 0);
	}
	
	// Make non-signal inlets
	
	if (x->declared_ins)
	{
		x->in_table = (t_outvoid *)t_getbytes(x->declared_ins * sizeof(t_outvoid));
		for (i = 0; i < x->declared_ins; i++)
			x->in_table[i] = outlet_new(0L, 0L);											// make generic unowned inlets
	}
	
	// Make signal ins
	
	x->num_proxies = (x->declared_sig_ins > x->declared_ins) ? x->declared_sig_ins : x->declared_ins;
	
	dsp_setup((t_pxobject *) x, x->num_proxies);
	x->x_obj.z_misc = Z_NO_INPLACE;															// due to output zeroing!!
	
	// Make signal outs
	
	for (i = 0; i < x->declared_sig_outs; i++)
		outlet_new((t_object *)x, "signal");
	
	// Initialise patcher symbol
	
	x->parent_patch = (t_patcher *)gensym("#P")->s_thing;									// store reference to parent patcher
	
	// Load patches and initialise it for all harmonics
		
	if (patch_name_entered)
	{
		for (i=0; i<x->f_ambisonic->getNumberOfHarmonics(); i++)
			hoa_processor_loadpatch(x, i, -1, patch_name_entered, ac, av);
	}
	
	// --------------------
	// Multithreading Setup - defaults to multi-threading off for nested objects, on for non-nested
	// --------------------
	
	if (Get_HoaProcessor_Object()) 
		x->multithread_flag = 0;									
	else 
		x->multithread_flag = 1;
	
#ifdef __APPLE__
	x->the_task = mach_task_self();
#endif

	// Multithreading variables
	
	x->thread_space_ptr = (t_threadspace *) ALIGNED_MALLOC (x->max_obj_threads * sizeof(t_threadspace));
	x->manual_threading = 1;
	x->request_manual_threading = 1;
	x->request_num_active_threads = x->max_obj_threads;
	x->thread_temp_buffer_size = 0;
	
	// Setup temporary memory 
	
	alloc_mem_swap(&x->temp_mem, 0, 0);
				
	// Create and eetup each threads variables
	
	for (i = 0; i < x->max_obj_threads; i++)
	{
		x->thread_space_ptr[i].pth = 0;
		x->thread_space_ptr[i].thread_temp_buffer = (void**)ALIGNED_MALLOC (x->declared_sig_outs * sizeof(void *));
		x->thread_space_ptr[i].temp_mem_ptr = 0;
		x->thread_space_ptr[i].hoa_processor_parent = x;
		x->thread_space_ptr[i].thread_num = i;
		x->thread_space_ptr[i].first_thread_space = x->thread_space_ptr;
		
		for (j = 0; j < x->declared_sig_outs; j++)
			x->thread_space_ptr[i].thread_temp_buffer[j] = 0;
	}
	
	// Create the extra threads and associated semaphores (thread zero is the main audio thread)

#ifdef __APPLE__	
	semaphore_create (x->the_task, &x->tick_semaphore, 0, 0);
#else
	//x->tick_semaphore  = CreateEvent(NULL, TRUE, FALSE, NULL);
	x->tick_semaphore  = CreateSemaphore(NULL, 0, max_obj_threads - 1, NULL);
#endif 

	for (i = 1; i < x->max_obj_threads; i++)
	{
		x->thread_space_ptr[i].processed = 1;
#ifdef __APPLE__
		pthread_attr_init (&tattr);																// initialized with default attributes 
		pthread_attr_getschedparam (&tattr, &param);											// safe to get existing scheduling param 
		param.sched_priority = newprio;															// set the priority; others are unchanged 
		pthread_attr_setschedparam (&tattr, &param);											// setting the new scheduling param 
		pthread_create(&(x->thread_space_ptr[i].pth), &tattr, hoa_processor_threadwait, x->thread_space_ptr + i);
#else
		x->thread_space_ptr[i].pth = CreateThread (NULL, 0, hoa_processor_threadwait, x->thread_space_ptr + i, 0, NULL);
		SetThreadPriority(x->thread_space_ptr[i].pth, THREAD_PRIORITY_TIME_CRITICAL);
		x->thread_space_ptr[i].exiting = 0;
#endif
	}
	
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_processor* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_ambisonic->getNumberOfHarmonics();//x->num_proxies;
	boxinfos->autoconnect_outputs = x->f_ambisonic->getNumberOfHarmonics();//x->declared_outs;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_processor_free(t_hoa_processor *x)
{
	t_patchspace *patch_space_ptr;
	long thread_temp_buffer_size = x->thread_temp_buffer_size;
	long i, j;
	
	dsp_free((t_pxobject *)x);
	
	// Free semaphores

#ifdef __APPLE__
	semaphore_destroy (x->the_task, x->tick_semaphore);
#else
	for (i = 1; i < x->max_obj_threads; i++)
	{
		x->thread_space_ptr[i].exiting = 1;
		//SetEvent(x->thread_space_ptr[i].tick_semaphore);
	}
	ReleaseSemaphore(x->tick_semaphore, x->max_obj_threads - 1, NULL);
	CloseHandle(x->tick_semaphore);
#endif
	
	// Free thread temporary buffers
	
	if (thread_temp_buffer_size)
	{
		for (i = 0; i < x->max_obj_threads; i++)
		{
			for (j = 0; j < x->declared_sig_outs; j ++)
			{
				if (x->thread_space_ptr[i].thread_temp_buffer[j])
					ALIGNED_FREE (x->thread_space_ptr[i].thread_temp_buffer[j]);
			}
			ALIGNED_FREE (x->thread_space_ptr[i].thread_temp_buffer);
		}
	}	
	
	// Free patches
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		hoa_processor_free_patch_and_dsp (x, patch_space_ptr);
		
		if (patch_space_ptr)
			freebytes((char *) patch_space_ptr, sizeof(t_patchspace));
	}
	
	// Free other resources
	
	free_mem_swap(&x->temp_mem);
	ALIGNED_FREE(x->thread_space_ptr);
	
	if (x->declared_sig_ins)
		ALIGNED_FREE(x->sig_ins);
	
	if (x->declared_sig_outs)
		ALIGNED_FREE(x->sig_outs);
	
	for (i = 0; i < x->declared_ins; i++)
		freeobject((t_object*)x->in_table[i]);
	
	if (x->in_table)
		freebytes(x->in_table, x->declared_ins * sizeof(t_outvoid));
	
	if (x->out_table)
		freebytes(x->out_table, x->declared_outs * sizeof(t_outvoid));
}

void hoa_processor_assist(t_hoa_processor *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_ambisonic->getHarmonicsName(a).c_str());
}


// ========================================================================================================================================== //
// Patcher Loading / Deleting
// ========================================================================================================================================== //


void hoa_processor_deletepatch (t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	hoa_processor_deletepatch_internal(x, argc ? atom_getlong(argv) - 1 : -1); 
}


void hoa_processor_deletepatch_internal (t_hoa_processor *x, long index)
{	
	t_patchspace *patch_space_ptr;
	t_atom a;
	atom_setlong(&a, index);

	if (index < 0 || index >= x->patch_spaces_allocated)
	{
		object_error((t_object*)x, "patch index out of range"); 
		return;
	}
	
	patch_space_ptr = x->patch_space_ptrs[index];
	patch_space_ptr->patch_valid = 0;
	
	defer(x,(method)hoa_processor_cleanpatch, 0L, 1, &a);
}

void hoa_processor_cleanpatch (t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	t_patchspace *patch_space_ptr;
	long index = atom_getlong(argv);
	
	// First close the window
	
	hoa_processor_dowclose(x, 0L, 1, argv);
	
	// Now free
	
	patch_space_ptr = x->patch_space_ptrs[index];
	hoa_processor_free_patch_and_dsp (x, patch_space_ptr);
	hoa_processor_init_patch_space(patch_space_ptr);
}

void hoa_processor_loadexit(t_hoa_processor *x, long replace_symbol_pointers, void *previous, void *previousindex)
{
	if (replace_symbol_pointers)
	{
		ps_HoaProcessor->s_thing = (struct object*)previous;
		ps_HoaProcessorPatchIndex->s_thing = (struct object*)previousindex;
	}
	ATOMIC_DECREMENT_BARRIER(&x->patch_is_loading);
}

void hoa_processor_loadpatch (t_hoa_processor *x, long index, long thread_request, t_symbol *patch_name_in, short argc, t_atom *argv)
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
	void *p;

	// Check that this object is not loading in another thread
	
	if (ATOMIC_INCREMENT_BARRIER(&x->patch_is_loading) > 1)
	{
		object_error((t_object*)x, "patch is loading in another thread");
		hoa_processor_loadexit(x, 0, 0, 0);
		return;
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
		object_error((t_object*)x, "slot out of range");
		hoa_processor_loadexit(x, 0, 0, 0);
		return;
	}
		
	// Create patchspaces up until the last allocated index (if necessary) and store the pointer
	
	for (i = patch_spaces_allocated; i < index + 1; i++)
		hoa_processor_new_patch_space (x, i);
	
	patch_space_ptr = x->patch_space_ptrs[index];
	
	// Free the old patch - the new patch is not yet valid, but we switch it on so it can be switched off at loadbang time
	
	patch_space_ptr->patch_valid = 0;
	hoa_processor_free_patch_and_dsp (x, patch_space_ptr);
	hoa_processor_init_patch_space(patch_space_ptr);
	patch_space_ptr->patch_on = 1;
	
	// Bind to the loading symbols and store the old symbols
	
	previous = ps_HoaProcessor->s_thing;
	previousindex = ps_HoaProcessorPatchIndex->s_thing;
	
	ps_HoaProcessor->s_thing = (t_object *) x;										
	ps_HoaProcessorPatchIndex->s_thing = (t_object *) (index + 1);						
	
	// Try to locate a file of the given name that is of the correct type
	
	strncpy_zero(filename, patch_name_in->s_name, MAX_FILENAME_CHARS);
	
	// if filetype does not exists
	if (locatefile_extended(filename, &patch_path, &type, &filetypelist, 1))
	{
		object_error((t_object*)x, "no patcher %s", filename);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return;
	}
	
	// Check the number of rarguments (only up to 16 allowed right now)
	
	if (argc > MAX_ARGS)
		argc = MAX_ARGS;
	
	// Load the patch (don't interrupt dsp)
	
	saveloadupdate = dsp_setloadupdate(false);
	p = intload(filename, patch_path, 0 , argc, argv, false);
	dsp_setloadupdate(saveloadupdate);
	
	// Check something has loaded
	
	if (!p) 
	{
		object_error((t_object*)x, "error loading %s", filename);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return;
	}
	
	// Check that it is a patcher that has loaded
	
	if (!ispatcher((t_object*)p))
	{
		object_error((t_object*)x, "%s is not a patcher file", filename);
		freeobject((t_object *)p);
		hoa_processor_loadexit(x, 1, previous, previousindex);
		return;
	}
	
	// Change the window name to : "patchname (index) [band arg]"
	
	harmonic_band = x->f_ambisonic->getHarmonicBand(index);
	harmonic_argument = x->f_ambisonic->getHarmonicArgument(index);
	
	snprintf(windowname, 256, "%s (%ld) [%ld %ld]", patch_name_in->s_name, index, harmonic_band, harmonic_argument);
	jpatcher_set_title((t_object*)p, gensym(windowname));
	
	// Set the relevant associations
	hoa_processor_patcher_descend((t_patcher *)p, (t_intmethod) hoa_processor_setsubassoc, x, x);	// associate subpatches with this instance
	
	// Link inlets and outlets
	
	if (x->declared_ins) 
		hoa_processor_patcher_descend((t_patcher *)p, (t_intmethod) hoa_processor_linkinlets, x, x);
	if (x->declared_outs) 
		hoa_processor_patcher_descend((t_patcher *)p, (t_intmethod) hoa_processor_linkoutlets, x, x);
	
	// Copy all the relevant data into the patch space
	
	patch_space_ptr->the_patch = (t_patcher*)p;
	patch_space_ptr->patch_name_in = patch_name_in;
	
	strcpy(patch_space_ptr->patch_name, filename);
	patch_space_ptr->patch_path = patch_path;	
	
	patch_space_ptr->x_argc = argc;
	for (i = 0; i < argc; i++) 
		patch_space_ptr->x_argv[i] = argv[i];
	
	// Set a request for a particular thread
	
	if (thread_request)
	{
		if (thread_request > 0) 
			patch_space_ptr->thread_request = thread_request - 1;
		else 
			patch_space_ptr->thread_request = index;
		x->update_thread_map = 1;
	}
	
	// Compile the dspchain in case dsp is on
	
	hoa_processor_dsp_internal (patch_space_ptr, x->last_vec_size, x->last_samp_rate);
	
	// The patch is valid and ready to go
	
	patch_space_ptr->patch_valid = 1;
	
	// Return to previous state
		
	hoa_processor_loadexit(x, 1, previous, previousindex);
}

void hoa_processor_user_clear (t_hoa_processor *x)
{
	long i;
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
		hoa_processor_deletepatch_internal (x, i);
}

void hoa_processor_user_loadpatch (t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	t_symbol *patch_name_entered = 0;
	
	long index = -1;
	long thread_request = -1;
	
	// Get requested patch index if there is one
	
	if (argc && atom_gettype(argv) == A_LONG)
	{
		index = atom_getlong(argv) - 1;
		if (index >= MAX_NUM_PATCHES) 
		{
			object_error((t_object*)x, "patch index out of range");
			return;
		}
		argc--; argv++;
	}
	
	// Get thread request if there is one
	
	if (argc && atom_gettype(argv) == A_LONG)
	{
		thread_request = atom_getlong(argv);
		argc--; argv++;
	}
	
	// If there is a patch name then try to load the patch
	
	if (argc && atom_gettype(argv) == A_SYM)			
	{
		patch_name_entered = argv->a_w.w_sym;
		argc--; argv++;
		
		hoa_processor_loadpatch (x, index, thread_request, patch_name_entered, argc, argv);
	} 
	else 
		object_error((t_object*)x, "no patch specified");
}

// ========================================================================================================================================== //
// Messages in passed on to the patcher via the "in" objects / Voice targeting
// ========================================================================================================================================== //


void hoa_processor_bang(t_hoa_processor *x)
{	
	long index = proxy_getinlet((t_object *)x);	
	long target_index = x->target_index;
	
	if (index >= x->declared_ins)
		return;

	if (target_index)
		hoa_processor_target(x, target_index, index, ps_bang, 0, 0);
	else
		outlet_bang(x->in_table[index]);
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
		hoa_processor_target(x, target_index, index, ps_int, 1, &n_atom);
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
		hoa_processor_target(x, target_index, index, ps_float, 1, &f_atom);
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
		hoa_processor_target(x, target_index, index, ps_list, argc, argv);
	else
		outlet_list(x->in_table[index], ps_list, argc, argv);
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
	void *outletptr;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b)) 
	{
		if (jbox_get_maxclass(b) == ps_in) 
		{
			io = (t_inout *) jbox_get_object(b);
			if (io->s_index == args->index)
			{
				outletptr = io->s_obj.o_outlet;
				outlet_anything (outletptr, args->msg, args->argc, args->argv);
			}
		}
    }
	return (0);
}

void hoa_processor_user_target(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	long target_index = argc ? atom_getlong(argv) : 0;
	
	x->target_index = target_index;
}

void hoa_processor_user_target_free(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	t_patchspace **patch_space_ptrs;
	
	long val1 = argc > 0 ? atom_getlong(argv + 0) : 0;
	long val2 = argc > 1 ? atom_getlong(argv + 1) : 0;
	long i, from, to;
	long target = 0;
	long patch_spaces_allocated = x->patch_spaces_allocated;
	
	if (val1 > patch_spaces_allocated) 
		val1 = patch_spaces_allocated;
	if (val2 > patch_spaces_allocated) 
		val2 = patch_spaces_allocated;
	
	if (val1 || val2)
	{
		if (val2) 
		{
			from = val1;
			to = val2;
		}
		else
		{
			from = 1;
			to = val1;
		}
	}
	else
	{
		from = 1;
		to = patch_spaces_allocated;
	}
	
	if (from < 1) 
		from = 1;
	
	patch_space_ptrs = x->patch_space_ptrs;
	
	for (i = from - 1; i < to; i++)
	{
		if (patch_space_ptrs[i]->patch_valid && !patch_space_ptrs[i]->patch_busy)
		{
			target = i + 1;
			break;
		}
	}
	
	if (target) 
		x->target_index = target;
	else 
		x->target_index = -1;
}


// ========================================================================================================================================== //
// Multithreading Messages
// ========================================================================================================================================== //


void hoa_processor_autoloadbalance(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	long n = 1;
	
	if (argc)
		n = atom_getlong(argv);
	
	if (!n)
		x->request_manual_threading = 1;
	else
		x->request_manual_threading = 0;
}

void hoa_processor_multithread(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	
	long n = 1;
	
	if (argc)
		n = atom_getlong(argv);
	
	x->multithread_flag = n;
}

void hoa_processor_activethreads(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	long n = x->max_obj_threads;
	
	if (argc)
		n = atom_getlong(argv);
	
	if (n < 1) 
		n = 1;
	if (n > x->max_obj_threads) 
		n = x->max_obj_threads;
	
	x->request_num_active_threads = n;
}

void hoa_processor_threadmap(t_hoa_processor *x, t_symbol *msg, short argc, t_atom *argv)
{
	long index = -1;
	long thread_request = 0;
	
	// Load arguments (and alter index by one to change counting point)
	
	if (argc > 0)
		index = atom_getlong(argv + 0) - 1;
		
	if (argc > 1)
		thread_request = atom_getlong(argv + 1);
		
	if (thread_request && index >= 0 && index < x->patch_spaces_allocated)
	{
		if (thread_request > 0) 
			x->patch_space_ptrs[index]->thread_request = thread_request - 1;
		else 
			x->patch_space_ptrs[index]->thread_request = index;
		x->update_thread_map = 1;
	}
}


// ========================================================================================================================================== //
// Perform and DSP Routines
// ========================================================================================================================================== //


void hoa_processor_free_temp_memory(t_hoa_processor *x, t_symbol *s, short argc, t_atom *argv)
{
	ALIGNED_FREE((void *)s);
}


void hoa_processor_perform_common(t_hoa_processor *x, void **sig_outs, long vec_size)
{
	t_threadspace *thread_space_ptr = x->thread_space_ptr;

	t_patchspace **patch_space_ptrs = x->patch_space_ptrs;
	t_patchspace *next_patch_space_ptr;
	
	void *new_temp_mem_ptr;
	long new_temp_mem_size;
	
	long declared_sig_outs = x->declared_sig_outs;
	long num_active_threads = x->request_num_active_threads;	
	long multithread_flag;
	long i;
	
	x->num_active_threads = num_active_threads;

	// Zero Outputs
	
	for (i = 0; i < declared_sig_outs; i++) 
		memset(sig_outs[i], 0, SIG_SIZE * vec_size);
	
	if (x->x_obj.z_disabled)
		return;

	// Update multithreading parameters (this is done in one thread and before all threads process to ensure uninterrupted audio processing
	
	multithread_flag = (x->patch_spaces_allocated > 1) && x->multithread_flag && (num_active_threads > 1);
	x->manual_threading = x->request_manual_threading;		
	
	if (!x->manual_threading)
	{
		for (i = 0; i < x->patch_spaces_allocated; i++)
			patch_space_ptrs[i]->processed_flag = 0;
	}
	
	if (x->update_thread_map)
	{
		x->update_thread_map = 0;											
		
		for (i = 0; i < x->patch_spaces_allocated; i++)
		{
			next_patch_space_ptr = patch_space_ptrs[i]; 
			next_patch_space_ptr->thread_current = next_patch_space_ptr->thread_request;
		}
	}
	
	// Update the temporary memory if relevant
	
	if (attempt_mem_swap(&x->temp_mem) == SWAP_DONE)
	{
		// Store the new pointers and size
		
		new_temp_mem_ptr = x->temp_mem.current_ptr;
		new_temp_mem_size = x->temp_mem.current_size;
		
		for (i = 0; i < x->max_obj_threads; i++)
		{
			thread_space_ptr[i].temp_mem_ptr = (char *) new_temp_mem_ptr + (new_temp_mem_size * i);
			thread_space_ptr[i].temp_mem_size = new_temp_mem_size;
		}
	}
	
	// Do multithreaded or non-multithread processing - the former case is switched to try to get more speed out of inlining with a fixed loop size
	
	if (multithread_flag)
	{		 
		switch (num_active_threads)
		{				
			case 2:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 2);
				break;
				
			case 3:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 3);
				break;
				
			case 4:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 4);
				break;
				
			case 5:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 5);
				break;
				
			case 6:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 6);
				break;
				
			case 7:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 7);
				break;
				
			case 8:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, 8);
				break;
				
			default:
				hoa_processor_multithread_perform(x, sig_outs, declared_sig_outs, vec_size, num_active_threads);
				break;
		}
	}
	else
		hoa_processor_threadprocess(x, (void **) sig_outs, x->thread_space_ptr[0].temp_mem_ptr, x->thread_space_ptr[0].temp_mem_size, vec_size, 0, 1);	
}

void hoa_processor_perform64 (t_hoa_processor *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long vec_size, long flags, void *userparam)
{		
	long i;
	
	for (i = 0; i < x->declared_sig_ins; i++)
		x->sig_ins[i] = ins[i];
		
	hoa_processor_perform_common(x, (void **) outs, vec_size);
}

void hoa_processor_sum_double(t_threadspace *thread_space_ptr, void **sig_outs, long declared_sig_outs, long vec_size, long num_active_threads)
{
	t_threadspace *next_thread_ptr = 0;
	double *next_sig_pointer;
	double *io_pointer;
	long i, j, k;
	
	// Sum output of threads for each signal outlet
	
	for (i = 0; i < declared_sig_outs; i++) 
	{	
		for (j = 0; j < num_active_threads; j++)
		{
			next_thread_ptr = thread_space_ptr + j;
			next_sig_pointer = (double*)next_thread_ptr->thread_temp_buffer[i];
			io_pointer = (double*)sig_outs[i];
			
			for (k = 0; k < vec_size; k++)
				*(io_pointer++) += *(next_sig_pointer++);
		}	
	} 
}


__inline void hoa_processor_multithread_perform(t_hoa_processor *x, void **sig_outs, long declared_sig_outs, long vec_size, long num_active_threads)
{
	t_threadspace *thread_space_ptr = x->thread_space_ptr;	
	long i;
	
	for (i = 1; i < num_active_threads; i++)
		thread_space_ptr[i].processed = 0;	
	
	// Tick the worker threads and process in this thread (the main audio thread)
	
#ifdef __APPLE__

	OSMemoryBarrier();

	for (i = 1; i < num_active_threads; i++)
		semaphore_signal (x->tick_semaphore);		
#else

	MemoryBarrier();
	ReleaseSemaphore(x->tick_semaphore, num_active_threads - 1, NULL);
	
#endif		
	
	// Process thread
	hoa_processor_threadprocess(x, thread_space_ptr->thread_temp_buffer, thread_space_ptr->temp_mem_ptr, thread_space_ptr->temp_mem_size, vec_size, 0, num_active_threads);		
	
	// Wait for all the other threads to return
	for (i = 1; i < num_active_threads; i++)
		while (thread_space_ptr[i].processed != 1);
			
	// Sum outputs
	hoa_processor_sum_double(thread_space_ptr, sig_outs, declared_sig_outs, vec_size, num_active_threads);
}


#ifdef __APPLE__
void *hoa_processor_threadwait(void *arg)
#else
DWORD WINAPI hoa_processor_threadwait(LPVOID arg)
#endif
{
	t_hoa_processor *x = (t_hoa_processor *) ((t_threadspace *) arg)->hoa_processor_parent;
	t_threadspace *thread_ptrs = (t_threadspace *)((t_threadspace *) arg)->first_thread_space;
	t_threadspace *this_thread;
	t_threadspace *constant_thread;
	long thread_num = ((t_threadspace *) arg)->thread_num;
	long current_thread_num;
	long num_active_threads;
	long i;
	
	constant_thread = thread_ptrs + thread_num;

	while(1)
	{
#ifdef __APPLE__
		kern_return_t tick_return = semaphore_wait(x->tick_semaphore);						
		if (tick_return == KERN_TERMINATED)
			break;
#else
		WaitForSingleObject(x->tick_semaphore, INFINITE);
		if (constant_thread->exiting)
			break;
#endif
		
		num_active_threads = x->num_active_threads;
		
		for (i = thread_num; i < thread_num + num_active_threads - 1; i++)
		{
			// N.B. Get values from thread each time in case they have been changed
			
			current_thread_num = (i % (num_active_threads - 1)) + 1;
			this_thread = thread_ptrs + current_thread_num;
			
			if (Atomic_Compare_And_Swap(0, 2, (t_int32_atomic *) &this_thread->processed))
			{
				hoa_processor_threadprocess(x, this_thread->thread_temp_buffer, this_thread->temp_mem_ptr, this_thread->temp_mem_size, this_thread->vec_size, current_thread_num, num_active_threads);
				this_thread->processed = 1;
			}
		}
	}
	
#ifdef __APPLE__
	return NULL;
#else
	return 0;
#endif
}

__inline void hoa_processor_threadprocess(t_hoa_processor *x, void **sig_outs, void *temp_mem_ptr, long temp_mem_size, long vec_size, long thread_num, long threads_running)
{
	t_patchspace **patch_space_ptrs = x->patch_space_ptrs;
	t_patchspace *next_patch_space_ptr = 0;
	
	t_dspchain *next_dspchain = 0;
	
	long declared_sig_outs = x->declared_sig_outs;
	long patch_spaces_allocated = x->patch_spaces_allocated; 
	long index;
	long i;
	
	// Turn off denormals
	
#if defined( __i386__ ) || defined( __x86_64__ )
	int oldMXCSR = _mm_getcsr();						// read the old MXCSR setting 
	int newMXCSR = oldMXCSR | 0x8040;					// set DAZ and FZ bits 
	_mm_setcsr( newMXCSR );								// write the new MXCSR setting to the MXCSR 
#endif
		
	// Zero outputs
	
	for (i = 0; i < declared_sig_outs; i++) 
		memset(sig_outs[i], 0, SIG_SIZE * vec_size);
	
	if (x->manual_threading)
	{
		// Here we run each patch in the requested thread
		
		for (i = 0; i < patch_spaces_allocated; i++)
		{
			next_patch_space_ptr = patch_space_ptrs[i];
			next_dspchain = next_patch_space_ptr->the_dspchain;
			
			if (next_patch_space_ptr->patch_valid && next_patch_space_ptr->patch_on && next_dspchain && next_patch_space_ptr->required_temp_mem_size <= temp_mem_size && 
				(next_patch_space_ptr->thread_current % threads_running) == thread_num)
			{							
				// Point to thread buffers and run DSP
				
				next_patch_space_ptr->out_ptrs = sig_outs;
				next_patch_space_ptr->temp_mem_ptr = temp_mem_ptr;
				
				dspchain_tick(next_dspchain);
			}
		}
	}
	else
	{
		// Here we start each thread at a different point in the cycle and whichever one reaches a patch first will process it
		
		index = (thread_num * (patch_spaces_allocated / threads_running)) - 1;
		for (i = 0; i < patch_spaces_allocated; i++)
		{
			if (++index >= patch_spaces_allocated)
				index -= patch_spaces_allocated;
			
			next_patch_space_ptr = patch_space_ptrs[index];
			next_dspchain = next_patch_space_ptr->the_dspchain;
			
			if (next_patch_space_ptr->patch_valid && next_patch_space_ptr->patch_on && next_dspchain && next_patch_space_ptr->required_temp_mem_size  <= temp_mem_size && 
				Atomic_Compare_And_Swap(0, 1, &next_patch_space_ptr->processed_flag))
			{							
				// Point to thread buffers and run DSP
				
				next_patch_space_ptr->out_ptrs = sig_outs;
				next_patch_space_ptr->temp_mem_ptr = temp_mem_ptr;
				
				dspchain_tick(next_dspchain);
			}
		}
	}
	
	// return denormals to previous state 
	
#if defined( __i386__ ) || defined( __x86_64__ )	
	_mm_setcsr(oldMXCSR);	
#endif
}


long hoa_processor_dsp_common(t_hoa_processor *x, long vec_size, long samp_rate)
{	
	t_patchspace *patch_space_ptr;
	long thread_temp_buffer_size;
	long mem_fail = 0;
	long i, j;
	
	for (i = 0; i < x->max_obj_threads; i++)
		x->thread_space_ptr[i].vec_size = vec_size;
	
	// Memory allocation for temporary thread buffers 
	
	thread_temp_buffer_size = vec_size * SIG_SIZE;
	
	if (thread_temp_buffer_size != x->thread_temp_buffer_size)
	{
		for (i = 0; i < x->max_obj_threads; i++)
		{
			for (j = 0; j < x->declared_sig_outs; j++)
			{
				ALIGNED_FREE (x->thread_space_ptr[i].thread_temp_buffer[j]);
				x->thread_space_ptr[i].thread_temp_buffer[j] = ALIGNED_MALLOC (thread_temp_buffer_size);
				if (!x->thread_space_ptr[i].thread_temp_buffer[j])
				{		
					object_error((t_object*)x, "not enough memory");
					mem_fail = 1;
					x->x_obj.z_disabled = TRUE;	
				}
			}
		}
	}
	
	// Do internal dsp compile (for each valid patch)
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		if (patch_space_ptr->patch_valid)
			hoa_processor_dsp_internal (patch_space_ptr, vec_size, samp_rate);
	}
	
	x->last_vec_size = vec_size;
	x->last_samp_rate = samp_rate;
	
	if (!mem_fail)
		x->thread_temp_buffer_size = thread_temp_buffer_size;
	
	return mem_fail;
}

void hoa_processor_dsp64 (t_hoa_processor *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	// Add to dsp if common routine successful
	
	if (!hoa_processor_dsp_common(x, maxvectorsize, samplerate))
		object_method(dsp64, gensym("dsp_add64"), x, hoa_processor_perform64, 0, NULL);
}


void hoa_processor_dsp_internal (t_patchspace *patch_space_ptr, long vec_size, long samp_rate)
{
	// Free the old dspchain
		
	if (patch_space_ptr->the_dspchain)
		freeobject((t_object *)patch_space_ptr->the_dspchain);
	
	// Recompile 
	
	patch_space_ptr->the_dspchain = dspchain_compile(patch_space_ptr->the_patch, vec_size, samp_rate);	
}


// ========================================================================================================================================== //
// Patcher Link Inlets / Outlets
// ========================================================================================================================================== //

// - inlet and outlet linking using the in and out objects

short hoa_processor_linkinlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b)) 
	{
		if (jbox_get_maxclass(b) == ps_in) 
		{
			io = (t_inout *) jbox_get_object(b);
			if (io->s_index <= x->declared_ins) outlet_add(x->in_table[io->s_index - 1], (struct inlet *)io->s_obj.o_outlet);
		}
    }
	return (0);
}

short hoa_processor_linkoutlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))
	{
		if (jbox_get_maxclass(b) == ps_out) 
		{
			io = (t_inout *) jbox_get_object(b);
			if (io->s_index <= x->declared_outs) outlet_add(io->s_outlet, x->out_table[io->s_index - 1]);
		}
    }
	return (0);
}

// - inlet and outlet removal using the in and out objects

short hoa_processor_unlinkinlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b)) 
	{
		if (jbox_get_maxclass(b) == ps_in) 
		{
			io = (t_inout *) jbox_get_object(b);
			if (io->s_index <= x->declared_ins) outlet_rm(x->in_table[io->s_index - 1], (struct inlet *)io->s_obj.o_outlet);
		}
    }
	return (0);
}

short hoa_processor_unlinkoutlets(t_patcher *p, t_hoa_processor *x)
{
	t_box *b;
	t_inout *io;
	
	for (b = jpatcher_get_firstobject(p); b; b = jbox_get_nextobject(b))
	{
		if (jbox_get_maxclass(b)  == ps_out) 
		{
			io = (t_inout *) jbox_get_object(b);
			if (io->s_index <= x->declared_outs) outlet_rm(io->s_outlet, x->out_table[io->s_index - 1]);
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
		mess0((t_object *)x->patch_space_ptrs[index]->the_patch, ps_front);		// this will always do the right thing
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
	t_object *assoc = 0;
	object_method(p, ps_getassoc, &assoc);				// Avoid recursion into a poly / pfft / hoa.process~
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
	object_method(p, ps_getassoc, &assoc);
	if (!assoc) 
		object_method(p, ps_setassoc, x);
	object_method(p, ps_noedit, 1);
	return 0;
}

void hoa_processor_pupdate(t_hoa_processor *x, void *b, t_patcher *p)
{
	t_patchspace *patch_space_ptr;
	long i;
	
	// Reload the patcher when it's updated
	
	for (i = 0; i < x->patch_spaces_allocated; i++)
	{
		patch_space_ptr = x->patch_space_ptrs[i];
		if (patch_space_ptr->the_patch == p) 
			hoa_processor_loadpatch (x, i, 0, patch_space_ptr->patch_name_in, patch_space_ptr->x_argc, patch_space_ptr->x_argv);
	}
}

void *hoa_processor_subpatcher(t_hoa_processor *x, long index, void *arg)
{		
	 if (arg && (long) arg != 1) 
		if (!NOGOOD(arg))								// arg might be good but not a valid object pointer
			if (ob_sym(arg) == ps_dspchain)				// don't report subpatchers to dspchain
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
	patch_space_ptr->patch_busy = 0;
	patch_space_ptr->the_dspchain = 0;
	patch_space_ptr->x_argc = 0;
	patch_space_ptr->out_ptrs = 0;
		
	patch_space_ptr->processed_flag = 0;
	patch_space_ptr->required_temp_mem_size = 0;
}

// Free the patch and dspchain

void hoa_processor_free_patch_and_dsp (t_hoa_processor *x, t_patchspace *patch_space_ptr)
{
	// free old patch and dspchain
	
	if (patch_space_ptr->the_dspchain)
		freeobject((t_object *)patch_space_ptr->the_dspchain);
	
	if (patch_space_ptr->the_patch)
	{
		if (x->declared_ins) hoa_processor_patcher_descend(patch_space_ptr->the_patch, (t_intmethod) hoa_processor_unlinkinlets, x, x);
		if (x->declared_outs) hoa_processor_patcher_descend(patch_space_ptr->the_patch, (t_intmethod) hoa_processor_unlinkoutlets, x, x);
		freeobject((t_object *)patch_space_ptr->the_patch);
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


//////////////////////////////////////////////////// State Queries ////////////////////////////////////////////////////


void hoa_processor_client_set_patch_on (t_hoa_processor *x, long index, long state)
{
	if (state) state = 1;
	if (index <= x->patch_spaces_allocated)
		x->patch_space_ptrs[index - 1]->patch_on = state;
}

void hoa_processor_client_set_patch_busy (t_hoa_processor *x, long index, long state)
{
	if (state) state = 1;
	if (index <= x->patch_spaces_allocated)
		x->patch_space_ptrs[index - 1]->patch_busy = state;
}

void *hoa_processor_client_get_patch_on (t_hoa_processor *x, long index)
{
	if (index <= x->patch_spaces_allocated)
		return (void *) (long) x->patch_space_ptrs[index - 1]->patch_on;
	
	return 0;
}

void *hoa_processor_client_get_patch_busy (t_hoa_processor *x, long index)
{
	if (index <= x->patch_spaces_allocated)
		return (void *) (long) x->patch_space_ptrs[index - 1]->patch_busy;
	
	return 0;
}


//////////////////////////////////////////////// Tempory Memory Queries ///////////////////////////////////////////////


// hoa.process~ provides memory per audio thread for temporary calculations. 
// Objects requiring temporary memory during their perform method request a minimum size during their dsp routine
// The pointer should be requested during the perform routine, and should not be stored
// This reduces memory alloaction, and potentially increases speed by keeping temporary memory in the cache


void *hoa_processor_query_temp_mem (t_hoa_processor *x, long index)
{
	if (index <= x->patch_spaces_allocated)
		return &x->patch_space_ptrs[index - 1]->temp_mem_ptr;
	else
		return 0;
}

void *hoa_processor_client_temp_mem_resize (t_hoa_processor *x, long index, long size)
{	
	schedule_grow_mem_swap(&x->temp_mem, x->max_obj_threads * size, size);
	
	if (index > 0 && index <= x->patch_spaces_allocated)
		x->patch_space_ptrs[index - 1]->required_temp_mem_size = size;
	
	return (void *) 1;
	
}

