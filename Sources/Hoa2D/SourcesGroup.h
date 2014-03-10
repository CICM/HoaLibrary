/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_SOURCESGROUP
#define DEF_SOURCESGROUP

#include "Source.h"
#include "SourcesManager.h"

namespace Hoa2D
{
	class SourcesManager;
	
	//! The sources group
    /** The SourcesGroup should be used to store and manage multiple Source
     */
	class SourcesGroup
	{
		
	private:
		std::vector <long>      m_sources;
		std::string             m_description;
		long                    m_exist;
		double*					m_color;
		double					m_centroid_x;
		double					m_centroid_y;
		SourcesManager*         m_source_manager;
		double                  m_maximum_radius;
		long                    m_mute;
		
		void computeCentroid();
		void shiftPolar(double radius, double azimuth);
		void shiftRadius(double radius);
		void shiftAngle(double azimuth);
		void shiftCartesian(double abscissa, double ordinate);
		void shiftAbscissa(double abscissa);
		void shiftOrdinate(double ordinate);
	public:
		SourcesGroup(SourcesManager* aSourceManager, long deadOrAlive);
		
		void setExistence(long deadOrAlive);
		void setDescription(std::string description);
		void setMaximumRadius(double limitValue);
		void setColor(double red, double green, double blue, double alpha);
		void addSource(long sourceIndex);
		void removeSource(long sourceIndex);
		void sourceHasMoved();
		void setMute(long aValue);
		
		void setCoordinatesPolar(double radius, double azimuth);
		void setRadius(double radius);
		void seAzimuth(double azimuth);
		void setCoordinatesCartesian(double abscissa, double ordinate);
		void setAbscissa(double abscissa);
		void setOrdinate(double ordinate);
		
		void setRelativeCoordinatesPolar(double radius, double azimuth);
		void setRelativeRadius(double radius);
		void setRelativeAngle(double azimuth);
		
		long   getExistence();
		double getRadius();
		double getAzimuth();
		double getAbscissa();
		double getOrdinate();
		long   getNumberOfSources();
		long   getSourceIndex(long index);
		std::string getDescription();
		double*  getColor();
		long   getMute();
		
		int compare(const SourcesGroup* a, const SourcesGroup *b);
		
		~SourcesGroup();
	};
}
#endif
