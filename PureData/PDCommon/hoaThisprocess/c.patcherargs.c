/*
 * PdEnhanced - Pure Data Enhanced
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "../../Sources/cicm_wrapper.h"

typedef struct  _patcherargs
{
	t_eobj      j_box;
    t_canvas*   f_canvas;
	t_outlet*   f_out_args;
    t_outlet*   f_out_attrs;
    t_outlet*   f_out_done;
    
    t_atom*     f_args;
    long        f_argc;
    
    long        f_n_attrs;
    t_symbol*   f_attr_name[256];
    t_atom*     f_attr_vals[256];
    long        f_attr_size[256];
    double      f_time;
    
} t_patcherargs;

t_eclass *patcherargs_class;

void *patcherargs_new(t_symbol *s, int argc, t_atom *argv);
void patcherargs_output(t_patcherargs *x);
void patcherargs_free(t_patcherargs *x);
void patcherargs_assist(t_patcherargs *x, void *b, long m, long a, char *s);
void patcherargs_click(t_patcherargs *x);
void patcherargs_bang(t_patcherargs *x);

void setup_c0x2epatcherargs(void)
{
	t_eclass *c;
    
	c = eclass_new("c.patcherargs", (method)patcherargs_new, (method)patcherargs_free, (short)sizeof(t_patcherargs), 0L, A_GIMME, 0);
   
    eclass_addmethod(c, (method)patcherargs_output,      "bang",       A_CANT, 0);
    eclass_addmethod(c, (method)patcherargs_click,       "click",      A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    cicm_post();
	patcherargs_class = c;
}

void *patcherargs_new(t_symbol *s, int argc, t_atom *argv)
{
    int i;
	t_patcherargs *x =  NULL;
    
    x = (t_patcherargs *)eobj_new(patcherargs_class);
    if(x)
    {
        // ARGUMENTS //
        for(i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_SYM && atom_getsym(argv+i)->s_name[0] == '@')
            {
                break;
            }
        }
        x->f_argc = pd_clip_min(i, 0);
        x->f_args = (t_atom *)calloc(x->f_argc, sizeof(t_atom));
        for(i = 0; i < x->f_argc; i++)
        {
            x->f_args[i] = argv[i];
        }
        
        // ATTRIBUTES //
        x->f_n_attrs = 0;
        for(i = x->f_argc; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_SYM && atom_getsym(argv+i)->s_name[0] == '@')
            {
                if(x->f_n_attrs < 256)
                {
                    x->f_attr_name[x->f_n_attrs] = atom_getsym(argv+i);
                    x->f_n_attrs++;
                }
            }
        }
        for(i = 0; i < x->f_n_attrs; i++)
        {
            atoms_get_attribute(argc-x->f_argc, argv+x->f_argc, x->f_attr_name[i], &x->f_attr_size[i], &x->f_attr_vals[i]);
        }
        
        if(canvas_getcurrent())
        {
            x->f_canvas = glist_getcanvas(canvas_getcurrent());
        }
        else
            x->f_canvas = NULL;
        
        x->f_out_args = (t_outlet *)listout(x);
        x->f_out_attrs = (t_outlet *)listout(x);
        x->f_out_done = (t_outlet *)bangout(x);
        x->f_time = clock_getsystime();
    }
    
    return (x);
}

void patcherargs_click(t_patcherargs *x)
{
    if(clock_gettimesince(x->f_time) < 250.)
        patcherargs_output(x);
    x->f_time = clock_getsystime();
}

void patcherargs_output(t_patcherargs *x)
{
    int i, size = 0, ac = 0;
    t_binbuf *b = NULL;
    t_atom  *av = NULL;
    t_atom  *argv = NULL;
    long argc = 0;
    if(x->f_canvas)
    {
        b = x->f_canvas->gl_obj.te_binbuf;
		
        if(b)
        {
            ac = binbuf_getnatom(b);
            av = binbuf_getvec(b);
            if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("pd"))
            {
                ac--;
                av++;
            }
            for(i = 0; i < ac; i++)
            {
                if(atom_gettype(av+i) == A_SYM && strchr(atom_getsym(av+i)->s_name,'@'))
                {
                    break;
                }
            }
            size = i;
        }
        if(size > 0 && size >= x->f_argc)
        {
			outlet_list(x->f_out_args, &s_list, size, av);
        }
        else if(size > 0)
        {
			for(i = 0; i < size; i++)
				x->f_args[i] = av[i];
			outlet_list(x->f_out_args, &s_list, x->f_argc, x->f_args);
        }
		else
		{
			outlet_list(x->f_out_args, &s_list,x->f_argc, x->f_args);
		}
		for(i = 0; i < x->f_n_attrs; i++)
		{
			if(size > 0 && ac && av)
				atoms_get_attribute(ac, av, x->f_attr_name[i], &argc, &argv);
			if(argc && argv)
			{
				outlet_anything(x->f_out_attrs, gensym(x->f_attr_name[i]->s_name+1), argc, argv);
				free(argv);
				argc = 0;
			}
			else
			{
				outlet_anything(x->f_out_attrs, gensym(x->f_attr_name[i]->s_name+1), x->f_attr_size[i], x->f_attr_vals[i]);
			}
		}
    }
    else
    {
        outlet_list(x->f_out_args, &s_list, x->f_argc, x->f_args);
        for(i = 0; i < x->f_n_attrs; i++)
            outlet_list(x->f_out_attrs, &s_list, x->f_attr_size[i], x->f_attr_vals[i]);
    }
    outlet_bang(x->f_out_done);
}

void patcherargs_free(t_patcherargs *x)
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
    eobj_free(x);
}

void patcherargs_assist(t_patcherargs *x, void *b, long m, long a, char *s)
{
	;
}


