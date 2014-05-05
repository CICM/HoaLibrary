/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaCommon.pd.h"

extern "C"
{
#include "../../ThirdParty/PureData/Sources/ecommon/d_ugen.h"
EXTERN t_canvas *canvas_list;
}

typedef struct _hoa_in
{
    t_eobj  f_obj;
    int     f_extra;
} t_hoa_in;

typedef struct _hoa_out
{
    t_eobj  f_obj;
    t_outlet *f_outlet;
    int    f_extra;
} t_hoa_out;

typedef struct _hoa_in_tilde
{
    t_edspobj   f_obj;
    t_sample*   f_signal;
    int         f_extra;
} t_hoa_in_tilde;

typedef struct _hoa_out_tilde
{
    t_edspobj   f_obj;
    t_sample*   f_signal;
    int         f_extra;
} t_hoa_out_tilde;

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

typedef struct _hoa_process
{
    t_edspobj           f_obj;
    int                 f_mode;
    
    Hoa2D::Ambisonic*   f_ambi_2d;
    Hoa3D::Ambisonic*   f_ambi_3d;
    Hoa2D::Planewaves*  f_planewaves;
    
    long                f_target;
    
    t_canvas**          f_canvas;
    long                f_ncanvas;
    
    char                f_have_inlets_instance;
    long                f_max_inlets_extra;
    char                f_have_outlets_instance;
    long                f_max_outlets_extra;
    
    char                f_have_inlets_instance_sig;
    long                f_max_inlets_extra_sig;
    char                f_have_outlets_instance_sig;
    long                f_max_outlets_extra_sig;
    
    
    long*               f_ninlets_instance;
    t_hoa_in***         f_inlets_instance;
    long*               f_ninlets_extra;
    t_hoa_in***         f_inlets_extra;
    
    long*               f_noutlets_instance;
    t_hoa_out***        f_outlets_instance;
    long*               f_noutlets_extra;
    t_hoa_out***        f_outlets_extra;
    
    long*               f_ninlets_instance_sig;
    t_hoa_in_tilde***   f_inlets_instance_sig;
    long*               f_ninlets_extra_sig;
    t_hoa_in_tilde***   f_inlets_extra_sig;
    
    long*               f_noutlets_instance_sig;
    t_hoa_out_tilde***  f_outlets_instance_sig;
    long*               f_noutlets_extra_sig;
    t_hoa_out_tilde***  f_outlets_extra_sig;
    
    t_dspcontext**      f_dsp_context;
    
    t_sample**          f_outlets_signals;
} t_hoa_process;

t_eclass *hoa_process_class;

void *hoa_process_new(t_symbol *s, long argc, t_atom *argv);
void hoa_process_free(t_hoa_process *x);
long hoa_process_get_number_of_inputs(t_hoa_process *x);
long hoa_process_get_number_of_outputs(t_hoa_process *x);

void hoa_process_dsp(t_hoa_process *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_process_perform(t_hoa_process *x, t_object *dsp, float **inps, long ni, float **outs, long no, long sf, long f,void *up);

void hoa_process_load(t_hoa_process *x, t_eattr *attr, long argc, t_atom* argv);
void hoa_process_click(t_hoa_process *x);
void hoa_process_open(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv);
void hoa_process_target(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv);

void hoa_process_bang(t_hoa_process *x);
void hoa_process_float(t_hoa_process *x, float f);
void hoa_process_symbol(t_hoa_process *x, t_symbol* s);
void hoa_process_list(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv);
void hoa_process_anything(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv);

t_hoa_err hoa_getinfos(t_hoa_process* x, t_hoa_boxinfos* boxinfos);

void hoa_process_load_canvas(t_hoa_process *x, t_symbol *s, long argc, t_atom* argv);

extern "C" void setup_hoa0x2eprocess_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.process~", (method)hoa_process_new, (method)hoa_process_free, (short)sizeof(t_hoa_process), CLASS_NOINLET, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_process_new, gensym("hoa.2d.process~"), A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_process_new, gensym("hoa.3d.process~"), A_GIMME, 0);
    
    eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_process_dsp,        "dsp",      A_CANT, 0);    
    eclass_addmethod(c, (method)hoa_process_click,      "click",    A_CANT, 0);
    eclass_addmethod(c, (method)hoa_process_open,       "open",     A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_process_target,     "target",   A_GIMME, 0);
    
    eclass_addmethod(c, (method)hoa_process_bang,       "bang",     A_CANT,  0);
    eclass_addmethod(c, (method)hoa_process_float,      "float",    A_FLOAT, 0);
    eclass_addmethod(c, (method)hoa_process_symbol,     "symbol",   A_SYMBOL,0);
    eclass_addmethod(c, (method)hoa_process_list,       "list",     A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_process_anything,   "anything", A_GIMME, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_process_class = c;
}

