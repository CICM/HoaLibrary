/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa3D.max.h"

typedef struct _hoa_vector 
{
	t_pxobject              f_ob;
    double*                 f_sig_ins;
    double*                 f_sig_outs;
    Hoa3D::Vector*          f_vector;
    int                     f_mode;
} t_hoa_vector;

void *hoa_vector_new(t_symbol *s, long argc, t_atom *argv);
void hoa_vector_free(t_hoa_vector *x);
void hoa_vector_assist(t_hoa_vector *x, void *b, long m, long a, char *s);

void hoa_vector_bang(t_hoa_vector *x);

void hoa_vector_dsp64(t_hoa_vector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_vector_perform64_energy(t_hoa_vector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_vector_perform64_velocity(t_hoa_vector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_vector_setChannels(t_hoa_vector *x, t_symbol* s, long argc, t_atom* argv);
t_hoa_err hoa_getinfos(t_hoa_vector* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_vector_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.3d.vector~", (method)hoa_vector_new, (method)hoa_vector_free, (long)sizeof(t_hoa_vector), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_vector_dsp64,	"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_vector_assist,   "assist",	A_CANT, 0);
    class_addmethod(c, (method)hoa_vector_setChannels,   "lscoord",    A_GIMME, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_vector_class = c;
    
	return 0;
}

void *hoa_vector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_vector *x = NULL;
	int	numberOfChannels = 1;
    int mode = 1;
    x = (t_hoa_vector *)object_alloc(hoa_vector_class);
	if (x)
	{		
		if(argc && atom_gettype(argv) == A_LONG)
			numberOfChannels = atom_getlong(argv);
        if(numberOfChannels < 1)
            numberOfChannels = 1;
        
        if(argc > 1 && atom_gettype(argv+1) == A_SYM && atom_getsym(argv+1) == gensym("velocity"))
			mode = 0;
        
        x->f_mode = mode;
		
		x->f_vector = new Hoa3D::Vector(numberOfChannels);
		for (int i = 0; i < 3; i++)
			outlet_new(x, "signal");
        
		dsp_setup((t_pxobject *)x, x->f_vector->getNumberOfChannels());
        x->f_sig_ins =  new double[x->f_vector->getNumberOfChannels() * SYS_MAXBLKSIZE];
        x->f_sig_outs = new double[3 * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_vector* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = x->f_vector->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_vector_dsp64(t_hoa_vector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(x->f_mode)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_vector_perform64_energy, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_vector_perform64_velocity, 0, NULL);
        
}

void hoa_vector_perform64_energy(t_hoa_vector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_vector->processEnergy(x->f_sig_ins + i * numins, x->f_sig_outs + i * numouts);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_vector_perform64_velocity(t_hoa_vector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_vector->processVelocity(x->f_sig_ins + i * numins, x->f_sig_outs + i * numouts);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_vector_assist(t_hoa_vector *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
    {
        sprintf(s,"(Signal) %s", x->f_vector->getChannelName(a).c_str());
    }
    else
    {
        if(x->f_mode)
        {
            if(a == 0)
                sprintf(s,"(Signal) Energy Vector Abscissa");
            else if(a == 1)
                sprintf(s,"(Signal) Energy Vector Ordinate");
            else if(a == 2)
                sprintf(s,"(Signal) Energy Vector Height");
        }
        else
        {
            if(a == 0)
                sprintf(s,"(Signal) Velocity Vector Abscissa");
            else if(a == 1)
                sprintf(s,"(Signal) Velocity Vector Ordinate");
            else if(a == 2)
                sprintf(s,"(Signal) Velocity Vector Height");
        }
    }
}

void hoa_vector_free(t_hoa_vector *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_vector;
    delete [] x->f_sig_ins;
    delete [] x->f_sig_outs;
}

void hoa_vector_setChannels(t_hoa_vector *x, t_symbol* s, long argc, t_atom* argv)
{
    if(argc > 2 && argv && atom_gettype(argv) == A_LONG && atom_gettype(argv+1) == A_FLOAT && atom_gettype(argv+2) == A_FLOAT)
    {
        x->f_vector->setChannelPosition(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
    }
    for(int i = 0; i < x->f_vector->getNumberOfChannels(); i++)
    {
        post("ls %i %f %f", i, x->f_vector->getChannelAzimuth(i), x->f_vector->getChannelElevation(i));
        post("ls %i %f %f %f", i, x->f_vector->getChannelAbscissa(i), x->f_vector->getChannelOrdinate(i), x->f_vector->getChannelHeight(i));
    }
}
