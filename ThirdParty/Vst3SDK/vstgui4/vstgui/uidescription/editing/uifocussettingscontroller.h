//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework not only for VST plugins
//
// Version 4.2
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2013, Steinberg Media Technologies, All Rights Reserved
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
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __uifocussettingscontroller__
#define __uifocussettingscontroller__

#include "../uidescription.h"

#if VSTGUI_LIVE_EDITING

#include <string>

namespace VSTGUI {

//----------------------------------------------------------------------------------------------------
class UIFocusSettingsController : public CBaseObject, public IController
{
public:
	UIFocusSettingsController (UIDescription* description);
	~UIFocusSettingsController ();

	CMessageResult notify (CBaseObject* sender, IdStringPtr message) VSTGUI_OVERRIDE_VMETHOD;
	CView* verifyView (CView* view, const UIAttributes& attributes, IUIDescription* description) VSTGUI_OVERRIDE_VMETHOD;
	void valueChanged (CControl* control) VSTGUI_OVERRIDE_VMETHOD;
protected:
	static bool valueToString (float value, char utf8String[256], void* userData);
	static bool stringToValue (UTF8StringPtr txt, float& result, void* userData);

	SharedPointer<UIDescription> editDescription;
	UIAttributes* settings;

	enum {
		kEnabledTag = 0,
		kColorTag,
		kWidthTag,
		kNumTags
	};
	CControl* controls[kNumTags];
};

} // namespace

#endif // VSTGUI_LIVE_EDITING

#endif // __uifocussettingscontroller__
