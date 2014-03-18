/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../HoaCommon.pd.h"

typedef enum {
	HOA_OBJECT_AMBI_2D      =	0,
	HOA_OBJECT_AMBI_3D      =	1,
	HOA_OBJECT_PLANEWAVES   =	2,
}e_hoa_object_mode;

typedef struct _vinlet
{
    t_object x_obj;
    t_canvas *x_canvas;
    t_inlet *x_inlet;
    int x_bufsize;
    t_float *x_buf;         /* signal buffer; zero if not a signal */
    t_float *x_endbuf;
    t_float *x_fill;
    t_float *x_read;
    int x_hop;
    /* if not reblocking, the next slot communicates the parent's inlet
     signal from the prolog to the DSP routine: */
    t_signal *x_directsignal;
    
    t_resample x_updown;
} t_vinlet;

typedef struct _voutlet
{
    t_object x_obj;
    t_canvas *x_canvas;
    t_outlet *x_parentoutlet;
    int x_bufsize;
    t_sample *x_buf;         /* signal buffer; zero if not a signal */
    t_sample *x_endbuf;
    t_sample *x_empty;       /* next to read out of buffer in epilog code */
    t_sample *x_write;       /* next to write in to buffer */
    int x_hop;              /* hopsize */
    /* vice versa from the inlet, if we don't block, this holds the
     parent's outlet signal, valid between the prolog and the dsp setup
     routines.  */
    t_signal *x_directsignal;
    /* and here's a flag indicating that we aren't blocked but have to
     do a copy (because we're switched). */
    char x_justcopyout;
    t_resample x_updown;
} t_voutlet;

typedef struct _hoa_process
{
    t_edspobj           f_obj;
    e_hoa_object_mode   f_mode;
    
    Hoa2D::Ambisonic*   f_ambi_2d;
    Hoa3D::Ambisonic*   f_ambi_3d;
    Hoa2D::Planewaves*  f_planewaves;
    
    t_canvas**          f_canvas;
    int                 f_ninlets;
    t_vinlet***         f_inlets;
    int                 f_ninlets_sig;
    t_vinlet***         f_inlets_sig;
    int**               f_inlets_sig_index;
    
    int                 f_ninlets_extra;
    t_vinlet***         f_inlets_extra;
    int                 f_ninlets_sig_extra;
    t_vinlet***         f_inlets_sig_extra;
    int**               f_inlets_sig_extra_index;
    
    int                 f_noutlets;
    t_voutlet***        f_outlets;
    int                 f_noutlets_sig;
    t_voutlet***        f_outlets_sig;
    int**               f_outlets_sig_index;
    
    int                 f_noutlets_extra;
    t_voutlet***        f_outlets_extra;
    int                 f_noutlets_sig_extra;
    t_voutlet***        f_outlets_sig_extra;
    int**               f_outlets_sig_extra_index;
} t_hoa_process;

t_eclass *hoa_process_class;

void *hoa_process_new(t_symbol *s, long argc, t_atom *argv);
void hoa_process_free(t_hoa_process *x);
long hoa_process_get_number_of_inputs(t_hoa_process *x);
long hoa_process_get_number_of_outputs(t_hoa_process *x);

void hoa_process_dsp(t_hoa_process *x, t_signal **sp);
void hoa_process_load(t_hoa_process *x, t_eattr *attr, long argc, t_atom* argv);
void hoa_process_click(t_hoa_process *x);
void hoa_process_open(t_hoa_process *x, float f);
void hoa_process_float(t_hoa_process *x, float f);

t_hoa_err hoa_getinfos(t_hoa_process* x, t_hoa_boxinfos* boxinfos);

void hoa_process_load_canvas(t_hoa_process *x, t_symbol *s);

