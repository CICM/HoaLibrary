/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define DISTANCE_MAX 10

HoaToolsAudioProcessor::HoaToolsAudioProcessor()
{
    m_number_of_sources = 2;
    m_sources   = new SourcesManager(DISTANCE_MAX);
    for(int i = 0; i < 16; i++)
        m_sources->sourceRemove(i);
    
    m_map       = new Map(3, 16);
    m_optim     = new Optim(3);
    m_decoder   = new DecoderRegular(3, 8);
    m_meter     = new Meter(8);
    m_lines     = new PolarLines(16);
   
    m_lines->setRamp(4410);
    m_meter->setChannelsOffset(0.125 * HOA_PI);
    m_decoder->setChannelsOffset(0.125 * HOA_PI);
    m_optim->setMode(Hoa2D::Optim::InPhase);
    
    m_input_vector = new float[16 * 8192];
    m_harmo_vector = new float[7 * 8192];
    m_output_vector= new float[8 * 8192];
    m_lines_vector = new float[32];
    setNumberOfSources(2);
    
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
}

HoaToolsAudioProcessor::~HoaToolsAudioProcessor()
{
    delete m_sources;
    delete m_map;
    delete m_optim;
    delete m_decoder;
    delete [] m_input_vector;
    delete [] m_output_vector;
    delete [] m_harmo_vector;
    delete [] m_lines_vector;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HoaToolsAudioProcessor();
}

const String HoaToolsAudioProcessor::getName() const
{
    return String("HoaOcto");
}

AudioProcessorEditor* HoaToolsAudioProcessor::createEditor()
{
    return new HoaToolsAudioProcessorEditor(this);
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
    return 2 * 16;
}

float HoaToolsAudioProcessor::getParameter(int index)
{
    int param_index = index % 2;
    int source_index = index / 2;
    
    switch (param_index)
    {
        case 0:
            return Hoa::scale(m_sources->sourceGetAbscissa(source_index), -DISTANCE_MAX, DISTANCE_MAX, 0, 1);
            break;
        case 1:
            return Hoa::scale(m_sources->sourceGetOrdinate(source_index), -DISTANCE_MAX, DISTANCE_MAX, 0, 1);
            break;
        default:
            return 0;
            break;
    }
}

void HoaToolsAudioProcessor::setParameter(int index, float newValue)
{
    int param_index = index % 2;
    int source_index = index / 2;
    
    switch (param_index)
    {
        case 0:
            m_sources->sourceSetAbscissa(source_index, Hoa::scale(newValue, 0, 1, -DISTANCE_MAX, DISTANCE_MAX) );
            break;
        case 1:
            m_sources->sourceSetOrdinate(source_index, Hoa::scale(newValue, 0, 1, -DISTANCE_MAX, DISTANCE_MAX) );
            break;
        default:
            break;
    }
    
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
}

float HoaToolsAudioProcessor::getParameterMin(int index)
{
    return 0.;
}

float HoaToolsAudioProcessor::getParameterMax(int index)
{
    return 1;
}

float HoaToolsAudioProcessor::getParameterDefault(int index)
{
    return 0.5;
}

int HoaToolsAudioProcessor::getParameterNumSteps(int index)
{
    return 1000;
}

float HoaToolsAudioProcessor::getParameterDefaultValue (int index)
{
    return 0.5;
}

const String HoaToolsAudioProcessor::getParameterName (int index)
{
    int param_index = index % 2;
    int source_index = index / 2;
    char text[256];
    
    switch (param_index)
    {
        case 0:
            sprintf(text, "Abscissa %i : ", source_index + 1);
            break;
        case 1:
            sprintf(text, "Ordinate %i : ", source_index + 1);
            break;
        default:
            sprintf(text, "");
            break;
    }
    
    return String(text);
}

String HoaToolsAudioProcessor::getParameterLabel(int index)
{
    int param_index = index % 2;
    int source_index = index / 2;
    char text[256];
    
    switch (param_index)
    {
        case 0:
        {
            sprintf(text, "%.2f", m_sources->sourceGetAbscissa( source_index ));
            break;
        }
        case 1:
        {
            sprintf(text, "%.2f", m_sources->sourceGetOrdinate( source_index ));
            break;
        }
        default:
            sprintf(text, "");
            break;
    }
    return String(text);
}

bool HoaToolsAudioProcessor::isParameterAutomatable (int index) const
{
    return true;
}

bool HoaToolsAudioProcessor::isMetaParameter(int index) const
{
    return false;
}

const String HoaToolsAudioProcessor::getParameterText (int index)
{
    int param_index = index % 2;
    int source_index = index / 2;
    char text[256];
    
    switch (param_index)
    {
        case 0:
        {
            sprintf(text, "%.2f", m_sources->sourceGetAbscissa( source_index ));
            break;
        }
        case 1:
        {
            sprintf(text, "%.2f", m_sources->sourceGetOrdinate( source_index ));
            break;
        }
        default:
            sprintf(text, "");
            break;
    }
    return String(text);
}

