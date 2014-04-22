/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

HoaToolsAudioProcessorEditor::HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, HoaProcessor* aHoaProcessor): AudioProcessorEditor(ownerFilter)
{
    m_processor = ownerFilter;
    m_hoa_processor = aHoaProcessor;
    
    m_map       = new HoaMapComponent(this, m_hoa_processor);
    m_meter     = new HoaMeterComponent(this, m_hoa_processor->getMeter());
    m_settings  = new HoaSettingsComponent(this, m_hoa_processor);
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




