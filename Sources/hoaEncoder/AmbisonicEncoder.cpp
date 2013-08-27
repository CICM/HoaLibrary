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

#include "AmbisonicEncoder.h"

AmbisonicEncoder::AmbisonicEncoder(long anOrder, long aMode, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
    m_mode = Tools::clip(aMode, (long)0, (long)1);
	if(m_mode == Hoa_Split)
		m_number_of_inputs	= m_order + 2;
	else
		m_number_of_inputs	= 2;
    
    m_encoder_matrix = new Cicm_Vector_Double[m_number_of_harmonics];
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		Cicm_Vector_Double_Malloc(m_encoder_matrix[i], NUMBEROFCIRCLEPOINTS);
	}
	Cicm_Vector_Float_Malloc(m_harmonics_vector_float, m_number_of_harmonics);
	Cicm_Vector_Double_Malloc(m_harmonics_vector_double, m_number_of_harmonics);
    
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

long AmbisonicEncoder::getMode()
{
	return m_mode;
}

void AmbisonicEncoder::setAngle(double anAngle)
{
    float angle = Tools::radianWrap(anAngle) / CICM_2PI;
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_harmonics_vector_float[i] = m_harmonics_vector_double[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
}

void AmbisonicEncoder::setVectorSize(long aVectorSize)
{
	Ambisonic::setVectorSize(aVectorSize);
	if(m_index_vector)
		free(m_index_vector);
	if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
	m_index_vector = new int[m_vector_size];
	Cicm_Vector_Float_Malloc(m_vector_float, m_vector_size);
	Cicm_Vector_Double_Malloc(m_vector_double, m_vector_size);
}

AmbisonicEncoder::~AmbisonicEncoder()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		Cicm_Free(m_encoder_matrix[i]);
	}
	Cicm_Free(m_encoder_matrix);
	Cicm_Free(m_harmonics_vector_double);
	Cicm_Free(m_harmonics_vector_float);
	if(m_index_vector)
		free(m_index_vector);
	if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
}