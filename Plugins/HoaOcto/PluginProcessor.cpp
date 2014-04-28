/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HoaOctoAudioProcessor::HoaOctoAudioProcessor()
{
}

HoaOctoAudioProcessor::~HoaOctoAudioProcessor()
{
}

//==============================================================================
const String HoaOctoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaOctoAudioProcessor::getNumParameters()
{
    return 0;
}

float HoaOctoAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void HoaOctoAudioProcessor::setParameter (int index, float newValue)
{
}

const String HoaOctoAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String HoaOctoAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String HoaOctoAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HoaOctoAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HoaOctoAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HoaOctoAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HoaOctoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HoaOctoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HoaOctoAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaOctoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaOctoAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaOctoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaOctoAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaOctoAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaOctoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HoaOctoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HoaOctoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HoaOctoAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool HoaOctoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HoaOctoAudioProcessor::createEditor()
{
    return new HoaOctoAudioProcessorEditor (this);
}

//==============================================================================
void HoaOctoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HoaOctoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaOctoAudioProcessor();
}
