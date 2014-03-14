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

#ifndef __cview__
#define __cview__

#include "vstguibase.h"
#include "cpoint.h"
#include "crect.h"
#include "vstkeycode.h"
#include <map>

namespace VSTGUI {
class CDrawContext;
class CGraphicsPath;
class CDragContainer;
class IDataPackage;
class VSTGUIEditorInterface;
class CBitmap;
class CFrame;
class CViewAttributeEntry;
#if VSTGUI_TOUCH_EVENT_HANDLING
class ITouchEvent;
#endif

namespace Animation {
	class IAnimationTarget;
	class ITimingFunction;
}

//----------------------------
// @brief Mouse Wheel Axis
//----------------------------
enum CMouseWheelAxis
{
	kMouseWheelAxisX = 0,
	kMouseWheelAxisY
};

//----------------------------
// @brief Mouse Event Results
//----------------------------
enum CMouseEventResult
{
	kMouseEventNotImplemented = 0,
	kMouseEventHandled,
	kMouseEventNotHandled,
	kMouseDownEventHandledButDontNeedMovedOrUpEvents,
	kMouseMoveEventHandledButDontNeedMoreEvents
};

//----------------------------
// @brief Cursor Type
//----------------------------
enum CCursorType
{
	kCursorDefault = 0,				///< arrow cursor
	kCursorWait,					///< wait cursor
	kCursorHSize,					///< horizontal size cursor
	kCursorVSize,					///< vertical size cursor
	kCursorSizeAll,					///< size all cursor
	kCursorNESWSize,				///< northeast and southwest size cursor
	kCursorNWSESize,				///< northwest and southeast size cursor
	kCursorCopy,					///< copy cursor (mainly for drag&drop operations)
	kCursorNotAllowed,				///< not allowed cursor (mainly for drag&drop operations)
	kCursorHand						///< hand cursor
};

//----------------------------
// @brief View Autosizing
//----------------------------
enum CViewAutosizing
{
	kAutosizeNone			= 0,
	kAutosizeLeft			= 1 << 0,
	kAutosizeTop			= 1 << 1,
	kAutosizeRight			= 1 << 2,
	kAutosizeBottom			= 1 << 3,
	kAutosizeColumn			= 1 << 4,	///< view containers treat their children as columns
	kAutosizeRow			= 1 << 5,	///< view containers treat their children as rows
	kAutosizeAll			= kAutosizeLeft | kAutosizeTop | kAutosizeRight | kAutosizeBottom
};

//-----------------------------------------------------------------------------
// Definitions of special characters in a platform independent way
extern UTF8StringPtr kDegreeSymbol;			///< degree sign
extern UTF8StringPtr kInfiniteSymbol;		///< infinity
extern UTF8StringPtr kCopyrightSymbol;		///< copyright sign
extern UTF8StringPtr kTrademarkSymbol;		///< trade mark sign
extern UTF8StringPtr kRegisteredSymbol;		///< registered sign
extern UTF8StringPtr kMicroSymbol;			///< micro sign
extern UTF8StringPtr kPerthousandSymbol;	///< per mille sign

//-----------------------------------------------------------------------------
extern IdStringPtr kMsgViewSizeChanged;		///< Message send to parent that the size of the view has changed

//-----------------------------------------------------------------------------
typedef uint32_t CViewAttributeID;
//-----------------------------------------------------------------------------
// Attributes
//		all attributes where the first letter is lowercase are reserved for the vstgui lib

extern const CViewAttributeID kCViewAttributeReferencePointer;	// 'cvrp'
extern const CViewAttributeID kCViewTooltipAttribute;			// 'cvtt'
extern const CViewAttributeID kCViewControllerAttribute;		// 'ictr' ///< see @ref IController

//----------------------------
// @brief Button Types (+modifiers)
//----------------------------
enum CButton
{
	kLButton			= 1 << 1,	///< left mouse button
	kMButton			= 1 << 2,	///< middle mouse button
	kRButton			= 1 << 3,	///< right mouse button
	kShift				= 1 << 4,	///< shift modifier
	kControl			= 1 << 5,	///< control modifier (Command Key on Mac OS X and Control Key on Windows)
	kAlt				= 1 << 6,	///< alt modifier
	kApple				= 1 << 7,	///< apple modifier (Mac OS X only. Is the Control key)
	kButton4			= 1 << 8,	///< 4th mouse button
	kButton5			= 1 << 9,	///< 5th mouse button
	kDoubleClick		= 1 << 10,	///< mouse button is double click
	kMouseWheelInverted	= 1 << 11	///< system mouse wheel setting is inverted (Only valid for onMouseWheel methods). The distance value is already transformed back to non inverted. But for scroll views we need to know if we need to invert it back.
};

//-----------------------------------------------------------------------------
// CButtonState Declaration
//! @brief Button and Modifier state
//-----------------------------------------------------------------------------
class CButtonState
{
public:
	CButtonState (int32_t state = 0) : state (state) {}
	CButtonState (const CButtonState& bs) : state (bs.state) {}
	
