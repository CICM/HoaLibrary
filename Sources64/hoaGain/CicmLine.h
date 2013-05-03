/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef DEF_CicmLine_h
#define DEF_CicmLine_h

#include "../CicmLibrary/CicmTools.h"
#define DEF_RAMPSIZE_IN_MS 20 // 882 samples at 44.1k samplerate

class CicmLine{
	
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
	CicmLine(long aVectorSize = 512, double aSampleRate = 44100, double _rampSizeInMs = DEF_RAMPSIZE_IN_MS);
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
	~CicmLine();
	
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