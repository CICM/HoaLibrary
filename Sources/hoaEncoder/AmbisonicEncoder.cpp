/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#include "AmbisonicEncoder.h"

AmbisonicEncoder::AmbisonicEncoder(long anOrder, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
    m_number_of_inputs	= 2;
    
    m_encoder_matrix = new cicm_vector_double[m_number_of_harmonics];
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		cicm_malloc_vec_d(m_encoder_matrix[i], NUMBEROFCIRCLEPOINTS);
	}
	cicm_malloc_vec_f(m_harmonics_vector_float, m_number_of_harmonics);
	cicm_malloc_vec_d(m_harmonics_vector_double, m_number_of_harmonics);
    
    m_index_vector = NULL;
	m_vector_float = NULL;
    m_vector_double = NULL;
    
    for(int i = 0; i < m_number_of_harmonics; i++)
	{
        if(getHarmonicIndex(i) >= 0)
        {
            for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
                m_encoder_matrix[i][j] = cos((double)getHarmonicOrder(i) * (((double)j / (double)NUMBEROFCIRCLEPOINTS) * (double)CICM_2PI));
        }
        else
        {
            for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
                m_encoder_matrix[i][j] = sin((double)getHarmonicOrder(i) * (((double)j / (double)NUMBEROFCIRCLEPOINTS) * (double)CICM_2PI));
        }
    }
	setAngle(0.);
}

void AmbisonicEncoder::setAngle(double anAngle)
{
    int index = Tools::radian_wrap(anAngle) * CICM_1OVER2PI_RATIO;
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_harmonics_vector_float[i] = m_harmonics_vector_double[i] = m_encoder_matrix[i][index];
}

void AmbisonicEncoder::setVectorSize(long aVectorSize)
{
	Ambisonic::setVectorSize(aVectorSize);
	if(m_index_vector)
		free(m_index_vector);
	if(m_vector_double)
		cicm_free(m_vector_double);
	if(m_vector_float)
		cicm_free(m_vector_float);
	m_index_vector = new int[m_vector_size];
	cicm_malloc_vec_f(m_vector_float, m_vector_size);
	cicm_malloc_vec_d(m_vector_double, m_vector_size);
}

AmbisonicEncoder::~AmbisonicEncoder()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		cicm_free(m_encoder_matrix[i]);
	}
	cicm_free(m_encoder_matrix);
	cicm_free(m_harmonics_vector_double);
	cicm_free(m_harmonics_vector_float);
	if(m_index_vector)
		free(m_index_vector);
	if(m_vector_double)
		cicm_free(m_vector_double);
	if(m_vector_float)
		cicm_free(m_vector_float);
}