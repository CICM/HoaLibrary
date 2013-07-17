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

#include "AmbisonicsWider.h"

AmbisonicsWider::AmbisonicsWider(long anOrder, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_number_of_inputs = m_number_of_harmonics + 1;
    Cicm_Vector_Float_Malloc  (m_scale_vector_float, m_vector_size);
    Cicm_Vector_Float_Malloc  (m_weight_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc (m_scale_vector_double, m_vector_size);
    Cicm_Vector_Double_Malloc (m_weight_vector_double, m_vector_size);
	computeWidenVector();
	setWidenValue(1.);
}

void AmbisonicsWider::computeWidenVector()
{
    Cicm_Vector_Float_Malloc  (m_minus_vector_float, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc  (m_dot_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc (m_minus_vector_double, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc (m_dot_vector_double, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc  (m_harmonics_float, m_number_of_harmonics - 1);
    Cicm_Vector_Double_Malloc (m_harmonics_double, m_number_of_harmonics - 1);
    
	m_order_weight_double = log((double)(m_order + 1));
    m_order_weight_float = m_order_weight_double;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_minus_vector_double[i] =  Tools::clip_min(log((double)abs(getHarmonicIndex(i))), 0.);
        m_minus_vector_double[i] = -m_minus_vector_double[i];
        m_minus_vector_float[i]  =  m_minus_vector_double[i];
        
		m_dot_vector_double[i]	= Tools::clip_min(log((double)abs(getHarmonicIndex(i)) + 1.), 0.);
		m_dot_vector_double[i] += m_minus_vector_double[i];
		m_dot_vector_double[i]  = 1. / m_dot_vector_double[i];
        m_dot_vector_float[i]   = m_dot_vector_double[i];
	}
}

void AmbisonicsWider::setWidenValueBoth(double aWidenValue)
{
    setWidenValue(aWidenValue);
    setWidenValue((float)aWidenValue);
}

void AmbisonicsWider::setWidenValue(double aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0., 1.);
    m_weight_double = (1. - m_widen_value) * m_order_weight_double + 1.;
    double scale = m_widen_value * m_order_weight_double;
    double zero = 0.;
    double one  = 1.;
    
    Cicm_Vector_Scalar_Double_Sum(m_minus_vector_double+1, &scale, m_harmonics_double, m_number_of_harmonics-1);
    Cicm_Vector_Vector_Double_Mul(m_dot_vector_double+1, m_harmonics_double, m_harmonics_double, m_number_of_harmonics-1);
    Cicm_Vector_Double_Clip(m_harmonics_double, &zero, &one, m_harmonics_double, m_number_of_harmonics-1);
}

void AmbisonicsWider::setWidenValue(float aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0.f, 1.f);
    m_weight_float = (1. - m_widen_value) * m_order_weight_float + 1.;
    float scale = m_widen_value * m_order_weight_float;
    float zero = 0.f;
    float one  = 1.f;
    
    Cicm_Vector_Scalar_Float_Sum(m_minus_vector_float+1, &scale, m_harmonics_float, m_number_of_harmonics-1);
    Cicm_Vector_Vector_Float_Mul(m_dot_vector_float+1, m_harmonics_float, m_harmonics_float, m_number_of_harmonics-1);
    Cicm_Vector_Float_Clip(m_harmonics_float, &zero, &one, m_harmonics_float, m_number_of_harmonics-1);
}

void AmbisonicsWider::setVectorSize(long aVectorSize)
{
    Cicm_Free(m_scale_vector_float);
    Cicm_Free(m_weight_vector_float);
    Cicm_Free(m_scale_vector_double);
    Cicm_Free(m_weight_vector_double);
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    Cicm_Vector_Float_Malloc(m_scale_vector_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_weight_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_scale_vector_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_weight_vector_double, m_vector_size);
}

AmbisonicsWider::~AmbisonicsWider()
{
	Cicm_Free(m_scale_vector_float);
    Cicm_Free(m_weight_vector_float);
    Cicm_Free(m_scale_vector_double);
    Cicm_Free(m_weight_vector_double);
    Cicm_Free(m_minus_vector_float);
    Cicm_Free(m_dot_vector_float);
    Cicm_Free(m_harmonics_float);
    Cicm_Free(m_minus_vector_double);
    Cicm_Free(m_dot_vector_double);
    Cicm_Free(m_harmonics_double);
}

