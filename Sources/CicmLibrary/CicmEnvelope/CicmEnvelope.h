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

#ifndef DEF_CICM_ENVELOPE
#define DEF_CICM_ENVELOPE

#include "../CicmSignal.h"

enum
{
    Cicm_Envelope_Square = 0,
    Cicm_Envelope_Hanning = 1,
    Cicm_Envelope_Hamming = 2,
    Cicm_Envelope_Tukey = 3,
    Cicm_Envelope_Halfsinus = 4,
    Cicm_Envelope_Sinus = 5,
    Cicm_Envelope_Lanczos,
    Cicm_Envelope_Triangular,
    Cicm_Envelope_Bartlett,
    Cicm_Envelope_Gaussian,
    Cicm_Envelope_BartlettHann,
    Cicm_Envelope_Blackman,
    Cicm_Envelope_Kaizer,
    Cicm_Envelope_Personnal
};

class CicmEnvelope
{
	
private:
	long                    m_size;
	long                    m_type;
	Cicm_Vector_Double      m_buffer;
    Cicm_Vector_Float       m_buffer_float;
    
    void normalize();
public:
	CicmEnvelope(long aSize = 1024, long aType = Cicm_Envelope_Hanning, bool fft_normalization = 0);
    
	void setSize(long aWindowSize);
	void setType(long aType, double a0 = -1., double a1 = -1., double a2 = -1., bool fft_normalization = 0);
    long getType();
    
	void square();
	void hanning();
	void hamming();
	void tukey(double a0 = 0.5);
	void halfsinus();
    void sinus();
	void lanczos();
	void triangular();
	void bartlett();
	void gaussian(double a0 = 0.5);
	void bartlettHann(double a0 = 0.62, double a1 = 0.48, double a2 = 0.38);
	void blackman(double a0 = 0.16);
	void kaiser(double a0 = 3.);
    void write(double* aBuffer, long aSize);
    void write(float* aBuffer, long aSize);
    
    ~CicmEnvelope();
    
    inline double getValue(long anIndex)
    {
        anIndex = Tools::clip(anIndex, 0, m_size-1);
        return m_buffer[anIndex];
    }
    
    inline double getValueRelative(double aPosition)
    {
        aPosition = Tools::clip(aPosition, 0., 1.);
        return m_buffer[(long)(aPosition * (m_size-1))];
    }
    
    inline void applyEnvelope(double* inputs, double* output)
    {
        cicm_product_vec_vec_d(inputs, m_buffer, output, m_size);
    }
    
    inline void applyEnvelope(float* inputs, float* output)
    {
        cicm_product_vec_vec_f(inputs, m_buffer_float, output, m_size);
    }
	
	
};

#endif