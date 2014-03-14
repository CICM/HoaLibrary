/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __HOA_COMPONENT_PLUGIN__
#define __HOA_COMPONENT_PLUGIN__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../Sources/HoaLibrary.h"

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
    
    long getOrder(){return m_order;};
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