void *hoa_process_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_process *x = NULL;
	int	argument = 1;
    t_outlet *outlet;
    
    if(argc < 2 || atom_gettype(argv) != A_LONG || atom_gettype(argv+1) != A_SYM)
    {
        error("%s needs at least 2 arguments, an integer and one symbol.", s->s_name);
        return NULL;
    }
    
    x = (t_hoa_process *)eobj_new(hoa_process_class);
	if(x)
	{
        argument = atom_getlong(argv);
        if(argument < 1)
            argument = 1;
        
        x->f_target = -1;
        if(argc > 2 && atom_gettype(argv+2) == A_SYM && atom_getsym(argv+2) == gensym("planewaves"))
        {
            x->f_planewaves = new Hoa2D::Planewaves(argument);
            x->f_ncanvas = x->f_planewaves->getNumberOfChannels();
            if(s == gensym("hoa.3d.process~"))
                x->f_mode = 3;
            else
                x->f_mode = 2;
        
        }
        else if(s == gensym("hoa.3d.process~"))
        {
            x->f_mode = 1;
            x->f_ambi_3d = new Hoa3D::Ambisonic(argument);
            x->f_ncanvas = x->f_ambi_3d->getNumberOfHarmonics();
        }
        else
        {
            x->f_mode = 0;
            x->f_ambi_2d = new Hoa2D::Ambisonic(argument);
            x->f_ncanvas = x->f_ambi_2d->getNumberOfHarmonics();
        }
        
        hoa_process_load_canvas(x, atom_getsym(argv+1), argc - 3, argv + 3);
        
        if(x->f_ncanvas == 0)
        {
            eobj_dspsetup(x, 1, 0);
            return x;
        }
        
        x->f_have_inlets_instance = 0;
        x->f_max_inlets_extra = 0;
        x->f_have_outlets_instance = 0;
        x->f_max_outlets_extra = 0;
        
        x->f_have_inlets_instance_sig = 0;
        x->f_max_inlets_extra_sig = 0;
        x->f_have_outlets_instance_sig = 0;
        x->f_max_outlets_extra_sig = 0;
        
        for(int i = 0; i < x->f_ncanvas; i++)
        {
            // Control //
            if(x->f_ninlets_instance[i] > 0)
                x->f_have_inlets_instance = 1;
            for(int j = 0; j < x->f_ninlets_extra[i]; j++)
            {
                if(x->f_inlets_extra[i][j]->f_extra > x->f_max_inlets_extra)
                    x->f_max_inlets_extra = x->f_inlets_extra[i][j]->f_extra;
            }
            
            if(x->f_noutlets_instance[i] > 0)
                x->f_have_outlets_instance = 1;
            for(int j = 0; j < x->f_noutlets_extra[i]; j++)
            {
                if(x->f_outlets_extra[i][j]->f_extra > x->f_max_outlets_extra)
                    x->f_max_outlets_extra = x->f_outlets_extra[i][j]->f_extra;
            }
            
            // Signal //
            if(x->f_ninlets_instance_sig[i] > 0)
                x->f_have_inlets_instance_sig = 1;
            for(int j = 0; j < x->f_ninlets_extra_sig[i]; j++)
            {
                if(x->f_inlets_extra_sig[i][j]->f_extra > x->f_max_inlets_extra_sig)
                    x->f_max_inlets_extra_sig = x->f_inlets_extra_sig[i][j]->f_extra;
            }
            
            if(x->f_noutlets_instance_sig[i] > 0)
                x->f_have_outlets_instance_sig = 1;
            for(int j = 0; j < x->f_noutlets_extra_sig[i]; j++)
            {
                if(x->f_outlets_extra_sig[i][j]->f_extra > x->f_max_outlets_extra_sig)
                    x->f_max_outlets_extra_sig = x->f_outlets_extra_sig[i][j]->f_extra;
            }
        }
        
        eobj_dspsetup(x, x->f_have_inlets_instance_sig * x->f_ncanvas + x->f_max_inlets_extra_sig, x->f_have_outlets_instance_sig * x->f_ncanvas + x->f_max_outlets_extra_sig);
        
        // Inlet signal intance //
        if(x->f_have_inlets_instance && !x->f_have_inlets_instance_sig)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                eobj_proxynew(x);
            }
        }
        
        // Inlet control extra //
        for(int i = x->f_max_inlets_extra_sig; i < x->f_max_inlets_extra; i++)
        {
            eobj_proxynew(x);
        }
        
        if(x->f_have_outlets_instance)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                outlet = outlet_new((t_object *)x, &s_anything);
                for(int j = 0; j < x->f_noutlets_instance[i]; j++)
                    x->f_outlets_instance[i][j]->f_outlet = outlet;
            }
        }
        
        for(int i = 0; i < x->f_max_outlets_extra; i++)
        {
            outlet = outlet_new((t_object *)x, &s_anything);
            for(int j = 0; j < x->f_ncanvas; j++)
            {
                for(int k = 0; k < x->f_noutlets_extra[j]; k++)
                {
                    if(x->f_outlets_extra[j][k]->f_extra == (i + 1))
                    {
                        x->f_outlets_extra[j][k]->f_outlet = outlet;
                    }
                }
            }
        }
        
        x->f_outlets_signals = new t_sample*[x->f_have_outlets_instance_sig * x->f_ncanvas + x->f_max_outlets_extra_sig];
        for(int i = 0 ; i < x->f_have_outlets_instance_sig * x->f_ncanvas + x->f_max_outlets_extra_sig; i++)
        {
            x->f_outlets_signals[i] = new t_sample[8192];
        }
		
        x->f_target = -1;
	}
    
	return x;
}

