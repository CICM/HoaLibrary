/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Ambisonic.h"

namespace Hoa3D
{
    Ambisonic::Ambisonic(unsigned int order)
    {
        assert(order > 0);
        m_order					= order;
        m_number_of_harmonics	= (m_order + 1) * (m_order + 1);
        m_number_of_inputs		= m_number_of_harmonics;
        m_number_of_outputs		= m_number_of_harmonics;
        
        m_harmonics_arguments   = new long[m_number_of_harmonics];
        m_harmonics_bands      = new long[m_number_of_harmonics];
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_harmonics_bands[i] = sqrtf((float)i);
            int index = i - (m_harmonics_bands[i]) * (m_harmonics_bands[i]);
            
            int index2 = (index - 1) / 2. + 1.;
            if (index % 2 == 1)
                index2 = -index2;
            m_harmonics_arguments[i] = index2;
        }
    }
    
    long Ambisonic::getOrder()
    {
        return m_order;
    }
    
    long Ambisonic::getNumberOfHarmonics()
    {
        return m_number_of_harmonics;
    }
    
    long Ambisonic::getNumberOfInputs()
    {
        return m_number_of_inputs;
    }
    
    long Ambisonic::getNumberOfOutputs()
    {
        return m_number_of_outputs;
    }
    
    long Ambisonic::getHarmonicArgument(unsigned int index)
    {
        assert(index < m_number_of_harmonics);
        return m_harmonics_arguments[index];
    }
    
    long Ambisonic::getHarmonicBand(unsigned int index)
    {
        assert(index < m_number_of_harmonics);
        return m_harmonics_bands[index];
    }
    
    std::string Ambisonic::getHarmonicsName(unsigned int index)
    {
        assert(index < m_number_of_harmonics);
        return "Harmonic " + Tools::intToString(getHarmonicBand(index)) + " " + Tools::intToString(getHarmonicArgument(index));
    }
    
    Ambisonic::~Ambisonic()
    {
        cicm_free(m_harmonics_arguments);
        cicm_free(m_harmonics_bands);
    }
}

