/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HoaMapAudioProcessor::HoaMapAudioProcessor()
{
    m_offset_of_loudspeakers    = 0;
    m_distance_of_loudspeakers  = 0.5;
    long anOrder = 1;
    m_number_of_loudspeakers = DEF_LOUDSPEAKERS;
    m_number_of_sources = DEF_SOURCES;
    if(m_number_of_loudspeakers%2 == 0)
        anOrder = m_number_of_loudspeakers / 2 - 1;
    else
        anOrder = m_number_of_loudspeakers / 2 - 0.5;
    
    m_ambisonic_tool    = new AmbisonicsMultiMaps(anOrder, m_number_of_sources);
    m_ambisonic_rotator = new AmbisonicsRotate(anOrder);
    m_ambisonic_decoder = new AmbisonicsDecoder(anOrder, m_number_of_loudspeakers);
    for(int i = 0; i < MAX_SOURCES; i++)
    {
        m_sources_abscissa[i] = 0;
        m_sources_ordinate[i] = 0;
    }
    
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        parameters[i].getValueObject().addListener(this);
    }
    parameters[0].init ("Offset", UnitDegrees, "Offset of the loudspeakers", 0, -180, 180, 0);
    parameters[1].init ("Distance", UnitGeneric, "Distance of the loudspeakers", 0.5, 0., 1., 0.5);
    
    for(int i = m_source_abscissa_1; i < m_number_of_parameters; i++)
    {
        if(i%2 == 0)
        {
            char name[256];
            char namo[256];
            sprintf(name, "Source %d X", i/2);
            sprintf(namo, "Abscissa of the source %d", i/2);
            parameters[i].init (name, UnitPan, namo, 0., -1., 1., 0);
        }
        else
        {
            char name[256];
            char namo[256];
            sprintf(name, "Source %d Y", (i-1)/2);
            sprintf(namo, "Ordinate of the source %d", (i-1)/2);
            parameters[i].init (name, UnitPan, namo, 0., -1., 1., 0.);
        }
    }
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        m_harmonics_vector_one[i] = new float[1];
        m_harmonics_vector_one[i] = NULL;
        m_harmonics_vector_two[i] = new float[1];
        m_harmonics_vector_two[i] = NULL;
    }
}

HoaMapAudioProcessor::~HoaMapAudioProcessor()
{
    for (int i = 0; i < m_number_of_parameters; i++)
    {
        parameters[i].getValueObject().removeListener (this);
    }
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        free(m_harmonics_vector_one[i]);
        free(m_harmonics_vector_two[i]);
    }
    delete m_ambisonic_tool;
    delete m_ambisonic_rotator;
    delete m_ambisonic_decoder;
}

//==============================================================================
const String HoaMapAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int HoaMapAudioProcessor::getNumParameters()
{
    return m_number_of_parameters;
}

float HoaMapAudioProcessor::getParameter(int index)
{
    return parameters[index].getNormalisedValue();
}

void HoaMapAudioProcessor::setParameter(int index, float newValue)
{
    parameters[index].setNormalisedValue(newValue);
    if(index == m_offset_of_loudspeakers_parameter)
    {
        m_offset_of_loudspeakers = parameters[m_distance_of_loudspeakers_parameter].getValue()*-1;
        m_ambisonic_rotator->setAzimuth(m_offset_of_loudspeakers / 360. * CICM_2PI);
    }
    else if(index == m_distance_of_loudspeakers_parameter)
    {
        m_distance_of_loudspeakers = parameters[m_distance_of_loudspeakers_parameter].getValue();
        if (m_distance_of_loudspeakers <= 0.0f) m_distance_of_loudspeakers = 0.00000001;
        for (int i = 0; i < getNumInputChannels(); i++) {
            m_ambisonic_tool->setCoordinatesCartesian(i, m_sources_abscissa[i] / m_distance_of_loudspeakers, m_sources_ordinate[i] / m_distance_of_loudspeakers);
        }
    }
    else if(index >= m_source_abscissa_1)
    {
        int coordIndex;
        if(coordIndex%2 == 0)
        {
            coordIndex = (index - m_source_abscissa_1)/2;
            m_sources_abscissa[coordIndex] = parameters[index].getValue();
            m_ambisonic_tool->setCoordinatesCartesian(coordIndex, parameters[index].getValue() / m_distance_of_loudspeakers, parameters[index+1].getValue() / m_distance_of_loudspeakers);
        }
        else
        {
            coordIndex = (index - m_source_abscissa_1 - 1)/2;
            m_sources_ordinate[coordIndex] = parameters[index].getValue();
            m_ambisonic_tool->setCoordinatesCartesian(coordIndex, parameters[index-1].getValue() / m_distance_of_loudspeakers, parameters[index].getValue() / m_distance_of_loudspeakers);
        }
    }
    //else if(index >= 2 && index < getNumParameters())
    /*
     else if(index >= m_source_abscissa_1)
     {
     int indexBis;
     if(index%2 == 0)
     {
     indexBis = ((index-2)/2);
     m_sources_abscissa[indexBis] = parameters[index].getValue();
     m_ambisonic_tool->setCartesianCoordinates(indexBis, parameters[index].getValue() / m_distance_of_loudspeakers, parameters[index+1].getValue() / m_distance_of_loudspeakers);
     }
     else
     {
     indexBis = ((index-3)/2);
     m_sources_ordinate[indexBis] = parameters[index].getValue();
     m_ambisonic_tool->setCartesianCoordinates(indexBis, parameters[index-1].getValue() / m_distance_of_loudspeakers, parameters[index].getValue() / m_distance_of_loudspeakers);
     }
     }
     */
}

