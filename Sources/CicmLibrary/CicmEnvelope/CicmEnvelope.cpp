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

#include "CicmEnvelope.h"

CicmEnvelope::CicmEnvelope(long aSize, long aType, bool fft_normalization)
{
	m_size = 0;
    m_buffer = NULL;
    m_buffer_float = NULL;

    setSize(aSize);
    setType(aType, fft_normalization);
}

void CicmEnvelope::setSize(long aSize)
{
    aSize = Tools::clip_min(aSize, 1);
    if(aSize != m_size)
    {
        if(m_buffer)
            Cicm_Free(m_buffer);
        if(m_buffer_float)
            Cicm_Free(m_buffer_float);
        
        m_size = aSize;
        Cicm_Vector_Double_Malloc(m_buffer, m_size);
        Cicm_Vector_Float_Malloc(m_buffer_float, m_size);
        setType(m_type);
    }
}

void CicmEnvelope::setType(long aType, double a0, double a1, double a2, bool fft_normalization)
{
	m_type = Tools::clip(aType, Cicm_Envelope_Square, Cicm_Envelope_Kaizer);
	if(m_type == Cicm_Envelope_Square)
    {
		square();
    }
	else if(m_type == Cicm_Envelope_Hanning)
    {
		hanning();
    }
	else if(m_type == Cicm_Envelope_Hamming)
    {
		hamming();
    }
	else if(m_type == Cicm_Envelope_Tukey)
	{
		if (a0 > 0.) 
			tukey(a0);
		else
			tukey();
	}
	else if(m_type == Cicm_Envelope_Halfsinus)
    {
		halfsinus();
    }
    else if(m_type == Cicm_Envelope_Sinus)
    {
		sinus();
    }
	else if(m_type == Cicm_Envelope_Lanczos)
    {
		lanczos();
    }
	else if(m_type == Cicm_Envelope_Triangular)
    {
		triangular();
    }
	else if(m_type == Cicm_Envelope_Bartlett)
    {
		bartlett();
    }
	else if(m_type == Cicm_Envelope_Gaussian)
	{
		if (a0 > 0.) 
			gaussian(a0);
		else
			gaussian();
	}
	else if(m_type == Cicm_Envelope_BartlettHann)
	{
		if (a0 > 0. && a1 > 0. && a2 >  0.)
			bartlettHann(a0, a1, a2);
		else
			bartlettHann();
	}
	else if(m_type == Cicm_Envelope_Blackman)
	{
		if (a0 > 0.)
			blackman(a0);
		else
			blackman();
	}
	else if(m_type == Cicm_Envelope_Kaizer)
	{
		if (a0 > 0.)
			kaiser(a0);
		else
			kaiser();
	}
    else
    {
        hanning();
    }
    if(fft_normalization)
        normalize();
    for(int i = 0; i < m_size; i++)
    {
        m_buffer_float[i] = m_buffer[i];
    }
}

void CicmEnvelope::square()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = 1.;
}

void CicmEnvelope::hanning()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = 0.5 * (1.0 - cos(2.0 * CICM_PI * (double)i / (double)(m_size - 1)));
}

void CicmEnvelope::hamming()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = 0.54 - (0.46 * cos(2.0 * CICM_PI * (double)i / (double)(m_size - 1)));
}

void CicmEnvelope::tukey(double a0)
{
	a0 = Tools::clip(a0);
	for(int i = 0; i < m_size; i++)
    {
		if(i <= ((a0 * (double)(m_size - 1)) / 2.))
			m_buffer[i] = 0.5 * ( 1. + cos(CICM_PI * ( ((2 * (double)i) / (a0 * (double)(m_size - 1))) - 1.)));
		else if(i > ((a0 * (double)(m_size - 1)) / 2.) && i <= ((double)(m_size - 1) * (1. - ( a0 / 2.))))
			m_buffer[i] = 1.;
		else 
			m_buffer[i] = 0.5 * ( 1. + cos(CICM_PI * ( ((2 *(double)i) / (a0 * (double)(m_size - 1))) + 1. - (2. / a0))));
    }
}

void CicmEnvelope::halfsinus()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = sin((CICM_PI * (double)i) / (double)(m_size - 1));
}

void CicmEnvelope::sinus()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = sin((CICM_2PI * (double)i) / (double)(m_size - 1));
}

void CicmEnvelope::lanczos()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = sin(CICM_PI * (((2. * (double)i) / (double)(m_size - 1)) - 1.)) / (CICM_PI * (((2. * (double)i) / (double)(m_size - 1)) - 1.));
}

void CicmEnvelope::triangular()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = (2. / (double)(m_size + 1)) * (((double)(m_size + 1) / 2.) - fabs((double)i - (double)(m_size - 1) / 2.));
}

void CicmEnvelope::bartlett()
{
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = (2. / (double)(m_size - 1)) * (((double)(m_size - 1) / 2.) - fabs((double)i - ((double)(m_size - 1) / 2.)));
}


void CicmEnvelope::gaussian(double a0)
{
	a0 = Tools::clip(a0, 0., 0.5);
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = exp((i - (double)(m_size - 1) / 2.)/(a0 * (double)(m_size - 1) / 2.) * (i - (double)(m_size - 1) / 2.)/(a0 * (double)(m_size - 1) / 2.) * -0.5);
}

void CicmEnvelope::bartlettHann(double a0, double a1, double a2)
{
	a0 = Tools::clip(a0);
	a1 = Tools::clip(a1);
	a2 = Tools::clip(a2);
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = a0 - a1 * fabs(((double)i / (double)(m_size - 1)) - 0.5) - a2 * cos((2.0 * CICM_PI *(double)i) / (double)(m_size - 1));
}

void CicmEnvelope::blackman(double a0)
{
	a0 = Tools::clip(a0);
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = ((1. - a0) / 2.) - (0.5 * cos(2.0 * CICM_PI * (double)i / (double)(m_size - 1))) + ((a0 / 2.) * cos(4.0 * CICM_PI * (double)i / (double)(m_size - 1)));
}

void CicmEnvelope::kaiser(double a0)
{
	//a0 = Tools::clip(a0, 0., 10.);
    /*
	for(int i = 0; i < m_size; i++)
		m_buffer[i] = gsl_sf_bessel_I0(CICM_PI * a0 * sqrt((1. - pow(((2. * (double)i) / (double)(m_size - 1)) - 1., 2.)))) / gsl_sf_bessel_I0(CICM_PI * a0);
    */
}

void CicmEnvelope::normalize()
{
    for(int i = 0; i < m_size; i++)
        m_buffer[i] /= (double)m_size * CICM_2PI;
}

long CicmEnvelope::getType()
{
    return m_type;
}

void CicmEnvelope::write(double* aBuffer, long aSize)
{
    setSize(aSize);
    m_type = Cicm_Envelope_Personnal;
    Cicm_Vector_Double_Copy(aBuffer, m_buffer, m_size);
    for(int i = 0; i < m_size; i++)
        m_buffer_float[i] = m_buffer[i];    
}

void CicmEnvelope::write(float* aBuffer, long aSize)
{
    setSize(aSize);
    m_type = Cicm_Envelope_Personnal;
    Cicm_Vector_Float_Copy(aBuffer, m_buffer_float, m_size);
    for(int i = 0; i < m_size; i++)
        m_buffer[i] = m_buffer_float[i];
}

CicmEnvelope::~CicmEnvelope()
{
	Cicm_Free(m_buffer);
    Cicm_Free(m_buffer_float);
}


