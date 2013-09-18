
#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../Sources/HoaLibrary.h"
#include "HoaMap/MapProcessor.h"

class HoaToolsAudioProcessor  : public AudioProcessor
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaToolsAudioProcessor)
    float**                     m_harmonics_matrix;
    MapProcessor*   m_map;
    AmbisonicsMultiDecoder*     m_decoder;
    
public:
    HoaToolsAudioProcessor();
    ~HoaToolsAudioProcessor();

    void numChannelsChanged();
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    
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

    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
