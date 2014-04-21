/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Ambisonic_3D.h"

namespace Hoa3D
{
    Ambisonic::Ambisonic(unsigned int order)
    {
        m_order					= order;
        m_number_of_harmonics	= (m_order + 1) * (m_order + 1);
        
        m_harmonics_arguments   = new int[m_number_of_harmonics];
        m_harmonics_bands      = new unsigned int[m_number_of_harmonics];
        for(unsigned int i = 0; i < m_number_of_harmonics; i++)
        {
            m_harmonics_bands[i] = sqrtf((float)i);
            int index = i - (m_harmonics_bands[i]) * (m_harmonics_bands[i]);
            
            int index2 = (index - 1) / 2. + 1.;
            if (index % 2 == 1)
                index2 = -index2;
            m_harmonics_arguments[i] = index2;
        }
    }

    Ambisonic::~Ambisonic()
    {
        delete [] m_harmonics_arguments;
        delete [] m_harmonics_bands;
    }
}

