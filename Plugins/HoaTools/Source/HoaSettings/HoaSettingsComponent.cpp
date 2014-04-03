/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaSettingsComponent.h"

static char hoa_settings_label[] = "Settings";

HoaSettingsComponent::HoaSettingsComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor)
{
    m_master    = master;
    m_processor = processor;
    
    m_settings_icon = ImageCache::getFromMemory(BinaryData::icongear256_png, BinaryData::icongear256_pngSize);
    
    m_setting_label = new Label();
    m_setting_label->setText("Settings", juce::dontSendNotification);
    
    m_label_settings = new Label();
    m_label_settings->setText("Settings", juce::dontSendNotification);
   

	// -- optimization
	
	m_optim_label = new Label();
    m_optim_label->setText("Optimization", juce::dontSendNotification);
	
    m_optim_value = new ComboBox();
    m_optim_value->setEditableText(false);
    m_optim_value->setJustificationType(Justification::centredLeft);
    m_optim_value->addItem("Basic", 1);
    m_optim_value->addItem("MaxRe", 2);
    m_optim_value->addItem("InPhase", 3);
    m_optim_value->addListener(this);
    m_optim_value->setSelectedId(m_processor->getOptimMode() + 1);

	// -- decoder
	
	m_decoder_label = new Label();
    m_decoder_label->setText("Decoding Mode", juce::dontSendNotification);
	
    m_decoder_value = new ComboBox();
    m_decoder_value->setEditableText(false);
    m_decoder_value->setJustificationType(Justification::centredLeft);
    m_decoder_value->addItem("Ambisonic", 1);
    m_decoder_value->addItem("Irregular", 2);
    m_decoder_value->addItem("Binaural", 3);
    m_decoder_value->addListener(this);
    m_decoder_value->setSelectedId(m_processor->getDecodingMode() + 1);
	
	
    // -- sources
	
	m_number_of_sources_label = new Label();
    m_number_of_sources_label->setText("Number of Sources", juce::dontSendNotification);
	
    m_number_of_sources_value = new Label();
	m_number_of_sources_value->setEditable(true, false, false);
    m_number_of_sources_value->setText(String(m_processor->getNumberOfSources()), juce::dontSendNotification);
	m_number_of_sources_value->addListener(this);
	
    // -- ordre
    
    m_ordre_label = new Label();
    m_ordre_label->setText("Order", juce::dontSendNotification);
	
    m_ordre_value = new Label();
	m_ordre_value->setEditable(true, false, false);
	m_ordre_value->setText(String(m_processor->getOrder()), juce::dontSendNotification);
	m_ordre_value->addListener(this);

	// -- channels
	
	m_number_of_channels_label = new Label();
    m_number_of_channels_label->setText("Number of Loudspeakers", juce::dontSendNotification);
	
    m_number_of_channels_value = new Label();
	m_number_of_channels_value->setEditable(true, false, false);
	m_number_of_channels_value->setText(String(m_processor->getNumberOfChannels()), juce::dontSendNotification);
	m_number_of_channels_value->addListener(this);
    
    
	// -- offset -- //
	
	m_offset_label = new Label();
    m_offset_label->setText("Offset", juce::dontSendNotification);
	
    m_offset_value = new Label();
	m_offset_value->setEditable(true, false, false);
	m_offset_value->setText(String(m_processor->getChannelsOffset()), juce::dontSendNotification);
    m_offset_value->addListener(this);
	
	// -- channels angles -- //
	
    m_channels_azimuth_label = new Label();
    m_channels_azimuth_label->setText("Angle of Loudspeakers", juce::dontSendNotification);
	
	for (int i = 0; i < m_processor->getNumberOfChannels(); i++)
	{
		Label* newLabel = new Label();
		newLabel->setEditable(true, false, false);
		newLabel->setText(String(0), juce::dontSendNotification);
		newLabel->addListener(this);
		m_channels_azimuth_values.push_back(newLabel);
	}
}

