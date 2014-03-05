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
		m_radius            = new double[numberOfSources];
		m_azimuth           = new double[numberOfSources];
		m_muted				= new bool[numberOfSources];
		
        for(unsigned int i = 0; i < m_number_of_sources; i++)
        {
			m_muted[i] = false;
			m_radius[i] = 1.;
			m_azimuth[i] = 0.;
            m_encoders.push_back(new Encoder(order));
            m_widers.push_back(new Wider(order));
        }
    }
    
    void Map::setAzimuth(unsigned int index, const double azimuth)
    {
        assert(index < m_number_of_sources);
        m_encoders[index]->setAzimuth(azimuth);
		m_azimuth[index] = azimuth;
    }
	
    void Map::setRadius(unsigned int index, const double radius)
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
            m_widers[index]->setWideningValue(clip_min(radius, 0.));
        }
		m_radius[index] = radius;
    }
    
    void Map::process(const float* inputs, float* outputs)
    {
		unsigned int i;
		
		for(i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_harmonics_float[i] = 0;

        for(unsigned int i = 1; i < m_number_of_sources; i++)
        {
			if (!m_muted[i])
			{
				m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_float);
				m_widers[i]->process(m_harmonics_float, m_harmonics_float);
				cblas_saxpy(m_number_of_harmonics, 1.f, m_harmonics_float, 1, outputs, 1);
			}
        }
    }
    
    void Map::process(const double* inputs, double* outputs)
    {
		unsigned int i;
		
		for(i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_harmonics_double[i] = 0;
		
        for(i = 0; i < m_number_of_sources; i++)
        {
			if (!m_muted[i])
			{
				m_encoders[i]->process(inputs[i] * m_gains[i], m_harmonics_double);
				m_widers[i]->process(m_harmonics_double, m_harmonics_double);
				cblas_daxpy(m_number_of_harmonics, 1.f, m_harmonics_double, 1, outputs, 1);
			}
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

