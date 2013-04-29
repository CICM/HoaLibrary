/*
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

#include "AmbisonicsDecoder.h"

AmbisonicsDecoder::AmbisonicsDecoder(long anOrder, long aNumberOfChannels, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
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

void AmbisonicsDecoder::computeMatrix()
{
    for (int i = 0; i < m_number_of_outputs; i++)
	{
		double angle = CICM_2PI * ((double)i / (double)(m_number_of_outputs));
		for (int j = 0; j < m_number_of_harmonics; j++)
		{
            int index = getHarmonicIndex(j);
            if(j == 0)
            {
                Cicm_Matrix_Float_Set(m_decoder_matrix_float, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
                Cicm_Matrix_Double_Set(m_decoder_matrix_double, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
            }
            else if(index > 0)
            {
                double value = cos(fabs(index) * angle) / (double)(m_order+1.);
                Cicm_Matrix_Float_Set(m_decoder_matrix_float, i, j, m_number_of_harmonics, value);
                Cicm_Matrix_Double_Set(m_decoder_matrix_double, i, j, m_number_of_harmonics, value);
            }
			else if(index < 0)
            {
                double value = sin(fabs(index) * angle) / (double)(m_order+1.);
                Cicm_Matrix_Float_Set(m_decoder_matrix_float, i, j, m_number_of_harmonics, value);
                Cicm_Matrix_Double_Set(m_decoder_matrix_double, i, j, m_number_of_harmonics, value);
            }
		}
    }
}

AmbisonicsDecoder::~AmbisonicsDecoder()
{
    Cicm_Free(m_decoder_matrix_float);
    Cicm_Free(m_decoder_matrix_double);
    Cicm_Free(m_vector_float_input);
    Cicm_Free(m_vector_double_input);
    Cicm_Free(m_vector_float_output);
    Cicm_Free(m_vector_double_output);
}

