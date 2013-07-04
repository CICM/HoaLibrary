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

#include "AmbisonicsSpectrum.h"

AmbisonicsSpectrum::AmbisonicsSpectrum(long aNumberOfLoudspeakers, long aNumberOfBands, long aVectorSize, long aSamplingRate)
: Planewaves(aNumberOfLoudspeakers, aVectorSize, aSamplingRate)
{
    m_vector = new AmbisonicsVector(m_number_of_loudspeakers, m_vector_size, m_sampling_rate);
    m_number_of_bands = 0;
    
    m_low_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_low_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_high_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_high_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    
    m_low_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_low_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_high_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_high_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    
    m_filtered_matrix_double[0] = m_low_vector_double;
    m_filtered_matrix_double[1] = m_low_medium_vector_double;
    m_filtered_matrix_double[2] = m_medium_vector_double;
    m_filtered_matrix_double[3] = m_high_medium_vector_double;
    m_filtered_matrix_double[4] = m_high_vector_double;
    
    m_filtered_matrix_float[0] = m_low_vector_float;
    m_filtered_matrix_float[1] = m_low_medium_vector_float;
    m_filtered_matrix_float[2] = m_medium_vector_float;
    m_filtered_matrix_float[3] = m_high_medium_vector_float;
    m_filtered_matrix_float[4] = m_high_vector_float;
    
    for(int i = 0; i < 5; i++)
    {
        Cicm_Vector_Double_Malloc(m_filtered_vector[i], m_number_of_loudspeakers);
    }
    
    m_frequency_band[0] = 200.;
    m_frequency_band[1] = 300.;
    m_frequency_band[2] = 600.;
    m_frequency_band[3] = 2400.;
    m_frequency_band[4] = 4000.;
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_low.push_back(new FilterBiquad(Cicm_Biquad_Lowpass, m_vector_size, m_sampling_rate));
        m_low[i]->setQValue(1.);
        m_low_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_low_medium[i]->setQValue(1.);
        m_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_medium[i]->setQValue(1.);
        m_high_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_high_medium[i]->setQValue(1.);
        m_high.push_back(new FilterBiquad(Cicm_Biquad_Highpass, m_vector_size, m_sampling_rate));
        m_high[i]->setQValue(1.);
        
        Cicm_Vector_Double_Malloc(m_low_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_low_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_vector_double[i], m_vector_size);
        
        Cicm_Vector_Float_Malloc(m_low_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_low_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_vector_float[i], m_vector_size);
    }
    setSamplingRate(m_sampling_rate);
    setTickTime(m_vector_size);
    setNumberOfBands(aNumberOfBands);
    
}

double AmbisonicsSpectrum::getAmplitude(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)4);
    return m_amplitudes[aBandIndex];
}

double AmbisonicsSpectrum::getAbscissa(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)4);
    return m_abscissa[aBandIndex];
}

double AmbisonicsSpectrum::getOrdinate(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)4);
    return m_ordinates[aBandIndex];
}

void AmbisonicsSpectrum::setVectorSize(long aVectorSize)
{
    Planewaves::setVectorSize(aVectorSize);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_low[i]->setVectorSize(m_vector_size);
        m_low_medium[i]->setVectorSize(m_vector_size);
        m_medium[i]->setVectorSize(m_vector_size);
        m_high_medium[i]->setVectorSize(m_vector_size);
        m_high[i]->setVectorSize(m_vector_size);
        
        Cicm_Free(m_low_vector_double[i]);
        Cicm_Free(m_low_medium_vector_double[i]);
        Cicm_Free(m_medium_vector_double[i]);
        Cicm_Free(m_high_medium_vector_double[i]);
        Cicm_Free(m_high_vector_double[i]);
        
        Cicm_Vector_Double_Malloc(m_low_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_low_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_vector_double[i], m_vector_size);
        
        Cicm_Free(m_low_vector_float[i]);
        Cicm_Free(m_low_medium_vector_float[i]);
        Cicm_Free(m_medium_vector_float[i]);
        Cicm_Free(m_high_medium_vector_float[i]);
        Cicm_Free(m_high_vector_float[i]);
        
        Cicm_Vector_Float_Malloc(m_low_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_low_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_vector_float[i], m_vector_size);
    }
   
	
}

