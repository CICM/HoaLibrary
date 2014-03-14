/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __HOA_COMPONENT_PLUGIN__
#define __HOA_COMPONENT_PLUGIN__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"

class HoaProcessor
{
private:
    long                    m_order;
    long                    m_number_of_sources;
    long                    m_number_of_harmonics;
    long                    m_number_of_channels;
    long                    m_optimization;
    long                    m_decoding_mode;
    double                  m_offset_of_channels;
    double                  m_angles_of_channels[256];
    long                    m_maximum_order;
    long                    m_maximum_number_of_channels;
    long                    m_minimum_number_of_channels;

    SourcesManager*         m_sources_manager;
    Map*					m_map;
    Optim*					m_optim;
    Rotate*					m_rotate;
    DecoderMulti*			m_decoder;
    Meter*					m_meter;
    float*                  m_harmonics_matrix[64];
    
public:
    HoaProcessor();
    ~HoaProcessor();
    
    void setOrder(long anOrder);
    void setNumberOfSources(long aNumberOfSources);
    void setNumberOfChannels(long aNumberOfChannels);
    void setDecodingMode(long aDecodingMode);
    void setOptimization(long anOptimization);
    void setOffsetOfChannels(double anOffset);
    void setAngleOfChannel(long anIndex, double anAngle);
    void setZoom(double aZoom);
    
    void prepareToPlay(long aSampleRate, long aVectorSize);
    void process(float** iovector);
    void postProcess();
    void releaseResources();
    
    long getOrder(){return m_order;};
    long getNumberOfSources(){return m_number_of_sources;};
    long getNumberOfHarmonics(){return m_number_of_harmonics;};
    long getNumberOfChannels(){return m_number_of_channels;};
    long getMaximumOrder(){return m_maximum_order;};
    long getMaximumNumberOfChannels(){return m_maximum_number_of_channels;};
    long getMinimumNumberOfChannels(){return m_minimum_number_of_channels;};
    long getDecodingMode(){return m_decoding_mode;};
    long getOptimization(){return m_optimization;};
    double getOffsetOfChannels(){return m_offset_of_channels;};
    double getAngleOfChannel(long anIndex){return m_angles_of_channels[(int)clip_minmax(anIndex, 0, 255)];};
    
    Meter*				getMeter(){return m_meter;};
    SourcesManager*     getSourceManager(){return m_sources_manager;};
};

#endif