//==============================================================================
float HoaMapAudioProcessor::getScaledParameter (int parameterIndex)
{
    return parameters[parameterIndex].getValue();
}

void HoaMapAudioProcessor::setScaledParameter (int parameterIndex, float newValue)
{
    parameters[parameterIndex].setValue (newValue);
}

float HoaMapAudioProcessor::getParameterMin (int parameterIndex)
{
    return parameters[parameterIndex].getMin();
}

float HoaMapAudioProcessor::getParameterMax (int parameterIndex)
{
    return parameters[parameterIndex].getMax();
}

float HoaMapAudioProcessor::getParameterDefault (int parameterIndex)
{
    return parameters[parameterIndex].getDefault();
}


const String HoaMapAudioProcessor::getParameterName (int index)
{
    return parameters[index].getName();
    return String::empty;
}

const String HoaMapAudioProcessor::getParameterText (int index)
{
    return parameters[index].getTextValueWithSuffix();
}

const String HoaMapAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String(channelIndex + 1);
}

const String HoaMapAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String(channelIndex + 1);
}

bool HoaMapAudioProcessor::isInputChannelStereoPair (int index) const
{
    return false;
}

bool HoaMapAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return false;
}

bool HoaMapAudioProcessor::isParameterAutomatable	(int parameterIndex) const
{
    return true;
}

bool HoaMapAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool HoaMapAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool HoaMapAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double HoaMapAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HoaMapAudioProcessor::getNumPrograms()
{
    return 0;
}

int HoaMapAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HoaMapAudioProcessor::setCurrentProgram (int index)
{
}

const String HoaMapAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void HoaMapAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void HoaMapAudioProcessor::numChannelsChanged()
{
    delete m_ambisonic_tool;
    delete m_ambisonic_rotator;
    delete m_ambisonic_decoder;
    long anOrder = 1;
    
    m_number_of_loudspeakers = getNumOutputChannels();
    m_number_of_sources = getNumInputChannels();
    Tools::clip((long)m_number_of_loudspeakers, (long)MIN_LOUDSPEAKERS, (long)MAX_LOUDSPEAKERS);
    Tools::clip((long)m_number_of_sources, (long)MIN_SOURCES, (long)MAX_SOURCES);
    
    if(m_number_of_loudspeakers%2 == 0)
        anOrder = m_number_of_loudspeakers / 2 - 1;
    else
        anOrder = m_number_of_loudspeakers / 2 - 0.5;
    
    m_ambisonic_tool = new AmbisonicsMultiMaps(anOrder, m_number_of_sources);
    m_ambisonic_rotator = new AmbisonicsRotate(anOrder);
    m_ambisonic_decoder = new AmbisonicsDecoder(anOrder, m_number_of_loudspeakers);
    
}
//==============================================================================
void HoaMapAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    numChannelsChanged();
    m_ambisonic_tool->setVectorSize(samplesPerBlock);
    m_ambisonic_rotator->setVectorSize(samplesPerBlock);
    m_ambisonic_decoder->setVectorSize(samplesPerBlock);
    for(int i = 0; i < MAX_LOUDSPEAKERS; i++)
    {
        if(m_harmonics_vector_one[i])
           free(m_harmonics_vector_one[i]);
        if(m_harmonics_vector_two[i])
            free(m_harmonics_vector_two[i]);
        m_harmonics_vector_one[i] = new float[samplesPerBlock];
        m_harmonics_vector_two[i] = new float[samplesPerBlock];
    }
}

void HoaMapAudioProcessor::releaseResources()
{
    ;
}

void HoaMapAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    float** channelArray = buffer.getArrayOfChannels();
    
    m_ambisonic_tool->process(channelArray, m_harmonics_vector_one);
    m_ambisonic_rotator->process(m_harmonics_vector_one, m_harmonics_vector_two);
    m_ambisonic_decoder->process(m_harmonics_vector_two, channelArray);
}

//==============================================================================
bool HoaMapAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* HoaMapAudioProcessor::createEditor()
{
    return new HoaMapAudioProcessorEditor (this);
}

//==============================================================================
void HoaMapAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    /*
     // Create an outer XML element..
     XmlElement xml ("HOA_EASE_PLUGINSETTINGS");
     
     // add some attributes to it..
     xml.setAttribute ("Offset", m_offset_of_loudspeakers);
     xml.setAttribute ("Distance", m_distance_of_loudspeakers);
     
     // then use this helper function to stuff it into the binary blob and return it..
     copyXmlToBinary (xml, destData);
     */
}

void HoaMapAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    /*
     ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
     
     if (xmlState != nullptr)
     {
     // make sure that it's actually our type of XML object..
     if (xmlState->hasTagName ("HOA_EASE_PLUGINSETTINGS"))
     {
     // ok, now pull out our parameters..
     m_offset_of_loudspeakers  = (float)  xmlState->getDoubleAttribute ("Offset", m_offset_of_loudspeakers);
     m_distance_of_loudspeakers = (float) xmlState->getDoubleAttribute ("Distance", m_distance_of_loudspeakers);
     
     //gain  = (float) xmlState->getDoubleAttribute ("gain", gain);
     //delay = (float) xmlState->getDoubleAttribute ("delay", delay);
     }
     }
     */
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaMapAudioProcessor();
}

//==============================================================================
void HoaMapAudioProcessor::valueChanged (Value& value)
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

PluginParameter& HoaMapAudioProcessor::getPluginParameter (int index)
{
    return parameters[index];
}
