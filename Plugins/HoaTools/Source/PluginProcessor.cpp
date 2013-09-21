
#include "PluginProcessor.h"
#include "PluginEditor.h"

HoaToolsAudioProcessor::HoaToolsAudioProcessor()
{
    m_can_process = 0;
    m_order = 1;
    m_number_of_harmonics = 3;
    m_map               = new MapProcessor();
    m_decoder           = new DecoderProcessor();
    m_harmonics_matrix  = m_harmonics_matrix = new float*[3];
    m_gui               = gui_mode_map;
}

HoaToolsAudioProcessor::~HoaToolsAudioProcessor()
{
    delete m_map;
    delete m_decoder;
    free(m_harmonics_matrix);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaToolsAudioProcessor();
}

const String HoaToolsAudioProcessor::getName() const
{
    return String("HoaTools");
}

AudioProcessorEditor* HoaToolsAudioProcessor::createEditor()
{
    return new HoaToolsAudioProcessorEditor(this, m_map, m_decoder);
}

bool HoaToolsAudioProcessor::hasEditor() const
{
    return true;
}

/************************************************************************************/
/***************************** PARAMETERS *******************************************/
/************************************************************************************/

int HoaToolsAudioProcessor::getNumParameters()
{
    return m_map->getNumberOfSources() + m_decoder->getNumberOfLoudspeakers() +1;
}

float HoaToolsAudioProcessor::getParameter(int index)
{
    if(index == 0)
        return m_decoder->getOrder();
    else
        return 1.;
    
    return 0.0f;
}

void HoaToolsAudioProcessor::setParameter(int index, float newValue)
{
    if(index == 0)
    {
        suspendProcessing(1);
        m_decoder->setConfiguation(index, m_decoder->getNumberOfLoudspeakers());
        m_map->setConfiguation(index, m_map->getNumberOfSources());
    }    
}

float HoaToolsAudioProcessor::getParameterMin(int index)
{
    if(index == 0)
    {
        return 1;
    }
    return 0.;
}

float HoaToolsAudioProcessor::getParameterMax(int index)
{
    if(index == 0)
    {
        return 1;
    }
    return 1.;
}

float HoaToolsAudioProcessor::getParameterDefault(int index)
{
    return 0.3;
}

int HoaToolsAudioProcessor::getParameterNumSteps(int parameterIndex)
{
    
}

float HoaToolsAudioProcessor::getParameterDefaultValue (int parameterIndex)
{
    
}

const String HoaToolsAudioProcessor::getParameterName (int index)
{
    if(index == 0)
        return String("Ambisonic Order");
    if(index % 2 == 0)
        return String("abscissa");
    else
        return String("ordiante");
}

const String HoaToolsAudioProcessor::getParameterText (int index)
{
    if(index % 2 == 0)
        return String("relative");
    else
        return String("phase");
}

/************************************************************************************/
/***************************** PLAY *************************************************/
/************************************************************************************/


void HoaToolsAudioProcessor::numChannelsChanged()
{
    AudioProcessorEditor* Editor = NULL;
    
    if(getNumOutputChannels() % 2 == 0)
        m_order = getNumOutputChannels() / 2 - 1;
    else
        m_order = getNumOutputChannels() / 2;
    if(m_order < 1)
        m_order = 1;
    
    m_number_of_harmonics = 2 * m_order + 1;
    
    m_map->setConfiguation(m_order, getNumInputChannels());
    m_decoder->setConfiguation(m_order, getNumOutputChannels());
    
    if(m_harmonics_matrix)
        free(m_harmonics_matrix);
    m_harmonics_matrix = new float*[m_number_of_harmonics];
    
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
    
    updateHostDisplay();
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    numChannelsChanged();
    m_map->prepareToPlay(sampleRate, samplesPerBlock);
    m_decoder->prepareToPlay(sampleRate, samplesPerBlock);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_harmonics_matrix[i] = new float[samplesPerBlock];
    }
    m_can_process = 1;
    if(m_number_of_harmonics != m_map->getNumberOfHarmonics() || m_number_of_harmonics != m_decoder->getNumberOfHarmonics())
        m_can_process = 0;
    else if(getNumInputChannels() != m_map->getNumberOfSources() || getNumOutputChannels() != m_decoder->getNumberOfLoudspeakers())
        m_can_process = 0;
}

void HoaToolsAudioProcessor::releaseResources()
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        free(m_harmonics_matrix[i]);
    }
}

void HoaToolsAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    float** iovector = buffer.getArrayOfChannels();
    if(m_can_process)
    {
        m_map->process(iovector, m_harmonics_matrix);
        m_decoder->process(m_harmonics_matrix, iovector);
    }
    else
    {
        for(int i = 0; i < getNumOutputChannels(); i++)
        {
            for(int j = 0; j < buffer.getNumSamples(); j++)
            {
                iovector[i][j] = 0.;
            }
        }
    }
}

/************************************************************************************/
/***************************** SAVE METHOD ******************************************/
/************************************************************************************/

void HoaToolsAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml("HoaToolsSettings");
    
    xml.setAttribute("Order", (int)m_decoder->getOrder());
    xml.setAttribute("DecodingMode", 0);
    
    copyXmlToBinary (xml, destData);
}

void HoaToolsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName("HoaToolsSettings"))
        {
            m_decoder->setConfiguation(xmlState->getIntAttribute("uiWidth"), 1);
        }
    }
}

/************************************************************************************/
/***************************** OTHER ************************************************/
/************************************************************************************/

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

