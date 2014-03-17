/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

class PolarLines
{
    
private:
    float*      m_values_old;
    float*      m_values_new;
    float*      m_values_step;
    unsigned int m_counter;
    unsigned int m_ramp;
    unsigned int m_number_of_sources;
    
public:
    PolarLines(unsigned int numberOfSources);
    ~PolarLines();
    
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
    
    void setRamp(unsigned int ramp);
    void setRadius(unsigned int index, double radius);
    void setAzimuth(unsigned int index, double azimuth);
    void setRadiusDirect(unsigned int index, double radius);
    void setAzimuthDirect(unsigned int index, double azimuth);
    
    void process(float* vector);
    float processOne();
};

typedef struct _hoa_recomposer
{
    t_edspobj               f_ob;
    t_symbol*               f_mode;
    double                  f_ramp;
    
	t_float*                f_ins;
    t_float*                f_outs;
    float*                  f_lines_vector;
    Hoa2D::Recomposer*      f_recomposer;
    PolarLines*             f_lines;
} t_hoa_recomposer;

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv);
void hoa_recomposer_free(t_hoa_recomposer *x);

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);
void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);
t_pd_err mode_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv);
t_pd_err ramp_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv);

void hoa_recomposer_dsp(t_hoa_recomposer *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);

void hoa_recomposer_perform_fixe(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_recomposer_perform_fisheye(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_recomposer_perform_free(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_recomposer* x, t_hoa_boxinfos* boxinfos);

t_eclass *hoa_recomposer_class;

t_symbol* hoa_sym_fixe       = gensym("fixe");
t_symbol* hoa_sym_fisheye    = gensym("fisheye");

extern "C" void setup_hoa0x2e2d0x2erecomposer_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.2d.recomposer~", (method)hoa_recomposer_new, (method)hoa_recomposer_free, (short)sizeof(t_hoa_recomposer), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method)hoa_recomposer_dsp,     "dsp",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_recomposer_angle,   "angle",    A_GIMME,0);
    eclass_addmethod(c, (method)hoa_recomposer_wide,    "wide",     A_GIMME,0);
    
    CLASS_ATTR_SYMBOL           (c, "mode", 0, t_hoa_recomposer, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_DEFAULT          (c, "mode", 0, "fixe");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    
    CLASS_ATTR_DOUBLE			(c,"ramp", 0, t_hoa_recomposer, f_ramp);
	CLASS_ATTR_LABEL			(c,"ramp", 0, "Ramp Time in milliseconds");
	CLASS_ATTR_CATEGORY			(c,"ramp", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"ramp", NULL, ramp_set);
    CLASS_ATTR_ORDER			(c,"ramp", 0,  "2");
    CLASS_ATTR_DEFAULT          (c,"ramp", 0, "100");
    CLASS_ATTR_SAVE             (c,"ramp", 1);
    
    eclass_register(CLASS_OBJ, c);
    hoa_recomposer_class = c;
    
    hoa_sym_fixe       = gensym("fixe");
    hoa_sym_fisheye    = gensym("fisheye");
}

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_recomposer *x = NULL;
    t_binbuf *d;
    int	order = 1;
    int numberOfLoudspeakers = 4;
    x = (t_hoa_recomposer *)eobj_new(hoa_recomposer_class);
    
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
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
		
        x->f_ramp       = 100;
        x->f_mode       = hoa_sym_fixe;
        
		x->f_recomposer = new Hoa2D::Recomposer(order, numberOfLoudspeakers);
        x->f_lines      = new PolarLines(x->f_recomposer->getNumberOfChannels());
        x->f_lines->setRamp(0.1 * sys_getsr());
		for (int i = 0; i < x->f_recomposer->getNumberOfChannels(); i++)
        {
            x->f_lines->setRadiusDirect(i, x->f_recomposer->getWideningValue(i));
            x->f_lines->setAzimuthDirect(i, x->f_recomposer->getAzimuth(i));
        }
        
        eobj_dspsetup(x, x->f_recomposer->getNumberOfChannels() + 1, x->f_recomposer->getNumberOfHarmonics());
        
		x->f_ins            = new t_float[x->f_recomposer->getNumberOfChannels() * SYS_MAXBLKSIZE];
        x->f_outs           = new t_float[x->f_recomposer->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_lines_vector   = new float[x->f_recomposer->getNumberOfChannels() * 2];
        
        ebox_attrprocess_viabinbuf(x, d);
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

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && x->f_mode == hoa_sym_free)
    {
        for(int i = 0; i < x->f_recomposer->getNumberOfChannels() && i < ac; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_lines->setAzimuth(i, atom_getfloat(av+i));
        }
    }
}

void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && x->f_mode == hoa_sym_free)
    {
        for(int i = 0; i < x->f_recomposer->getNumberOfChannels() && i < ac; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_lines->setRadius(i, atom_getfloat(av+i));
        }
    }
}

void hoa_recomposer_dsp(t_hoa_recomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_lines->setRamp(x->f_ramp / 1000. * samplerate);
    if(x->f_mode == hoa_sym_fixe)
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_recomposer_perform_fixe, 0, NULL);
    else if(x->f_mode == hoa_sym_fisheye)
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_recomposer_perform_fisheye, 0, NULL);
    else if(x->f_mode == hoa_sym_free)
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_recomposer_perform_free, 0, NULL);
}

