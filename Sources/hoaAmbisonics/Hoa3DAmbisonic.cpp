/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Hoa3DAmbisonic.h"

namespace Hoa3D
{
    Ambisonic::Ambisonic(unsigned int order)
    {
        m_order					= Tools::clip_min(order, (long)1);
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
        if(index < m_number_of_harmonics)
        {
            return m_harmonics_arguments[index];
        }
        else
            return 0;
    }
    
    long Ambisonic::getHarmonicBand(unsigned int index)
    {
        if(index < m_number_of_harmonics)
        {
            return m_harmonics_bands[index];
        }
        else
            return 0;
    }
    
    std::string Ambisonic::getHarmonicsName(unsigned int index)
    {
        if(index < m_number_of_harmonics)
            return "Harmonic " + Tools::intToString(getHarmonicBand(index)) + " " + Tools::intToString(getHarmonicArgument(index));
        else
            return "No harmonic";
    }
    
    Ambisonic::~Ambisonic()
    {
        cicm_free(m_harmonics_arguments);
        cicm_free(m_harmonics_bands);
    }
}

