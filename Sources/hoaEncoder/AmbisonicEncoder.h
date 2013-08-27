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

#ifndef DEF_AmbisonicEncoder
#define DEF_AmbisonicEncoder

#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicEncoder : public Ambisonic
{
	
private:
	long m_mode;
	
	Cicm_Vector_Double*	m_encoder_matrix;
    
	Cicm_Vector_Float	m_harmonics_vector_float;
    Cicm_Vector_Double	m_harmonics_vector_double;
    
    int*				m_index_vector;
	Cicm_Vector_Float	m_vector_float;
    Cicm_Vector_Double	m_vector_double;
    
public:
	AmbisonicEncoder(long anOrder = 1, long aMode = Hoa_Basic, long aVectorSize = 0);

	long    getMode();
    
    void    setVectorSize(long aVectorSize);
	void	setAngle(double anAngle);
    
	~AmbisonicEncoder();
    
    /********************************************************************/
    /**************************** Basic Mode ****************************/
    /********************************************************************/
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double anInput, double* outputs)
	{
        Cicm_Vector_Scalar_Double_Mul(m_harmonics_vector_double, anInput, outputs, m_number_of_harmonics);
	}

    inline void process(const float anInput, float* outputs)
	{
        Cicm_Vector_Scalar_Float_Mul(m_harmonics_vector_float, anInput, outputs, m_number_of_harmonics);
	}
    
    inline void process(const double anInput, double* outputs, const double anAngle)
	{
		double angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
    
    inline void process(const float anInput, float* outputs, const float anAngle)
	{
        float angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
		
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        double input = ioVector[0];
        process(input, ioVector);
	}
    
    inline void process(float* ioVector)
	{
        float input = ioVector[0];
        process(input, ioVector);
	}
    
    inline void process(double* ioVector, const double anAngle)
	{
		double input = ioVector[0];
        process(input, ioVector, anAngle);
	}
    
    inline void process(float* ioVector, const float anAngle)
	{
        float input = ioVector[0];
        process(input, ioVector, anAngle);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(inputs, m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void process(const float* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(inputs, m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}
    
	inline void process(const double* inputs, double** outputs, const double* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Double_Copy((double* )inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Vector_Double_Mul(inputs, m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* inputs, float** outputs, const float* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Float_Copy((float* )inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			Cicm_Vector_Vector_Float_Mul(inputs, m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(ioVectors[0], m_harmonics_vector_double[i], ioVectors[i], m_vector_size);
	}
    
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(ioVectors[0], m_harmonics_vector_float[i], ioVectors[i], m_vector_size);
	}
    
	inline void process(double** ioVectors, const double* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
            Cicm_Vector_Double_Copy(ioVectors[0], ioVectors[i], m_vector_size);
			Cicm_Vector_Double_Mul(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors, const float* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
            Cicm_Vector_Float_Copy(ioVectors[0], ioVectors[i], m_vector_size);
			Cicm_Vector_Float_Mul(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
    
    /********************************************************************/
    /**************************** Add Mode ******************************/
    /********************************************************************/
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processAdd(double anInput, double* outputs)
	{
        Cicm_Vector_Scalar_Double_Mul_And_Add(m_harmonics_vector_double, anInput, outputs, m_number_of_harmonics);
	}
    
    inline void processAdd(float anInput, float* outputs)
	{
        Cicm_Vector_Scalar_Float_Mul_And_Add(m_harmonics_vector_float, anInput, outputs, m_number_of_harmonics);
	}
    
    inline void processAdd(const double anInput, double* outputs, const double anAngle)
	{
		float angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
    
    inline void processAdd(const float anInput, float* outputs, const float anAngle)
	{
        double angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processAdd(double* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul_And_Add(inputs, m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void processAdd(float* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul_And_Add(inputs, m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}
    
	inline void processAdd(const double* inputs, double** outputs, const double* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Double_Add(inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Double_Mul(inputs, m_vector_double, m_vector_size);
            Cicm_Vector_Double_Add(m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void processAdd(const float* inputs, float** outputs, const float* angleValues)
	{
		int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Float_Add(inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			Cicm_Vector_Float_Mul(inputs, m_vector_float, m_vector_size);
            Cicm_Vector_Float_Add(m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /********************************************************************/
    /**************************** Add Mode ******************************/
    /********************************************************************/
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processSplit(double* inputs, double* outputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_harmonics_vector_double[i] * inputs[getHarmonicOrder(i)];
	}
    
    inline void processSplit(float* inputs, float* outputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_harmonics_vector_double[i] * inputs[getHarmonicOrder(i)];
	}
    
	inline void processSplit(double* inputs, double* outputs, double anAngle)
	{
		double angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		return processSplit(inputs, outputs);
	}
	
    inline void processSplit(float* inputs, float* outputs, float anAngle)
	{
		float angle = Tools::radianWrap(anAngle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_encoder_matrix[i][(int)(angle*(double)(NUMBEROFCIRCLEPOINTS-1))];
		return processSplit(inputs, outputs);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processSplit(const double* const* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Double_Mul(inputs[getHarmonicOrder(i)], m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void processSplit(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			Cicm_Vector_Scalar_Float_Mul(inputs[getHarmonicOrder(i)], m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}
    
    inline void processSplit(const double* const* inputs, double** outputs, const double* angleValues)
	{
        int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Double_Copy((double* )inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			Cicm_Vector_Vector_Double_Mul(inputs[getHarmonicOrder(i)], m_vector_double, outputs[i], m_vector_size);
		}
	}

    inline void processSplit(const float* const* inputs, float** outputs, const float* angleValues)
	{
        int index;
		Cicm_Vector_Double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::radianWrap(angleValues[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        Cicm_Vector_Float_Copy((float* )inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			Cicm_Vector_Vector_Float_Mul(inputs[getHarmonicOrder(i)], m_vector_float, outputs[i], m_vector_size);
		}
    }
	
};

#endif