//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Examples
// Filename    : public.sdk/samples/vst/note_expression_synth/source/note_expression_synth_ui.h
// Created by  : Steinberg, 12/2010
// Description : Note Expression Synth UI version using VSTGUI 4
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2013, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __note_expression_synth_ui__
#define __note_expression_synth_ui__

#include "note_expression_synth_controller.h"
#include "note_expression_synth_processor.h"
#include "vstgui/plugin-bindings/vst3editor.h"

namespace Steinberg {
namespace Vst {
namespace NoteExpressionSynth {

//-----------------------------------------------------------------------------
/** Example Note Expression Audio Controller + User Interface */
class ControllerWithUI : public Controller, public VST3EditorDelegate
{
public:
	
	virtual IPlugView* PLUGIN_API createView (FIDString name);
	// VST3EditorDelegate
	IController* createSubController (UTF8StringPtr name, IUIDescription* description, VST3Editor* editor) VSTGUI_OVERRIDE_VMETHOD;

	static FUnknown* createInstance (void*) { return (IEditController*)new ControllerWithUI (); }

	static FUID cid;
};

//-----------------------------------------------------------------------------
/** Example Note Expression Audio Processor + User Interface */
class ProcessorWithUIController : public Processor
{
public:
	ProcessorWithUIController ();

	static FUnknown* createInstance (void*) { return (IAudioProcessor*)new ProcessorWithUIController (); }

	static FUID cid;
};

}}} // namespaces

#endif // __note_expression_synth_ui__
