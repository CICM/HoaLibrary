/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HoaScopeAudioProcessor::HoaScopeAudioProcessor()
{
}

HoaScopeAudioProcessor::~HoaScopeAudioProcessor()
{
}

//==============================================================================
const String HoaScopeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaScopeAudioProcessor::getNumParameters()
{
    return 0;
}

float HoaScopeAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void HoaScopeAudioProcessor::setParameter (int index, float newValue)
{
}

const String HoaScopeAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String HoaScopeAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String HoaScopeAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HoaScopeAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HoaScopeAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HoaScopeAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HoaScopeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HoaScopeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HoaScopeAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaScopeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaScopeAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaScopeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaScopeAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaScopeAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaScopeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HoaScopeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HoaScopeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HoaScopeAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

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
bool HoaScopeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HoaScopeAudioProcessor::createEditor()
{
    return new HoaScopeAudioProcessorEditor (this);
}

//==============================================================================
void HoaScopeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HoaScopeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaScopeAudioProcessor();
}
