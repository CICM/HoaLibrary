/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Source.h"

namespace Hoa2D
{
	Source::Source(long deadOrAlive, double aRadius, double anAngle)
	{
		m_exist = clip_minmax(deadOrAlive, (long)0, (long)1);
		setRadius(aRadius);
		setAngle(anAngle);
		m_color = new double[4];
		setColor(0.2, 0.2, 0.2, 1.);
		setDescription("");
		m_maximum_radius = -1;
		m_mute = 0;
	}
	
	void Source::setMaximumRadius(double aLimitValue)
	{
		m_maximum_radius = aLimitValue;
	}
	
	void Source::setExistence(long deadOrAlive)
	{
		m_exist = clip_minmax(deadOrAlive, (long)0, (long)1);
	}
	
	void Source::setCoordinatesPolar(double aRadius, double anAngle)
	{
		setRadius(aRadius);
		setAngle(anAngle);
	}
	
	void Source::setRadius(double aRadius)
	{
		if(m_maximum_radius >= 0)
		{
			if(aRadius < -m_maximum_radius || aRadius > m_maximum_radius)
				return;
		}
		m_radius = clip_min(aRadius, 0.);
	}
	
	void Source::setAngle(double azimuth)
	{
		m_azimuth = wrap_twopi(azimuth);
	}
	
	void Source::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
	{
		setRadius(radius(anAbscissa, anOrdinate));
		setAngle(azimuth(anAbscissa, anOrdinate) - HOA_PI2);
	}
	
	void Source::setAbscissa(double anAbscissa)
	{
		double ordinate = getOrdinate();
		setRadius(radius(anAbscissa, ordinate));
		setAngle(azimuth(anAbscissa, ordinate) - HOA_PI2);
	}
	
	void Source::setOrdinate(double anOrdinate)
	{
		double abscissa = getAbscissa();
		setRadius(radius(abscissa, anOrdinate));
		setAngle(azimuth(abscissa, anOrdinate) - HOA_PI2);
	}
	
	void Source::setColor(double red, double green, double blue, double alpha)
	{
		m_color[0]	=  clip_minmax(red, 0., 1.);
		m_color[1]	=  clip_minmax(green, 0., 1.);
		m_color[2]	=  clip_minmax(blue, 0., 1.);
		m_color[3]	=  clip_minmax(alpha, 0., 1.);
	}
	
	void Source::setDescription(std::string aDescription)
	{
		m_description = aDescription;
	}
	
	void Source::setGroup(long aGroupIndex)
	{
		for(int i = 0; i < m_groups.size(); i++)
		{
			if(m_groups[i] == aGroupIndex)
				return;
		}
		m_groups.push_back(aGroupIndex);
	}
	
	void Source::setMute(long aValue)
	{
		m_mute = aValue != 0;
	}
	
	void Source::removeGroup(long aGroupIndex)
	{
		for(int i = 0; i < m_groups.size(); i++)
		{
			if(m_groups[i] == aGroupIndex)
			{
				for(int j = i; j < m_groups.size() - 1; j++)
				{
					m_groups[j] = m_groups[j+1];
				}
				m_groups.pop_back();
			}
		}
	}
	
	long Source::getGroupIndex(long anIndex)
	{
		if(anIndex < m_groups.size() && anIndex >= 0)
			return m_groups[anIndex];
		else
			return -1;
	}
	
	long Source::isOwnedByGroup(long aGroupIndex)
	{
		for (int i = 0; i < m_groups.size(); i++)
			if (m_groups[i] == aGroupIndex) return 1;
		return 0;
	}
	
	Source::~Source()
	{
		delete m_color;
		m_groups.clear();
	}
}