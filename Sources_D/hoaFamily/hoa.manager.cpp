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

#include "../MaxAmbisonic.h"

typedef struct _hoa_manager 
{
	t_pxobject			f_ob;
    
} t_hoa_manager;

void *hoa_manager_new(t_symbol *s, long argc, t_atom *argv);
void hoa_manager_free(t_hoa_manager *x);
void hoa_manager_assist(t_hoa_manager *x, void *b, long m, long a, char *s);

void hoa_manager_attach(t_hoa_manager *x);
void hoa_manager_connect(t_hoa_manager *x, t_symbol *s, long argc, t_atom* argv);
t_max_err hoa_manager_notify(t_hoa_manager *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void hoa_manager_dsp64(t_hoa_manager *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_manager_perform64(t_hoa_manager *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_manager_perform64_offset(t_hoa_manager *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* hoa_manager_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.manager", (method)hoa_manager_new, (method)dsp_free, (long)sizeof(t_hoa_manager), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_manager_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)hoa_manager_notify,  "notify",   A_CANT, 0);
    class_addmethod(c, (method)hoa_manager_connect, "connect",  A_GIMME, 0);
				
	class_register(CLASS_BOX, c);	
	hoa_manager_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoa_manager_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_manager *x = (t_hoa_manager *)object_alloc(hoa_manager_class);
	if (x)
	{
        defer_low(x, (method)hoa_manager_attach, NULL, NULL, NULL);
		x->f_ob.z_misc = Z_NO_INPLACE;
        
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
        
        t_dictionary* d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void hoa_manager_attach(t_hoa_manager *x)
{
	x->f_ambi_max->attach_to_notification();
}

void hoa_manager_dsp64(t_hoa_manager *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_wider->setVectorSize(maxvectorsize);
	if(count[x->f_ambi_wider->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, hoa_manager_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, hoa_manager_perform64_offset, 0, NULL);
}

void hoa_manager_perform64(t_hoa_manager *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambi_wider->process(ins, outs, ins[numins - 1]);
}

void hoa_manager_perform64_offset(t_hoa_manager *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{    
	x->f_ambi_wider->process(ins, outs);
}

void hoa_manager_assist(t_hoa_manager *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
		sprintf(s,"(Signal) %s", x->f_ambi_wider->getInputName(a).c_str());
	else
		sprintf(s,"(Signal) %s", x->f_ambi_wider->getOutputName(a).c_str());
}

void hoa_manager_connect(t_hoa_manager *x, t_symbol *s, long argc, t_atom* argv)
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

t_max_err hoa_manager_notify(t_hoa_manager *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    return x->f_ambi_max->notify(s, msg, sender, data);
}


void hoa_manager_free(t_hoa_manager *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambi_wider;
    delete x->f_ambi_max;
}

