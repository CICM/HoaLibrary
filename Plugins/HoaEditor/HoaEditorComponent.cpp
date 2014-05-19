/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "..\HoaQuadra\Source\PluginProcessor.h"
#include "HoaEditorComponent.h"


HoaToolsAudioProcessorEditor::HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter) : AudioProcessorEditor(ownerFilter)
{
    m_processor = ownerFilter;
    
    m_map       = new HoaMapComponent(this, m_processor);
    m_meter     = new HoaMeterComponent(this, m_processor);
    m_value     = new HoaLabel(this, m_processor, m_map);
    m_logo_icon = ImageCache::getFromMemory(BinaryData::hoa_icon_02_transp_png, BinaryData::hoa_icon_02_transp_pngSize);
    
    addAndMakeVisible(m_map);
    m_map->setSize(495, 495);
    m_map->setBounds(2.5, 2.5, 495, 495);
    
    addAndMakeVisible(m_meter);
    m_meter->setSize(123, 123);
    m_meter->setBounds(436, 375, 124, 124);
    
    addAndMakeVisible(m_value);
    m_value->setBounds(60, 458, 25, 14);
    
    setSize(565, 500);
}

HoaToolsAudioProcessorEditor::~HoaToolsAudioProcessorEditor()
{
	delete m_map;
    delete m_meter;
    delete m_value;
}

void HoaToolsAudioProcessorEditor::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.fillAll();
    
    g.setColour(Colours::lightgrey);
    g.fillEllipse(2.5, 2.5, 495, 495);
    
    g.setColour(Colours::black);
    
    g.setFont(Font(String("Arial"), 22, Font::FontStyleFlags::bold | Font::FontStyleFlags::italic));
    g.setColour(Colour(0.2f, 0.f, 0.f, 1.f));
    g.drawText(String("HOA"), 2.5, 2.5, 130, 29, Justification::topLeft, 0);
    g.drawText(String(HoaPlugin_Name), 2.5, 20, 130, 29, Justification::topLeft, 0);
    
    g.setFont(Font(String("Arial"), 11, Font::FontStyleFlags::plain));
    g.drawText(String("HOA Library by CICM | University Paris 8"), 2.5, 489, 1000, 10, Justification::left, 0);
    g.drawImage(m_logo_icon, 441, 2.5, 115, 115, 0, 0, m_logo_icon.getWidth(), m_logo_icon.getHeight());
    
    g.setFont(16);
    g.drawText(String("Number of"), 2.5, 442, 100, 10, Justification::centredLeft, 0);
    g.drawText(String("Sources")  , 2.5, 460, 100, 10, Justification::centredLeft, 0);
    g.setColour(Colours::lightgrey);
    g.fillRect(60, 458, 25, 14);
    g.setColour(Colours::black);
    g.drawRect(60, 458, 25, 14);
    
    
    
    m_value->processorUpdated();
}