extern "C" void setup_hoa0x2eprocess_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.process~", (method)hoa_process_new, (method)hoa_process_free, (short)sizeof(t_hoa_process), 0, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_process_new, gensym("hoa.2d.process~"), A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_process_new, gensym("hoa.3d.process~"), A_GIMME, 0);
    
    eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
    class_addmethod((t_class *)c, (t_method)hoa_process_dsp, gensym("dsp"), A_CANT, 0);
    eclass_addmethod(c, (method)hoa_process_click,  "click",    A_CANT, 0);
    eclass_addmethod(c, (method)hoa_process_open,   "open",     A_FLOAT, 0);
    eclass_addmethod(c, (method)hoa_process_float,  "float",    A_FLOAT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_process_class = c;
}

void *hoa_process_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_process *x = NULL;
	int	argument = 1;
    
    if(argc < 1 || atom_gettype(argv) != A_LONG || atom_gettype(argv+1) != A_SYM)
    {
        error("%s needs at least two arguments, an integer and a symbol.", s->s_name);
        return NULL;
    }
    
    x = (t_hoa_process *)eobj_new(hoa_process_class);
	if(x)
	{
        argument = atom_getlong(argv);
        if(argument < 1)
            argument = 1;
        
        if(argc > 2 && atom_gettype(argv+2) == A_SYM && atom_getsym(argv+2) == gensym("planewaves"))
        {
            x->f_mode = HOA_OBJECT_PLANEWAVES;
            x->f_planewaves = new Hoa2D::Planewaves(argument);
        
        }
        else if(argc > 2 && atom_gettype(argv+2) == A_SYM && s == gensym("hoa.3d.process~"))
        {
            x->f_mode = HOA_OBJECT_AMBI_3D;
            x->f_ambi_3d = new Hoa3D::Ambisonic(argument);
        }
        else
        {
            x->f_mode = HOA_OBJECT_AMBI_2D;
            x->f_ambi_2d = new Hoa2D::Ambisonic(argument);
        }
        hoa_process_load_canvas(x, atom_getsym(argv+1));
        
        if(x->f_ninlets_sig)
            eobj_dspsetup(x, x->f_ambi_2d->getNumberOfHarmonics() + x->f_ninlets_sig_extra, 2);
        else
            eobj_dspsetup(x, x->f_ninlets_sig_extra, 2);
	}
    
    
	return x;
}

long hoa_process_get_number_of_inputs(t_hoa_process *x)
{
    if(x->f_mode == HOA_OBJECT_PLANEWAVES)
    {
        return x->f_planewaves->getNumberOfChannels();
    }
    else
        return 0;
}

