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

#ifndef DEF_AMBISONICSGRAIN
#define DEF_AMBISONICSGRAIN

#include "../HoaAmbisonics/AmbisonicsDiffuser.h"

class AmbisonicsGrain : public AmbisonicsDiffuser
{
private:
    vector <CicmQsgs*> m_grain;
    
    double  m_maximum_delay_time;
    double  m_grain_size;
    double  m_delay_time;
    double  m_feedback;
    double  m_rarefaction;
    
public:
	AmbisonicsGrain(long anOrder = 1, bool aMode = Hoa_Post_Encoding, double aMaximumDelayInMs = 5000., long aVectorSize = 0,  long aSamplingRate = 44100);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    
    void setGrainSize(double aGrainSize);
    void setDelayTime(double aDelayTime);
    void setFeedback(double aFeedback);
    void setRarefaction(double aRarefaction);
    
    void setWindowFunction(long aEnvelopeType);
    void writeWidowFunction(double* aBuffer, long aSize);
    void writeWidowFunction(float* aBuffer, long aSize);
    
    double getGrainSize();
    double getDelayTime();
    double getFeedback();
    double getRarefaction();
    long   getWidowFunction();
    
    double getGrainSizeFromIndex(long anIndex);
    double getDelayTimeFromIndex(long anIndex);
    
	~AmbisonicsGrain();
	
    /****************************/
	/* Perform sample by sample */
    /****************************/

    inline void process(double aInputs, double* aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            aOutputs[i] = m_grain[i]->process(aInputs);
        }
	}
    
	inline void process(double* aInputs, double* aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            aOutputs[i] = m_grain[i]->process(aInputs[i]);
        }
	}
    
    inline void process(float aInputs, float* aOutputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
        {
            aOutputs[i] = m_grain[i]->process(aInputs);
        }
	}
    
    inline void process(float* aInputs, float* aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            aOutputs[i] = m_grain[i]->process(aInputs[i]);
        }
	}
    

    /************************/
	/* Perform block sample */
    /************************/
    
	inline void process(double* aInputs, double** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_grain[i]->process(aInputs, aOutputs[i]);
        }
	}
    
    inline void process(double** aInputs, double** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_grain[i]->process(aInputs[i], aOutputs[i]);
        }
	}
    
    inline void process(float* aInputs, float** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_grain[i]->process(aInputs, aOutputs[i]);
        }
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_grain[i]->process(aInputs[i], aOutputs[i]);
        }
	}

};



#endif


