/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_SOURCESMANAGER
#define DEF_SOURCESMANAGER

#include "../Hoa/Hoa.h"
#include "Source.h"
#include "SourcesGroup.h"

namespace Hoa2D
{
	class SourcesGroup;
	
	//! The sources manager
    /** The SourcesManager should be used to store and manage multiple Source and SourcesGroup
     */
	class SourcesManager
	{
		
	private:
		
		double                      m_maximum_radius;
		std::vector <Source*>       m_sources;
		std::vector <SourcesGroup*> m_groups;
		long                        m_existence;
		double                      m_zoom;
		
		void checkMute();
		
	public:
		SourcesManager(double maximumLimitValue = -1., long deadOrAlive = 1);
		
		void clearAll();
		void setMaximumRadius(double limitValue);
		void setExistence(long deadOrAlive);
		void setZoom(double aZoom);
		long getMaximumIndexOfSource();
		long getNumberOfSources();
		long getMaximumIndexOfGroup();
		long getNumberOfGroups();
		double getLimitMaximum();
		long getExistence();
		double getZoom();
		
		/* Source */
		void sourceNewPolar(double radius, double azimuth);
		void sourceNewCartesian(double abscissa, double ordinate);
		
		void sourceSetPolar(long index, double radius, double azimuth);
		void sourceSetRadius(long index, double radius);
		void sourceSetAngle(long index, double azimuth);
		void sourceSetCartesian(long index, double abscissa, double ordinate);
		void sourceSetAbscissa(long index, double abscissa);
		void sourceSetOrdinate(long index, double ordinate);
		void sourceSetColor(long index, double red, double green, double blue, double alpha);
		void sourceSetDescription(long index, std::string description);
		void sourceRemove(long index);
		void sourceSetMute(long index, long aValue);
		
		long sourceGetExistence(long index);
		double sourceGetRadius(long index);
		double sourceGetAzimuth(long index);
		double sourceGetAbscissa(long index);
		double sourceGetOrdinate(long index);
		double* sourceGetColor(long index);
		std::string sourceGetDescription(long index);
		long sourceGetNumberOfGroups(long index);
		long sourceGetGroupIndex(long sourceIndex, long groupeIndex);
		long sourceGetMute(long index);
		
		/* Groups */
		void groupSetSource(long groupeIndex, long sourceIndex);
		void groupRemoveSource(long groupeIndex, long sourceIndex);
		void groupSetPolar(long groupeIndex, double radius, double azimuth);
		void groupSetRadius(long groupeIndex, double radius);
		void groupSetAngle(long groupeIndex, double azimuth);
		void groupSetCartesian(long groupeIndex, double abscissa, double ordinate);
		void groupSetAbscissa(long groupeIndex, double abscissa);
		void groupSetOrdinate(long groupeIndex, double ordinate);
		void groupSetColor(long groupeIndex, double red, double green, double blue, double alpha);
		void groupSetDescription(long groupeIndex, std::string description);
		void groupRemove(long groupeIndex);
		void groupRemoveWithSources(long groupeIndex);
		long groupGetNumberOfSources(long groupeIndex);
		long groupGetSourceIndex(long groupeIndex, long sourceIndex);
		void groupSetMute(long index, long state);
		void groupClean();
		void groupSetRelativePolar(long groupeIndex, double radius, double azimuth);
		void groupSetRelativeRadius(long groupeIndex, double radius);
		void groupSetRelativeAngle(long groupeIndex, double azimuth);
		
		
		long groupGetExistence(long index);
		double groupGetRadius(long index);
		double groupGetAngle(long index);
		double groupGetAbscissa(long index);
		double groupGetOrdinate(long index);
		double* groupGetColor(long index);
		std::string groupGetDescription(long index);
		long groupGetMute(long index);
		long groupGetIfSourceMuted(long index);
		long groupGetNextIndex();
		
		int groupCompare(long groupIndexA, const long groupIndexB);
		
		~SourcesManager();
	};
}

#endif
