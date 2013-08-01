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

#ifndef DEF_AMBISONICSDELAY
#define DEF_AMBISONICSDELAY

#include "../HoaAmbisonics/AmbisonicsDiffuser.h"

class AmbisonicsDelay : public AmbisonicsDiffuser
{
private:
    
    vector <CicmDecorrelation*> m_delay;
    vector <CicmLine*>          m_line;
    double                      m_delay_time;
    double                      m_maximum_delay;
    
public:
	AmbisonicsDelay(long anOrder = 1, bool aMode = Hoa_Post_Encoding, double aMaximumDelayInMs = 5000., long aVectorSize = 0,  long aSamplingRate = 44100);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    void setDiffuseFactor(double aDiffuseValue);
    void setDelayTimeInSample(long aDelayInSample);
    void setDelayTimeInMs(double aDelayInMs);
    void setRampInSample(long aRampInSample);
    void setRampInMs(double aRampInMs);
    
    long    getDelayTimeInSample();
    double  getDelayTimeInMs();
    long    getRampInSample();
    double  getRampInMs();
    
	~AmbisonicsDelay();
	
    /****************************/
	/* Perform sample by sample */
    /****************************/

    inline void process(double aInputs, double* aOutputs)
	{
        for(int i =0; i < m_number_of_harmonics; i++)
            aOutputs[i] = m_delay[i]->process(aInputs);
	}
    
	inline void process(double* aInputs, double* aOutputs)
	{
        if(m_encoding_compensation)
        {
            double gain;
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                gain = m_line[i]->process();
                aInputs[i] *= gain;
                aInputs[i] += (1. - gain) * aInputs[0];
  
                aOutputs[i] = m_delay[i]->process(aInputs[i]);
            }
        }
        else
        {
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                aOutputs[i] = m_delay[i]->process(aInputs[i]);
            }
        }
	}
    
    inline void process(float aInputs, float* aOutputs)
	{
		for(int i =0; i < m_number_of_harmonics; i++)
            aOutputs[i] = m_delay[i]->process(aInputs);
	}
    
    inline void process(float* aInputs, float* aOutputs)
	{
        if(m_encoding_compensation)
        {
            float gain;
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                gain = m_line[i]->process();
                aInputs[i] *= gain;
                aInputs[i] += (1. - gain) * aInputs[0];
                
                aOutputs[i] = m_delay[i]->process(aInputs[i]);
            }
        }
        else
        {
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                aOutputs[i] = m_delay[i]->process(aInputs[i]);
            }
        }            
	}
    

    /************************/
	/* Perform block sample */
    /************************/
    
	inline void process(double* aInputs, double** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_delay[i]->process(aInputs, aOutputs[i]);
	}
    
    inline void process(double** aInputs, double** aOutputs)
	{
        if(m_encoding_compensation)
        {
            double gain;
            double signal;
            double* input_zero;
            double* input;
            double* output;
            input_zero = aInputs[0];
            for(int i = 0; i < m_number_of_harmonics; i++)
            {
                input = aInputs[i];
                output= aOutputs[i];
                for(int j = 0; j < m_vector_size; j++)
                {
                    gain = m_line[i]->process();
                    signal = input[j] * gain;
                    signal += (1. - gain) * input_zero[j];
                    
                    output[j] = m_delay[i]->process(signal);
                }
            }
        }
        else
        {
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                m_delay[i]->process(aInputs[i], aOutputs[i]);
            }
        }
	}
    
    inline void process(float* aInputs, float** aOutputs)
	{
        for(int i =0; i < m_number_of_harmonics; i++)
            m_delay[i]->process(aInputs, aOutputs[i]);
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
        if(m_encoding_compensation)
        {
            float gain;
            float signal;
            float* input_zero;
            float* input;
            float* output;
            input_zero = aInputs[0];
            for(int i = 0; i < m_number_of_harmonics; i++)
            {
                input = aInputs[i];
                output= aOutputs[i];
                for(int j = 0; j < m_vector_size; j++)
                {
                    gain = m_line[i]->process();
                    signal = input[j] * gain;
                    signal += (1. - gain) * input_zero[j];
                    
                    output[j] = m_delay[i]->process(signal);
                }
            }
        }
        else
        {
            for(int i =0; i < m_number_of_harmonics; i++)
            {
                m_delay[i]->process(aInputs[i], aOutputs[i]);
            }
        }
	}

};



#endif


