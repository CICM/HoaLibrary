/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_2114B1A5__
#define __PLUGINPROCESSOR_H_2114B1A5__

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaLibrary.h"

//==============================================================================
/**
 */
class HoaMapAudioProcessor  :
public AudioProcessor,
public Value::Listener,
public ChangeBroadcaster
{
    
public:
    //==============================================================================
    HoaMapAudioProcessor();
    ~HoaMapAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    
    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    
    //==============================================================================
    const String getName() const;
    
    int getNumParameters();
    
    float getParameter (int index);
    void setParameter (int index, float newValue);
    
    const String getParameterName (int index);
    const String getParameterText (int index);
    
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    
    bool isParameterAutomatable	(int parameterIndex) const;
    
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;
    
    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);
    
    //====================
	float getScaledParameter (int parameterIndex);
    void setScaledParameter (int parameterIndex, float newValue);
	float getParameterMin (int parameterIndex);
    float getParameterMax (int parameterIndex);
    float getParameterDefault (int parameterIndex);
	void smoothParameters();
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    void numChannelsChanged();
    
    enum Parameters
    {
        m_offset_of_loudspeakers_parameter = 0,
        m_distance_of_loudspeakers_parameter,
        
        m_source_abscissa_1 , m_source_ordinate_1,
        m_source_abscissa_2 , m_source_ordinate_2,
        m_source_abscissa_3 , m_source_ordinate_3,
        m_source_abscissa_4 , m_source_ordinate_4,
        m_source_abscissa_5 , m_source_ordinate_5,
        m_source_abscissa_6 , m_source_ordinate_6,
        m_source_abscissa_7 , m_source_ordinate_7,
        m_source_abscissa_8 , m_source_ordinate_8,
        m_source_abscissa_9 , m_source_ordinate_9,
        m_source_abscissa_10 , m_source_ordinate_10,
        m_source_abscissa_11 , m_source_ordinate_11,
        m_source_abscissa_12 , m_source_ordinate_12,
        m_source_abscissa_13 , m_source_ordinate_13,
        m_source_abscissa_14 , m_source_ordinate_14,
        m_source_abscissa_15 , m_source_ordinate_15,
        m_source_abscissa_16 , m_source_ordinate_16,
        m_source_abscissa_17 , m_source_ordinate_17,
        m_source_abscissa_18 , m_source_ordinate_18,
        m_source_abscissa_19 , m_source_ordinate_19,
        m_source_abscissa_20 , m_source_ordinate_20,
        m_source_abscissa_21 , m_source_ordinate_21,
        m_source_abscissa_22 , m_source_ordinate_22,
        m_source_abscissa_23 , m_source_ordinate_23,
        m_source_abscissa_24 , m_source_ordinate_24,
        m_source_abscissa_25 , m_source_ordinate_25,
        m_source_abscissa_26 , m_source_ordinate_26,
        m_source_abscissa_27 , m_source_ordinate_27,
        m_source_abscissa_28 , m_source_ordinate_28,
        m_source_abscissa_29 , m_source_ordinate_29,
        m_source_abscissa_30 , m_source_ordinate_30,
        m_source_abscissa_31 , m_source_ordinate_31,
        m_source_abscissa_32 , m_source_ordinate_32,
        m_number_of_parameters
    };
    
    float   m_sources_ordinate[MAX_SOURCES], m_sources_abscissa[MAX_SOURCES];
    float   m_offset_of_loudspeakers, m_distance_of_loudspeakers;
    int     m_number_of_loudspeakers, m_number_of_sources;
    //==============================================================================
    void valueChanged(Value& value);
    PluginParameter& getPluginParameter (int index);
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaMapAudioProcessor)
    AmbisonicsMultiMaps* m_ambisonic_tool;
    AmbisonicRotate* m_ambisonic_rotator;
    AmbisonicsDecoder* m_ambisonic_decoder;
    float* m_harmonics_vector_one[MAX_LOUDSPEAKERS];
    float* m_harmonics_vector_two[MAX_LOUDSPEAKERS];
    PluginParameter parameters[m_number_of_parameters];
};

#endif  // __PLUGINPROCESSOR_H_2114B1A5__
