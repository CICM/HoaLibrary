/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HoaMeterAudioProcessor::HoaMeterAudioProcessor()
{
    f_numberOfLoudspeakers = 8;
    f_amplitudeOfLoudspeakers = new double[f_numberOfLoudspeakers];
    for(int i = 0; i < f_numberOfLoudspeakers; i++)
        f_amplitudeOfLoudspeakers[i] = 0.000001;
    
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        parameters[i].getValueObject().addListener(this);
    }
    parameters[0].init ("Offset", UnitDegrees, "Offset of the loudspeakers", 0, -180, 180, 0);
}

HoaMeterAudioProcessor::~HoaMeterAudioProcessor()
{
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        parameters[i].getValueObject().removeListener (this);
    }
    delete [] f_amplitudeOfLoudspeakers;
}

//==============================================================================
const String HoaMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaMeterAudioProcessor::getNumParameters()
{
    return m_number_of_parameters;
}

float HoaMeterAudioProcessor::getParameter (int index)
{
    return parameters[index].getNormalisedValue();
}

void HoaMeterAudioProcessor::setParameter (int index, float newValue)
{
    parameters[index].setNormalisedValue(newValue);
    if(index == 0)
    {
        m_offset_of_loudspeakers = parameters[0].getValue();
    }
}

//==============================================================================
float HoaMeterAudioProcessor::getScaledParameter (int parameterIndex)
{
    return parameters[parameterIndex].getValue();
}

void HoaMeterAudioProcessor::setScaledParameter (int parameterIndex, float newValue)
{
    parameters[parameterIndex].setValue (newValue);
}

float HoaMeterAudioProcessor::getParameterMin (int parameterIndex)
{
    return parameters[parameterIndex].getMin();
}

float HoaMeterAudioProcessor::getParameterMax (int parameterIndex)
{
    return parameters[parameterIndex].getMax();
}

float HoaMeterAudioProcessor::getParameterDefault (int parameterIndex)
{
    return parameters[parameterIndex].getDefault();
}
//==============================================================================

const String HoaMeterAudioProcessor::getParameterName (int index)
{
    return parameters[index].getName();
}

const String HoaMeterAudioProcessor::getParameterText (int index)
{
    return parameters[index].getTextValueWithSuffix();
}

const String HoaMeterAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HoaMeterAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HoaMeterAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HoaMeterAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HoaMeterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HoaMeterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HoaMeterAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaMeterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaMeterAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaMeterAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaMeterAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaMeterAudioProcessor::changeProgramName (int index, const String& newName)
{
    
}

//==============================================================================
void HoaMeterAudioProcessor::numChannelsChanged()
{
    f_numberOfLoudspeakers = getNumInputChannels();
}
void HoaMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if (f_numberOfLoudspeakers != getNumInputChannels())
    {
        f_numberOfLoudspeakers = Tools::clip(getNumInputChannels(), MIN_LOUDSPEAKERS, MAX_LOUDSPEAKERS);
        delete [] f_amplitudeOfLoudspeakers;
        f_amplitudeOfLoudspeakers = new double[f_numberOfLoudspeakers];
        for(int i = 0; i < f_numberOfLoudspeakers; i++)
            f_amplitudeOfLoudspeakers[i] = 0.000001;
    }
    f_sampleframes = samplesPerBlock;
}

void HoaMeterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HoaMeterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int j;
    double max;
    
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);
        
        max = f_amplitudeOfLoudspeakers[channel];
        for(j = 0; j < f_sampleframes; j++)
        {
            if(fabs(channelData[j]) > fabs(max))
                max = channelData[j];
        }
        f_amplitudeOfLoudspeakers[channel] = max;
    }

    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool HoaMeterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HoaMeterAudioProcessor::createEditor()
{
    return new HoaMeterAudioProcessorEditor (this);
}

//==============================================================================
void HoaMeterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HoaMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaMeterAudioProcessor();
}

void HoaMeterAudioProcessor::resetAmplitude()
{
    for (int i = 0; i < f_numberOfLoudspeakers; i++) {
        f_amplitudeOfLoudspeakers[i] = 0.0000000001;
    }
}

//==============================================================================
void HoaMeterAudioProcessor::valueChanged (Value& value)
{
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        PluginParameter& currentParameter = parameters[i];
        if (value.refersToSameSourceAs(currentParameter.getValueObject()))
        {
            sendParamChangeMessageToListeners(i, currentParameter.getNormalisedValue());
        }
    }
}

PluginParameter& HoaMeterAudioProcessor::getPluginParameter (int index)
{
    return parameters[index];
}

