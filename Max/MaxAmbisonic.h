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

#ifndef DEF_MAX_AMBISONIC
#define DEF_MAX_AMBISONIC

#include "MaxConverter.h"

typedef struct _hoa_object
{
	t_pxobject			f_ob;
	Ambisonic*          f_ambi;
    
} t_hoa_object;

class MaxAmbisonic
{
protected:
    t_hoa_object*   m_parent;
    
    long        m_order;
    double      m_color_positive[4];
	double      m_color_negative[4];
    long        m_auto_connect;
    
    long        m_number_of_box_text_items;
    t_atom*     m_box_text_items;
    
    t_object*   m_box;
    t_object*   m_patcher;
    t_object*   m_patcherview;
    
    vector <t_object*>  m_retained_objects;
    vector <long>       m_retained_outlets;
    
    long        m_line_selected;
    t_object*   m_line_to_connect;
    
public:
    MaxAmbisonic(t_hoa_object* aParentObject, long argc = 0, t_atom* argv = NULL);
    
    long getOrder();
    void setOrder(long anOrder);
    
    void attach();
    void save_to_dictionary(t_dictionary* d);
    
    void connect_outlets();
    void connect_inlets();
    void connect_outlets_with_line(t_object* line);
    void connect_inlets_with_line(t_object* line);
    void color_inlets();
    void color_outlets();
    void retain_objects();
    void relink_objects();
    void clear_last_inlet();
    
    void rename_box();
    
    virtual void realloc_ambisonic() = 0;
    t_max_err notify(t_symbol *s, t_symbol *msg, void *sender, void *data);
    
    virtual ~MaxAmbisonic();
};

/**************************************************************************************/
/*************************** HOA CLASS FUNCTION ***************************************/
/**************************************************************************************/

typedef struct _hoa_object_all
{
	t_pxobject          f_ob;
	AmbisonicOptim*		f_ambi_optim;
    MaxAmbisonic*       f_ambi_max;
    
} t_hoa_object_all;

void class_hoainit(t_class* c);
t_max_err hoa_notify(t_hoa_object_all *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void hoa_save(t_hoa_object_all *x, t_dictionary *d);
void hoa_attach(t_hoa_object_all *x, t_symbol *s, long argc, t_atom *argv);
void hoa_connect(t_hoa_object_all *x, t_symbol *s, long argc, t_atom* argv);
void hoa_assist(t_hoa_object_all *x, void *b, long m, long a, char *s);
t_max_err hoa_attr_order_set(t_object *x, t_object *attr, long argc, t_atom *argv);

#endif