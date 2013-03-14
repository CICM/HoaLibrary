/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_MAC_CARBONVIEWWRAPPERCOMPONENT_JUCEHEADER__
#define __JUCE_MAC_CARBONVIEWWRAPPERCOMPONENT_JUCEHEADER__


//==============================================================================
/**
    Creates a floating carbon window that can be used to hold a carbon UI.

    This is a handy class that's designed to be inlined where needed, e.g.
    in the audio plugin hosting code.
*/
class CarbonViewWrapperComponent  : public Component,
                                    public ComponentMovementWatcher,
                                    public Timer
{
public:
    CarbonViewWrapperComponent()
        : ComponentMovementWatcher (this),
          wrapperWindow (0),
          carbonWindow (0),
          embeddedView (0),
          recursiveResize (false)
    {
    }

    virtual ~CarbonViewWrapperComponent()
    {
        jassert (embeddedView == 0); // must call deleteWindow() in the subclass's destructor!
    }

    virtual HIViewRef attachView (WindowRef windowRef, HIViewRef rootView) = 0;
    virtual void removeView (HIViewRef embeddedView) = 0;
    virtual void handleMouseDown (int, int) {}
    virtual void handlePaint() {}

    virtual bool getEmbeddedViewSize (int& w, int& h)
    {
        if (embeddedView == 0)
            return false;

        HIRect bounds;
        HIViewGetBounds (embeddedView, &bounds);
        w = jmax (1, roundToInt (bounds.size.width));
        h = jmax (1, roundToInt (bounds.size.height));
        return true;
    }

    void createWindow()
    {
        if (wrapperWindow == 0)
        {
            Rect r;
            r.left   = (short) getScreenX();
            r.top    = (short) getScreenY();
            r.right  = (short) (r.left + getWidth());
            r.bottom = (short) (r.top + getHeight());

            CreateNewWindow (kDocumentWindowClass,
                             (WindowAttributes) (kWindowStandardHandlerAttribute | kWindowCompositingAttribute
                                                  | kWindowNoShadowAttribute | kWindowNoTitleBarAttribute),
                             &r, &wrapperWindow);

            jassert (wrapperWindow != 0);
            if (wrapperWindow == 0)
                return;

            carbonWindow = [[NSWindow alloc] initWithWindowRef: wrapperWindow];

            [getOwnerWindow() addChildWindow: carbonWindow
                                     ordered: NSWindowAbove];

            embeddedView = attachView (wrapperWindow, HIViewGetRoot (wrapperWindow));

            // Check for the plugin creating its own floating window, and if there is one,
            // we need to reparent it to make it visible..
            NSWindow* floatingChildWindow = [[carbonWindow childWindows] objectAtIndex: 0];

            if (floatingChildWindow != nil)
                [getOwnerWindow() addChildWindow: floatingChildWindow
                                         ordered: NSWindowAbove];

            EventTypeSpec windowEventTypes[] =
            {
                { kEventClassWindow, kEventWindowGetClickActivation },
                { kEventClassWindow, kEventWindowHandleDeactivate },
                { kEventClassWindow, kEventWindowBoundsChanging },
                { kEventClassMouse,  kEventMouseDown },
                { kEventClassMouse,  kEventMouseMoved },
                { kEventClassMouse,  kEventMouseDragged },
                { kEventClassMouse,  kEventMouseUp},
                { kEventClassWindow, kEventWindowDrawContent },
                { kEventClassWindow, kEventWindowShown },
                { kEventClassWindow, kEventWindowHidden }
            };

            EventHandlerUPP upp = NewEventHandlerUPP (carbonEventCallback);
            InstallWindowEventHandler (wrapperWindow, upp,
                                       sizeof (windowEventTypes) / sizeof (EventTypeSpec),
                                       windowEventTypes, this, &eventHandlerRef);

            setOurSizeToEmbeddedViewSize();
            setEmbeddedWindowToOurSize();

            creationTime = Time::getCurrentTime();
        }
    }

    void deleteWindow()
    {
        removeView (embeddedView);
        embeddedView = 0;

        if (wrapperWindow != 0)
        {
            NSWindow* ownerWindow = getOwnerWindow();

            if ([[ownerWindow childWindows] count] > 0)
            {
                [ownerWindow removeChildWindow: carbonWindow];
                [carbonWindow close];
            }

            RemoveEventHandler (eventHandlerRef);
            DisposeWindow (wrapperWindow);
            wrapperWindow = 0;
        }
    }

    //==============================================================================
    void setOurSizeToEmbeddedViewSize()
    {
        int w, h;
        if (getEmbeddedViewSize (w, h))
        {
            if (w != getWidth() || h != getHeight())
            {
                startTimer (50);
                setSize (w, h);

                if (Component* p = getParentComponent())
                    p->setSize (w, h);
            }
            else
            {
                startTimer (jlimit (50, 500, getTimerInterval() + 20));
            }
        }
        else
        {
            stopTimer();
        }
    }

    void setEmbeddedWindowToOurSize()
    {
        if (! recursiveResize)
        {
            recursiveResize = true;

            if (embeddedView != 0)
            {
                HIRect r;
                r.origin.x = 0;
                r.origin.y = 0;
                r.size.width  = (float) getWidth();
                r.size.height = (float) getHeight();
                HIViewSetFrame (embeddedView, &r);
            }

            if (wrapperWindow != 0)
            {
                Rect wr;
                wr.left   = (short) getScreenX();
                wr.top    = (short) getScreenY();
                wr.right  = (short) (wr.left + getWidth());
                wr.bottom = (short) (wr.top + getHeight());

                SetWindowBounds (wrapperWindow, kWindowContentRgn, &wr);
                ShowWindow (wrapperWindow);
            }

            recursiveResize = false;
        }
    }

    void componentMovedOrResized (bool /*wasMoved*/, bool /*wasResized*/)
    {
        setEmbeddedWindowToOurSize();
    }

    void componentPeerChanged()
    {
        deleteWindow();
        createWindow();
    }

    void componentVisibilityChanged()
    {
        if (isShowing())
            createWindow();
        else
            deleteWindow();

        setEmbeddedWindowToOurSize();
    }

    static void recursiveHIViewRepaint (HIViewRef view)
    {
        HIViewSetNeedsDisplay (view, true);
        HIViewRef child = HIViewGetFirstSubview (view);

        while (child != 0)
        {
            recursiveHIViewRepaint (child);
            child = HIViewGetNextView (child);
        }
    }

    void timerCallback()
    {
        setOurSizeToEmbeddedViewSize();

        // To avoid strange overpainting problems when the UI is first opened, we'll
        // repaint it a few times during the first second that it's on-screen..
        if ((Time::getCurrentTime() - creationTime).inMilliseconds() < 1000)
            recursiveHIViewRepaint (HIViewGetRoot (wrapperWindow));
    }

    OSStatus carbonEventHandler (EventHandlerCallRef /*nextHandlerRef*/, EventRef event)
    {
        switch (GetEventKind (event))
        {
            case kEventWindowHandleDeactivate:
                ActivateWindow (wrapperWindow, TRUE);
                return noErr;

            case kEventWindowGetClickActivation:
            {
                getTopLevelComponent()->toFront (false);
                [carbonWindow makeKeyAndOrderFront: nil];

                ClickActivationResult howToHandleClick = kActivateAndHandleClick;

                SetEventParameter (event, kEventParamClickActivation, typeClickActivationResult,
                                   sizeof (ClickActivationResult), &howToHandleClick);

                HIViewSetNeedsDisplay (embeddedView, true);
                return noErr;
            }
        }

        return eventNotHandledErr;
    }

    static pascal OSStatus carbonEventCallback (EventHandlerCallRef nextHandlerRef, EventRef event, void* userData)
    {
        return ((CarbonViewWrapperComponent*) userData)->carbonEventHandler (nextHandlerRef, event);
    }

protected:
    WindowRef wrapperWindow;
    NSWindow* carbonWindow;
    HIViewRef embeddedView;
    bool recursiveResize;
    Time creationTime;

    EventHandlerRef eventHandlerRef;

    NSWindow* getOwnerWindow() const    { return [((NSView*) getWindowHandle()) window]; }
};

#endif   // __JUCE_MAC_CARBONVIEWWRAPPERCOMPONENT_JUCEHEADER__
