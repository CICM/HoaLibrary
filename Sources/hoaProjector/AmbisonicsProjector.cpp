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

#include "AmbisonicsProjector.h"

AmbisonicsProjector::AmbisonicsProjector(long anOrder, long aNumberOfChannels, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
	m_number_of_outputs		= Tools::clip_min(aNumberOfChannels, m_number_of_harmonics);
    
	Cicm_Matrix_Float_Malloc(m_decoder_matrix_float, m_number_of_outputs, m_number_of_harmonics);
    Cicm_Matrix_Double_Malloc(m_decoder_matrix_double, m_number_of_outputs, m_number_of_harmonics);
    
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_vector_float_output, m_number_of_outputs);
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_vector_double_output, m_number_of_outputs);
    
    computeMatrix();
}

void AmbisonicsProjector::computeMatrix()
{
    for (int i = 0; i < m_number_of_outputs; i++)
	{
		double angle = CICM_2PI * ((double)i / (double)(m_number_of_outputs));
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

AmbisonicsProjector::~AmbisonicsProjector()
{
    Cicm_Free(m_decoder_matrix_float);
    Cicm_Free(m_decoder_matrix_double);
    Cicm_Free(m_vector_float_input);
    Cicm_Free(m_vector_double_input);
    Cicm_Free(m_vector_float_output);
    Cicm_Free(m_vector_double_output);
}

