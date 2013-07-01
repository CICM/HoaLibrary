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

AmbisonicsSpectrum::AmbisonicsSpectrum(long aNumberOfLoudspeakers, long aWindowSize, long aVectorSize, long aSamplingRate) : Planewaves(aNumberOfLoudspeakers, aVectorSize, aSamplingRate)
{
    m_vector = new AmbisonicsVector(aNumberOfLoudspeakers, m_vector_size, m_sampling_rate);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_low.push_back(new FilterBiquad(Cicm_Biquad_Lowpass, m_vector_size, m_sampling_rate));
        m_low[i]->setCutoffFrequency(200.);
        m_low_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_low_medium[i]->setCutoffFrequency(300.);
        m_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_medium[i]->setCutoffFrequency(600.);
        m_high_medium.push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
        m_high_medium[i]->setCutoffFrequency(2400.);
        m_high.push_back(new FilterBiquad(Cicm_Biquad_Highpass, m_vector_size, m_sampling_rate));
        m_high[i]->setCutoffFrequency(4000.);
    }
  
}

AmbisonicsSpectrum::~AmbisonicsSpectrum()
{
    delete m_vector;
}

