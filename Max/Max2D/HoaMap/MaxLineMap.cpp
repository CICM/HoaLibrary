/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "MaxLineMap.h"

PolarLines::PolarLines(unsigned int numberOfSources)
{
    assert(numberOfSources > 0);
    m_number_of_sources = numberOfSources;
    
    m_values_old    = (float *)malloc(m_number_of_sources * 2 * sizeof(float));
    m_values_new    = (float *)malloc(m_number_of_sources * 2 * sizeof(float));
    m_values_step   = (float *)malloc(m_number_of_sources * 2 * sizeof(float));
}

PolarLines::~PolarLines()
{
    free(m_values_old);
    free(m_values_new);
    free(m_values_step);
}

void PolarLines::setRamp(unsigned int ramp)
{
	if(ramp < 1)
		ramp = 1;
    m_ramp = ramp;
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

