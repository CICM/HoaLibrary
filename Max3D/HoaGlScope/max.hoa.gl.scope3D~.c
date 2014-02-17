/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "hoa.gl.scope3D~.h"

t_jit_err hoa_gl_scope_init(void);

void *max_hoa_gl_scope_new(t_symbol *s, long argc, t_atom *argv);
void max_hoa_gl_scope_free(t_max_hoa_gl_scope *x);

void hoa_gl_scope_assist(t_max_hoa_gl_scope *x, void *b, long m, long a, char *s);
void hoa_gl_scope_dsp64(t_max_hoa_gl_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_gl_scope_perform64(t_max_hoa_gl_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *max_hoa_gl_scope_class;

int C74_EXPORT main(void)
{	
	t_class *maxclass, *jitclass;
	
	// initialize our Jitter class
	hoa_gl_scope_init();
	
	// create our Max class
	maxclass = class_new("hoa.gl.scope3D~", (method)max_hoa_gl_scope_new, (method)max_hoa_gl_scope_free, sizeof(t_max_hoa_gl_scope), NULL, A_GIMME, 0);

	// specify a byte offset to keep additional information about our object
	max_jit_class_obex_setup(maxclass, calcoffset(t_max_hoa_gl_scope, obex));
	
	// look up our Jitter class in the class registry
	jitclass = (t_class*) jit_class_findbyname(gensym("hoa_gl_scope"));
	
	// wrap our Jitter class with the standard methods for Jitter objects
    max_jit_class_wrap_standard(maxclass, jitclass, 0);
    			   
   	// use standard ob3d assist method
    //class_addmethod(maxclass, (method)max_jit_ob3d_assist, "assist", A_CANT, 0);
	class_addmethod(maxclass, (method)hoa_gl_scope_dsp64,  "dsp64",		A_CANT, 0);
	class_addmethod(maxclass, (method)hoa_gl_scope_assist, "assist",	A_CANT, 0);

	// add methods for 3d drawing
    max_jit_class_ob3d_wrap(maxclass);
		
	class_dspinit(maxclass);
	class_register(CLASS_BOX, maxclass);
	max_hoa_gl_scope_class = maxclass;
	
	hoa_credit();
	
	return 0;
}

void hoa_gl_scope_assist(t_max_hoa_gl_scope *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

void hoa_gl_scope_dsp64(t_max_hoa_gl_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_index = 0;
    object_method(dsp64, gensym("dsp_add64"), x, hoa_gl_scope_perform64, 0, NULL);
}
void hoa_gl_scope_perform64(t_max_hoa_gl_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
		//object_method_long(x->jitObject, gensym("set_index"), x->f_index, NULL);
    }
}


void max_hoa_gl_scope_free(t_max_hoa_gl_scope *x)
{
	// lookup our internal Jitter object instance and free
	jit_object_free(max_jit_obex_jitob_get(x));
	
	dsp_free((t_pxobject *)x);
	delete x->f_scope;
    delete [] x->f_signals;
	
	// free resources associated with our obex entry
	max_jit_object_free(x);
}

void *max_hoa_gl_scope_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_hoa_gl_scope* x = NULL;
	t_jit_object *jit_ob = NULL;
	long attrstart;
	t_symbol *dest_name_sym = _jit_sym_nothing;
	t_atom_long order = 1;

	if ((x = (t_max_hoa_gl_scope *)max_jit_object_alloc(max_hoa_gl_scope_class, gensym("hoa_gl_scope"))))
	{
		// get first normal arg, the destination name
		attrstart = max_jit_attr_args_offset(argc,argv);
		
		if (argc >= 1 && argv)
		{
			if (atom_gettype(argv) == A_LONG)
			{
				order = jit_atom_getlong(argv);
			}
			if (argc >= 2)
			{
				jit_atom_arg_getsym(&dest_name_sym, 1, attrstart, argv);
			}
		}
		
		jit_ob = (t_jit_object*)jit_object_new(gensym("hoa_gl_scope"), dest_name_sym, x);

		// instantiate Jitter object with dest_name arg
		//if ((jit_ob = (t_jit_object*)jit_object_new(gensym("hoa_gl_scope"), dest_name_sym)))
		if (jit_ob)
		{
			// set internal jitter object instance
			max_jit_obex_jitob_set(x, jit_ob);
			
			x->f_scope = new Hoa3D::Scope(order, 100, 199);
			dsp_setup((t_pxobject *)x, x->f_scope->getNumberOfHarmonics());
			
			x->f_signals = new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
			x->f_index = 0;
			
			max_jit_attr_args(x, argc, argv);
		} 
		else 
		{
			error("hoa.gl.scope3D~: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}


