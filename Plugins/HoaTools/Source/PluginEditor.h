
#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap/MapComponent.h"
#include "HoaDecoder/DecoderComponent.h"
#include "HoaOption/OptionComponent.h"
#include "PluginProcessor.h"
#include "HoaComponent.h"

class HoaToolsAudioProcessorEditor  : public AudioProcessorEditor, public ComboBoxListener, public ButtonListener, public ValueListener
{
private:
    HoaToolsAudioProcessor* m_processor;
    HoaProcessor*           m_hoa_processor;
    
    MapProcessor*           m_m_proc;
    AmbisonicOptim*         m_optim_processor;
    AmbisonicsMultiMaps*    m_map_processor;
    AmbisonicsMultiDecoder* m_decoder_processor;
    SourcesManager*         m_sources_manager;
    MapEditor*              m_map;
    DecoderEditor*          m_decoder;
    
    ShapeButton*            m_switch;
    
    Label*                  m_order_text;
    Slider*                 m_order_menu;
    Value                   m_order;
    
    Label*                  m_sources_text;
    Slider*                 m_sources_menu;
    Value                   m_nunber_of_sources;
    
    Label*                  m_loudspeakers_text;
    Slider*                 m_loudspeakers_menu;
    Value                   m_nunber_of_loudspeakers;
    
    ComboBox*               m_decoder_menu;
    ComboBox*               m_optim_menu;
    Label*                  m_offset_text;
    Label*                  m_offset_menu;
    
    HoaLookAndFeel          LookAndFeel;
    Font                    HoaFont;
public:
    HoaToolsAudioProcessorEditor(HoaToolsAudioProcessor* ownerFilter, HoaProcessor* aHoaProcessor);
    ~HoaToolsAudioProcessorEditor();

    void paint(Graphics& g);
    void comboBoxChanged(ComboBox* aComboBox);
    void buttonClicked(Button* aButton);
    void valueChanged(Value& aValue);
};


#endif
