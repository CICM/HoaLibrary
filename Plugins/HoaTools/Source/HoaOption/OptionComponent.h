/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __HOA_MENU_BOX__
#define __HOA_MENU_BOX__

#include <JuceHeader.h>

class MenuBox : public ComboBox
{
private:

public:
    MenuBox(const String& componentName = String::empty);
    ~MenuBox();
    
    void paint (Graphics&);
};


#endif