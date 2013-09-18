
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginMap.h"
#include "PluginProcessor.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
private:
    SourcesManager* m_sources_manager;
    MapComponent*   m_map;
    
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, SourcesManager* aSourcesManger);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void timerCallback();
};


#endif