	int32_t getButtonState () const { return state & (kLButton | kRButton | kMButton | kButton4 | kButton5); }
	int32_t getModifierState () const { return state & (kShift | kAlt | kControl | kApple); }

	/** returns true if only the left button is set. Ignores modifier state */
	bool isLeftButton () const { return getButtonState () == kLButton; }
	/** returns true if only the right button is set. Ignores modifier state */
	bool isRightButton () const { return getButtonState () == kRButton; }

	bool isDoubleClick () const { return (state & kDoubleClick) ? true : false; }

	int32_t operator() () const { return state; }
	CButtonState& operator= (int32_t s) { state = s; return *this; }
	CButtonState& operator&= (int32_t s) { state &= s; return *this; }
	CButtonState& operator|= (int32_t s) { state |= s; return *this; }

	int32_t operator& (const CButtonState& s) const { return state & s.state; }
	int32_t operator| (const CButtonState& s) const { return state | s.state; }
	int32_t operator~ () const { return ~state; }

	bool operator== (const CButtonState& s) const { return state == s.state; }
	bool operator!= (const CButtonState& s) const { return state != s.state; }
protected:
	int32_t state;
};

//-----------------------------------------------------------------------------
// CView Declaration
//! @brief Base Class of all view objects
/// @ingroup views
//-----------------------------------------------------------------------------
class CView : public CBaseObject
{
public:
	CView (const CRect& size);
	CView (const CView& view);

	//-----------------------------------------------------------------------------
	/// @name Draw and Update Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void draw (CDrawContext *pContext);															///< called if the view should draw itself
	virtual void drawRect (CDrawContext *pContext, const CRect& updateRect) { draw (pContext); }		///< called if the view should draw itself
	virtual bool checkUpdate (const CRect& updateRect) const { return updateRect.rectOverlap (size); }

	virtual bool isDirty () const { return (viewFlags & kDirty) ? true : false; }						///< check if view is dirty
	virtual void setDirty (bool val = true);															///< set the view to dirty so that it is redrawn in the next idle. Thread Safe !
	static bool kDirtyCallAlwaysOnMainThread;															///< if this is true, setting a view dirty will call invalid() instead of checking it in idle. Default value is false.

	virtual void invalidRect (const CRect& rect);														///< mark rect as invalid
	virtual void invalid () { setDirty (false); invalidRect (size); }									///< mark whole view as invalid

	virtual void setVisible (bool state);																///< set visibility state
	bool isVisible () const { return (viewFlags & kVisible) && alphaValue > 0.f; }						///< get visibility state
	//@}

	//-----------------------------------------------------------------------------
	/// @name Mouse Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual CMouseEventResult onMouseDown (CPoint& where, const CButtonState& buttons);											///< called when a mouse down event occurs
	virtual CMouseEventResult onMouseUp (CPoint& where, const CButtonState& buttons);											///< called when a mouse up event occurs
	virtual CMouseEventResult onMouseMoved (CPoint& where, const CButtonState& buttons);										///< called when a mouse move event occurs
	virtual CMouseEventResult onMouseCancel ();																					///< called when mouse tracking should be canceled

	virtual CMouseEventResult onMouseEntered (CPoint& where, const CButtonState& buttons) {return kMouseEventNotImplemented;}	///< called when the mouse enters this view
	virtual CMouseEventResult onMouseExited (CPoint& where, const CButtonState& buttons) {return kMouseEventNotImplemented;}	///< called when the mouse leaves this view

	void setHitTestPath (CGraphicsPath* path);
	virtual bool hitTest (const CPoint& where, const CButtonState& buttons = -1);												///< check if where hits this view

	virtual bool onWheel (const CPoint& where, const float& distance, const CButtonState& buttons);									///< called if a mouse wheel event is happening over this view
	virtual bool onWheel (const CPoint& where, const CMouseWheelAxis& axis, const float& distance, const CButtonState& buttons);	///< called if a mouse wheel event is happening over this view

	virtual void setMouseEnabled (bool bEnable = true);											///< turn on/off mouse usage for this view
	virtual bool getMouseEnabled () const { return viewFlags & kMouseEnabled; }					///< get the state of wheather this view uses the mouse or not

