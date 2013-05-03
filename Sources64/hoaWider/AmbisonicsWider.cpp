/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "AmbisonicsWider.h"

AmbisonicsWider::AmbisonicsWider(long anOrder, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_number_of_inputs = m_number_of_harmonics + 1;
    Cicm_Vector_Float_Malloc(m_scale_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_weight_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_scale_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_weight_vector_double, m_vector_size);
	computeWidenVector();
	setWidenValue(1.);
}

void AmbisonicsWider::computeWidenVector()
{
    Cicm_Vector_Float_Malloc(m_minus_vector_float, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_dot_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_minus_vector_double, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_dot_vector_double, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_harmonics_float, m_number_of_harmonics - 1);
    Cicm_Vector_Double_Malloc(m_harmonics_double, m_number_of_harmonics - 1);
    
	m_order_weight_double = log((double)(m_order + 1));
    m_order_weight_float = m_order_weight_double;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_minus_vector_double[i] = Tools::clip_min(log((double)abs(getHarmonicIndex(i))), 0.);
        m_minus_vector_double[i] =-m_minus_vector_double[i];
        m_minus_vector_float[i] = m_minus_vector_double[i];
        
		m_dot_vector_double[i]	= Tools::clip_min(log((double)abs(getHarmonicIndex(i)) + 1.), 0.);
		m_dot_vector_double[i] += m_minus_vector_double[i];
		m_dot_vector_double[i] = 1. / m_dot_vector_double[i];
        m_dot_vector_float[i] = m_dot_vector_double[i];
	}
}

void AmbisonicsWider::setWidenValue(double aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0., 1.);
    m_weight_double = (1. - m_widen_value) * m_order_weight_double + 1.;
    double scale = m_widen_value * m_order_weight_double;
    double  zero = 0.;
    double  one  = 1.;
    
    Cicm_Vector_Scalar_Double_Sum(m_minus_vector_double, &scale, m_harmonics_double, m_number_of_harmonics - 1);
    Cicm_Matrix_Vector_Double_Mul(m_dot_vector_double, m_harmonics_double, m_harmonics_double, m_number_of_harmonics - 1);
    Cicm_Vector_Double_Clip(m_harmonics_double, &zero, &one, m_harmonics_double, m_number_of_harmonics - 1);
}

void AmbisonicsWider::setWidenValue(float aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0.f, 1.f);
    m_weight_float = (1. - m_widen_value) * m_order_weight_float + 1.;
    float scale = m_widen_value * m_order_weight_float;
    float  zero = 0.f;
    float  one  = 1.f;
    
    Cicm_Vector_Scalar_Float_Sum(m_minus_vector_float, &scale, m_harmonics_float, m_number_of_harmonics - 1);
    Cicm_Matrix_Vector_Float_Mul(m_dot_vector_float, m_harmonics_float, m_harmonics_float, m_number_of_harmonics - 1);
    Cicm_Vector_Float_Clip(m_harmonics_float, &zero, &one, m_harmonics_float, m_number_of_harmonics - 1);
}

void AmbisonicsWider::setVectorSize(long aVectorSize)
{
    Cicm_Free(m_scale_float);
    Cicm_Free(m_weight_vector_float);
    Cicm_Free(m_scale_double);
    Cicm_Free(m_weight_vector_double);
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    Cicm_Vector_Float_Malloc(m_scale_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_weight_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_scale_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_weight_vector_double, m_vector_size);
}

void AmbisonicsWider::setWidenValueBoth(double aWidenValue)
{
    setWidenValue(aWidenValue);
    setWidenValue((float)aWidenValue);
}

AmbisonicsWider::~AmbisonicsWider()
{
	Cicm_Free(m_scale_float);
    Cicm_Free(m_weight_vector_float);
    Cicm_Free(m_scale_double);
    Cicm_Free(m_weight_vector_double);
    Cicm_Free(m_minus_vector_float);
    Cicm_Free(m_dot_vector_float);
    Cicm_Free(m_harmonics_float);
    Cicm_Free(m_minus_vector_double);
    Cicm_Free(m_dot_vector_double);
    Cicm_Free(m_harmonics_double);
}

