/*
 * AmbisonicSourcesManager.h
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot, Eliott Paris Universite Paris 8
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

#ifndef DEF_AMBISONICSOURCESMANAGER
#define DEF_AMBISONICSOURCESMANAGER

#include "cicmTools.h"

class SourcesManager
{
	
private: 

    class Source
    {
    private:
        coordinatesPolar        m_coordinate_polar;
        color                   m_color;
        std::string             m_description;
        long                    m_exist;
        std::vector <long>      m_groups;
        double                  m_maximum_radius;
        
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
        
        long   getExistence();
        double getRadius();
        double getAngle();
        double getAbscissa();
        double getOrdinate();
        color  getColor();
        std::string getDescription();
        long   getNumberOfGroups();
        long   getGroupIndex(long anIndex);
        
        ~Source();
    };

    class SourcesGroup
    {
        
    private:
        std::vector <long>      m_sources;
        std::string             m_description;
        long                    m_exist;
        color                   m_color;
        coordinatesCartesian    m_centroid;
        SourcesManager*         m_source_manager;
        double                  m_maximum_radius;
        
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
        color  getColor();
        
        ~SourcesGroup();
    };
    double                      m_maximum_radius;
    std::vector <Source*>       m_sources;
    std::vector <SourcesGroup*> m_groups;
    
public:
	SourcesManager(double aMaximumLimitValue = -1.);
    
    void setMaximumRadius(double aLimitValue);
    long getMaximumIndexOfSource();
    long getNumberOfSources();
    long getMaximumIndexOfGroup();
    long getNumberOfGroups();
    double getLimitMaximum();
    
    /* Source */
	void sourceSetPolar(long anIndex, double aRadius, double anAngle);
	void sourceSetRadius(long anIndex, double aRadius);
    void sourceSetAngle(long anIndex, double anAngle);
    void sourceSetCartesian(long anIndex, double anAbscissa, double anOrdinate);
	void sourceSetAbscissa(long anIndex, double anAbscissa);
	void sourceSetOrdinate(long anIndex, double anOrdinate);
    void sourceSetColor(long anIndex, double red, double green, double blue, double alpha);
	void sourceSetDescription(long anIndex, std::string aDescription);
    void sourceRemove(long anIndex);	
    
    long sourceGetExistence(long anIndex);
    coordinatesPolar sourceGetCoordinatesPolar(long anIndex);
	double sourceGetRadius(long anIndex);
	double sourceGetAngle(long anIndex);
    coordinatesCartesian sourceGetCoordinatesCartesian(long anIndex);
	double sourceGetAbscissa(long anIndex);
	double sourceGetOrdinate(long anIndex);
    color sourceGetColor(long anIndex);
    std::string sourceGetDescription(long anIndex);
    long sourceGetNumberOfGroups(long anIndex);
    long sourceGetGroupIndex(long aSourceIndex, long aGroupIndex);
    
    /* Groups */
    void groupSetSource(long aGroupIndex, long aSourceIndex);
    void groupRemoveSource(long aGroupIndex, long aSourceIndex);
	void groupSetPolar(long aGroupIndex, double aRadius, double anAngle);
    void groupSetRadius(long aGroupIndex, double aRadius);
    void groupSetAngle(long aGroupIndex, double anAngle);
    void groupSetCartesian(long aGroupIndex, double anAbscissa, double anOrdinate);
    void groupSetAbscissa(long aGroupIndex, double anAbscissa);
    void groupSetOrdinate(long aGroupIndex, double anOrdinate);
    void groupSetColor(long aGroupIndex, double red, double green, double blue, double alpha);
    void groupSetDescription(long aGroupIndex, std::string aDescription);
    void groupRemove(long aGroupIndex);
    long groupGetNumberOfSources(long aGroupIndex);
    long groupGetSourceIndex(long aGroupIndex, long aSourceIndex);
    
	void groupSetRelativePolar(long aGroupIndex, double aRadius, double anAngle);
	void groupSetRelativeRadius(long aGroupIndex, double aRadius);
    void groupSetRelativeAngle(long aGroupIndex, double anAngle);

    
    long groupGetExistence(long anIndex);
	double groupGetRadius(long anIndex);
	double groupGetAngle(long anIndex);
	double groupGetAbscissa(long anIndex);
	double groupGetOrdinate(long anIndex);
    color groupGetColor(long anIndex);
    std::string groupGetDescription(long anIndex);
	
	~SourcesManager();
};

#endif
