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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_CICM_DECORRELATION
#define DEF_CICM_DECORRELATION

/****************************************/
/*   VARIABLE DELAY WITHOUT FILTERING   */
/****************************************/

#include "../CicmFilters/CicmFilterDelay.h"
#include "../CicmEnvelope/CicmEnvelope.h"
#include "../CicmLines/CicmLine.h"

class CicmDecorrelation
{
protected:
    CicmFilterDelay*    m_delay;
    CicmLine*           m_line;
    CicmEnvelope*       m_envelope;
    double              m_value;
    double              m_maximum_delay;
    
    long    m_delay_time_one;
    long    m_delay_time_two;
    long    m_new_delay;
    
    long	m_vector_size;
    long	m_sampling_rate;
    bool    m_current_delay;
    double  m_max_gain;

public:
	CicmDecorrelation(double aMaximumDelay = 5000., long aVectorSize = 1, long aSamplingRate = 44100);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    void setDelayTimeInSample(long aDelayInSample);
    void setDelayTimeInMs(double aDelayInMs);
    void setRampInSample(long aRampInSample);
    void setRampInMs(double aRampInMs);
    
	long getVectorSize();
	long getSamplingRate();
    long getDelayTimeInSample();
    double getDelayTimeInMs();
    long getRampInSample();
    double getRampInMs();
	
	~CicmDecorrelation();
    
	/**********************************/
	/**** Perform sample by sample ****/
    /**********************************/
    
	inline float process(float input)
	{
        m_value = m_line->process();
        float gain = m_envelope->getValueRelative(m_value);
        
        if(m_value == 0.5)
        {
            m_delay_time_two = m_new_delay;
            m_line->setCoefficient(0.);
            m_current_delay = 1;
        }
        else if(m_value == 0.)
        {
            m_delay_time_one = m_new_delay;
            m_line->setCoefficient(0.5);
            m_current_delay = 0;
        }
        
        m_delay->write(input);
        
        return m_delay->read_no_sample(m_delay_time_one) * gain + m_delay->read_no_sample(m_delay_time_two) * (m_max_gain - gain);
	}
    
	inline double process(double input)
	{
		m_value = m_line->process();
        double gain = m_envelope->getValueRelative(m_value);
        
        if(m_value == 0.5)
        {
            m_delay_time_two = m_new_delay;
            m_line->setCoefficient(0.);
            m_current_delay = 1;
        }
        else if(m_value == 0.)
        {
            m_delay_time_one = m_new_delay;
            m_line->setCoefficient(0.5);
            m_current_delay = 0;
        }
        
        m_delay->write(input);
        return m_delay->read_no_sample(m_delay_time_one) * gain + m_delay->read_no_sample(m_delay_time_two) * (m_max_gain - gain);
	}
    
    /**********************************/
	/****** Perform block sample ******/
    /**********************************/
	
	inline void process(float* inputs, float* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = process(inputs[i]);
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = process(inputs[i]);
	}
};



#endif


