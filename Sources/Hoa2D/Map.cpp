/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Map.h"

namespace Hoa2D
{
    Map::Map(unsigned int order, unsigned int numberOfSources) : Ambisonic(order)
    {
        assert(numberOfSources > 0);
        
        m_number_of_sources = numberOfSources;
        m_harmonics_float   = new float[m_number_of_harmonics];
        m_harmonics_double  = new double[m_number_of_harmonics];
        m_gains             = new double[m_number_of_harmonics];
		m_muted				= new bool[numberOfSources];
		m_first_source      = 0;
		
        for(unsigned int i = 0; i < m_number_of_sources; i++)
        {
			setMute(i, 0);
            m_encoders.push_back(new Encoder(order));
            m_widers.push_back(new Wider(order));
        }
    }
    
    void Map::setAzimuth(const unsigned int index, const double azimuth)
    {
        assert(index < m_number_of_sources);
        m_encoders[index]->setAzimuth(azimuth);
    }
	
    void Map::setRadius(const unsigned int index, const double radius)
    {
        assert(index < m_number_of_sources);
        if(radius >= 1.)
        {
            m_gains[index] = 1. / (radius * radius);
            m_widers[index]->setWideningValue(1.);
        }
        else
        {
            m_gains[index] = 1.;
			m_widers[index]->setWideningValue(radius);
        }
    }
    
    void Map::setMute(const unsigned int index, const bool muted)
    {
        assert(index < m_number_of_sources);
        m_muted[index] = muted;
        m_first_source = -1;
        for(unsigned int i = 0; i < m_number_of_sources; i++)
        {
            if(!m_muted[i])
            {
                m_first_source = i;
                break;
            }
        }
    }
    
    void Map::process(const float* inputs, float* outputs)
    {
        if(m_first_source > -1)
        {
            m_encoders[m_first_source]->process(inputs[m_first_source] * m_gains[m_first_source], m_harmonics_float);
            m_widers[m_first_source]->process(m_harmonics_float, outputs);
            for(unsigned int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if (!m_muted[i])
                {
                    m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_float);
                    m_widers[i]->process(m_harmonics_float, m_harmonics_float);
                    cblas_saxpy(m_number_of_harmonics, 1.f, m_harmonics_float, 1, outputs, 1);
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_harmonics; i++)
                outputs[i] = 0.f;
        }
    }
    
    void Map::process(const double* inputs, double* outputs)
    {
		if(m_first_source > -1)
        {
            m_encoders[m_first_source]->process(inputs[m_first_source] * m_gains[m_first_source], m_harmonics_double);
            m_widers[m_first_source]->process(m_harmonics_double, outputs);
			
            for(unsigned int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if (!m_muted[i])
                {
                    m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_double);
                    m_widers[i]->process(m_harmonics_double, m_harmonics_double);
                    cblas_daxpy(m_number_of_harmonics, 1.f, m_harmonics_double, 1, outputs, 1);
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_harmonics; i++)
                outputs[i] = 0.;
        }
    }
    
    Map::~Map()
    {
        m_encoders.clear();
        m_widers.clear();
        delete [] m_harmonics_double;
        delete [] m_harmonics_float;
        delete [] m_gains;
        delete [] m_muted;
    }
}