	virtual void setMouseableArea (const CRect& rect)  { mouseableArea = rect; }				///< set the area in which the view reacts to the mouse
	virtual CRect& getMouseableArea (CRect& rect) const { rect = mouseableArea; return rect;}	///< get the area in which the view reacts to the mouse
	virtual const CRect& getMouseableArea () const { return mouseableArea; }					///< read only access to the mouseable area
	//@}

#if VSTGUI_TOUCH_EVENT_HANDLING
	//-----------------------------------------------------------------------------
	/// @name Touch Event Handling Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void onTouchEvent (ITouchEvent& event) {}
	virtual bool wantsMultiTouchEvents () const { return false; }
	//@}
#endif

	//-----------------------------------------------------------------------------
	/// @name Drag & Drop Methods
	//-----------------------------------------------------------------------------
	//@{
	enum DragResult {
		kDragRefused = 0,
		kDragMoved,
		kDragCopied,
		kDragError = -1
	};
	virtual DragResult doDrag (IDataPackage* source, const CPoint& offset = CPoint (0, 0), CBitmap* dragBitmap = 0);	///< start a drag operation. See CDropSource to create the source data package
	virtual bool onDrop (IDataPackage* drag, const CPoint& where) { return false; }				///< called if a drag is dropped onto this view
	virtual void onDragEnter (IDataPackage* drag, const CPoint& where) {}						///< called if a drag is entering this view
	virtual void onDragLeave (IDataPackage* drag, const CPoint& where) {}						///< called if a drag is leaving this view
	virtual void onDragMove (IDataPackage* drag, const CPoint& where) {}						///< called if a drag is moved inside this view
	//@}

	//-----------------------------------------------------------------------------
	/// @name Keyboard Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual int32_t onKeyDown (VstKeyCode& keyCode);											///< called if a key down event occurs and this view has focus
	virtual int32_t onKeyUp (VstKeyCode& keyCode);												///< called if a key up event occurs and this view has focus
	//@}

	//-----------------------------------------------------------------------------
	/// @name View Size Methods
	//-----------------------------------------------------------------------------
	//@{
	CCoord getHeight () const { return size.height (); }										///< get the height of the view
	CCoord getWidth ()  const { return size.width (); }											///< get the width of the view
	virtual void setViewSize (const CRect& rect, bool invalid = true);							///< set views size
	CRect& getViewSize (CRect& rect) const { rect = size; return rect; }						///< returns the current view size
	const CRect& getViewSize () const { return size; }											///< read only access to view size
	virtual CRect getVisibleViewSize () const;													///< returns the visible size of the view
	virtual void parentSizeChanged () {}														///< notification that one of the views parent has changed its size
	virtual CPoint& frameToLocal (CPoint& point) const;											///< conversion from frame coordinates to local view coordinates
	virtual CPoint& localToFrame (CPoint& point) const;											///< conversion from local view coordinates to frame coordinates
	virtual void setAutosizeFlags (int32_t flags) { autosizeFlags = flags; }					///< set autosize flags
	virtual int32_t getAutosizeFlags () const { return autosizeFlags; }							///< get autosize flags
	virtual bool sizeToFit () { return false; }													///< resize view to optimal size
	//@}

	//-----------------------------------------------------------------------------
	/// @name Focus Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void looseFocus ();																	///< called if view should loose focus
	virtual void takeFocus ();																	///< called if view should take focus
	virtual bool wantsFocus () const { return (viewFlags & kWantsFocus) ? true : false; }		///< check if view supports focus
	virtual void setWantsFocus (bool state);													///< set focus support on/off
	//@}

	//-----------------------------------------------------------------------------
	/// @name Attribute Methods
	//-----------------------------------------------------------------------------
	//@{
	bool getAttributeSize (const CViewAttributeID id, int32_t& outSize) const;									///< get the size of an attribute
	bool getAttribute (const CViewAttributeID id, const int32_t inSize, void* outData, int32_t& outSize) const;	///< get an attribute
	bool setAttribute (const CViewAttributeID id, const int32_t inSize, const void* inData);						///< set an attribute
	bool removeAttribute (const CViewAttributeID id);																///< remove an attribute
	//@}

	//-----------------------------------------------------------------------------
	/// @name Background Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void setBackground (CBitmap* background);											///< set the background image of this view
	CBitmap* getBackground () const { return pBackground; }										///< get the background image of this view

	virtual void setDisabledBackground (CBitmap* background);									///< set background image used when the mouse is not enabled
	CBitmap* getDisabledBackground () const { return pDisabledBackground; }						///< get background image used when the mouse is not enabled

	CBitmap* getDrawBackground () const { return (pDisabledBackground ? (getMouseEnabled () ? pBackground : pDisabledBackground): pBackground); }
	//@}

	//-----------------------------------------------------------------------------
	/// @name Transparency Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void setTransparency (bool val);															///< set views transparent state
	virtual bool getTransparency () const { return (viewFlags & kTransparencyEnabled) ? true : false; }	///< get views transparent state

	virtual void setAlphaValue (float alpha);													///< set alpha value which will be applied when drawing this view
	float getAlphaValue () const { return alphaValue; }											///< get alpha value
	//@}

