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

#ifndef DEF_AMBISONICLINE
#define DEF_AMBISONICLINE

#include "../CicmLibrary/CicmTools.h"
#define RAMP_SAMPLE 4410

class AmbisonicLine{
	
private:
	long        m_vector_size;
    
    long double      m_value_old;
	long double      m_value_new;
    long double      m_value_step;
    long        m_counter;
public:
	AmbisonicLine(long aVectorSize = 0);
	double  getValue();
    double  getVectorSize();

    void setCoefficientDirect(double aCoefficient);
    void setCoefficient(double aCoefficient);
	void setVectorSize(long aVectorSize);
	~AmbisonicLine();
	
	/* Perform sample by sample */
	inline double process()
	{
        m_value_old += m_value_step;
        if(m_counter++ >= RAMP_SAMPLE)
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
            if(m_counter++ >= RAMP_SAMPLE)
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
            if(m_counter++ >= RAMP_SAMPLE)
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