/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __PLUGINEDITOR_H_INCLUDED__
#define __PLUGINEDITOR_H_INCLUDED__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "HoaMapComponent.h"
#include "HoaMeterComponent.h"

#ifdef __APPLE__

#include "PluginProcessor.h"

#elif _WINDOWS

#ifdef HOA_QUADRA
#include "..\HoaQuadra\Source\PluginProcessor.h"
#endif
#ifdef HOA_OCTO
#include "..\HoaOcto\Source\PluginProcessor.h"
#endif
#ifdef HOA_BINAURAL
#include "..\HoaBinaural\Source\PluginProcessor.h"
#endif
#ifdef HOA_FIVEDOTONE
#include "..\HoaFiveDotOne\Source\PluginProcessor.h"
#endif
#ifdef HOA_HEXA
#include "..\HoaHexa\Source\PluginProcessor.h"
#endif
#ifdef HOA_HEXADECA
#include "..\HoaHexaDeca\Source\PluginProcessor.h"
#endif

#endif




class HoaLabel : public Label
{
private:
    HoaToolsAudioProcessor* m_processor;
	AudioProcessorEditor*	m_master;
    HoaMapComponent*        m_map;
public:
    HoaLabel(AudioProcessorEditor* master, HoaToolsAudioProcessor* processor, HoaMapComponent* map)
    {
        m_processor = processor;
        m_master    = master;
        m_map       = map;
        setEditable(true, false, false);
        Label::setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
    }
    
    ~HoaLabel(){};
    
    void valueChanged (Value& nada)
    {
        Label::valueChanged(nada);
        setText(getText(), NotificationType::dontSendNotification);
    }
    
    void setText(const String& newText, const NotificationType notification)
    {
        m_processor->setNumberOfSources(newText.getIntValue());
        m_map->repaint();
        Label::setText(String((int)m_processor->getNumberOfSources()), notification);
    }
    
    void processorUpdated()
    {
        if(getText().getIntValue() != m_processor->getNumberOfSources())
            Label::setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
    }
};

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor
{
private:
    HoaToolsAudioProcessor* m_processor;

    HoaMapComponent*        m_map;
    HoaMeterComponent*      m_meter;
    Image                   m_logo_icon;
    HoaLabel*               m_value;
    
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
};


#endif
