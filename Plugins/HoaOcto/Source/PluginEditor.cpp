/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


HoaToolsAudioProcessorEditor::HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter) : AudioProcessorEditor(ownerFilter)
{
    m_processor = ownerFilter;
    
    m_map       = new HoaMapComponent(this, m_processor);
    m_meter     = new HoaMeterComponent(this, m_processor);
    m_logo_icon = ImageCache::getFromMemory(BinaryData::hoa_icon_02_transp_png, BinaryData::hoa_icon_02_transp_pngSize);
    
    addAndMakeVisible(m_map);
    m_map->setSize(495, 495);
    m_map->setBounds(2.5, 2.5, 495, 495);
    
    addAndMakeVisible(m_meter);
    m_meter->setSize(123, 123);
    m_meter->setBounds(501, 375, 124, 124);
    
    m_label = new Label();
    m_label->setText("Number of Sources", juce::dontSendNotification);
    m_value = new Label();
	m_value->setEditable(true, false, false);
	m_value->addListener(this);
    m_value->setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
    addAndMakeVisible(m_label);
    m_label->setBounds(501, 330, 120, 20);
    addAndMakeVisible(m_value);
    m_value->setBounds(501, 352, 120, 20);
    setSize(625, 500);
}

void HoaToolsAudioProcessorEditor::labelTextChanged(Label* label)
{
    int val = label->getText().getDoubleValue();
    if(val < 0)
        val = 0;
    else if(val > 16)
        val = 16;
    
    m_processor->setNumberOfSources(val);
    m_value->setText(String((int)m_processor->getNumberOfSources()), juce::dontSendNotification);
    m_map->repaint();
}

HoaToolsAudioProcessorEditor::~HoaToolsAudioProcessorEditor()
{
	delete m_map;
    delete m_meter;
    delete m_label;
    removeChildComponent(m_value);
    delete m_value;
}

void HoaToolsAudioProcessorEditor::paint(Graphics& g)
{
    g.setColour(Colours::lightgrey);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 5);
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5.);
    
    g.setColour(Colours::grey);
    g.drawLine(499., 1., 498., getHeight() - 2., 2.5);
    g.setColour(Colours::grey);
    g.drawLine(500, 374, 625, 374, 2.5);

    g.setColour(Colours::grey);
    g.drawLine(500, 124, 625, 124, 2.5);
    
    g.drawImage(m_logo_icon, 501, 0, 125, 125, 0, 0, m_logo_icon.getWidth(), m_logo_icon.getHeight());
}
