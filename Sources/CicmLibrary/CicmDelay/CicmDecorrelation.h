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


