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
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
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

/* OnePole LowPass Filter */

#ifndef DEF_AMBISONICONEPOLE
#define DEF_AMBISONICONEPOLE

#include "../CicmTools.h"

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