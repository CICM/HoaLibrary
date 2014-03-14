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
    
    m_map       = new MapEditor(m_hoa_processor->getSourceManager(), ownerFilter);
    m_meter     = new MeterEditor(m_hoa_processor->getMeter());

    HoaFont.setHeight(11.);
    HoaFont.setBold(1);
    
    if(ownerFilter->getGui() == gui_mode_map)
    {
        addAndMakeVisible(m_map);
        m_map->setSize(495, 495);
        m_map->setBounds(2.5, 2.5, 495, 495);
    
        addAndMakeVisible(m_meter);
        m_meter->setSize(123, 123);
        m_meter->setBounds(501, 375, 124, 124);
    }
    else
    {        
        addAndMakeVisible(m_meter);
        m_meter->setSize(495, 495);
        m_meter->setBounds(2.5, 2.5, 495, 495);
        
        addAndMakeVisible(m_map);
        m_map->setSize(123, 123);
        m_map->setBounds(501, 375, 124, 124);
    }
    
    /////////////////////////////////////////////////
    /////////////////   ORDER   /////////////////////
    /////////////////////////////////////////////////
    addAndMakeVisible(m_order_text = new Label());
    m_order_text->setText(String("Order :"), NotificationType(0));
    m_order_text->setBounds(501, 5, 80, 15);
    m_order_text->setFont(HoaFont);

    addAndMakeVisible(m_order_menu = new Slider());
    m_order_menu->setSliderStyle(Slider::IncDecButtons);
    m_order_menu->setTextBoxIsEditable(1);
    m_order_menu->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 11);
    m_order_menu->setBounds(581, 5, 50, 12);
    m_order_menu->setRange(0, 64, 1);
    m_order = (int)m_hoa_processor->getOrder();
    m_order_menu->getValueObject().referTo(m_order);
    m_order.addListener(this);
    
    /////////////////////////////////////////////////
    /////////////////   NINPUTS  ////////////////////
    /////////////////////////////////////////////////
    addAndMakeVisible(m_sources_text = new Label());
    m_sources_text->setText(String("Sources :"), NotificationType(0));
    m_sources_text->setBounds(501, 25, 80, 15);
    m_sources_text->setFont(HoaFont);
    
    addAndMakeVisible(m_sources_menu = new Slider());
    m_sources_menu->setSliderStyle(Slider::IncDecButtons);
    m_sources_menu->setTextBoxIsEditable(1);
    m_sources_menu->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 11);
    m_sources_menu->setBounds(581, 25, 50, 12);
    m_sources_menu->setRange(0, 64, 1);
    m_nunber_of_sources = (int)m_hoa_processor->getNumberOfSources();
    m_sources_menu->getValueObject().referTo(m_nunber_of_sources);
    m_nunber_of_sources.addListener(this);
    
    /////////////////////////////////////////////////
    /////////////////   NOUTPUTS  ///////////////////
    /////////////////////////////////////////////////
    addAndMakeVisible(m_loudspeakers_text = new Label());
    m_loudspeakers_text->setText(String("Loudspeakers :"), NotificationType(0));
    m_loudspeakers_text->setBounds(501, 45, 80, 15);
    m_loudspeakers_text->setFont(HoaFont);
    
    addAndMakeVisible(m_loudspeakers_menu = new Slider());
    m_loudspeakers_menu->setSliderStyle(Slider::IncDecButtons);
    m_loudspeakers_menu->setTextBoxIsEditable(1);
    m_loudspeakers_menu->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 11);
    m_loudspeakers_menu->setBounds(581, 45, 50, 12);
    m_loudspeakers_menu->setRange(0, 64, 1);
    m_nunber_of_loudspeakers = (int)m_hoa_processor->getNumberOfLoudspeakers();
    m_loudspeakers_menu->getValueObject().referTo(m_nunber_of_loudspeakers);
    m_nunber_of_loudspeakers.addListener(this);
    
    /////////////////////////////////////////////////
    /////////////////   DECMODE   ///////////////////
    /////////////////////////////////////////////////
    addAndMakeVisible(m_decoder_menu = new ComboBox());
    m_decoder_menu->setEditableText(false);
    m_decoder_menu->setJustificationType(Justification::centredLeft);
    m_decoder_menu->setTextWhenNoChoicesAvailable("(no choices)");
    m_decoder_menu->addItem("Decoding : Ambisonic", 1);
    m_decoder_menu->addItem("Decoding : Binaural", 2);
    m_decoder_menu->addItem("Decoding : Irregular", 3);
    m_decoder_menu->addListener(this);
    m_decoder_menu->setSelectedId(m_hoa_processor->getDecodingMode()+1);
    m_decoder_menu->setBounds(501, 77, 122, 15);
    m_decoder_menu->setLookAndFeel(&LookAndFeel);
    
    /////////////////////////////////////////////////
    /////////////////   OPTIM   /////////////////////
    /////////////////////////////////////////////////
    addAndMakeVisible(m_optim_menu = new ComboBox());
    m_optim_menu->setEditableText(false);
    m_optim_menu->setJustificationType(Justification::centredLeft);
    m_optim_menu->setTextWhenNoChoicesAvailable("(no choices)");
    m_optim_menu->addItem("Optim : Basic", 1);
    m_optim_menu->addItem("Optim : MaxRe", 2);
    m_optim_menu->addItem("Optim : InPhase", 3);
    m_optim_menu->addListener(this);
    m_optim_menu->setSelectedId(m_hoa_processor->getOptimization()+1);
    m_optim_menu->setBounds(501, 92, 122, 15);
    m_optim_menu->setLookAndFeel(&LookAndFeel);    
    
    addAndMakeVisible(m_offset_text = new Label("Offset"));
    m_offset_text->setText(String("Offset of loudspeakers"), NotificationType(1));
    m_offset_text->setBounds(501, 107, 122, 15);
    addAndMakeVisible(m_offset_menu = new Label("Offset"));
    m_offset_menu->setText(String(0), NotificationType(1));
    m_offset_menu->setEditable(1);
    m_offset_menu->setBounds(501, 122, 122, 15);
   
    addAndMakeVisible(m_switch    = new ShapeButton(String(""), Colour::fromRGBA(0,0,0,0), Colour::fromRGBA(50, 50, 50, 50), Colour::fromRGBA(50, 50, 50, 125)));
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

