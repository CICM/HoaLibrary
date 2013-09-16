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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicProjector.h"

AmbisonicProjector::AmbisonicProjector(long anOrder, long aNumberOfLoudspeakers, long aVectorSize) : Ambisonic(anOrder, aVectorSize), Planewaves(aNumberOfLoudspeakers, aVectorSize)
{        
    m_decoder_matrix_float = NULL;
    m_decoder_matrix_double = NULL;
    m_input_matrix_float = NULL;
    m_input_matrix_double = NULL;
    m_output_matrix_float = NULL;
    m_output_matrix_double = NULL;
    
    setNumberOfLoudspeakers(aNumberOfLoudspeakers);
}

long AmbisonicProjector::getNumberOfInputs()
{
    return Ambisonic::getNumberOfInputs();
}

long AmbisonicProjector::getNumberOfOutputs()
{
    return Planewaves::getNumberOfOutputs();
}

void AmbisonicProjector::computeMatrix()
{
    for (int i = 0; i < m_number_of_loudspeakers; i++)
	{
		double angle = CICM_2PI * ((double)i / (double)m_number_of_loudspeakers);
		for (int j = 0; j < m_number_of_harmonics; j++)
		{
            int index = (int)((((double)j - 1.) / 2.) + 1.);
			if (j % 2 == 1)
				index = -index;
			
			if (index < 0)
            {
                double value = sin(fabs((double)index) * angle);
                m_decoder_matrix_float[i * m_number_of_harmonics + j]    = value / (double)(m_order+1.);
                m_decoder_matrix_double[i * m_number_of_harmonics + j]   = value / (double)(m_order+1.);
            }
			else
            {
                double value = cos(fabs((double)index) * angle);
                m_decoder_matrix_float[i * m_number_of_harmonics + j]    = value / (double)(m_order+1.);
                m_decoder_matrix_double[i * m_number_of_harmonics + j]   = value / (double)(m_order+1.);
            }
            
            if (index == 0)
            {
                m_decoder_matrix_float[i * m_number_of_harmonics + j]    /= 2.;
                m_decoder_matrix_double[i * m_number_of_harmonics + j]   /= 2.;
            }
            
		}
	}
}

void AmbisonicProjector::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{
    if(aNumberOfLoudspeakers < m_number_of_harmonics)
        aNumberOfLoudspeakers = m_number_of_harmonics;
    Planewaves::setNumberOfLoudspeakers(aNumberOfLoudspeakers, 0);
    
    Planewaves::m_number_of_inputs = Ambisonic::m_number_of_inputs;
    Ambisonic::m_number_of_outputs = Planewaves::m_number_of_outputs;
    
    if(m_decoder_matrix_float)
        cicm_free(m_decoder_matrix_float);
    if(m_decoder_matrix_double)
        cicm_free(m_decoder_matrix_double);
    
    cicm_malloc_mat_f(m_decoder_matrix_float, m_number_of_loudspeakers, m_number_of_harmonics);
    cicm_malloc_mat_d(m_decoder_matrix_double, m_number_of_loudspeakers, m_number_of_harmonics);
    computeMatrix();
}

void AmbisonicProjector::setVectorSize(long aVectorSize)
{
    Planewaves::setVectorSize(aVectorSize);
    Ambisonic::setVectorSize(aVectorSize);
    
    if(m_input_matrix_float)
        cicm_free(m_input_matrix_float);
    if(m_input_matrix_double)
        cicm_free(m_input_matrix_double);
    if(m_output_matrix_float)
        cicm_free(m_output_matrix_float);
    if(m_output_matrix_double)
        cicm_free(m_output_matrix_double);
    
    cicm_malloc_mat_f(m_input_matrix_float, m_number_of_harmonics, Ambisonic::m_vector_size);
    cicm_malloc_mat_d(m_input_matrix_double, m_number_of_harmonics, Ambisonic::m_vector_size);
    cicm_malloc_mat_f(m_output_matrix_float, m_number_of_loudspeakers, Ambisonic::m_vector_size);
    cicm_malloc_mat_d(m_output_matrix_double, m_number_of_loudspeakers, Ambisonic::m_vector_size);
}

AmbisonicProjector::~AmbisonicProjector()
{
    if(m_decoder_matrix_float)
        cicm_free(m_decoder_matrix_float);
    if(m_decoder_matrix_double)
        cicm_free(m_decoder_matrix_double);
    if(m_input_matrix_float)
        cicm_free(m_input_matrix_float);
    if(m_input_matrix_double)
        cicm_free(m_input_matrix_double);
    if(m_output_matrix_float)
        cicm_free(m_output_matrix_float);
    if(m_output_matrix_double)
        cicm_free(m_output_matrix_double);
}

