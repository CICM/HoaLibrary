
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap/MapComponent.h"
#include "HoaDecoder/DecoderComponent.h"
#include "HoaOption/OptionComponent.h"
#include "PluginProcessor.h"


class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public ComboBoxListener, public ButtonListener
{
private:
    HoaToolsAudioProcessor* m_processor;
    AmbisonicOptim*         m_optim_processor;
    
    MapEditor*              m_map;
    DecoderEditor*          m_decoder;
    
    ShapeButton*            m_switch;
    ComboBox*               m_optim_menu;
    
    HoaLookAndFeel          LookAndFeel;
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, MapProcessor* aMapProcessor, DecoderProcessor* aDecoderProcessor);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void comboBoxChanged(ComboBox* aComboBox);
    void buttonClicked(Button* button);
};


#endif