long hoa_process_get_number_of_outputs(t_hoa_process *x)
{
    return 0;
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

void hoa_process_open(t_hoa_process *x, float f)
{
    if(f >= 0 && f <= 2)
    {
        canvas_vis(x->f_canvas[0], (int)f);
    }
}

void hoa_process_float(t_hoa_process *x, float f)
{
    t_atom av;
    atom_setfloat(&av, f);
    pd_typedmess((t_pd *)x->f_inlets[0][0], &s_float, 1, &av);
}

void hoa_process_dsp(t_hoa_process *x, t_signal **sp)
{
    post("hi");
}

void hoa_process_free(t_hoa_process *x)
{
    eobj_dspfree(x);
    for(int i = 0; i < 0; i++)
    {
        if(x->f_canvas[i])
            canvas_free(x->f_canvas[i]);
    }
    
    delete [] x->f_canvas;
    
}

void canvas_addtolist(t_canvas *x)
{
    x->gl_next = canvas_list;
    canvas_list = x;
}

void canvas_takeofflist(t_canvas *x)
{
    if (x == canvas_list) canvas_list = x->gl_next;
    else
    {
        t_canvas *z;
        for (z = canvas_list; z->gl_next != x; z = z->gl_next)
            ;
        z->gl_next = x->gl_next;
    }
}

void hoa_process_load_canvas(t_hoa_process *x, t_symbol *s)
{
    int fd;
    t_atom av;
    char* name;
    int size;
    char dirbuf[MAXPDSTRING], *nameptr;
    int number_of_canvas = 0;
    t_gobj *y;
    t_vinlet* inlet;
    t_voutlet* outlet;
    t_atom *argv;
    long    argc;
    if(x->f_mode == HOA_OBJECT_PLANEWAVES)
        number_of_canvas = x->f_planewaves->getNumberOfChannels();
    else if(x->f_mode == HOA_OBJECT_AMBI_3D)
        number_of_canvas = x->f_ambi_3d->getNumberOfHarmonics();
    else
        number_of_canvas = x->f_ambi_2d->getNumberOfHarmonics();
    
    x->f_canvas     = new t_canvas*[number_of_canvas];
    
    x->f_inlets     = new t_vinlet**[number_of_canvas];
    x->f_inlets_sig = new t_vinlet**[number_of_canvas];
    x->f_inlets_extra       = new t_vinlet**[number_of_canvas];
    x->f_inlets_sig_extra   = new t_vinlet**[number_of_canvas];
    
    x->f_outlets    = new t_voutlet**[number_of_canvas];
    x->f_outlets_sig = new t_voutlet**[number_of_canvas];
    x->f_outlets_extra       = new t_voutlet**[number_of_canvas];
    x->f_outlets_sig_extra   = new t_voutlet**[number_of_canvas];
    x->f_outlets_sig_extra_index = new int*[number_of_canvas];
    
    for(int i = 0; i < number_of_canvas; i++)
        x->f_canvas[i] = NULL;
    
    if((fd = canvas_open(canvas_getcurrent(), s->s_name, ".pd", dirbuf, &nameptr, MAXPDSTRING, 0)) >= 0)
    {
        for(int i = 0; i < number_of_canvas; i++)
        {
            x->f_canvas[i] = (t_canvas *)glob_evalfile(NULL, gensym(nameptr), gensym(dirbuf));
            if(x->f_canvas[i])
            {
                atom_setfloat(&av, i);
                canvas_setargs(1, &av);
                x->f_canvas[i]->gl_owner = eobj_getcanvas(x);
                canvas_vis(x->f_canvas[i], 0);
                canvas_takeofflist(x->f_canvas[i]);
                
                x->f_ninlets        = 0;
                x->f_noutlets       = 0;
                x->f_ninlets_sig    = 0;
                x->f_noutlets_sig   = 0;
                x->f_ninlets_extra      = 0;
                x->f_ninlets_sig_extra  = 0;
                x->f_noutlets_extra      = 0;
                x->f_noutlets_sig_extra  = 0;
                
                for(y = x->f_canvas[i]->gl_list; y; y = y->g_next)
                {
                    if(eobj_getclassname(y) == gensym("inlet"))
                    {
                        inlet = (t_vinlet *)y;
                        binbuf_gettext(inlet->x_obj.te_binbuf, &name, &size);
                        if(size && name)
                        {
                            binbuf_get_attribute(inlet->x_obj.te_binbuf, gensym("@extra"), &argc, &argv);
                            if(!strncmp(name, "inlet~", 6))
                            {
                                if(argc && argv)
                                    x->f_ninlets_sig_extra++;
                                else
                                    x->f_ninlets_sig++;
                            }
                            else
                            {
                                if(argc && argv)
                                    x->f_ninlets_extra++;
                                else
                                    x->f_ninlets++;
                            }
                        }
                    }
                    else if(eobj_getclassname(y) == gensym("outlet"))
                    {
                        outlet = (t_voutlet *)y;
                        binbuf_get_attribute(outlet->x_obj.te_binbuf, gensym("@extra"), &argc, &argv);
                        if(!strncmp(name, "outlet~", 6))
                        {
                            if(argc && argv)
                                x->f_noutlets_sig_extra++;
                            else
                                x->f_noutlets_sig++;
                        }
                        else
                        {
                            if(argc && argv)
                                x->f_noutlets_extra++;
                            else
                                x->f_noutlets++;
                        }
                    }
                }
                x->f_inlets[i]      = new t_vinlet*[x->f_ninlets];
                x->f_inlets_sig[i]  = new t_vinlet*[x->f_ninlets_sig];
                x->f_inlets_extra[i]      = new t_vinlet*[x->f_ninlets_extra];
                x->f_inlets_sig_extra[i]  = new t_vinlet*[x->f_ninlets_sig_extra];
                
                x->f_outlets[i]      = new t_voutlet*[x->f_noutlets];
                x->f_outlets_sig[i]  = new t_voutlet*[x->f_noutlets_sig];
                x->f_outlets_extra[i]      = new t_voutlet*[x->f_noutlets_extra];
                x->f_outlets_sig_extra[i]  = new t_voutlet*[x->f_noutlets_sig_extra];
                
                x->f_ninlets        = 0;
                x->f_noutlets       = 0;
                x->f_ninlets_sig    = 0;
                x->f_noutlets_sig   = 0;
                x->f_ninlets_extra      = 0;
                x->f_ninlets_sig_extra  = 0;
                x->f_noutlets_extra      = 0;
                x->f_noutlets_sig_extra  = 0;
                
                for(y = x->f_canvas[i]->gl_list; y; y = y->g_next)
                {
                    if(eobj_getclassname(y) == gensym("inlet"))
                    {
                        inlet = (t_vinlet *)y;
                        binbuf_gettext(inlet->x_obj.te_binbuf, &name, &size);
                        if(size && name)
                        {
                            binbuf_get_attribute(inlet->x_obj.te_binbuf, gensym("@extra"), &argc, &argv);
                            if(!strncmp(name, "inlet~", 6))
                            {
                                if(argc && argv)
                                    x->f_inlets_sig_extra[i][x->f_ninlets_sig_extra++] = inlet;
                                else
                                    x->f_inlets_sig[i][x->f_ninlets_sig++] = inlet;
                            }
                            else
                            {
                                if(argc && argv)
                                    x->f_inlets_extra[i][x->f_ninlets_extra++] = inlet;
                                else
                                    x->f_inlets[i][x->f_ninlets++] = inlet;
                            }
                        }
                    }
                    else if(eobj_getclassname(y) == gensym("outlet"))
                    {
                        outlet = (t_voutlet *)y;
                        binbuf_gettext(outlet->x_obj.te_binbuf, &name, &size);
                        if(size && name)
                        {
                            binbuf_get_attribute(outlet->x_obj.te_binbuf, gensym("@extra"), &argc, &argv);
                            if(!strncmp(name, "outlet~", 6))
                            {
                                if(argc && argv)
                                    x->f_outlets_sig_extra[i][x->f_noutlets_sig_extra++] = outlet;
                                else
                                    x->f_outlets_sig[i][x->f_noutlets_sig++] = outlet;
                            }
                            else
                            {
                                if(argc && argv)
                                    x->f_outlets_extra[i][x->f_noutlets_extra++] = outlet;
                                else
                                    x->f_outlets[i][x->f_noutlets++] = outlet;
                            }
                        }
                        
                    }
                }
                post("nombre d'inlets controle %i", x->f_ninlets);
                post("nombre d'inlets signal %i", x->f_ninlets_sig);
                post("nombre d'inlets controle extra %i", x->f_ninlets_extra);
                post("nombre d'inlets signal extra %i", x->f_ninlets_sig_extra);
                
                post("nombre d'outlets controle %i", x->f_noutlets);
                post("nombre d'outlets signal %i", x->f_noutlets_sig);
                post("nombre d'outlets controle extra %i", x->f_noutlets_extra);
                post("nombre d'outlets signal extra %i", x->f_noutlets_sig_extra);
            }
            else
            {
                canvas_setcurrent(eobj_getcanvas(x));
                return;
            }
        }
    }
    
    canvas_setcurrent(eobj_getcanvas(x));
}

