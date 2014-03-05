/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// TODO : LINE DE AZIMUT ELEVATION ET DISTANCE

#include "../Hoa2D.max.h"
#include "Line.h"

typedef enum {
	HOA_MODE_POL	=	0,
	HOA_MODE_CAR	=	1
} e_hoa_mode;

typedef struct _hoa_map 
{
	t_pxobject      f_ob;
	Hoa2D::Map		*f_map;
    double			*f_sig_ins;
    double			*f_sig_outs;
	t_symbol		*f_mode_sym;
    e_hoa_mode		f_mode;
    float           f_ramp;
	Line			**f_lines_x;
	Line			**f_lines_y;
	double			f_first_radius;
	double			f_first_azimuth;
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

void hoa_map_perform64_in1(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_in2(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_in1_in2(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err hoa_map_mode(t_hoa_map *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_map_ramp(t_hoa_map *x, t_object *attr, long argc, t_atom *argv);

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_map_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.2d.map~", (method)hoa_map_new, (method)hoa_map_free, (long)sizeof(t_hoa_map), 0L, A_GIMME, 0);
	
	class_alias(c, gensym("hoa.map~"));
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_map_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_map_int,         "int",		A_LONG, 0);
    class_addmethod(c, (method)hoa_map_list,        "list",		A_GIMME, 0);
	class_addmethod(c, (method)hoa_map_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_map_assist,      "assist",	A_CANT, 0);
	
	CLASS_ATTR_SYM              (c, "mode", 0, t_hoa_map, f_mode_sym);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Coordinates Types");
    CLASS_ATTR_ENUM             (c, "mode", 0, "polar cartesian");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, hoa_map_mode);
	CLASS_ATTR_SAVE				(c, "mode", 1);
    
    CLASS_ATTR_FLOAT            (c, "ramp", 0, t_hoa_map, f_ramp);
	CLASS_ATTR_CATEGORY			(c, "ramp", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp Time (ms)");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, hoa_map_ramp);
	CLASS_ATTR_SAVE				(c, "ramp", 1);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_map_class = c;
	return 0;
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
			order = Hoa2D::clip_min(atom_getlong(argv), 0);
        if(argc > 1 && atom_gettype(argv+1) == A_LONG)
            numberOfSources = Hoa2D::clip_minmax(atom_getlong(argv+1), 1, 254);

		x->f_map = new Hoa2D::Map(order, numberOfSources);
		if(x->f_map->getNumberOfSources() == 1)
            dsp_setup((t_pxobject *)x, 3);
        else
            dsp_setup((t_pxobject *)x, x->f_map->getNumberOfSources());
		
		for (int i = 0; i < x->f_map->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        if(x->f_map->getNumberOfSources() == 1)
            x->f_sig_ins    =  new double[3 * SYS_MAXBLKSIZE];
        else
            x->f_sig_ins    =  new double[x->f_map->getNumberOfSources() * SYS_MAXBLKSIZE];
		
        x->f_sig_outs   =  new double[x->f_map->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
		
		x->f_lines_x = new Line*[x->f_map->getNumberOfSources()];
		x->f_lines_y = new Line*[x->f_map->getNumberOfSources()];
		
		for (int i=0; i < x->f_map->getNumberOfSources(); i++)
		{
			x->f_lines_x[i] = new Line(100., sys_getmaxblksize(), sys_getsr());
			x->f_lines_y[i] = new Line(100., sys_getmaxblksize(), sys_getsr());
		}
		
		x->f_first_radius = x->f_first_azimuth = 0;
		
		t_atom av;
        atom_setlong(&av, 1);
        object_method(x, gensym("mode"), 1, &av);
        atom_setlong(&av, 100.);
        object_method(x, gensym("ramp"), 1, &av);
        
        if(atom_gettype(argv+1) == A_SYM)
            object_method(x, gensym("mode"), 1, argv+1);
        
        attr_args_process(x, argc, argv);
        
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
    
	return (x);
}

void hoa_map_float(t_hoa_map *x, double f)
{
	long inlet = proxy_getinlet((t_object *)x);
    if(x->f_map->getNumberOfSources() == 1)
    {
		if(x->f_mode == HOA_MODE_POL)
		{
			if(inlet == 1)
			{
				x->f_lines_x[0]->setValue(Hoa2D::abscissa(f, x->f_first_azimuth));
				x->f_lines_y[0]->setValue(Hoa2D::ordinate(f, x->f_first_azimuth));
				x->f_first_radius = Hoa2D::clip_min(f, 0.);
			}
			else if(inlet == 2)
			{
				x->f_lines_x[0]->setValue(Hoa2D::abscissa(x->f_first_radius, f));
				x->f_lines_y[0]->setValue(Hoa2D::ordinate(x->f_first_radius, f));
				x->f_first_azimuth = Hoa2D::wrap_twopi(f);
			}
		}
		else if(x->f_mode == HOA_MODE_CAR)
		{
			if(inlet == 1)
			{
				x->f_lines_x[0]->setValue(f);
			}
			else if(inlet == 2)
			{
				x->f_lines_y[0]->setValue(f);
			}
		}
    }
    
}

void hoa_map_int(t_hoa_map *x, long n)
{
	hoa_map_float(x, (double) n);
}

void hoa_map_list(t_hoa_map *x, t_symbol* s, long argc, t_atom* argv)
{
	double azimuth, radius;
	int mode = 0;
	int index = atom_getlong(argv);
	
	if( (index < 0) || (index > x->f_map->getNumberOfSources() - 1) || atom_gettype(argv+1) != A_SYM)
		return;
	
	if(atom_getsym(argv+1) == hoa_sym_car || atom_getsym(argv+1) == hoa_sym_cartesian)
		mode = 1;
	
	if(argc > 3)
	{
		if (mode == HOA_MODE_POL)
		{
			radius = atom_getfloat(argv+2);
			azimuth = atom_getfloat(argv+3);
			x->f_lines_x[index]->setValue(Hoa2D::abscissa(radius, azimuth));
			x->f_lines_y[index]->setValue(Hoa2D::ordinate(radius, azimuth));
		}
		else if (mode == HOA_MODE_CAR)
		{
			x->f_lines_x[index]->setValue(atom_getfloat(argv+2));
			x->f_lines_y[index]->setValue(atom_getfloat(argv+3));
		}
	}
	
	if (atom_getsym(argv+1) == hoa_sym_mute)
	{
		if (argc > 2)
		{
			x->f_map->setMute(index, atom_getlong(argv+2));
		}
	}
}

t_max_err hoa_map_mode(t_hoa_map *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_SYM)
        x->f_mode = (atom_getsym(argv) == hoa_sym_cartesian || atom_getsym(argv) == hoa_sym_car) ? HOA_MODE_CAR : HOA_MODE_POL;
	
    else if(atom_gettype(argv) == A_LONG)
        x->f_mode = (atom_getlong(argv) != 0) ? HOA_MODE_POL : HOA_MODE_CAR;
	
	x->f_mode_sym = x->f_mode ? hoa_sym_cartesian : hoa_sym_polar;
	
    return MAX_ERR_NONE;
}

t_max_err hoa_map_ramp(t_hoa_map *x, t_object *attr, long argc, t_atom *argv)
{
	double ramp;
	if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
	{
		ramp = atom_getfloat(argv);
		for (int i = 0; i < x->f_map->getNumberOfSources(); i++)
		{
			x->f_lines_x[i]->setRampInMs(ramp);
			x->f_lines_y[i]->setRampInMs(ramp);
		}
	}
	
	x->f_ramp = x->f_lines_x[0]->getRampInMs();
	
    return MAX_ERR_NONE;
}

void hoa_map_dsp64(t_hoa_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	long in1, in2;
	in1 = count[1];
	in2 = count[2];
	
	for (int i = 0; i < x->f_map->getNumberOfSources(); i++)
	{
		x->f_lines_x[i]->setVectorSize(maxvectorsize);
		x->f_lines_y[i]->setVectorSize(maxvectorsize);
		x->f_lines_x[i]->setSamplingRate(samplerate);
		x->f_lines_y[i]->setSamplingRate(samplerate);
	}
	
    if(x->f_map->getNumberOfSources() == 1)
    {
		if(in1 && in2)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_in1_in2, 0, NULL);
        else if(in1 && !in2)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_in1, 0, NULL);
        else if(!in1 && in2)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_in2, 0, NULL);
		else if(!in1 && !in2)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64, 0, NULL);
    }
    else
    {
        object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_multisources, 0, NULL);
    }
}

