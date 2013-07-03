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

#ifndef DEF_AMBISONICSSPECTRUM
#define DEF_AMBISONICSSPECTRUM

#include "../hoaAmbisonics/Planewaves.h"
#include "../hoaVector/AmbisonicsVector.h"
#include "../CicmLibrary/CicmFilters/CicmFilterBiquad.h"

class AmbisonicsSpectrum : public Planewaves
{
	
private:
    AmbisonicsVector*                   m_vector;
    long                                m_tick_time;
    long                                m_number_of_bands;
    
    vector <FilterBiquad*>              m_low_pass;
    vector <FilterBiquad*>              m_high_pass;
    vector <vector <FilterBiquad*> >    m_band_pass;
    
    vector <FilterBiquad*>         m_low;
    vector <FilterBiquad*>         m_low_medium;
    vector <FilterBiquad*>         m_medium;
    vector <FilterBiquad*>         m_high_medium;
    vector <FilterBiquad*>         m_high;
    
    Cicm_Vector_Float*              m_low_vector_float;
    Cicm_Vector_Float*              m_low_medium_vector_float;
    Cicm_Vector_Float*              m_medium_vector_float;
    Cicm_Vector_Float*              m_high_medium_vector_float;
    Cicm_Vector_Float*              m_high_vector_float;
    
    Cicm_Vector_Double*             m_low_vector_double;
    Cicm_Vector_Double*             m_low_medium_vector_double;
    Cicm_Vector_Double*             m_medium_vector_double;
    Cicm_Vector_Double*             m_high_medium_vector_double;
    Cicm_Vector_Double*             m_high_vector_double;
    
    Cicm_Vector_Double*             m_filtered_matrix_double[5];
    Cicm_Vector_Float*              m_filtered_matrix_float[5];
    
    Cicm_Vector_Double              m_filtered_vector[5];    
    Cicm_Double                     m_amplitudes[5];
    Cicm_Double                     m_abscissa[5];
    Cicm_Double                     m_ordinates[5];
    Cicm_Double                     m_vectors[4];
    Cicm_Double                     m_frequency_band[5];
    
    void initializeFrequencyBands();
    
public:
	AmbisonicsSpectrum(long aNumberOfLoudspeakers = 1, long aNumberOfBands = 5, long aVectorSize = 0, long aSamplingRate = 44100);
    
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 0);
    void setLoudspeakerAngle(long anIndex, double anAngle);
    void setFrequencyBandsLimit(long anIndex, double aFrequency);
    void setTickTime(long aNumberOfSample);
    void setNumberOfBands(long aNumberOfBands);
    
    double getAmplitude(long aBandIndex);
    double getAbscissa(long aBandIndex);
    double getOrdinate(long aBandIndex);
    double getFrequencyBandsLimit(long anIndex);
    long   getTickTime();
    long   getNumberOfBands();
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    
	~AmbisonicsSpectrum();
	
	/* Perform block sample */
	inline void process(float** inputs)
	{
        for(int h = 0; h < m_vector_size; h++)
        {
        }
	}
    
	inline void process(double** inputs)
	{
        /* Signal 5 Band Filtering */
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            m_low[i]->process(inputs[i], m_low_vector_double[i]);
            m_low_medium[i]->process(inputs[i], m_low_medium_vector_double[i]);
            m_medium[i]->process(inputs[i], m_medium_vector_double[i]);
            m_high_medium[i]->process(inputs[i], m_high_medium_vector_double[i]);
            m_high[i]->process(inputs[i], m_high_vector_double[i]);
        }
        
        for(int j = 0; j < 5; j++)
        {
            /* Peak Amplitude Computation */
            m_amplitudes[j] = 0.;
            for(int i = 0; i < m_vector_size; i++)
            {
                double amp = 0.;
                for(int k = 0; k < m_number_of_loudspeakers; k++)
                {
                    amp += fabs(m_filtered_matrix_double[j][k][i]);
                }
                amp /= (double)m_number_of_loudspeakers;
                if(amp > m_amplitudes[j])
                    m_amplitudes[j] = amp;
            }
            
            /* Energy Vector Computation */
            for(int k = 0; k < m_number_of_loudspeakers; k++)
            {
                m_filtered_vector[j][k] = m_filtered_matrix_double[j][k][m_vector_size-1];
            }
            m_vector->process(m_filtered_vector[j], m_vectors);
            m_abscissa[j] = m_vectors[2];
            m_ordinates[j] = m_vectors[3];
        }
	}
    
};

#endif