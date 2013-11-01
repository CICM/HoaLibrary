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

#ifndef DEF_FILTER
#define DEF_FILTER

#include "../CicmDefine.h"

class Filter
{
protected:
    long	m_vector_size;
    long	m_sampling_rate;

public:
	Filter(long aVectorSize = 0, long aSamplingRate = 44100);
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


