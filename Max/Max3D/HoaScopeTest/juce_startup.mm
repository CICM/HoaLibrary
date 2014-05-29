#include "JuceLibraryCode/AppConfig.h"

#define JUCE_MAC_WINDOW_VISIBITY_BODGE 1

#include "../../../Sources/JuceModules/juce_audio_plugin_client/utility/juce_IncludeSystemHeaders.h"
#include "../../../Sources/JuceModules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h"
#include "../../../Sources/JuceModules/juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h"
#include "../../../Sources/JuceModules/juce_audio_plugin_client/utility/juce_CarbonVisibility.h"

using namespace juce;

void initialiseMac();
void initialiseMac()
{
#if ! JUCE_64BIT
    [NSApplication sharedApplication];
    NSApplicationLoad();
#endif
}

void componentCreateWindow (Component* comp);
void componentCreateWindow (Component* comp)
{
    NSView* pluginView = (NSView*) comp->getWindowHandle();
    NSWindow* pluginWindow = [pluginView window];
    [pluginWindow setExcludedFromWindowsMenu: YES];
    [pluginWindow setCanHide: YES];
    [pluginWindow setReleasedWhenClosed: YES];
    [pluginWindow setIgnoresMouseEvents: NO];
}