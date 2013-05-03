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

AmbisonicsRestitution::AmbisonicsRestitution(long anOrder, double anAngle, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_number_of_virtual_loudspeakers = m_number_of_harmonics+1;
    m_number_of_real_loudspeakers    = Tools::clip(<#Type aValue#>)
	m_decoder = new AmbisonicsDecoder(anOrder, m_number_of_loudspeakers, aVectorSize);
    
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_number_of_loudspeakers);
    
    Cicm_Vector_Float_Malloc(m_loudspeakers_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_loudspeakers_vector_double, m_number_of_loudspeakers);
    
    Cicm_Vector_Float_Malloc(m_left_gains_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Float_Malloc(m_right_gains_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_left_gains_vector_double, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_right_gains_vector_double, m_number_of_loudspeakers);
    
    setLoudspeakersDelta(anAngle);
    m_number_of_outputs = 2;
}

void AmbisonicsRestitution::setLoudspeakersDelta(double anAngle)
{
    m_delta = Tools::clip(anAngle, 0., 180.);
    double loudspeakerAngleLeft = (m_delta / 2.) / 360. * CICM_2PI;
    double loudspeakerAngleRight = - loudspeakerAngleLeft;
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        double virtualLoudspeakerAngle = ((double)i / (double)m_number_of_loudspeakers) * CICM_2PI;
        double distance = virtualLoudspeakerAngle - loudspeakerAngleLeft;
        m_left_gains_vector_double[i]   = fabs(cos(distance / 2.));
        m_left_gains_vector_float[i]    = m_left_gains_vector_double[i];
        distance = fabs((virtualLoudspeakerAngle - loudspeakerAngleRight));
        m_right_gains_vector_double[i]  = fabs(cos(distance / 2.));
        m_right_gains_vector_float[i]   = m_right_gains_vector_double[i];
    }

}

double AmbisonicsRestitution::getLoudspeakersDelta()
{
    return m_delta;
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

