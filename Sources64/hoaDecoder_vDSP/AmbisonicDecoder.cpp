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


#include "AmbisonicDecoder.h"

AmbisonicDecoder::AmbisonicDecoder(long anOrder, long aNumberOfChannels, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= Tools::clip_min(aNumberOfChannels, m_number_of_harmonics);
	m_vector_size           = 0;
    
	Cicm_Signal_Matrix_Float_Malloc(m_decoder_matrix_float, m_number_of_harmonics, m_number_of_outputs);
    Cicm_Signal_Matrix_Double_Malloc(m_decoder_matrix_double, m_number_of_harmonics, m_number_of_outputs);
    
    Cicm_Signal_Vector_Float_Malloc(m_signal_vector_float_input, m_number_of_harmonics);
    Cicm_Signal_Vector_Float_Malloc(m_signal_vector_float_output, m_number_of_outputs);
    Cicm_Signal_Vector_Double_Malloc(m_signal_vector_double_input, m_number_of_harmonics);
    Cicm_Signal_Vector_Double_Malloc(m_signal_vector_double_output, m_number_of_outputs);
    
    computeMatrix();
	setVectorSize(aVectorSize);
}

long AmbisonicDecoder::getOrder()
{
	return m_order;
}

long AmbisonicDecoder::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicDecoder::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicDecoder::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicDecoder::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicDecoder::computeMatrix()
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
                double value = sin(fabs(index) * angle);
                m_decoder_matrix_float[j][i]    = value;
                m_decoder_matrix_double[j][i]   = value;
            }
			else
            {
                double value = cos(fabs(index) * angle);
                m_decoder_matrix_float[j][i]    = value;
                m_decoder_matrix_double[j][i]   = value;
            }
		}
	}
}

void AmbisonicDecoder::setVectorSize(int aVectorSize)
{
    if(aVectorSize != m_vector_size)
    {
        m_vector_size = Tools::clip_power_of_two(aVectorSize);
	}
}

AmbisonicDecoder::~AmbisonicDecoder()
{
    Cicm_Free(m_decoder_matrix_float);
    Cicm_Free(m_decoder_matrix_double);
    Cicm_Free(m_signal_vector_float_input);
    Cicm_Free(m_signal_vector_double_input);
    Cicm_Free(m_signal_vector_float_output);
    Cicm_Free(m_signal_vector_double_output);
}

