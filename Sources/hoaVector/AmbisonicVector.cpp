/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "AmbisonicVector.h"

Ambisonicvector::Ambisonicvector(long aNumberOfLoudspeakers,  std::string aMode, long aVectorSize)
{
	m_number_of_loudspeakers = Tools::clip_min(aNumberOfLoudspeakers, (long)3);
	m_number_of_inputs		= m_number_of_loudspeakers;
	m_number_of_outputs		= 4;
    
    m_abscissa_of_loudspeakers = new double[m_number_of_loudspeakers];
    m_ordinate_of_loudspeakers = new double[m_number_of_loudspeakers];
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_abscissa_of_loudspeakers[i] = cos(((double)i / m_number_of_loudspeakers) * (double)CICM_2PI);
        m_ordinate_of_loudspeakers[i] = sin(((double)i / m_number_of_loudspeakers) * (double)CICM_2PI);
    }
    setVectorSize(aVectorSize);
    setMode("aMode");
}

long Ambisonicvector::getNumberOfLoudspeakers()
{
	return m_number_of_loudspeakers;
}

long Ambisonicvector::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long Ambisonicvector::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long Ambisonicvector::getVectorSize()
{
	return m_vector_size;   
}

std::string Ambisonicvector::getMode()
{
    if(!m_mode)
        return "polar";
    else
        return "cartesian";
}

void Ambisonicvector::setMode(std::string aMode)
{
    if(aMode == "cartesian")
        m_mode = 1;
    else
        m_mode = 0;        
}

void Ambisonicvector::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

Ambisonicvector::~Ambisonicvector()
{
	free(m_abscissa_of_loudspeakers);
    free(m_ordinate_of_loudspeakers);
}
