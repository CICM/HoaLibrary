/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa3D.max.h"

typedef struct _hoa_rotate 
{
	t_pxobject              f_ob;
	double*                 f_ins;
    double*                 f_outs;
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

t_hoa_err hoa_getinfos(t_hoa_rotate* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_rotate_class;

int C74_EXPORT main(void)
{

	t_class *c;
	
	c = class_new("hoa.3d.rotate~", (method)hoa_rotate_new, (method)hoa_rotate_free, (long)sizeof(t_hoa_rotate), 0L, A_GIMME, 0);
	
    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_rotate_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_rotate_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_rotate_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_rotate_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_rotate_class = c;
    
	return 0;
}

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_rotate *x = NULL;
	int	order = 1;
    x = (t_hoa_rotate *)object_alloc(hoa_rotate_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_rotate = new Hoa3D::Rotate(order);
		
		dsp_setup((t_pxobject *)x, x->f_rotate->getNumberOfHarmonics() + 3);
		for (int i = 0; i < x->f_rotate->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
        
		x->f_ins = new double[x->f_rotate->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_rotate->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_rotate* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_rotate->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_rotate->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_rotate_float(t_hoa_rotate *x, double f)
{
	if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics())
    {
        x->f_rotate->setRoll(f);
    }
	else if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics() + 1)
    {
        x->f_rotate->setPitch(f);
    }
	else if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics() + 2)
    {
        x->f_rotate->setYaw(f);
    }
}

void hoa_rotate_int(t_hoa_rotate *x, long n)
{
	if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics())
    {
        x->f_rotate->setRoll(n);
    }
	else if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics() + 1)
    {
        x->f_rotate->setPitch(n);
    }
	else if(proxy_getinlet((t_object *)x) == x->f_rotate->getNumberOfHarmonics() + 2)
    {
        x->f_rotate->setYaw(n);
    }
}

void hoa_rotate_dsp64(t_hoa_rotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	bool roll, pitch, yaw;
	roll = count[x->f_rotate->getNumberOfHarmonics()];
	pitch = count[x->f_rotate->getNumberOfHarmonics() + 1];
	yaw = count[x->f_rotate->getNumberOfHarmonics() + 2];
	
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
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRotations(ins[numins-3][i], ins[numins-2][i], ins[numins-1][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setPitch(ins[numins-2][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll_pitch(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
		x->f_rotate->setPitch(ins[numins-2][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_roll_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setRoll(ins[numins-3][i]);
		x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64_pitch_yaw(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setPitch(ins[numins-2][i]);
		x->f_rotate->setYaw(ins[numins-1][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_perform64(t_hoa_rotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_assist(t_hoa_rotate *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
	{
		if (a == x->f_rotate->getNumberOfHarmonics())
		{
			sprintf(s,"(Signal or float) Roll (X Axis)");
		}
		else if (a == x->f_rotate->getNumberOfHarmonics() + 1)
		{
			sprintf(s,"(Signal or float) Pitch (Y Axis)");
		}
		else if (a == x->f_rotate->getNumberOfHarmonics() + 2)
		{
			sprintf(s,"(Signal or float) Yaw (Z Axis)");
		}
        else
        {
            sprintf(s,"(Signal) %s", x->f_rotate->getHarmonicsName(a).c_str());
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
    delete [] x->f_ins;
	delete [] x->f_outs;
}

