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

#ifndef DEF_CICM_RINGMODULATION
#define DEF_CICM_RINGMODULATION

/****************************************/
/*           RING MODULATION            */
/****************************************/

#include "../CicmFilters/CicmFilterDelay.h"
#include "../CicmEnvelope/CicmEnvelope.h"
#include "../CicmLines/CicmLine.h"

class CicmRingModulation
{
protected:
    CicmLine*           m_line;
    CicmEnvelope*       m_envelope;

    long	m_vector_size;
    long	m_sampling_rate;
    double  m_frequency;
    
public:
	CicmRingModulation(long aVectorSize = 1, double aSamplingRate = 44100.);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    void setFrequency(double aFrequency);
    
	long getVectorSize();
	long getSamplingRate();
    double getFrequency();
    
	~CicmRingModulation();
    
	/**********************************/
	/**** Perform sample by sample ****/
    /**********************************/
    
	inline float process(float input)
	{
        float ramp = m_line->process();
        float gain = m_envelope->getValueRelative(ramp);
        if(ramp >= 1.)
        {
            m_line->setCoefficientDirect(0.f);
            m_line->setCoefficient(1.f);
        }
        return input * gain;
	}
    
	inline double process(double input)
	{
		double ramp = m_line->process();
        double gain = m_envelope->getValueRelative(ramp);
        if(ramp >= 1.)
        {
            m_line->setCoefficientDirect(0.f);
            m_line->setCoefficient(1.f);
        }
        return input * gain;
	}
    
    /**********************************/
	/****** Perform block sample ******/
    /**********************************/
	
	inline void process(float* inputs, float* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = process(inputs[i]);
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = process(inputs[i]);
	}
};



#endif