/************************************************************************************/
/***************************** PLAY *************************************************/
/************************************************************************************/


void HoaToolsAudioProcessor::numChannelsChanged()
{
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
    
    updateHostDisplay();
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	m_vector_size = samplesPerBlock;
    
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
}

void HoaToolsAudioProcessor::releaseResources()
{
    
}

void HoaToolsAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int i;
    int numins = getNumInputChannels();
    int numouts = getNumOutputChannels();
    int nharmo = 7;
    float* channelData;

    for(i = 0; i < numins && i < m_number_of_sources; i++)
    {
        channelData = buffer.getWritePointer(i);
        cblas_scopy(m_vector_size, channelData, 1, m_input_vector+i, numins);
        m_lines->setRadius(i, m_sources->sourceGetRadius(i));
        m_lines->setAzimuth(i, m_sources->sourceGetAzimuth(i));
    }
    for(i = 0; i < m_vector_size; i++)
    {
        m_lines->process(m_lines_vector);
        for(int j = 0; j < numins && j < m_number_of_sources; j++)
            m_map->setRadius(j, m_lines_vector[j]);
        for(int j = 0; j < numins && j < m_number_of_sources; j++)
            m_map->setAzimuth(j, m_lines_vector[j+numins]);
        
        m_map->process(m_input_vector+ numins * i, m_harmo_vector + nharmo * i);
        m_optim->process(m_harmo_vector + nharmo * i, m_harmo_vector + nharmo * i);
        m_decoder->process(m_harmo_vector + nharmo * i, m_output_vector + numouts * i);
        m_meter->process(m_output_vector + numouts * i);
    }
    for(i = 0; i < numouts; i++)
    {
        channelData = buffer.getWritePointer(i);
        cblas_scopy(m_vector_size, m_output_vector+i, numouts, channelData, 1);
    }
}

/************************************************************************************/
/***************************** SAVE METHOD ******************************************/
/************************************************************************************/

void HoaToolsAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    setNumberOfSources(2);
}

void HoaToolsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    setNumberOfSources(2);
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
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
    sprintf(text, "Channel %i", channelIndex+1);
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

HoaToolsAudioProcessor::PolarLines::PolarLines(unsigned int numberOfSources)
{
    assert(numberOfSources > 0);
    m_number_of_sources = numberOfSources;
    
    m_values_old    = new float[m_number_of_sources * 2];
    m_values_new    = new float[m_number_of_sources * 2];
    m_values_step   = new float[m_number_of_sources * 2];
}

HoaToolsAudioProcessor::PolarLines::~PolarLines()
{
    delete [] m_values_old;
    delete [] m_values_new;
    delete [] m_values_step;
}

void HoaToolsAudioProcessor::PolarLines::setRamp(unsigned int ramp)
{
    m_ramp = clip_min(ramp, (long)1);
}

void HoaToolsAudioProcessor::PolarLines::setRadius(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_new[index]  = radius;
    m_values_step[index] = (m_values_new[index] - m_values_old[index]) / (double)m_ramp;
    m_counter = 0;
}

void HoaToolsAudioProcessor::PolarLines::setAzimuth(unsigned int index, double azimuth)
{
    assert(index < m_number_of_sources);
    double new_value = wrap_twopi(azimuth);
    double old_value = wrap_twopi(m_values_old[index + m_number_of_sources]);
    double distance;
    
    
    if(old_value > new_value)
        distance = old_value - new_value;
    else
        distance = new_value - old_value;
    
    if(distance > HOA_PI && new_value > old_value)
        new_value -= HOA_2PI;
    else if(distance > HOA_PI)
        new_value += HOA_2PI;
    
    m_values_new[index + m_number_of_sources] = new_value;
    m_values_step[index + m_number_of_sources] = (new_value - old_value) / (double)m_ramp;
    m_counter = 0;
}

void HoaToolsAudioProcessor::PolarLines::setRadiusDirect(unsigned int index, double radius)
{
    assert(index < m_number_of_sources);
    m_values_old[index] = m_values_new[index] = radius;
    m_values_step[index] = 0.;
    m_counter = 0;
}

void HoaToolsAudioProcessor::PolarLines::setAzimuthDirect(unsigned int index, double azimuth)
{
    assert(index < m_number_of_sources);
    m_values_old[index + m_number_of_sources] = m_values_new[index + m_number_of_sources] = azimuth;
    m_values_step[index + m_number_of_sources] = 0.;
    m_counter = 0;
}

void HoaToolsAudioProcessor::PolarLines::process(float* vector)
{
    cblas_saxpy(m_number_of_sources * 2, 1., m_values_step, 1, m_values_old, 1);
    if(m_counter++ >= m_ramp)
    {
        cblas_scopy(m_number_of_sources * 2, m_values_new, 1, m_values_old, 1);
        memset(m_values_step, 0, sizeof(float) * m_number_of_sources * 2);
        m_counter    = 0;
    }
    cblas_scopy(m_number_of_sources * 2, m_values_old, 1, vector, 1);
}


