/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_160AE7E1__
#define __PLUGINPROCESSOR_H_160AE7E1__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Ambisonics/AmbisonicPolyEase.h"
#include "Ambisonics/AmbisonicDecoder.h"
#include "Ambisonics/cicmTools.h"
#include "dRowAudio_PluginParameter.h"

//==============================================================================
/**
*/
class HoaplugAudioProcessor  :
    public AudioProcessor,
    public Value::Listener
{
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaplugAudioProcessor)
    AmbisonicPolyEase* m_ambisonic_tool;
    AmbisonicDecode* m_ambisonic_decoder;
    float* m_harmonics_vector[64];
    PluginParameter parameters[130];
public:
    //==============================================================================
    HoaplugAudioProcessor();
    ~HoaplugAudioProcessor();

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
        m_distance_of_loudspeakers_parameter = 1,
        
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
        m_source_abscissa_33 , m_source_ordinate_33,
        m_source_abscissa_34 , m_source_ordinate_34,
        m_source_abscissa_35 , m_source_ordinate_35,
        m_source_abscissa_36 , m_source_ordinate_36,
        m_source_abscissa_37 , m_source_ordinate_37,
        m_source_abscissa_38 , m_source_ordinate_38,
        m_source_abscissa_39 , m_source_ordinate_39,
        m_source_abscissa_40 , m_source_ordinate_40,
        m_source_abscissa_41 , m_source_ordinate_41,
        m_source_abscissa_42 , m_source_ordinate_42,
        m_source_abscissa_43 , m_source_ordinate_43,
        m_source_abscissa_44 , m_source_ordinate_44,
        m_source_abscissa_45 , m_source_ordinate_45,
        m_source_abscissa_46 , m_source_ordinate_46,
        m_source_abscissa_47 , m_source_ordinate_47,
        m_source_abscissa_48 , m_source_ordinate_48,
        m_source_abscissa_49 , m_source_ordinate_49,
        m_source_abscissa_50 , m_source_ordinate_50,
        m_source_abscissa_51 , m_source_ordinate_51,
        m_source_abscissa_52 , m_source_ordinate_52,
        m_source_abscissa_53 , m_source_ordinate_53,
        m_source_abscissa_54 , m_source_ordinate_54,
        m_source_abscissa_55 , m_source_ordinate_55,
        m_source_abscissa_56 , m_source_ordinate_56,
        m_source_abscissa_57 , m_source_ordinate_57,
        m_source_abscissa_58 , m_source_ordinate_58,
        m_source_abscissa_59 , m_source_ordinate_59,
        m_source_abscissa_60 , m_source_ordinate_60,
        m_source_abscissa_61 , m_source_ordinate_61,
        m_source_abscissa_62 , m_source_ordinate_62,
        m_source_abscissa_63 , m_source_ordinate_63,
        m_source_abscissa_64 , m_source_ordinate_64,
        
        
        
        m_number_of_parameters
    };
    
    float   m_sources_ordinate[64], m_sources_abscissa[64];
    float   m_offset_of_loudspeakers, m_distance_of_loudspeakers;
    int     m_number_of_loudspeakers, m_number_of_sources;
    //==============================================================================
    void valueChanged(Value& value);
    PluginParameter& getPluginParameter (int index);
};

#endif  // __PLUGINPROCESSOR_H_160AE7E1__
