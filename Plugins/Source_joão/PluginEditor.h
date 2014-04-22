
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap/HoaMapComponent.h"
#include "HoaMeter/HoaMeterComponent.h"
#include "HoaInfos/HoaInfosComponent.h"
#include "HoaSettings/HoaSettingsComponent.h"
#include "HoaLogo/HoaLogoComponent.h"
#include "PluginProcessor.h"
#include "HoaComponent.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public HoaComponentListener
{
private:
    HoaToolsAudioProcessor* m_processor;
    HoaProcessor*           m_hoa_processor;

    HoaMapComponent*        m_map;
    HoaMeterComponent*      m_meter;
    HoaInfosComponent*      m_infos;
    HoaSettingsComponent*   m_settings;
    HoaLogoComponent*       m_logo;
    Component*              m_front_component;
    
    
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, HoaProcessor* aHoaProcessor);
    ~HoaToolsAudioProcessorEditor();

    void componentHasBeenClicked(Component* component);
    void paint(Graphics& g);
};


#endif
