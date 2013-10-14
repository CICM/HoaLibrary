/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_7C6F24B5__
#define __PLUGINPROCESSOR_H_7C6F24B5__

#include "cicmTools.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "dRowAudio_PluginParameter.h"

//==============================================================================
/**
*/
class HoaMeterAudioProcessor  :
    public AudioProcessor,
    public Value::Listener
{
public:
    //==============================================================================
    HoaMeterAudioProcessor();
    ~HoaMeterAudioProcessor();

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

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    void numChannelsChanged();
    
    //====================
	float getScaledParameter (int parameterIndex);
    void setScaledParameter (int parameterIndex, float newValue);
	float getParameterMin (int parameterIndex);
    float getParameterMax (int parameterIndex);
    float getParameterDefault (int parameterIndex);
	void smoothParameters();
    void valueChanged(Value& value);
    PluginParameter& getPluginParameter (int index);
    
    enum Parameters
    {
        m_offset_of_loudspeakers_parameter = 0,
        m_number_of_parameters
    };
    
    int         f_numberOfLoudspeakers;
	double*		f_amplitudeOfLoudspeakers;
    float       m_offset_of_loudspeakers;
    
    void resetAmplitude();
    
private:
    int         f_sampleframes;
    PluginParameter parameters[m_number_of_parameters];
        
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaMeterAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_7C6F24B5__
