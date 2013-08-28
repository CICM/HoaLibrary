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

#include "MaxAmbisonic.h"

MaxAmbisonic::MaxAmbisonic(t_hoa_object* aParentObject, long argc, t_atom* argv)
{
	m_parent = aParentObject;
    
    OBJ_ATTR_LONG           ((t_object *)m_parent,"order", 0, m_order);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)m_parent,"order","label",    USESYM(symbol),0,"s",gensym_tr("Ambisonic Order"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"order","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"order","order",    USESYM(long),  0,"1");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"order","save",     USESYM(long),  1,"1");
    
    m_color_positive[0] = 0.;
    m_color_positive[1] = 0.;
    m_color_positive[2] = 1.;
    m_color_positive[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)m_parent,"poscolor", 0, 4, m_color_positive);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)m_parent,"poscolor","label",    USESYM(symbol), 0,"s",gensym_tr("Positive Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"poscolor","style",    USESYM(symbol), 0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"poscolor","category", USESYM(symbol), 0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"poscolor","order",    USESYM(long),   0,"2");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"poscolor","save",     USESYM(long),   0,"1");
    
    m_color_negative[0] = 1.;
    m_color_negative[1] = 0.;
    m_color_negative[2] = 0.;
    m_color_negative[3] = 1.;
    OBJ_ATTR_DOUBLE_ARRAY   ((t_object *)m_parent,"negcolor", 0, 4, m_color_negative);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)m_parent,"negcolor","label",    USESYM(symbol),0,"s",gensym_tr("Negative Color"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"negcolor","style",    USESYM(symbol),0,"rgba");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"negcolor","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"negcolor","order",    USESYM(long),  0,"3");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"negcolor","save",     USESYM(long),  1,"1");
    
    m_auto_connect = 1;
    OBJ_ATTR_LONG           ((t_object *)m_parent,"autoconnect", 0, m_auto_connect);
    OBJ_ATTR_ATTR_FORMAT    ((t_object *)m_parent,"autoconnect","label",    USESYM(symbol),0,"s",gensym_tr("Auto Connection"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"autoconnect","style",    USESYM(symbol),0,"onoff");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"autoconnect","category", USESYM(symbol),0,str_tr("HoaLibrary"));
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"autoconnect","order",    USESYM(long),  0,"4");
    OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"autoconnect","save",     USESYM(long),  1,"1");
    
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
    {
        m_order = (long)atom_getfloat(argv);
    }
    m_number_of_box_text_items = argc;
    m_box_text_items = new t_atom[m_number_of_box_text_items];
    for(int i = 0; i < m_number_of_box_text_items; i++)
        m_box_text_items[i] = argv[i];
    
    m_line_selected = 0;
}

long MaxAmbisonic::getOrder()
{
    return m_order;
}

void MaxAmbisonic::setOrder(long anOrder)
{
    m_order = anOrder;
    atom_setlong(m_box_text_items, m_order);
    object_attr_touch((t_object *)m_parent, gensym("order"));
}

void MaxAmbisonic::attach_to_notification()
{
    object_attach_byptr_register(m_parent, m_parent, CLASS_BOX);
    object_obex_lookup(m_parent, gensym("#P"), (t_object **)&m_patcher);
    object_obex_lookup(m_parent, gensym("#B"), (t_object **)&m_box);
    m_patcherview = jpatcher_get_firstview(m_patcher);
    object_attach_byptr_register(m_parent, m_patcherview, CLASS_NOBOX);
}

void MaxAmbisonic::connect_outlets()
{
    for(t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if (jpatchline_get_box1(line) == m_box && inlet_count(jbox_get_object(jpatchline_get_box2(line))) >= m_order * 2 + 1)
        {
            CicmMax::connect_lines(m_patcher, m_box, jpatchline_get_box2(line), m_order * 2 + 1);
        }
    }
}

void MaxAmbisonic::connect_inlets()
{
    for(t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if (jpatchline_get_box2(line) == m_box && outlet_count(jbox_get_object(jpatchline_get_box1(line))) >= m_order * 2 + 1)
        {
            CicmMax::connect_lines(m_patcher, jpatchline_get_box1(line), m_box, m_order * 2 + 1);
        }
    }
}

