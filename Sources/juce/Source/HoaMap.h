/*
  ==============================================================================

    HoaMap.h
    Created: 13 Mar 2013 11:15:41pm
    Author:  eliott PARIS

  ==============================================================================
*/

#ifndef __HoaMap_H_5D25AFEF__
#define __HoaMap_H_5D25AFEF__

#include "../JuceLibraryCode/JuceHeader.h"

#ifndef HOA_PI
    #define HOA_PI		(3.1415926535897932384626433832795028842)
    #define HOA_2PI		(2. * 3.1415926535897932384626433832795028842)
#endif

//==============================================================================
/*
*/
class HoaMap    : public Component
{
public:
    HoaMap();
    ~HoaMap();

    void paint (Graphics&);
    void draw_head (Graphics&);
    void draw_speakers (Graphics&);
    void draw_sources (Graphics&);
    void resized();
    
    // setters :
    void setNbSources(int _nbSources);
    void setNbSpeakers(int _nbSpeakers);
    void setSpeakerDistance(float _speakerDistance);
    void setSpeakerOffset(float _speakerOffset);

private:
    int m_nbSources, m_nbSpeakers;
    float m_speakerOffset, m_speakerDistance;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaMap)
};


#endif  // __HoaMap_H_5D25AFEF__
