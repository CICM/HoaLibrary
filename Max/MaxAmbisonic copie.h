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

#ifndef DEF_MAX_HOA
#define DEF_MAX_HOA

#include "MaxConverter.h"


/**************************************************************************************/
/******************************* AMBISONIC CLASSES ************************************/
/**************************************************************************************/
    
typedef struct _ambisonic
{
    long    order;
    double  color_positive[4];
	double  color_negative[4];
    long    auto_connect;
    
    long    argc;
    t_atom* argv;

    t_object* patcherview;
    
    long       number_of_object_to_keep;
    t_object** object_to_keep;
    
    long      line_selected;
    t_object* object_to_connect;
} t_ambisonic;

typedef struct _hoa_object
{
    t_pxobject			f_ob;
    t_ambisonic         f_hoa;
	Ambisonic*          f_ambi;
} t_hoa_object;

static void ambisonic_new(t_hoa_object* x, long argc, t_atom* argv);
static void ambisonic_free(t_hoa_object* x);
static void ambisonic_attach(t_hoa_object* x, t_symbol* sym, long argc, t_atom* argv);

class MaxAmbisonic
{
private:
    t_object*   m_parent;
    
    long        m_order;
    double      m_color_positive[4];
	double      m_color_negative[4];
    long        m_auto_connect;
    
    long        m_number_of_box_text_items;
    t_atom*     m_box_text_items;
    
    t_object*   m_box;
    t_object*   m_patcher;
    t_object*   m_patcherview;
    
    
    long        m_number_of_object_to_keep;
    t_object**  m_object_to_keep;
    
    long        m_line_selected;
    t_object*   m_object_to_connect;
public:
    MaxAmbisonic(t_object* aParentObject, long argc = 0, t_atom* argv = NULL);
    ~MaxAmbisonic();
};

/**************************************************************************************/
/********************************* INITIALIZATION *************************************/
/**************************************************************************************/

static void ambisonic_new(t_hoa_object* x, long argc, t_atom* argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
    {
        x->f_hoa.order = (long)atom_getfloat(argv);
    }
    x->f_hoa.argc = argc;
    x->f_hoa.argv = new t_atom[x->f_hoa.argc];
    for(int i = 0; i < x->f_hoa.argc; i++)
        x->f_hoa.argv[i] = argv[i];
    
    OBJ_ATTR_LONG           ((t_object *)x,"order", 0, x->f_hoa.order);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"order","label",    USESYM(symbol),0,"s",gensym_tr("Ambisonic Order"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","order",    USESYM(long),  0,"1");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"order","save",     USESYM(long),  1,"1");
    
    x->f_hoa.color_positive[0] = 0.;
    x->f_hoa.color_positive[1] = 0.;
    x->f_hoa.color_positive[2] = 1.;
    x->f_hoa.color_positive[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)x,"poscolor", 0, 4, x->f_hoa.color_positive);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"poscolor","label",    USESYM(symbol), 0,"s",gensym_tr("Positive Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","style",    USESYM(symbol), 0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","category", USESYM(symbol), 0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","order",    USESYM(long),   0,"2");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"poscolor","save",     USESYM(long),   0,"1");
    
    x->f_hoa.color_negative[0] = 1.;
    x->f_hoa.color_negative[1] = 0.;
    x->f_hoa.color_negative[2] = 0.;
    x->f_hoa.color_negative[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)x,"negcolor", 0, 4, x->f_hoa.color_negative);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"negcolor","label",    USESYM(symbol),0,"s",gensym_tr("Negative Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","style",    USESYM(symbol),0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","order",    USESYM(long),  0,"3");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"negcolor","save",     USESYM(long),  1,"1");
    
    x->f_hoa.auto_connect = 1;
    OBJ_ATTR_LONG           ((t_object *)x,"autoconnect", 0, x->f_hoa.auto_connect);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)x,"autoconnect","label",    USESYM(symbol),0,"s",gensym_tr("Auto Connection"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","style",    USESYM(symbol),0,"onoff");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","order",    USESYM(long),  0,"4");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)x,"autoconnect","save",     USESYM(long),  1,"1");
    
    x->f_hoa.line_selected = 0;
    x->f_hoa.number_of_object_to_keep = 0;
    x->f_hoa.object_to_keep = NULL;
    
    defer_low(x, (method)ambisonic_attach, NULL, NULL, NULL);
}

