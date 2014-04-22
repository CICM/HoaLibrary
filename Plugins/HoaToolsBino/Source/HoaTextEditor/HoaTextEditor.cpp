/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaTextEditor.h"

HoaTextEditor::HoaTextEditor(const String& componentName) : TextEditor(componentName)
{
}

HoaTextEditor::~HoaTextEditor()
{
}

void HoaTextEditor::setMaster(TextEditorListener *c)
{
	m_master = c;
}

void HoaTextEditor::returnPressed()
{
	m_master->textEditorReturnKeyPressed(*this);
}

bool HoaTextEditor::keyPressed(const KeyPress& k)
{
	if(k.returnKey)
		m_master->textEditorReturnKeyPressed(*this);
	
	return TextEditor::keyPressed(k);
}