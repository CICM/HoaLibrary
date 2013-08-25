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

#ifndef DEF_AMBISONICSPACE
#define DEF_AMBISONICSPACE

#include "../HoaAmbisonics/Planewaves.h"

#define RAMP_SAMPLE 4410

class AmbisonicSpace : public Planewaves
{
private:
    vector <CicmLine*>   m_lines;
    Cicm_Vector_Float	m_vector_float;
    Cicm_Vector_Double	m_vector_double;
    
public:
	AmbisonicSpace(long aNumberOfLoudspeakers, long aVectorSize = 0, long aSamplingRate = 44100);
	
    double  getCoefficient(long anIndex);
    long    getRampInSample();
    double  getRampInMs();

    void setCoefficient(long anIndex, double aCoefficient);
    void setCoefficient(double* aCoefficientVector);
    void setCoefficient(float* aCoefficientVector);
    void setRampInSample(long aTimeInSample);
    void setRampInMs(double aTimeInMs);
	void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 0);
    
	~AmbisonicSpace();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
		for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            outputs[i] = m_lines[i]->process() * inputs[i];
		}
	}
    
    inline void process(const float* inputs, float* outputs)
	{
		for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            outputs[i] = m_lines[i]->process() * inputs[i];
		}
	}
	
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            ioVector[i] *= m_lines[i]->process();
		}
	}
    
    inline void process(float* ioVector)
	{
        for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            ioVector[i] *= m_lines[i]->process();
		}
	}
    
	/************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* const* inputs, double** outputs)
	{
		for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            m_lines[i]->process(m_vector_double);
            Cicm_Vector_Vector_Double_Mul(inputs[i], m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            m_lines[i]->process(m_vector_float);
            Cicm_Vector_Vector_Float_Mul(inputs[i], m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
	{
		for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            m_lines[i]->process(m_vector_double);
            Cicm_Vector_Double_Mul(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors)
	{
        for (int i = 0; i < m_number_of_loudspeakers; i++)
		{
            m_lines[i]->process(m_vector_float);
            Cicm_Vector_Float_Mul(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
	
};

#endif