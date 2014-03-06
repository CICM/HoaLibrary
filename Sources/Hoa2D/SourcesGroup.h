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
	
	class SourcesGroup
	{
		
	private:
		std::vector <long>      m_sources;
		std::string             m_description;
		long                    m_exist;
		t_hoa_rgba              m_color;
		coordinatesCartesian    m_centroid;
		SourcesManager*         m_source_manager;
		double                  m_maximum_radius;
		long                    m_mute;
		
		void computeCentroid();
		void shiftPolar(double aRadius, double anAngle);
		void shiftRadius(double aRadius);
		void shiftAngle(double anAngle);
		void shiftCartesian(double anAbscissa, double anOrdinate);
		void shiftAbscissa(double anAbscissa);
		void shiftOrdinate(double anOrdinate);
	public:
		SourcesGroup(SourcesManager* aSourceManager, long deadOrAlive);
		
		void setExistence(long deadOrAlive);
		void setDescription(std::string aDescription);
		void setMaximumRadius(double aLimitValue);
		void setColor(double red, double green, double blue, double alpha);
		void addSource(long aSourceIndex);
		void removeSource(long aSourceIndex);
		void sourceHasMoved();
		void setMute(long aValue);
		
		void setCoordinatesPolar(double aRadius, double anAngle);
		void setRadius(double aRadius);
		void setAngle(double anAngle);
		void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
		void setAbscissa(double anAbscissa);
		void setOrdinate(double anOrdinate);
		
		void setRelativeCoordinatesPolar(double aRadius, double anAngle);
		void setRelativeRadius(double aRadius);
		void setRelativeAngle(double anAngle);
		
		long   getExistence();
		double getRadius();
		double getAngle();
		double getAbscissa();
		double getOrdinate();
		long   getNumberOfSources();
		long   getSourceIndex(long anIndex);
		std::string getDescription();
		t_hoa_rgba  getColor();
		long   getMute();
		
		int compare(const SourcesGroup* a, const SourcesGroup *b);
		
		
		~SourcesGroup();
	};
}
#endif
