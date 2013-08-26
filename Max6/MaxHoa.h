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

#ifndef DEF_MAX_HOA
#define DEF_MAX_HOA

#include "MaxConverter.h"

typedef struct _ambisonic
{
    long    order;
    double  color_positive[4];
	double  color_negative[4];
    long    auto_connect;
    
    long    argc;
    t_atom* argv;
    t_object* patcherview;
    
} t_ambisonic;

/**************************************************************************************/
/********************************* AMBISONIC CLASS ************************************/
/**************************************************************************************/

static void ambisonic_attach(t_object* x, t_symbol* sym, long argc, t_atom* argv)
{
    t_object * patcher;
    t_ambisonic *ambisonic = (t_ambisonic *)atom_getobj(argv);
    object_attach_byptr_register(x, x, CLASS_BOX);
    
    object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    ambisonic->patcherview = jpatcher_get_firstview(patcher);
    object_attach_byptr_register(x, jpatcher_get_firstview(patcher), CLASS_NOBOX);
}

static void ambisonic_new(t_object* x, t_ambisonic* ambisonic, long argc, t_atom* argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
    {
        ambisonic->order = (long)atom_getfloat(argv);
    }
    ambisonic->argc = argc;
    ambisonic->argv = new t_atom[ambisonic->argc];
    for(int i = 0; i < ambisonic->argc; i++)
        ambisonic->argv[i] = argv[i];
    
    OBJ_ATTR_LONG           ((t_object *)x,"order", 0, ambisonic->order);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"order","label",    USESYM(symbol),0,"s",gensym_tr("Ambisonic Order"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","order",    USESYM(long),  0,"1");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","save",     USESYM(long),  1,"1");
    
    ambisonic->color_positive[0] = 0.;
    ambisonic->color_positive[1] = 0.;
    ambisonic->color_positive[2] = 1.;
    ambisonic->color_positive[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)x,"poscolor", 0, 4, ambisonic->color_positive);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"poscolor","label",    USESYM(symbol), 0,"s",gensym_tr("Positive Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","style",    USESYM(symbol), 0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","category", USESYM(symbol), 0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","order",    USESYM(long),   0,"2");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","save",     USESYM(long),   0,"1");
    
    ambisonic->color_negative[0] = 1.;
    ambisonic->color_negative[1] = 0.;
    ambisonic->color_negative[2] = 0.;
    ambisonic->color_negative[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)x,"negcolor", 0, 4, ambisonic->color_negative);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"negcolor","label",    USESYM(symbol),0,"s",gensym_tr("Negative Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","style",    USESYM(symbol),0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","order",    USESYM(long),  0,"3");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","save",     USESYM(long),  1,"1");
    
    ambisonic->auto_connect = 1;
    OBJ_ATTR_LONG           ((t_object *)x,"autoconnect", 0, ambisonic->auto_connect);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"autoconnect","label",    USESYM(symbol),0,"s",gensym_tr("Auto Connection"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","style",    USESYM(symbol),0,"onoff");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","order",    USESYM(long),  0,"4");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","save",     USESYM(long),  1,"1");
    
    t_atom point[1];
    atom_setobj(point, (void *)ambisonic);
    defer_low(x, (method)ambisonic_attach, NULL, 1, point);
}

static void ambisonic_free(t_object* x, t_ambisonic* ambisonic)
{
    free(ambisonic->argv);
    object_detach_byptr(x, ambisonic->patcherview);
}

static void ambisonic_connect_outlet(t_object* x)
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
        if (jpatchline_get_box1(line) == object_outlet && jpatchline_get_outletnum(line) == 0)
        {
            object_inlet = jpatchline_get_box2(line);
            if(object_attr_getlong(object_inlet, gensym("order")) != 0 && jpatchline_get_inletnum(line) == 0)
            {
                int max_number_of_harmonics = object_attr_getlong(x, gensym("order")) * 2 + 1;
                if(object_attr_getlong(object_inlet, gensym("order")) * 2 + 1 < max_number_of_harmonics)
                    max_number_of_harmonics = object_attr_getlong(object_inlet, gensym("order"))  * 2 + 1;
                for(int i = 0; i < max_number_of_harmonics; i++)
                {
                    t_atom msg[4];
                    t_atom rv;
                    
                    atom_setobj(msg, object_outlet);
                    atom_setlong(msg + 1, i);
                    atom_setobj(msg + 2, object_inlet);
                    atom_setlong(msg + 3, i);
                    
                    object_method_typed(patcher, gensym("connect"), 4, msg, &rv);
                }
            }
        }
    }
}

