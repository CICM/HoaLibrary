/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_JUCEBOX_WRAPPER
#define DEF_JUCEBOX_WRAPPER

extern "C"
{
#include <ext.h>
#include <ext_obex.h>
#include <z_dsp.h>
#include <ext_common.h>
#include <jpatcher_api.h>
#include <jgraphics.h>
#include <jpatcher_syms.h>
#include <ext_dictionary.h>
#include <buffer.h>
#include <ext_globalsymbol.h>
#include <commonsyms.h>
#include <ext_parameter.h>
#include <jpatcher_syms.h>
}

#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;
//extern void initialiseMac(void);
//extern void componentCreateWindow (juce::Component* comp);

class PdJuceComponent : public juce::Component, public Timer
{
private:
public:
    
	PdJuceComponent() : Component(), Timer()
    {
        setBounds(100, 100, 300, 300);
        //ComponentPeer::StyleFlags::windowIgnoresMouseClicks |
        addToDesktop(ComponentPeer::StyleFlags::windowIsTemporary);
        setEnabled(true);
        setAlwaysOnTop(true);
        setVisible (true);
        toFront(false);
        setOpaque(false);
        
        //m_clock = clock_new((void *)m_box, m_callback);
    }
    
    void paint (Graphics& g)
    {
        g.setColour(juce::Colours::green);
        g.drawEllipse(2, 2, getWidth() - 4, getWidth() - 4, 5);
        post("%ld", isTimerRunning());
        
    }
    
    void mouseEnter(const MouseEvent &event)
    {
        post("%i %i", event.x, event.y);
    }
    
    void mouseMove(const MouseEvent &event)
    {
        post("%i %i", event.x, event.y);
    }
    
    void mouseDown(const MouseEvent &event)
    {
        post("%f %f", event.x, event.y);
    }
    
    void timerCallback()
    {
        post("zaza");
    }
    
    void mouseDrag(const MouseEvent &event){};
    void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel){};
    
    ~PdJuceComponent()
    {
        
    }
};

/*
void jucebox_initclass(t_class* c, method paint, long flags);
void jucebox_new(t_jucebox* x);
void jucebox_free(t_jucebox* x);
void jucebox_paint(t_jucebox* x, t_object *patcherview);
void jucebox_setsize(t_jucebox* x);
*/
#endif