/*
 // Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.map~.cpp
 @name      hoa.3d.map~
 @realname  hoa.3d.map~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A 3d ambisonic multisource spatializer
 
 @description
 <o>hoa.3d.map~</o> is a tool that encodes several sources in the spherical harmonics domain, it's easy to use and work with the GUI <o>hoa.3d.map</o>. With a single source's configuration you can manage coordinates at signal rate
 
 @discussion
 <o>hoa.3d.map~</o> is a tool that encodes several sources in the spherical harmonics domain, it's easy to use and work with the GUI <o>hoa.3d.map</o>. With a single source's configuration you can manage coordinates at signal rate
 
 @category ambisonics, hoa objects, audio, MSP
 
 @seealso hoa.2d.map~, hoa.3d.map, hoa.3d.encoder~, hoa.3d.decoder~, hoa.3d.optim~, hoa.3d.scope~, hoa.3d.wider~
 */

#include "Hoa3D.max.h"

class MapPolarLines3D
{
    
private:
    float*      m_values_old;
    float*      m_values_new;
    float*      m_values_step;
    unsigned int m_counter;
    unsigned int m_ramp;
    unsigned int m_number_of_sources;
    
public:
    MapPolarLines3D(unsigned int numberOfSources);
    ~MapPolarLines3D();
    
    inline unsigned int getNumberOfSources() const
    {
        return m_number_of_sources;
    }
    
    inline unsigned int getRamp() const
    {
        return m_ramp;
    }
    
    inline double getRadius(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[index];
    }
    
    inline double getAzimuth(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[m_number_of_sources +index];
    }
    
    inline double getElevation(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[m_number_of_sources * 2 +index];
    }
    
    void setRamp(unsigned int ramp);
    void setRadius(unsigned int index, double radius);
    void setAzimuth(unsigned int index, double azimuth);
    void setElevation(unsigned int index, double elevation);
    void setRadiusDirect(unsigned int index, double radius);
    void setAzimuthDirect(unsigned int index, double azimuth);
    void setElevationDirect(unsigned int index, double elevation);
    
    void process(float* vector);
};

typedef struct _hoa_3d_map 
{
	t_pxobject      f_ob;
    Hoa3D::Map*     f_map;
	
	MapPolarLines3D*  f_lines;
    float*			f_lines_vector;
	double			f_ramp;
	int             f_mode;
	
	double*         f_sig_ins;
    double*         f_sig_outs;
} t_hoa_3d_map;


void *hoa_3d_map_new(t_symbol *s, long argc, t_atom *argv);
void hoa_3d_map_free(t_hoa_3d_map *x);
void hoa_3d_map_assist(t_hoa_3d_map *x, void *b, long m, long a, char *s);

void hoa_3d_map_float(t_hoa_3d_map *x, double f);
void hoa_3d_map_int(t_hoa_3d_map *x, long n);
void hoa_3d_map_list(t_hoa_3d_map *x, t_symbol* s, long argc, t_atom* argv);

void hoa_3d_map_dsp64(t_hoa_3d_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);

