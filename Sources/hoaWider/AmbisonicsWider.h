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

#define MAX_WIDER_SIZE 100000

class AmbisonicsWider : public Ambisonics
{
private:
	double	m_widen_value;
    Cicm_Vector_Double*	m_wider_matrix;

	Cicm_Vector_Float	m_harmonics_vector_float;
    Cicm_Vector_Double	m_harmonics_vector_double;
    int*				m_index_vector;
	Cicm_Vector_Float	m_vector_float;
    Cicm_Vector_Double	m_vector_double;
	void computeWidenVector();
public:
	AmbisonicsWider(long anOrder = 1, long aVectorSize = 0);
    
	void setWidenValue(double aWidenValue);
	void setVectorSize(long aVectorSize);
	~AmbisonicsWider();
	
	/* Perform sample by sample */
	inline void process(double* aInputs, double* aOutputs)
	{
		;
	}
    
    inline void process(float* aInputs, float* aOutputs)
	{
		;
	}
    
    inline void process(double* ioVector)
	{
       ;
	}

	 inline void process(float* ioVector)
	{
       ;
	}
    
	inline void process(double* aInputs, double* aOutputs, double aWidenValues)
	{
        ;
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

	inline void process(float* ioVector, float aWidenValues)
	{
        setWidenValue(aWidenValues);
        process(ioVector);
	}

    /************************/
	/* Perform block sample */
    /************************/
	inline void process(const double* const* aInputs, double** aOutputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(aInputs[i], m_harmonics_vector_double[i], aOutputs[i], m_vector_size);
	}
    
    inline void process(const float* const* aInputs, float** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(aInputs[i], m_harmonics_vector_float[i], aOutputs[i], m_vector_size);
	}

	inline void process(const double* const* aInputs, double** aOutputs, const double* aWidenValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(aWidenValues[i], 0., 1.) * (double)(MAX_WIDER_SIZE-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Vector_Double_Mul(aInputs[i], m_vector_double, aOutputs[i], m_vector_size);
		}
	}
    
    inline void process(float** aInputs, float** aOutputs, float* aWidenValues)
	{
		;
	}
};



#endif


