/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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


#ifndef DEF_AMBISONICMULTIMAPS
#define DEF_AMBISONICMULTIMAPS

#include "AmbisonicsMap.h"

class AmbisonicsMultiMaps : public Ambisonics
{
	
private:
    vector <AmbisonicsMap*> m_maps;
    long    m_number_of_sources;
    long    m_first_source;
    
    bool     m_mute[64];
    double   m_radius[64];
    double   m_azimuth[64];

public:
	AmbisonicsMultiMaps(long anOrder = 1, long aNumberOfSources = 1, long aRampSample = 4410, long aVectorSize = 0, long aSamplingRate = 0);
    

    long     getNumberOfSources();
    long     getMuted(long aSourceIndex);
    double   getRadius(long aSourceIndex);
    double   getAzimuth(long aSourceIndex);
    long     getRamp();
    std::string getSourceName(long anIndex);
    
	void setVectorSize(long aVectorSize);
    
    void setCoordinatesPolar(long aSourceIndex, double aRadius, double anAzimuth);
    void setCoordinatesRadius(long aSourceIndex, double aRadius);
    void setCoordinatesAzimuth(long aSourceIndex,double anAzimuth);
    void setCoordinatesCartesian(long aSourceIndex, double anAbscissa, double anOrdinate);
    void setCoordinatesAbscissa(long aSourceIndex, double anAbscissa);
    void setCoordinatesOrdinate(long aSourceIndex,double anOrdinate);
    
    void setMuted(long aSourceIndex, long aValue);
    void setRamp(long aNumberOfSample);
    
    
	~AmbisonicsMultiMaps();
	
	/* Perform sample by sample */
	void process(float* aInputs, float* aOutputs)
	{
        if(m_first_source >= 0)
        {
            m_maps[m_first_source]->process(aInputs[m_first_source], aOutputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(m_mute[i])
                    m_maps[i]->processAdd(aInputs[i], aOutputs);
            }
        }
    }
    
    void process(double* aInputs, double* aOutputs)
	{
		if(m_first_source >= 0)
        {
            m_maps[m_first_source]->process(aInputs[m_first_source], aOutputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(m_mute[i])
                   m_maps[i]->processAdd(aInputs[i], aOutputs);
            }
        }
    }
    
	/***************************************/
	/******** Perform block sample *********/
    /***************************************/
    
	inline void process(float** aInputs, float** aOutputs)
	{        
		if(m_first_source >= 0)
        {
            m_maps[m_first_source]->process(aInputs[m_first_source], aOutputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(!m_mute[i])
                    m_maps[i]->processAdd(aInputs[i], aOutputs);
            }
        }
	}
    
    inline void process(double** aInputs, double** aOutputs)
	{
		if(m_first_source != m_number_of_sources)
        {
            m_maps[m_first_source]->process(aInputs[m_first_source], aOutputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(!m_mute[i])
                    m_maps[i]->processAdd(aInputs[i], aOutputs);
            }
        }
	}
    
    /***************************************/
    /* One Source Perform sample by sample */
    /***************************************/
    
