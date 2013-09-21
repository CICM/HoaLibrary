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

HoaToolsAudioProcessorEditor::HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, MapProcessor* aMapProcessor,  DecoderProcessor* aDecoderProcessor): AudioProcessorEditor(ownerFilter)
{
    m_processor = ownerFilter;
    m_map       = new MapEditor(aMapProcessor);
    m_decoder   = new DecoderEditor(aDecoderProcessor);
    m_switch    = new ShapeButton(String(""), Colour::fromRGBA(0,0,0,0), Colour::fromRGBA(50, 50, 50, 50), Colour::fromRGBA(50, 50, 50, 125));
    
    if(m_processor->getGui() == gui_mode_map)
    {
        addAndMakeVisible(m_map);
        m_map->setSize(495, 495);
        m_map->setBounds(2.5, 2.5, 495, 495);
    
        addAndMakeVisible(m_decoder);
        m_decoder->setSize(123, 123);
        m_decoder->setBounds(501, 375, 124, 124);
    }
    else
    {        
        addAndMakeVisible(m_decoder);
        m_decoder->setSize(495, 495);
        m_decoder->setBounds(2.5, 2.5, 495, 495);
        
        addAndMakeVisible(m_map);
        m_map->setSize(123, 123);
        m_map->setBounds(501, 375, 124, 124);
    }
    
    addAndMakeVisible(m_switch);
    m_switch->setSize(123, 123);
    m_switch->setBounds(501, 375, 124, 124);
    m_switch->addListener(this);
    
    setSize(625, 500);
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

void HoaToolsAudioProcessorEditor::buttonClicked(Button* button)
{
    if(m_processor->getGui() == gui_mode_map)
    {
        m_decoder->setSize(495, 495);
        m_decoder->setBounds(2.5, 2.5, 495, 495);
        m_map->setSize(123, 123);
        m_map->setBounds(501, 375, 124, 124);
        m_processor->setGui(gui_mode_meter);
    }
    else
    {
        m_map->setSize(495, 495);
        m_map->setBounds(2.5, 2.5, 495, 495);
        m_decoder->setSize(123, 123);
        m_decoder->setBounds(501, 375, 124, 124);
        m_processor->setGui(gui_mode_map);
    }
}


HoaToolsAudioProcessorEditor::~HoaToolsAudioProcessorEditor()
{
    delete m_map;
    delete m_decoder;
    delete m_switch;
}



