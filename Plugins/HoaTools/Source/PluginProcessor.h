
#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap/MapComponent.h"
#include "HoaDecoder/DecoderComponent.h"
#include "HoaLookAndFeel.h"
#include "HoaComponent.h"

enum
{
    gui_mode_map = 0,
    gui_mode_meter,
};

class HoaToolsAudioProcessor  : public AudioProcessor, public ChangeBroadcaster
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaToolsAudioProcessor)
    
    long                        m_gui;
    HoaProcessor*               m_processor;
    
public:
    HoaToolsAudioProcessor();
    ~HoaToolsAudioProcessor();

    void numChannelsChanged();
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    long getGui(){return m_gui;};
    void setGui(long aMode){m_gui = aMode;};
    
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
    String getParameterLabel(int index) const;
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
