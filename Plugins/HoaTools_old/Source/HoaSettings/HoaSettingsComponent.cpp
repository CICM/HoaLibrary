/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaSettingsComponent.h"

HoaSettingsComponent::HoaSettingsComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor)
{
    m_master    = master;
    m_processor = processor;
    
    m_settings_icon = ImageCache::getFromMemory(BinaryData::icongear256_png, BinaryData::icongear256_pngSize);   

    // -- ordre
    
    m_order_label = new Label();
    m_order_label->setText("Decomposition Order", juce::dontSendNotification);
	
    m_order_value = new Label();
	m_order_value->setEditable(true, false, false);
	m_order_value->setText(String(m_processor->getOrder()), juce::dontSendNotification);
	m_order_value->addListener(this);
    
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
    
    // -- sources
	
	m_number_of_sources_label = new Label();
    m_number_of_sources_label->setText("Number of Sources", juce::dontSendNotification);
	
    m_number_of_sources_value = new Label();
	m_number_of_sources_value->setEditable(true, false, false);
	m_number_of_sources_value->addListener(this);

	// -- channels
	
	m_number_of_channels_label = new Label();
    m_number_of_channels_label->setText("Number of Channels", juce::dontSendNotification);
	
    m_number_of_channels_value = new Label();
	m_number_of_channels_value->setEditable(true, false, false);
	m_number_of_channels_value->addListener(this);
    
    
	// -- offset
	
	m_offset_label = new Label();
    m_offset_label->setText("Offset of Channels (degrees)", juce::dontSendNotification);
	
    m_offset_value = new Label();
	m_offset_value->setEditable(true, false, false);
    m_offset_value->addListener(this);
	
	// -- channels angles
	
    m_channels_azimuth_label = new Label();
    m_channels_azimuth_label->setText("Angles of Channels (degrees)", juce::dontSendNotification);
	
	for (int i = 0; i < m_processor->getNumberOfChannels(); i++)
	{
		m_channels_azimuth_values.push_back(new Label());
        m_channels_azimuth_values[i]->setEditable(true, false, false);
        m_channels_azimuth_values[i]->addListener(this);
        m_channels_azimuth_labels.push_back(new Label());
	}
    
    // -- Pinna
    
    m_pinna_label = new Label();
    m_pinna_label->setText("Pinna", juce::dontSendNotification);
    
    
    m_pinna_value = new ComboBox();
    m_pinna_value->setEditableText(false);
    m_pinna_value->setJustificationType(Justification::centredLeft);
    m_pinna_value->addItem("Small", 1);
    m_pinna_value->addItem("Large", 2);
    m_pinna_value->addListener(this);
    
    updated();
}

HoaSettingsComponent::~HoaSettingsComponent()
{
    delete m_order_label;
    delete m_order_value;
    delete m_decoder_value;
    delete m_decoder_label;
    delete m_optim_value;
    delete m_optim_label;
    delete m_number_of_sources_value;
    delete m_number_of_sources_label;
    delete m_number_of_channels_value;
    delete m_number_of_channels_label;
    delete m_offset_value;
    delete m_offset_label;
    delete m_channels_azimuth_label;
    m_channels_azimuth_values.clear();
    m_channels_azimuth_labels.clear();
    delete m_pinna_label;
    delete m_pinna_value;
}

void HoaSettingsComponent::comboBoxChanged(ComboBox* comboBox)
{
    if(comboBox == m_optim_value)
        m_processor->setOptimMode(static_cast<Optim::Mode>(m_optim_value->getSelectedId() - 1));
	else if(comboBox == m_decoder_value)
        m_processor->setDecodingMode(static_cast<DecoderMulti::Mode>(m_decoder_value->getSelectedId() - 1));
    
    if(m_processor->isSuspended())
        m_processor->applyChanges();
    updated();
}

