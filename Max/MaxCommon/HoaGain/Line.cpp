/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Line.h"

Line::Line(long samps, long vector_size, long sampling_rate)
{
	init(vector_size, sampling_rate);
	setRampInSample(samps);
}

Line::Line(double ms, long vector_size, long sampling_rate)
{
	init(vector_size, sampling_rate);
	setRampInMs(ms);
}

void Line::init(const long vector_size, const long sampling_rate)
{
	m_value_old = 0.;
	m_value_new = 0.;
	m_value_step = 0.;
	m_counter = 0;
	
	setVectorSize(vector_size);
	setSamplingRate(sampling_rate);
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

void Line::setRampInSample(const long samps)
{
	m_ramp = clip_min(samps, (long)1);
}

void Line::setRampInMs(const double ms)
{
	setRampInSample(ms * (double)m_sampling_rate / 1000.);
}

void Line::setValueDirect(const double value)
{
	m_value_old = m_value_new = value;
	m_value_step = 0.;
	m_counter = 0;
}

void Line::setValue(const double value)
{
	m_value_new  = value;
	m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
	m_counter = 0;
}

void Line::setValueAngleDirect(const double angle)
{
	m_value_old = m_value_new = wrap_twopi(angle);
	m_value_step = 0.;
	m_counter = 0;
}

void Line::setValueAngle(const double angle)
{
	m_value_new = wrap_twopi(angle);
	m_value_old = wrap_twopi(m_value_old);
    double distance;
    if(m_value_old > m_value_new)
        distance = (m_value_old - m_value_new);
    else
        distance = (m_value_new - m_value_old);
	if(distance <= HOA_PI)
	{
		m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
	}
	else
	{
		if(m_value_new > m_value_old)
		{
			m_value_step = ((m_value_new - HOA_2PI) - m_value_old) / (double)m_ramp;
		}
		else
		{
			m_value_step = ((m_value_new + HOA_2PI) - m_value_old) / (double)m_ramp;
		}
	}
	m_counter = 0;
}