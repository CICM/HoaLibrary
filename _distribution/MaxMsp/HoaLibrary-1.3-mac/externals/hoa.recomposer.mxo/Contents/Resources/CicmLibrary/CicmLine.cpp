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

#include "CicmLine.h"

CicmLine::CicmLine(long aRamp, long aVectorSize)
{
    m_value_old = 0.;
    m_value_new = 0.;
    m_value_step = 0.;
    m_counter = 0;
    
    setRamp(aRamp);
    setVectorSize(aVectorSize);
}

double CicmLine::getVectorSize()
{
	return m_vector_size;    
}

double CicmLine::getCoefficient()
{
    return m_value_new;
}

long CicmLine::getRamp()
{
    return m_ramp;
}

void CicmLine::setRamp(long aNumberOfSample)
{
    m_ramp = Tools::clip_min(aNumberOfSample, (long)1);
}

void CicmLine::setCoefficientDirect(double aCoefficient)
{
    m_value_old = m_value_new = aCoefficient;
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine::setCoefficient(double aCoefficient)
{
    m_value_new  = aCoefficient;
    m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
    m_counter = 0;
}

void CicmLine::setCoefficientAngleDirect(double anAngle)
{
    m_value_old = m_value_new = Tools::radianWrap(anAngle);
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine::setCoefficientAngle(double anAngle)
{
    m_value_new = Tools::radianWrap(anAngle);
    m_value_old = Tools::radianWrap(m_value_old);
    if(Tools::radianDistance(m_value_old, m_value_new) <= CICM_PI)
    {
        m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
    }
    else
    {
        if(m_value_new > Tools::radianWrap(m_value_old))
        {
            m_value_step = ((m_value_new - CICM_2PI) - m_value_old) / (double)m_ramp;
        }
        else
        {
            m_value_step = ((m_value_new + CICM_2PI) - m_value_old) / (double)m_ramp;
        }
    }
    m_counter = 0;
}

void CicmLine::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
    m_counter = 0;
}

CicmLine::~CicmLine()
{
    ;
}
