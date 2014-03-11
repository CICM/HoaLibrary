/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Source.h"

namespace Hoa2D
{
	Source::Source(bool existence, double radius, double azimuth)
	{
		m_exist = existence;
		setRadius(radius);
		seAzimuth(azimuth);
		m_color = new double[4];
		setColor(0.2, 0.2, 0.2, 1.);
		setDescription("");
		m_maximum_radius = -1;
		m_mute = 0;
	}
	
	void Source::setMaximumRadius(double limitValue)
	{
		m_maximum_radius = limitValue;
	}
	
	void Source::setExistence(bool state)
	{
		m_exist = state;
	}
	
	void Source::setCoordinatesPolar(double radius, double azimuth)
	{
		setRadius(radius);
		seAzimuth(azimuth);
	}
	
	void Source::setRadius(double radius)
	{
		if(m_maximum_radius >= 0)
		{
			if(radius < -m_maximum_radius || radius > m_maximum_radius)
				return;
		}
		m_radius = clip_min(radius, 0.);
	}
	
	void Source::seAzimuth(double azimuth)
	{
		m_azimuth = wrap_twopi(azimuth);
	}
	
	void Source::setCoordinatesCartesian(double abscissa, double ordinate)
	{
		setRadius(radius(abscissa, ordinate));
		seAzimuth(azimuth(abscissa, ordinate) - HOA_PI2);
	}
	
	void Source::setAbscissa(double abscissa)
	{
		double ordinate = getOrdinate();
		setRadius(radius(abscissa, ordinate));
		seAzimuth(azimuth(abscissa, ordinate) - HOA_PI2);
	}
	
	void Source::setOrdinate(double ordinate)
	{
		double abscissa = getAbscissa();
		setRadius(radius(abscissa, ordinate));
		seAzimuth(azimuth(abscissa, ordinate) - HOA_PI2);
	}
	
	void Source::setColor(double red, double green, double blue, double alpha)
	{
		m_color[0]	=  clip_minmax(red, 0., 1.);
		m_color[1]	=  clip_minmax(green, 0., 1.);
		m_color[2]	=  clip_minmax(blue, 0., 1.);
		m_color[3]	=  clip_minmax(alpha, 0., 1.);
	}
	
	void Source::setDescription(std::string description)
	{
		m_description = description;
	}
	
	void Source::setGroup(long groupIndex)
	{
		for(int i = 0; i < m_groups.size(); i++)
		{
			if(m_groups[i] == groupIndex)
				return;
		}
		m_groups.push_back(groupIndex);
	}
	
	void Source::setMute(bool state)
	{
		m_mute = state;
	}
	
	void Source::removeGroup(long groupIndex)
	{
		for(int i = 0; i < m_groups.size(); i++)
		{
			if(m_groups[i] == groupIndex)
			{
				for(int j = i; j < m_groups.size() - 1; j++)
				{
					m_groups[j] = m_groups[j+1];
				}
				m_groups.pop_back();
			}
		}
	}
	
	long Source::getGroupIndex(long index)
	{
		if(index < m_groups.size() && index >= 0)
			return m_groups[index];
		else
			return -1;
	}
	
	bool Source::isOwnedByGroup(long groupIndex)
	{
		for (int i = 0; i < m_groups.size(); i++)
			if (m_groups[i] == groupIndex) return true;
		return false;
	}
	
	Source::~Source()
	{
		delete m_color;
		m_groups.clear();
	}
}