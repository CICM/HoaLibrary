/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    return getNumberOfSources() * 3;
}

float HoaToolsAudioProcessor::getParameter(int index)
{
    if((index + 1) % 3 == 0)
        return sourceGetMute(index / 3);
    else if((index + 2) % 3 == 0)
        return sourceGetOrdinate(index / 3) / 20. + 0.5;
    else
        return sourceGetAbscissa(index / 3) / 20. +  0.5;
}

void HoaToolsAudioProcessor::setParameter(int index, float newValue)
{
    if((index + 1) % 3 == 0)
    {
        newValue += 0.5;
        sourceSetMute(index / 3, newValue);
    }
    else if((index + 2) % 3 == 0)
        sourceSetOrdinate(index / 3, (newValue - 0.5) * 20.);
    else
        sourceSetAbscissa(index / 3, (newValue - 0.5) * 20.);
    
    AudioProcessorEditor* Editor = NULL;
    Editor = getActiveEditor();
    if(Editor)
        Editor->repaint();
}

float HoaToolsAudioProcessor::getParameterMin(int index)
{
    if((index + 1) % 3 == 0)
        return 0;
    else if((index + 2) % 3 == 0)
        return -10.;
    else
        return -10.;
}

float HoaToolsAudioProcessor::getParameterMax(int index)
{
    if((index + 1) % 3 == 0)
        return 1;
    else if((index + 2) % 3 == 0)
        return 10.;
    else
        return 10.;
}

float HoaToolsAudioProcessor::getParameterDefault(int index)
{
    if((index + 1) % 3 == 0)
        return 0;
    else if((index + 2) % 3 == 0)
        return 0.;
    else
        return 0.;
}

int HoaToolsAudioProcessor::getParameterNumSteps(int index)
{
    if((index + 1) % 3 == 0)
        return 1;
    else if((index + 2) % 3 == 0)
        return 0.001;
    else
        return 0.001;
}

float HoaToolsAudioProcessor::getParameterDefaultValue (int index)
{
    if((index + 1) % 3 == 0)
        return 0;
    else if((index + 2) % 3 == 0)
        return 0.;
    else
        return 0.;
}

const String HoaToolsAudioProcessor::getParameterName (int index)
{
    char text[256];
    if((index + 1) % 3 == 0)
        sprintf(text, "Mute     %i : ", index / 3 + 1);
    else if((index + 2) % 3 == 0)
        sprintf(text, "Ordinate %i : ", index / 3 + 1);
    else
        sprintf(text, "Abscissa %i : ", index / 3 + 1);
       
    return String(text);
}

String HoaToolsAudioProcessor::getParameterLabel(int index)
{
    char text[256];
    if((index + 1) % 3 == 0)
    {
        if (sourceGetMute(index / 3))
            sprintf(text, "Muted");
        else
           sprintf(text, "Unmuted"); 
        
    }
    else if((index + 2) % 3 == 0)
        sprintf(text, "%f", sourceGetOrdinate(index / 3));
    else
        sprintf(text, "%f", sourceGetAbscissa(index / 3));
    
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
    char text[256];
    if((index + 1) % 3 == 0)
    {
        if (sourceGetMute(index / 3))
            sprintf(text, "Muted");
        else
            sprintf(text, "Unmuted");
        
    }
    else if((index + 2) % 3 == 0)
        sprintf(text, "%f", sourceGetOrdinate(index / 3));
    else
        sprintf(text, "%f", sourceGetAbscissa(index / 3));
    
    return String(text);
}

/************************************************************************************/
/***************************** PLAY *************************************************/
/************************************************************************************/


void HoaToolsAudioProcessor::numChannelsChanged()
{
    if(getNumInputChannels() >= getNumberOfSources() && getNumOutputChannels() >= getNumberOfChannels())
    {
        suspendProcessing(false);
        if(getActiveEditor())
            getActiveEditor()->processorHasBeenUpdated();
    }
}

void HoaToolsAudioProcessor::applySettingChanges()
{
    if(isSuspended())
    {
        applyChanges();
        setNumberOfInputs(getNumberOfSources());
        setNumberOfOutputs(getNumberOfChannels());
    }
    else
    {
        suspendProcessing(true);
    }
}

void HoaToolsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	setSampleRate(sampleRate);
	setVectorSize(samplesPerBlock);
}

void HoaToolsAudioProcessor::processBlock(int numins, int numouts, float** inputs, float** outputs, int size)
{
    if(isSuspended())
    {
        for(int i = 0; i < numouts; i++)
            memset(outputs, 0, size * sizeof(float));
        
        applySettingChanges();
    }
    else if(numouts >= getNumberOfChannels() && numins >= getNumberOfSources())
        process((const float**)inputs, outputs);
    else
         applySettingChanges();
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
            applySettingChanges();
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

