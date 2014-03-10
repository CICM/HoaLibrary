/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_SOURCE
#define DEF_SOURCE

#include "../Hoa/Hoa.h"

namespace Hoa2D
{	
	class Source
	{
	private:
		double					m_radius;
		double					m_azimuth;
		double*					m_color;
		std::string             m_description;
		long                    m_exist;
		std::vector <long>      m_groups;
		double                  m_maximum_radius;
		long                    m_mute;
	public:
		Source(long deadOrAlive, double aRadius = 0., double anAngle = 0.);
		
		void setExistence(long deadOrAlive);
		void setCoordinatesPolar(double aRadius, double anAngle);
		void setRadius(double aRadius);
		void setAngle(double anAngle);
		void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
		void setAbscissa(double anAbscissa);
		void setOrdinate(double anOrdinate);
		void setColor(double red, double green, double blue, double alpha);
		void setDescription(std::string aDescription);
		void setGroup(long aGroupIndex);
		void removeGroup(long aGroupIndex);
		void setMaximumRadius(double aLimitValue);
		void setMute(long aValue);
		
		long			getExistence()		const {return m_exist;}
		double			getRadius()			const {return m_radius;}
		double			getAzimuth()		const {return m_azimuth;}
		double			getAbscissa()		const {return abscissa(m_radius, m_azimuth + HOA_PI2);}
		double			getOrdinate()		const {return ordinate(m_radius, m_azimuth + HOA_PI2);}
		double*			getColor()			const {return m_color;}
		std::string		getDescription()	const {return m_description;}
		long			getNumberOfGroups() const {return m_groups.size();}
		long			getGroupIndex(long anIndex);
		long			isOwnedByGroup(long aGroupIndex);
		long			getMute()			const {return m_mute;}
		
		~Source();
	};
}
#endif