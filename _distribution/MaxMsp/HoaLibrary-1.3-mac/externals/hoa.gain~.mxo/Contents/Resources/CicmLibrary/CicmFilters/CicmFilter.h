/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#ifndef DEF_FILTER
#define DEF_FILTER

#include "../CicmDefine.h"
#include "../CicmTools.h"

class Filter
{
protected:
    long	m_vector_size;
    long	m_sampling_rate;

public:
	Filter(long aVectorSize = 0, double aSamplingRate = 44100.);
	long getVectorSize();
	long getSamplingRate();
    
	void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);

	~Filter();
	
	/* Perform sample by sample */
	inline float process(float input)
	{	
		return input;
	}
    
	inline double process(double input)
	{
		return input;
	}
	
	/* Perform block sample */
	inline void process(float* inputs, float* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            outputs[i] = inputs[i];
        }
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            outputs[i] = inputs[i];
        }
	}
};



#endif