static void ambisonic_color_outlet(t_object* x)
{
    t_object *patcher;
    t_object *object_outlet;
    t_object *line;
    t_max_err err;
    t_jrgba   color;
    
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
            if(jpatchline_get_outletnum(line)%2 == 0)
                object_attr_getjrgba(x, gensym("poscolor"), &color);
            else
                object_attr_getjrgba(x, gensym("negcolor"), &color);
            
            jpatchline_set_color(line, &color);
        }
    }
}

static void ambisonic_rename_object(t_object* x, int argc, t_atom* argv)
{
    t_max_err   err;
    t_object    *jbox_object;
    char        name[256];
    char        tempory[256];
    
    err = object_obex_lookup(x, gensym("#B"), (t_object **)&jbox_object);
    if (err != MAX_ERR_NONE)
        return;
    
    strcpy(name, jbox_get_maxclass(jbox_object)->s_name);
    for(int i = 0; i < argc; i++)
    {
        if(atom_gettype(argv+i) == A_SYM)
            sprintf(tempory, " %s", atom_getsym(argv+i)->s_name);
        else if(atom_gettype(argv+i) == A_LONG)
            sprintf(tempory, " %ld", (long)atom_getlong(argv+i));
        else if(atom_gettype(argv+i) == A_FLOAT)
            sprintf(tempory, " %f", atom_getfloat(argv+i));
        
        strcat(name, tempory);
    }
    object_method(jbox_get_textfield((t_object *)jbox_object), gensym("settext"), name);
}

static void ambisonic_notify(t_object* x, t_ambisonic* ambisonic, t_symbol* msg, void *sender, void* data)
{
    if(msg == gensym("connect"))
    {
        ambisonic_connect_outlet((t_object *)x);
        ambisonic_color_outlet((t_object *)x);
    }
    else if(msg == gensym("poscolor") || msg == gensym("negcolor"))
    {
        object_attr_setjrgba(x, msg, (t_jrgba *)data);
    }
    else if(msg == gensym("autoconnect") || msg == gensym("order"))
    {
        object_attr_setlong(x, msg, (long)data);
    }
    /*
    if(msg == gensym("attr_modified"))
	{
        if(sender == ambisonic->patcherview)
        {
            t_symbol* attr_name = (t_symbol *)object_method(data, gensym("getname"));
            if(attr_name == gensym("selectedlines"))
            {
                long ac = 0;
                t_atom *av = NULL;
                
                object_attr_getvalueof(sender, attr_name, &ac, &av);
                if(atom_gettype(av) == A_OBJ)
                {
                    t_object* object_outlet;
                    t_object* object_inlet;
                    t_object *patcher;
                    object_obex_lookup(x, gensym("#B"), (t_object **)&object_outlet);
                    object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
                    t_object* line = (t_object *)atom_getobj(av);
                    if(jpatchline_get_box1(line) == object_outlet)
                    {
                        object_inlet = jpatchline_get_box2(line);
                        //if(object_attr_getlong(object_inlet, gensym("order")) != 0 && jpatchline_get_inletnum(line) == 0)
                        {
                            
                            if(jkeyboard_getcurrentmodifiers() == eAltKey)
                            {
                                post("scope");
                                int max_number_of_harmonics = object_attr_getlong(x, gensym("order")) * 2 + 1;
                                post("%i", max_number_of_harmonics);
                                //if(object_attr_getlong(object_inlet, gensym("order")) * 2 + 1 < max_number_of_harmonics)
                                    //max_number_of_harmonics = object_attr_getlong(object_inlet, gensym("order"))  * 2 + 1;
                                for(int i = 0; i < max_number_of_harmonics; i++)
                                {
                                    t_atom msg[4];
                                    t_atom rv;
                                    
                                    atom_setobj(msg, object_outlet);
                                    atom_setlong(msg + 1, i);
                                    atom_setobj(msg + 2, object_inlet);
                                    atom_setlong(msg + 3, i);
                                    
                                    object_method_typed(patcher, gensym("connect"), 4, msg, &rv);
                                }
                            }
                        }
                    }
                }
                
            }
        }
    }*/
}

#endif