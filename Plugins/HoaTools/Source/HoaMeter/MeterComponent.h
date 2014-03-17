/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __HOA_DECODER_PLUGIN__
#define __HOA_DECODER_PLUGIN__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"

class MeterEditor : public Component, public Timer
{
private:
    Meter*  m_meter;

public:
    MeterEditor(Meter * aMeter);
    ~MeterEditor();
    
    void paint (Graphics&);
    void timerCallback();
};


#endif