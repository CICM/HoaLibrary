/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaCommon.pd.h"


typedef struct _hoa_thisprocess
{
    t_eobj      j_box;
    char        f_nit;
    
    t_outlet*   f_out_hoa_args;
    t_outlet*   f_out_hoa_mode;
	t_outlet*   f_out_args;
    t_outlet*   f_out_attrs;
    t_outlet*   f_out_mute;
    
    t_atom      f_hoa_args[3];
    t_atom      f_hoa_mode[2];
    
    t_atom*     f_args;
    long        f_argc;
    
    long        f_n_attrs;
    t_symbol**  f_attr_name;
    t_atom*     f_attr_vals[256];
    long        f_attr_size[256];
    double      f_time;
} t_hoa_thisprocess;

t_eclass *hoa_thisprocess_class;

void *hoa_thisprocess_new(t_symbol *s, long argc, t_atom *argv);
void hoa_thisprocess_free(t_hoa_thisprocess *x);
void hoa_thisprocess_bang(t_hoa_thisprocess *x);
void hoa_thisprocess_click(t_hoa_thisprocess *x);

t_hoa_err hoa_getinfos(t_hoa_thisprocess* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2ethisprocess_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.thisprocess~", (method)hoa_thisprocess_new, (method)hoa_thisprocess_free, (short)sizeof(t_hoa_thisprocess), 0, A_GIMME, 0);
    
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_thisprocess_bang,       "bang",     A_CANT, 0);
    eclass_addmethod(c, (method)hoa_thisprocess_click,      "click",    A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_thisprocess_class = c;
}

void *hoa_thisprocess_new(t_symbol *s, long argc, t_atom *argv)
{
    int i;
	t_hoa_thisprocess *x =  NULL;
    
    x = (t_hoa_thisprocess *)eobj_new(hoa_thisprocess_class);
    if(x)
    {
        x->f_nit = 0;
        // ARGUMENTS //
        x->f_argc = atoms_get_attributes_offset(argc, argv);
        x->f_args = (t_atom *)calloc(x->f_argc, sizeof(t_atom));
        for(i = 0; i < x->f_argc; i++)
        {
            x->f_args[i] = argv[i];
        }
        
        // ATTRIBUTES //
        x->f_n_attrs = atoms_get_keys(argc-x->f_argc, argv+x->f_argc, &x->f_attr_name);
        for(i = 0; i < x->f_n_attrs; i++)
        {
            atoms_get_attribute(argc-x->f_argc, argv+x->f_argc, x->f_attr_name[i], &x->f_attr_size[i], &x->f_attr_vals[i]);
        }
        
        x->f_out_hoa_args = listout(x);
        x->f_out_hoa_mode = anythingout(x);
        x->f_out_args     = anythingout(x);
        x->f_out_attrs    = anythingout(x);
        //x->f_out_mute       = floatout(x);
        
        x->f_time = clock_getsystime();
    }
    
    return (x);
}

void hoa_thisprocess_click(t_hoa_thisprocess *x)
{
    if(clock_gettimesince(x->f_time) < 250.)
        hoa_thisprocess_bang(x);
    x->f_time = clock_getsystime();
}

void hoa_thisprocess_bang(t_hoa_thisprocess *x)
{
    char        attr_char[MAXPDSTRING];
    for(int i = 0; i < x->f_n_attrs; i++)
    {
        sprintf(attr_char, "%s", x->f_attr_name[i]->s_name+1);
        outlet_anything(x->f_out_attrs, gensym(attr_char), x->f_attr_size[i], x->f_attr_vals[i]);
    }
    
    if(x->f_argc && x->f_args)
        outlet_list(x->f_out_args, &s_list, x->f_argc, x->f_args);
    if(x->f_nit)
    {
        outlet_list(x->f_out_hoa_mode,  &s_list, 2, x->f_hoa_mode);
        if(atom_getsym(x->f_hoa_mode) == gensym("2d"))
            outlet_list(x->f_out_hoa_args, &s_list, 2, x->f_hoa_args);
        else if(atom_getsym(x->f_hoa_mode) == gensym("3d") && atom_getsym(x->f_hoa_mode+1) == gensym("planewaves"))
            outlet_list(x->f_out_hoa_args, &s_list, 2, x->f_hoa_args);
        else
            outlet_list(x->f_out_hoa_args, &s_list, 3, x->f_hoa_args);
    }
    outlet_symbol(x->f_out_attrs, gensym("done"));
}


void hoa_thisprocess_free(t_hoa_thisprocess *x)
{
    int i;
    if(x->f_argc)
        free(x->f_args);
    if(x->f_n_attrs)
    {
        for(i = 0; i < x->f_n_attrs; i++)
        {
            if(x->f_attr_size[i])
                free(x->f_attr_vals[i]);
        }
    }
    free(x->f_attr_name);
    eobj_free(x);
}

t_hoa_err hoa_getinfos(t_hoa_thisprocess* x, t_hoa_boxinfos* boxinfos)
{
    boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}
