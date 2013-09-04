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
    
    m_order = 1;
    if(argc && (atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT))
        m_order = atom_getfloat(argv);
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
        m_number_of_box_text_items = argc;
        m_box_text_items = new t_atom[m_number_of_box_text_items];
        for(int i = 0; i < m_number_of_box_text_items; i++)
            m_box_text_items[i] = argv[i];
    }
    else
    {
        m_number_of_box_text_items = argc+1;
        m_box_text_items = new t_atom[m_number_of_box_text_items];
        atom_setlong(m_box_text_items, m_order);
        for(int i = 1; i < m_number_of_box_text_items; i++)
            m_box_text_items[i] = argv[i-1];
    }    
    
    m_line_selected = 0;
    defer_low(m_parent, (method)hoa_attach, NULL, argc, argv);
    rename_box();
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

void MaxAmbisonic::attach()
{
    object_attach_byptr_register(m_parent, m_parent, CLASS_BOX);
    object_obex_lookup(m_parent, gensym("#P"), (t_object **)&m_patcher);
    object_obex_lookup(m_parent, gensym("#B"), (t_object **)&m_box);
    m_patcherview = jpatcher_get_firstview(m_patcher);
    object_attach_byptr_register(m_parent, m_patcherview, CLASS_NOBOX);
    
    t_dictionary* d = (t_dictionary *)gensym("#D")->s_thing;
    if (d) attr_dictionary_process(m_parent, d);
    attr_args_process(m_parent, m_number_of_box_text_items, m_box_text_items);
}

void MaxAmbisonic::save_to_dictionary(t_dictionary* d)
{
    if(d)
    {
        char        name[256];
        char        tempory[256];
        
        strcpy(name, object_classname(m_parent)->s_name);
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
        dictionary_appendstring(d, gensym("text"), name);
    }
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

    strcpy(name, object_classname(m_parent)->s_name);
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
    
    defer_low(m_parent, (method)CicmMax::rename_box, gensym(name), NULL, NULL);
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

int postons = 0;

void class_hoainit(t_class* c)
{
    if(c->c_sym != gensym("hoa.encoder~"))
        class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
    else
    {
        if(!postons)
        {
            post("hoa.library (version 1.3) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
            post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
            postons = 1;
        }
    }
    class_addmethod(c, (method)hoa_notify,   "notify",   A_CANT, 0);
    class_addmethod(c, (method)hoa_save,     "appendtodictionary",    A_CANT, 0);
    class_addmethod(c, (method)hoa_connect,  "connect",  A_GIMME, 0);
    class_addmethod(c, (method)hoa_assist,   "assist",	A_CANT, 0);
}

t_max_err hoa_notify(t_hoa_object_all *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    return x->f_ambi_max->notify(s, msg, sender, data);
}

void hoa_save(t_hoa_object_all *x, t_dictionary *d)
{
    x->f_ambi_max->save_to_dictionary(d);
}

void hoa_attach(t_hoa_object_all *x, t_symbol *s, long argc, t_atom *argv)
{
	x->f_ambi_max->attach();
}

void hoa_connect(t_hoa_object_all *x, t_symbol *s, long argc, t_atom* argv)
{
    if(!argc)
    {
        x->f_ambi_max->connect_outlets();
        x->f_ambi_max->color_outlets();
        x->f_ambi_max->connect_inlets();
        x->f_ambi_max->color_inlets();
    }
    else if(argc == 2 && atom_gettype(argv) == A_OBJ)
    {
        if(atom_getsym(argv+1) == gensym("outlet"))
        {
            x->f_ambi_max->connect_outlets_with_line((t_object *)atom_getobj(argv));
            x->f_ambi_max->color_outlets();
        }
        else if(atom_getsym(argv+1) == gensym("inlet"))
        {
            x->f_ambi_max->connect_inlets_with_line((t_object *)atom_getobj(argv));
            x->f_ambi_max->color_inlets();
        }
        
    }
}

void hoa_assist(t_hoa_object_all *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_ambi_optim->getHarmonicsName(a).c_str());
}







