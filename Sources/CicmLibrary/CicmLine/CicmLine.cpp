/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CicmLine.h"

namespace Cicm
{
	Line::Line(long aTimeInSample, long aVectorSize, long aSamplingRate)
	{
		m_value_old = 0.;
		m_value_new = 0.;
		m_value_step = 0.;
		m_counter = 0;
		
		setVectorSize(aVectorSize);
		setSamplingRate(aSamplingRate);
		setRampInSample(aTimeInSample);
	}
	
	Line::Line(double aTimeInMs, long aVectorSize, long aSamplingRate)
	{
		m_value_old = 0.;
		m_value_new = 0.;
		m_value_step = 0.;
		m_counter = 0;
		
		setVectorSize(aVectorSize);
		setSamplingRate(aSamplingRate);
		setRampInMs(aTimeInMs);
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
	
	long Line::getVectorSize()
	{
		return m_vector_size;
	}
	
	long Line::getSamplingRate()
	{
		return m_sampling_rate;
	}
	
	double Line::getCoefficient()
	{
		return m_value_new;
	}
	
	long Line::getRampInSample()
	{
		return m_ramp;
	}
	
	double Line::getRampInMs()
	{
		return ((double)m_ramp / (double)m_sampling_rate) * 1000.;
	}
	
	void Line::setRampInSample(long aTimeInSample)
	{
		m_ramp = Hoa2D::clip_min(aTimeInSample, (long)1);
	}
	
	void Line::setRampInMs(double aTimeInMs)
	{
		setRampInSample(aTimeInMs * (double)m_sampling_rate / 1000.);
	}
	
	void Line::setCoefficientDirect(double aCoefficient)
	{
		m_value_old = m_value_new = aCoefficient;
		m_value_step = 0.;
		m_counter = 0;
	}
	
	void Line::setCoefficient(double aCoefficient)
	{
		m_value_new  = aCoefficient;
		m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
		m_counter = 0;
	}
	
	void Line::setCoefficientAngleDirect(double anAngle)
	{
		m_value_old = m_value_new = Hoa2D::wrap_twopi(anAngle);
		m_value_step = 0.;
		m_counter = 0;
	}
	
	void Line::setCoefficientAngle(double anAngle)
	{
		m_value_new = Hoa2D::wrap_twopi(anAngle);
		m_value_old = Hoa2D::wrap_twopi(m_value_old);
		if(Hoa2D::radianDistance(m_value_old, m_value_new) <= CICM_PI)
		{
			m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
		}
		else
		{
			if(m_value_new > Hoa2D::wrap_twopi(m_value_old))
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
	
	void Line::setVectorSize(long aVectorSize)
	{
		m_vector_size = Hoa2D::clip_power_of_two(aVectorSize);
	}
	
	void Line::setSamplingRate(long aSamplingRate)
	{
		m_sampling_rate = Hoa2D::clip_min(aSamplingRate, long(1));
	}
	
	Line::~Line()
	{
		;
	}
}