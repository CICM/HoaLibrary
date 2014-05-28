/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "MapPolarLines3D.h"

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