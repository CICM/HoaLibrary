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

#ifndef DEF_CICMLINE
#define DEF_CICMLINE

#include "CicmTools.h"

class CicmLine{
	
private:
	long        m_vector_size;
    
    double      m_value_old;
	double      m_value_new;
    double      m_value_step;
    long        m_counter;
    long        m_ramp;
    
public:
    CicmLine(long aRamp = 4410, long aVectorSize = 0);
    
    double  getVectorSize();
    long    getRamp();
    double  getCoefficient();
    
    void setVectorSize(long aVectorSize);
    void setRamp(long aNumberOfSample);
    void setCoefficientDirect(double aCoefficient);
    void setCoefficient(double aCoefficient);
    void setCoefficientAngleDirect(double anAngle);
    void setCoefficientAngle(double anAngle);
    
	~CicmLine();
	
	/* Perform sample by sample */
	inline double process()
	{
        m_value_old += m_value_step;
        if(m_counter++ >= m_ramp)
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
            if(m_counter++ >= m_ramp)
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
            if(m_counter++ >= m_ramp)
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