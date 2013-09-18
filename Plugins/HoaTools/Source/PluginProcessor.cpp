
#include "PluginProcessor.h"
#include "PluginEditor.h"

HoaToolsAudioProcessor::HoaToolsAudioProcessor()
{
    m_map               = new MapProcessor();
    m_decoder           = new AmbisonicsMultiDecoder(1);
    m_harmonics_matrix  = NULL;
    numChannelsChanged();
}

HoaToolsAudioProcessor::~HoaToolsAudioProcessor()
{
    delete m_map;
    delete m_decoder;
}

//==============================================================================
const String HoaToolsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaToolsAudioProcessor::getNumParameters()
{
    return 0;
}

float HoaToolsAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void HoaToolsAudioProcessor::setParameter (int index, float newValue)
{
}

const String HoaToolsAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String HoaToolsAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String HoaToolsAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HoaToolsAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HoaToolsAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HoaToolsAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HoaToolsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HoaToolsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HoaToolsAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaToolsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaToolsAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaToolsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaToolsAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaToolsAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaToolsAudioProcessor::changeProgramName(int index, const String& newName)
{
    ;
}

void HoaToolsAudioProcessor::numChannelsChanged()
{
    long number_of_outputs  = getNumOutputChannels();
    long number_of_inputs   = getNumInputChannels();
    long order;
    if(number_of_outputs % 2 == 0)
        order = number_of_outputs / 2 - 1;
    else
        order = number_of_outputs / 2;
    
    if(number_of_outputs != m_decoder->getNumberOfLoudspeakers())
    {
        if(m_map)
            delete m_map;
        if(m_decoder)
            delete m_decoder;
        if(m_harmonics_matrix)
            free(m_harmonics_matrix);
        if(number_of_outputs > 3)
            m_decoder   = new AmbisonicsMultiDecoder(order, number_of_outputs, Hoa_Dec_Ambisonic, Hoa_Small, "", 512, 44100);
        else
            m_decoder   = new AmbisonicsMultiDecoder(order, number_of_outputs, Hoa_Dec_Irregular, Hoa_Small, "", 512, 44100);
        m_harmonics_matrix = new float*[order*2+1];
    }
    m_map->setNumberOfChannels(number_of_inputs, number_of_outputs);
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    numChannelsChanged();
    long order;
    if(getNumOutputChannels() % 2 == 0)
        order = getNumOutputChannels() / 2 - 1;
    else
        order = getNumOutputChannels() / 2;
    m_decoder->setSamplingRate(sampleRate);
    m_decoder->setVectorSize(samplesPerBlock);
    m_map->prepareToPlay(sampleRate, samplesPerBlock);
    for(int i = 0; i < order * 2 + 1; i++)
    {
        m_harmonics_matrix[i] = new float[samplesPerBlock];
    }
}

void HoaToolsAudioProcessor::releaseResources()
{
    long order;
    if(getNumOutputChannels() % 2 == 0)
        order = getNumOutputChannels() / 2 - 1;
    else
        order = getNumOutputChannels() / 2;
    for(int i = 0; i < order * 2 + 1; i++)
    {
        free(m_harmonics_matrix[i]);
    }
}

void HoaToolsAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    float** iovector = buffer.getArrayOfChannels();
    
    m_map->process(iovector, m_harmonics_matrix);
    m_decoder->process(m_harmonics_matrix, iovector);
}

// EDITOR BEHAVIOR //
AudioProcessorEditor* HoaToolsAudioProcessor::createEditor()
{
    return new HoaToolsAudioProcessorEditor(this, m_sources_manager);
}

bool HoaToolsAudioProcessor::hasEditor() const
{
    return true;
}

//==============================================================================
void HoaToolsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HoaToolsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaToolsAudioProcessor();
}
