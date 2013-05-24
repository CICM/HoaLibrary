/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef DEF_AMBISONICSDIFFUSER
#define DEF_AMBISONICSDIFFUSER

#include "../HoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmFilters/CicmFilterBiquad.h"


class AmbisonicsDiffuser : public Ambisonics
{
	
private:
    double m_diffuse_factor;
    vector<FilterBiquad*> m_filters;
	
public:
	AmbisonicsDiffuser(long anOrder = 1, long aVectorSize = 0, long aSamplingRate = 44100);
    
    void setDiffuseFactor(double aDiffusefactor);
    double getDiffuseFactor();
    
	~AmbisonicsDiffuser();
	
    /* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_filters[i]->process(inputs[i]);
	}
    
	inline void process(double* inputs, double* outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = m_filters[i]->process(inputs[i]);
	}
    
    inline void process(float* inputs, float* outputs, float aDiffusefactor)
	{
        setDiffuseFactor(aDiffusefactor);
        process(inputs, outputs);
	}
    
	inline void process(double* inputs, double* outputs, double aDiffusefactor)
	{
        setDiffuseFactor(aDiffusefactor);
        process(inputs, outputs);
	}
	
	/* Perform block sample */
	inline void process(float** inputs, float** outputs)
	{
        m_filters[0]->process(inputs[0], outputs[0]);
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_filters[i]->process(inputs[i], outputs[i]);
        
        m_filters[m_number_of_harmonics-1]->process(inputs[m_number_of_harmonics-1], outputs[m_number_of_harmonics-1]);
	}
    
    /* Perform block sample */
	inline void process(double** inputs, double** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_filters[i]->process(inputs[i], outputs[i]);
	}
};



#endif