void HoaSettingsComponent::labelTextChanged(Label* label)
{
	double value = label->getText().getDoubleValue();
	
    if(label == m_order_value)
        m_processor->setOrder(clip_minmax(value, 1, 15));
	else if(label == m_number_of_sources_value)
		m_processor->setNumberOfSources(clip_minmax(value, 1, 32));
	else if(label == m_number_of_channels_value)
        m_processor->setNumberOfChannels(clip_minmax(value, 1, 32));
	else if (label == m_offset_value)
        m_processor->setChannelsOffset(degToRad(value));
	else
	{
		for (int i = 0; i < m_channels_azimuth_values.size(); i++)
		{
			if (label == m_channels_azimuth_values[i])
			{
				m_processor->setChannelAzimuth(i, degToRad(value));
				break;
			}
		}
	}
    
    if(m_processor->isSuspended())
        m_processor->applyChanges();
    updated();
}

void HoaSettingsComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < PLUG_MENU_WIDTH)
    {
        m_master->componentHasBeenClicked(this);
		return;
    }
}

void HoaSettingsComponent::updated()
{
    if(getWidth() >= PLUG_MENU_WIDTH)
    {
        char label_String[1024];
        int x1 = 10, x2 = getWidth() * 0.5, y = 10, width = getWidth() * 0.5 - 10, height = 20;
        
        // Ajouter des boites //
        for (int i = m_channels_azimuth_values.size(); i < m_processor->getNumberOfChannels(); i++)
		{
            m_channels_azimuth_values.push_back(new Label());
			m_channels_azimuth_values[i]->setEditable(true, false, false);
			m_channels_azimuth_values[i]->addListener(this);
		}
        
        for (int i = m_channels_azimuth_labels.size(); i < m_processor->getNumberOfChannels(); i++)
		{
            m_channels_azimuth_labels.push_back(new Label());
        }
        
        // Supprimer des boites //
		for (int i = m_channels_azimuth_values.size(); i > m_processor->getNumberOfChannels(); i--)
		{
            m_channels_azimuth_values[i-1]->removeListener(this);
			removeChildComponent(m_channels_azimuth_values[i-1]);
            m_channels_azimuth_values.pop_back();
		}
        
        for (int i = m_channels_azimuth_labels.size(); i > m_processor->getNumberOfChannels(); i--)
		{
            removeChildComponent(m_channels_azimuth_labels[i-1]);
            m_channels_azimuth_labels.pop_back();
		}
        
        m_order_value->setText(String((int)m_processor->getOrder()), juce::dontSendNotification);
        m_decoder_value->setSelectedId(m_processor->getDecodingMode() + 1);
        m_optim_value->setSelectedId(m_processor->getOptimMode() + 1);
        m_number_of_sources_value->setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
        m_number_of_channels_value->setText(String((int)m_processor->getNumberOfChannels()), juce::dontSendNotification);
        m_offset_value->setText(String((float)radToDeg(m_processor->getChannelsOffset())), juce::dontSendNotification);
        if(m_processor->getPinnaSize() == Hoa2D::DecoderBinaural::Small)
            m_pinna_value->setSelectedId(1);
        else
            m_pinna_value->setSelectedId(2);
            
        
        addAndMakeVisible(m_order_label);
        m_order_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_order_value);
        m_order_value->setBounds(x2, y, width, height);
        y += 40;
        
        addAndMakeVisible(m_decoder_label);
        m_decoder_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_decoder_value);
        m_decoder_value->setBounds(x2, y, width, height);
        y += 40;
        
        addAndMakeVisible(m_optim_label);
        m_optim_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_optim_value);
        m_optim_value->setBounds(x2, y, width, height);
		y += 40;
        
        addAndMakeVisible(m_number_of_sources_label);
        m_number_of_sources_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_number_of_sources_value);
        m_number_of_sources_value->setBounds(x2, y, width, height);
        y += 40;
        
        if(m_processor->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
        {
            removeChildComponent(m_number_of_channels_label);
            removeChildComponent(m_number_of_channels_value);
            removeChildComponent(m_offset_value);
            removeChildComponent(m_offset_label);
            removeChildComponent(m_channels_azimuth_label);
            
            for (int i = 0; i < m_channels_azimuth_values.size(); i++)
                removeChildComponent(m_channels_azimuth_values[i]);
            
            for (int i = 0; i < m_channels_azimuth_labels.size(); i++)
                removeChildComponent(m_channels_azimuth_labels[i]);
            
            addAndMakeVisible(m_pinna_label);
            m_pinna_label->setBounds(x1, y, width, height);
            addAndMakeVisible(m_pinna_value);
            m_pinna_value->setBounds(x2, y, width, height);
        }
        else
        {
            removeChildComponent(m_pinna_label);
            removeChildComponent(m_pinna_value);
            
            addAndMakeVisible(m_number_of_channels_label);
            m_number_of_channels_label->setBounds(x1, y, width, height);
            addAndMakeVisible(m_number_of_channels_value);
            m_number_of_channels_value->setBounds(x2, y, width, height);
            y += 40;
            
            addAndMakeVisible(m_offset_label);
            m_offset_label->setBounds(x1, y, width, height);
            addAndMakeVisible(m_offset_value);
            m_offset_value->setBounds(x2, y, width, height);
        
            y += 40;
            addAndMakeVisible(m_channels_azimuth_label);
            m_channels_azimuth_label->setBounds(x1, y, width, height);
            
            y += 40;
            int offset = (getWidth() - 10) / 8.;
            for (int i = 0; i < m_channels_azimuth_values.size(); i++)
            {
                int index_line = i / 8;
                int index_column = i - index_line * 8;
                if(m_processor->getDecodingMode() != Hoa2D::DecoderMulti::Irregular)
                    m_channels_azimuth_values[i]->setOpaque(1);
                else
                    m_channels_azimuth_values[i]->setOpaque(0);
                
                addAndMakeVisible(m_channels_azimuth_values[i]);
                m_channels_azimuth_values[i]->setText(String((float)m_processor->getChannelAzimuth(i) / HOA_2PI * 360), juce::dontSendNotification);
                m_channels_azimuth_values[i]->setBounds(index_column * offset + 10, index_line * 50 + 25 + y, offset-10, 20);
            }
            for (int i = 0; i < m_channels_azimuth_labels.size(); i++)
            {
                int index_line = i / 8;
                int index_column = i - index_line * 8;
                addAndMakeVisible(m_channels_azimuth_labels[i]);
                sprintf(label_String, "Ch. %i", i+1);
                m_channels_azimuth_labels[i]->setText(label_String, juce::dontSendNotification);
                m_channels_azimuth_labels[i]->setBounds(index_column * offset + 10, index_line * 50 + y, offset-10, 20);
            }
        }
    }
}

void HoaSettingsComponent::paint(Graphics& g)
{
    if(getWidth() < PLUG_MENU_WIDTH)
    {
        removeChildComponent(m_order_label);
        removeChildComponent(m_order_value);
        removeChildComponent(m_decoder_label);
        removeChildComponent(m_decoder_value);
        removeChildComponent(m_optim_label);
        removeChildComponent(m_optim_value);
        removeChildComponent(m_number_of_sources_label);
        removeChildComponent(m_number_of_sources_value);
        removeChildComponent(m_number_of_channels_label);
        removeChildComponent(m_number_of_channels_value);
        removeChildComponent(m_offset_label);
        removeChildComponent(m_offset_value);
        removeChildComponent(m_channels_azimuth_label);
        for (int i = 0; i < m_channels_azimuth_values.size(); i++)
            removeChildComponent(m_channels_azimuth_values[i]);
        for (int i = 0; i < m_channels_azimuth_labels.size(); i++)
            removeChildComponent(m_channels_azimuth_labels[i]);

        g.drawImage(m_settings_icon, 25, 25, PLUG_MENU_WIDTH, PLUG_MENU_WIDTH, 0, 0, m_settings_icon.getWidth() * 1.8, m_settings_icon.getHeight() * 1.8);
    }
}