void MaxAmbisonic::connect_outlets_with_line(t_object* line)
{
    t_object *obj;
    t_max_err err = object_obex_lookup(jpatchline_get_box2(line), gensym("#B"), (t_object **)&obj);
    if (err != MAX_ERR_NONE)
        return;
    
    if(CicmMax::is_dsp(jbox_get_object(jpatchline_get_box1(line))) && inlet_count(jbox_get_object(obj)) >= m_order * 2 + 1)
    {
        CicmMax::connect_lines(m_patcher, m_box, obj, m_order * 2 + 1);
    }

    m_line_selected = 0;
    m_line_to_connect = NULL;
}

void MaxAmbisonic::connect_inlets_with_line(t_object* line)
{
    t_object *obj;
    t_max_err err = object_obex_lookup(jpatchline_get_box1(line), gensym("#B"), (t_object **)&obj);
    if (err != MAX_ERR_NONE)
        return;
    
    if(CicmMax::is_dsp(jbox_get_object(jpatchline_get_box1(line))) && outlet_count(jbox_get_object(obj)) >= m_order * 2 + 1)
    {
        CicmMax::connect_lines(m_patcher, obj, m_box, m_order * 2 + 1);
    }
    
    m_line_selected = 0;
    m_line_to_connect = NULL;
}

void MaxAmbisonic::color_inlets()
{
    t_jrgba   color;
    for (t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if(jpatchline_get_box2(line) == m_box && jpatchline_get_inletnum(line) < m_order * 2 + 1 && CicmMax::is_dsp(jbox_get_object(jpatchline_get_box1(line))))
        {

            if(jpatchline_get_inletnum(line) % 2 == 0)
                object_attr_getjrgba(m_parent, gensym("poscolor"), &color);
            else
                object_attr_getjrgba(m_parent, gensym("negcolor"), &color);
            
            jpatchline_set_color(line, &color);
        }
    }
}

void MaxAmbisonic::color_outlets()
{
    t_jrgba   color;
    for (t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if(jpatchline_get_box1(line) == m_box && jpatchline_get_outletnum(line) < m_order * 2 + 1 && CicmMax::is_dsp(jbox_get_object(jpatchline_get_box1(line))))
        {
            if(jpatchline_get_outletnum(line) % 2 == 0)
                object_attr_getjrgba(m_parent, gensym("poscolor"), &color);
            else
                object_attr_getjrgba(m_parent, gensym("negcolor"), &color);
            
            jpatchline_set_color(line, &color);
        }
    }
}

void MaxAmbisonic::rename_box()
{
    char        name[256];
    char        tempory[256];

    strcpy(name, jbox_get_maxclass(m_box)->s_name);
    sprintf(tempory, " %ld", m_order);
    strcat(name, tempory);
    for(int i = 1; i < m_number_of_box_text_items; i++)
    {
        if(atom_gettype(m_box_text_items+i) == A_SYM)
            sprintf(tempory, " %s", atom_getsym(m_box_text_items+i)->s_name);
        else if(atom_gettype(m_box_text_items+i) == A_LONG)
            sprintf(tempory, " %ld", (long)atom_getlong(m_box_text_items+i));
        else if(atom_gettype(m_box_text_items+i) == A_FLOAT)
            sprintf(tempory, " %f", atom_getfloat(m_box_text_items+i));
        
        strcat(name, tempory);
    }
    object_method(jbox_get_textfield((t_object *)m_box), gensym("settext"), name);
}

void MaxAmbisonic::retain_objects()
{
    m_retained_objects.clear();
    m_retained_outlets.clear();
    t_object* old_line = NULL;
    for (t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if(old_line)
            CicmMax::disconnect_line(m_patcher, jpatchline_get_box1(old_line), jpatchline_get_outletnum(old_line), m_box, m_order * 2 + 1);
        if(jpatchline_get_box2(line) == m_box && jpatchline_get_inletnum(line) == m_order * 2 + 1)
        {            
            m_retained_objects.push_back(jpatchline_get_box1(line));
            m_retained_outlets.push_back(jpatchline_get_outletnum(line));
            old_line = line;
        }
    }
    if(old_line)
        CicmMax::disconnect_line(m_patcher, jpatchline_get_box1(old_line), jpatchline_get_outletnum(old_line), m_box, m_order * 2 + 1);
}

void MaxAmbisonic::relink_objects()
{
    for(int i = 0; i < m_retained_objects.size(); i++)
    {
        CicmMax::connect_line(m_patcher, m_retained_objects[i], m_retained_outlets[i], m_box, m_order * 2 + 1);
    }
    m_retained_objects.clear();
    m_retained_outlets.clear();
}

