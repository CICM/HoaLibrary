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

#ifndef DEF_CICM_QSGS
#define DEF_CICM_QSGS

/****************************************/
/* QUASI SYNCHRONOUS GRANULAR SYNTHESIS */
/****************************************/

#include "../CicmFilters/CicmFilterDelay.h"
#include "../CicmEnvelope/CicmEnvelope.h"
#include "../CicmLines/CicmLine.h"

class CicmQsgs
{
protected:
    CicmFilterDelay*    m_delay;
    CicmLine*           m_line;
    CicmEnvelope*       m_envelope;
    
    double  m_grain_size;
    double  m_delay_time;
    double  m_feedback;
    double  m_rarefaction;
    
    double  m_delay_rand;
    double  m_bypass;
    double  m_feedback_real;
    
    double  m_buffer;
    long	m_vector_size;
    long	m_sampling_rate;

public:
	CicmQsgs(double aMaximumDelay = 5000., long aVectorSize = 1, double aSamplingRate = 44100.);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    
    void setGrainSize(double aGrainSize);
    void setDelayTime(double aDelayTime);
    void setFeedback(double aFeedback);
    void setRarefaction(double aRarefaction);
    
    void setWindowFunction(long aEnvelopeType);
    void writeWidowFunction(double* aBuffer, long aSize);
    void writeWidowFunction(float* aBuffer, long aSize);
    
	long getVectorSize();
	long getSamplingRate();
    
    double getGrainSize();
    double getDelayTime();
    double getFeedback();
    double getRarefaction();
    
    long   getWidowFunction();
	
	~CicmQsgs();
    
	/**********************************/
	/**** Perform sample by sample ****/
    /**********************************/
    
	inline float process(float input)
	{
        float output;
        float ramp = m_line->process();
        float gain = m_envelope->getValueRelative(ramp);
        
        m_delay->write(input + m_buffer * m_feedback_real);
        
        if(ramp >= 1.)
        {
            m_line->setCoefficientDirect(0.f);
            m_line->setCoefficient(1.f);
            m_delay_rand = Tools::getRandf(1.f, m_delay_time);
            if(Tools::getRandf(0.f, 1.f) > m_rarefaction)
                m_bypass = 1;
            else
                m_bypass = 0;
            
            m_feedback_real = m_feedback;
        }
        gain *= m_bypass;
		
        m_buffer = m_delay->read_no_ms(m_delay_rand) * gain;
        output = input * 0.02 * gain + m_buffer;
        return output;
	}
    
	inline double process(double input)
	{
		double output;
        double ramp = m_line->process();
        double gain = m_envelope->getValueRelative(ramp);
        
        if(ramp >= 1.)
        {
            m_line->setRampInMs(m_grain_size);
            m_line->setCoefficientDirect(0.f);
            m_line->setCoefficient(1.f);
            m_delay_rand = Tools::getRandf(1.f, m_delay_time);
            if(Tools::getRandf(0.f, 1.f) > m_rarefaction)
                m_bypass = 1;
            else
                m_bypass = 0;
            
            m_feedback_real = m_feedback;
        }
        
        m_delay->write(input + m_buffer * m_feedback_real);
        gain *= m_bypass;
        m_buffer = m_delay->read_no_ms(m_delay_rand) * gain;
        output = input * 0.02 * gain + m_buffer;
        return output;
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


