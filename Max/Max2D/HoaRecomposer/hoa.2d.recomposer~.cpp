/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

typedef struct _hoa_recomposer 
{
	t_pxobject              f_ob;
	double*                 f_ins;
    double*                 f_outs;
    Hoa2D::Projector*       f_recomposer;
    t_symbol*               f_mode;
    double                  f_ramp;
    
} t_hoa_recomposer;

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv);
void hoa_recomposer_free(t_hoa_recomposer *x);
void hoa_recomposer_assist(t_hoa_recomposer *x, void *b, long m, long a, char *s);
void hoa_recomposer_float(t_hoa_recomposer *x, double d);
void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);
void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);

t_max_err mode_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv);
t_max_err ramp_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv);

t_max_err HoaRecomposer_notify(t_hoa_recomposer *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void hoa_recomposer_dsp64(t_hoa_recomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_recomposer_perform64(t_hoa_recomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_recomposer* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_recomposer_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.2d.recomposer~", (method)hoa_recomposer_new, (method)hoa_recomposer_free, (long)sizeof(t_hoa_recomposer), 0L, A_GIMME, 0);
    class_alias(c, gensym("hoa.recomposer~"));
	
    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_recomposer_dsp64,	"dsp64",            A_CANT, 0);
	class_addmethod(c, (method)hoa_recomposer_assist,   "assist",           A_CANT, 0);
    class_addmethod(c, (method)hoa_recomposer_angle,    "angles",           A_GIMME,0);
    class_addmethod(c, (method)hoa_recomposer_wide,     "directivities",    A_GIMME,0);
    class_addmethod(c, (method)hoa_recomposer_float,    "float",            A_FLOAT,0);
    
    CLASS_ATTR_SYM              (c,"mode", 0, t_hoa_recomposer, f_mode);
	CLASS_ATTR_LABEL			(c,"mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c,"mode", 0, "fixe fisheye free");
	CLASS_ATTR_CATEGORY			(c,"mode", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"mode", NULL, mode_set);
    CLASS_ATTR_ORDER			(c,"mode", 0,  "1");
    CLASS_ATTR_SAVE             (c,"mode", 1);
    
    CLASS_ATTR_DOUBLE			(c,"ramp", 0, t_hoa_recomposer, f_ramp);
	CLASS_ATTR_LABEL			(c,"ramp", 0, "Ramp Time in milliseconds");
	CLASS_ATTR_CATEGORY			(c,"ramp", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"ramp", NULL, ramp_set);
    CLASS_ATTR_ORDER			(c,"ramp", 0,  "2");
    CLASS_ATTR_SAVE             (c,"ramp", 1);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_recomposer_class = c;
    
	return 0;
}

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_recomposer *x = NULL;
	int	order = 1;
    int numberOfLoudspeakers = 10;
    x = (t_hoa_recomposer *)object_alloc(hoa_recomposer_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        if(atom_gettype(argv+1) == A_LONG)
			numberOfLoudspeakers = atom_getlong(argv+1);
        if(numberOfLoudspeakers < order * 2 + 1)
            numberOfLoudspeakers = order * 2 + 1;
		
		x->f_recomposer = new Hoa2D::Projector(order, numberOfLoudspeakers);
		
		dsp_setup((t_pxobject *)x, x->f_recomposer->getNumberOfHarmonics());
		for (int i = 0; i < x->f_recomposer->getNumberOfChannels(); i++)
			outlet_new(x, "signal");
        
		x->f_ins = new double[x->f_recomposer->getNumberOfChannels() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_recomposer->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_recomposer* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_recomposer->getNumberOfChannels();
	boxinfos->autoconnect_outputs = x->f_recomposer->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_recomposer_float(t_hoa_recomposer *x, double d)
{
    if(x->f_mode == gensym("fisheye"))
    {
        
    }
}

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(x->f_mode == gensym("free"))
    {
        
    }
}

void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(x->f_mode == gensym("free"))
    {
        
    }
}

void hoa_recomposer_dsp64(t_hoa_recomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(x->f_mode == gensym("fisheye"))
    {
        
    }
    else if(x->f_mode == gensym("fisheye"))
    {
        
    }
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_recomposer_perform64, 0, NULL);
}

void hoa_recomposer_perform64(t_hoa_recomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_recomposer->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_recomposer_assist(t_hoa_recomposer *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_OUTLET)
        sprintf(s,"(Signal) %s", x->f_recomposer->getHarmonicsName(a).c_str());
    else
        sprintf(s,"(Signal) %s", x->f_recomposer->getChannelName(a).c_str());
}


void hoa_recomposer_free(t_hoa_recomposer *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_recomposer;
    delete [] x->f_ins;
	delete [] x->f_outs;
}

t_max_err mode_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv)
{
    return 0;
}

t_max_err ramp_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv)
{
    return 0;
}

