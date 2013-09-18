

#ifndef HOA_MAP_PLUGIN
#define HOA_MAP_PLUGIN

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../Sources/HoaLibrary.h"

class MapComponent:public Component, public ChangeBroadcaster
{
private:    
    SourcesManager*             m_sources_manager;
    AmbisonicsMultiMaps*        m_map;
    double          m_sources_size;
    long            m_souce_selected;
    long            m_background_invalidate;
public:
    MapComponent(SourcesManager* aSourcesManger);
    ~MapComponent();
    
    void setNumberOfChannels(long aNumberOfInputs, long aNumberOfOuputs);
    void prepareToPlay(long aSampleRate, long aVectorSize);
    void process(float** inputs, float** outputs);
   
    void paint(Graphics& g);
    void draw_background(Graphics& g);
    void draw_sources(Graphics& g);
    
    void mouseMove(const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseDrag(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel);
};


#endif