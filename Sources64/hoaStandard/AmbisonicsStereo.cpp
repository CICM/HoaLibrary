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

#include "AmbisonicsStereo.h"

AmbisonicsStereo::AmbisonicsStereo(long anOrder, double aDelta, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_number_of_loudspeakers = m_number_of_harmonics+1;
    m_delta = Tools::clip(aDelta, 0., 180.);
    double loudspeakerAngleLeft = (m_delta / 2.) / 360. * CICM_2PI;
    double loudspeakerAngleRight = (360. - m_delta / 2.) / 360. * CICM_2PI;
	m_decoder = new AmbisonicsDecoder(anOrder, m_number_of_loudspeakers, aVectorSize);
    
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_number_of_loudspeakers);
    
    Cicm_Vector_Float_Malloc(m_loudspeakers_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_loudspeakers_vector_double, m_number_of_loudspeakers);
    
    Cicm_Vector_Float_Malloc(m_left_gains_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Float_Malloc(m_right_gains_vector_float, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_left_gains_vector_double, m_number_of_loudspeakers);
    Cicm_Vector_Double_Malloc(m_right_gains_vector_double, m_number_of_loudspeakers);
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        double virtualLoudspeakerAngle = ((double)i / (double)m_number_of_loudspeakers) * CICM_2PI;
        double distance = Tools::radianDistance(virtualLoudspeakerAngle, loudspeakerAngleLeft) / 2.;
        m_left_gains_vector_double[i]   = cos();
        m_right_gains_vector_double[i]  = cos(Tools::radianDistance(virtualLoudspeakerAngle, loudspeakerAngleRight) / 2.);
        m_left_gains_vector_float[i]    = m_left_gains_vector_double[i];
        m_right_gains_vector_float[i]   = m_right_gains_vector_double[i];
    }
    m_number_of_outputs = 2;
}


AmbisonicsStereo::~AmbisonicsStereo()
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

