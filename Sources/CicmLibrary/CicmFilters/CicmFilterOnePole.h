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

/* OnePole LowPass Filter */

#ifndef DEF_FILTERONEPOLE
#define DEF_FILTERONEPOLE

#include "CicmFilter.h"

class FilterOnePole : public Filter
{
	
private:
    double      m_coeff_b;
    double      m_coeff_a;
    double      m_cut_off_frequency;
    double      m_last_sample;
    
public:
	FilterOnePole(double aSamplingRate = 44100, long aVectorSize = 0);

    void setSamplingRate(double aSamplingRate);
    void setCoeffA(double aCoefficient);
    void setCoeffB(double aCoefficient);
    void setCutOffFrequency(double aFrequency);
    
    double  getCoeffA();
    double  getCoeffB();
    double  getCutOffFrequency();
    
	~FilterOnePole();
	
	/* Perform sample by sample */
	inline double process(double aSample)
	{
        double result = aSample * m_coeff_b - m_last_sample * m_coeff_a;
        m_last_sample = aSample;
        return result;
    }
    
    inline float process(float aSample)
	{
        float result = aSample * m_coeff_b - m_last_sample * m_coeff_a;
        m_last_sample = aSample;
        return result;
    }
	
	/* Perform sample block */	
	inline void process(double* anInputVector, double* anOutputVector)
	{
        for(int i = 0; i < m_vector_size; i++)
            anOutputVector[i] = process(anInputVector[i]);
    }
    
    /* Perform sample block */
	inline void process(float* anInputVector, float* anOutputVector)
	{
        for(int i = 0; i < m_vector_size; i++)
            anOutputVector[i] = process(anInputVector[i]);
	}
	
};

#endif