void hoa_recomposer_perform_fixe(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int numberOfChannels = x->f_recomposer->getNumberOfChannels();
    for(int i = 0; i < numberOfChannels && i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numberOfChannels);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_recomposer->processFixe(x->f_ins + numberOfChannels * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_recomposer_perform_fisheye(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int numberOfChannels = x->f_recomposer->getNumberOfChannels();
    for(int i = 0; i < numberOfChannels && i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numberOfChannels);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_recomposer->setFisheye(ins[numberOfChannels][i]);
        x->f_recomposer->processFisheye(x->f_ins + numberOfChannels * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_recomposer_perform_free(t_hoa_recomposer *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int numberOfChannels = x->f_recomposer->getNumberOfChannels();
    
    for(int i = 0; i < numberOfChannels && i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numberOfChannels);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_lines->process(x->f_lines_vector);
        for(int j = 0; j < numberOfChannels && j < numins; j++)
            x->f_recomposer->setWideningValue(j, x->f_lines_vector[j]);
        for(int j = 0; j < numberOfChannels && j < numins; j++)
            x->f_recomposer->setAzimuth(j, x->f_lines_vector[j + numberOfChannels]);
        x->f_recomposer->processFree(x->f_ins + numberOfChannels * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}


void hoa_recomposer_free(t_hoa_recomposer *x)
{
	eobj_dspfree(x);
	delete x->f_recomposer;
    delete x->f_lines;
    delete [] x->f_lines_vector;
    delete [] x->f_ins;
	delete [] x->f_outs;
}

t_pd_err mode_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_fixe && x->f_mode != hoa_sym_fixe)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_fixe;
                canvas_resume_dsp(dspState);
            }
            else if(atom_getsym(argv) == hoa_sym_fisheye && x->f_mode != hoa_sym_fisheye)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_fisheye;
                x->f_lines->setRadiusDirect(0, 0.);
                canvas_resume_dsp(dspState);
            }
            else if(atom_getsym(argv) == hoa_sym_free && x->f_mode != hoa_sym_free)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_free;
                for(int i = 0; i < x->f_recomposer->getNumberOfChannels(); i++)
                {
                    x->f_lines->setRadiusDirect(i, 1);
                    x->f_lines->setAzimuthDirect(i, (double)i / (double)x->f_recomposer->getNumberOfChannels() * HOA_2PI);
                }
                canvas_resume_dsp(dspState);
            }
        }
        else if(atom_gettype(argv) == A_LONG)
        {
            if(atom_getlong(argv) == 0 && x->f_mode != hoa_sym_fixe)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_fixe;
                canvas_resume_dsp(dspState);
            }
            else if(atom_getlong(argv) == 1 && x->f_mode != hoa_sym_fisheye)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_fisheye;
                x->f_lines->setRadiusDirect(0, 0.);
                canvas_resume_dsp(dspState);
            }
            else if(atom_getlong(argv) == 1 && x->f_mode != hoa_sym_free)
            {
                int dspState = canvas_suspend_dsp();
                x->f_mode = hoa_sym_free;
                for(int i = 0; i < x->f_recomposer->getNumberOfChannels(); i++)
                {
                    x->f_lines->setRadiusDirect(i, 1);
                    x->f_lines->setAzimuthDirect(i, (double)i / (double)x->f_recomposer->getNumberOfChannels() * HOA_2PI);
                    canvas_resume_dsp(dspState);
                }
            }
        }
    }
    return 0;
}

t_pd_err ramp_set(t_hoa_recomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        {
            x->f_ramp = clip_min(atom_getfloat(argv), 0);
            x->f_lines->setRamp(x->f_ramp / 1000. * sys_getsr());
        }
    }
    
    return 0;
}

PolarLines::PolarLines(unsigned int numberOfSources)
{
    assert(numberOfSources > 0);
    m_number_of_sources = numberOfSources;
    
    m_values_old    = new float[m_number_of_sources * 2];
    m_values_new    = new float[m_number_of_sources * 2];
    m_values_step   = new float[m_number_of_sources * 2];
}

PolarLines::~PolarLines()
{
    delete [] m_values_old;
    delete [] m_values_new;
    delete [] m_values_step;
}

void PolarLines::setRamp(unsigned int ramp)
{
    m_ramp = clip_min(ramp, (long)1);
}

void PolarLines::setRadius(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_new[index]  = radius;
    m_values_step[index] = (m_values_new[index] - m_values_old[index]) / (double)m_ramp;
    m_counter = 0;
}

void PolarLines::setAzimuth(unsigned int index, double azimuth)
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
        if(m_values_new > m_values_old)
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

void PolarLines::setRadiusDirect(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_old[index] = m_values_new[index] = radius;
    m_values_step[index] = 0.;
    m_counter = 0;
}

void PolarLines::setAzimuthDirect(unsigned int index, double azimuth)
{
    assert(index < m_number_of_sources);
    m_values_old[index + m_number_of_sources] = m_values_new[index + m_number_of_sources] = azimuth;
    m_values_step[index + m_number_of_sources] = 0.;
    m_counter = 0;
}

void PolarLines::process(float* vector)
{
    cblas_saxpy(m_number_of_sources * 2, 1., m_values_step, 1, m_values_old, 1);
    if(m_counter++ >= m_ramp)
    {
        cblas_scopy(m_number_of_sources * 2, m_values_new, 1, m_values_old, 1);
        memset(m_values_step, 0, sizeof(float) * m_number_of_sources * 2);
        m_counter    = 0;
    }
    cblas_scopy(m_number_of_sources * 2, m_values_old, 1, vector, 1);
}

float PolarLines::processOne()
{
    m_values_old[0] += m_values_step[0];
    if(m_counter++ >= m_ramp)
    {
        m_values_old[0] = m_values_new[0];
        m_values_step[0] = 0.;
        m_counter    = 0;
    }
    return m_values_old[0];
}



