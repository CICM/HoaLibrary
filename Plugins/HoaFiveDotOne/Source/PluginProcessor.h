/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __PLUGINPROCESSOR_H_INCLUDED__
#define __PLUGINPROCESSOR_H_INCLUDED__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"

class HoaToolsAudioProcessor : public AudioProcessor, public ChangeBroadcaster
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaToolsAudioProcessor)
    
    class PolarLines
    {
        
    private:
        float*      m_values_old;
        float*      m_values_new;
        float*      m_values_step;
        unsigned int m_counter;
        unsigned int m_ramp;
        unsigned int m_number_of_sources;
        
    public:
        PolarLines(unsigned int numberOfSources);
        ~PolarLines();
        
        inline unsigned int getNumberOfSources() const
        {
            return m_number_of_sources;
        }
        
        inline unsigned int getRamp() const
        {
            return m_ramp;
        }
        
        inline double getRadius(unsigned int index) const
        {
            assert(index < m_number_of_sources);
            return m_values_new[index];
        }
        
        inline double getAzimuth(unsigned int index) const
        {
            assert(index < m_number_of_sources);
            return m_values_new[m_number_of_sources +index];
        }
        
        void setRamp(unsigned int ramp);
        void setRadius(unsigned int index, double radius);
        void setAzimuth(unsigned int index, double azimuth);
        void setRadiusDirect(unsigned int index, double radius);
        void setAzimuthDirect(unsigned int index, double azimuth);
        
        void process(float* vector);
    };

    
    SourcesManager* m_sources;
    Map*            m_map;
    Optim*          m_optim;
    DecoderIrregular* m_decoder;
    Meter*          m_meter;
    PolarLines*     m_lines;
    
    int             m_vector_size;
    int             m_number_of_sources;
    float*          m_input_vector;
    float*          m_harmo_vector;
    float*          m_output_vector;
    float*          m_lines_vector;
public:
    HoaToolsAudioProcessor();
    ~HoaToolsAudioProcessor();

    void numChannelsChanged();
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    
    SourcesManager* getSources() const
    {
        return m_sources;
    }
    
    Meter* getMeter() const
    {
        return m_meter;
    }
    
    int getNumberOfSources() const
    {
        return m_number_of_sources;
    }
    
    void setNumberOfSources(int value)
    {
        int oldnumber = m_number_of_sources;
        m_number_of_sources = (int)clip_minmax(value, 0, 16);
        
        for(int i = 0; i < 16; i++)
        {
            if(i >= oldnumber && i < m_number_of_sources)
            {
                m_sources->sourceSetPolar(i, 1., 0.);
                m_sources->sourceSetMute(i, 0);
            }
            else if(i >= m_number_of_sources)
            {
                m_sources->sourceSetMute(i, 1);
                m_sources->sourceRemove(i);
            }
        }
        m_sources->groupClean();
    
    }
    
    const String getName() const;

    int getNumParameters();
    float getParameter (int index);
    void setParameter (int index, float newValue);
    float getParameterMin(int index);
    float getParameterMax(int index);
    float getParameterDefault(int index);
    int getParameterNumSteps(int parameterIndex);
    float getParameterDefaultValue (int parameterIndex);
    const String getParameterName (int index);
    const String getParameterText (int index);
    String getParameterLabel(int index);
    bool isParameterAutomatable (int index) const;
    bool isMetaParameter(int index) const;
    
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