HoaSettingsComponent::~HoaSettingsComponent()
{
	//m_number_of_channels_value->removeListener(this);
    delete m_label_settings;
    delete m_optim_value;
    delete m_optim_label;
    delete m_decoder_value;
    delete m_decoder_label;
    delete m_number_of_sources_value;
    delete m_number_of_sources_label;
    delete m_ordre_label;
    delete m_ordre_value;
    delete m_number_of_channels_value;
    delete m_number_of_channels_label;
    delete m_offset_value;
    delete m_offset_label;
    delete m_channels_azimuth_label;
    m_channels_azimuth_values.clear();
}

void HoaSettingsComponent::comboBoxChanged(ComboBox* comboBox)
{
    if(comboBox == m_optim_value)
    {
        m_processor->setOptimMode(static_cast<Optim::Mode>(m_optim_value->getSelectedId() - 1));
        
    }
	else if(comboBox == m_decoder_value)
    {
        m_processor->setDecodingMode(static_cast<DecoderMulti::Mode>(m_decoder_value->getSelectedId() - 1));
        m_number_of_channels_value->setText(String((int)m_processor->getNumberOfChannels()), juce::dontSendNotification);
        
        // Ajouter des boites //
        for (int i = m_channels_azimuth_values.size(); i < m_processor->getNumberOfChannels(); i++)
		{
            m_channels_azimuth_values.push_back(new Label());
			m_channels_azimuth_values[i]->setEditable(true, false, false);
			m_channels_azimuth_values[i]->setText(String(0), juce::dontSendNotification);
			m_channels_azimuth_values[i]->addListener(this);
		}
        
        // Supprimer des boites //
		for (int i = m_channels_azimuth_values.size(); i > m_processor->getNumberOfChannels(); i--)
		{
            m_channels_azimuth_values[i-1]->removeListener(this);
			removeChildComponent(m_channels_azimuth_values[i-1]);
            m_channels_azimuth_values.pop_back();
		}
        
        for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
            m_channels_azimuth_values[i]->setText(String((int)3.14), juce::dontSendNotification);
        
        m_master->componentRedrawMeter();
        
        if(m_processor->getDecodingMode() == DecoderMulti::Binaural)
        {
            m_offset_value->setEnabled(0);
            m_number_of_channels_value->setEnabled(0);
            for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
                m_channels_azimuth_values[i]->setEnabled(0);
        }
        else if(m_processor->getDecodingMode() == DecoderMulti::Regular)
        {
            m_number_of_channels_value->setEnabled(1);
            for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
                m_channels_azimuth_values[i]->setEnabled(0);
        }
        else if(m_processor->getDecodingMode() == DecoderMulti::Irregular)
        {
            m_number_of_channels_value->setEnabled(1);
            for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
                m_channels_azimuth_values[i]->setEnabled(1);
        }
    }
}

void HoaSettingsComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < PLUG_MENU_WIDTH)
    {
        m_master->componentHasBeenClicked(this);
		return;
    }
}

