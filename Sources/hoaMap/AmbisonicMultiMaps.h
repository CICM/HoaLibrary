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

#ifndef DEF_AMBISONICMULTIMAPS
#define DEF_AMBISONICMULTIMAPS

#include "AmbisonicMap.h"

class AmbisonicsMultiMaps : public Ambisonic
{
	
private:
    vector <AmbisonicMap*> m_maps;
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
    
    void setNumberOfSources(long aNumberOfSources);
    void setCoordinatesPolar(long aSourceIndex, double aRadius, double anAzimuth);
    void setCoordinatesRadius(long aSourceIndex, double aRadius);
    void setCoordinatesAzimuth(long aSourceIndex,double anAzimuth);
    void setCoordinatesCartesian(long aSourceIndex, double anAbscissa, double anOrdinate);
    void setCoordinatesAbscissa(long aSourceIndex, double anAbscissa);
    void setCoordinatesOrdinate(long aSourceIndex,double anOrdinate);
    
    void setMuted(long aSourceIndex, long aValue);
    void setRamp(long aNumberOfSample);
    
    
	~AmbisonicsMultiMaps();
	
	/************************************************************************************/
    /*********************************** MULTISOURCES ***********************************/
    /************************************************************************************/
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const float* inputs, float* outputs)
	{
        cicm_clear_vec_f(outputs, m_number_of_harmonics);
        if(m_first_source >= 0)
        {
            m_maps[m_first_source]->process(inputs[m_first_source], outputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(m_mute[i])
                    m_maps[i]->processAdd(inputs[i], outputs);
            }
        }
    }
    
    inline void process(const double* inputs, double* outputs)
	{
        cicm_clear_vec_d(outputs, m_number_of_harmonics);
		if(m_first_source >= 0)
        {
            m_maps[m_first_source]->process(inputs[m_first_source], outputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(m_mute[i])
                   m_maps[i]->processAdd(inputs[i], outputs);
            }
        }
    }
    
	/************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const float* const* inputs, float** outputs)
	{        
		if(m_first_source != m_number_of_sources)
        {
            m_maps[m_first_source]->process(inputs[m_first_source], outputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(!m_mute[i])
                    m_maps[i]->processAdd(inputs[i], outputs);
            }
        }
        else
        {
            for(int i = 0; i < m_number_of_harmonics; i++)
                cicm_clear_vec_f(outputs[i], m_vector_size);
        }
	}
    
    inline void process(const double* const* inputs, double** outputs)
	{
		if(m_first_source != m_number_of_sources)
        {
            m_maps[m_first_source]->process(inputs[m_first_source], outputs);
            for(int i = m_first_source+1; i < m_number_of_sources; i++)
            {
                if(!m_mute[i])
                    m_maps[i]->processAdd(inputs[i], outputs);
            }
        }
        else
        {
            for(int i = 0; i < m_number_of_harmonics; i++)
                cicm_clear_vec_d(outputs[i], m_vector_size);
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


