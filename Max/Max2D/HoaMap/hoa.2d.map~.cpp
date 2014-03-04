/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// TODO : LINE DE AZIMUT ELEVATION ET DISTANCE

#include "../Hoa2D.max.h"
#include "../../../Sources/CicmLibrary/CicmLine/CicmLine.h"

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
	bool			*f_muteTable;
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
void hoa_map_perform64_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_map_perform64_azimuth_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err hoa_map_mode(t_hoa_map *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_map_ramp(t_hoa_map *x, t_object *attr, long argc, t_atom *argv);

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_map_class;

t_symbol *hoa_sym_pol;
t_symbol *hoa_sym_polar;
t_symbol *hoa_sym_car;
t_symbol *hoa_sym_cartesian;
t_symbol *hoa_sym_mute;
    

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
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp Time");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, hoa_map_ramp);
	CLASS_ATTR_SAVE				(c, "ramp", 1);
	
	hoa_sym_pol			= gensym("pol");
	hoa_sym_polar		= gensym("polar");
	hoa_sym_car			= gensym("car");
	hoa_sym_cartesian	= gensym("cartesian");
	hoa_sym_mute		= gensym("mute");
	
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
		
		x->f_muteTable = new bool[x->f_map->getNumberOfSources()];
		
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
				x->f_map->setAzimuth(0, f);
			else if(inlet == 2)
				x->f_map->setRadius(0, f);
		}
		else if(x->f_mode == HOA_MODE_CAR)
		{
			/*
			if(inlet == 1)
				x->f_map->setAzimuth(0, Hoa2D::azimuth(f, <#double y#>) f);
			else if(inlet == 2)
				x->f_map->setRadius(0, f);
			*/
		}
    }
    
}

void hoa_map_int(t_hoa_map *x, long n)
{
	hoa_map_float(x, (double) n);
}

void hoa_map_list(t_hoa_map *x, t_symbol* s, long argc, t_atom* argv)
{
	double abscissa, ordinate;
	int mode = 0;
	int index = atom_getlong(argv);
	
	if( (index < 0) || (index > x->f_map->getNumberOfSources() - 1)  || atom_gettype(argv+1) != A_SYM)
		return;
	
	if(atom_getsym(argv+1) == hoa_sym_car || atom_getsym(argv+1) == hoa_sym_cartesian)
		mode = 1;
	
	if(argc > 3)
	{
		if (mode == 0)
		{
			x->f_map->setAzimuth(index, atom_getfloat(argv+2));
			x->f_map->setRadius(index, atom_getfloat(argv+3));
		}
		else if (mode == 1)
		{
			abscissa = atom_getfloat(argv+2);
			ordinate = atom_getfloat(argv+3);
			x->f_map->setAzimuth(index, Hoa2D::azimuth(abscissa, ordinate));
			x->f_map->setRadius(index, Hoa2D::radius(abscissa, ordinate));
		}
	}
	
	if (atom_getsym(argv+1) == hoa_sym_mute)
	{
		if (argc > 2)
		{
			x->f_muteTable[index] = atom_getlong(argv+2) != 0;
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
	
    return NULL;
}

t_max_err hoa_map_ramp(t_hoa_map *x, t_object *attr, long argc, t_atom *argv)
{
	/*
    if(atom_gettype(argv) == A_LONG)
        x->f_map->setRamp(atom_getlong(argv) * sys_getsr() / 1000.);
    else if(atom_gettype(argv) == A_FLOAT)
        x->f_map->setRamp(atom_getfloat(argv) * sys_getsr() / 1000.);
    
    x->f_ramp = x->f_maps->getRamp() / sys_getsr() * 1000.;
	*/
    return NULL;
}

void hoa_map_dsp64(t_hoa_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	long azimuth, distance;
	azimuth = count[1];
	distance = count[2];
    if(x->f_map->getNumberOfSources() == 1)
    {
		if(azimuth && distance)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth_distance, 0, NULL);
        else if(azimuth && !distance)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_azimuth, 0, NULL);
        else if(!azimuth && distance)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64_distance, 0, NULL);
		else if(!azimuth && !distance)
            object_method(dsp64, gensym("dsp_add64"), x, hoa_map_perform64, 0, NULL);
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

void hoa_map_perform64_distance(t_hoa_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_map->setRadius(0, ins[2][i]);
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
        x->f_map->setRadius(0, ins[2][i]);
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
                sprintf(s,"(Signal) Input");
            else if(a == 1)
                sprintf(s,"(Signal or float) Azimuth");
			else if(a == 2)
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

