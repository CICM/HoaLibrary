/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HoaSpaceAudioProcessor::HoaSpaceAudioProcessor()
{
    m_numberOfInputs = 1;
    m_numberOfOutputs = 8;
    m_offset_of_loudspeakers = 0;
    m_grainsize = 100;
    m_delay = 1000;
    m_feedback = 0;
    m_rarefaction = 0;
    GrainPlugProcessor = new GrainPlug();
    
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        parameters[i].getValueObject().addListener(this);
    }
    parameters[m_offset_of_loudspeakers_parameter].init ("Offset", UnitDegrees, "Offset of the loudspeakers", m_offset_of_loudspeakers, -180, 180, m_offset_of_loudspeakers);
    parameters[m_grainsize_parameter].init ("GrainSize", UnitMilliseconds, "Size of Grain in ms", m_grainsize, 10, 2000, m_grainsize);
    parameters[m_delay_parameter].init ("Delay", UnitMilliseconds, "Delay Time in ms", m_delay, 0, 4000, m_delay);
    parameters[m_feedback_parameter].init ("Feedback", UnitPercent, "Feedback Factor in %", m_feedback, 0, 100, m_feedback);
    parameters[m_rarefaction_parameter].init ("Rarefaction", UnitPercent, "Rarefaction Factor in %", m_rarefaction, 0, 100, m_rarefaction);
    
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        m_inputVector[i] = new float[1];
    }
}

HoaSpaceAudioProcessor::~HoaSpaceAudioProcessor()
{
    for (int i = 0; i < m_number_of_parameters; i++)
        parameters[i].getValueObject().removeListener (this);
    if (GrainPlugProcessor) delete GrainPlugProcessor;
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        free(m_inputVector[i]);
    }
}

//==============================================================================
const String HoaSpaceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaSpaceAudioProcessor::getNumParameters()
{
    return m_number_of_parameters;
}

float HoaSpaceAudioProcessor::getParameter (int index)
{
    return parameters[index].getNormalisedValue();
}

void HoaSpaceAudioProcessor::setParameter (int index, float newValue)
{
    parameters[index].setNormalisedValue(newValue);
    switch (index) {
        case m_offset_of_loudspeakers_parameter:
        {
            m_offset_of_loudspeakers = parameters[index].getValue();
            break;
        }
        case m_grainsize_parameter:
        {
            m_grainsize = parameters[index].getValue();
            GrainPlugProcessor->setGrainSize(m_grainsize);
            break;
        }
        case m_delay_parameter:
        {
            m_delay = parameters[index].getValue();
            GrainPlugProcessor->setDelay(m_delay);
            break;
        }
        case m_feedback_parameter:
        {
            m_feedback = parameters[index].getValue();
            GrainPlugProcessor->setFeedback(m_feedback*0.01); // range 0 -> 1
            break;
        }
        case m_rarefaction_parameter:
        {
            m_rarefaction = parameters[index].getValue();
            GrainPlugProcessor->setRarefaction(m_rarefaction*0.01); // range 0 -> 1
            break;
        }
        default: break;
    }
}

//==============================================================================
float HoaSpaceAudioProcessor::getScaledParameter (int parameterIndex)
{
    return parameters[parameterIndex].getValue();
}

void HoaSpaceAudioProcessor::setScaledParameter (int parameterIndex, float newValue)
{
    parameters[parameterIndex].setValue (newValue);
}

float HoaSpaceAudioProcessor::getParameterMin (int parameterIndex)
{
    return parameters[parameterIndex].getMin();
}

float HoaSpaceAudioProcessor::getParameterMax (int parameterIndex)
{
    return parameters[parameterIndex].getMax();
}

float HoaSpaceAudioProcessor::getParameterDefault (int parameterIndex)
{
    return parameters[parameterIndex].getDefault();
}
//==============================================================================

const String HoaSpaceAudioProcessor::getParameterName (int index)
{
    return parameters[index].getName();
}

const String HoaSpaceAudioProcessor::getParameterText (int index)
{
    return parameters[index].getTextValueWithSuffix();
}

const String HoaSpaceAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HoaSpaceAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HoaSpaceAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HoaSpaceAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HoaSpaceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HoaSpaceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HoaSpaceAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaSpaceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaSpaceAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaSpaceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaSpaceAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaSpaceAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaSpaceAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HoaSpaceAudioProcessor::numChannelsChanged()
{
    m_numberOfInputs = getNumInputChannels();
    m_numberOfOutputs = getNumOutputChannels();
    GrainPlugProcessor->setOrderWithNumberOfLoudspeakers(m_numberOfOutputs);
    GrainPlugProcessor->setPlugIO(m_numberOfInputs, m_numberOfOutputs);
}

void HoaSpaceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    GrainPlugProcessor->setSampleRate(sampleRate);
    GrainPlugProcessor->setVectorSize(samplesPerBlock);
    f_sampleframes = samplesPerBlock;
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        free(m_inputVector[i]);
        m_inputVector[i] = new float[samplesPerBlock];
    }
    //GrainPlugProcessor->setPlugIO(m_numberOfInputs, m_numberOfOutputs);
}

void HoaSpaceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HoaSpaceAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    float** channelArray = buffer.getArrayOfChannels();
    
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
        for(int j = 0; j < f_sampleframes; j++)
            m_inputVector[channel][j] = channelArray[channel][j];
    
    GrainPlugProcessor->process(m_inputVector, getNumInputChannels(), channelArray, getNumOutputChannels());

    //GrainPlugProcessor->process(channelArray, getNumInputChannels(), channelArray, getNumOutputChannels());

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    /*
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    */
}

//==============================================================================
bool HoaSpaceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HoaSpaceAudioProcessor::createEditor()
{
    return new HoaSpaceAudioProcessorEditor (this);
}

//==============================================================================
void HoaSpaceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HoaSpaceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaSpaceAudioProcessor();
}

//==============================================================================
void HoaSpaceAudioProcessor::valueChanged (Value& value)
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

PluginParameter& HoaSpaceAudioProcessor::getPluginParameter (int index)
{
    return parameters[index];
}