void hoa_map_perform64_multisources(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double abscissa, ordinate;
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
		for (int j = 0; j < x->f_map->getNumberOfSources(); j++)
		{
			abscissa = x->f_lines_x[j]->process();
			ordinate = x->f_lines_y[j]->process();
			x->f_map->setRadius(j, Hoa2D::radius(abscissa, ordinate));
			x->f_map->setAzimuth(j, Hoa2D::azimuth(abscissa, ordinate));
		}
        x->f_map->process(x->f_sig_ins + numins * i, x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double abscissa, ordinate;
	for(int i = 0; i < sampleframes; i++)
    {
		abscissa = x->f_lines_x[0]->process();
		ordinate = x->f_lines_y[0]->process();
		x->f_map->setRadius(0, Hoa2D::radius(abscissa, ordinate));
		x->f_map->setAzimuth(0, Hoa2D::azimuth(abscissa, ordinate));
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_in1(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double abscissa, ordinate;
    for(int i = 0; i < sampleframes; i++)
    {
		abscissa = x->f_lines_x[0]->process();
		ordinate = x->f_lines_y[0]->process();
		
		if (x->f_mode == HOA_MODE_POL)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, Hoa2D::azimuth(abscissa, ordinate));
		}
		else if (x->f_mode == HOA_MODE_CAR)
		{
			x->f_map->setAzimuth(0, Hoa2D::azimuth(ins[1][i], ordinate));
			x->f_map->setRadius(0, Hoa2D::radius(ins[1][i], ordinate));
		}
		
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_in2(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double abscissa, ordinate;
	for(int i = 0; i < sampleframes; i++)
    {
		abscissa = x->f_lines_x[0]->process();
		ordinate = x->f_lines_y[0]->process();
		
		if (x->f_mode == HOA_MODE_POL)
		{
			x->f_map->setAzimuth(0, ins[2][i]);
			x->f_map->setRadius(0, Hoa2D::radius(abscissa, ordinate));
		}
		else if (x->f_mode == HOA_MODE_CAR)
		{
			x->f_map->setAzimuth(0, Hoa2D::azimuth(abscissa, ins[2][i]));
			x->f_map->setRadius(0, Hoa2D::radius(abscissa, ins[2][i]));
		}
		
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_map_perform64_in1_in2(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
		if (x->f_mode == HOA_MODE_POL)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, ins[2][i]);
		}
		else if (x->f_mode == HOA_MODE_CAR)
		{
			x->f_map->setAzimuth(0, Hoa2D::azimuth(ins[1][i], ins[2][i]));
			x->f_map->setRadius(0, Hoa2D::radius(ins[1][i], ins[2][i]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	
	if(x->f_map->getNumberOfSources() == 1)
		boxinfos->autoconnect_inputs = 1;
	else
		boxinfos->autoconnect_inputs = x->f_map->getNumberOfSources();
	
	boxinfos->autoconnect_outputs = x->f_map->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_map_assist(t_hoa_map *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
	{
        if(x->f_map->getNumberOfSources() == 1)
        {
            if(a == 0)
                sprintf(s,"(signal) Source 0");
            else if(a == 1)
                sprintf(s,"(signal/float) Radius or Abscissa");
			else if(a == 2)
                sprintf(s,"(signal/float) Azimuth or Ordinate");
        }
        else
        {
            if(a == 0)
                sprintf(s,"(signal/messages) Input 0 and sources messages");
            else
                sprintf(s,"(signal/float) Input %ld", a);
        }
        
	}
	else 
	{
		sprintf(s,"(signal) %s", x->f_map->getHarmonicsName(a).c_str());
	}
}


void hoa_map_free(t_hoa_map *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_map;
    delete [] x->f_sig_ins;
    delete [] x->f_sig_outs;
	
	for (int i=0; i < x->f_map->getNumberOfSources(); i++)
	{
		delete x->f_lines_x[i];
		delete x->f_lines_y[i];
	}
	delete [] x->f_lines_x;
	delete [] x->f_lines_y;
}

