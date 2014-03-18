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
    m_settings  = new HoaSettingsComponent(this, m_processor);
    m_infos     = new HoaInfosComponent(this);
    m_logo      = new HoaLogoComponent();
    
    addAndMakeVisible(m_map);
    m_map->setSize(495, 495);
    m_map->setBounds(2.5, 2.5, 495, 495);
    m_front_component = m_map;
    
    addAndMakeVisible(m_logo);
    m_logo->setSize(123, 123);
    m_logo->setBounds(501, 2.5, 124, 124);
    
    addAndMakeVisible(m_infos);
    m_infos->setSize(123, 123);
    m_infos->setBounds(501, 125, 124, 124);
    
    addAndMakeVisible(m_settings);
    m_settings->setSize(123, 123);
    m_settings->setBounds(501, 250, 124, 124);
    
    addAndMakeVisible(m_meter);
    m_meter->setSize(123, 123);
    m_meter->setBounds(501, 375, 124, 124);
    
    setSize(625, 500);
}

HoaToolsAudioProcessorEditor::~HoaToolsAudioProcessorEditor()
{
    delete m_logo;
    delete m_infos;
    delete m_settings;
    delete m_map;
    delete m_meter;
}

void HoaToolsAudioProcessorEditor::componentHasBeenClicked(Component* component)
{
    double x, y;
    if(component != m_logo)
    {
        x = component->getX();
        y = component->getY();
        
        component->setSize(495, 495);
        component->setBounds(2.5, 2.5, 495, 495);
        
        m_front_component->setSize(124, 124);
        m_front_component->setBounds(x, y, 124, 124);
        m_front_component = component;
        repaint();
    }
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
}
