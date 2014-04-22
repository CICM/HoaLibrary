/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef _HOA_SETTINGS_COMPONENT_
#define _HOA_SETTINGS_COMPONENT_

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "PluginProcessor.h"
#include "HoaTextEditor.h"

class HoaSettingsComponent : public Component, public ComboBox::Listener, public Label::Listener
{
private:
    HoaComponentListener*   m_master;
    HoaToolsAudioProcessor* m_processor;
    
    Image                   m_settings_icon;
	
    Label*                  m_order_label;
    Label*					m_order_value;
    Label*                  m_decoder_label;
	ComboBox*               m_decoder_value;
    Label*                  m_optim_label;
	ComboBox*               m_optim_value;
	Label*                  m_number_of_sources_label;
    Label*					m_number_of_sources_value;
	Label*                  m_number_of_channels_label;
    Label*					m_number_of_channels_value;
	Label*                  m_offset_label;
    Label*					m_offset_value;
	
    Label*					m_channels_azimuth_label;
    std::vector<Label*>		m_channels_azimuth_values;
    std::vector<Label*>		m_channels_azimuth_labels;
    
    Label*                  m_pinna_label;
    ComboBox*               m_pinna_value;
    
public:
    HoaSettingsComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor);
    ~HoaSettingsComponent();
    
    void updated();
    void paint(Graphics&);
    void mouseDown(const MouseEvent &event);
    void comboBoxChanged(ComboBox* aComboBox);
	
	void labelTextChanged (Label* label);
};


#endif