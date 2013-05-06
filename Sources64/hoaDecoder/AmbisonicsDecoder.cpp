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

AmbisonicsDecoder::AmbisonicsDecoder(long anOrder, long aNumberOfLoudspeakers, double anOffset, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_number_of_harmonics);
    
    m_decoder_matrix_float  = NULL;
    m_decoder_matrix_double = NULL;
    m_vector_float_output   = NULL;
    m_vector_double_output  = NULL;
    m_offset = Tools::degToRad(Tools::degreeWrap(anOffset));
    m_number_of_loudspeakers = 0;
    setNumberOfLoudspeakers(aNumberOfLoudspeakers);
}

void AmbisonicsDecoder::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{
    m_number_of_outputs		= Tools::clip_min(aNumberOfLoudspeakers, m_number_of_harmonics);
    if(m_number_of_loudspeakers != m_number_of_outputs)
    {
        if(m_decoder_matrix_float)
            Cicm_Free(m_decoder_matrix_float);
        if(m_decoder_matrix_double)
            Cicm_Free(m_decoder_matrix_double);
        if(m_vector_float_output)
            Cicm_Free(m_vector_float_output);
        if(m_vector_double_output)
            Cicm_Free(m_vector_double_output);
        
        m_number_of_loudspeakers = m_number_of_outputs;
        
        Cicm_Matrix_Float_Malloc(m_decoder_matrix_float, m_number_of_outputs, m_number_of_harmonics);
        Cicm_Matrix_Double_Malloc(m_decoder_matrix_double, m_number_of_outputs, m_number_of_harmonics);
        Cicm_Vector_Float_Malloc(m_vector_float_output, m_number_of_outputs);
        Cicm_Vector_Double_Malloc(m_vector_double_output, m_number_of_outputs);
        computeMatrix();
    }
}

long AmbisonicsDecoder::getNumberOfLoudspeakers()
{
    return m_number_of_loudspeakers;
}

void AmbisonicsDecoder::setOffset(double anOffset)
{
    m_offset = Tools::degToRad(Tools::degreeWrap(anOffset));
    computeMatrix();
}

double AmbisonicsDecoder::getOffset()
{
    return Tools::radToDeg(m_offset);
}

double AmbisonicsDecoder::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        double angle = CICM_2PI * ((double)anIndex / (double)(m_number_of_outputs)) + m_offset;
        angle = Tools::radianWrap(angle);
        return Tools::radToDeg(angle);
    }
    else
        return 0.;
}

std::string AmbisonicsDecoder::getLoudspeakerName(long anIndex)
{
    float angle = (anIndex / (double)m_number_of_loudspeakers * 360. + m_offset);
    if(angle > 360.)
        angle -= 360.;
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(angle) + "°";
    else
        return "No channel";
}


void AmbisonicsDecoder::computeMatrix()
{
    for (int i = 0; i < m_number_of_outputs; i++)
	{
		double angle = CICM_2PI * ((double)i / (double)(m_number_of_outputs)) + m_offset;
        angle = Tools::radianWrap(angle);
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
    Cicm_Free(m_vector_float_input);
    Cicm_Free(m_vector_double_input);
    
    Cicm_Free(m_decoder_matrix_float);
    Cicm_Free(m_decoder_matrix_double);
    Cicm_Free(m_vector_float_output);
    Cicm_Free(m_vector_double_output);
}

