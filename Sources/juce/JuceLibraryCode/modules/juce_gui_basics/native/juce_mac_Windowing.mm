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

void LookAndFeel::playAlertSound()
{
    NSBeep();
}

//==============================================================================
class OSXMessageBox  : private AsyncUpdater
{
public:
    OSXMessageBox (AlertWindow::AlertIconType type, const String& t, const String& m,
                   const char* b1, const char* b2, const char* b3,
                   ModalComponentManager::Callback* c, const bool runAsync)
        : iconType (type), title (t), message (m), callback (c),
          button1 (b1), button2 (b2), button3 (b3)
    {
        if (runAsync)
            triggerAsyncUpdate();
    }

    int getResult() const
    {
        switch (getRawResult())
        {
            case NSAlertDefaultReturn:  return 1;
            case NSAlertOtherReturn:    return 2;
            default:                    return 0;
        }
    }

    static int show (AlertWindow::AlertIconType iconType, const String& title, const String& message,
                     ModalComponentManager::Callback* callback, const char* b1, const char* b2, const char* b3,
                     bool runAsync)
    {
        ScopedPointer<OSXMessageBox> mb (new OSXMessageBox (iconType, title, message, b1, b2, b3,
                                                            callback, runAsync));
        if (! runAsync)
            return mb->getResult();

        mb.release();
        return 0;
    }

private:
    AlertWindow::AlertIconType iconType;
    String title, message;
    ModalComponentManager::Callback* callback;
    const char* button1;
    const char* button2;
    const char* button3;

    void handleAsyncUpdate()
    {
        const int result = getResult();

        if (callback != nullptr)
            callback->modalStateFinished (result);

        delete this;
    }

    static NSString* translateIfNotNull (const char* s)
    {
        return s != nullptr ? juceStringToNS (TRANS (s)) : nil;
    }

    NSInteger getRawResult() const
    {
        NSString* msg = juceStringToNS (message);
        NSString* ttl = juceStringToNS (title);
        NSString* b1  = translateIfNotNull (button1);
        NSString* b2  = translateIfNotNull (button2);
        NSString* b3  = translateIfNotNull (button3);

        switch (iconType)
        {
            case AlertWindow::InfoIcon:     return NSRunInformationalAlertPanel (ttl, msg, b1, b2, b3);
            case AlertWindow::WarningIcon:  return NSRunCriticalAlertPanel      (ttl, msg, b1, b2, b3);
            default:                        return NSRunAlertPanel              (ttl, msg, b1, b2, b3);
        }
    }
};


void JUCE_CALLTYPE NativeMessageBox::showMessageBox (AlertWindow::AlertIconType iconType,
                                                     const String& title, const String& message,
                                                     Component* /*associatedComponent*/)
{
    OSXMessageBox::show (iconType, title, message, nullptr, "OK", nullptr, nullptr, false);
}

void JUCE_CALLTYPE NativeMessageBox::showMessageBoxAsync (AlertWindow::AlertIconType iconType,
                                                          const String& title, const String& message,
                                                          Component* /*associatedComponent*/,
                                                          ModalComponentManager::Callback* callback)
{
    OSXMessageBox::show (iconType, title, message, callback, "OK", nullptr, nullptr, true);
}

bool JUCE_CALLTYPE NativeMessageBox::showOkCancelBox (AlertWindow::AlertIconType iconType,
                                                      const String& title, const String& message,
                                                      Component* /*associatedComponent*/,
                                                      ModalComponentManager::Callback* callback)
{
    return OSXMessageBox::show (iconType, title, message, callback,
                                "OK", "Cancel", nullptr, callback != nullptr) == 1;
}

int JUCE_CALLTYPE NativeMessageBox::showYesNoCancelBox (AlertWindow::AlertIconType iconType,
                                                        const String& title, const String& message,
                                                        Component* /*associatedComponent*/,
                                                        ModalComponentManager::Callback* callback)
{
    return OSXMessageBox::show (iconType, title, message, callback,
                                "Yes", "Cancel", "No", callback != nullptr);
}