void MaxAmbisonic::clear_last_inlet()
{
    for (t_object* line = jpatcher_get_firstline(m_patcher); line; line = jpatchline_get_nextline(line))
    {
        if(jpatchline_get_box2(line) == m_box && jpatchline_get_inletnum(line) == m_order * 2 + 1)
        {
            CicmMax::disconnect_line(m_patcher, jpatchline_get_box1(line), jpatchline_get_outletnum(line), m_box, m_order * 2 + 1);
        }
    }
}

t_max_err MaxAmbisonic::notify(t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if(msg == gensym("attr_modified"))
	{
		t_symbol* attr_name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
        if(attr_name == gensym("order"))
        {
            if(object_attr_getlong(m_parent, gensym("order")) != m_parent->f_ambi->getOrder())
            {
                t_atom* state = CicmMax::dsp_stop((t_object *)m_parent);
                retain_objects();
                delete(m_parent->f_ambi);
                realloc_ambisonic();
                m_order = m_parent->f_ambi->getOrder();
                
                CicmMax::resize_inlet((t_object *)m_parent, m_parent->f_ambi->getNumberOfInputs());
                CicmMax::resize_outlet((t_object *)m_parent, m_parent->f_ambi->getNumberOfOutputs());
                rename_box();
                
                clear_last_inlet();
                relink_objects();
                if(object_attr_getlong(m_parent, gensym("autoconnect")))
                {
                    object_method(m_parent, gensym("connect"));
                }
                
                object_attr_setlong(m_parent, gensym("order"), m_parent->f_ambi->getOrder());
                CicmMax::dsp_start(state);
            }
        }
        else if(attr_name == gensym("poscolor") || attr_name == gensym("negcolor"))
        {
            
            color_outlets();
            color_inlets();
        }
    }

    if(msg == gensym("connect"))
    {
        connect_outlets();
        color_outlets();
    }
    else if(msg == gensym("poscolor") || msg == gensym("negcolor"))
    {
        object_attr_setjrgba(m_parent, msg, (t_jrgba *)data);
    }
    else if(msg == gensym("autoconnect") || msg == gensym("order"))
    {
        object_attr_setlong(m_parent, msg, (long)data);
    }
    if(sender == m_patcherview)
    {
        if(msg == gensym("attr_modified"))
        {
            t_symbol* attr_name = (t_symbol *)object_method(data, gensym("getname"));
            
            if(attr_name == gensym("dirty") && jkeyboard_getcurrentmodifiers() == 8)
            {
                t_atom obj[2];
                atom_setobj(obj, m_line_to_connect);
                if(jpatchline_get_box2(m_line_to_connect) == m_box)
                    atom_setsym(obj+1, gensym("inlet"));
                else
                    atom_setsym(obj+1, gensym("outlet"));
                defer_low(m_parent, object_getmethod(m_parent, gensym("connect")), gensym("connect"), 2, obj);
            }
            else if(attr_name == gensym("selectedlines"))
            {
                long ac = 0;
                t_atom *av = NULL;
                
                object_attr_getvalueof(sender, attr_name, &ac, &av);
                
                if(ac && atom_gettype(av) == A_OBJ)
                {
                    t_object* line = (t_object *)atom_getobj(av);
                    
                    if(ac && (jpatchline_get_box1(line) == m_box || jpatchline_get_box2(line) == m_box))
                    {
                        m_line_selected = 1;
                        m_line_to_connect = line;
                        if(jkeyboard_getcurrentmodifiers() == 24)
                        {
                            t_atom obj[2];
                            atom_setobj(obj, m_line_to_connect);
                            if(jpatchline_get_box2(m_line_to_connect) == m_box)
                                atom_setsym(obj+1, gensym("inlet"));
                            else
                                atom_setsym(obj+1, gensym("outlet"));
                            defer_low(m_parent, object_getmethod(m_parent, gensym("connect")), gensym("connect"), 2, obj);
                        }
                    }
                }
            }
            else
            {
                m_line_selected = 0;
                m_line_to_connect = NULL;
            }            
        }
    }
    return MAX_ERR_NONE;
}

MaxAmbisonic::~MaxAmbisonic()
{
	free(m_box_text_items);
    object_detach_byptr(m_parent, m_patcherview);
}

