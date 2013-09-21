
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap/MapComponent.h"
#include "HoaDecoder/DecoderComponent.h"
#include "PluginProcessor.h"


class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public ButtonListener
{
private:
    HoaToolsAudioProcessor* m_processor;
    MapEditor*              m_map;
    DecoderEditor*          m_decoder;
    ShapeButton*            m_switch;
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, MapProcessor* aMapProcessor, DecoderProcessor* aDecoderProcessor);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void buttonClicked(Button* button);
};


#endif