//==============================================================================
bool DragAndDropContainer::performExternalDragDropOfFiles (const StringArray& files, const bool /*canMoveFiles*/)
{
    if (files.size() == 0)
        return false;

    MouseInputSource* draggingSource = Desktop::getInstance().getDraggingMouseSource(0);

    if (draggingSource == nullptr)
    {
        jassertfalse;  // This method must be called in response to a component's mouseDown or mouseDrag event!
        return false;
    }

    Component* sourceComp = draggingSource->getComponentUnderMouse();

    if (sourceComp == nullptr)
    {
        jassertfalse;  // This method must be called in response to a component's mouseDown or mouseDrag event!
        return false;
    }

    JUCE_AUTORELEASEPOOL

    NSView* view = (NSView*) sourceComp->getWindowHandle();

    if (view == nil)
        return false;

    NSPasteboard* pboard = [NSPasteboard pasteboardWithName: NSDragPboard];
    [pboard declareTypes: [NSArray arrayWithObject: NSFilenamesPboardType]
                   owner: nil];

    NSMutableArray* filesArray = [NSMutableArray arrayWithCapacity: 4];
    for (int i = 0; i < files.size(); ++i)
        [filesArray addObject: juceStringToNS (files[i])];

    [pboard setPropertyList: filesArray
                    forType: NSFilenamesPboardType];

    NSPoint dragPosition = [view convertPoint: [[[view window] currentEvent] locationInWindow]
                                     fromView: nil];
    dragPosition.x -= 16;
    dragPosition.y -= 16;

    [view dragImage: [[NSWorkspace sharedWorkspace] iconForFile: juceStringToNS (files[0])]
                 at: dragPosition
             offset: NSMakeSize (0, 0)
              event: [[view window] currentEvent]
         pasteboard: pboard
             source: view
          slideBack: YES];

    return true;
}

bool DragAndDropContainer::performExternalDragDropOfText (const String& /*text*/)
{
    jassertfalse;    // not implemented!
    return false;
}

//==============================================================================
bool Desktop::canUseSemiTransparentWindows() noexcept
{
    return true;
}

Point<int> MouseInputSource::getCurrentMousePosition()
{
    JUCE_AUTORELEASEPOOL
    const NSPoint p ([NSEvent mouseLocation]);
    return Point<int> (roundToInt (p.x), roundToInt ([[[NSScreen screens] objectAtIndex: 0] frame].size.height - p.y));
}

void Desktop::setMousePosition (const Point<int>& newPosition)
{
    // this rubbish needs to be done around the warp call, to avoid causing a
    // bizarre glitch..
    CGAssociateMouseAndMouseCursorPosition (false);
    CGWarpMouseCursorPosition (convertToCGPoint (newPosition));
    CGAssociateMouseAndMouseCursorPosition (true);
}

Desktop::DisplayOrientation Desktop::getCurrentOrientation() const
{
    return upright;
}

//==============================================================================
#if defined (MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7)
 #define JUCE_USE_IOPM_SCREENSAVER_DEFEAT 1
#endif

#if ! (defined (JUCE_USE_IOPM_SCREENSAVER_DEFEAT) || defined (__POWER__))
 extern "C"  { extern OSErr UpdateSystemActivity (UInt8); } // Some versions of the SDK omit this function..
#endif

class ScreenSaverDefeater   : public Timer
{
public:
   #if JUCE_USE_IOPM_SCREENSAVER_DEFEAT
    ScreenSaverDefeater()
    {
        startTimer (5000);
        timerCallback();
    }

    void timerCallback()
    {
        if (Process::isForegroundProcess())
        {
            if (assertion == nullptr)
                assertion = new PMAssertion();
        }
        else
        {
            assertion = nullptr;
        }
    }

    struct PMAssertion
    {
        PMAssertion()  : assertionID (kIOPMNullAssertionID)
        {
            IOReturn res = IOPMAssertionCreateWithName (kIOPMAssertionTypePreventUserIdleDisplaySleep,
                                                        kIOPMAssertionLevelOn,
                                                        CFSTR ("JUCE Playback"),
                                                        &assertionID);
            jassert (res == kIOReturnSuccess); (void) res;
        }

        ~PMAssertion()
        {
            if (assertionID != kIOPMNullAssertionID)
                IOPMAssertionRelease (assertionID);
        }

        IOPMAssertionID assertionID;
    };

    ScopedPointer<PMAssertion> assertion;
   #else
    ScreenSaverDefeater()
    {
        startTimer (10000);
        timerCallback();
    }

    void timerCallback()
    {
        if (Process::isForegroundProcess())
            UpdateSystemActivity (1 /*UsrActivity*/);
    }
   #endif
};

static ScopedPointer<ScreenSaverDefeater> screenSaverDefeater;

void Desktop::setScreenSaverEnabled (const bool isEnabled)
{
    if (isEnabled)
        screenSaverDefeater = nullptr;
    else if (screenSaverDefeater == nullptr)
        screenSaverDefeater = new ScreenSaverDefeater();
}

