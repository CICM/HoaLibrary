/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_MAX_CONVERTER
#define DEF_MAX_CONVERTER

#include "../Sources/HoaLibrary.h"

extern "C"
{    
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "commonsyms.h"
#include "ext_parameter.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
}

#define MAX_SPEAKER 256



class CicmMax
{
public:
    static t_jrgba cicmColorToMaxColor(color aCicmColor)
    {
        t_jrgba maxColor;
        maxColor.red = aCicmColor.red;
        maxColor.green = aCicmColor.green;
        maxColor.blue = aCicmColor.blue;
        maxColor.alpha = aCicmColor.alpha;
        return maxColor;
    }
    
    static t_jrgba jrgba_addContrast(t_jrgba baseColor, double contrast, bool preserveAlpha = true)
    {
        t_jrgba maxColor = baseColor;
        maxColor.red = Tools::clip(maxColor.red += contrast, 0., 1.);
        maxColor.green = Tools::clip(maxColor.green += contrast, 0., 1.);
        maxColor.blue = Tools::clip(maxColor.blue += contrast, 0., 1.);
        if(!preserveAlpha)
            maxColor.alpha = Tools::clip(maxColor.alpha += contrast, 0., 1.);
        return maxColor;
    }
    
    static t_pt maxPtToCartCoords(t_pt pt, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        t_pt cartPt = pt;
        cartPt.x = ((cartPt.x / aMaxRect->width * 2.) - 1.) / aZoomfactor;
        cartPt.y = ((-cartPt.y / aMaxRect->height * 2.) + 1.) / aZoomfactor;
        return cartPt;
    }
    
    static t_pt maxPtToCartCoords(double x, double y, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        t_pt cartPt = {x, y};
        cartPt.x = ((cartPt.x / aMaxRect->width * 2.) - 1.) / aZoomfactor;
        cartPt.y = ((-cartPt.y / aMaxRect->height * 2.) + 1.) / aZoomfactor;
        return cartPt;
    }
    
    static t_pt cartCoordsToCartMaxPt(t_pt pt, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        t_pt maxPt = pt;
        maxPt.x *= (aMaxRect->width*0.5) * aZoomfactor;
        maxPt.y *= (aMaxRect->height*0.5) * aZoomfactor;
        return maxPt;
    }
    
    static t_pt cartCoordsToMaxPt(t_pt pt, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        t_pt maxPt = pt;
        //maxPt.x = (maxPt.x * (aMaxRect->width*0.5) * aZoomfactor) + (aMaxRect->width*0.5);
        //maxPt.y = (maxPt.y * (aMaxRect->height*0.5) * aZoomfactor)+ (aMaxRect->width*0.5);
        maxPt.x = (maxPt.x * (aMaxRect->width*0.5) * aZoomfactor) + (aMaxRect->width*0.5);
        maxPt.y = -1*(maxPt.y * (aMaxRect->height*0.5) * aZoomfactor)+ (aMaxRect->height*0.5);
        return maxPt;
    }
    
    static double cicmAbscissaToMaxAbscissa(double aCicmAbscissa, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        return aMaxRect->width / 2. + aZoomfactor * aCicmAbscissa * aMaxRect->width / 2.;
    }
    
    static double cicmAbscissaToMaxOrdinate(double aCicmOrdinate, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        return aMaxRect->height / 2. + aZoomfactor * aCicmOrdinate * aMaxRect->height / -2.;
    }
    
    /**************************************************************************************/
    /*********************************** CONNECTION ***************************************/
    /**************************************************************************************/
    
    static inline void connect_line(t_object* patcher, t_object* outlet_object, int outlet_index, t_object* inlet_object, int inlet_index)
    {
        t_atom msg[4];
        t_atom rv;
        
        atom_setobj(msg, outlet_object);
        atom_setlong(msg + 1, outlet_index);
        atom_setobj(msg + 2, inlet_object);
        atom_setlong(msg + 3, inlet_index);
        
        object_method_typed(patcher, gensym("connect"), 4, msg, &rv);
    }
    
    static inline void connect_lines(t_object* patcher, t_object* outlet_object, t_object* inlet_object, int number_of_lines)
    {
        for(int i = 0; i < number_of_lines; i++)
        {
            connect_line(patcher, outlet_object, i, inlet_object, i);
        }
    }
    
    
    /**************************************************************************************/
    /*********************************** DSP UPDATE ***************************************/
    /**************************************************************************************/
    
