/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

typedef struct _hoa_canvas
{
    t_object    x_obj;
    t_canvas*   x_canvas;
    t_inlet*    x_inlets;
    t_inlet*    x_sig_inlets;
    float       x_f;
} t_hoa_canvas;

void *hoa_canvas_new(t_symbol *s, long argc, t_atom *argv);
void hoa_canvas_free(t_hoa_canvas *x);
void hoa_canvas_dsp(t_hoa_canvas *x, t_signal **sp);

t_class *hoa_canvas_class;

extern "C" void setup_hoa0x2ecanvas_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.canvas~"), (t_newmethod)hoa_canvas_new, (t_method)hoa_canvas_free, (short)sizeof(t_hoa_canvas), 0, A_GIMME, 0);
    CLASS_MAINSIGNALIN(c, t_hoa_canvas, x_f);
    
    class_addmethod(c, (t_method)hoa_canvas_dsp, gensym("dsp"), A_CANT, 0);
    
    hoa_canvas_class = c;
    hoa_post();
}

void *hoa_canvas_new(t_symbol *s, long argc, t_atom *argv)
{
    t_atom av[3];
    
    atom_setfloat(av, 0);
	t_hoa_canvas *x = (t_hoa_canvas *)pd_new(hoa_canvas_class);
    t_canvas* owner = canvas_getcurrent();
    x->x_canvas = canvas_new(0, 0, 0, NULL);
    canvas_vis(x->x_canvas, 0);
    pd_typedmess((t_pd *)x->x_canvas, gensym("pop"), 1, av);
    canvas_setcurrent(owner);
    
    if(argc && atom_gettype(argv) == A_SYM)
    {
        
        
        atom_setfloat(av, 0);
        atom_setfloat(av+1, 20);
        atom_setsym(av+2, atom_getsym(argv));
        pd_typedmess((t_pd *)x->x_canvas, gensym("obj"), 3, av);
    }
    
    canvas_loadbang(x->x_canvas);
    canvas_vis(x->x_canvas, 1);
    
    outlet_new((t_object *)x, &s_signal);
    return (x);
}

void hoa_canvas_dsp(t_hoa_canvas *x, t_signal **sp)
{
    ;
}

void hoa_canvas_free(t_hoa_canvas *x)
{
    ;
}
