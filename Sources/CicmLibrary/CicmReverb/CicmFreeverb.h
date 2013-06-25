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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_FREEVERB
#define DEF_FREEVERB


#include "CicmTuning.h"
#include "../CicmFilters/CicmFilterAllpass.h"
#include "../CicmFilters/CicmFilterComb.h"

class Freeverb
{
private:
    long    m_sampling_rate;
    long    m_vector_size;
    
	double	m_gain;
    double  m_wet;
    double  m_dry;
	double	roomsize, roomsize1;
	double	damp, damp1;
	double	mode;
    
    double  m_diffuse_spread;
    double  m_directional_spread;
    vector <FilterComb*>    m_comb_filter;
    vector <FilterAllpass*> m_allpass_filter;

	void	update();

public:
	Freeverb();

    void	setSamplingRate(long aSamplingRate);
	long	getSamplingRate();
    void	setVectorSize(long aVectorSize);
    long	getVectorSize();
    
    void	setDryValue(double value);
	double	getDryValue();
    void	setWetValue(double value);
	double	getWetValue();
	void	setroomsize(double value);
	double	getroomsize();
	void	setdamp(double value);
	double	getdamp();
	void	setmode(double value);
	double	getmode();
    void	setAllpassFeedback(double value);
	double	getAllpassFeedback();
    void	setSpread(double value);
    void	setDiffuseSpread(double value);
    void	setDirectionalSpread(double value);
	double	getDiffuseSpread();
    double  getDirectionalSpread();

	inline void	process(float *anInput, float *anOutput)
    {
        float input;
        for(int i = 0; i < m_vector_size; i++)
        {
            input = anInput[i];
            input *= m_gain;
            anOutput[i] = 0.;
            for(int j = 0; j < numcombs; j++)
                anOutput[i] += m_comb_filter[j]->process(input);
            
            for(int j = 0; j < numallpasses; j++)
                anOutput[i] = m_allpass_filter[j]->process(anOutput[i]);
            anOutput[i] *= m_wet;
            anOutput[i] += anInput[i] * m_dry;
        }
    };
    
    inline void	process(double *anInput, double *anOutput)
    {
        double input;
        for(int i = 0; i < m_vector_size; i++)
        {
            input = anInput[i];
            input *= m_gain;
            anOutput[i] = 0.;
            for(int j = 0; j < numcombs; j++)
                anOutput[i] += m_comb_filter[j]->process(input);
            
            for(int j = 0; j < numallpasses; j++)
                anOutput[i] = m_allpass_filter[j]->process(anOutput[i]);
            anOutput[i] *= m_wet;
            anOutput[i] += anInput[i] * m_dry;
        }
    };
    
	~Freeverb();
};


#endif
