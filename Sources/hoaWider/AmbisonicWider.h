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

#define MAX_WIDER_SIZE 10000

class AmbisonicWider : public Ambisonics
{
private:
    Cicm_Vector_Double*	m_wider_matrix;

	Cicm_Vector_Float	m_harmonics_vector_float;
    Cicm_Vector_Double	m_harmonics_vector_double;
    
    int*				m_index_vector;
	Cicm_Vector_Float	m_vector_float;
    Cicm_Vector_Double	m_vector_double;
    
	void computeWidenVector();
public:
	AmbisonicWider(long anOrder = 1, long aVectorSize = 0);
    
	void setWidenValue(double aWidenValue);
	void setVectorSize(long aVectorSize);
	~AmbisonicWider();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
		Cicm_Vector_Vector_Double_Mul(inputs, m_harmonics_vector_double, outputs, m_number_of_harmonics);
	}
    
    inline void process(float* inputs, float* outputs)
	{
		Cicm_Vector_Vector_Float_Mul(inputs, m_harmonics_vector_float, outputs, m_number_of_harmonics);
	}
    
	inline void process(double* inputs, double* outputs, const double aWidenValue)
	{
        double widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(MAX_WIDER_SIZE-1))];
        process(inputs, outputs);
	}
    
    inline void process(float* inputs, float* outputs, const float aWidenValue)
	{
        float widenValue = Tools::clip(aWidenValue, 0., 1.);
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(MAX_WIDER_SIZE-1))];
		process(inputs, outputs);
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        Cicm_Vector_Double_Mul(m_harmonics_vector_double, ioVector, m_number_of_harmonics);
	}
    
    inline void process(float* ioVector)
	{
        Cicm_Vector_Float_Mul(m_harmonics_vector_float, ioVector, m_number_of_harmonics);
	}
    
    inline void process(double* ioVector, double aWidenValue)
	{
        double widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
           m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(MAX_WIDER_SIZE-1))];
        process(ioVector);
	}

	inline void process(float* ioVector, float aWidenValue)
	{
        float widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(MAX_WIDER_SIZE-1))];
        process(ioVector);
	}

    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* const* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(inputs[i], m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(inputs[i], m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}

	inline void process(const double* const* inputs, double** outputs, const double* widenValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(MAX_WIDER_SIZE-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Vector_Double_Mul(inputs[i], m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* const* inputs, float** outputs, const float* widenValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(MAX_WIDER_SIZE-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			Cicm_Vector_Vector_Float_Mul(inputs[i], m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(ioVectors[i], m_harmonics_vector_double[i], ioVectors[i], m_vector_size);
	}
    
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(ioVectors[i], m_harmonics_vector_float[i], ioVectors[i], m_vector_size);
	}
    
	inline void process(double** ioVectors, const double* widenValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(MAX_WIDER_SIZE-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Double_Mul(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors, const float* widenValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(MAX_WIDER_SIZE-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			Cicm_Vector_Float_Mul(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
};



#endif