void hoa_process_free(t_hoa_process *x)
{
    int state = canvas_suspend_dsp();
    
    signal_cleanup();
    for(int i = 0 ; i < x->f_have_outlets_instance_sig * x->f_ncanvas + x->f_max_outlets_extra_sig; i++)
    {
        delete [] x->f_outlets_signals[i];
    }
    
    delete [] x->f_outlets_signals;
    
    for(int i = 0; i < x->f_ncanvas; i++)
    {
        if(x->f_canvas[i])
        {
            x->f_canvas[i]->gl_owner = eobj_getcanvas(x);
            canvas_free(x->f_canvas[i]);
            dsp_context_free(x->f_dsp_context[i]);
            
            delete [] x->f_inlets_instance[i];
            delete [] x->f_inlets_extra[i];
            
            delete [] x->f_outlets_instance[i];
            delete [] x->f_outlets_extra[i];
            
            delete [] x->f_inlets_instance_sig[i];
            delete [] x->f_inlets_extra_sig[i];
            
            delete [] x->f_outlets_instance_sig[i];
            delete [] x->f_outlets_extra_sig[i];
        }
    }
    delete [] x->f_canvas;
    
    delete [] x->f_dsp_context;
    
    delete [] x->f_ninlets_instance;
    delete [] x->f_ninlets_extra;
    delete [] x->f_inlets_instance;
    delete [] x->f_inlets_extra;
    
    delete [] x->f_noutlets_instance;
    delete [] x->f_noutlets_extra;
    delete [] x->f_outlets_instance;
    delete [] x->f_outlets_extra;
    
    delete [] x->f_ninlets_instance_sig;
    delete [] x->f_ninlets_extra_sig;
    delete [] x->f_inlets_instance_sig;
    delete [] x->f_inlets_extra_sig;
    
    delete [] x->f_noutlets_instance_sig;
    delete [] x->f_noutlets_extra_sig;
    delete [] x->f_outlets_instance_sig;
    delete [] x->f_outlets_extra_sig;
    
    if(x->f_mode > 1)
        delete x->f_planewaves;
    else if(x->f_mode == 1)
        delete x->f_ambi_3d;
    else
        delete x->f_ambi_2d;
        
        
    eobj_dspfree(x);
    canvas_resume_dsp(state);
}

void hoa_process_dsp(t_hoa_process *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    int inc = 0;
    
    signal_cleanup();
    for(int i = 0; i < x->f_ncanvas; i++)
    {
        dsp_context_removecanvas(x->f_dsp_context[i]);
    }

    if(x->f_have_inlets_instance_sig)
    {
        for(int i = 0; i < x->f_ncanvas; i++)
        {
            for(int j = 0; j < x->f_ninlets_instance_sig[i]; j++)
            {
                x->f_inlets_instance_sig[i][j]->f_signal = eobj_getsignalinput(x, inc);
                memset(eobj_getsignalinput(x, inc), 0, maxvectorsize * sizeof(t_sample));
            }
            inc++;
        }
    }
    
    for(int i = 0; i < x->f_max_inlets_extra_sig; i++)
    {
        for(int j = 0; j < x->f_ncanvas; j++)
        {
            for(int k = 0; k < x->f_ninlets_extra_sig[j]; k++)
            {
                if(x->f_inlets_extra_sig[j][k]->f_extra == (i+1))
                {
                    x->f_inlets_extra_sig[j][k]->f_signal = eobj_getsignalinput(x, inc);
                    memset(eobj_getsignalinput(x, inc), 0, maxvectorsize * sizeof(t_sample));
                }
            }
        }
        inc++;
    }
    
    inc  = 0;
    if(x->f_have_outlets_instance_sig)
    {
        memset(x->f_outlets_signals[inc], 0, maxvectorsize * sizeof(t_sample));
        for(int i = 0; i < x->f_ncanvas; i++)
        {
            for(int j = 0; j < x->f_noutlets_instance_sig[i]; j++)
            {
                x->f_outlets_instance_sig[i][j]->f_signal = x->f_outlets_signals[inc];
            }
            inc++;
        }
    }
    
    for(int i = 0; i < x->f_max_outlets_extra_sig; i++)
    {
        memset(x->f_outlets_signals[inc], 0, maxvectorsize * sizeof(t_sample));
        for(int j = 0; j < x->f_ncanvas; j++)
        {
            for(int k = 0; k < x->f_noutlets_extra_sig[j]; k++)
            {
                if(x->f_outlets_extra_sig[j][k]->f_extra == (i+1))
                {
                    x->f_outlets_extra_sig[j][k]->f_signal = x->f_outlets_signals[inc];
                }
            }
        }
        inc++;
    }
    
    for(int i = 0; i < x->f_ncanvas; i++)
    {
        if(x->f_canvas[i] && x->f_dsp_context[i])
        {
            dsp_context_addcanvas(x->f_dsp_context[i], x->f_canvas[i]);
            dsp_context_compile(x->f_dsp_context[i]);
        }
    }
    
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_process_perform, 0, NULL);
}

