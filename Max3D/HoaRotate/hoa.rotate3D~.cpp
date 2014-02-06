/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../Sources/Hoa3D/Hoa3D.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _hoa_rotate 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Rotate*          f_rotate;
    
} t_hoa_rotate;


void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv);
void hoa_rotate_free(t_hoa_rotate *x);
void hoa_rotate_assist(t_hoa_rotate *x, void *b, long m, long a, char *s);

void hoa_rotate_float(t_hoa_rotate *x, double f);
void hoa_rotate_int(t_hoa_rotate *x, long n);

void hoa_rotate_dsp64(t_hoa_rotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_rotate_perform64_roll_pitch_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_roll(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_roll_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_roll_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64_pitch_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_rotate_perform64(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_rotate_class;


int C74_EXPORT main(void)
{

	t_class *c;
	
	c = class_new("hoa.rotate3D~", (method)hoa_rotate_new, (method)hoa_rotate_free, (long)sizeof(t_hoa_rotate), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_rotate_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_rotate_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_rotate_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_rotate_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_rotate_class = c;
    
    class_findbyname(CLASS_BOX, gensym("hoa.encoder3D~"));
    
	return 0;
}

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_rotate *x = NULL;
	int	order = 4;

    x = (t_hoa_rotate *)object_alloc(hoa_rotate_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_rotate = new Hoa3D::Rotate(order);
		
		dsp_setup((t_pxobject *)x, x->f_rotate->getNumberOfInputs());
		for (int i = 0; i < x->f_rotate->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        
        x->f_signals =  new double[x->f_rotate->getNumberOfOutputs() * SYS_MAXBLKSIZE];
	}

	return (x);
}

void hoa_rotate_float(t_hoa_rotate *x, double f)
{
	long nbIns = x->f_rotate->getNumberOfInputs();
	if(proxy_getinlet((t_object *)x) == nbIns - 3)
    {
        x->f_rotate->setRoll(f);
    }
	else if(proxy_getinlet((t_object *)x) == nbIns - 2)
    {
        x->f_rotate->setPitch(f);
    }
	else if(proxy_getinlet((t_object *)x) == nbIns - 1)
    {
        x->f_rotate->setYaw(f);
    }
}

void hoa_rotate_int(t_hoa_rotate *x, long n)
{
    long nbIns = x->f_rotate->getNumberOfInputs();
	if(proxy_getinlet((t_object *)x) == nbIns - 3)
    {
        x->f_rotate->setRoll(n);
    }
	else if(proxy_getinlet((t_object *)x) == nbIns - 2)
    {
        x->f_rotate->setPitch(n);
    }
	else if(proxy_getinlet((t_object *)x) == nbIns - 1)
    {
        x->f_rotate->setYaw(n);
    }
}

void hoa_rotate_dsp64(t_hoa_rotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	bool roll, pitch, yaw;
	roll = count[x->f_rotate->getNumberOfInputs() - 3];
	pitch = count[x->f_rotate->getNumberOfInputs() - 2];
	yaw = count[x->f_rotate->getNumberOfInputs() - 1];
	
    if(roll && pitch && yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_roll_pitch_yaw, 0, NULL);
	else if(roll && !pitch && !yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_roll, 0, NULL);
	else if(!roll && pitch && !yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_pitch, 0, NULL);
	else if(!roll && !pitch && yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_yaw, 0, NULL);
	else if(roll && pitch && !yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_roll_pitch, 0, NULL);
	else if(roll && !pitch && yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_roll_yaw, 0, NULL);
	else if(!roll && pitch && yaw)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64_pitch_yaw, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_rotate_perform64, 0, NULL);
}

void hoa_rotate_perform64_roll_pitch_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRotations(ins[numins-3][i], ins[numins-2][i], ins[numins-1][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setPitch(ins[numins-2][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
		x->f_rotate->setPitch(ins[numins-2][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
		x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_pitch_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setPitch(ins[numins-2][i]);
		x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_assist(t_hoa_rotate *x, void *b, long m, long a, char *s)
{
	long nbIns = x->f_rotate->getNumberOfInputs();
	
	if ( (m == ASSIST_INLET) && (a >= nbIns-3) )
	{
		if (a == nbIns - 3)
		{
			sprintf(s,"(Signal or float) x-axis tilt (roll)");
		}
		else if (a == nbIns - 2)
		{
			sprintf(s,"(Signal or float) y-axis tumble (pitch)");
		}
		else if (a == nbIns - 1)
		{
			sprintf(s,"(Signal or float) z-axis rotation (yaw)");
		}
		
	}
	else 
	{
		sprintf(s,"(Signal) %s", x->f_rotate->getHarmonicsName(a).c_str());
	}
}


void hoa_rotate_free(t_hoa_rotate *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_rotate;
    delete [] x->f_signals;
}