void AmbisonicsSpectrum::setSamplingRate(long aSamplingRate)
{
	Planewaves::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_low[i]->setSamplingRate(m_sampling_rate);
        m_low[i]->setCutoffFrequency(m_frequency_band[0]);
        m_low_medium[i]->setSamplingRate(m_sampling_rate);
        m_low_medium[i]->setCutoffFrequency(m_frequency_band[1]);
        m_medium[i]->setSamplingRate(m_sampling_rate);
        m_medium[i]->setCutoffFrequency(m_frequency_band[2]);
        m_high_medium[i]->setSamplingRate(m_sampling_rate);
        m_high_medium[i]->setCutoffFrequency(m_frequency_band[3]);
        m_high[i]->setSamplingRate(m_sampling_rate);
        m_high[i]->setCutoffFrequency(m_frequency_band[4]);
    }
}

void AmbisonicsSpectrum::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff )
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        Cicm_Free(m_low_vector_double[i]);
        Cicm_Free(m_low_medium_vector_double[i]);
        Cicm_Free(m_medium_vector_double[i]);
        Cicm_Free(m_high_medium_vector_double[i]);
        Cicm_Free(m_high_vector_double[i]);
        Cicm_Free(m_low_vector_float[i]);
        Cicm_Free(m_low_medium_vector_float[i]);
        Cicm_Free(m_medium_vector_float[i]);
        Cicm_Free(m_high_medium_vector_float[i]);
        Cicm_Free(m_high_vector_float[i]);
    }
    Cicm_Free(m_low_vector_double);
    Cicm_Free(m_low_medium_vector_double);
    Cicm_Free(m_medium_vector_double);
    Cicm_Free(m_high_medium_vector_double);
    Cicm_Free(m_high_vector_double);
    Cicm_Free(m_low_vector_float);
    Cicm_Free(m_low_medium_vector_float);
    Cicm_Free(m_medium_vector_float);
    Cicm_Free(m_high_medium_vector_float);
    Cicm_Free(m_high_vector_float);
    
    m_low.clear();
    m_low_medium.clear();
    m_medium.clear();
    m_high_medium.clear();
    m_high.clear();
    
    for(int i = 0; i < 5; i++)
    {
        Cicm_Free(m_filtered_vector[i]);
    }
    
    Planewaves::setNumberOfLoudspeakers(aNumberOfLoudspeakers, standardOnOff);
    m_vector->setNumberOfLoudspeakers(aNumberOfLoudspeakers, standardOnOff);

    m_low_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_low_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_high_medium_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    m_high_vector_double = new Cicm_Vector_Double[m_number_of_loudspeakers];
    
    m_low_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_low_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_high_medium_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_high_vector_float = new Cicm_Vector_Float[m_number_of_loudspeakers];
    
    m_filtered_matrix_double[0] = m_low_vector_double;
    m_filtered_matrix_double[1] = m_low_medium_vector_double;
    m_filtered_matrix_double[2] = m_medium_vector_double;
    m_filtered_matrix_double[3] = m_high_medium_vector_double;
    m_filtered_matrix_double[4] = m_high_vector_double;
    
    m_filtered_matrix_float[0] = m_low_vector_float;
    m_filtered_matrix_float[1] = m_low_medium_vector_float;
    m_filtered_matrix_float[2] = m_medium_vector_float;
    m_filtered_matrix_float[3] = m_high_medium_vector_float;
    m_filtered_matrix_float[4] = m_high_vector_float;
    
    for(int i = 0; i < 5; i++)
    {
        Cicm_Vector_Double_Malloc(m_filtered_vector[i], m_number_of_loudspeakers);
    }
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_low.push_back(new FilterBiquad(Cicm_Biquad_Lowpass, m_vector_size, m_sampling_rate));
        m_low[i]->setQValue(1.);
        m_low_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_low_medium[i]->setQValue(1.);
        m_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_medium[i]->setQValue(1.);
        m_high_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_high_medium[i]->setQValue(1.);
        m_high.push_back(new FilterBiquad(Cicm_Biquad_Highpass, m_vector_size, m_sampling_rate));
        m_high[i]->setQValue(1.);
        
        Cicm_Vector_Double_Malloc(m_low_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_low_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_medium_vector_double[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_high_vector_double[i], m_vector_size);
        
        Cicm_Vector_Float_Malloc(m_low_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_low_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_medium_vector_float[i], m_vector_size);
        Cicm_Vector_Float_Malloc(m_high_vector_float[i], m_vector_size);
    }
    setSamplingRate(m_sampling_rate);
}

