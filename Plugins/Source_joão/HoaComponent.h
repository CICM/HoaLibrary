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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HOA_COMPONENT_PLUGIN
#define HOA_COMPONENT_PLUGIN

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../Sources/HoaLibrary.h"

class HoaComponentListener
{
public:
    HoaComponentListener(){};
    virtual ~HoaComponentListener(){};
    virtual void componentHasBeenClicked(Component* component){};
};


class HoaProcessor
{
private:
    long                    m_order;
    long                    m_number_of_sources;
    long                    m_number_of_harmonics;
    long                    m_number_of_loudspeakers;
    long                    m_optimization;
    long                    m_decoding_mode;
    double                  m_offset_of_loudspeakers;
    double                  m_angles_of_loudspeakers[256];
    long                    m_maximum_order;
    long                    m_maximum_number_of_loudspeakers;
    long                    m_minimum_number_of_loudspeakers;

    SourcesManager*         m_sources_manager;
    AmbisonicsMultiMaps*    m_map;
    AmbisonicOptim*         m_optim;
    AmbisonicRotate*        m_rotate;
    AmbisonicsMultiDecoder* m_decoder;
    AmbisonicsMeter*        m_meter;
    float*                  m_harmonics_matrix[64];
    
public:
    HoaProcessor();
    ~HoaProcessor();
    
    void setOrder(long anOrder);
    void setNumberOfSources(long aNumberOfSources);
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    void setDecodingMode(long aDecodingMode);
    void setOptimization(long anOptimization);
    void setOffsetOfLoudspeakers(double anOffset);
    void setAngleOfLoudspeaker(long anIndex, double anAngle);
    void setZoom(double aZoom);
    
    void prepareToPlay(long aSampleRate, long aVectorSize);
    void process(float** iovector);
    void postProcess();
    void releaseResources();
    
    long getDecompositionOrder(){return m_order;};
    long getNumberOfSources(){return m_number_of_sources;};
    long getNumberOfHarmonics(){return m_number_of_harmonics;};
    long getNumberOfLoudspeakers(){return m_number_of_loudspeakers;};
    long getMaximumOrder(){return m_maximum_order;};
    long getMaximumNumberOfLoudspeakers(){return m_maximum_number_of_loudspeakers;};
    long getMinimumNumberOfLoudspeakers(){return m_minimum_number_of_loudspeakers;};
    long getDecodingMode(){return m_decoding_mode;};
    long getOptimization(){return m_optimization;};
    double getOffsetOfLoudspeakers(){return m_offset_of_loudspeakers;};
    double getAngleOfLoudspeaker(long anIndex){return m_angles_of_loudspeakers[(int)Tools::clip(anIndex, 0, 255)];};
    
    AmbisonicsMeter*    getMeter(){return m_meter;};
    SourcesManager*     getSourceManager(){return m_sources_manager;};
};

#endif