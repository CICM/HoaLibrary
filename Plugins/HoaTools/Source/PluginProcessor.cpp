/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define DISTANCE_MAX 10

HoaToolsAudioProcessor::HoaToolsAudioProcessor() : KitSources()
{
    m_gui = gui_mode_map;
}

HoaToolsAudioProcessor::~HoaToolsAudioProcessor()
{
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
    // abscissa / ordinate / mute-state
    return getNumberOfSources() * 3;
}

float HoaToolsAudioProcessor::getParameter(int index)
{
    int param_index = index % 3;
    int source_index = index / 3;
    
    switch (param_index)
    {
        case 0:
            return Hoa::scale(sourceGetAbscissa(source_index), -DISTANCE_MAX, DISTANCE_MAX, 0, 1);
            break;
        case 1:
            return Hoa::scale(sourceGetOrdinate(source_index), -DISTANCE_MAX, DISTANCE_MAX, 0, 1);
            break;
        case 2:
            return sourceGetMute(source_index);
            break;
        default:
            return 0;
            break;
    }
}

void HoaToolsAudioProcessor::setParameter(int index, float newValue)
{
    int param_index = index % 3;
    int source_index = index / 3;
    
    switch (param_index)
    {
        case 0:
            sourceSetAbscissa(source_index, Hoa::scale(newValue, 0, 1, -DISTANCE_MAX, DISTANCE_MAX) );
            break;
        case 1:
            sourceSetOrdinate(source_index, Hoa::scale(newValue, 0, 1, -DISTANCE_MAX, DISTANCE_MAX) );
            break;
        case 2:
            sourceSetMute(source_index, newValue > 0.5);
            break;
        default:
            break;
    }
    
    // ??
    
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
    int param_index = index % 3;
    
    if(param_index == 0 || param_index == 1)
        return 0.5;
    else
        return 0;
}

int HoaToolsAudioProcessor::getParameterNumSteps(int index)
{
    int param_index = index % 3;
    
    if(param_index == 0 || param_index == 1)
        return 1000;
    else
        return 0;
}

float HoaToolsAudioProcessor::getParameterDefaultValue (int index)
{
    int param_index = index % 3;
    
    if(param_index == 0 || param_index == 1)
        return 0.5;
    else
        return 0;
}

const String HoaToolsAudioProcessor::getParameterName (int index)
{
    int param_index = index % 3;
    int source_index = index / 3;
    char text[256];
    
    switch (param_index)
    {
        case 0:
            sprintf(text, "Abscissa %i : ", source_index + 1);
            break;
        case 1:
            sprintf(text, "Ordinate %i : ", source_index + 1);
            break;
        case 2:
            sprintf(text, "Mute     %i : ", source_index + 1);
            break;
        default:
            sprintf(text, "");
            break;
    }
    
    return String(text);
}

String HoaToolsAudioProcessor::getParameterLabel(int index)
{
    int param_index = index % 3;
    int source_index = index / 3;
    char text[256];
    
    switch (param_index)
    {
        case 0:
        {
            sprintf(text, "%f", sourceGetAbscissa( source_index ));
            break;
        }
        case 1:
        {
            sprintf(text, "%f", sourceGetOrdinate( source_index ));
            break;
        }
        case 2:
        {
            if (sourceGetMute( source_index ))
                sprintf(text, "Muted");
            else
                sprintf(text, "Unmuted");
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
    int param_index = index % 3;
    int source_index = index / 3;
    char text[256];
    
    switch (param_index)
    {
        case 0:
        {
            sprintf(text, "%f", sourceGetAbscissa( source_index ));
            break;
        }
        case 1:
        {
            sprintf(text, "%f", sourceGetOrdinate( source_index ));
            break;
        }
        case 2:
        {
            if (sourceGetMute( source_index ))
                sprintf(text, "Muted");
            else
                sprintf(text, "Unmuted");
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
    if(getNumInputChannels() < getNumberOfSources())
    {
        setNumberOfSources(getNumInputChannels());
    }
    if(getNumOutputChannels() < getNumberOfChannels())
    {
        setNumberOfChannels(getNumOutputChannels());
    }
    if(isSuspended())
    {
        if(applyChanges())
        {
            setNumberOfInputs(getNumberOfSources());
            setNumberOfOutputs(getNumberOfChannels());
        }
    }
    
    if(getActiveEditor())
        getActiveEditor()->processorHasBeenUpdated();
    
    updateHostDisplay();
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	setSampleRate(sampleRate);
	setVectorSize(samplesPerBlock);
    if(applyChanges())
    {
        setNumberOfInputs(getNumberOfSources());
        setNumberOfOutputs(getNumberOfChannels());
        updateHostDisplay();
        if(getActiveEditor())
            getActiveEditor()->processorHasBeenUpdated();
    }
}

void HoaToolsAudioProcessor::releaseResources()
{
    
}

void HoaToolsAudioProcessor::processBlock(float** inputs, float** outputs)
{
    if(getNumOutputChannels() >= getNumberOfChannels() && getNumInputChannels() >= getNumberOfSources())
    {
        process((const float**)inputs, outputs);
    }
    if(applyChanges())
    {
        setNumberOfInputs(getNumberOfSources());
        setNumberOfOutputs(getNumberOfChannels());
        updateHostDisplay();
        if(getActiveEditor())
            getActiveEditor()->processorHasBeenUpdated();
    }
}

/************************************************************************************/
/***************************** SAVE METHOD ******************************************/
/************************************************************************************/

void HoaToolsAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml("HoaToolsSettings");
    
    xml.setAttribute("Order", (int)getOrder());
    xml.setAttribute("NumberOfSources", (int)getNumberOfSources());
    xml.setAttribute("NumberOfChannels", (int)getNumberOfChannels());
    xml.setAttribute("OffsetOfChannels", (int)getChannelsOffset());
    xml.setAttribute("Optimization", (int)getOptimMode());
    xml.setAttribute("Zoom", (double)getZoom());
    
    copyXmlToBinary(xml, destData);
}

void HoaToolsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName("HoaToolsSettings"))
        {
            setOrder(xmlState->getIntAttribute("Order"));
            setNumberOfSources(xmlState->getIntAttribute("NumberOfSources"));
            setNumberOfChannels(xmlState->getIntAttribute("NumberOfChannels"));
            setChannelsOffset(xmlState->getIntAttribute("OffsetOfChannels"));
            setOptimMode((Optim::Mode)xmlState->getIntAttribute("Optimization"));
            setZoom(xmlState->getDoubleAttribute("Zoom"));
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

