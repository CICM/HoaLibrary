/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Ambisonic.h"

namespace Hoa2D
{
    Ambisonic::Ambisonic(unsigned int order)
    {
        assert(order > 0);
        m_order					= order;
        m_number_of_harmonics	= m_order * 2 + 1;
        m_number_of_inputs		= m_number_of_harmonics;
        m_number_of_outputs		= m_number_of_harmonics;
        
        m_harmonics_arguments   = new long[m_number_of_harmonics];
        m_harmonics_arguments[0] = 0;
        for(int i = 1, j = 1; i < m_order; i++, j += 2)
        {
            m_harmonics_arguments[j] = -i;
            m_harmonics_arguments[j+1] = i;
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
        return abs(m_harmonics_arguments[index]);
    }
    
    std::string Ambisonic::getHarmonicsName(unsigned int index)
    {
        assert(index < m_number_of_harmonics);
        return "Harmonic " + Tools::intToString(getHarmonicArgument(index));
    }
    
    Ambisonic::~Ambisonic()
    {
        delete [] m_harmonics_arguments;
    }
}

