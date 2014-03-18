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
    size = 1;
    
    m_label_settings = new Label();
    m_label_settings->setText("Settings", juce::dontSendNotification);
    
    m_optimization = new ComboBox();
    m_optimization->setEditableText(false);
    m_optimization->setJustificationType(Justification::centredLeft);
    m_optimization->addItem("Basic", 1);
    m_optimization->addItem("Maxre", 2);
    m_optimization->addItem("Inphase", 3);
    m_optimization->addListener(this);
    m_optimization->setSelectedId(m_processor->getOptimMode() + 1);
    
    m_label_optimization = new Label();
    m_label_optimization->setText("Optimization", juce::dontSendNotification);

    m_decoder = new ComboBox();
    m_decoder->setEditableText(false);
    m_decoder->setJustificationType(Justification::centredLeft);
    m_decoder->addItem("Ambisonic", 1);
    m_decoder->addItem("Irregulier", 2);
    m_decoder->addItem("Binoral", 3);
    m_decoder->addListener(this);
    m_decoder->setSelectedId(m_processor->getDecodingMode() + 1);
    
    m_label_decoder = new Label();
    m_label_decoder->setText("Decoding Mode", juce::dontSendNotification);
    
    m_sources = new TextEditor();
    
    m_label_sources = new Label();
    m_label_sources->setText("Number of Sources", juce::dontSendNotification);
    
    m_loudspeakers = new TextEditor();
    // codition de numbres
    
    m_label_loudspeakers = new Label();
    m_label_loudspeakers->setText("Number of Loudspeakers", juce::dontSendNotification);
    
    
    m_offset = new TextEditor();
    
    m_label_offset = new Label();
    m_label_offset->setText("Offset", juce::dontSendNotification);
    
    m_label_angle = new Label();
    m_label_angle->setText("Angle", juce::dontSendNotification);
    
    m_loudspeakers->addListener(this);
}

HoaSettingsComponent::~HoaSettingsComponent()
{
    delete m_label_settings;
    delete m_optimization;
    delete m_label_optimization;
    delete m_decoder;
    delete m_label_decoder;
    delete m_sources;
    delete m_label_sources;
    delete m_loudspeakers;
    delete m_label_loudspeakers;
    delete m_offset;
    delete m_label_offset;
    delete m_label_angle;
    m_angles.clear();
}

void HoaSettingsComponent::comboBoxChanged(ComboBox* aComboBox)
{
    if(aComboBox == m_optimization)
    {
        m_processor->setOptimMode(static_cast<Optim::Mode>(m_optimization->getSelectedId() - 1));
    }
}

void HoaSettingsComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
    }
    else
    {
        
    }
}

void HoaSettingsComponent::paint(Graphics& g)
{
    int nouveaunombre = 35;
    
    g.setColour(Colours::black);
    if(getWidth() < 125)
    {
        g.drawText(hoa_settings_label, 0, 0, getWidth(), getWidth(), Justification::centred, 0);
        removeChildComponent(m_label_settings);
        removeChildComponent(m_optimization);
        removeChildComponent(m_label_optimization);
        removeChildComponent(m_decoder);
        removeChildComponent(m_label_decoder);
        
    }
    else
    {
        addAndMakeVisible(m_label_settings);
        m_label_settings->setBounds(5, 10, getWidth() * 0.5 - 10, 14);

        
        g.setColour(Colours::darkgrey);
        g.drawLine(0, 50, 495, 50);
        
        g.setColour(Colours::black);
        addAndMakeVisible(m_optimization);
        m_optimization->setBounds(getWidth() * 0.5, 60, getWidth() * 0.5 - 10, 14);
        
        addAndMakeVisible(m_label_optimization);
        m_label_optimization->setBounds(10, 60, getWidth() * 0.5 - 10, 14);
        
        addAndMakeVisible(m_decoder);
        m_decoder->setBounds(getWidth() * 0.5, 80, getWidth() * 0.5 - 10, 14);
        
        addAndMakeVisible(m_label_decoder);
        m_label_decoder->setBounds(10, 80, getWidth() * 0.5 - 10, 14);
        
        g.setColour(Colours::grey);
        g.drawLine(0, 130, 495, 130);
    
        g.setColour(Colours::black);
        addAndMakeVisible(m_label_sources);
        m_label_sources->setBounds(80, 150, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_sources);
        m_sources->setBounds(280, 150, 40, 20);

        addAndMakeVisible(m_label_loudspeakers);
        m_label_loudspeakers->setBounds(80, 190, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_loudspeakers);
        m_loudspeakers->setBounds(280, 190, 40, 20);
        
        addAndMakeVisible(m_label_offset);
        m_label_offset->setBounds(80, 230, getWidth() * 0.5 - 10, 20);
        
        addAndMakeVisible(m_offset);
        m_offset->setBounds(280, 230, 40, 20);

        addAndMakeVisible(m_label_angle);
        m_label_angle->setBounds(10, 320, getWidth() * 0.5 - 10, 20);
        
        for (int i = 0; i < m_angles.size(); i++)
        {
            int index_line = i / 12;
            int index_column = i - index_line * 12;
            m_angles[i]->setBounds(index_column * 45 + 2.5, index_line * 25 + 340, 40, 20);
            addAndMakeVisible(m_angles[i]);
            
        }
        
        g.drawLine(0, 0, size, getHeight());
    }
}

void HoaSettingsComponent::textEditorReturnKeyPressed(TextEditor &textedit)
{
    size = getWidth();
  
    if(&textedit == m_loudspeakers)
    {
        String text;
        long textNum;
        text = textedit.getText();
        
        //textNum = text.getIntValue();
        
        textNum = 8;
        
        if (textNum > 1 && textNum <= 32)
        {
            for (int i = m_angles.size(); i <= textNum; i++)
                m_angles.push_back(new TextEditor());
            
            for (int i = m_angles.size(); i >= textNum; i--)
                m_angles.pop_back();
        }
        
        repaint();
    }
    repaint();
}