    static t_atom* dsp_stop(t_object* x)
    {
        t_atom* state = new t_atom[1];
        if(!sys_getdspobjdspstate((t_object *)x))
        {
            atom_setsym(state, gensym("dsp_off"));
        }
        else
        {
            t_object* patch = NULL;
            t_object* dac = NULL;
     
            if(object_obex_lookup(x, gensym("#P"), (t_object **)&patch))
            {
                t_object* box;
                box = jpatcher_get_firstobject(patch);
                while(box)
                {
                    if(object_classname(jbox_get_object(box)) == gensym("dac~") || object_classname(jbox_get_object(box)) == gensym("ezdac~") || object_classname(jbox_get_object(box)) == gensym("adc~") || object_classname(jbox_get_object(box)) == gensym("ezadc~"))
                    {
                        dac = jbox_get_object(box);
                    }
                    
                    box = jbox_get_nextobject(box);
                }
            }
            if(dac == NULL)
            {
                atom_setsym(state, gensym("dsp_on"));
            }
            else
            {
                atom_setobj(state, dac);
            }
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        }
        return state;
    }
    
    static void dsp_start(t_atom* x)
    {
        if(atom_gettype(x) == A_SYM && atom_getsym(x) == gensym("dsp_off"))
        {
            free(x);
            return;
        }
        else if(atom_gettype(x) == A_SYM && atom_getsym(x) == gensym("dsp_on"))
        {
            free(x);
            object_method(gensym("dsp")->s_thing, gensym("start"));
        }
        else if(atom_gettype(x) == A_OBJ)
        {
            object_method(x, gensym("startwindow"));
            free(x);
        }
    }
    
    static void resize_inlet(t_object* x, long aNumberOfInlet)
    {
        int dspState = sys_getdspobjdspstate((t_object *)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        if(aNumberOfInlet <= 0)
            aNumberOfInlet = 1;
        
        t_object *b = NULL;
        object_obex_lookup(x, gensym("#B"), (t_object **)&b);
        object_method(b, gensym("dynlet_begin"));
        
        dsp_resize((t_pxobject*)x, aNumberOfInlet);
        object_method(b, gensym("dynlet_end"));
    }
    
    static void resize_outlet(t_object* x, long aNumberOfOutlet)
    {
        int dspState = sys_getdspobjdspstate((t_object *)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        if(aNumberOfOutlet <= 0)
            aNumberOfOutlet = 1;
        
        long num_outlet = outlet_count((t_object *)x);
        
        t_object *b = NULL;
        
        object_obex_lookup(x, gensym("#B"), (t_object **)&b);
        object_method(b, gensym("dynlet_begin"));
        
        if(num_outlet > aNumberOfOutlet)
        {
            for(int i = num_outlet; i > aNumberOfOutlet; i--)
            {
                outlet_delete(outlet_nth((t_object*)x, i-1));
            }
        }
        else if(num_outlet < aNumberOfOutlet)
        {
            for(int i = num_outlet; i < aNumberOfOutlet; i++)
            {
                outlet_append((t_object*)x, NULL, gensym("signal"));
            }
        }
        
        object_method(b, gensym("dynlet_end"));
    }
    
    static void connect_outlet(t_object* x)
    {
        t_object *patcher;
        t_object *object_outlet;
        t_object *object_inlet;
        t_object *line;
        t_max_err err;
        
        err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
        if (err != MAX_ERR_NONE)
            return;
        
        err = object_obex_lookup(x, gensym("#B"), (t_object **)&object_outlet);
        if (err != MAX_ERR_NONE)
            return;
        
        for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
        {
            if (jpatchline_get_box1(line) == object_outlet)
            {
                object_inlet = jpatchline_get_box2(line);
                if(outlet_count(jbox_get_object(object_inlet)) >= outlet_count((t_object *)x))
                {
                    for(int i = 0; i < outlet_count((t_object *)x); i++)
                    {
                        t_atom msg[4];
                        t_atom rv;
                        
                        atom_setobj(msg, object_outlet);
                        atom_setlong(msg + 1, i);
                        atom_setobj(msg + 2, object_inlet);
                        atom_setlong(msg + 3, i);
                        
                        object_method_typed(patcher , gensym("connect"), 4, msg, &rv);
                    }
                }
            }
        }
    }
    
    static bool is_dsp(t_object* x)
    {
        if(object_classname(x)->s_name[strlen(object_classname(x)->s_name)-1] == '~')
            return 1;
        else
            return 0;
    }
};

#endif /* defined(DEF_MAX_CONVERTER) */