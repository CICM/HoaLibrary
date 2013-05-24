/*
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


#include "AmbisonicsDiffuser.h"

AmbisonicsDiffuser::AmbisonicsDiffuser(long anOrder, long aVectorSize, long aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    m_filters.push_back(new FilterBiquad(Cicm_Biquad_Highshelf, m_vector_size, m_sampling_rate));
    m_filters[0]->setAll(100., 1., 0.);
    for(int i = 1; i < m_number_of_harmonics - 1; i++)
    {
        m_filters.push_back(new FilterBiquad(Cicm_Biquad_Ambisonics, m_vector_size, m_sampling_rate));
        m_filters[i]->setAll(1000., 1., 0.);
    }
    
    m_filters.push_back(new FilterBiquad(Cicm_Biquad_Lowshelf, m_vector_size, m_sampling_rate));
    m_filters[m_number_of_harmonics-1]->setAll(1000., 1., 0.);
    
    m_number_of_inputs = m_number_of_harmonics + 1;
}

void AmbisonicsDiffuser::setDiffuseFactor(double aDiffusefactor)
{
    m_diffuse_factor = Tools::clip(aDiffusefactor, 0., 1.);
    double factor = aDiffusefactor * -45.;
    m_filters[0]->setGain(factor);
    factor = aDiffusefactor * 45.;
    for(int i = 1; i < m_number_of_harmonics - 1; i++)
    {
        m_filters[i]->setGain(factor);
    }
    factor = aDiffusefactor * 45.;
    m_filters[m_number_of_harmonics-1]->setGain(factor);
}

double AmbisonicsDiffuser::getDiffuseFactor()
{
    return m_diffuse_factor;
}

AmbisonicsDiffuser::~AmbisonicsDiffuser()
{
	m_filters.clear();
}

