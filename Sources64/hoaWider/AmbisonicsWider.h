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

#ifndef DEF_AMBISONISCWIDER
#define DEF_AMBISONISCWIDER

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsWider : public Ambisonics
{
private:
	double	m_widen_value;
    double	m_order_weight_double;
    float	m_order_weight_float;
    
    float   m_weight_float;
    double  m_weight_double;
    
	Cicm_Vector_Float	m_minus_vector_float;
    Cicm_Vector_Double	m_minus_vector_double;
    
	Cicm_Vector_Float	m_dot_vector_float;
	Cicm_Vector_Double	m_dot_vector_double;

    Cicm_Vector_Double	m_harmonics_double;
	Cicm_Vector_Float	m_harmonics_float;
    
    Cicm_Vector_Double	m_weight_vector_double;
	Cicm_Vector_Float	m_weight_vector_float;
    Cicm_Vector_Double	m_scale_vector_double;
	Cicm_Vector_Float	m_scale_vector_float;
    
	void computeIndex();
	void computeWidenVector();
public:
	AmbisonicsWider(long anOrder = 1, long aVectorSize = 0);
    
    void setWidenValueBoth(double aWidenValue);
	void setWidenValue(double aWidenValue);
    void setWidenValue(float aWidenValue);
	void setVectorSize(long aVectorSize);

	~AmbisonicsWider();
	
	/* Perform sample by sample */
	inline void process(double* aInputs, double* aOutputs)
	{
        /* All Harmonics */
        Cicm_Vector_Scalar_Double_Mul(aInputs, &m_weight_double, aOutputs, m_number_of_harmonics);
        /* Harmonics Exept Zero */
        Cicm_Matrix_Vector_Double_Mul(aOutputs+1, m_harmonics_double, aOutputs+1, m_number_of_harmonics-1);
	}
    
    inline void process(float* aInputs, float* aOutputs)
	{
		/* All Harmonics */
        Cicm_Vector_Scalar_Float_Mul(aInputs, &m_weight_float, aOutputs, m_number_of_harmonics);
        /* Harmonics Exept Zero */
        Cicm_Matrix_Vector_Float_Mul(aOutputs+1, m_harmonics_float, aOutputs+1, m_number_of_harmonics-1);
	}
    
    inline void process(double* ioVector)
	{
        /* All Harmonics */
        Cicm_Vector_Scalar_Double_Mul(ioVector, &m_weight_double, ioVector, m_number_of_harmonics);
        /* Harmonics Exept Zero */
        Cicm_Matrix_Vector_Double_Mul(ioVector+1, m_harmonics_double, ioVector+1, m_number_of_harmonics-1);
	}
    
	inline void process(double* aInputs, double* aOutputs, double aWidenValues)
	{
        setWidenValue(aWidenValues);
        process(aInputs, aOutputs);
	}
    
    inline void process(float* aInputs, float* aOutputs, float aWidenValues)
	{
		setWidenValue(aWidenValues);
		process(aInputs, aOutputs);
	}
    
    inline void process(double* ioVector, double aWidenValues)
	{
        setWidenValue(aWidenValues);
        process(ioVector);
	}

    /************************/
	/* Perform block sample */
    /************************/
	inline void process(double** aInputs, double** aOutputs)
	{
        Cicm_Vector_Scalar_Double_Mul(aInputs[0], &m_weight_double, aOutputs[0], m_vector_size);
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Scalar_Double_Mul(aInputs[i], &m_weight_double, aOutputs[i], m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(aOutputs[i], &m_harmonics_double[i-1], aOutputs[i], m_vector_size);
        }
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
        Cicm_Vector_Scalar_Float_Mul(aInputs[0], &m_weight_float, aOutputs[0], m_vector_size);
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Scalar_Float_Mul(aInputs[i], &m_weight_float, aOutputs[i], m_vector_size);
            Cicm_Vector_Scalar_Float_Mul(aOutputs[i], &m_harmonics_float[i-1], aOutputs[i], m_vector_size);
        }
	}

	inline void process(double** aInputs, double** aOutputs, double* aWidenValues)
	{
        double  zero = 0.;
        double  one  = 1.;
        Cicm_Vector_Double_Clip(aWidenValues, &zero, &one, aWidenValues, m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
             m_weight_vector_double[i] = (1. - aWidenValues[i]) * m_order_weight_double + 1.;
        Cicm_Vector_Scalar_Double_Mul(aWidenValues, &m_order_weight_double, m_scale_vector_double, m_vector_size);
        
        for(int i = 0; i < m_number_of_harmonics; i++)
            Cicm_Matrix_Vector_Double_Mul(aInputs[i], m_weight_vector_double, aOutputs[i], m_vector_size);
        
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Scalar_Double_Sum(m_scale_vector_double, &m_minus_vector_double[i], m_weight_vector_double, m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(m_weight_vector_double, &m_dot_vector_double[i], m_weight_vector_double, m_vector_size);
            Cicm_Vector_Double_Clip(m_weight_vector_double, &zero, &one, m_weight_vector_double, m_vector_size);
            Cicm_Matrix_Vector_Double_Mul(aOutputs[i], m_weight_vector_double, aOutputs[i], m_vector_size);
        }
        
        /* Save last widen value */
        m_widen_value = aWidenValues[m_vector_size - 1];
	}
    
    inline void process(float** aInputs, float** aOutputs, float* aWidenValues)
	{
        float  zero = 0.f;
        float  one  = 1.f;
        Cicm_Vector_Float_Clip(aWidenValues, &zero, &one, aWidenValues, m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
            m_weight_vector_float[i] = (1. - aWidenValues[i]) * m_order_weight_double + 1.;
        Cicm_Vector_Scalar_Float_Mul(aWidenValues, &m_order_weight_float, m_scale_vector_float, m_vector_size);
        
        for(int i = 0; i < m_number_of_harmonics; i++)
            Cicm_Matrix_Vector_Float_Mul(aInputs[i], m_weight_vector_float, aOutputs[i], m_vector_size);
        
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Scalar_Float_Sum(m_scale_vector_float, &m_minus_vector_float[i], m_weight_vector_float, m_vector_size);
            Cicm_Vector_Scalar_Float_Mul(m_weight_vector_float, &m_dot_vector_float[i], m_weight_vector_float, m_vector_size);
            Cicm_Vector_Float_Clip(m_weight_vector_float, &zero, &one, m_weight_vector_float, m_vector_size);
            Cicm_Matrix_Vector_Float_Mul(aOutputs[i], m_weight_vector_float, aOutputs[i], m_vector_size);
        }
        
        /* Save last widen value */
        m_widen_value = aWidenValues[m_vector_size - 1];
	}
};



#endif


