/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __PLUGINEDITOR_H_INCLUDED__
#define __PLUGINEDITOR_H_INCLUDED__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "HoaMap/HoaMapComponent.h"
#include "HoaMeter/HoaMeterComponent.h"
#include "HoaInfos/HoaInfosComponent.h"
#include "HoaSettings/HoaSettingsComponent.h"
#include "HoaLogo/HoaLogoComponent.h"
#include "PluginProcessor.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public HoaComponentListener
{
private:
    HoaToolsAudioProcessor* m_processor;

    HoaMapComponent*        m_map;
    HoaMeterComponent*      m_meter;
    HoaInfosComponent*      m_infos;
    HoaSettingsComponent*   m_settings;
    HoaLogoComponent*       m_logo;
    Component*              m_front_component;
    
    HoaLookAndFeel*         m_lookAndFeel;
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void componentHasBeenClicked(Component* component);
    void componentRedrawMap();
    void componentRedrawMeter();
};


#endif
