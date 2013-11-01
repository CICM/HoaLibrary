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

#ifndef DEF_CICMLINE
#define DEF_CICMLINE

#include "../CicmDefine.h"

class CicmLine{
	
private:
	long        m_vector_size;
    long        m_sampling_rate;
    
    double      m_value_old;
	double      m_value_new;
    double      m_value_step;
    long        m_counter;
    long        m_ramp;
    
public:
    CicmLine(long aTimeInSample = 4410, long aVectorSize = 0, long aSamplingRate = 44100);
    CicmLine(double aTimeInMs = 100., long aVectorSize = 0, long aSamplingRate = 44100);
    
    long    getVectorSize();
    long    getSamplingRate();
    long    getRampInSample();
    double  getRampInMs();
    double  getCoefficient();
    
    void setSamplingRate(long aSamplingRate);
    void setVectorSize(long aVectorSize);
    
    void setRampInSample(long aTimeInSample);
    void setRampInMs(double aTimeInMs);
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