static void ambisonic_free(t_hoa_object* x)
{
    free(x->f_hoa.argv);
    object_detach_byptr(x, x->f_hoa.patcherview);
}

static void ambisonic_attach(t_hoa_object* x, t_symbol* sym, long argc, t_atom* argv)
{
    t_object* patcher;
    object_attach_byptr_register(x, x, CLASS_BOX);
    
    object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    
    x->f_hoa.patcherview = jpatcher_get_firstview(patcher);
    object_attach_byptr_register(x, x->f_hoa.patcherview, CLASS_NOBOX);
;
}

/**************************************************************************************/
/************************************ CONNECTION **************************************/
/**************************************************************************************/

static void ambisonic_connect_outlet(t_hoa_object* x)
{
    t_object *patcher;
    t_object *object_outlet;
    t_object *object_inlet;
    t_object *line;
    t_max_err err;
    
    err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);    
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
                int number_of_harmonics = object_attr_getlong(x, gensym("order")) * 2 + 1;
                if(object_attr_getlong(object_inlet, gensym("order")) * 2 + 1 < number_of_harmonics)
                    number_of_harmonics = object_attr_getlong(object_inlet, gensym("order")) * 2 + 1;
                
                CicmMax::connect_lines(patcher, object_outlet, object_inlet, number_of_harmonics);
            }
        }
    }
}

static void ambisonic_connect_outlet_with_line(t_hoa_object* x, t_object* line)
{
    t_object *patcher;
    t_object *outlet_object;
    t_object *inlet_object;
    t_max_err err;
    
    err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    err = object_obex_lookup(x, gensym("#B"), (t_object **)&outlet_object);    
    err = object_obex_lookup(jpatchline_get_box2(line), gensym("#B"), (t_object **)&inlet_object);
    
    if (err != MAX_ERR_NONE)
        return;
    
    int number_of_harmonics = x->f_hoa.order * 2 + 1;
    
    CicmMax::connect_lines(patcher, outlet_object, inlet_object, number_of_harmonics);
    x->f_hoa.line_selected = 0;
    x->f_hoa.object_to_connect = NULL;
}

static void ambisonic_connect_outlet_with_object(t_hoa_object* x, t_object* object)
{
    t_object *patcher;
    t_object *outlet_object;
    t_object *inlet_object;
    t_max_err err;
    
    err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    err = object_obex_lookup(x, gensym("#B"), (t_object **)&outlet_object);
    err = object_obex_lookup(object, gensym("#B"), (t_object **)&inlet_object);
    
    if (err != MAX_ERR_NONE)
        return;
    
    int number_of_harmonics = x->f_hoa.order * 2 + 1;
    
    CicmMax::connect_lines(patcher, outlet_object, inlet_object, number_of_harmonics);
    x->f_hoa.line_selected = 0;
    x->f_hoa.object_to_connect = NULL;
}

static void ambisonic_keep_inlet_objects(t_hoa_object* x, long index)
{
    t_object *patcher;
    t_object *object_outlet;
    t_object *object_inlet;
    t_object *line;
    t_max_err err;
    
    err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    err = object_obex_lookup(x, gensym("#B"), (t_object **)&object_inlet);
    if (err != MAX_ERR_NONE)
        return;
    
    x->f_hoa.number_of_object_to_keep = 0;
    if(x->f_hoa.object_to_keep)
        free(x->f_hoa.object_to_keep);
    
    for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
    {
        if(jpatchline_get_box2(line) == object_inlet && jpatchline_get_inletnum(line) == index)
        {
            x->f_hoa.number_of_object_to_keep++;
        }
    }
    x->f_hoa.object_to_keep = new t_object*[x->f_hoa.number_of_object_to_keep];
    int i = 0;
    for (line = jpatcher_get_firstline(patcher), i = 0; line; line = jpatchline_get_nextline(line), i++)
    {
        if(jpatchline_get_box2(line) == object_inlet && jpatchline_get_inletnum(line) == index)
        {
            object_outlet = jbox_get_object(jpatchline_get_box1(line));
            x->f_hoa.object_to_keep[i] = object_outlet;
        }
    }
    post("%ld", x->f_hoa.number_of_object_to_keep);
}

