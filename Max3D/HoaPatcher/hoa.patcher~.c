/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "../hoa.max.h"

typedef struct  _hoa_patcher
{
	t_pxobject          f_ob;
    t_object*           f_patcher;
	t_object**          f_subpatchers;
    
    long                f_ninlets;
    t_object**          f_inlets;
    long                f_noutlets;
    t_object**          f_outlets;
    Hoa3D::Ambisonic*   f_ambisonic;
    
} t_hoa_patcher;

t_class *hoa_patcher_class;

void *hoa_patcher_new(t_symbol *s, int argc, t_atom *argv);
void hoa_patcher_free(t_hoa_patcher *x);
void hoa_patcher_assist(t_hoa_patcher *x, void *b, long m, long a, char *s);

void hoa_patcher_anything(t_hoa_patcher *x, t_symbol* s, long argc, t_atom* argv);
void hoa_patcher_list(t_hoa_patcher *x, t_symbol* s, long argc, t_atom* argv);
void hoa_patcher_float(t_hoa_patcher *x, double f);
void hoa_patcher_int(t_hoa_patcher *x, long n);
void hoa_patcher_bang(t_hoa_patcher *x);

void hoa_patcher_dblclick(t_hoa_patcher *x);
void hoa_patcher_dsp64(t_hoa_patcher *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.patcher~", (method)hoa_patcher_new, (method)hoa_patcher_free, (short)sizeof(t_hoa_patcher), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)hoa_patcher_anything,    "anything", A_GIMME, 0);
    class_addmethod(c, (method)hoa_patcher_list,        "list",		A_GIMME, 0);
    class_addmethod(c, (method)hoa_patcher_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_patcher_int,         "int",		A_LONG, 0);
    class_addmethod(c, (method)hoa_patcher_bang,        "bang",		A_CANT, 0);
    
    
	class_addmethod(c, (method)hoa_patcher_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_patcher_assist,      "assist",	A_CANT, 0);
    class_addmethod(c, (method)hoa_patcher_dblclick,    "dblclick", A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_patcher_class = c;
    hoa_credit();
    
}

void *hoa_patcher_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_patcher* x;
    char    name[MAX_FILENAME_CHARS];
    short   path[MAX_PATH_CHARS];
    int order  = 1;
    
    
    x = (t_hoa_patcher *)object_alloc(hoa_patcher_class);
	if(x && argc && atom_gettype(argv) == A_LONG)
	{
        order = atom_getlong(argv);
        if(order < 1)
            order = 1;
        
        x->f_ambisonic      = new Hoa3D::Ambisonic(order); // Ambisonic class to easely compute the ambisonic infos
        x->f_patcher        = (t_object *)object_new(CLASS_NOBOX, gensym("jpatcher"), 0, NULL); // Global patcher
        x->f_subpatchers    = new t_object*[x->f_ambisonic->getNumberOfHarmonics()]; // The subpatchers
        x->f_ninlets        = 0;
        x->f_noutlets       = 0;
        x->f_inlets         = new t_object*[x->f_ambisonic->getNumberOfHarmonics()]; // The subpatchers inlets
        x->f_outlets        = new t_object*[x->f_ambisonic->getNumberOfHarmonics()]; // The subpatchers inlets
        
        strncpy_zero(name, atom_getsym(argv+1)->s_name, MAX_FILENAME_CHARS);
        strncat(name, ".maxpat", MAX_FILENAME_CHARS);
        
        if(!locatefiletype(name, path, 0L, 0L))
        {
            for(int i = 0; i < x->f_ambisonic->getNumberOfHarmonics(); i++)
            {
                x->f_subpatchers[i] = newobject_sprintf(x->f_patcher, "@maxclass newobj @text \"%s %i %i\" @patching_rect %i 100 20 20", atom_getsym(argv+1)->s_name, (int)x->f_ambisonic->getHarmonicBand(i), (int)x->f_ambisonic->getHarmonicArgument(i), i * 100 + 10);
                
                x->f_inlets[i] = (t_object *)jbox_getinlet((t_jbox *)x->f_subpatchers[i], 0);
            }
            x->f_ninlets = inlet_count(x->f_subpatchers[0]) - 1;
            x->f_noutlets = outlet_count(x->f_subpatchers[0]);
        }
        
        dsp_setup((t_pxobject *)x, x->f_ambisonic->getNumberOfHarmonics() * x->f_ninlets);
        for (int i = 0; i < x->f_ambisonic->getNumberOfHarmonics() * x->f_noutlets; i++)
            outlet_new(x, "signal");
        
        object_method(x->f_patcher, gensym("loadbang"));
	}
    
	return x;
}

void hoa_patcher_anything(t_hoa_patcher *x, t_symbol* s, long argc, t_atom* argv)
{
    object_method_typed(x->f_inlets[0], gensym("list"), argc, argv, NULL);
}

void hoa_patcher_list(t_hoa_patcher *x, t_symbol* s, long argc, t_atom* argv)
{
    object_method_typed(x->f_inlets[0], gensym("list"), argc, argv, NULL);
}

void hoa_patcher_float(t_hoa_patcher *x, double f)
{
    object_method_float(x->f_inlets[0], gensym("float"), f, NULL);
}

void hoa_patcher_int(t_hoa_patcher *x, long n)
{
    object_method_long(x->f_inlets[0], gensym("int"), n, NULL);
}

void hoa_patcher_bang(t_hoa_patcher *x)
{
    object_method_typed(x->f_inlets[0], gensym("bang"), 0, NULL, NULL);
}

void hoa_patcher_dblclick(t_hoa_patcher *x)
{
    object_method(x->f_subpatchers[0], gensym("mousedoubleclick"));
}

void hoa_patcher_dsp64(t_hoa_patcher *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    t_dspchain* dspchain = NULL;
    /*
    post(object_classname(dsp64)->s_name);
    t_class *c = object_class(dsp64);
    for(int i = 0; i < c->c_messcount - 1; i++)
        post(c->c_messlist[i].m_sym->s_name);
    */
    //post("chain : %ld", (long)dspchain);
    
    //dspchain_compile(x->f_subpatchers[0], maxvectorsize, samplerate);
    //object_method(, gensym("getdspchain"), &dspchain);
	/*
    post("objchain : %ld", (long)dsp64);
    dspchain = dspchain_fromobject(x->f_subpatchers[0]);
    post("dspchain :%ld count : %ld", (long)dspchain, dspchain->c_usedcount);
    dspchain = dspchain_fromobject(x->f_subpatchers[1]);
    post("dspchain :%ld count : %ld", (long)dspchain, dspchain->c_usedcount);
	*/
	// object_method((t_object *)x->f_patcher, gensym("dsp64"), dsp64, count, samplerate, maxvectorsize, flags);
}

void hoa_patcher_assist(t_hoa_patcher *x, void *b, long m, long a, char *s)
{
    //sprintf(s,"(Signal) %s", x->f_ambisonic->getHarmonicsName(a).c_str());
}

void hoa_patcher_free(t_hoa_patcher *x)
{
    post("free");
	dsp_free((t_pxobject *)x);
    delete x->f_ambisonic;
    free(x->f_subpatchers);
    object_free(x->f_patcher);
}