	//-----------------------------------------------------------------------------
	/// @name Attaching Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual bool removed (CView* parent);														///< view is removed from parent view
	virtual bool attached (CView* parent);														///< view is attached to a parent view
	bool isAttached () const { return (viewFlags & kIsAttached) ? true : false; }				///< is view attached to a parentView
	//@}

	//-----------------------------------------------------------------------------
	/// @name Parent Methods
	//-----------------------------------------------------------------------------
	//@{
	CView* getParentView () const { return pParentView; }										///< get parent view
	CFrame* getFrame () const { return pParentFrame; }											///< get frame
	virtual VSTGUIEditorInterface* getEditor () const;											///< get editor
	//@}

	//-----------------------------------------------------------------------------
	/// @name Animation Methods
	//-----------------------------------------------------------------------------
	//@{
	void addAnimation (IdStringPtr name, Animation::IAnimationTarget* target, Animation::ITimingFunction* timingFunction, CBaseObject* notificationObject = 0);
	void removeAnimation (IdStringPtr name);
	void removeAllAnimations ();
	//@}
	
	//-----------------------------------------------------------------------------
	/// @name Idle Methods
	//! Should be used when a view needs to do a task periodically.
	//! The onIdle() method will be called only if the view is attached.
	//-----------------------------------------------------------------------------
	//@{
	virtual void onIdle () {}																	///< called on idle when view wants idle
	void setWantsIdle (bool state);																///< enable/disable onIdle() callback
	bool wantsIdle () const { return (viewFlags & kWantsIdle) ? true : false; }					///< returns if the view wants idle callback or not
	static int32_t idleRate;																	///< global idle rate in Hz, defaults to 30 Hz
	//@}

	#if DEBUG
	virtual void dumpInfo ();
	#endif

	// overwrites
	CMessageResult notify (CBaseObject* sender, IdStringPtr message) VSTGUI_OVERRIDE_VMETHOD;

	//-------------------------------------------
	CLASS_METHODS(CView, CBaseObject)
protected:
	~CView ();

	CGraphicsPath* getHitTestPath () const { return pHitTestPath; }
	
	CRect  size;
	CRect  mouseableArea;

	CFrame* pParentFrame;
	CView* pParentView;

	enum {
		kMouseEnabled			= 1 << 0,
		kTransparencyEnabled	= 1 << 1,
		kWantsFocus				= 1 << 2,
		kIsAttached				= 1 << 3,
		kVisible				= 1 << 4,
		kDirty					= 1 << 5,
		kWantsIdle				= 1 << 6,
		kLastCViewFlag			= 6
	};
	int32_t viewFlags;
	
	int32_t autosizeFlags;
	
	float alphaValue;

private:
	SharedPointer<CBitmap> pBackground;
	SharedPointer<CBitmap> pDisabledBackground;
	SharedPointer<CGraphicsPath> pHitTestPath;

	std::map<CViewAttributeID, CViewAttributeEntry*> attributes;

#if DEBUG
public:
	// these are here so that inherited classes which have not changed the buttons parameter type will fail on compilation
	virtual char onMouseDown (CPoint &where, const long& buttons) {return kMouseEventNotImplemented;}
	virtual char onMouseUp (CPoint &where, const long& buttons) {return kMouseEventNotImplemented;}
	virtual char onMouseMoved (CPoint &where, const long& buttons) {return kMouseEventNotImplemented;}
	virtual char onMouseEntered (CPoint &where, const long& buttons) {return kMouseEventNotImplemented;}
	virtual char onMouseExited (CPoint &where, const long& buttons) {return kMouseEventNotImplemented;}
	virtual long hitTest (const CPoint& where, const long buttons = -1) { return false;}
	virtual long onWheel (const CPoint &where, const float &distance, const long &buttons) { return false; }
	virtual long onWheel (const CPoint &where, const CMouseWheelAxis &axis, const float &distance, const long &buttons) { return false; }
#endif
};

//-----------------------------------------------------------------------------
///	@brief Helper class to port old code which used CDragContainer
///	@ingroup new_in_4_2
//-----------------------------------------------------------------------------
class CDragContainerHelper
{
public:
	CDragContainerHelper (IDataPackage* drag);

	void* first (int32_t& size, int32_t& type);
	void* next (int32_t& size, int32_t& type);
	
	int32_t getType (int32_t idx) const;
	int32_t getCount () const;
	
	enum CDragType {
		kFile = 0,								///< File (MacOSX = UTF8 String)
		kText,									///< ASCII Text
		kUnicodeText,							///< UTF8 Text
		
		kUnknown = -1,
		kError = -2
	};
protected:
	
	IDataPackage* drag;
	int32_t index;
};

} // namespace

#endif