bool Desktop::isScreenSaverEnabled()
{
    return screenSaverDefeater == nullptr;
}

//==============================================================================
class DisplaySettingsChangeCallback  : private DeletedAtShutdown
{
public:
    DisplaySettingsChangeCallback()
    {
        CGDisplayRegisterReconfigurationCallback (displayReconfigurationCallBack, 0);
    }

    ~DisplaySettingsChangeCallback()
    {
        CGDisplayRemoveReconfigurationCallback (displayReconfigurationCallBack, 0);
        clearSingletonInstance();
    }

    static void displayReconfigurationCallBack (CGDirectDisplayID, CGDisplayChangeSummaryFlags, void*)
    {
        const_cast <Desktop::Displays&> (Desktop::getInstance().getDisplays()).refresh();
    }

    juce_DeclareSingleton_SingleThreaded_Minimal (DisplaySettingsChangeCallback);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplaySettingsChangeCallback)
};

juce_ImplementSingleton_SingleThreaded (DisplaySettingsChangeCallback);

static Rectangle<int> convertDisplayRect (NSRect r, CGFloat mainScreenBottom)
{
    r.origin.y = mainScreenBottom - (r.origin.y + r.size.height);
    return convertToRectInt (r);
}

void Desktop::Displays::findDisplays()
{
    JUCE_AUTORELEASEPOOL

    DisplaySettingsChangeCallback::getInstance();

    NSArray* screens = [NSScreen screens];
    const CGFloat mainScreenBottom = [[screens objectAtIndex: 0] frame].size.height;

    for (unsigned int i = 0; i < [screens count]; ++i)
    {
        NSScreen* s = (NSScreen*) [screens objectAtIndex: i];

        Display d;
        d.userArea  = convertDisplayRect ([s visibleFrame], mainScreenBottom);
        d.totalArea = convertDisplayRect ([s frame], mainScreenBottom);
        d.isMain = (i == 0);

       #if defined (MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7)
        if ([s respondsToSelector: @selector (backingScaleFactor)])
            d.scale = s.backingScaleFactor;
        else
       #endif
            d.scale = 1.0;

        displays.add (d);
    }
}

//==============================================================================
bool juce_areThereAnyAlwaysOnTopWindows()
{
    NSArray* windows = [NSApp windows];

    for (unsigned int i = 0; i < [windows count]; ++i)
    {
        const NSInteger level = [((NSWindow*) [windows objectAtIndex: i]) level];

        if (level == NSFloatingWindowLevel
             || level == NSStatusWindowLevel
             || level == NSModalPanelWindowLevel)
            return true;
    }

    return false;
}

//==============================================================================
Image juce_createIconForFile (const File& file)
{
    JUCE_AUTORELEASEPOOL

    NSImage* image = [[NSWorkspace sharedWorkspace] iconForFile: juceStringToNS (file.getFullPathName())];

    Image result (Image::ARGB, (int) [image size].width, (int) [image size].height, true);

    [NSGraphicsContext saveGraphicsState];
    [NSGraphicsContext setCurrentContext: [NSGraphicsContext graphicsContextWithGraphicsPort: juce_getImageContext (result) flipped: false]];

    [image drawAtPoint: NSMakePoint (0, 0)
              fromRect: NSMakeRect (0, 0, [image size].width, [image size].height)
             operation: NSCompositeSourceOver fraction: 1.0f];

    [[NSGraphicsContext currentContext] flushGraphics];
    [NSGraphicsContext restoreGraphicsState];

    return result;
}

//==============================================================================
void SystemClipboard::copyTextToClipboard (const String& text)
{
    NSPasteboard* pb = [NSPasteboard generalPasteboard];

    [pb declareTypes: [NSArray arrayWithObject: NSStringPboardType]
               owner: nil];

    [pb setString: juceStringToNS (text)
          forType: NSStringPboardType];
}

String SystemClipboard::getTextFromClipboard()
{
    NSString* text = [[NSPasteboard generalPasteboard] stringForType: NSStringPboardType];

    return text == nil ? String::empty
                       : nsStringToJuce (text);
}

void Process::setDockIconVisible (bool isVisible)
{
   #if defined (MAC_OS_X_VERSION_10_6) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_6)
    [NSApp setActivationPolicy: isVisible ? NSApplicationActivationPolicyRegular
                                          : NSApplicationActivationPolicyProhibited];
   #else
    (void) isVisible;
    jassertfalse; // sorry, not available in 10.5!
   #endif
}
