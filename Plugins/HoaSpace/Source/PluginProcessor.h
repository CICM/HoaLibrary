/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_DCBB15D8__
#define __PLUGINPROCESSOR_H_DCBB15D8__

#include "../JuceLibraryCode/JuceHeader.h"
#include "cicmTools.h"
#include "PluginParameter.h"
#include "GrainPlug.h"

//==============================================================================

class HoaSpaceAudioProcessor  :
    public AudioProcessor,
    public Value::Listener
{
public:
    //==============================================================================
    HoaSpaceAudioProcessor();
    ~HoaSpaceAudioProcessor();

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
        m_grainsize_parameter,
        m_delay_parameter,
        m_feedback_parameter,
        m_rarefaction_parameter,
        
        m_number_of_parameters
    };
    
    int         m_numberOfInputs;
    int         m_numberOfOutputs;
	//double*		f_amplitudeOfLoudspeakers;
    float      m_offset_of_loudspeakers;
    float      m_grainsize;
    float      m_delay;
    float      m_feedback;
    float      m_rarefaction;
    
    float*    m_inputVector[MAX_LOUDSPEAKERS];
    
private:
    GrainPlug*  GrainPlugProcessor;
    int         f_sampleframes;
    PluginParameter parameters[m_number_of_parameters];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaSpaceAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_DCBB15D8__
