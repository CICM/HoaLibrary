/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#ifndef DEF_FILTERDELAY
#define DEF_FILTERDELAY

#include "CicmFilter.h"

class FilterDelay : public Filter
{
	private:
	
	long                m_size;
    Cicm_Vector_Double  m_buffer;
	long                m_ramp;
	
	public:
	
	FilterDelay(long aBufferSize, long aVectorSize = 1, long aSamplingRate = 44100);
    FilterDelay(double aBufferSize, long aVectorSize = 1, long aSamplingRate = 44100);
    
    void    setBufferSizeInSample(long aBufferSize);
    void    setBufferSizeInMs(double aBufferSize);
    /*******************************************/
    /****************   Write   ****************/
    /*******************************************/
    
    inline void write(double aSample)
    {
        m_buffer[m_ramp] = aSample;
        if(++m_ramp == m_size)
            m_ramp = 0;
    }
    
    inline void write(double* samples)
    {
        for(int i = 0; i < m_vector_size; i++)
            write(samples[i]);
    }
    
    inline void write(float* samples)
    {
        for(int i = 0; i < m_vector_size; i++)
            write(samples[i]);
    }
    
    /*******************************************/
    /*********** Read No Interpolation *********/
    /*******************************************/
    
    double read_no_sample(long aDelay)
    {
        Tools::clip(aDelay, 0, m_size);
        aDelay = m_ramp - aDelay;
        if(aDelay < 0)
            aDelay += m_size;
        return m_buffer[aDelay];
    }
    
    double read_no_ms(double aDelay)
    {
        return read_no_sample(aDelay * m_sampling_rate);
    }
    
    void read_no_sample(long* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_no_sample(delays[i]);
    }
    
    void read_no_sample(long* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_no_sample(delays[i]);
    }
    
    void read_no_ms(long* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_no_ms(delays[i]);
    }
    
    void read_no_ms(long* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_no_ms(delays[i]);
    }
    
    /*******************************************/
    /******** Read Linear Interpolation ********/
    /*******************************************/
    
    double read_linear_sample(double aDelay)
    {
        long	floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        return read_no_sample(aDelay) * (1. - decimalPart) + read_no_sample(aDelay - 1) * decimalPart;
    }
    
    double read_linear_ms(double aDelay)
    {
        return read_linear_sample(aDelay * m_sampling_rate);
    }
    
    void read_linear_sample(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_linear_sample(delays[i]);
    }
    
    void read_linear_sample(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_linear_sample(delays[i]);
    }
    
    void read_linear_ms(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_linear_sample(delays[i]);
    }
    
    void read_linear_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_linear_sample(delays[i]);
    }

    /*******************************************/
    /****** Read Quadratic Interpolation *******/
    /*******************************************/

    double read_quadratic_sample(double aDelay)
    {
        int		floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        double	one, two, thr, fou, oneMthr, alpha;
        
        fou = read_no_sample(aDelay - 3);
        thr = read_no_sample(aDelay - 2);
        two = read_no_sample(aDelay - 1);
        one = read_no_sample(aDelay);
        oneMthr = thr - two;
        alpha = 5. / 3.;
        
        return two + decimalPart * (oneMthr - alpha * (1. - decimalPart) * ((fou - one - 3. * oneMthr) * decimalPart + (fou + 2. * one - 3. * two)));
    }
    
    double read_quadratic_ms(double aDelay)
    {
        return read_quadratic_sample(aDelay * m_sampling_rate);
    }
    
    void read_quadratic_sample(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_quadratic_sample(delays[i]);
    }
    
    void read_quadratic_sample(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_quadratic_sample(delays[i]);
    }
    
    void read_quadratic_ms(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_quadratic_sample(delays[i]);
    }
    
    void read_quadratic_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_quadratic_sample(delays[i]);
    }
    
    /*******************************************/
    /******* Read Lagrange Interpolation *******/
    /*******************************************/
    
    double read_lagrange_sample(double aDelay)
    {
        int i, j;
        long floorPart  = aDelay;
        double decimalPart = aDelay - floorPart + 1.;
        long tmpIndex;
        double output, weight;
        
        for (i = 0, output = 0.; i < 4; ++i)
        {
            tmpIndex = floorPart - 1 + i;
            for (j = 0, weight = 1.; j < 4; ++j) 
            {
                if (j != i) 
                    weight *= (decimalPart - j) / (double)(i - j);
            }
            
            output += weight * read_no_sample(tmpIndex);
        }
        
        return output;
    }
    
	~FilterDelay();
};

#endif