void HoaSettingsComponent::paint(Graphics& g)
{
    if(getWidth() < PLUG_MENU_WIDTH)
    {
        removeChildComponent(m_label_settings);
        removeChildComponent(m_optim_value);
        removeChildComponent(m_optim_label);
        removeChildComponent(m_decoder_value);
        removeChildComponent(m_decoder_label);
		
        addAndMakeVisible(m_setting_label);
        m_setting_label->setBounds(7, 80, getWidth() * 1.2, 60);
        
        
        g.drawImage(m_settings_icon, 25, 25, PLUG_MENU_WIDTH, PLUG_MENU_WIDTH, 0, 0, m_settings_icon.getWidth() * 1.8, m_settings_icon.getHeight() * 1.8);
    }
    else
    {
		
		m_processor->setNumberOfChannels(8);
		
        addAndMakeVisible(m_label_settings);
        m_label_settings->setBounds(5, 10, getWidth() * 0.5 - 10, 14);

        g.setColour(Colours::darkgrey);
        g.drawLine(0, 50, 495, 50);
        
        g.setColour(Colours::black);
        addAndMakeVisible(m_optim_value);
        m_optim_value->setBounds(getWidth() * 0.5, 60, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_optim_label);
        m_optim_label->setBounds(10, 60, getWidth() * 0.5 - 10, 20);
        
		addAndMakeVisible(m_decoder_label);
        m_decoder_label->setBounds(10, 85, getWidth() * 0.5 - 10, 20);
		
        addAndMakeVisible(m_decoder_value);
        m_decoder_value->setBounds(getWidth() * 0.5, 85, getWidth() * 0.5 - 10, 20);
        
        g.setColour(Colours::grey);
        g.drawLine(0, 130, 495, 130);
    
        g.setColour(Colours::black);
        addAndMakeVisible(m_number_of_sources_label);
        m_number_of_sources_label->setBounds(80, 150, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_number_of_sources_value);
        m_number_of_sources_value->setBounds(280, 150, 40, 20);
        
        addAndMakeVisible(m_ordre_label);
        m_ordre_label->setBounds(80, 190, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_ordre_value);
        m_ordre_value->setBounds(280, 190, 40, 20);

        addAndMakeVisible(m_number_of_channels_label);
        m_number_of_channels_label->setBounds(80, 230, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_number_of_channels_value);
        m_number_of_channels_value->setBounds(280, 230, 40, 20);
		
        addAndMakeVisible(m_offset_label);
        m_offset_label->setBounds(80, 270, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_offset_value);
        m_offset_value->setBounds(280, 270, 40, 20);

        addAndMakeVisible(m_channels_azimuth_label);
        m_channels_azimuth_label->setBounds(10, 320, getWidth() * 0.5 - 10, 20);
        
        for (int i = 0; i < m_channels_azimuth_values.size(); i++)
        {
            int index_line = i / 12;
            int index_column = i - index_line * 12;
			addAndMakeVisible(m_channels_azimuth_values[i]);
            m_channels_azimuth_values[i]->setBounds(index_column * 45 + 2.5, index_line * 25 + 340, 40, 20);
        }
    }
}


void HoaSettingsComponent::labelTextChanged (Label* label)
{
	double value = label->getText().getDoubleValue();
	
	if (label == m_number_of_sources_value)
	{
		m_processor->setNumberOfSources(clip_minmax(value, 1, 32));
        m_number_of_sources_value->setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
        m_master->componentRedrawMap();
	}
    else if(label == m_ordre_value)
    {
        m_processor->setOrder(clip_minmax(value, 2, 64));
        m_ordre_value->setText(String((int)m_processor->getOrder()), juce::dontSendNotification);
    }
	else if (label == m_number_of_channels_value)
	{
		m_processor->setNumberOfChannels(clip_minmax(value, 2, 32));
        m_number_of_channels_value->setText(String((int)m_processor->getNumberOfChannels()), juce::dontSendNotification);
        
        // Ajouter des boites //
        for (int i = m_channels_azimuth_values.size(); i < m_processor->getNumberOfChannels(); i++)
		{
            m_channels_azimuth_values.push_back(new Label());
			m_channels_azimuth_values[i]->setEditable(true, false, false);
			m_channels_azimuth_values[i]->setText(String(0), juce::dontSendNotification);
			m_channels_azimuth_values[i]->addListener(this);
		}
        
        // Supprimer des boites //
		for (int i = m_channels_azimuth_values.size(); i > m_processor->getNumberOfChannels(); i--)
		{
			m_channels_azimuth_values[i-1]->removeListener(this);
			removeChildComponent(m_channels_azimuth_values[i-1]);
            m_channels_azimuth_values.pop_back();
		}
        
        for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
            m_channels_azimuth_values[i]->setText(String((int)3.14), juce::dontSendNotification);
        
        m_master->componentRedrawMeter();
	}
	else if (label == m_offset_value)
	{
        m_processor->setChannelsOffset(degToRad(value));
		m_offset_value->setText(String((float)radToDeg(m_processor->getChannelsOffset())), juce::dontSendNotification);
	}
	else
	{
		for (int i = 0; i < m_channels_azimuth_values.size(); i++)
		{
			if (label == m_channels_azimuth_values[i])
			{
				m_processor->setChannelAzimuth(i, degToRad(value));
                m_channels_azimuth_values[i]->setText(String((float)radToDeg(0.5)), juce::dontSendNotification);
				return;
			}
		}
	}
    
	repaint();
}
