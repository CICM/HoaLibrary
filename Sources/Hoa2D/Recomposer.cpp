/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Recomposer.h"

namespace Hoa2D
{
    Recomposer::Recomposer(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        m_harmonics_float   = new float[m_number_of_harmonics];
        m_harmonics_double  = new double[m_number_of_harmonics];
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_encoders.push_back(new Encoder(order));
            m_widers.push_back(new Wider(order));
        }
    }

    void Recomposer::setAzimuth(unsigned int index, const double azimuth)
    {
        assert(index < m_number_of_channels);
        m_encoders[index]->setAzimuth(azimuth);
    }
	
    void Recomposer::setWideningValue(unsigned int index, const double value)
    {
        assert(index < m_number_of_channels);
        m_widers[index]->setWideningValue(value);
    }
    
    void Recomposer::process(const float* inputs, float* outputs)
	{
		m_encoders[0]->process(inputs[0], m_harmonics_float);
        m_widers[0]->process(m_harmonics_float, outputs);
        for(unsigned int i = 1; i < m_number_of_channels; i++)
        {
            m_encoders[i]->process(inputs[i], m_harmonics_float);
            m_widers[i]->process(m_harmonics_float, m_harmonics_float);
            cblas_saxpy(m_number_of_harmonics, 1.f, m_harmonics_float, 1, outputs, 1);
        }
	}
	
	void Recomposer::process(const double* inputs, double* outputs)
	{
		m_encoders[0]->process(inputs[0], m_harmonics_double);
        m_widers[0]->process(m_harmonics_double, outputs);
        for(unsigned int i = 1; i < m_number_of_channels; i++)
        {
            m_encoders[i]->process(inputs[i], m_harmonics_double);
            m_widers[i]->process(m_harmonics_double, m_harmonics_double);
            cblas_daxpy(m_number_of_harmonics, 1.f, m_harmonics_double, 1, outputs, 1);
        }
	}
	
	Recomposer::~Recomposer()
	{
		m_encoders.clear();
        m_widers.clear();
        delete [] m_harmonics_double;
        delete [] m_harmonics_float;
	}
}

