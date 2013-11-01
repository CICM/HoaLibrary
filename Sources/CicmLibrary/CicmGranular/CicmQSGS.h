/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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
	CicmQsgs(double aMaximumDelay = 5000., long aVectorSize = 1, long aSamplingRate = 44100);
    
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
    double getMaximumSizeInMs();
    long   getMaximumSizeInSample();
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
        
        if(ramp >= 1.f)
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


