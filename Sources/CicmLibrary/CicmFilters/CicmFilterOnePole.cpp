/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CicmFilterOnePole.h"

FilterOnePole::FilterOnePole(double aSamplingRate, long aVectorSize)
{
    setSamplingRate(aSamplingRate);
    setVectorSize(aVectorSize);
}

void FilterOnePole::setSamplingRate(double aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, 0.);
    setCutOffFrequency(m_cut_off_frequency);
}

void FilterOnePole::setCutOffFrequency(double aFrequency)
{
    m_cut_off_frequency = Tools::clip(aFrequency, 0., m_sampling_rate / 2.);
    m_coeff_a = sin(CICM_2PI * m_cut_off_frequency / m_sampling_rate);
    m_coeff_b = - (1. - m_coeff_a);
}

double  FilterOnePole::getCoeffA()
{
    return m_coeff_a;
}

double  FilterOnePole::getCoeffB()
{
    return m_coeff_b;
}

double  FilterOnePole::getCutOffFrequency()
{
    return m_cut_off_frequency;
}

FilterOnePole::~FilterOnePole()
{
    ;
}
