/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// TODO : LINE DE AZIMUT ELEVATION ET DISTANCE

#include "../hoa.max.h"

int postons = 0;

typedef struct _hoa_map 
{
	t_pxobject      f_ob;
    double*         f_sig_ins;
    double*         f_sig_outs;
    Hoa3D::Map*     f_map;
    
} t_hoa_map;


void *hoa_map_new(t_symbol *s, long argc, t_atom *argv);
void hoa_map_free(t_hoa_map *x);
void hoa_map_assist(t_hoa_map *x, void *b, long m, long a, char *s);

void hoa_map_float(t_hoa_map *x, double f);
void hoa_map_int(t_hoa_map *x, long n);
void hoa_map_list(t_hoa_map *x, t_symbol* s, long argc, t_atom* argv);

void hoa_map_dsp64(t_hoa_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);

void hoa_map_perform64_multisources(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_map_perform64(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_map_perform64_azimuth(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_elevation(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_map_perform64_azimuth_elevation(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_azimuth_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_elevation_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_map_perform64_azimuth_elevation_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_map_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.map3D~", (method)hoa_map_new, (method)hoa_map_free, (long)sizeof(t_hoa_map), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_map_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_map_int,         "int",		A_LONG, 0);
    class_addmethod(c, (method)hoa_map_list,        "list",		A_GIMME, 0);
	class_addmethod(c, (method)hoa_map_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_map_assist,      "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_map_class = c;
	return 0;
}

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_map->getNumberOfSources();
	boxinfos->autoconnect_outputs = x->f_map->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_map *x = NULL;
	int	order = 1;
    int numberOfSources = 1;
    x = (t_hoa_map *)object_alloc(hoa_map_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
        if(atom_gettype(argv+1) == A_LONG)
            numberOfSources = atom_getlong(argv+1);

		x->f_map = new Hoa3D::Map(order, numberOfSources);
		if(x->f_map->getNumberOfSources() == 1)
            dsp_setup((t_pxobject *)x, 4);
        else
            dsp_setup((t_pxobject *)x, x->f_map->getNumberOfSources());
		
		for (int i = 0; i < x->f_map->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        x->f_sig_ins =  new double[x->f_map->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_sig_outs =  new double[x->f_map->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}
    
	return (x);
}

void hoa_map_float(t_hoa_map *x, double f)
{
    if(x->f_map->getNumberOfSources() == 1)
    {
        if(proxy_getinlet((t_object *)x) == 1)
        {
            x->f_map->setAzimuth(0, f);
        }
        else if(proxy_getinlet((t_object *)x) == 2)
        {
            x->f_map->setElevation(0, f);
        }
        else if(proxy_getinlet((t_object *)x) == 3)
        {
            x->f_map->setDistance(0, f);
        }
    }
    
}

void hoa_map_int(t_hoa_map *x, long n)
{
	if(x->f_map->getNumberOfSources() == 1)
    {
        if(proxy_getinlet((t_object *)x) == 1)
        {
            x->f_map->setAzimuth(0, n);
        }
        else if(proxy_getinlet((t_object *)x) == 2)
        {
            x->f_map->setElevation(0, n);
        }
        else if(proxy_getinlet((t_object *)x) == 3)
        {
            x->f_map->setDistance(0, n);
        }
    }
}

void hoa_map_list(t_hoa_map *x, t_symbol* s, long argc, t_atom* argv)
{
    if(argc && argv && atom_gettype(argv) == A_LONG)
    {
        int index = atom_getlong(argv);
        if(index < 0)
            return;
        if(index > x->f_map->getNumberOfSources() - 1)
            return;
        if(argc > 1 && atom_gettype(argv+1) == A_FLOAT)
            x->f_map->setAzimuth(index, atom_getfloat(argv+1));
        if(argc > 2 && atom_gettype(argv+2) == A_FLOAT)
            x->f_map->setElevation(index, atom_getfloat(argv+2));
        if(argc > 3 && atom_gettype(argv+3) == A_FLOAT)
            x->f_map->setDistance(index, atom_getfloat(argv+3));
    }
}

void hoa_map_dsp64(t_hoa_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(x->f_map->getNumberOfSources() == 1)
    {
        if(!count[1] && !count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64, 0, NULL);
        else if(count[1] && !count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth, 0, NULL);
        else if(!count[1] && count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_elevation, 0, NULL);
        else if(!count[1] && !count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_distance, 0, NULL);
        else if(count[1] && count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth_elevation, 0, NULL);
        else if(count[1] && !count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth_distance, 0, NULL);
        else if(!count[1] && count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_elevation_distance, 0, NULL);
        else
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth_elevation_distance, 0, NULL);
    }
    else
    {
        object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_multisources, 0, NULL);
    }
}

void hoa_map_perform64_multisources(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->process(x->f_sig_ins + numins * i, x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_azimuth(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setAzimuth(0, ins[1][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_elevation(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setElevation(0, ins[2][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setDistance(0, ins[3][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_azimuth_elevation(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setAzimuth(0, ins[1][i]);
        x->f_map->setElevation(0, ins[2][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_azimuth_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setAzimuth(0, ins[1][i]);
        x->f_map->setDistance(0, ins[3][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_elevation_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setElevation(0, ins[2][i]);
        x->f_map->setDistance(0, ins[3][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_azimuth_elevation_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setAzimuth(0, ins[1][i]);
        x->f_map->setElevation(0, ins[2][i]);
        x->f_map->setDistance(0, ins[3][i]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_assist(t_hoa_map *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
	{
        if(x->f_map->getNumberOfSources() == 1)
        {
            if(a == 0)
                sprintf(s,"(Signal) Input");
            else if(a == 1)
                sprintf(s,"(Signal or float) Azimuth");
            else if(a == 2)
                sprintf(s,"(Signal or float) Elevation");
            else
                sprintf(s,"(Signal or float) Distance");
        }
        else
        {
            if(a == 0)
                sprintf(s,"(Signal and messages) Input 0 and sources coordinates");
            else
                sprintf(s,"(Signal or float) Input %ld", a);
        }
        
	}
	else 
	{
		sprintf(s,"(Signal) %s", x->f_map->getHarmonicsName(a).c_str());
	}
}


void hoa_map_free(t_hoa_map *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_map;
    delete [] x->f_sig_ins;
    delete [] x->f_sig_outs;
}

