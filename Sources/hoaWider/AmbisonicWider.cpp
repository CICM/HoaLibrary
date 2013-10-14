/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

