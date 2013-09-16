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

#include "AmbisonicWider.h"

AmbisonicWider::AmbisonicWider(long anOrder, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
    m_number_of_inputs = m_number_of_harmonics + 1;

	m_wider_matrix = new cicm_vector_double[m_number_of_harmonics];
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		cicm_malloc_vec_d(m_wider_matrix[i], NUMBEROFLINEARPOINTS);
	}
	cicm_malloc_vec_f(m_harmonics_vector_float, m_number_of_harmonics);
	cicm_malloc_vec_d(m_harmonics_vector_double, m_number_of_harmonics);
	m_index_vector = NULL;
	m_vector_float = NULL;
    m_vector_double = NULL;
	computeWidenVector();
	setWidenValue(1.);
}

std::string AmbisonicWider::getInputName(long anIndex)
{
    if(anIndex == m_number_of_inputs-1)
        return "Widen value";
    else
        return Ambisonic::getHarmonicsName(anIndex);
}

std::string AmbisonicWider::getOutputName(long anIndex)
{
    return Ambisonic::getHarmonicsName(anIndex);
}

void AmbisonicWider::computeWidenVector()
{    
	double weight_order = log((double)(m_order + 1));
   
	for(int j = 0; j < NUMBEROFLINEARPOINTS; j++)
	{
		m_wider_matrix[0][j] = (1. - ((double)j / (double)(NUMBEROFLINEARPOINTS-1))) * weight_order + 1.;
	}
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		double minus =  Tools::clip_min(log((double)getHarmonicOrder(i)), 0.);
        minus = -minus;
        
		double dot	= Tools::clip_min(log((double)getHarmonicOrder(i) + 1.), 0.);
		dot += minus;
		dot  = 1. / dot;
       
		for(int j = 0; j < NUMBEROFLINEARPOINTS; j++)
		{
			double weight = (1. - ((double)j / (double)(NUMBEROFLINEARPOINTS-1))) * weight_order + 1.;
			double scale = ((double)j / (double)(NUMBEROFLINEARPOINTS-1)) * weight_order;
			double new_weight = (minus + scale) * dot;
			new_weight = Tools::clip(new_weight, 0., 1.);
			m_wider_matrix[i][j] = new_weight * weight;
		}
	}
	
}

void AmbisonicWider::setWidenValue(double aWidenValue)
{
	double widenValue = Tools::clip(aWidenValue, 0., 1.);
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		m_harmonics_vector_float[i] = m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
	}
}

void AmbisonicWider::setVectorSize(long aVectorSize)
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

AmbisonicWider::~AmbisonicWider()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		cicm_free(m_wider_matrix[i]);
	}
	cicm_free(m_wider_matrix);
	cicm_free(m_harmonics_vector_double);
	cicm_free(m_harmonics_vector_float);
	if(m_index_vector)
		free(m_index_vector);
	if(m_vector_double)
		cicm_free(m_vector_double);
	if(m_vector_float)
		cicm_free(m_vector_float);
}

