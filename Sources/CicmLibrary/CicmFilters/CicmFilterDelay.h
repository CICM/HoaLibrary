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

#ifndef DEF_CICM_FILTER_DELAY
#define DEF_CICM_FILTER_DELAY

#include "CicmFilter.h"

class CicmFilterDelay : public Filter
{
	private:
	
	long                m_size;
    Cicm_Vector_Double  m_buffer;
	long                m_ramp;
	
	public:
	
	CicmFilterDelay(long aBufferSize, long aVectorSize = 1, long aSamplingRate = 44100);
    CicmFilterDelay(double aBufferSize, long aVectorSize = 1, long aSamplingRate = 44100);
    
    void    setBufferSizeInSample(long aBufferSize);
    void    setBufferSizeInMs(double aBufferSize);
    
    long    getBufferSizeInSample();
    double  getBufferSizeInMs();
    /*******************************************/
    /****************   Write   ****************/
    /*******************************************/
    
    inline void write(double aSample)
    {
        m_buffer[m_ramp] = aSample;
        if(++m_ramp == m_size)
            m_ramp = 0;
    }
    
    inline void write(float aSample)
    {
        m_buffer[m_ramp] = aSample;
        if(++m_ramp == m_size)
            m_ramp = 0;
    }
    /*
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
    */
    /*******************************************/
    /*********** Read No Interpolation *********/
    /*******************************************/
    
    inline double read_no_sample(long aDelay)
    {
        aDelay = Tools::clip(aDelay, 0, m_size-1);
        aDelay = m_ramp - aDelay - 1;
        if(aDelay < 0)
            aDelay += m_size;
        return m_buffer[aDelay];
    }
    
    inline double read_no_ms(double aDelay)
    {
        return read_no_sample((long)(aDelay * m_sampling_rate / 1000.));
    }
    
    inline float read_no_sample(int aDelay)
    {
        aDelay = Tools::clip(aDelay, 0, m_size-1);
        aDelay = m_ramp - aDelay - 1;
        if(aDelay < 0)
            aDelay += m_size;
        return m_buffer[aDelay];
    }
    
    inline float read_no_ms(float aDelay)
    {
        return read_no_sample((int)(aDelay * m_sampling_rate / 1000.));
    }
    /*
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
    */
    /*******************************************/
    /******** Read Cosinus Interpolation *******/
    /*******************************************/
    
    double read_cosinus_sample(double aDelay)
    {
        long	floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        double  alpha = (1. - cos(decimalPart * CICM_PI)) / 2.;

        return read_no_sample((long)aDelay) * (1. - alpha) + read_no_sample((long)(aDelay - 1)) * alpha;
    }
    
    double read_cosinus_ms(double aDelay)
    {
        return read_cosinus_sample(aDelay * m_sampling_rate / 1000.);
    }
    /*
    void read_cosinus_sample(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cosinus_sample(delays[i]);
    }
    
    void read_cosinus_sample(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cosinus_sample(delays[i]);
    }
    
    void read_lcosinus_ms(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cosinus_ms(delays[i]);
    }
    
    void read_cosinus_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cosinus_ms(delays[i]);
    }
    */
    /*******************************************/
    /******** Read Linear Interpolation ********/
    /*******************************************/
    
    double read_linear_sample(double aDelay)
    {
        long	floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        return read_no_sample((long)aDelay) * (1. - decimalPart) + read_no_sample((long)aDelay + 1) * decimalPart;
    }
    
    double read_linear_ms(double aDelay)
    {
        return read_linear_sample(aDelay * m_sampling_rate / 1000.);
    }
    /*
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
            outputs[i] = read_linear_ms(delays[i]);
    }
    
    void read_linear_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_linear_ms(delays[i]);
    }
    */
    /*******************************************/
    /******** Read Cubic Interpolation *********/
    /*******************************************/
    
    double read_cubic_sample(double aDelay)
    {
        if(aDelay < 1.)
            aDelay = 1;
        int		floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        double	one, two, thr, fou, alpha;
        alpha = decimalPart * decimalPart;
        
        fou = read_no_sample((long)aDelay - 2);
        thr = read_no_sample((long)aDelay - 1);
        two = read_no_sample((long)aDelay);
        one = read_no_sample((long)aDelay - 1);
        
        double a0 = fou - thr - one + two;
        double a1 = one - two - a0;
        double a2 = thr - one;
        double a3 = two;
        
        return a0 * decimalPart * alpha + a1 * alpha + a2 * decimalPart + a3;
    }
    /*
    double read_cubic_ms(double aDelay)
    {
        return read_cubic_sample(aDelay * m_sampling_rate / 1000.);
    }
    
    void read_cubic_sample(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cubic_sample(delays[i]);
    }
    
    void read_cubic_sample(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cubic_sample(delays[i]);
    }
    
    void read_cubic_ms(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cubic_ms(delays[i]);
    }
    
    void read_cubic_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_cubic_ms(delays[i]);
    }
    */
    /*******************************************/
    /****** Read Quadratic Interpolation *******/
    /*******************************************/

    double read_quadratic_sample(double aDelay)
    {
        if(aDelay < 1.)
            aDelay = 1;
        int		floorPart	= aDelay;
        double	decimalPart = aDelay - floorPart;
        double	one, two, thr, fou, oneMthr, alpha;
        
        fou = read_no_sample((long)aDelay - 2);
        thr = read_no_sample((long)aDelay - 1);
        two = read_no_sample((long)aDelay);
        one = read_no_sample((long)aDelay - 1);
        oneMthr = thr - two;
        alpha = 5. / 3.;
        
        return two + decimalPart * (oneMthr - alpha * (1. - decimalPart) * ((fou - one - 3. * oneMthr) * decimalPart + (fou + 2. * one - 3. * two)));
    }
    /*
    double read_quadratic_ms(double aDelay)
    {
        return read_quadratic_sample(aDelay * m_sampling_rate / 1000.);
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
    */
    /*******************************************/
    /******* Read Lagrange Interpolation *******/
    /*******************************************/
    
    double read_lagrange_sample(double aDelay)
    {
        long    floorPart  = aDelay;
        double  decimalPart = aDelay - floorPart + 1.;
        long    tmpIndex;
        double  output = 0.;
        double  weight;
        
        for (int i = 0; i < 4; ++i)
        {
            tmpIndex = floorPart - 1 + i;
            weight = 1.;
            for (int j = 0; j < 4; ++j)
            {
                if (j != i) 
                    weight *= (decimalPart - j) / (double)(i - j);
            }
            
            output += weight * read_no_sample(tmpIndex);
        }
        
        return output;
    }
    
    double read_lagrange_ms(double aDelay)
    {
        return read_lagrange_sample(aDelay * m_sampling_rate / 1000.);
    }
    /*
    void read_lagrange_sample(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_lagrange_sample(delays[i]);
    }
    
    void read_lagrange_sample(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_lagrange_sample(delays[i]);
    }
    
    void read_lagrange_ms(double* delays, double* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_lagrange_ms(delays[i]);
    }
    
    void read_lagrange_ms(float* delays, float* outputs)
    {
        for(int i = 0; i < m_vector_size; i++)
            outputs[i] = read_lagrange_ms(delays[i]);
    }
    */
	~CicmFilterDelay();
};

#endif