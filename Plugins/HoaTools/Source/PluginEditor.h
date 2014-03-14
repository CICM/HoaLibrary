/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __PLUGINEDITOR_H_INCLUDED__
#define __PLUGINEDITOR_H_INCLUDED__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "HoaMap/MapComponent.h"
#include "HoaMeter/MeterComponent.h"
#include "PluginProcessor.h"
#include "HoaComponent.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public ComboBoxListener, public ButtonListener, public ValueListener
{
private:
    HoaToolsAudioProcessor* m_processor;
    HoaProcessor*           m_hoa_processor;

    MapEditor*              m_map;
    MeterEditor*            m_meter;
    
    ShapeButton*            m_switch;
    
    Label*                  m_order_text;
    Slider*                 m_order_menu;
    Value                   m_order;
    
    Label*                  m_sources_text;
    Slider*                 m_sources_menu;
    Value                   m_nunber_of_sources;
    
    Label*                  m_channels_text;
    Slider*                 m_channels_menu;
    Value                   m_nunber_of_channels;
    
    ComboBox*               m_decoder_menu;
    ComboBox*               m_optim_menu;
    Label*                  m_offset_text;
    Label*                  m_offset_menu;
    
    HoaLookAndFeel          LookAndFeel;
    Font                    HoaFont;
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, HoaProcessor* aHoaProcessor);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void comboBoxChanged(ComboBox* aComboBox);
    void buttonClicked(Button* aButton);
    void valueChanged(Value& aValue);
};


#endif
