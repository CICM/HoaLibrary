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