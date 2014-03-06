/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Line.h"

Line::Line(long aTimeInSample, long aVectorSize, long aSamplingRate)
{
	init(aVectorSize, aSamplingRate);
	setRampInSample(aTimeInSample);
}

Line::Line(double aTimeInMs, long aVectorSize, long aSamplingRate)
{
	init(aVectorSize, aSamplingRate);
	setRampInMs(aTimeInMs);
}

void Line::init(long aVectorSize, long aSamplingRate)
{
	m_value_old = 0.;
	m_value_new = 0.;
	m_value_step = 0.;
	m_counter = 0;
	
	setVectorSize(aVectorSize);
	setSamplingRate(aSamplingRate);
}

double Line::process()
{
	m_value_old += m_value_step;
	if(m_counter++ >= m_ramp)
	{
		m_value_step = 0.;
		m_value_old  = m_value_new;
		m_counter    = 0;
	}
	return m_value_old;
}

void Line::setRampInSample(long aTimeInSample)
{
	m_ramp = Hoa2D::clip_min(aTimeInSample, (long)1);
}

void Line::setRampInMs(double aTimeInMs)
{
	setRampInSample(aTimeInMs * (double)m_sampling_rate / 1000.);
}

void Line::setValueDirect(double aCoefficient)
{
	m_value_old = m_value_new = aCoefficient;
	m_value_step = 0.;
	m_counter = 0;
}

void Line::setValue(double aCoefficient)
{
	m_value_new  = aCoefficient;
	m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
	m_counter = 0;
}

void Line::setValueAngleDirect(double anAngle)
{
	m_value_old = m_value_new = Hoa2D::wrap_twopi(anAngle);
	m_value_step = 0.;
	m_counter = 0;
}

void Line::setValueAngle(double anAngle)
{
	m_value_new = Hoa2D::wrap_twopi(anAngle);
	m_value_old = Hoa2D::wrap_twopi(m_value_old);
    double distance;
    if(m_value_old > m_value_new)
        distance = (m_value_old - m_value_new);
    else
        distance = (m_value_new - m_value_old);
	if(distance <= CICM_PI)
	{
		m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
	}
	else
	{
		if(m_value_new > m_value_old)
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