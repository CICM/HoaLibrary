/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

/* OnePole LowPass Filter */

#ifndef DEF_AMBISONICONEPOLE
#define DEF_AMBISONICONEPOLE

#include "../cicmTools.h"

class AmbisonicOnePole{
	
private:
	long        m_vector_size;
    double      m_samplig_rate;
    double      m_coeff_b;
    double      m_coeff_a;
    double      m_cut_off_frequency;
    double      m_last_sample;
    
public:
	AmbisonicOnePole(double aSamplingRate = 44100, long aVectorSize = 0);

	void setVectorSize(long aVectorSize);
    void setSamplingRate(double aSamplingRate);
    void setCoeffA(double aCoefficient);
    void setCoeffB(double aCoefficient);
    void setCutOffFrequency(double aCoefficient);
    
    long    getVectorSize();
    double  getSamplingRate();
    double  getCoeffA();
    double  getCoeffB();
    double  getCutOffFrequency();
    
	~AmbisonicOnePole();
	
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