static void ambisonic_connect_keep_objects(t_hoa_object* x, long index)
{
    t_object *patcher;
    t_object *object_outlet;
    t_object *object_inlet;
    t_max_err err;
    
    object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    object_obex_lookup(x, gensym("#B"), (t_object **)&object_inlet);
    
    for(int i = 0; i < x->f_hoa.number_of_object_to_keep; i++)
    {
        //err = object_obex_lookup(x->f_hoa.object_to_keep[i], gensym("#B"), (t_object **)&object_outlet);
        //if (err != MAX_ERR_NONE)
          //  return;
        
        //CicmMax::connect_line(patcher, x->f_hoa.object_to_keep[i], 0, object_inlet, index);
        post("index %ld", index);
    }
    
    if(x->f_hoa.number_of_object_to_keep && x->f_hoa.object_to_keep)
        free(x->f_hoa.object_to_keep);
    x->f_hoa.number_of_object_to_keep = 0;
    x->f_hoa.object_to_keep = NULL;
}

/**************************************************************************************/
/************************************ COLORING ****************************************/
/**************************************************************************************/

static void ambisonic_color_inlet(t_object* x)
{
    t_object *patcher;
    t_object *object_inlet;
    t_object *line;
    t_max_err err;
    t_jrgba   color;
    
    err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
    if (err != MAX_ERR_NONE)
        return;
    
    err = object_obex_lookup(x, gensym("#B"), (t_object **)&object_inlet);
    if (err != MAX_ERR_NONE)
        return;
    
    for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
    {
        if(jpatchline_get_box1(line) == object_inlet)
        {
            if(jpatchline_get_inletnum(line)%2 == 0)
                object_attr_getjrgba(x, gensym("poscolor"), &color);
            else
                object_attr_getjrgba(x, gensym("negcolor"), &color);
            
            jpatchline_set_color(line, &color);
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

/**************************************************************************************/
/************************************ RENAME ******************************************/
/**************************************************************************************/

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

/**************************************************************************************/
/************************************ NOTIFY ******************************************/
/**************************************************************************************/

static void ambisonic_notify(t_hoa_object* x, t_symbol* msg, void *sender, void* data)
{
    if(msg == gensym("connect"))
    {
        ambisonic_connect_outlet((t_hoa_object *)x);
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
    if(sender == x->f_hoa.patcherview)
    {
        if(msg == gensym("attr_modified"))
        {
            t_symbol* attr_name = (t_symbol *)object_method(data, gensym("getname"));

            if(attr_name == gensym("dirty") && jkeyboard_getcurrentmodifiers() == 8)
            {
                t_atom obj[1];
                atom_setobj(obj, x->f_hoa.object_to_connect);
                defer_low(x, object_getmethod(x, gensym("connect")), gensym("connect"), 1, obj);
            }
            else if(attr_name == gensym("selectedlines"))
            {
                long ac = 0;
                t_atom *av = NULL;
                
                object_attr_getvalueof(sender, attr_name, &ac, &av);
        
                if(ac && atom_gettype(av) == A_OBJ)
                {
                    t_object* this_object;
                    t_object* line = (t_object *)atom_getobj(av);
                    
                    object_obex_lookup(x, gensym("#B"), (t_object **)&this_object);
                    
                    if(ac && jpatchline_get_box1(line) == this_object)
                    {
                        x->f_hoa.line_selected = 1;
                        x->f_hoa.object_to_connect = line;
                        if(jkeyboard_getcurrentmodifiers() == 24)
                        {
                            t_atom obj[1];
                            atom_setobj(obj, x->f_hoa.object_to_connect);
                            defer_low(x, object_getmethod(x, gensym("connect")), gensym("connect"), 1, obj);
                        }
                    }
                }
            }
            else
            {
                x->f_hoa.line_selected = 0;
                x->f_hoa.object_to_connect = NULL;
            }
            
            
        }
    }
}

#endif