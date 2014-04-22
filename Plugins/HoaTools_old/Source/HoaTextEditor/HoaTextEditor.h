/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef _HOA_TEXTEDITOR_COMPONENT_
#define _HOA_TEXTEDITOR_COMPONENT_

#include <JuceHeader.h>

class HoaTextEditor : public TextEditor
{
private:
	TextEditorListener* m_master;
public:
    HoaTextEditor(const String& componentName = String::empty);
    ~HoaTextEditor();
	
	void setMaster(TextEditorListener *c);
	void returnPressed();
	bool keyPressed (const KeyPress&);
};


#endif