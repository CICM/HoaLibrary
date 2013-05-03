/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#include "AmbisonicsRestitution.h"

AmbisonicsRestitution::AmbisonicsRestitution(long anOrder, long aNumberOfLoudspeakers, long lowFrequencyEffect, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_number_of_virtual_loudspeakers = m_number_of_harmonics+1;
    m_number_of_real_loudspeakers    = Tools::clip_min(aNumberOfLoudspeakers, (long)0);
    m_low_frequency_effect           = Tools::clip(lowFrequencyEffect, (long)0, (long)1);
	m_decoder = new AmbisonicsDecoder(anOrder, m_number_of_virtual_loudspeakers, aVectorSize);
    
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_number_of_virtual_loudspeakers);
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_number_of_virtual_loudspeakers);
    Cicm_Vector_Float_Malloc(m_loudspeakers_vector_float, m_number_of_virtual_loudspeakers);
    Cicm_Vector_Double_Malloc(m_loudspeakers_vector_double, m_number_of_virtual_loudspeakers);
    
    m_loudspeakers_gains_vector_float   = new Cicm_Vector_Float[m_number_of_real_loudspeakers];
    m_loudspeakers_gains_vector_double  = new Cicm_Vector_Double[m_number_of_real_loudspeakers];

    for(int i = 0; i < m_number_of_real_loudspeakers; i++)
    {
        Cicm_Vector_Float_Malloc(m_loudspeakers_gains_vector_float[i], m_number_of_virtual_loudspeakers);
        Cicm_Vector_Double_Malloc(m_loudspeakers_gains_vector_double[i], m_number_of_virtual_loudspeakers);
    }
    
    m_angles_of_loudspeakers = new double[m_number_of_real_loudspeakers];
    for (int i = 0; i < m_number_of_real_loudspeakers; i++)
        setLoudspeakerAngle(i, (double)i / (double)m_number_of_real_loudspeakers * CICM_2PI);
    
    m_number_of_outputs = m_number_of_real_loudspeakers + m_low_frequency_effect;
}

void AmbisonicsRestitution::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_real_loudspeakers)
    {
        m_angles_of_loudspeakers[anIndex] = anAngle / 360. * CICM_2PI;
    }
    computeLoudspeakersGains();
}

double AmbisonicsRestitution::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_real_loudspeakers)
        return m_angles_of_loudspeakers[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

void AmbisonicsRestitution::computeLoudspeakersGains()
{
    for(int i = 0; i < m_number_of_virtual_loudspeakers; i++)
    {
        double virtualAngle = ((double)i / (double)m_number_of_virtual_loudspeakers) * CICM_2PI;
        for(int j = 0; j < m_number_of_real_loudspeakers - 1; j++)
        {
            if(virtualAngle >= m_angles_of_loudspeakers[j] && virtualAngle >= m_angles_of_loudspeakers[j+1])
            {
                
            }
        }
        /*
        double distance = virtualLoudspeakerAngle - loudspeakerAngleLeft;
        m_left_gains_vector_double[i]   = fabs(cos(distance / 2.));
        m_left_gains_vector_float[i]    = m_left_gains_vector_double[i];
        distance = fabs((virtualLoudspeakerAngle - loudspeakerAngleRight));
        m_right_gains_vector_double[i]  = fabs(cos(distance / 2.));
        m_right_gains_vector_float[i]   = m_right_gains_vector_double[i];
         */
    }

}


AmbisonicsRestitution::~AmbisonicsRestitution()
{
    Cicm_Free(m_vector_float_input);
    Cicm_Free(m_vector_double_input);
    Cicm_Free(m_loudspeakers_vector_float);
    Cicm_Free(m_loudspeakers_vector_double);
    Cicm_Free(m_left_gains_vector_float);
    Cicm_Free(m_right_gains_vector_float);
    Cicm_Free(m_left_gains_vector_double);
    Cicm_Free(m_right_gains_vector_double);
	delete m_decoder;
}