void AmbisonicsSpectrum::setLoudspeakerAngle(long anIndex, double anAngle)
{
    Planewaves::setLoudspeakerAngle(anIndex, anAngle);
    m_vector->setLoudspeakerAngle(anIndex, anAngle);
}

void AmbisonicsSpectrum::setFrequencyBandsLimit(long anIndex, double aFrequency)
{
    if (anIndex >= 0 && anIndex < 5)
    {
        m_frequency_band[anIndex] = Tools::clip(aFrequency, 20., (double)m_sampling_rate / 2.);
        Tools::sortVector(m_frequency_band, 5);
    }
    setSamplingRate(m_sampling_rate);
}

double AmbisonicsSpectrum::getFrequencyBandsLimit(long anIndex)
{
    if (anIndex >= 0 && anIndex < 5)
        return m_frequency_band[anIndex];
    else
        return NULL;
}

void AmbisonicsSpectrum::setTickTime(long aNumberOfSample)
{
    m_tick_time = Tools::clip_min(aNumberOfSample, (long)1);
}

long AmbisonicsSpectrum::getTickTime()
{
    return m_tick_time;
}

void AmbisonicsSpectrum::setNumberOfBands(long aNumberOfBands)
{
    if (aNumberOfBands != m_number_of_bands)
    {
        aNumberOfBands = Tools::clip_min(aNumberOfBands, (long)1);
        long currentNumberOfBandPass = m_band_pass.size();
        long newNunberOfBandPass = Tools::clip_min(aNumberOfBands - 2, (long)0);
        if(newNunberOfBandPass < currentNumberOfBandPass)
        {
            for(int i = newNunberOfBandPass; i < currentNumberOfBandPass; i++)
                m_band_pass.pop_back();
        }
        else if(newNunberOfBandPass > currentNumberOfBandPass)
        {
            for(int i = currentNumberOfBandPass; i < newNunberOfBandPass; i++)
            {
                m_band_pass.push_back(vector <FilterBiquad*>());
                for(int j = 0; j < m_number_of_loudspeakers; j++)
                {
                    m_band_pass[m_band_pass.size()-1].push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
                    m_high_medium[m_band_pass.size()-1]->setQValue(1.);
                }
            }
        }
        m_number_of_bands = aNumberOfBands;
        initializeFrequencyBands();
    }
}

void AmbisonicsSpectrum::initializeFrequencyBands()
{
    m_frequency_band[0] = 200.;
    m_frequency_band[1] = 300.;
    m_frequency_band[2] = 600.;
    m_frequency_band[3] = 2400.;
    m_frequency_band[4] = 4000.;
    
    if(m_number_of_bands == 2)
    {
        m_frequency_band[0] = 2400.;
        m_frequency_band[1] = 2400.;
    }
    else if(m_number_of_bands == 3)
    {
        m_frequency_band[0] = 2400.;
        m_frequency_band[1] = 2400.;
    }
}

AmbisonicsSpectrum::~AmbisonicsSpectrum()
{
    delete m_vector;
    m_low.clear();
    m_low_medium.clear();
    m_medium.clear();
    m_high_medium.clear();
    m_high.clear();
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        Cicm_Free(m_low_vector_double[i]);
        Cicm_Free(m_low_medium_vector_double[i]);
        Cicm_Free(m_medium_vector_double[i]);
        Cicm_Free(m_high_medium_vector_double[i]);
        Cicm_Free(m_high_vector_double[i]);
        Cicm_Free(m_low_vector_float[i]);
        Cicm_Free(m_low_medium_vector_float[i]);
        Cicm_Free(m_medium_vector_float[i]);
        Cicm_Free(m_high_medium_vector_float[i]);
        Cicm_Free(m_high_vector_float[i]);
    }
    Cicm_Free(m_low_vector_double);
    Cicm_Free(m_low_medium_vector_double);
    Cicm_Free(m_medium_vector_double);
    Cicm_Free(m_high_medium_vector_double);
    Cicm_Free(m_high_vector_double);
    Cicm_Free(m_low_vector_float);
    Cicm_Free(m_low_medium_vector_float);
    Cicm_Free(m_medium_vector_float);
    Cicm_Free(m_high_medium_vector_float);
    Cicm_Free(m_high_vector_float);
    
    for(int i = 0; i < 5; i++)
    {
        Cicm_Free(m_filtered_vector[i]);
    }
}

