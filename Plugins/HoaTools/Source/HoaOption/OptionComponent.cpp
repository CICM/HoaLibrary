/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "OptionComponent.h"

/************************************************************************************/
/***************************** OPTION ***********************************************/
/************************************************************************************/

MenuBox::MenuBox(const String& componentName) : ComboBox(componentName)
{
    
}

MenuBox::~MenuBox()
{
    
}
 
void MenuBox::paint(Graphics& g)
{
    g.fillAll(Colours::white);
}