    inline void processCartesian(float aInputs, float* aOutputs, float anAbscissa, float anOrdinate)
	{
        m_maps[0]->setCoordinatesCartesian(anAbscissa, anOrdinate);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processPolar(float aInputs, float* aOutputs, float aRadius, float anAzimuth)
	{
         m_maps[0]->setCoordinatesPolar(aRadius, anAzimuth);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processCartesian(double aInputs, double* aOutputs, double anAbscissa, double anOrdinate)
	{
        m_maps[0]->setCoordinatesCartesian(anAbscissa, anOrdinate);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processPolar(double aInputs, double* aOutputs, double aRadius, double anAzimuth)
	{
        m_maps[0]->setCoordinatesPolar(aRadius, anAzimuth);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processRadius(float aInputs, float* aOutputs, float aRadius)
	{
        m_maps[0]->setCoordinatesRadius(aRadius);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processAzimuth(float aInputs, float* aOutputs, float anAzimuth)
	{
        m_maps[0]->setCoordinatesAzimuth(anAzimuth);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processRadius(double aInputs, double* aOutputs, double aRadius)
	{
        m_maps[0]->setCoordinatesRadius(aRadius);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processAzimuth(double aInputs, double* aOutputs, double anAzimuth)
	{
        m_maps[0]->setCoordinatesAzimuth(anAzimuth);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processAbscissa(float aInputs, float* aOutputs, float anAbscissa)
	{
        m_maps[0]->setCoordinatesAbscissa(anAbscissa);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processOrdinate(float aInputs, float* aOutputs, float anOrdinate)
	{
        m_maps[0]->setCoordinatesOrdinate(anOrdinate);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processAbscissa(double aInputs, double* aOutputs, double anAbscissa)
	{
        m_maps[0]->setCoordinatesAbscissa(anAbscissa);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    inline void processOrdinate(double aInputs, double* aOutputs, double anOrdinate)
	{
        m_maps[0]->setCoordinatesOrdinate(anOrdinate);
        if(!m_mute[0])
            m_maps[0]->process(aInputs, aOutputs);
    }
    
    /***************************************/
    /*** One Source Perform block sample ***/
    /***************************************/
    
    inline void processCartesian(float* aInputs, float** aOutputs, float* anAbscissa, float* anOrdinate)
	{
        if(!m_mute[0])
            m_maps[0]->processCartesian(aInputs, aOutputs, anAbscissa, anOrdinate);
    }
    
    inline void processPolar(float* aInputs, float** aOutputs, float* aRadius, float* anAzimuth)
	{
        if(!m_mute[0])
            m_maps[0]->processPolar(aInputs, aOutputs, aRadius, anAzimuth);
    }
    
    inline void processCartesian(double* aInputs, double** aOutputs, double* anAbscissa, double* anOrdinate)
	{
        if(!m_mute[0])
            m_maps[0]->processCartesian(aInputs, aOutputs, anAbscissa, anOrdinate);
    }
    
    inline void processPolar(double* aInputs, double** aOutputs, double* aRadius, double* anAzimuth)
	{
        if(!m_mute[0])
            m_maps[0]->processPolar(aInputs, aOutputs, aRadius, anAzimuth);
    }
    
    inline void processRadius(float* aInputs, float** aOutputs, float* aRadius)
	{
        if(!m_mute[0])
            m_maps[0]->processRadius(aInputs, aOutputs, aRadius);
    }
    
    inline void processAzimuth(float* aInputs, float** aOutputs, float* anAzimuth)
	{
        if(!m_mute[0])
            m_maps[0]->processAzimuth(aInputs, aOutputs, anAzimuth);
    }
    
    inline void processRadius(double* aInputs, double** aOutputs, double* aRadius)
	{
        if(!m_mute[0])
            m_maps[0]->processRadius(aInputs, aOutputs, aRadius);
    }
    
    inline void processAzimuth(double* aInputs, double** aOutputs, double* anAzimuth)
	{
        if(!m_mute[0])
            m_maps[0]->processAzimuth(aInputs, aOutputs, anAzimuth);
    }
    inline void processAbscissa(float* aInputs, float** aOutputs, float* anAbscissa)
	{
        if(!m_mute[0])
            m_maps[0]->processAbscissa(aInputs, aOutputs, anAbscissa);
    }
    
    inline void processOrdinate(float* aInputs, float** aOutputs, float* anOrdinate)
	{
        if(!m_mute[0])
            m_maps[0]->processOrdinate(aInputs, aOutputs, anOrdinate);
    }
    
    inline void processAbscissa(double* aInputs, double** aOutputs, double* anAbscissa)
	{
        if(!m_mute[0])
            m_maps[0]->processAbscissa(aInputs, aOutputs, anAbscissa);
    }
    
    inline void processOrdinate(double* aInputs, double** aOutputs, double* anOrdinate)
	{
        if(!m_mute[0])
            m_maps[0]->processOrdinate(aInputs, aOutputs, anOrdinate);
    }
};



#endif