void hoa_3d_map_perform_in1_in2_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in1_in2(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in1_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in2_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in1(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in2(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_map_perform(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_3d_map_perform_multisources(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err ramp_set(t_hoa_3d_map *x, t_object *attr, long argc, t_atom *argv);

t_hoa_err hoa_getinfos(t_hoa_3d_map* x, t_hoa_boxinfos* boxinfos);
t_class *hoa_3d_map_class;

#ifdef HOA_PACKED_LIB
int hoa_3d_map_main(void)
#else
int C74_EXPORT main(void)
#endif
{	

	t_class *c;
	
	c = class_new("hoa.3d.map~", (method)hoa_3d_map_new, (method)hoa_3d_map_free, (long)sizeof(t_hoa_3d_map), 0L, A_GIMME, 0);
	class_setname((char *)"hoa.3d.map~", (char *)"hoa.3d.map~");
    
	hoa_initclass(c, (method)hoa_getinfos);
	
	// @method float @digest Set single source coordinate with messages depending on the mode.
	// @description Set single source coordinate with messages depending on the mode.
	// @marg 0 @name coord @optional 0 @type float
	class_addmethod(c, (method)hoa_3d_map_float,		"float",	A_FLOAT, 0);
	
	// @method int @digest Set single source coordinate with messages depending on the mode.
	// @description Set single source coordinate with messages depending on the mode.
	// @marg 0 @name coord @optional 0 @type int
	class_addmethod(c, (method)hoa_3d_map_int,         "int",		A_LONG, 0);
	
	// @method list @digest Send source messages (coordinates and mute state).
	// @description Send source messages like coordinates and mute state. The list must be formatted like this : source-index input-mode radius azimuth elevation to set source positions or like this : source-index 'mute' mute-state to set the mute state of a source.
	// marg 0 @name source-index @optional 0 @type int
	// marg 1 @name input-mode/mute @optional 0 @type symbol
	// marg 2 @name coord-1/mute-state @optional 0 @type float/int
	// marg 3 @name coord-2 @optional 0 @type float
	// marg 4 @name coord-3 @optional 0 @type float
    class_addmethod(c, (method)hoa_3d_map_list,        "list",		A_GIMME, 0);
	
	// @method signal @digest Sources signals to encode.
	// @description If you have a single source, the first signal inlet is for the source to encode, the three other ones are to control source position at signal rate. If you have more than one source to spatialize, all of the inputs represent a signal to encode and coordonates are given with messages.
	class_addmethod(c, (method)hoa_3d_map_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_3d_map_assist,      "assist",	A_CANT, 0);
	
	CLASS_ATTR_DOUBLE           (c, "ramp", 0, t_hoa_3d_map, f_ramp);
	CLASS_ATTR_CATEGORY			(c, "ramp", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp Time (ms)");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, ramp_set);
	// @description The ramp time in milliseconds.
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_3d_map_class = c;
	return 0;
}

void *hoa_3d_map_new(t_symbol *s, long argc, t_atom *argv)
{
	// @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
	
	// @arg 1 @name number-of-sources @optional 0 @type int @digest The number of sources
	// @description Second argument is the number of sources to spatialize.
	// If there is a single source, <o>hoa.2d.map~</o> object owns 4 inlets, the first one correspond to the signal to encode, the three other ones can be used to control source position at control or signal rate. If you have more than one source to spatialize, the number of signal inlets will be equal to the number of sources to encode, and coordinates will be given with list messages.
	
	t_hoa_3d_map *x = NULL;
	int	order = 1;
    int numberOfSources = 1;
	
    x = (t_hoa_3d_map *)object_alloc(hoa_3d_map_class);
	if (x)
	{
		if(argc && atom_gettype(argv) == A_LONG)
			order = clip_min(atom_getlong(argv), 0);
		if(argc > 1 && atom_gettype(argv+1) == A_LONG)
			numberOfSources = clip_minmax(atom_getlong(argv+1), 1, 255);
		if(argc > 2 && atom_gettype(argv+2) == A_SYM)
		{
			if(atom_getsym(argv+2) == gensym("car") || atom_getsym(argv+2) == gensym("cartesian"))
				x->f_mode = 1;
			else
				x->f_mode = 0;
		}
		else
			x->f_mode = 0;
		
		x->f_ramp       = 100;
		x->f_map        = new Hoa3D::Map(order, numberOfSources);
		x->f_lines      = new MapPolarLines3D(x->f_map->getNumberOfSources());
		x->f_lines->setRamp(0.1 * sys_getsr());
		for (int i = 0; i < x->f_map->getNumberOfSources(); i++)
		{
			x->f_lines->setRadiusDirect(i, 1);
			x->f_lines->setAzimuthDirect(i, 0.);
		}
		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
        if(argc > 1 && atom_gettype(argv+1) == A_LONG)
            numberOfSources = atom_getlong(argv+1);

		x->f_map = new Hoa3D::Map(order, numberOfSources);
		if(x->f_map->getNumberOfSources() == 1)
            dsp_setup((t_pxobject *)x, 4);
        else
            dsp_setup((t_pxobject *)x, x->f_map->getNumberOfSources());
		
		for (int i = 0; i < x->f_map->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        if(x->f_map->getNumberOfSources() == 1)
            x->f_sig_ins    =  new double[4 * SYS_MAXBLKSIZE];
        else
            x->f_sig_ins    =  new double[x->f_map->getNumberOfSources() * SYS_MAXBLKSIZE];
        x->f_sig_outs		=  new double[x->f_map->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
		x->f_lines_vector   = new float[x->f_map->getNumberOfSources() * 3];
		
		attr_args_process(x, argc, argv);
	}
    
	return (x);
}

void hoa_3d_map_float(t_hoa_3d_map *x, double f)
{
	if(x->f_map->getNumberOfSources() == 1)
    {
		if(x->f_mode == 0)
		{
			if(proxy_getinlet((t_object *)x) == 1)
			{
				x->f_lines->setRadius(0, clip_min(f, 0.));
			}
			else if(proxy_getinlet((t_object *)x) == 2)
			{
				x->f_lines->setAzimuth(0, f);
			}
            else if(proxy_getinlet((t_object *)x) == 3)
			{
				x->f_lines->setElevation(0, f);
			}
		}
		else if(x->f_mode == 1)
		{
			if(proxy_getinlet((t_object *)x) == 1)
			{
                double abs = f;
                double ord = ordinate(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
                double hei = height(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
				x->f_lines->setRadius(0, radius(abs, ord, hei));
                x->f_lines->setAzimuth(0, azimuth(abs, ord, hei));
                x->f_lines->setElevation(0, elevation(abs, ord, hei));
			}
			else if(proxy_getinlet((t_object *)x) == 2)
			{
				double abs = abscissa(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
                double ord = f;
                double hei = height(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
				x->f_lines->setRadius(0, radius(abs, ord, hei));
                x->f_lines->setAzimuth(0, azimuth(abs, ord, hei));
                x->f_lines->setElevation(0, elevation(abs, ord, hei));
			}
            else if(proxy_getinlet((t_object *)x) == 3)
			{
				double abs = abscissa(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
                double ord = ordinate(x->f_lines->getRadius(0), x->f_lines->getAzimuth(0), x->f_lines->getElevation(0));
                double hei = f;
                x->f_lines->setRadius(0, radius(abs, ord, hei));
                x->f_lines->setAzimuth(0, azimuth(abs, ord, hei));
                x->f_lines->setElevation(0, elevation(abs, ord, hei));
			}
		}
    }
}

void hoa_3d_map_int(t_hoa_3d_map *x, long n)
{
	hoa_3d_map_float(x, n);
	/*
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
            x->f_map->setRadius(0, n);
        }
    }
	*/
}

t_max_err ramp_set(t_hoa_3d_map *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        {
            x->f_ramp = clip_min(atom_getfloat(argv), 0);
            x->f_lines->setRamp(x->f_ramp / 1000. * sys_getsr());
        }
    }
    
    return MAX_ERR_NONE;
}

void hoa_3d_map_list(t_hoa_3d_map *x, t_symbol* s, long argc, t_atom* argv)
{
	if(argc > 2 && argv && atom_gettype(argv) == A_LONG && atom_gettype(argv+1) == A_SYM)
    {
        int index = atom_getlong(argv);
        if(index < 1 || index > x->f_map->getNumberOfSources())
            return;
        
        if(argc > 4 && (atom_getsym(argv+1) == hoa_sym_polar || atom_getsym(argv+1) == hoa_sym_pol))
        {
            x->f_lines->setRadius(index-1, atom_getfloat(argv+2));
            x->f_lines->setAzimuth(index-1, atom_getfloat(argv+3));
            x->f_lines->setElevation(index-1, atom_getfloat(argv+4));
        }
        else if(argc > 4 && (atom_getsym(argv+1) == hoa_sym_cartesian || atom_getsym(argv+1) == hoa_sym_car))
        {
            x->f_lines->setRadius(index-1, radius(atom_getfloat(argv+2), atom_getfloat(argv+3), atom_getfloat(argv+4)));
            x->f_lines->setAzimuth(index-1, azimuth(atom_getfloat(argv+2), atom_getfloat(argv+3), atom_getfloat(argv+4)));
            x->f_lines->setElevation(index-1, elevation(atom_getfloat(argv+2), atom_getfloat(argv+3), atom_getfloat(argv+4)));
        }
        else if(argc > 2 && atom_getsym(argv+1) == hoa_sym_mute)
        {
            x->f_map->setMute(index-1, atom_getlong(argv+2));
        }
    }
}

void hoa_3d_map_dsp64(t_hoa_3d_map *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	
	x->f_lines->setRamp(x->f_ramp / 1000. * samplerate);
    
    if(x->f_map->getNumberOfSources() == 1)
    {
		if(count[1] && count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in1_in2_in3, 0, NULL);
        else if(count[1] && count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in1_in2, 0, NULL);
        else if(count[1] && !count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in1_in3, 0, NULL);
        else if(!count[1] && count[2] && count[3])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in1_in3, 0, NULL);
        else if(count[1] && !count[2])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in1, 0, NULL);
        else if(!count[1] && count[2])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in2, 0, NULL);
        else if(!count[1] && count[2])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_in3, 0, NULL);
		else if(!count[1] && !count[2] && !count[3])
            object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform, 0, NULL);
    }
    else
    {
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_3d_map_perform_multisources, 0, NULL);
    }
}

void hoa_3d_map_perform64_multisources(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int nsources = x->f_map->getNumberOfSources();
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
		for(int j = 0; j < nsources; j++)
			x->f_map->setRadius(j, x->f_lines_vector[j]);
        for(int j = 0; j < nsources; j++)
			x->f_map->setAzimuth(j, x->f_lines_vector[j + nsources]);
        for(int j = 0; j < nsources; j++)
			x->f_map->setElevation(j, x->f_lines_vector[j + nsources * 2]);
        
        x->f_map->process(x->f_sig_ins + numins * i, x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in1_in2_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, ins[2][i]);
            x->f_map->setElevation(0, ins[3][i]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(ins[1][i], ins[2][i], ins[3][i]));
			x->f_map->setRadius(0, radius(ins[1][i], ins[2][i], ins[3][i]));
            x->f_map->setElevation(0,elevation(ins[1][i], ins[2][i], ins[3][i]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in1_in2(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, ins[2][i]);
            x->f_map->setElevation(0, x->f_lines_vector[2]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(ins[1][i], ins[2][i], x->f_lines_vector[2]));
			x->f_map->setRadius(0, radius(ins[1][i], ins[2][i], x->f_lines_vector[2]));
            x->f_map->setElevation(0, elevation(ins[1][i], ins[2][i], x->f_lines_vector[2]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in1_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, x->f_lines_vector[1]);
            x->f_map->setElevation(0, ins[3][i]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(ins[1][i], x->f_lines_vector[1], ins[3][i]));
			x->f_map->setRadius(0, radius(ins[1][i], x->f_lines_vector[1], ins[3][i]));
            x->f_map->setElevation(0, elevation(ins[1][i], x->f_lines_vector[1], ins[3][i]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in2_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, x->f_lines_vector[0]);
			x->f_map->setAzimuth(0, ins[2][i]);
            x->f_map->setElevation(0, ins[3][i]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(x->f_lines_vector[0], ins[2][i], ins[3][i]));
			x->f_map->setRadius(0, radius(x->f_lines_vector[0], ins[2][i], ins[3][i]));
            x->f_map->setElevation(0, elevation(x->f_lines_vector[0], ins[2][i], ins[3][i]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in1(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
		x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, ins[1][i]);
			x->f_map->setAzimuth(0, x->f_lines_vector[1]);
            x->f_map->setElevation(0, x->f_lines_vector[2]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(ins[1][i], x->f_lines_vector[1], x->f_lines_vector[2]));
			x->f_map->setRadius(0, radius(ins[1][i], x->f_lines_vector[1], x->f_lines_vector[2]));
            x->f_map->setElevation(0, elevation(ins[1][i], x->f_lines_vector[1], x->f_lines_vector[2]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in2(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
		x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, x->f_lines_vector[0]);
			x->f_map->setAzimuth(0, ins[2][i]);
            x->f_map->setElevation(0, x->f_lines_vector[2]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(x->f_lines_vector[0], ins[2][i], x->f_lines_vector[2]));
			x->f_map->setRadius(0, radius(x->f_lines_vector[0], ins[2][i], x->f_lines_vector[2]));
            x->f_map->setElevation(0, elevation(x->f_lines_vector[0], ins[2][i], x->f_lines_vector[2]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_in3(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
		x->f_lines->process(x->f_lines_vector);
        if(x->f_mode == 0)
		{
			x->f_map->setRadius(0, x->f_lines_vector[0]);
			x->f_map->setAzimuth(0, x->f_lines_vector[1]);
            x->f_map->setElevation(0, ins[3][i]);
		}
		else if(x->f_mode == 1)
		{
			x->f_map->setAzimuth(0, azimuth(x->f_lines_vector[0], x->f_lines_vector[1], ins[3][i]));
			x->f_map->setRadius(0, radius(x->f_lines_vector[0], x->f_lines_vector[1], ins[3][i]));
            x->f_map->setElevation(0, elevation(x->f_lines_vector[0], x->f_lines_vector[1], ins[3][i]));
		}
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
		x->f_lines->process(x->f_lines_vector);
		x->f_map->setRadius(0, x->f_lines_vector[0]);
		x->f_map->setAzimuth(0, x->f_lines_vector[1]);
        x->f_map->setElevation(0, x->f_lines_vector[2]);
        x->f_map->process(&ins[0][i], x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}

void hoa_3d_map_perform_multisources(t_hoa_3d_map *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int nsources = x->f_map->getNumberOfSources();
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_sig_ins+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
		for(int j = 0; j < nsources; j++)
			x->f_map->setRadius(j, x->f_lines_vector[j]);
        for(int j = 0; j < nsources; j++)
			x->f_map->setAzimuth(j, x->f_lines_vector[j + nsources]);
        for(int j = 0; j < nsources; j++)
			x->f_map->setElevation(j, x->f_lines_vector[j + nsources * 2]);
        
        x->f_map->process(x->f_sig_ins + numins * i, x->f_sig_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_sig_outs+i, numouts, outs[i], 1);
    }
}



t_hoa_err hoa_getinfos(t_hoa_3d_map* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_map->getNumberOfSources();
	boxinfos->autoconnect_outputs = x->f_map->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_3d_map_assist(t_hoa_3d_map *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
	{
        if(x->f_map->getNumberOfSources() == 1)
        {
            if(a == 0)
                sprintf(s,"(signal) Input");
            else if(a == 1)
                sprintf(s,"(signal/float) Radius");
            else if(a == 2)
                sprintf(s,"(signal/float) Azimuth");
            else
                sprintf(s,"(signal/float) Elevation");
        }
        else
        {
            if(a == 0)
                sprintf(s,"(signal and messages) Input 0 and sources coordinates");
            else
                sprintf(s,"(signal/float) Input %ld", a);
        }
        
	}
	else 
	{
		sprintf(s,"(signal) %s", x->f_map->getHarmonicName(a).c_str());
	}
}


void hoa_3d_map_free(t_hoa_3d_map *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_lines;
	delete x->f_map;
    delete [] x->f_sig_ins;
    delete [] x->f_sig_outs;
	delete [] x->f_lines_vector;
}

// -----------------------------------------------------------------------------------------------------
// MapPolarLines3D
// -----------------------------------------------------------------------------------------------------

MapPolarLines3D::MapPolarLines3D(unsigned int numberOfSources)
{
    assert(numberOfSources > 0);
    m_number_of_sources = numberOfSources;
    
    m_values_old    = new float[m_number_of_sources * 3];
    m_values_new    = new float[m_number_of_sources * 3];
    m_values_step   = new float[m_number_of_sources * 3];
}

MapPolarLines3D::~MapPolarLines3D()
{
    delete [] m_values_old;
    delete [] m_values_new;
    delete [] m_values_step;
}

void MapPolarLines3D::setRamp(unsigned int ramp)
{
    m_ramp = clip_min(ramp, (long)1);
}

void MapPolarLines3D::setRadius(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_new[index]  = radius;
    m_values_step[index] = (m_values_new[index] - m_values_old[index]) / (double)m_ramp;
    m_counter = 0;
}

void MapPolarLines3D::setAzimuth(unsigned int index, double azimuth)
{
    assert(index < m_number_of_sources);
    m_values_new[index + m_number_of_sources] = wrap_twopi(azimuth);
    m_values_old[index + m_number_of_sources] = wrap_twopi(m_values_old[index + m_number_of_sources]);
    
    double distance;
    if(m_values_old[index + m_number_of_sources] > m_values_new[index + m_number_of_sources])
        distance = (m_values_old[index + m_number_of_sources] - m_values_new[index + m_number_of_sources]);
    else
        distance = (m_values_new[index + m_number_of_sources] - m_values_old[index + m_number_of_sources]);
    
    if(distance <= HOA_PI)
    {
        m_values_step[index + m_number_of_sources] = (m_values_new[index + m_number_of_sources] - m_values_old[index + m_number_of_sources]) / (double)m_ramp;
    }
    else
    {
        if(m_values_new[index + m_number_of_sources] > m_values_old[index + m_number_of_sources])
        {
            m_values_step[index + m_number_of_sources] = ((m_values_new[index + m_number_of_sources] - HOA_2PI) - m_values_old[index + m_number_of_sources]) / (double)m_ramp;
        }
        else
        {
            m_values_step[index + m_number_of_sources] = ((m_values_new[index + m_number_of_sources] + HOA_2PI) - m_values_old[index + m_number_of_sources]) / (double)m_ramp;
        }
    }
    m_counter = 0;
}

void MapPolarLines3D::setElevation(unsigned int index, double elevation)
{
    assert(index < m_number_of_sources);
    m_values_new[index + m_number_of_sources * 2] = wrap_twopi(elevation);
    m_values_old[index + m_number_of_sources * 2] = wrap_twopi(m_values_old[index + m_number_of_sources * 2]);
    
    double distance;
    if(m_values_old[index + m_number_of_sources * 2] > m_values_new[index + m_number_of_sources * 2])
        distance = (m_values_old[index + m_number_of_sources * 2] - m_values_new[index + m_number_of_sources * 2]);
    else
        distance = (m_values_new[index + m_number_of_sources * 2] - m_values_old[index + m_number_of_sources * 2]);
    
    if(distance <= HOA_PI)
    {
        m_values_step[index + m_number_of_sources * 2] = (m_values_new[index + m_number_of_sources * 2] - m_values_old[index + m_number_of_sources * 2]) / (double)m_ramp;
    }
    else
    {
        if(m_values_new[index + m_number_of_sources * 2] > m_values_old[index + m_number_of_sources * 2])
        {
            m_values_step[index + m_number_of_sources * 2] = ((m_values_new[index + m_number_of_sources * 2] - HOA_2PI) - m_values_old[index + m_number_of_sources * 2]) / (double)m_ramp;
        }
        else
        {
            m_values_step[index + m_number_of_sources * 2] = ((m_values_new[index + m_number_of_sources * 2] + HOA_2PI) - m_values_old[index + m_number_of_sources * 2]) / (double)m_ramp;
        }
    }
    m_counter = 0;
}

void MapPolarLines3D::setRadiusDirect(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_old[index] = m_values_new[index] = radius;
    m_values_step[index] = 0.;
    m_counter = 0;
}

void MapPolarLines3D::setAzimuthDirect(unsigned int index, double azimuth)
{
    assert(index < m_number_of_sources);
    m_values_old[index + m_number_of_sources] = m_values_new[index + m_number_of_sources] = azimuth;
    m_values_step[index + m_number_of_sources] = 0.;
    m_counter = 0;
}


void MapPolarLines3D::setElevationDirect(unsigned int index, double elevation)
{
    assert(index < m_number_of_sources);
    m_values_old[index + m_number_of_sources * 2] = m_values_new[index + m_number_of_sources * 2] = elevation;
    m_values_step[index + m_number_of_sources * 2] = 0.;
    m_counter = 0;
}

void MapPolarLines3D::process(float* vector)
{
    cblas_saxpy(m_number_of_sources * 3, 1., m_values_step, 1, m_values_old, 1);
    if(m_counter++ >= m_ramp)
    {
        cblas_scopy(m_number_of_sources * 3, m_values_new, 1, m_values_old, 1);
        memset(m_values_step, 0, sizeof(float) * m_number_of_sources * 3);
        m_counter    = 0;
    }
    cblas_scopy(m_number_of_sources * 3, m_values_old, 1, vector, 1);
}