void hoa_process_perform(t_hoa_process *x, t_object *dsp, float **inps, long ni, float **outs, long nouts, long sampleframe, long f,void *up)
{
    for(int i = 0; i < nouts; i++)
    {
        memcpy(outs[i], x->f_outlets_signals[i], sampleframe * sizeof(float));
        memset(x->f_outlets_signals[i], 0, sampleframe * sizeof(float));
    }
}

t_hoa_err hoa_getinfos(t_hoa_process* x, t_hoa_boxinfos* boxinfos)
{
    boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_process_click(t_hoa_process *x)
{
    if(x->f_canvas[0])
    {
        canvas_vis(x->f_canvas[0], 1);
    }
}

void hoa_process_open(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv)
{
    int index, band;
    if(!argc || !argv)
        return;
        
    if(atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("all"))
    {
        for(int i = 0; i < x->f_ncanvas; i++)
        {
            if(x->f_canvas[i])
            {
                canvas_vis(x->f_canvas[i], 1);
            }
        }
    }
    else if(argc > 1 && argv && atom_gettype(argv) == A_FLOAT && atom_gettype(argv+1) == A_FLOAT && x->f_mode == 1)
    {
        band = atom_getfloat(argv);
        index = atom_getfloat(argv+1);
        if(band < 0 || band > x->f_ambi_3d->getDecompositionOrder())
        {
            object_error(x, "hoa.process~ open band index must be between 0 and %i", (int)x->f_ambi_3d->getDecompositionOrder());
            return;
        }
        if(index < (int)-band || index > band)
        {
            object_error(x, "hoa.process~ open argument index must be between %i and %i for the band %i", (int)-x->f_ambi_3d->getDecompositionOrder(), (int)x->f_ambi_3d->getDecompositionOrder(), (int)x->f_ambi_3d->getDecompositionOrder());
            return;
        }
        if(index < 0)
            index = -index * 2 - 1;
        else
            index = index * 2;
        index += band * band;
        canvas_vis(x->f_canvas[index], 1);
    }
    else if(atom_gettype(argv) == A_FLOAT && x->f_mode > 1)
    {
        index = atom_getfloat(argv);
        if(index < 1 || index > x->f_planewaves->getNumberOfChannels())
        {
            object_error(x, "hoa.process~ open index must be between 1 and %i", (int)x->f_planewaves->getNumberOfChannels());
            return;
        }
        index -= 1;
        canvas_vis(x->f_canvas[index], 1);
    }
    else if(atom_gettype(argv) == A_FLOAT && x->f_mode == 0)
    {
        index = atom_getfloat(argv);

        if(index < (int)-x->f_ambi_2d->getDecompositionOrder() || index > x->f_ambi_2d->getDecompositionOrder())
        {
            object_error(x, "hoa.process~ open index must be between %i and %i", (int)-x->f_ambi_2d->getDecompositionOrder(), x->f_ambi_2d->getDecompositionOrder());
            return;
        }
        if(index < 0)
            index = -index * 2 - 1;
        else
            index = index * 2;
        
        canvas_vis(x->f_canvas[index], 1);
    }
}

void hoa_process_target(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv)
{
    int index, band;
    if(!argc || !argv)
        return;
    
    if(atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("none"))
        x->f_target = -2;
    if(atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("all"))
        x->f_target = -1;
    else if(argc > 1 && atom_gettype(argv) == A_FLOAT && atom_gettype(argv+1) == A_FLOAT && x->f_mode == 1)
    {
        band = atom_getfloat(argv);
        index = atom_getfloat(argv+1);
        if(band < 0 || band > x->f_ambi_3d->getDecompositionOrder())
        {
            object_error(x, "hoa.process~ target band index must be between 0 and %i", (int)x->f_ambi_3d->getDecompositionOrder());
            return;
        }
        if(index < (int)-band || index > band)
        {
            object_error(x, "hoa.process~ target argument index must be between %i and %i for the band %i", (int)-x->f_ambi_3d->getDecompositionOrder(), (int)x->f_ambi_3d->getDecompositionOrder(), (int)x->f_ambi_3d->getDecompositionOrder());
            return;
        }
        if(index < 0)
            index = -index * 2 - 1;
        else
            index = index * 2;
        index += band * band;
        x->f_target = index;
    }
    else if(atom_gettype(argv) == A_FLOAT && x->f_mode > 1)
    {
        index = atom_getfloat(argv);
        if(index < 1 || index > x->f_planewaves->getNumberOfChannels())
        {
            object_error(x, "hoa.process~ target index must be between 1 and %i", (int)x->f_planewaves->getNumberOfChannels());
            return;
        }
        index -= 1;
        x->f_target = index;
    }
    else if(atom_gettype(argv) == A_FLOAT && x->f_mode == 0)
    {
        index = atom_getfloat(argv);
        if(index < (int)-x->f_ambi_2d->getDecompositionOrder() || index > (int)x->f_ambi_2d->getDecompositionOrder())
        {
            object_error(x, "hoa.process~ target index must be between %i and %i", (int)-x->f_ambi_2d->getDecompositionOrder(), x->f_ambi_2d->getDecompositionOrder());
            return;
        }
        if(index < 0)
            index = -index * 2 - 1;
        else
            index = index * 2;
        
        x->f_target = index;
    }
}

void hoa_process_bang(t_hoa_process *x)
{
    int extra;
    int index = eobj_getproxy(x);
    if((x->f_have_inlets_instance || x->f_have_inlets_instance_sig) && index < x->f_ncanvas)
    {
        for(int i = 0; i < x->f_ninlets_instance[index]; i++)
            pd_bang((t_pd *)x->f_inlets_instance[index][i]);
    }
    else
    {
        if(x->f_target == -2)
            return;
        
        if(x->f_have_inlets_instance || x->f_have_inlets_instance_sig)
            extra = index - (x->f_ncanvas - 1);
        else
            extra = index + 1;
        if(x->f_target == -1)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                for(int j = 0; j < x->f_ninlets_extra[i]; j++)
                {
                    if(x->f_inlets_extra[i][j]->f_extra == extra)
                    {
                        pd_bang((t_pd *)x->f_inlets_extra[i][j]);
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < x->f_ninlets_extra[x->f_target]; j++)
            {
                if(x->f_inlets_extra[x->f_target][j]->f_extra == extra)
                {
                    pd_bang((t_pd *)x->f_inlets_extra[x->f_target][j]);
                }
            }
        }
    }
}

void hoa_process_float(t_hoa_process *x, float f)
{
    int extra;
    int index = eobj_getproxy(x);

    if((x->f_have_inlets_instance || x->f_have_inlets_instance_sig) && index < x->f_ncanvas)
    {
        for(int i = 0; i < x->f_ninlets_instance[index]; i++)
        {
            pd_float((t_pd *)x->f_inlets_instance[index][i], f);
        }
    }
    else
    {
        if(x->f_target == -2)
            return;
        
        if(x->f_have_inlets_instance || x->f_have_inlets_instance_sig)
            extra = index - (x->f_ncanvas - 1);
        else
            extra = index + 1;
        if(x->f_target < 0)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                for(int j = 0; j < x->f_ninlets_extra[i]; j++)
                {
                    if(x->f_inlets_extra[i][j]->f_extra == extra)
                    {
                        pd_float((t_pd *)x->f_inlets_extra[i][j], f);
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < x->f_ninlets_extra[x->f_target]; j++)
            {
                if(x->f_inlets_extra[x->f_target][j]->f_extra == extra)
                {
                    pd_float((t_pd *)x->f_inlets_extra[x->f_target][j], f);
                }
            }
        }
    }
}

void hoa_process_symbol(t_hoa_process *x, t_symbol* s)
{
    int extra;
    int index = eobj_getproxy(x);
    if((x->f_have_inlets_instance || x->f_have_inlets_instance_sig) && index < x->f_ncanvas)
    {
        for(int i = 0; i < x->f_ninlets_instance[index]; i++)
            pd_symbol((t_pd *)x->f_inlets_instance[index][i], s);
    }
    else
    {
        if(x->f_target == -2)
            return;
        
        if(x->f_have_inlets_instance || x->f_have_inlets_instance_sig)
            extra = index - (x->f_ncanvas - 1);
        else
            extra = index + 1;
        if(x->f_target == -1)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                for(int j = 0; j < x->f_ninlets_extra[i]; j++)
                {
                    if(x->f_inlets_extra[i][j]->f_extra == extra)
                    {
                        pd_symbol((t_pd *)x->f_inlets_extra[i][j], s);
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < x->f_ninlets_extra[x->f_target]; j++)
            {
                if(x->f_inlets_extra[x->f_target][j]->f_extra == extra)
                {
                    pd_symbol((t_pd *)x->f_inlets_extra[x->f_target][j], s);
                }
            }
        }
    }
}

void hoa_process_list(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv)
{
    int extra;
    int index = eobj_getproxy(x);
    if((x->f_have_inlets_instance || x->f_have_inlets_instance_sig) && index < x->f_ncanvas)
    {
        for(int i = 0; i < x->f_ninlets_instance[index]; i++)
            pd_list((t_pd *)x->f_inlets_instance[index][i], s, argc, argv);
    }
    else
    {
        if(x->f_target == -2)
            return;
        
        if(x->f_have_inlets_instance || x->f_have_inlets_instance_sig)
            extra = index - (x->f_ncanvas - 1);
        else
            extra = index + 1;
        if(x->f_target == -1)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                for(int j = 0; j < x->f_ninlets_extra[i]; j++)
                {
                    if(x->f_inlets_extra[i][j]->f_extra == extra)
                    {
                        pd_list((t_pd *)x->f_inlets_extra[i][j], s, argc, argv);
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < x->f_ninlets_extra[x->f_target]; j++)
            {
                if(x->f_inlets_extra[x->f_target][j]->f_extra == extra)
                {
                    pd_list((t_pd *)x->f_inlets_extra[x->f_target][j], s, argc, argv);
                }
            }
        }
    }
}

void hoa_process_anything(t_hoa_process *x, t_symbol* s, int argc, t_atom* argv)
{
    int extra;
    int index = eobj_getproxy(x);
    
    if((x->f_have_inlets_instance || x->f_have_inlets_instance_sig) && index < x->f_ncanvas)
    {
        for(int i = 0; i < x->f_ninlets_instance[index]; i++)
            pd_typedmess((t_pd *)x->f_inlets_instance[index][i], s, argc, argv);
    }
    else
    {
        if(x->f_target == -2)
            return;
        
        if(x->f_have_inlets_instance || x->f_have_inlets_instance_sig)
            extra = index - (x->f_ncanvas - 1);
        else
            extra = index + 1;
        if(x->f_target == -1)
        {
            for(int i = 0; i < x->f_ncanvas; i++)
            {
                for(int j = 0; j < x->f_ninlets_extra[i]; j++)
                {
                    if(x->f_inlets_extra[i][j]->f_extra == extra)
                    {
                        pd_typedmess((t_pd *)x->f_inlets_extra[i][j], s, argc, argv);
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < x->f_ninlets_extra[x->f_target]; j++)
            {
                if(x->f_inlets_extra[x->f_target][j]->f_extra == extra)
                {
                    pd_typedmess((t_pd *)x->f_inlets_extra[x->f_target][j], s, argc, argv);
                }
            }
        }
    }
}

void hoa_process_get_thisprocess(t_hoa_process *x, int index, long argc, t_atom* argv)
{
    int i, offset;
    t_gobj *y;
    t_hoa_thisprocess *tp;
    for(y = x->f_canvas[index]->gl_list; y; y = y->g_next)
    {
        if(eobj_getclassname(y) == gensym("hoa.thisprocess~"))
        {
            tp = (t_hoa_thisprocess *)y;
            
            if(x->f_mode == 3)
            {
                atom_setsym(tp->f_hoa_mode, gensym("3d"));
                atom_setsym(tp->f_hoa_mode+1, gensym("planewaves"));
                atom_setfloat(tp->f_hoa_args, x->f_planewaves->getNumberOfChannels());
                atom_setfloat(tp->f_hoa_args+1, index+1);
            }
            else if(x->f_mode == 2)
            {
                atom_setsym(tp->f_hoa_mode, gensym("2d"));
                atom_setsym(tp->f_hoa_mode+1, gensym("planewaves"));
                atom_setfloat(tp->f_hoa_args, x->f_planewaves->getNumberOfChannels());
                atom_setfloat(tp->f_hoa_args+1, index+1);
            }
            else if(x->f_mode == 1)
            {
                atom_setsym(tp->f_hoa_mode, gensym("3d"));
                atom_setsym(tp->f_hoa_mode+1, gensym("harmonics"));
                atom_setfloat(tp->f_hoa_args, x->f_ambi_3d->getDecompositionOrder());
                atom_setfloat(tp->f_hoa_args+1, x->f_ambi_3d->getHarmonicDegree(index));
                atom_setfloat(tp->f_hoa_args+2, x->f_ambi_3d->getHarmonicOrder(index));
            }
            else
            {
                atom_setsym(tp->f_hoa_mode, gensym("2d"));
                atom_setsym(tp->f_hoa_mode+1, gensym("harmonics"));
                atom_setfloat(tp->f_hoa_args, x->f_ambi_2d->getDecompositionOrder());
                atom_setfloat(tp->f_hoa_args+1, x->f_ambi_2d->getHarmonicOrder(index));
            }
            
            if(tp->f_argc < atoms_get_attributes_offset(argc, argv))
            {
                free(tp->f_args);
                tp->f_argc = atoms_get_attributes_offset(argc, argv);
                tp->f_args = (t_atom *)calloc(tp->f_argc, sizeof(t_atom));
            }
            
            offset = atoms_get_attributes_offset(argc, argv);
            for(i = 0; i < offset; i++)
            {
                tp->f_args[i] = argv[i];
            }
            
            for(i = 0; i < tp->f_n_attrs; i++)
            {
                if(atoms_has_attribute(argc-offset, argv+offset, tp->f_attr_name[i]))
                {
                    free(tp->f_attr_vals[i]);
                    tp->f_attr_size[i] = 0;
                    atoms_get_attribute(argc-offset, argv+offset, tp->f_attr_name[i], &tp->f_attr_size[i], &tp->f_attr_vals[i]);
                }
            }
            tp->f_nit = 1;
               
        }
    }
}

void hoa_process_get_io(t_hoa_process *x, int index)
{
    t_gobj *y;
    t_hoa_in *inlet;
    t_hoa_out *outlet;
    t_hoa_in_tilde *inlet_sig;
    t_hoa_out_tilde *outlet_sig;
    
    x->f_ninlets_extra[index] = 0;
    x->f_ninlets_instance[index] = 0;
    x->f_noutlets_extra[index] = 0;
    x->f_noutlets_instance[index] = 0;
    
    x->f_ninlets_extra_sig[index] = 0;
    x->f_ninlets_instance_sig[index] = 0;
    x->f_noutlets_extra_sig[index] = 0;
    x->f_noutlets_instance_sig[index] = 0;
    
    for(y = x->f_canvas[index]->gl_list; y; y = y->g_next)
    {
        if(eobj_getclassname(y) == gensym("hoa.in"))
        {
            inlet = (t_hoa_in *)y;
            if(inlet->f_extra)
                x->f_ninlets_extra[index]++;
            else
                x->f_ninlets_instance[index]++;
        }
        else if(eobj_getclassname(y) == gensym("hoa.out"))
        {
            outlet = (t_hoa_out *)y;
            if(outlet->f_extra)
                x->f_noutlets_extra[index]++;
            else
                x->f_noutlets_instance[index]++;
        }
        else if(eobj_getclassname(y) == gensym("hoa.in~"))
        {
            inlet_sig = (t_hoa_in_tilde *)y;
            if(inlet_sig->f_extra)
                x->f_ninlets_extra_sig[index]++;
            else
                x->f_ninlets_instance_sig[index]++;
        }
        else if(eobj_getclassname(y) == gensym("hoa.out~"))
        {
            outlet_sig = (t_hoa_out_tilde *)y;
            if(outlet_sig->f_extra)
                x->f_noutlets_extra_sig[index]++;
            else
                x->f_noutlets_instance_sig[index]++;
        }
    }
    
    x->f_inlets_instance[index] = new t_hoa_in*[x->f_ninlets_instance[index]];
    x->f_inlets_extra[index]    = new t_hoa_in*[x->f_ninlets_extra[index]];
    
    x->f_outlets_instance[index] = new t_hoa_out*[x->f_ninlets_instance[index]];
    x->f_outlets_extra[index]    = new t_hoa_out*[x->f_ninlets_extra[index]];
    
    x->f_inlets_instance_sig[index] = new t_hoa_in_tilde*[x->f_ninlets_instance_sig[index]];
    x->f_inlets_extra_sig[index]    = new t_hoa_in_tilde*[x->f_ninlets_extra_sig[index]];
    
    x->f_outlets_instance_sig[index] = new t_hoa_out_tilde*[x->f_noutlets_instance_sig[index]];
    x->f_outlets_extra_sig[index]    = new t_hoa_out_tilde*[x->f_noutlets_extra_sig[index]];
    
    x->f_ninlets_extra[index] = 0;
    x->f_ninlets_instance[index] = 0;
    x->f_noutlets_extra[index] = 0;
    x->f_noutlets_instance[index] = 0;
    
    x->f_ninlets_extra_sig[index] = 0;
    x->f_ninlets_instance_sig[index] = 0;
    x->f_noutlets_extra_sig[index] = 0;
    x->f_noutlets_instance_sig[index] = 0;
    
    for(y = x->f_canvas[index]->gl_list; y; y = y->g_next)
    {
        if(eobj_getclassname(y) == gensym("hoa.in"))
        {
            inlet = (t_hoa_in *)y;
            if(inlet->f_extra)
                x->f_inlets_extra[index][x->f_ninlets_extra[index]++] = inlet;
            else
                x->f_inlets_instance[index][x->f_ninlets_instance[index]++] = inlet;
            
        }
        else if(eobj_getclassname(y) == gensym("hoa.out"))
        {
            outlet = (t_hoa_out *)y;
            if(outlet->f_extra)
                x->f_outlets_extra[index][x->f_noutlets_extra[index]++] = outlet;
            else
                x->f_outlets_instance[index][x->f_noutlets_instance[index]++] = outlet;
        }
        else if(eobj_getclassname(y) == gensym("hoa.in~"))
        {
            inlet_sig = (t_hoa_in_tilde *)y;
            if(inlet_sig->f_extra)
                x->f_inlets_extra_sig[index][x->f_ninlets_extra_sig[index]++] = inlet_sig;
            else
                x->f_inlets_instance_sig[index][x->f_ninlets_instance_sig[index]++] = inlet_sig;
        }
        else if(eobj_getclassname(y) == gensym("hoa.out~"))
        {
            outlet_sig = (t_hoa_out_tilde *)y;
            if(outlet_sig->f_extra)
                x->f_outlets_extra_sig[index][x->f_noutlets_extra_sig[index]++] = outlet_sig;
            else
                x->f_outlets_instance_sig[index][x->f_noutlets_instance_sig[index]++] = outlet_sig;
        }
    }
    
}

static void canvas_removefromlist(t_canvas *x)
{
    t_canvas *z;
    if (x == canvas_list)
        canvas_list = x->gl_next;
    else
    {
        for (z = canvas_list; z->gl_next != x; z = z->gl_next)
            ;
        z->gl_next = x->gl_next;
    }
}

void hoa_process_load_canvas(t_hoa_process *x, t_symbol *s, long argc, t_atom* argv)
{
    int fd;
    t_atom av[2];
    char dirbuf[MAXPDSTRING], *nameptr;
    int ncnv;
    int state = canvas_suspend_dsp();
    
    // Memory allocation for all the canvas, the inlets and the outlets
    x->f_canvas         = new t_canvas*[x->f_ncanvas];
    x->f_dsp_context    = new t_dspcontext*[x->f_ncanvas];
    
    x->f_ninlets_instance    = new long[x->f_ncanvas];
    x->f_inlets_instance    = new t_hoa_in**[x->f_ncanvas];
    
    x->f_ninlets_extra       = new long[x->f_ncanvas];
    x->f_inlets_extra       = new t_hoa_in**[x->f_ncanvas];
    
    x->f_noutlets_instance   = new long[x->f_ncanvas];
    x->f_outlets_instance   = new t_hoa_out**[x->f_ncanvas];
    
    x->f_noutlets_extra      = new long[x->f_ncanvas];
    x->f_outlets_extra      = new t_hoa_out**[x->f_ncanvas];
    
    x->f_ninlets_instance_sig    = new long[x->f_ncanvas];
    x->f_inlets_instance_sig    = new t_hoa_in_tilde**[x->f_ncanvas];
    
    x->f_ninlets_extra_sig       = new long[x->f_ncanvas];
    x->f_inlets_extra_sig       = new t_hoa_in_tilde**[x->f_ncanvas];
    
    x->f_noutlets_instance_sig   = new long[x->f_ncanvas];
    x->f_outlets_instance_sig   = new t_hoa_out_tilde**[x->f_ncanvas];
    
    x->f_noutlets_extra_sig      = new long[x->f_ncanvas];
    x->f_outlets_extra_sig      = new t_hoa_out_tilde**[x->f_ncanvas];
    
    
    for(int i = 0; i < x->f_ncanvas; i++)
    {
        x->f_canvas[i] = NULL;
        x->f_dsp_context[i] = NULL;
    }
    ncnv = x->f_ncanvas;
    x->f_ncanvas = 0;
    
    // Location of the file
    fd = canvas_open(canvas_getcurrent(), s->s_name, ".pd", dirbuf, &nameptr, MAXPDSTRING, 0);

    if(fd >= 0)
    {
  
        // Allocation of each canvas
        for(int i = 0; i < ncnv; i++)
        {
            x->f_canvas[i] = NULL;
            if(x->f_mode > 1)
            {
                atom_setfloat(av, i+1);
                canvas_setargs(1, av);
            }
            else if(x->f_mode == 1)
            {
                atom_setfloat(av, x->f_ambi_3d->getHarmonicDegree(i));
                atom_setfloat(av+1, x->f_ambi_3d->getHarmonicOrder(i));
                canvas_setargs(2, av);
            }
            else
            {
                atom_setfloat(av, x->f_ambi_2d->getHarmonicOrder(i));
                canvas_setargs(1, av);
            }
            
            // Load the canvas
            t_pd *boundx = s__X.s_thing;
            s__X.s_thing = 0;
            binbuf_evalfile(gensym(nameptr), gensym(dirbuf));
            while (( (t_pd *)x->f_canvas[i] != s__X.s_thing) && s__X.s_thing)
            {
                x->f_canvas[i] = (t_canvas *)s__X.s_thing;
                vmess((t_pd *)x->f_canvas[i], gensym("pop"), "i", 1);
            }
            
            s__X.s_thing = boundx;
            
            // If the canvas is loaded
            if(x->f_canvas[i])
            {
                hoa_process_get_thisprocess(x, i, argc, argv);
                
                x->f_canvas[i]->gl_owner = eobj_getcanvas(x);   // Set the owner of the canvas
                canvas_removefromlist(x->f_canvas[i]);          // Remove canvas from top level
                canvas_loadbang(x->f_canvas[i]);                // Send loadbang
                
                // Retrieve inlets and outlets of the canvas
                hoa_process_get_io(x, i);
                x->f_dsp_context[i] = dsp_context_new();
                x->f_ncanvas++;
                canvas_vis(x->f_canvas[i], 0);                  // Hide the canvas
            }
            else
            {
                canvas_setcurrent(eobj_getcanvas(x));
                pd_error(x, "hoa.process~ : error while loading canvas.");
				canvas_resume_dsp(state);
                return;
            }
        }
    }
    else
    {
        pd_error(x, "hoa.process~ : error while loading canvas.");
    }
    canvas_setcurrent(eobj_getcanvas(x));
    canvas_resume_dsp(state);
}

