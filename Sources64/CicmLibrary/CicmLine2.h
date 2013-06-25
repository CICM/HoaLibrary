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

#ifndef DEF_CicmLine2_h
#define DEF_CicmLine2_h

#include "../CicmLibrary/CicmTools.h"
#define DEF_RAMPSIZE_IN_MS 20 // 882 samples at 44.1k samplerate

class CicmLine2{
	
private:
    double      m_sampling_rate;
	long        m_vector_size;
    double      m_ramptime_in_ms;
    long        m_ramptime_in_samps;
    double      m_value_old;
	double      m_value_new;
    double      m_value_step;
    long        m_counter;
    int         m_mode; /* samps=0 | ms=1 */
    
    void setValueStep();
    
public:
	CicmLine2(long aVectorSize = 512, double aSampleRate = 44100, double _rampSizeInMs = DEF_RAMPSIZE_IN_MS);
	inline double getValue()               {return m_value_new;}
    inline double getSampleRate()          {return m_sampling_rate;}
    inline long   getVectorSize()          {return m_vector_size;}
    inline long   getRampTimeInSamps()     {return m_ramptime_in_samps;}
    inline double getRampTimeInMs()        {return m_ramptime_in_ms;}

    void setCoefficientDirect(double aCoefficient);
    void setCoefficient(double aCoefficient);
    void setSampleRate(double aSampleRate);
	void setVectorSize(long aVectorSize);
    void setRampTimeInMs(double _rampTimeInMs);
    void setRampTimeInSamps(long _rampTimeInSamps);
	~CicmLine2();
	
	/* Perform sample by sample */
	inline double process()
	{
        m_value_old += m_value_step;
        if(m_counter++ >= m_ramptime_in_samps)
        {
            m_value_step = 0.;
            m_value_old  = m_value_new;
            m_counter    = 0;
        }
        return m_value_old;
	}
	
	/* Perform sample block */	
	inline void process(double* anOutputVector)
	{
		for(int i = 0; i < m_vector_size; i++)
        {
            m_value_old     += m_value_step;
            if(m_counter++ >= m_ramptime_in_samps)
            {
                m_value_step = 0.;
                m_value_old  = m_value_new;
                m_counter    = 0;
            }
            anOutputVector[i] = m_value_old;
		}
    }
    
    /* Perform sample block */
	inline void process(float* anOutputVector)
	{
		for(int i = 0; i < m_vector_size; i++)
        {
            m_value_old     += m_value_step;
            if(m_counter++ >= m_ramptime_in_samps)
            {
                m_value_step = 0.;
                m_value_old  = m_value_new;
                m_counter    = 0;
            }
            anOutputVector[i] = m_value_old;
		}        
	}
	
};

#endif