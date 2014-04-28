/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __PLUGINEDITOR_H_INCLUDED__
#define __PLUGINEDITOR_H_INCLUDED__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "HoaMap/HoaMapComponent.h"
#include "HoaMeter/HoaMeterComponent.h"
#include "PluginProcessor.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public Label::Listener
{
private:
    HoaToolsAudioProcessor* m_processor;

    HoaMapComponent*        m_map;
    HoaMeterComponent*      m_meter;
    Image                   m_logo_icon;
    Label*                  m_label;
    Label*					m_value;
    
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void labelTextChanged (Label* label);
};


#endif
