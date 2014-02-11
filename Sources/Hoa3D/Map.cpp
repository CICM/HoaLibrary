/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Map.h"

namespace Hoa3D
{
    Map::Map(unsigned int order, unsigned int numberOfSources) : Ambisonic(order)
    {
        assert(numberOfSources > 0);
        
        m_number_of_sources = numberOfSources;
        m_harmonics_float   = new float[m_number_of_harmonics];
        m_harmonics_double  = new double[m_number_of_harmonics];
        m_gains             = new double[m_number_of_harmonics];
        for(int i = 0; i < m_number_of_sources; i++)
        {
            m_encoders.push_back(new Encoder(order));
            m_widers.push_back(new Wider(order));
        }
    }
    
    void Map::setAzimuth(const unsigned int index, const double azimuth)
    {
        assert(index < m_number_of_sources);
        m_encoders[index]->setAzimuth(azimuth);
    }
    
    void Map::setElevation(const unsigned int index, const double elevation)
    {
        assert(index < m_number_of_sources);
        m_encoders[index]->setElevation(elevation);
    }
    
    void Map::setDistance(const unsigned int index, const double distance)
    {
        assert(index < m_number_of_sources);
        if(distance >= 1.)
        {
            m_gains[index] = 1. / (distance * distance);
            m_widers[index]->setWideningValue(1.);
        }
        else
        {
            m_gains[index] = 1.;
            m_widers[index]->setWideningValue(Tools::clip_min(distance, 0.));
        }
    }
    
    void Map::process(const float* inputs, float* outputs)
    {
        m_encoders[0]->process(inputs[0] * m_gains[0], outputs);
        m_widers[0]->process(outputs, outputs);
        for(int i = 1; i < m_number_of_sources; i++)
        {
            m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_float);
            m_widers[i]->process(m_harmonics_float, m_harmonics_float);
            cblas_saxpy(m_number_of_harmonics, 1.f, m_harmonics_float, 1, outputs, 1);
        }
    }
    
    void Map::process(const double* inputs, double* outputs)
    {
        m_encoders[0]->process(inputs[0] * m_gains[0], outputs);
        m_widers[0]->process(outputs, outputs);
        for(int i = 1; i < m_number_of_sources; i++)
        {
            m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_double);
            m_widers[i]->process(m_harmonics_double, m_harmonics_double);
            cblas_daxpy(m_number_of_harmonics, 1.f, m_harmonics_double, 1, outputs, 1);
        }
    }
    
    Map::~Map()
    {
        m_encoders.clear();
        m_widers.clear();
        delete [] m_harmonics_double;
        delete [] m_harmonics_float;
        delete [] m_gains;
    }
}

