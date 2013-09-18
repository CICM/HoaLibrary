/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICSOURCESMANAGER
#define DEF_AMBISONICSOURCESMANAGER

#include "../hoaAmbisonics/Ambisonic.h"


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
        
        long   getExistence();
        double getRadius();
        double getAngle();
        double getAbscissa();
        double getOrdinate();
        color  getColor();
        std::string getDescription();
        long   getNumberOfGroups();
        long   getGroupIndex(long anIndex);
        long   isOwnedByGroup(long aGroupIndex);
        long   getMute();
        

        
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
        color  getColor();
        long   getMute();
        
        int compare(const SourcesGroup* a, const SourcesGroup *b);

        
        ~SourcesGroup();
    };
    double                      m_maximum_radius;
    std::vector <Source*>       m_sources;
    std::vector <SourcesGroup*> m_groups;
    long                        m_existence;
    double                      m_zoom; // For VST Audio Plugin //
    void checkMute();
public:
	SourcesManager(double aMaximumLimitValue = -1., long deadOrAlive = 1);
    
    void clearAll();
    void setMaximumRadius(double aLimitValue);
    void setExistence(long deadOrAlive);
    long getMaximumIndexOfSource();
    long getNumberOfSources();
    long getMaximumIndexOfGroup();
    long getNumberOfGroups();
    double getLimitMaximum();
    long getExistence();
    void setZoom(double aZoomValue);
    double getZoom();
    
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
    void sourceSetMute(long anIndex, long aValue);
    
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
    long sourceGetMute(long anIndex);
    
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
    void groupRemoveWithSources(long aGroupIndex);
    long groupGetNumberOfSources(long aGroupIndex);
    long groupGetSourceIndex(long aGroupIndex, long aSourceIndex);
    void groupSetMute(long anIndex, long aValue);
    
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
	long groupGetMute(long anIndex);
    
    int groupCompare(long groupIndexA, const long groupIndexB);
    
	~SourcesManager();
};



#endif
