/*
  ==============================================================================

    map.h
    Created: 13 Mar 2013 11:15:41pm
    Author:  eliott PARIS

  ==============================================================================
*/

#ifndef __MAP_H_5D25AFEF__
#define __MAP_H_5D25AFEF__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class map    : public Component
{
public:
    map();
    ~map();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (map)
};


#endif  // __MAP_H_5D25AFEF__
