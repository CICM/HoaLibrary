//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins :
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

#include "cscrollview.h"
#include "cvstguitimer.h"
#include "cdrawcontext.h"
#include "cframe.h"
#include "animation/animations.h"
#include "animation/timingfunctions.h"
#include <cmath>

/// @cond ignore
namespace VSTGUI {

// CScrollContainer is private
//-----------------------------------------------------------------------------
class CScrollContainer : public CViewContainer
//-----------------------------------------------------------------------------
{
public:
	CScrollContainer (const CRect &size, const CRect &containerSize);
	CScrollContainer (const CScrollContainer& v);
	~CScrollContainer ();

	void setScrollOffset (CPoint offset, bool withRedraw = false);
	void getScrollOffset (CPoint& off) const { off = offset; }
	const CPoint& getScrollOffset () const { return offset; }

	CRect getContainerSize () const { return containerSize; }
	void setContainerSize (const CRect& cs);

	bool isDirty () const;

	void onDragMove (IDataPackage* drag, const CPoint& where);
	void setAutoDragScroll (bool state) { autoDragScroll = state; }

	bool attached (CView* parent);
	CMessageResult notify (CBaseObject* sender, IdStringPtr message);

	CLASS_METHODS(CScrollContainer, CViewContainer)
//-----------------------------------------------------------------------------
protected:
	bool getScrollValue (const CPoint& where, float& x, float& y);

	CRect containerSize;
	CPoint offset;
	bool autoDragScroll;
	bool inScrolling;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CScrollContainer::CScrollContainer (const CRect &size, const CRect &containerSize)
: CViewContainer (size)
, containerSize (containerSize)
, offset (CPoint (0, 0))
, autoDragScroll (false)
, inScrolling (false)
{
	setTransparency (true);
}

//-----------------------------------------------------------------------------
CScrollContainer::CScrollContainer (const CScrollContainer& v)
: CViewContainer (v)
, containerSize (v.containerSize)
, offset (v.offset)
, inScrolling (false)
{
}

//-----------------------------------------------------------------------------
CScrollContainer::~CScrollContainer ()
{
}


//-----------------------------------------------------------------------------
void CScrollContainer::setContainerSize (const CRect& cs)
{
	containerSize = cs;
	setScrollOffset (offset, false);
}

//-----------------------------------------------------------------------------
void CScrollContainer::setScrollOffset (CPoint newOffset, bool redraw)
{
	newOffset.x = floor (newOffset.x + 0.5);
	newOffset.y = floor (newOffset.y + 0.5);
	if (containerSize.getWidth () >= getViewSize ().width ())
	{
		if (newOffset.x < containerSize.left - (containerSize.width () - getViewSize ().width ()))
			newOffset.x = containerSize.left - (containerSize.width () - getViewSize ().width ());
	}
	else
	{
		if (newOffset.x < containerSize.left - containerSize.width ())
			newOffset.x = containerSize.left - containerSize.width ();
	}
	if (newOffset.x > containerSize.right)
		newOffset.x = containerSize.right;
	if (newOffset.y < containerSize.top)
		newOffset.y = containerSize.top;
	if (newOffset.y > containerSize.bottom)
		newOffset.y = containerSize.bottom;
	CPoint diff ((int32_t)(newOffset.x - offset.x), (int32_t)(offset.y - newOffset.y));
	if (diff.x == 0 && diff.y == 0)
		return;
	inScrolling = true;
	FOREACHSUBVIEW
		CRect r;
		pV->getViewSize (r);
		r.offset (diff.x , diff.y);
		pV->setViewSize (r, false);
		pV->getMouseableArea (r);
		r.offset (diff.x , diff.y);
		pV->setMouseableArea (r);
	ENDFOREACHSUBVIEW
	inScrolling = false;
	offset = newOffset;
	if (!isAttached ())
		return;

	if (getTransparency ())
	{
		invalid ();
	}
	else
	{
		CRect scrollRect (0, 0, getViewSize ().getWidth (), getViewSize ().getHeight ());
		CPoint p;
		localToFrame (p);
		scrollRect.offset (p.x, p.y);
		CRect visibleRect = getVisibleSize (CRect (0, 0, getViewSize ().getWidth (), getViewSize ().getHeight ()));
		visibleRect.offset (p.x, p.y);
		scrollRect.bound (visibleRect);

		CPoint distance (diff.x, diff.y);
		if (distance.x > 0)
			scrollRect.right -= distance.x;
		else if (distance.x < 0)
			scrollRect.left -= distance.x;
		if (distance.y > 0)
			scrollRect.bottom -= distance.y;
		else if (distance.y < 0)
			scrollRect.top -= distance.y;
		getFrame ()->scrollRect (scrollRect, distance);
	}
}

//-----------------------------------------------------------------------------
bool CScrollContainer::isDirty () const
{
	if (CView::isDirty ())
		return true;

	FOREACHSUBVIEW
		if (pV->isDirty () && pV->isVisible ())
		{
			CRect r = pV->getVisibleViewSize ();
			if (r.getWidth () > 0 && r.getHeight () > 0)
				return true;
			else
				pV->setDirty (false);
		}
	ENDFOREACHSUBVIEW
	return false;
}

//-----------------------------------------------------------------------------
bool CScrollContainer::getScrollValue (const CPoint& where, float& x, float& y)
{
	const CCoord kWidth = 10;
	x = 0.f;
	y = 0.f;
	if (where.x <= getViewSize ().left + kWidth)
	{
		x = (float)(where.x - (getViewSize ().left + kWidth));
	}
	else if (where.x >= getViewSize ().right - kWidth)
	{
		x = (float)(where.x - (getViewSize ().right - kWidth));
	}
	if (where.y <= getViewSize ().top + kWidth)
	{
		y = (float)(where.y - (getViewSize ().top + kWidth));
	}
	else if (where.y >= getViewSize ().bottom - kWidth)
	{
		y = (float)(where.y - (getViewSize ().bottom - kWidth));
	}
	return (x != 0.f || y != 0.f);
}

//-----------------------------------------------------------------------------
void CScrollContainer::onDragMove (IDataPackage* drag, const CPoint& where)
{
	if (autoDragScroll)
	{
		float x, y;
		if (getScrollValue (where, x, y))
		{
			CScrollView* scrollView = static_cast<CScrollView*> (getParentView ());
			if (scrollView)
			{
				CRect r (getViewSize ());
				r.offset (x, y);
				scrollView->makeRectVisible (r);
			}
		}
	}
	return CViewContainer::onDragMove (drag, where);
}

//-----------------------------------------------------------------------------
bool CScrollContainer::attached (CView* parent)
{
	bool result = CViewContainer::attached (parent);
	if (getNbViews () == 1)
	{
		CView* view = getView (0);
		if (view)
		{
			CRect r (view->getViewSize ());
			CRect newContainerSize (containerSize);
			newContainerSize.setWidth (r.getWidth ());
			newContainerSize.setHeight (r.getHeight ());
			if (newContainerSize != containerSize)
			{
				CScrollView* scrollView = (CScrollView*)getParentView ();
				scrollView->setContainerSize (newContainerSize);
			}
		}
	}
	return result;
}

//-----------------------------------------------------------------------------
CMessageResult CScrollContainer::notify (CBaseObject* sender, IdStringPtr message)
{
	if (message == kMsgViewSizeChanged && !inScrolling)
	{
		int32_t numSubViews = getNbViews ();
		CView* view = static_cast<CView*> (sender);
		if (numSubViews == 1 && view && isChild (view))
		{
			CRect r (view->getViewSize ());
			CRect newContainerSize (containerSize);
			newContainerSize.setWidth (r.getWidth ());
			newContainerSize.setHeight (r.getHeight ());
			if (newContainerSize != containerSize)
			{
				CScrollView* scrollView = (CScrollView*)getParentView ();
				scrollView->setContainerSize (newContainerSize);
			}
		}
	}
	return getParentView () ? getParentView ()->notify (sender, message) : kMessageUnknown;
}

/// @endcond

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CScrollView::CScrollView (const CRect &size, const CRect &containerSize, int32_t style, CCoord scrollbarWidth, CBitmap* pBackground)
: CViewContainer (size)
, sc (0)
, vsb (0)
, hsb (0)
, containerSize (containerSize)
, scrollbarWidth (scrollbarWidth)
, style (style)
, activeScrollbarStyle (0)
{
	if (pBackground)
		setBackground(pBackground);
	recalculateSubViews ();
}

#if VSTGUI_ENABLE_DEPRECATED_METHODS
//-----------------------------------------------------------------------------
CScrollView::CScrollView (const CRect &size, const CRect &containerSize, CFrame* pParent, int32_t style, CCoord scrollbarWidth, CBitmap* pBackground)
: CViewContainer (size, pParent, pBackground)
, sc (0)
, vsb (0)
, hsb (0)
, containerSize (containerSize)
, scrollbarWidth (scrollbarWidth)
, style (style)
, activeScrollbarStyle (0)
{
	recalculateSubViews ();
}
#endif

//-----------------------------------------------------------------------------
CScrollView::CScrollView (const CScrollView& v)
: CViewContainer (v)
, containerSize (v.containerSize)
, style (v.style)
, activeScrollbarStyle (v.activeScrollbarStyle)
, scrollbarWidth (v.scrollbarWidth)
{
	CViewContainer::removeAll ();
	if (activeScrollbarStyle & kHorizontalScrollbar && v.hsb)
	{
		hsb = (CScrollbar*)v.hsb->newCopy ();
		hsb->setListener (this);
		CViewContainer::addView (hsb);
	}
	if (activeScrollbarStyle & kVerticalScrollbar && v.vsb)
	{
		vsb = (CScrollbar*)v.vsb->newCopy ();
		vsb->setListener (this);
		CViewContainer::addView (vsb);
	}
	sc = (CScrollContainer*)v.sc->newCopy ();
	CViewContainer::addView (sc);
}

//-----------------------------------------------------------------------------
CScrollView::~CScrollView ()
{
}

//-----------------------------------------------------------------------------
void CScrollView::recalculateSubViews ()
{
	CRect scsize (0, 0, getViewSize ().getWidth (), getViewSize ().getHeight ());
	if (!(style & kDontDrawFrame))
	{
		scsize.left++; scsize.top++;
		scsize.right-=1; scsize.bottom--;
	}
	if (style & kAutoHideScrollbars)
	{
		activeScrollbarStyle = 0;
		CRect r (scsize);
		if (style & kHorizontalScrollbar)
		{
			if (style & kVerticalScrollbar && r.getHeight () < containerSize.getHeight ())
			{
				activeScrollbarStyle |= kVerticalScrollbar;
				if (!(style & kOverlayScrollbars))
					r.right -= scrollbarWidth;
			}
			activeScrollbarStyle |= containerSize.getWidth () <= r.getWidth () ? 0 : kHorizontalScrollbar;
			if (!(style & kOverlayScrollbars))
				r.bottom -= scrollbarWidth;
			if (activeScrollbarStyle == kHorizontalScrollbar && style & kVerticalScrollbar && r.getHeight () < containerSize.getHeight ())
			{
				activeScrollbarStyle |= kVerticalScrollbar;
			}
		}
		else if (style & kVerticalScrollbar)
		{
			activeScrollbarStyle |= containerSize.getHeight () <= r.getHeight () ? 0 : kVerticalScrollbar;
		}
	}
	else
	{
		activeScrollbarStyle = (style & kHorizontalScrollbar) | (style & kVerticalScrollbar);
	}
	
	if (activeScrollbarStyle & kHorizontalScrollbar)
	{
		CRect sbr (getViewSize ());
		sbr.originize ();
		sbr.top = sbr.bottom - scrollbarWidth;
		if (activeScrollbarStyle & kVerticalScrollbar)
		{
			if (hsb && (vsb && vsb->isVisible () == false))
				hsb->invalid ();
			sbr.right -= (scrollbarWidth - 1);
		}
		if (hsb)
		{
			hsb->setViewSize (sbr, true);
			hsb->setMouseableArea (sbr);
			hsb->setVisible (true);
		}
		else
		{
			hsb = new CScrollbar (sbr, this, kHSBTag, CScrollbar::kHorizontal, containerSize);
			hsb->setAutosizeFlags (kAutosizeLeft | kAutosizeRight | kAutosizeBottom);
			CViewContainer::addView (hsb);
		}
		if (!(style & kOverlayScrollbars))
			scsize.bottom = sbr.top;
		hsb->setOverlayStyle (style & kOverlayScrollbars ? true : false);
	}
	else if (hsb)
	{
		hsb->setVisible (false);
	}
	if (activeScrollbarStyle & kVerticalScrollbar)
	{
		CRect sbr (getViewSize ());
		sbr.originize ();
		sbr.left = sbr.right - scrollbarWidth;
		if (activeScrollbarStyle & kHorizontalScrollbar)
		{
			if (vsb && (hsb  && hsb->isVisible () == false))
				vsb->invalid ();
			sbr.bottom -= (scrollbarWidth - 1);
		}
		if (vsb)
		{
			vsb->setViewSize (sbr, true);
			vsb->setMouseableArea (sbr);
			vsb->setVisible (true);
		}
		else
		{
			vsb = new CScrollbar (sbr, this, kVSBTag, CScrollbar::kVertical, containerSize);
			vsb->setAutosizeFlags (kAutosizeTop | kAutosizeRight | kAutosizeBottom);
			CViewContainer::addView (vsb);
		}
		if (!(style & kOverlayScrollbars))
			scsize.right = sbr.left;
		vsb->setOverlayStyle (style & kOverlayScrollbars ? true : false);
	}
	else if (vsb)
	{
		vsb->setVisible (false);
	}

	if (!sc)
	{
		sc = new CScrollContainer (scsize, containerSize);
		sc->setAutosizeFlags (kAutosizeAll);
		CViewContainer::addView (sc);
	}
	else
	{
		sc->setViewSize (scsize, true);
		sc->setMouseableArea (scsize);
	}
	if (style & kOverlayScrollbars)
		CViewContainer::changeViewZOrder (sc, 0);
	sc->setAutoDragScroll (style & kAutoDragScrolling ? true : false);
}

//-----------------------------------------------------------------------------
void CScrollView::setViewSize (const CRect &rect, bool invalid)
{
	CViewContainer::setViewSize (rect, invalid);
	setContainerSize (containerSize, true);
}

//-----------------------------------------------------------------------------
void CScrollView::setAutosizeFlags (int32_t flags)
{
	CViewContainer::setAutosizeFlags (flags);
	if (sc)
		sc->setAutosizeFlags (flags);
}

//-----------------------------------------------------------------------------
void CScrollView::setStyle (int32_t newStyle)
{
	if (style != newStyle)
	{
		style = newStyle;
		recalculateSubViews ();
	}
}

//-----------------------------------------------------------------------------
void CScrollView::setScrollbarWidth (CCoord width)
{
	if (scrollbarWidth != width)
	{
		scrollbarWidth = width;
		recalculateSubViews ();
	}
}

//-----------------------------------------------------------------------------
void CScrollView::setContainerSize (const CRect& cs, bool keepVisibleArea)
{
	CRect oldSize (containerSize);
	containerSize = cs;
	if (sc)
	{
		sc->setContainerSize (cs);
	}
	if (style & kAutoHideScrollbars)
		recalculateSubViews ();
	if (vsb)
	{
		CRect oldScrollSize = vsb->getScrollSize (oldScrollSize);
		float oldValue = vsb->getValue ();
		vsb->setScrollSize (cs);
		if (cs.getHeight () <= getViewSize ().getHeight ())
			vsb->setValue (0);
		else if (sc && keepVisibleArea && oldScrollSize.getHeight () != cs.getHeight ())
		{
			CRect vSize = sc->getViewSize (vSize);
			float newValue = (float)(oldValue * ((float)(oldScrollSize.getHeight () - vSize.getHeight ()) / ((float)cs.getHeight () - vSize.getHeight ())));
			if (newValue > 1.f)
				newValue = 1.f;
			else if (newValue < 0.f)
				newValue = 0.f;
			vsb->setValue (newValue);
		}
		valueChanged (vsb);
	}
	if (hsb)
	{
		CRect oldScrollSize = hsb->getScrollSize (oldScrollSize);
		float oldValue = hsb->getValue ();
		hsb->setScrollSize (cs);
		if (cs.getWidth () <= getViewSize ().getWidth ())
			hsb->setValue (0);
		else if (sc && keepVisibleArea && oldScrollSize.getWidth () != cs.getWidth ())
		{
			CRect vSize = sc->getViewSize (vSize);
			float newValue = (float)(oldValue * ((float)(oldScrollSize.getWidth () - vSize.getWidth ()) / ((float)cs.getWidth () - vSize.getWidth ())));
			if (newValue > 1.f)
				newValue = 1.f;
			else if (newValue < 0.f)
				newValue = 0.f;
			hsb->setValue (newValue);
		}
		valueChanged (hsb);
	}
}

//-----------------------------------------------------------------------------
void CScrollView::makeRectVisible (const CRect& rect)
{
	CRect r (rect);
	const CPoint& scrollOffset = sc->getScrollOffset ();
	CPoint newOffset (scrollOffset);
	CRect vs;
	sc->getViewSize (vs);
	if (!(style & kDontDrawFrame))
	{
		vs.left--; //vs.top--;
		vs.right++; //vs.bottom++;
	}
	CRect cs (containerSize);
	cs.offset (-cs.left, -cs.top);
	cs.setWidth (vs.getWidth ());
	cs.setHeight (vs.getHeight ());
	if (r.top >= cs.top && r.bottom <= cs.bottom && r.left >= cs.left && r.right <= cs.right)
		return;
	if (r.top < cs.top)
	{
		newOffset.y -= (cs.top - r.top);
	}
	else if (r.bottom > cs.bottom)
	{
		newOffset.y += (r.bottom - cs.bottom);
	}
	if (r.left < cs.left)
	{
		newOffset.x -= (cs.left + r.left);
	}
	else if (r.right > cs.right && r.left != cs.left)
	{
		newOffset.x += (cs.right - r.right);
	}
	if (vsb && newOffset.y != scrollOffset.y)
	{
		vsb->setValue ((float)(newOffset.y - vs.top) / (float)(containerSize.getHeight () - vs.getHeight ()));
		vsb->bounceValue ();
		vsb->onVisualChange ();
		vsb->invalid ();
		valueChanged (vsb);
	}
	if (hsb && newOffset.x != scrollOffset.x)
	{
		hsb->setValue (-(float)(newOffset.x - vs.left) / (float)(containerSize.getWidth () - vs.getWidth ()));
		hsb->bounceValue ();
		hsb->onVisualChange ();
		hsb->invalid ();
		valueChanged (hsb);
	}
}

//-----------------------------------------------------------------------------
void CScrollView::resetScrollOffset ()
{
	if (vsb)
	{
		vsb->setValue (0);
		vsb->bounceValue ();
		vsb->onVisualChange ();
		vsb->invalid ();
		valueChanged (vsb);
	}
	if (hsb)
	{
		hsb->setValue (0);
		hsb->bounceValue ();
		hsb->onVisualChange ();
		hsb->invalid ();
		valueChanged (hsb);
	}
}

//-----------------------------------------------------------------------------
const CPoint& CScrollView::getScrollOffset () const
{
	return sc->getScrollOffset ();
}

//-----------------------------------------------------------------------------
bool CScrollView::addView (CView *pView)
{
	return sc->addView (pView);
}

//-----------------------------------------------------------------------------
bool CScrollView::addView (CView *pView, const CRect &mouseableArea, bool mouseEnabled)
{
	return sc->addView (pView, mouseableArea, mouseEnabled);
}

//-----------------------------------------------------------------------------
bool CScrollView::addView (CView* pView, CView* pBefore)
{
	return sc->addView (pView, pBefore);
}

//-----------------------------------------------------------------------------
bool CScrollView::removeView (CView *pView, bool withForget)
{
	return sc->removeView (pView, withForget);
}

//-----------------------------------------------------------------------------
bool CScrollView::removeAll (bool withForget)
{
	return sc->removeAll ();
}

//-----------------------------------------------------------------------------
int32_t CScrollView::getNbViews () const
{
	return sc->getNbViews ();
}

//-----------------------------------------------------------------------------
CView* CScrollView::getView (int32_t index) const
{
	return sc->getView (index);
}

//-----------------------------------------------------------------------------
void CScrollView::setTransparency (bool val)
{
	CViewContainer::setTransparency (val);
}

//-----------------------------------------------------------------------------
void CScrollView::setBackgroundColor (const CColor& color)
{
	CViewContainer::setBackgroundColor (color);
}

//-----------------------------------------------------------------------------
void CScrollView::valueChanged (CControl *pControl)
{
	if (sc)
	{
		float value = pControl->getValue ();
		int32_t tag = pControl->getTag ();
		CPoint offset;
		CRect vsize = sc->getViewSize (vsize);
		CRect csize = sc->getContainerSize ();
		sc->getScrollOffset (offset);

		switch (tag)
		{
			case kHSBTag:
			{
				if (csize.getWidth () > vsize.getWidth ())
				{
					offset.x = (int32_t) (csize.left - (csize.width () - vsize.width ()) * value);
					sc->setScrollOffset (offset, false);
				}
				else if (offset.x < 0)
				{
					offset.x = 0;
					sc->setScrollOffset (offset, false);
				}
				break;
			}
			case kVSBTag:
			{
				if (csize.getHeight () > vsize.getHeight ())
				{
					offset.y = (int32_t) (csize.top + (csize.height () - vsize.height ()) * value);
					sc->setScrollOffset (offset, false);
				}
				else if (offset.y > 0)
				{
					offset.y = 0;
					sc->setScrollOffset (offset, false);
				}
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
void CScrollView::drawBackgroundRect (CDrawContext *pContext, const CRect& _updateRect)
{
	CRect r (getViewSize ());
	r.originize ();
	if ((backgroundColor.alpha != 255 && getTransparency ()) || !getTransparency ())
	{
		pContext->setDrawMode (kAliasing);
		pContext->setFillColor (backgroundColor);
		pContext->drawRect (r, kDrawFilled);
	}
	if (!(style & kDontDrawFrame))
	{
		pContext->setDrawMode (kAliasing);
		pContext->setFrameColor (backgroundColor);
		pContext->setLineWidth (1);
		pContext->drawRect (r);
	}
}

//-----------------------------------------------------------------------------
bool CScrollView::onWheel (const CPoint &where, const CMouseWheelAxis &axis, const float &distance, const CButtonState &buttons)
{
	bool result = CViewContainer::onWheel (where, axis, distance, buttons);
	if (!result)
	{
		if (vsb && axis == kMouseWheelAxisY)
			result = vsb->onWheel (where, axis, distance, buttons);
		else if (hsb && axis == kMouseWheelAxisX)
			result = hsb->onWheel (where, axis, distance, buttons);
	}
	return result;
}

//-----------------------------------------------------------------------------
CMessageResult CScrollView::notify (CBaseObject* sender, IdStringPtr message)
{
	if (message == kMsgNewFocusView && getStyle () & kFollowFocusView)
	{
		CView* focusView = (CView*)sender;
		if (sc->isChild (focusView, true))
		{
			CRect r = focusView->getViewSize ();
			CPoint p;
			focusView->localToFrame (p);
			frameToLocal (p);
			r.offset (p.x, p.y);
			makeRectVisible (r);
		}
	}
	return CViewContainer::notify (sender, message);
}

//-----------------------------------------------------------------------------
CScrollbar::CScrollbar (const CRect& size, CControlListener* listener, int32_t tag, ScrollbarDirection direction, const CRect& scrollSize)
: CControl (size, listener, tag, 0)
, direction (direction)
, scrollSize (scrollSize)
, scrollerArea (size)
, stepValue (0.1f)
, scrollerLength (0)
, overlayStyle (false)
, drawer (0)
, timer (0)
{
	setTransparency (true);
	setWheelInc (0.05f);
	scrollerArea.inset (2, 2);
	calculateScrollerLength ();
	frameColor (0, 0, 0, 255);
	scrollerColor (0, 0, 255, 255);
	backgroundColor (255, 255, 255, 200);
}

//-----------------------------------------------------------------------------
CScrollbar::CScrollbar (const CScrollbar& v)
: CControl (v)
, direction (v.direction)
, scrollSize (v.scrollSize)
, scrollerArea (v.scrollerArea)
, stepValue (v.stepValue)
, scrollerLength (v.scrollerLength)
, frameColor (v.frameColor)
, scrollerColor (v.scrollerColor)
, backgroundColor (v.backgroundColor)
, overlayStyle (v.overlayStyle)
, drawer (v.drawer)
, timer (0)
{
	calculateScrollerLength ();
}

//-----------------------------------------------------------------------------
CScrollbar::~CScrollbar ()
{
}

//-----------------------------------------------------------------------------
void CScrollbar::setViewSize (const CRect &newSize, bool invalid)
{
	scrollerArea = newSize;
	scrollerArea.inset (2, 2);
	CControl::setViewSize (newSize, invalid);
	calculateScrollerLength ();
}

//-----------------------------------------------------------------------------
void CScrollbar::setScrollSize (const CRect& ssize)
{
	if (scrollSize != ssize)
	{
		scrollSize = ssize;
		calculateScrollerLength ();
		setDirty (true);
	}
}

//-----------------------------------------------------------------------------
void CScrollbar::calculateScrollerLength ()
{
	CCoord newScrollerLength;
	if (direction == kHorizontal)
	{
		float factor = (float)getViewSize ().width () / (float)scrollSize.width ();
		if (factor >= 1.f)
			factor = 0;
		newScrollerLength = (CCoord) (getViewSize ().width () * factor);
	}
	else
	{
		float factor = (float)getViewSize ().height () / (float)scrollSize.height ();
		if (factor >= 1.f)
			factor = 0;
		newScrollerLength = (CCoord) (getViewSize ().height () * factor);
	}
	if (newScrollerLength != scrollerLength)
	{
		scrollerLength = newScrollerLength;
		setDirty (true);
	}
}

//-----------------------------------------------------------------------------
CRect CScrollbar::getScrollerRect ()
{
	CRect scrollerRect (scrollerArea);
	CCoord l = (direction == kHorizontal) ? scrollerArea.width () : scrollerArea.height ();
	CCoord scrollerOffset = (CCoord) (value * (l - scrollerLength));
	if (direction == kHorizontal)
	{
		scrollerRect.setWidth (scrollerLength);
		scrollerRect.offset (scrollerOffset, 0);
	}
	else
	{
		scrollerRect.setHeight (scrollerLength);
		scrollerRect.offset (0, scrollerOffset);
	}
	return scrollerRect;
}

//-----------------------------------------------------------------------------
void CScrollbar::doStepping ()
{
	CRect scrollerRect = getScrollerRect ();
	if (timer)
	{
		if (!startPoint.isInside (getViewSize ()) || startPoint.isInside (scrollerRect))
			return;
	}
	bool dir = (direction == kHorizontal && startPoint.x < scrollerRect.left) || (direction == kVertical && startPoint.y < scrollerRect.top);
	float newValue;
	if (direction == kHorizontal)
	{
		if (dir)
			newValue = value - (float)scrollerLength / (float)scrollerArea.width ();
		else
			newValue = value + (float)scrollerLength / (float)scrollerArea.width ();
	}
	else
	{
		if (dir)
			newValue = value - (float)scrollerLength / (float)scrollerArea.height ();
		else
			newValue = value + (float)scrollerLength / (float)scrollerArea.height ();
	}
	if (newValue < 0.f) newValue = 0.f;
	if (newValue > 1.f) newValue = 1.f;
	if (newValue != value)
	{
		value = newValue;
		valueChanged ();
		invalid ();
	}
}

//-----------------------------------------------------------------------------
CMessageResult CScrollbar::notify (CBaseObject* sender, IdStringPtr message)
{
	if (message == CVSTGUITimer::kMsgTimer && timer)
	{
		doStepping ();
		timer->setFireTime (80);
		return kMessageNotified;
	}
	return kMessageUnknown;
}

//-----------------------------------------------------------------------------
void CScrollbar::setOverlayStyle (bool state)
{
	if (overlayStyle != state)
	{
		overlayStyle = state;
		setAlphaValue (overlayStyle ? 0.001f : 1.f);
	}
}

//-----------------------------------------------------------------------------
CMouseEventResult CScrollbar::onMouseEntered (CPoint& where, const CButtonState& buttons)
{
	if (overlayStyle)
	{
		addAnimation ("AlphaValueAnimation", new Animation::AlphaValueAnimation (1.f), new Animation::LinearTimingFunction (100));
	}
	return kMouseEventNotHandled;
}

//-----------------------------------------------------------------------------
CMouseEventResult CScrollbar::onMouseExited (CPoint& where, const CButtonState& buttons)
{
	if (overlayStyle)
	{
		Animation::ITimingFunction* timingFunction = 0;
		if (getAlphaValue () == 1.f)
		{
			Animation::InterpolationTimingFunction* interpolTimingFunction = new Animation::InterpolationTimingFunction (400);
			interpolTimingFunction->addPoint (300.f/400.f, 1.f);
			timingFunction = interpolTimingFunction;
		}
		else
			timingFunction = new Animation::LinearTimingFunction (100);
		addAnimation ("AlphaValueAnimation", new Animation::AlphaValueAnimation (0.001f), timingFunction);
	}
	return kMouseEventNotHandled;
}

//-----------------------------------------------------------------------------
CMouseEventResult CScrollbar::onMouseDown (CPoint &where, const CButtonState& buttons)
{
	if (buttons != kLButton || scrollerLength == 0)
		return kMouseDownEventHandledButDontNeedMovedOrUpEvents;

	startPoint = where;
	scrollerRect = getScrollerRect ();
	scrolling = where.isInside (scrollerRect);
	if (scrolling)
	{
		scrollerRect = getScrollerRect ();
		return kMouseEventHandled;
	}
	else if (where.isInside (scrollerArea))
	{
		doStepping ();
		timer = new CVSTGUITimer (this, 250);
		timer->start ();
		return kMouseEventHandled;
	}
	return kMouseDownEventHandledButDontNeedMovedOrUpEvents;
}

//-----------------------------------------------------------------------------
CMouseEventResult CScrollbar::onMouseUp (CPoint &where, const CButtonState& buttons)
{
	if (timer)
	{
		timer->forget ();
		timer = 0;
	}
	return kMouseEventHandled;
}

//-----------------------------------------------------------------------------
CMouseEventResult CScrollbar::onMouseMoved (CPoint &where, const CButtonState& buttons)
{
	if (buttons & kLButton)
	{
		if (scrolling)
		{
			float newValue = 0.f;
			CPoint newPoint (where);
			newPoint.x -= startPoint.x - scrollerRect.left;
			newPoint.y -= startPoint.y - scrollerRect.top;
			if (direction == kHorizontal)
			{
				newValue = (float)((float)(newPoint.x - scrollerArea.left) / ((float)scrollerArea.width () - scrollerRect.width ()));
			}
			else
			{
				newValue = (float)((float)(newPoint.y - scrollerArea.top) / ((float)scrollerArea.height () - scrollerRect.height ()));
			}
			if (newValue < 0.f) newValue = 0.f;
			if (newValue > 1.f) newValue = 1.f;
			if (newValue != value)
			{
				value = newValue;
				valueChanged ();
				invalid ();
			}
		}
		else
		{
			CPoint old (startPoint);
			startPoint = where;
			CRect scollerRect = getScrollerRect ();
			if (where.isInside (getViewSize ()) && old.isInside (scollerRect) && !startPoint.isInside (scrollerRect))
				doStepping ();
		}
		return kMouseEventHandled;
	}
	return kMouseEventNotHandled;
}

//------------------------------------------------------------------------
void CScrollbar::onVisualChange ()
{
	if (overlayStyle && getFrame ())
	{
		CPoint mousePos;
		getFrame ()->getCurrentMouseLocation (mousePos);
		frameToLocal (mousePos);
		if (getMouseableArea ().pointInside (mousePos) == false)
		{
			Animation::InterpolationTimingFunction* timingFunction = new Animation::InterpolationTimingFunction (1100);
			timingFunction->addPoint (1000.f/1100.f, 0);
			addAnimation ("AlphaValueAnimation", new Animation::AlphaValueAnimation (0.001f), timingFunction);
			setAlphaValue (1.f);
		}
	}
}

//------------------------------------------------------------------------
bool CScrollbar::onWheel (const CPoint &where, const CMouseWheelAxis &axis, const float &_distance, const CButtonState &buttons)
{
	if (!getMouseEnabled ())
		return false;

	if (buttons != 0 && !(buttons & (kShift|kMouseWheelInverted)))
		return false;

	if (direction == kHorizontal && axis == kMouseWheelAxisY)
		return false;

	if (direction == kVertical && axis == kMouseWheelAxisX)
		return false;

	float distance = _distance;
	if (direction == kHorizontal && axis == kMouseWheelAxisY)
		distance *= -1;
	if (buttons & kMouseWheelInverted)
		distance *= -1;

	if (buttons & kShift)
		value -= 0.1f * distance * wheelInc;
	else
		value -= distance * wheelInc;
	bounceValue ();

	if (isDirty ())
	{
		if (getMouseableArea().pointInside (where) == false)
		{
			onVisualChange ();
		}

		valueChanged ();
		invalid ();
	}
	return true;
}

//-----------------------------------------------------------------------------
void CScrollbar::drawBackground (CDrawContext* pContext)
{
	CRect r (getViewSize ());
	if (drawer)
		drawer->drawScrollbarBackground (pContext, r, direction, this);
	else
	{
		pContext->setDrawMode (kAliasing);
		pContext->setLineWidth (1);
		pContext->setFillColor (backgroundColor);
		pContext->setFrameColor (frameColor);
		pContext->setLineStyle (kLineSolid);
		pContext->drawRect (r, kDrawFilledAndStroked);
	}
}

//-----------------------------------------------------------------------------
void CScrollbar::drawScroller (CDrawContext* pContext, const CRect& size)
{
	CRect r (size);
	if (drawer)
		drawer->drawScrollbarScroller (pContext, r, direction, this);
	else
	{
		pContext->setLineWidth (1);
		pContext->setFillColor (scrollerColor);
		pContext->setFrameColor (frameColor);

		CCoord wideness = (direction == kVertical ? getWidth() : getHeight()) / 2 - 2;
		OwningPointer<CGraphicsPath> path = wideness > 2 ? pContext->createGraphicsPath () : 0;
		if (path)
		{
			if (wideness > 4)
				wideness = 4;
			pContext->setDrawMode (kAntiAliasing);
			path->addRoundRect (r, wideness);
			pContext->drawGraphicsPath (path, CDrawContext::kPathFilled);
			pContext->drawGraphicsPath (path, CDrawContext::kPathStroked);
		}
		else
		{
			pContext->setDrawMode (kAliasing);
			pContext->drawRect (r, kDrawFilledAndStroked);
		}
	}
}

//-----------------------------------------------------------------------------
void CScrollbar::draw (CDrawContext* pContext)
{
	drawBackground (pContext);
	if (scrollerLength > 0)
	{
		CRect scrollerRect = getScrollerRect ();
		drawScroller (pContext, scrollerRect);
	}
	setDirty (false);
}

} // namespace

