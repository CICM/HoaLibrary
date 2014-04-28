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
	m_order_value->setText(String(m_processor->getDecompositionOrder()), juce::dontSendNotification);
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

    // -- sources
	
	m_number_of_sources_label = new Label();
    m_number_of_sources_label->setText("Number of Sources", juce::dontSendNotification);
	
    m_number_of_sources_value = new Label();
	m_number_of_sources_value->setEditable(true, false, false);
	m_number_of_sources_value->addListener(this);

    
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
    delete m_optim_value;
    delete m_optim_label;
    delete m_number_of_sources_value;
    delete m_number_of_sources_label;
    delete m_pinna_label;
    delete m_pinna_value;
}

void HoaSettingsComponent::comboBoxChanged(ComboBox* comboBox)
{
    if(comboBox == m_optim_value)
        m_processor->setOptimMode(static_cast<Optim::Mode>(m_optim_value->getSelectedId() - 1));
    
    else if(m_processor->isSuspended())
        m_processor->applyChanges();
    updated();
}

void HoaSettingsComponent::labelTextChanged(Label* label)
{
	double value = label->getText().getDoubleValue();
	
    if(label == m_order_value)
        m_processor->setOrder(clip_minmax(value, 1, 15));

    
    else if(m_processor->isSuspended())
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
        int x1 = 10, x2 = getWidth() * 0.5, y = 10, width = getWidth() * 0.5 - 10, height = 20;
        
        
        m_order_value->setText(String((int)m_processor->getDecompositionOrder()), juce::dontSendNotification);
        m_optim_value->setSelectedId(m_processor->getOptimMode() + 1);
        m_number_of_sources_value->setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);

        if(m_processor->getPinnaSize() == Hoa2D::DecoderBinaural::Small)
            m_pinna_value->setSelectedId(1);
        else
            m_pinna_value->setSelectedId(2);
            
        
        addAndMakeVisible(m_order_label);
        m_order_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_order_value);
        m_order_value->setBounds(x2, y, width, height);
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
        
        addAndMakeVisible(m_pinna_label);
        m_pinna_label->setBounds(x1, y, width, height);
        addAndMakeVisible(m_pinna_value);
        m_pinna_value->setBounds(x2, y, width, height);
        
       
    }
}

void HoaSettingsComponent::paint(Graphics& g)
{
    if(getWidth() < PLUG_MENU_WIDTH)
    {
        removeChildComponent(m_order_label);
        removeChildComponent(m_order_value);
        removeChildComponent(m_optim_label);
        removeChildComponent(m_optim_value);
        removeChildComponent(m_number_of_sources_label);
        removeChildComponent(m_number_of_sources_value);
 

        g.drawImage(m_settings_icon, 25, 25, PLUG_MENU_WIDTH, PLUG_MENU_WIDTH, 0, 0, m_settings_icon.getWidth() * 1.8, m_settings_icon.getHeight() * 1.8);
    }
}

