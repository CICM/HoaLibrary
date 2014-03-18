/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef _HOA_SETTINGS_COMPONENT_
#define _HOA_SETTINGS_COMPONENT_

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "PluginProcessor.h"
#include "HoaTextEditor.h"

class HoaSettingsComponent : public Component, public ComboBox::Listener, public TextEditor::Listener, public KeyListener
{
private:
    HoaComponentListener*   m_master;
    HoaToolsAudioProcessor* m_processor;
    Label*                  m_label_settings;
    ComboBox*               m_optimization;
    Label*                  m_label_optimization;
    ComboBox*               m_decoder;
    Label*                  m_label_decoder;
    TextEditor*             m_sources;
    Label*                  m_label_sources;
    TextEditor*				m_loudspeakers;
    Label*                  m_label_loudspeakers;
    TextEditor*             m_offset;
    Label*                  m_label_offset;
    Label*                  m_label_angle;
    
    std::vector<TextEditor*>  m_angles;
    int size;
    //TextEditor**             m_angles;
    
    
    // Boites nombres
    // Menus
    // Etc...
public:
    HoaSettingsComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor);
    ~HoaSettingsComponent();
    
    void paint(Graphics&);
    void mouseDown(const MouseEvent &event);
    void comboBoxChanged(ComboBox* aComboBox);
    void textEditorReturnKeyPressed(TextEditor&);
	
	bool keyPressed (const KeyPress& key, Component* originatingComponent);
	bool keyStateChanged (bool isKeyDown, Component* originatingComponent);
};


#endif