/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#include "CicmOnePole.h"

AmbisonicOnePole::AmbisonicOnePole(double aSamplingRate, long aVectorSize)
{
    setSamplingRate(aSamplingRate);
    setVectorSize(aVectorSize);
}

void AmbisonicOnePole::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void AmbisonicOnePole::setSamplingRate(double aSamplingRate)
{
	m_samplig_rate = Tools::clip_min(aSamplingRate, 0.);
    setCutOffFrequency(m_cut_off_frequency);
}

void AmbisonicOnePole::setCutOffFrequency(double aFrequency)
{
    m_cut_off_frequency = Tools::clip(aFrequency, 0., m_samplig_rate / 2.);
    m_coeff_a = sin(CICM_2PI * m_cut_off_frequency / m_samplig_rate);
    m_coeff_b = - (1. - m_coeff_a);
}

long AmbisonicOnePole::getVectorSize()
{
	return m_vector_size;    
}

double AmbisonicOnePole::getSamplingRate()
{
	return m_samplig_rate;
}

double  AmbisonicOnePole::getCoeffA()
{
    return m_coeff_a;
}

double  AmbisonicOnePole::getCoeffB()
{
    return m_coeff_b;
}

double  AmbisonicOnePole::getCutOffFrequency()
{
    return m_cut_off_frequency;
}

AmbisonicOnePole::~AmbisonicOnePole()
{
    ;
}
