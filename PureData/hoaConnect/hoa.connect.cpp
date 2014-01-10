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

typedef struct _hoa_connect
{
    t_eobj      f_obj;

} t_hoa_connect;

void *hoa_connect_new(t_symbol *s, long argc, t_atom *argv);
void hoa_connect_free(t_hoa_connect *x);
void hoa_connect_bang(t_hoa_connect *x);

t_eclass *hoa_connect_class;

extern "C" void setup_hoa0x2econnect(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.connect", (method)hoa_connect_new, (method)hoa_connect_free, (short)sizeof(t_hoa_connect), 0, A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_connect_bang,          "bang",             A_CANT, 0);
    
    eclass_register(CLASS_BOX, c);
    hoa_connect_class = c;
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
}

void *hoa_connect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_connect *x = (t_hoa_connect *)eobj_new(hoa_connect_class);
    
    return (x);
}

void hoa_connect_bang(t_hoa_connect *x)
{
    int i, j, index = 0;
    int x1, x2, y1, y2;
    int nx1, nx2, ny1, ny2;
    t_gobj *y = NULL;
    t_gobj *list[256];
    t_outconnect *oc;
    for(y = eobj_getcanvas(x)->gl_list; y; y = y->g_next)
    {
        if(strncmp(eobj_getclassname(y)->s_name, "hoa.", 4) == 0 && glist_isselected(eobj_getcanvas(x), y))
        {
            gobj_getrect(y, eobj_getcanvas(x), &nx1, &ny1, &nx2, &ny2);
            for(i = 0; i < index; i++)
            {
                gobj_getrect(list[i], eobj_getcanvas(x), &x1, &y1, &x2, &y2);
                if(ny1 < y1 || (ny1 == y1 && nx1 < x1))
                {
                    for(j = index; j > i; j--)
                    {
                        list[j] = list[j-1];
                    }
                    list[i] = y;
                    index = pd_clip_max(index+1, 255);
                    break;
                }
            }
            if(i == index)
            {
                list[index] = y;
                index = pd_clip_max(index+1, 255);
            }
            
        }
    }
    for(i = 0; i < index-1; i++)
    {
        for(j = 0; j < obj_noutlets((t_object *)list[i]) && j < obj_ninlets((t_object *)list[i+1]); j++)
        {
            obj_disconnect((t_object *)list[i], j, (t_object *)list[i+1], j);
            oc = obj_connect((t_object *)list[i], j, (t_object *)list[i+1], j);
            if(glist_isvisible(eobj_getcanvas(x)))
            {
                sys_vgui(".x%lx.c create line %d %d %d %d -width %d -fill black -tags [list l%lx cord]\n",
                         glist_getcanvas(eobj_getcanvas(x)), 0, 0, 0, 0,
                         (obj_issignaloutlet((t_object *)list[i], j) ? 2 : 1),
                          oc);
            }
           
        }
        canvas_fixlinesfor(eobj_getcanvas(x), (t_text *)list[i]);
    }
}

void hoa_connect_free(t_hoa_connect *x)
{
    eobj_free(x);
}