HoaToolsAudioProcessorEditor::~HoaToolsAudioProcessorEditor()
{
    delete m_map;
    delete m_meter;
    delete m_optim_menu;
    delete m_order_menu;
    delete m_offset_menu;
    delete m_decoder_menu;
    delete m_switch;
}

void HoaToolsAudioProcessorEditor::valueChanged(Value& aValue)
{
    if(aValue == m_nunber_of_sources)
    {
        m_hoa_processor->setNumberOfSources(m_sources_menu->getValue());
    }
    else if(aValue == m_nunber_of_loudspeakers)
    {
        m_hoa_processor->setNumberOfLoudspeakers(m_loudspeakers_menu->getValue());
    }
}

void HoaToolsAudioProcessorEditor::comboBoxChanged(ComboBox* aComboBox)
{
    if(aComboBox == m_optim_menu)
    {
        m_hoa_processor->setOptimization(m_optim_menu->getSelectedId()-1);
    }
    else if(aComboBox == m_decoder_menu)
    {
        ;
    }
}


void HoaToolsAudioProcessorEditor::buttonClicked(Button* aButton)
{
    if(m_processor->getGui() == gui_mode_map)
    {
        m_meter->setSize(495, 495);
        m_meter->setBounds(2.5, 2.5, 495, 495);
        m_map->setSize(123, 123);
        m_map->setBounds(501, 375, 124, 124);
        m_processor->setGui(gui_mode_meter);
    }
    else
    {
        m_map->setSize(495, 495);
        m_map->setBounds(2.5, 2.5, 495, 495);
        m_meter->setSize(123, 123);
        m_meter->setBounds(501, 375, 124, 124);
        m_processor->setGui(gui_mode_map);
    }
}




