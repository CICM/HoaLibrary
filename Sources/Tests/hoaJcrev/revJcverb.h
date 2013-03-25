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

#ifndef DEF_JCREV
#define DEF_JCREV

#include "revFeedbackCombFilter.h"
#include "revAllpassFilter.h"
#include "revJcTuning.h"
#include "cicmTools.h"

class Jcverb
{
private:
    long	m_order;
	long	m_factor;
    long    m_sampling_rate;
    long    m_vector_size;
    
	double	m_gain;
    double  m_wet;
    double  m_dry;
	double	roomsize, roomsize1;
	double	damp, damp1;
	double	mode;
    vector <FeedbackCombFilter*>    m_comb_filter;
    vector <AllpassFilter*> m_allpass_filter;

	void	update();

public:
	Jcverb(long anOrder, double aFactor);

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

	inline void	process(float *anInput, float *anOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            anOutput[i] = anInput[i];
            for(int j = 0; j < numallpasses; j++)
                anOutput[i] = m_allpass_filter[j]->process(anOutput[i]);
            
            for(int j = m_order; j < numcombs; j++)
                anOutput[i] += m_comb_filter[j-m_order]->process(anInput[i]);
            
            
            anOutput[i] *= m_wet;
            anOutput[i] += anInput[i] * m_dry;
        }
    };
    
    inline void	process(double *anInput, double *anOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            anInput[i] *= m_gain;
            anOutput[i] = 0.;
            for(int j = m_order; j < numcombs; j++)
                anOutput[i] += m_comb_filter[j-m_order]->process(anInput[i]);
            
            for(int j = 0; j < numallpasses; j++)
                anOutput[i] = m_allpass_filter[j]->process(anOutput[i]);
            anOutput[i] *= m_wet;
            anOutput[i] += anInput[i] * m_dry;
        }
    };
    
	~Jcverb();
};


#endif
