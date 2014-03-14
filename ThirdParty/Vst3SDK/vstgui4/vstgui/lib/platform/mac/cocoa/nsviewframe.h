//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
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

#ifndef __nsviewframe__
#define __nsviewframe__

#include "../../../cframe.h"

#if MAC_COCOA

#include <list>

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
struct NSView;
struct NSRect;
#endif

namespace VSTGUI {
class CocoaTooltipWindow;

//-----------------------------------------------------------------------------
class NSViewFrame : public IPlatformFrame
{
public:
	NSViewFrame (IPlatformFrameCallback* frame, const CRect& size, NSView* parent);
	~NSViewFrame ();

	NSView* getPlatformControl () const { return nsView; }
	IPlatformFrameCallback* getFrame () const { return frame; }
	
	void setLastDragOperationResult (CView::DragResult result) { lastDragOperationResult = result; }
	void setIgnoreNextResignFirstResponder (bool state) { ignoreNextResignFirstResponder = state; }
	bool getIgnoreNextResignFirstResponder () const { return ignoreNextResignFirstResponder; }

	void initTrackingArea ();
	void cursorUpdate ();
	virtual void drawRect (NSRect* rect);

	// IPlatformFrame
	bool getGlobalPosition (CPoint& pos) const VSTGUI_OVERRIDE_VMETHOD;
	bool setSize (const CRect& newSize) VSTGUI_OVERRIDE_VMETHOD;
	bool getSize (CRect& size) const VSTGUI_OVERRIDE_VMETHOD;
	bool getCurrentMousePosition (CPoint& mousePosition) const VSTGUI_OVERRIDE_VMETHOD;
	bool getCurrentMouseButtons (CButtonState& buttons) const VSTGUI_OVERRIDE_VMETHOD;
	bool setMouseCursor (CCursorType type) VSTGUI_OVERRIDE_VMETHOD;
	bool invalidRect (const CRect& rect) VSTGUI_OVERRIDE_VMETHOD;
	bool scrollRect (const CRect& src, const CPoint& distance) VSTGUI_OVERRIDE_VMETHOD;
	bool showTooltip (const CRect& rect, const char* utf8Text) VSTGUI_OVERRIDE_VMETHOD;
	bool hideTooltip () VSTGUI_OVERRIDE_VMETHOD;
	void* getPlatformRepresentation () const VSTGUI_OVERRIDE_VMETHOD { return nsView; }
	IPlatformTextEdit* createPlatformTextEdit (IPlatformTextEditCallback* textEdit) VSTGUI_OVERRIDE_VMETHOD;
	IPlatformOptionMenu* createPlatformOptionMenu () VSTGUI_OVERRIDE_VMETHOD;
#if VSTGUI_OPENGL_SUPPORT
	IPlatformOpenGLView* createPlatformOpenGLView () VSTGUI_OVERRIDE_VMETHOD;
#endif
	IPlatformViewLayer* createPlatformViewLayer (IPlatformViewLayerDelegate* drawDelegate, IPlatformViewLayer* parentLayer = 0) VSTGUI_OVERRIDE_VMETHOD;
	COffscreenContext* createOffscreenContext (CCoord width, CCoord height) VSTGUI_OVERRIDE_VMETHOD;
	CView::DragResult doDrag (IDataPackage* source, const CPoint& offset, CBitmap* dragBitmap) VSTGUI_OVERRIDE_VMETHOD;
	void setClipboard (IDataPackage* data) VSTGUI_OVERRIDE_VMETHOD;
	IDataPackage* getClipboard () VSTGUI_OVERRIDE_VMETHOD;

//-----------------------------------------------------------------------------
protected:
	static void initClass ();

	IPlatformFrameCallback* frame;
	NSView* nsView;
	CocoaTooltipWindow* tooltipWindow;

	CView::DragResult lastDragOperationResult;
	bool ignoreNextResignFirstResponder;
	bool trackingAreaInitialized;
	bool inDraw;
	CCursorType cursor;
};

} // namespace

#endif // MAC_COCOA
#endif // __nsviewframe__
