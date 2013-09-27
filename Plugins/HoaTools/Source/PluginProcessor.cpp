
#include "PluginProcessor.h"
#include "PluginEditor.h"

HoaToolsAudioProcessor::HoaToolsAudioProcessor()
{
    m_processor         = new HoaProcessor();
    m_gui               = gui_mode_map;
}

HoaToolsAudioProcessor::~HoaToolsAudioProcessor()
{
    delete m_processor;
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
    return new HoaToolsAudioProcessorEditor(this, m_processor);
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
    return m_processor->getNumberOfSources() * 3;
}

float HoaToolsAudioProcessor::getParameter(int index)
{
    if(index == 0)
        return m_processor->getOrder();
    else
        return 1.;
    
    return 0.0f;
}

void HoaToolsAudioProcessor::setParameter(int index, float newValue)
{
    if(index == 0)
    {
        ;
    }
    if(index == 1)
    {
        ;
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
    else if(index == 1)
        return String("Number of sources Order");
    
    if(index % 2 == 0)
        return String("abscissa");
    else
        return String("ordiante");
}

String HoaToolsAudioProcessor::getParameterLabel(int index) const
{
    if(index == 0)
        return String();
    else if(index == 1)
        return String();
    else
        return String("bof");
}

bool HoaToolsAudioProcessor::isParameterAutomatable (int index) const
{
    if(index == 0)
        return false;
    else if(index == 1)
        return false;
    else
        return true;
}

bool HoaToolsAudioProcessor::isMetaParameter(int index) const
{
    if(index == 0)
        return true;
    else if(index == 1)
        return true;
    else
        return false;
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
    
    if(getNumInputChannels() < m_processor->getNumberOfSources())
        ;
    if(getNumOutputChannels() < m_processor->getNumberOfLoudspeakers())
    {
        ;
    }
    
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
    bool state = isSuspended();
    if(state)
        suspendProcessing(true);
    updateHostDisplay();
    if(state)
        suspendProcessing(false);
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    m_processor->prepareToPlay(sampleRate, samplesPerBlock);
}

void HoaToolsAudioProcessor::releaseResources()
{
    
}

void HoaToolsAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    m_processor->process(buffer.getArrayOfChannels());
    setNumberOfInputs(m_processor->getSourceManager()->getNumberOfSources());
    setNumberOfOutputs(m_processor->getNumberOfLoudspeakers());
    m_processor->postProcess();
}

/************************************************************************************/
/***************************** SAVE METHOD ******************************************/
/************************************************************************************/

void HoaToolsAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml("HoaToolsSettings");
    
    xml.setAttribute("Order", (int)m_processor->getOrder());    
    xml.setAttribute("NumberOfSources", (int)m_processor->getNumberOfSources());
    xml.setAttribute("NumberOfLoudspeakers", (int)m_processor->getNumberOfLoudspeakers());
    xml.setAttribute("OffsetOfLoudspeakers", (int)m_processor->getOffsetOfLoudspeakers());
    xml.setAttribute("Optimization", (int)m_processor->getOptimization());
    
    copyXmlToBinary(xml, destData);
}

void HoaToolsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName("HoaToolsSettings"))
        {
            m_processor->setOrder(xmlState->getIntAttribute("Order"));
            m_processor->setNumberOfSources(xmlState->getIntAttribute("NumberOfSources"));
            m_processor->setNumberOfLoudspeakers(xmlState->getIntAttribute("NumberOfLoudspeakers"));
            m_processor->setOffsetOfLoudspeakers(xmlState->getIntAttribute("OffsetOfLoudspeakers"));
            m_processor->setOptimization(xmlState->getIntAttribute("Optimization"));
            setNumberOfInputs(m_processor->getNumberOfSources());
            setNumberOfOutputs(m_processor->getNumberOfLoudspeakers());
        }
    }
}

/************************************************************************************/
/***************************** OTHER ************************************************/
/************************************************************************************/

const String HoaToolsAudioProcessor::getInputChannelName (int channelIndex) const
{
    char text[256];
    sprintf(text, "Source %i", channelIndex+1);
    return String(text);
}

const String HoaToolsAudioProcessor::getOutputChannelName (int channelIndex) const
{
    char text[256];
    sprintf(text, "Loudspeaker %i", channelIndex+1);
    return String(text);
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

