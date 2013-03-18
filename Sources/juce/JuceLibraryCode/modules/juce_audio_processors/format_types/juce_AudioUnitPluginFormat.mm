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

#if JUCE_PLUGINHOST_AU && JUCE_MAC

} // (juce namespace)

#include <AudioUnit/AudioUnit.h>
#include <AudioUnit/AUCocoaUIView.h>
#include <CoreAudioKit/AUGenericView.h>
#include <AudioToolbox/AudioUnitUtilities.h>
#include <CoreMIDI/MIDIServices.h>

#if JUCE_SUPPORT_CARBON
 #include <AudioUnit/AudioUnitCarbonView.h>
#endif

namespace juce
{

#include "../../juce_audio_devices/native/juce_MidiDataConcatenator.h"

#if JUCE_SUPPORT_CARBON
 #include "../../juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h"
#endif

// Change this to disable logging of various activities
#ifndef AU_LOGGING
 #define AU_LOGGING 1
#endif

#if AU_LOGGING
 #define log(a) Logger::writeToLog(a);
#else
 #define log(a)
#endif

namespace AudioUnitFormatHelpers
{
    static int insideCallback = 0;

    String osTypeToString (OSType type)
    {
        const juce_wchar s[4] = { (juce_wchar) ((type >> 24) & 0xff),
                                  (juce_wchar) ((type >> 16) & 0xff),
                                  (juce_wchar) ((type >> 8) & 0xff),
                                  (juce_wchar) (type & 0xff) };
        return String (s, 4);
    }

    OSType stringToOSType (String s)
    {
        if (s.trim().length() >= 4) // (to avoid trimming leading spaces)
            s = s.trim();

        s += "    ";

        return (((OSType) (unsigned char) s[0]) << 24)
             | (((OSType) (unsigned char) s[1]) << 16)
             | (((OSType) (unsigned char) s[2]) << 8)
             |  ((OSType) (unsigned char) s[3]);
    }

    static const char* auIdentifierPrefix = "AudioUnit:";

    String createAUPluginIdentifier (const ComponentDescription& desc)
    {
        jassert (osTypeToString ('abcd') == "abcd"); // agh, must have got the endianness wrong..
        jassert (stringToOSType ("abcd") == (OSType) 'abcd'); // ditto

        String s (auIdentifierPrefix);

        if (desc.componentType == kAudioUnitType_MusicDevice)
            s << "Synths/";
        else if (desc.componentType == kAudioUnitType_MusicEffect
                  || desc.componentType == kAudioUnitType_Effect)
            s << "Effects/";
        else if (desc.componentType == kAudioUnitType_Generator)
            s << "Generators/";
        else if (desc.componentType == kAudioUnitType_Panner)
            s << "Panners/";

        s << osTypeToString (desc.componentType) << ","
          << osTypeToString (desc.componentSubType) << ","
          << osTypeToString (desc.componentManufacturer);

        return s;
    }

    void getAUDetails (ComponentRecord* comp, String& name, String& manufacturer)
    {
        Handle componentNameHandle = NewHandle (sizeof (void*));
        Handle componentInfoHandle = NewHandle (sizeof (void*));

        if (componentNameHandle != 0 && componentInfoHandle != 0)
        {
            ComponentDescription desc;

            if (GetComponentInfo (comp, &desc, componentNameHandle, componentInfoHandle, 0) == noErr)
            {
                ConstStr255Param nameString = (ConstStr255Param) (*componentNameHandle);
                ConstStr255Param infoString = (ConstStr255Param) (*componentInfoHandle);

                if (nameString != 0 && nameString[0] != 0)
                {
                    const String all ((const char*) nameString + 1, nameString[0]);
                    DBG ("name: " + all);

                    manufacturer = all.upToFirstOccurrenceOf (":", false, false).trim();
                    name = all.fromFirstOccurrenceOf (":", false, false).trim();
                }

                if (infoString != 0 && infoString[0] != 0)
                {
                    DBG ("info: " + String ((const char*) infoString + 1, infoString[0]));
                }

                if (name.isEmpty())
                    name = "<Unknown>";
            }

            DisposeHandle (componentNameHandle);
            DisposeHandle (componentInfoHandle);
        }
    }

    bool getComponentDescFromIdentifier (const String& fileOrIdentifier, ComponentDescription& desc,
                                         String& name, String& version, String& manufacturer)
    {
        zerostruct (desc);

        if (fileOrIdentifier.startsWithIgnoreCase (auIdentifierPrefix))
        {
            String s (fileOrIdentifier.substring (jmax (fileOrIdentifier.lastIndexOfChar (':'),
                                                        fileOrIdentifier.lastIndexOfChar ('/')) + 1));

            StringArray tokens;
            tokens.addTokens (s, ",", String::empty);
            tokens.removeEmptyStrings();

            if (tokens.size() == 3)
            {
                desc.componentType         = stringToOSType (tokens[0]);
                desc.componentSubType      = stringToOSType (tokens[1]);
                desc.componentManufacturer = stringToOSType (tokens[2]);

                if (ComponentRecord* comp = FindNextComponent (0, &desc))
                {
                    getAUDetails (comp, name, manufacturer);
                    return true;
                }
            }
        }

        return false;
    }

    bool getComponentDescFromFile (const String& fileOrIdentifier, ComponentDescription& desc,
                                   String& name, String& version, String& manufacturer)
    {
        zerostruct (desc);

        if (getComponentDescFromIdentifier (fileOrIdentifier, desc, name, version, manufacturer))
            return true;

        const File file (fileOrIdentifier);
        if (! file.hasFileExtension (".component"))
            return false;

        const char* const utf8 = fileOrIdentifier.toUTF8();

        if (CFURLRef url = CFURLCreateFromFileSystemRepresentation (0, (const UInt8*) utf8,
                                                                    strlen (utf8), file.isDirectory()))
        {
            CFBundleRef bundleRef = CFBundleCreate (kCFAllocatorDefault, url);
            CFRelease (url);

            if (bundleRef != 0)
            {
                CFTypeRef bundleName = CFBundleGetValueForInfoDictionaryKey (bundleRef, CFSTR("CFBundleName"));

                if (bundleName != 0 && CFGetTypeID (bundleName) == CFStringGetTypeID())
                    name = String::fromCFString ((CFStringRef) bundleName);

                if (name.isEmpty())
                    name = file.getFileNameWithoutExtension();

                CFTypeRef versionString = CFBundleGetValueForInfoDictionaryKey (bundleRef, CFSTR("CFBundleVersion"));

                if (versionString != 0 && CFGetTypeID (versionString) == CFStringGetTypeID())
                    version = String::fromCFString ((CFStringRef) versionString);

                CFTypeRef manuString = CFBundleGetValueForInfoDictionaryKey (bundleRef, CFSTR("CFBundleGetInfoString"));

                if (manuString != 0 && CFGetTypeID (manuString) == CFStringGetTypeID())
                    manufacturer = String::fromCFString ((CFStringRef) manuString);

                const short resFileId = CFBundleOpenBundleResourceMap (bundleRef);
                UseResFile (resFileId);

                for (ResourceIndex i = 1; i <= Count1Resources ('thng'); ++i)
                {
                    if (Handle h = Get1IndResource ('thng', i))
                    {
                        HLock (h);
                        const uint32* const types = (const uint32*) *h;

                        if (types[0] == kAudioUnitType_MusicDevice
                             || types[0] == kAudioUnitType_MusicEffect
                             || types[0] == kAudioUnitType_Effect
                             || types[0] == kAudioUnitType_Generator
                             || types[0] == kAudioUnitType_Panner)
                        {
                            desc.componentType = types[0];
                            desc.componentSubType = types[1];
                            desc.componentManufacturer = types[2];
                            break;
                        }

                        HUnlock (h);
                        ReleaseResource (h);
                    }
                }

                CFBundleCloseBundleResourceMap (bundleRef, resFileId);
                CFRelease (bundleRef);
            }
        }

        return desc.componentType != 0 && desc.componentSubType != 0;
    }

    const char* getCategory (OSType type) noexcept
    {
        switch (type)
        {
            case kAudioUnitType_Effect:
            case kAudioUnitType_MusicEffect:    return "Effect";
            case kAudioUnitType_MusicDevice:    return "Synth";
            case kAudioUnitType_Generator:      return "Generator";
            case kAudioUnitType_Panner:         return "Panner";
            default: break;
        }

        return nullptr;
    }
}

//==============================================================================
class AudioUnitPluginWindowCarbon;
class AudioUnitPluginWindowCocoa;

//==============================================================================
class AudioUnitPluginInstance     : public AudioPluginInstance
{
public:
    AudioUnitPluginInstance (const String& fileOrId)
        : fileOrIdentifier (fileOrId),
          wantsMidiMessages (false),
          producesMidiMessages (false),
          wasPlaying (false),
          prepared (false),
          currentBuffer (nullptr),
          numInputBusChannels (0),
          numOutputBusChannels (0),
          numInputBusses (0),
          numOutputBusses (0),
          audioUnit (0),
          parameterListenerRef (0),
          midiConcatenator (2048)
    {
        using namespace AudioUnitFormatHelpers;

        try
        {
            ++insideCallback;

            log ("Opening AU: " + fileOrIdentifier);

            if (getComponentDescFromFile (fileOrIdentifier, componentDesc, pluginName, version, manufacturer))
            {
                if (ComponentRecord* const comp = FindNextComponent (0, &componentDesc))
                {
                    audioUnit = (AudioUnit) OpenComponent (comp);

                    wantsMidiMessages = componentDesc.componentType == kAudioUnitType_MusicDevice
                                     || componentDesc.componentType == kAudioUnitType_MusicEffect;
                }
            }

            --insideCallback;
        }
        catch (...)
        {
            --insideCallback;
        }
    }

    ~AudioUnitPluginInstance()
    {
        const ScopedLock sl (lock);

        jassert (AudioUnitFormatHelpers::insideCallback == 0);

        if (parameterListenerRef != 0)
        {
            AUListenerDispose (parameterListenerRef);
            parameterListenerRef = 0;
        }

        if (audioUnit != 0)
        {
            if (prepared)
                releaseResources();

            CloseComponent (audioUnit);
            audioUnit = 0;
        }
    }

    void initialise()
    {
        refreshParameterList();
        updateNumChannels();
        producesMidiMessages = canProduceMidiOutput();
        setPluginCallbacks();
        setPlayConfigDetails (numInputBusChannels * numInputBusses,
                              numOutputBusChannels * numOutputBusses, 0, 0);
        setLatencySamples (0);
    }

    //==============================================================================
    // AudioPluginInstance methods:

    void fillInPluginDescription (PluginDescription& desc) const
    {
        desc.name = pluginName;
        desc.descriptiveName = pluginName;
        desc.fileOrIdentifier = AudioUnitFormatHelpers::createAUPluginIdentifier (componentDesc);
        desc.uid = ((int) componentDesc.componentType)
                    ^ ((int) componentDesc.componentSubType)
                    ^ ((int) componentDesc.componentManufacturer);
        desc.lastFileModTime = Time();
        desc.pluginFormatName = "AudioUnit";
        desc.category = AudioUnitFormatHelpers::getCategory (componentDesc.componentType);
        desc.manufacturerName = manufacturer;
        desc.version = version;
        desc.numInputChannels = getNumInputChannels();
        desc.numOutputChannels = getNumOutputChannels();
        desc.isInstrument = (componentDesc.componentType == kAudioUnitType_MusicDevice);
    }

    void* getPlatformSpecificData()             { return audioUnit; }
    const String getName() const                { return pluginName; }

    bool silenceInProducesSilenceOut() const
    {
        return getTailLengthSeconds() <= 0;
    }

    double getTailLengthSeconds() const
    {
        Float64 tail = 0;
        UInt32 tailSize = sizeof (tail);

        if (audioUnit != 0)
            AudioUnitGetProperty (audioUnit, kAudioUnitProperty_TailTime, kAudioUnitScope_Global,
                                  0, &tail, &tailSize);

        return tail;
    }

    bool acceptsMidi() const                    { return wantsMidiMessages; }
    bool producesMidi() const                   { return producesMidiMessages; }

    //==============================================================================
    // AudioProcessor methods:

    void prepareToPlay (double sampleRate_, int estimatedSamplesPerBlock)
    {
        if (audioUnit != 0)
        {
            releaseResources();
            updateNumChannels();

            Float64 sampleRateIn = 0, sampleRateOut = 0;
            UInt32 sampleRateSize = sizeof (sampleRateIn);
            const Float64 sr = sampleRate_;

            for (int i = 0; i < numInputBusses; ++i)
            {
                AudioUnitGetProperty (audioUnit, kAudioUnitProperty_SampleRate, kAudioUnitScope_Input, i, &sampleRateIn, &sampleRateSize);

                if (sampleRateIn != sr)
                    AudioUnitSetProperty (audioUnit, kAudioUnitProperty_SampleRate, kAudioUnitScope_Input, i, &sr, sizeof (sr));
            }

            for (int i = 0; i < numOutputBusses; ++i)
            {
                AudioUnitGetProperty (audioUnit, kAudioUnitProperty_SampleRate, kAudioUnitScope_Output, i, &sampleRateOut, &sampleRateSize);

                if (sampleRateOut != sr)
                    AudioUnitSetProperty (audioUnit, kAudioUnitProperty_SampleRate, kAudioUnitScope_Output, i, &sr, sizeof (sr));
            }

            UInt32 frameSize = (UInt32) estimatedSamplesPerBlock;
            AudioUnitSetProperty (audioUnit, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0,
                                  &frameSize, sizeof (frameSize));

            setPlayConfigDetails (numInputBusChannels * numInputBusses,
                                  numOutputBusChannels * numOutputBusses,
                                  sampleRate_, estimatedSamplesPerBlock);

            Float64 latencySecs = 0.0;
            UInt32 latencySize = sizeof (latencySecs);
            AudioUnitGetProperty (audioUnit, kAudioUnitProperty_Latency, kAudioUnitScope_Global,
                                  0, &latencySecs, &latencySize);

            setLatencySamples (roundToInt (latencySecs * sampleRate_));

            for (int i = 0; i < numInputBusses; ++i)   AudioUnitReset (audioUnit, kAudioUnitScope_Input, i);
            for (int i = 0; i < numOutputBusses; ++i)  AudioUnitReset (audioUnit, kAudioUnitScope_Output, i);

            AudioUnitReset (audioUnit, kAudioUnitScope_Global, 0);

            {
                AudioStreamBasicDescription stream;
                zerostruct (stream); // (can't use "= { 0 }" on this object because it's typedef'ed as a C struct)
                stream.mSampleRate       = sampleRate_;
                stream.mFormatID         = kAudioFormatLinearPCM;
                stream.mFormatFlags      = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved | kAudioFormatFlagsNativeEndian;
                stream.mFramesPerPacket  = 1;
                stream.mBytesPerPacket   = 4;
                stream.mBytesPerFrame    = 4;
                stream.mBitsPerChannel   = 32;
                stream.mChannelsPerFrame = numInputBusChannels;

                for (int i = 0; i < numInputBusses; ++i)
                    AudioUnitSetProperty (audioUnit, kAudioUnitProperty_StreamFormat,
                                          kAudioUnitScope_Input, i, &stream, sizeof (stream));

                stream.mChannelsPerFrame = numOutputBusChannels;

                for (int i = 0; i < numOutputBusses; ++i)
                    AudioUnitSetProperty (audioUnit, kAudioUnitProperty_StreamFormat,
                                          kAudioUnitScope_Output, i, &stream, sizeof (stream));
            }

            if (numOutputBusses != 0 && numOutputBusChannels != 0)
                outputBufferList.calloc (numOutputBusses, getAudioBufferSizeInBytes());

            zerostruct (timeStamp);
            timeStamp.mSampleTime = 0;
            timeStamp.mHostTime = AudioGetCurrentHostTime();
            timeStamp.mFlags = kAudioTimeStampSampleTimeValid | kAudioTimeStampHostTimeValid;

            currentBuffer = nullptr;
            wasPlaying = false;

            prepared = (AudioUnitInitialize (audioUnit) == noErr);
            jassert (prepared);
        }
    }

    void releaseResources()
    {
        if (prepared)
        {
            AudioUnitUninitialize (audioUnit);

            for (int i = 0; i < numInputBusses; ++i)   AudioUnitReset (audioUnit, kAudioUnitScope_Input, i);
            for (int i = 0; i < numOutputBusses; ++i)  AudioUnitReset (audioUnit, kAudioUnitScope_Output, i);

            AudioUnitReset (audioUnit, kAudioUnitScope_Global, 0);

            outputBufferList.free();
            currentBuffer = nullptr;
            prepared = false;
        }

        incomingMidi.clear();
    }

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
    {
        const int numSamples = buffer.getNumSamples();

        if (prepared)
        {
            timeStamp.mHostTime = AudioGetCurrentHostTime();

            for (int i = 0; i < numOutputBusses; ++i)
            {
                AudioBufferList* const abl = getAudioBufferListForBus(i);
                abl->mNumberBuffers = numOutputBusChannels;

                for (int j = 0; j < numOutputBusChannels; ++j)
                {
                    abl->mBuffers[j].mNumberChannels = 1;
                    abl->mBuffers[j].mDataByteSize = sizeof (float) * numSamples;
                    abl->mBuffers[j].mData = buffer.getSampleData (i * numOutputBusChannels + j, 0);
                }
            }

            currentBuffer = &buffer;

            if (wantsMidiMessages)
            {
                const uint8* midiEventData;
                int midiEventSize, midiEventPosition;
                MidiBuffer::Iterator i (midiMessages);

                while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
                {
                    if (midiEventSize <= 3)
                        MusicDeviceMIDIEvent (audioUnit,
                                              midiEventData[0], midiEventData[1], midiEventData[2],
                                              midiEventPosition);
                    else
                        MusicDeviceSysEx (audioUnit, midiEventData, midiEventSize);
                }

                midiMessages.clear();
            }

            AudioUnitRenderActionFlags flags = 0;

            for (int i = 0; i < numOutputBusses; ++i)
                AudioUnitRender (audioUnit, &flags, &timeStamp, i, numSamples, getAudioBufferListForBus (i));

            timeStamp.mSampleTime += numSamples;
        }
        else
        {
            // Plugin not working correctly, so just bypass..
            for (int i = 0; i < getNumOutputChannels(); ++i)
                buffer.clear (i, 0, buffer.getNumSamples());
        }

        if (producesMidiMessages)
        {
            const ScopedLock sl (midiInLock);
            midiMessages.swapWith (incomingMidi);
            incomingMidi.clear();
        }
    }

    //==============================================================================
    bool hasEditor() const                  { return true; }
    AudioProcessorEditor* createEditor();

    //==============================================================================
    const String getInputChannelName (int index) const
    {
        if (isPositiveAndBelow (index, getNumInputChannels()))
            return "Input " + String (index + 1);

        return String::empty;
    }

    const String getOutputChannelName (int index) const
    {
        if (isPositiveAndBelow (index, getNumOutputChannels()))
            return "Output " + String (index + 1);

        return String::empty;
    }

    bool isInputChannelStereoPair (int index) const    { return isPositiveAndBelow (index, getNumInputChannels()); }
    bool isOutputChannelStereoPair (int index) const   { return isPositiveAndBelow (index, getNumOutputChannels()); }

    //==============================================================================
    int getNumParameters()              { return parameters.size(); }

    float getParameter (int index)
    {
        const ScopedLock sl (lock);

        AudioUnitParameterValue value = 0;

        if (audioUnit != 0)
        {
            if (const ParamInfo* p = parameters[index])
            {
                AudioUnitGetParameter (audioUnit,
                                       p->paramID,
                                       kAudioUnitScope_Global, 0,
                                       &value);

                value = (value - p->minValue) / (p->maxValue - p->minValue);
            }
        }

        return value;
    }

    void setParameter (int index, float newValue)
    {
        const ScopedLock sl (lock);

        if (audioUnit != 0)
        {
            if (const ParamInfo* p = parameters[index])
            {
                AudioUnitSetParameter (audioUnit, p->paramID, kAudioUnitScope_Global, 0,
                                       p->minValue + (p->maxValue - p->minValue) * newValue, 0);

                sendParameterChangeEvent (index);
            }
        }
    }

    void sendParameterChangeEvent (int index)
    {
        jassert (audioUnit != 0);

        const ParamInfo& p = *parameters.getUnchecked (index);

        AudioUnitEvent ev;
        ev.mEventType                        = kAudioUnitEvent_ParameterValueChange;
        ev.mArgument.mParameter.mAudioUnit   = audioUnit;
        ev.mArgument.mParameter.mParameterID = p.paramID;
        ev.mArgument.mParameter.mScope       = kAudioUnitScope_Global;
        ev.mArgument.mParameter.mElement     = 0;

        AUEventListenerNotify (nullptr, nullptr, &ev);
    }

    void sendAllParametersChangedEvents()
    {
        for (int i = 0; i < parameters.size(); ++i)
            sendParameterChangeEvent (i);
    }

    const String getParameterName (int index)
    {
        if (const ParamInfo* p = parameters[index])
            return p->name;

        return String::empty;
    }

    const String getParameterText (int index)   { return String (getParameter (index)); }

    bool isParameterAutomatable (int index) const
    {
        if (const ParamInfo* p = parameters[index])
            return p->automatable;

        return false;
    }

    //==============================================================================
    int getNumPrograms()
    {
        CFArrayRef presets;
        UInt32 sz = sizeof (CFArrayRef);
        int num = 0;

        if (AudioUnitGetProperty (audioUnit, kAudioUnitProperty_FactoryPresets,
                                  kAudioUnitScope_Global, 0, &presets, &sz) == noErr)
        {
            num = (int) CFArrayGetCount (presets);
            CFRelease (presets);
        }

        return num;
    }

    int getCurrentProgram()
    {
        AUPreset current;
        current.presetNumber = 0;
        UInt32 sz = sizeof (AUPreset);

        AudioUnitGetProperty (audioUnit, kAudioUnitProperty_PresentPreset,
                              kAudioUnitScope_Global, 0, &current, &sz);

        return current.presetNumber;
    }

    void setCurrentProgram (int newIndex)
    {
        AUPreset current;
        current.presetNumber = newIndex;
        current.presetName = CFSTR("");

        AudioUnitSetProperty (audioUnit, kAudioUnitProperty_PresentPreset,
                              kAudioUnitScope_Global, 0, &current, sizeof (AUPreset));

        sendAllParametersChangedEvents();
    }

    const String getProgramName (int index)
    {
        String s;
        CFArrayRef presets;
        UInt32 sz = sizeof (CFArrayRef);

        if (AudioUnitGetProperty (audioUnit, kAudioUnitProperty_FactoryPresets,
                                  kAudioUnitScope_Global, 0, &presets, &sz) == noErr)
        {
            for (CFIndex i = 0; i < CFArrayGetCount (presets); ++i)
            {
                if (const AUPreset* p = (const AUPreset*) CFArrayGetValueAtIndex (presets, i))
                {
                    if (p->presetNumber == index)
                    {
                        s = String::fromCFString (p->presetName);
                        break;
                    }
                }
            }

            CFRelease (presets);
        }

        return s;
    }

    void changeProgramName (int index, const String& newName)
    {
        jassertfalse; // xxx not implemented!
    }

    //==============================================================================
    void getStateInformation (MemoryBlock& destData)
    {
        getCurrentProgramStateInformation (destData);
    }

    void getCurrentProgramStateInformation (MemoryBlock& destData)
    {
        CFPropertyListRef propertyList = 0;
        UInt32 sz = sizeof (CFPropertyListRef);

        if (AudioUnitGetProperty (audioUnit,
                                  kAudioUnitProperty_ClassInfo,
                                  kAudioUnitScope_Global,
                                  0, &propertyList, &sz) == noErr)
        {
            CFWriteStreamRef stream = CFWriteStreamCreateWithAllocatedBuffers (kCFAllocatorDefault, kCFAllocatorDefault);
            CFWriteStreamOpen (stream);

            CFIndex bytesWritten = CFPropertyListWriteToStream (propertyList, stream, kCFPropertyListBinaryFormat_v1_0, 0);
            CFWriteStreamClose (stream);

            CFDataRef data = (CFDataRef) CFWriteStreamCopyProperty (stream, kCFStreamPropertyDataWritten);

            destData.setSize (bytesWritten);
            destData.copyFrom (CFDataGetBytePtr (data), 0, destData.getSize());
            CFRelease (data);

            CFRelease (stream);
            CFRelease (propertyList);
        }
    }

    void setStateInformation (const void* data, int sizeInBytes)
    {
        setCurrentProgramStateInformation (data, sizeInBytes);
    }

    void setCurrentProgramStateInformation (const void* data, int sizeInBytes)
    {
        CFReadStreamRef stream = CFReadStreamCreateWithBytesNoCopy (kCFAllocatorDefault,
                                                                    (const UInt8*) data,
                                                                    sizeInBytes,
                                                                    kCFAllocatorNull);
        CFReadStreamOpen (stream);

        CFPropertyListFormat format = kCFPropertyListBinaryFormat_v1_0;
        CFPropertyListRef propertyList = CFPropertyListCreateFromStream (kCFAllocatorDefault,
                                                                         stream,
                                                                         0,
                                                                         kCFPropertyListImmutable,
                                                                         &format,
                                                                         0);
        CFRelease (stream);

        if (propertyList != 0)
        {
            AudioUnitSetProperty (audioUnit,
                                  kAudioUnitProperty_ClassInfo,
                                  kAudioUnitScope_Global,
                                  0, &propertyList, sizeof (propertyList));

            sendAllParametersChangedEvents();
        }
    }

    void refreshParameterList()
    {
        parameters.clear();

        if (audioUnit != 0)
        {
            UInt32 paramListSize = 0;
            AudioUnitGetProperty (audioUnit, kAudioUnitProperty_ParameterList, kAudioUnitScope_Global,
                                  0, 0, &paramListSize);

            if (paramListSize > 0)
            {
                const size_t numParams = paramListSize / sizeof (int);

                HeapBlock<UInt32> ids;
                ids.calloc (numParams);

                AudioUnitGetProperty (audioUnit, kAudioUnitProperty_ParameterList, kAudioUnitScope_Global,
                                      0, ids, &paramListSize);

                for (int i = 0; i < numParams; ++i)
                {
                    AudioUnitParameterInfo info;
                    UInt32 sz = sizeof (info);

                    if (AudioUnitGetProperty (audioUnit,
                                              kAudioUnitProperty_ParameterInfo,
                                              kAudioUnitScope_Global,
                                              ids[i], &info, &sz) == noErr)
                    {
                        ParamInfo* const param = new ParamInfo();
                        parameters.add (param);
                        param->paramID = ids[i];
                        param->minValue = info.minValue;
                        param->maxValue = info.maxValue;
                        param->automatable = (info.flags & kAudioUnitParameterFlag_NonRealTime) == 0;

                        if ((info.flags & kAudioUnitParameterFlag_HasCFNameString) != 0)
                        {
                            param->name = String::fromCFString (info.cfNameString);

                            if ((info.flags & kAudioUnitParameterFlag_CFNameRelease) != 0)
                                CFRelease (info.cfNameString);
                        }
                        else
                        {
                            param->name = String (info.name, sizeof (info.name));
                        }
                    }
                }
            }
        }
    }

    void handleIncomingMidiMessage (void*, const MidiMessage& message)
    {
        const ScopedLock sl (midiInLock);
        incomingMidi.addEvent (message, 0);
    }

    void handlePartialSysexMessage (void*, const uint8*, int, double) {}

private:
    //==============================================================================
    friend class AudioUnitPluginWindowCarbon;
    friend class AudioUnitPluginWindowCocoa;
    friend class AudioUnitPluginFormat;

    ComponentDescription componentDesc;
    String pluginName, manufacturer, version;
    String fileOrIdentifier;
    CriticalSection lock;
    bool wantsMidiMessages, producesMidiMessages, wasPlaying, prepared;

    HeapBlock <AudioBufferList> outputBufferList;
    AudioTimeStamp timeStamp;
    AudioSampleBuffer* currentBuffer;
    int numInputBusChannels, numOutputBusChannels, numInputBusses, numOutputBusses;

    AudioUnit audioUnit;
    AUParameterListenerRef parameterListenerRef;

    struct ParamInfo
    {
        UInt32 paramID;
        String name;
        AudioUnitParameterValue minValue, maxValue;
        bool automatable;
    };

    OwnedArray <ParamInfo> parameters;

    MidiDataConcatenator midiConcatenator;
    CriticalSection midiInLock;
    MidiBuffer incomingMidi;

    void setPluginCallbacks()
    {
        if (audioUnit != 0)
        {
            {
                AURenderCallbackStruct info;
                zerostruct (info); // (can't use "= { 0 }" on this object because it's typedef'ed as a C struct)

                info.inputProcRefCon = this;
                info.inputProc = renderGetInputCallback;

                for (int i = 0; i < numInputBusses; ++i)
                    AudioUnitSetProperty (audioUnit, kAudioUnitProperty_SetRenderCallback,
                                          kAudioUnitScope_Input, i, &info, sizeof (info));
            }

            if (producesMidiMessages)
            {
                AUMIDIOutputCallbackStruct info;
                zerostruct (info);

                info.userData = this;
                info.midiOutputCallback = renderMidiOutputCallback;

                producesMidiMessages = (AudioUnitSetProperty (audioUnit, kAudioUnitProperty_MIDIOutputCallback,
                                                              kAudioUnitScope_Global, 0, &info, sizeof (info)) == noErr);
            }

            {
                HostCallbackInfo info;
                zerostruct (info);

                info.hostUserData = this;
                info.beatAndTempoProc = getBeatAndTempoCallback;
                info.musicalTimeLocationProc = getMusicalTimeLocationCallback;
                info.transportStateProc = getTransportStateCallback;

                AudioUnitSetProperty (audioUnit, kAudioUnitProperty_HostCallbacks,
                                      kAudioUnitScope_Global, 0, &info, sizeof (info));
            }

            AUListenerCreate (parameterListenerCallback, this, nullptr, nullptr, 0, &parameterListenerRef);

            for (int i = 0; i < parameters.size(); ++i)
            {
                const ParamInfo& p = *parameters.getUnchecked(i);

                AudioUnitParameter paramToAdd;
                paramToAdd.mAudioUnit = audioUnit;
                paramToAdd.mParameterID = p.paramID;
                paramToAdd.mScope = kAudioUnitScope_Global;
                paramToAdd.mElement = 0;

                AUListenerAddParameter (parameterListenerRef, nullptr, &paramToAdd);
            }
        }
    }

    void parameterChanged (const AudioUnitParameter* param, AudioUnitParameterValue newValue)
    {
        for (int i = 0; i < parameters.size(); ++i)
        {
            const ParamInfo& p = *parameters.getUnchecked(i);

            if (p.paramID == param->mParameterID)
            {
                sendParamChangeMessageToListeners (i, (newValue - p.minValue) / (p.maxValue - p.minValue));
                break;
            }
        }
    }

    static void parameterListenerCallback (void* userData, void*, const AudioUnitParameter* param, AudioUnitParameterValue newValue)
    {
        ((AudioUnitPluginInstance*) userData)->parameterChanged (param, newValue);
    }

    //==============================================================================
    OSStatus renderGetInput (AudioUnitRenderActionFlags* ioActionFlags,
                             const AudioTimeStamp* inTimeStamp,
                             UInt32 inBusNumber,
                             UInt32 inNumberFrames,
                             AudioBufferList* ioData) const
    {
        if (currentBuffer != nullptr)
        {
            jassert (inNumberFrames == (UInt32) currentBuffer->getNumSamples()); // if this ever happens, might need to add extra handling

            for (UInt32 i = 0; i < ioData->mNumberBuffers; ++i)
            {
                const int bufferChannel = inBusNumber * numInputBusChannels + i;

                if (bufferChannel < currentBuffer->getNumChannels())
                {
                    memcpy (ioData->mBuffers[i].mData,
                            currentBuffer->getSampleData (bufferChannel, 0),
                            sizeof (float) * inNumberFrames);
                }
                else
                {
                    zeromem (ioData->mBuffers[i].mData,
                             sizeof (float) * inNumberFrames);
                }
            }
        }

        return noErr;
    }

    OSStatus renderMidiOutput (const MIDIPacketList* pktlist)
    {
        if (pktlist != nullptr && pktlist->numPackets)
        {
            const double time = Time::getMillisecondCounterHiRes() * 0.001;
            const MIDIPacket* packet = &pktlist->packet[0];

            for (UInt32 i = 0; i < pktlist->numPackets; ++i)
            {
                midiConcatenator.pushMidiData (packet->data, (int) packet->length, time, (void*) nullptr, *this);
                packet = MIDIPacketNext (packet);
            }
        }

        return noErr;
    }

    OSStatus getBeatAndTempo (Float64* outCurrentBeat, Float64* outCurrentTempo) const
    {
        AudioPlayHead* const ph = getPlayHead();
        AudioPlayHead::CurrentPositionInfo result;

        if (ph != nullptr && ph->getCurrentPosition (result))
        {
            if (outCurrentBeat  != nullptr)    *outCurrentBeat  = result.ppqPosition;
            if (outCurrentTempo != nullptr)    *outCurrentTempo = result.bpm;
        }
        else
        {
            if (outCurrentBeat  != nullptr)    *outCurrentBeat  = 0;
            if (outCurrentTempo != nullptr)    *outCurrentTempo = 120.0;
        }

        return noErr;
    }

    OSStatus getMusicalTimeLocation (UInt32* outDeltaSampleOffsetToNextBeat, Float32* outTimeSig_Numerator,
                                     UInt32* outTimeSig_Denominator, Float64* outCurrentMeasureDownBeat) const
    {
        AudioPlayHead* const ph = getPlayHead();
        AudioPlayHead::CurrentPositionInfo result;

        if (ph != nullptr && ph->getCurrentPosition (result))
        {
            if (outTimeSig_Numerator != nullptr)            *outTimeSig_Numerator   = result.timeSigNumerator;
            if (outTimeSig_Denominator != nullptr)          *outTimeSig_Denominator = result.timeSigDenominator;
            if (outDeltaSampleOffsetToNextBeat != nullptr)  *outDeltaSampleOffsetToNextBeat = 0; //xxx
            if (outCurrentMeasureDownBeat != nullptr)       *outCurrentMeasureDownBeat = result.ppqPositionOfLastBarStart; //xxx wrong
        }
        else
        {
            if (outDeltaSampleOffsetToNextBeat != nullptr)  *outDeltaSampleOffsetToNextBeat = 0;
            if (outTimeSig_Numerator != nullptr)            *outTimeSig_Numerator = 4;
            if (outTimeSig_Denominator != nullptr)          *outTimeSig_Denominator = 4;
            if (outCurrentMeasureDownBeat != nullptr)       *outCurrentMeasureDownBeat = 0;
        }

        return noErr;
    }

    OSStatus getTransportState (Boolean* outIsPlaying, Boolean* outTransportStateChanged,
                                Float64* outCurrentSampleInTimeLine, Boolean* outIsCycling,
                                Float64* outCycleStartBeat, Float64* outCycleEndBeat)
    {
        AudioPlayHead* const ph = getPlayHead();
        AudioPlayHead::CurrentPositionInfo result;

        if (ph != nullptr && ph->getCurrentPosition (result))
        {
            if (outIsPlaying != nullptr)
                *outIsPlaying = result.isPlaying;

            if (outTransportStateChanged != nullptr)
            {
                *outTransportStateChanged = result.isPlaying != wasPlaying;
                wasPlaying = result.isPlaying;
            }

            if (outCurrentSampleInTimeLine != nullptr)
                *outCurrentSampleInTimeLine = (Float64) result.timeInSamples;

            if (outIsCycling != nullptr)        *outIsCycling = false;
            if (outCycleStartBeat != nullptr)   *outCycleStartBeat = 0;
            if (outCycleEndBeat != nullptr)     *outCycleEndBeat = 0;
        }
        else
        {
            if (outIsPlaying != nullptr)                *outIsPlaying = false;
            if (outTransportStateChanged != nullptr)    *outTransportStateChanged = false;
            if (outCurrentSampleInTimeLine != nullptr)  *outCurrentSampleInTimeLine = 0;
            if (outIsCycling != nullptr)                *outIsCycling = false;
            if (outCycleStartBeat != nullptr)           *outCycleStartBeat = 0;
            if (outCycleEndBeat != nullptr)             *outCycleEndBeat = 0;
        }

        return noErr;
    }

    //==============================================================================
    static OSStatus renderGetInputCallback (void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags,
                                            const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber,
                                            UInt32 inNumberFrames, AudioBufferList* ioData)
    {
        return static_cast <AudioUnitPluginInstance*> (inRefCon)
                    ->renderGetInput (ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames, ioData);
    }

    static OSStatus renderMidiOutputCallback (void* userData, const AudioTimeStamp* timeStamp, UInt32 midiOutNum,
                                              const struct MIDIPacketList* pktlist)
    {
        return static_cast <AudioUnitPluginInstance*> (userData)->renderMidiOutput (pktlist);
    }

    static OSStatus getBeatAndTempoCallback (void* inHostUserData, Float64* outCurrentBeat, Float64* outCurrentTempo)
    {
        return static_cast <AudioUnitPluginInstance*> (inHostUserData)
                    ->getBeatAndTempo (outCurrentBeat, outCurrentTempo);
    }

    static OSStatus getMusicalTimeLocationCallback (void* inHostUserData, UInt32* outDeltaSampleOffsetToNextBeat,
                                                    Float32* outTimeSig_Numerator, UInt32* outTimeSig_Denominator,
                                                    Float64* outCurrentMeasureDownBeat)
    {
        return static_cast <AudioUnitPluginInstance*> (inHostUserData)
                    ->getMusicalTimeLocation (outDeltaSampleOffsetToNextBeat, outTimeSig_Numerator,
                                              outTimeSig_Denominator, outCurrentMeasureDownBeat);
    }

    static OSStatus getTransportStateCallback (void* inHostUserData, Boolean* outIsPlaying, Boolean* outTransportStateChanged,
                                               Float64* outCurrentSampleInTimeLine, Boolean* outIsCycling,
                                               Float64* outCycleStartBeat, Float64* outCycleEndBeat)
    {
        return static_cast <AudioUnitPluginInstance*> (inHostUserData)
                    ->getTransportState (outIsPlaying, outTransportStateChanged, outCurrentSampleInTimeLine,
                                         outIsCycling, outCycleStartBeat, outCycleEndBeat);
    }

    //==============================================================================
    size_t getAudioBufferSizeInBytes() const noexcept
    {
        return offsetof (AudioBufferList, mBuffers) + (sizeof (AudioBuffer) * numOutputBusChannels);
    }

    AudioBufferList* getAudioBufferListForBus (int busIndex) const noexcept
    {
        return addBytesToPointer (outputBufferList.getData(), getAudioBufferSizeInBytes() * busIndex);
    }

    int getElementCount (AudioUnitScope scope) const noexcept
    {
        UInt32 count;
        UInt32 countSize = sizeof (count);

        if (AudioUnitGetProperty (audioUnit, kAudioUnitProperty_ElementCount, scope, 0, &count, &countSize) != noErr
             || countSize == 0)
            count = 1;

        return (int) count;
    }

    void updateNumChannels()
    {
        numInputBusses = getElementCount (kAudioUnitScope_Input);
        numOutputBusses = getElementCount (kAudioUnitScope_Output);

        AUChannelInfo supportedChannels [128];
        UInt32 supportedChannelsSize = sizeof (supportedChannels);

        if (AudioUnitGetProperty (audioUnit, kAudioUnitProperty_SupportedNumChannels, kAudioUnitScope_Global,
                                  0, supportedChannels, &supportedChannelsSize) == noErr
             && supportedChannelsSize > 0)
        {
            int explicitNumIns = 0;
            int explicitNumOuts = 0;
            int maximumNumIns = 0;
            int maximumNumOuts = 0;

            for (int i = 0; i < (int) (supportedChannelsSize / sizeof (AUChannelInfo)); ++i)
            {
                const int inChannels  = (int) supportedChannels[i].inChannels;
                const int outChannels = (int) supportedChannels[i].outChannels;

                if (inChannels < 0)
                    maximumNumIns  = jmin (maximumNumIns, inChannels);
                else
                    explicitNumIns = jmax (explicitNumIns, inChannels);

                if (outChannels < 0)
                    maximumNumOuts  = jmin (maximumNumOuts, outChannels);
                else
                    explicitNumOuts = jmax (explicitNumOuts, outChannels);
            }

            if ((maximumNumIns == -1 && maximumNumOuts == -1)  // (special meaning: any number of ins/outs, as long as they match)
                || (maximumNumIns == -2 && maximumNumOuts == -1) // (special meaning: any number of ins/outs, even if they don't match)
                || (maximumNumIns == -1 && maximumNumOuts == -2))
            {
                numInputBusChannels = numOutputBusChannels = 2;
            }
            else
            {
                numInputBusChannels = explicitNumIns;
                numOutputBusChannels = explicitNumOuts;

                if (maximumNumIns == -1 || (maximumNumIns < 0 && explicitNumIns <= -maximumNumIns))
                    numInputBusChannels = 2;

                if (maximumNumOuts == -1 || (maximumNumOuts < 0 && explicitNumOuts <= -maximumNumOuts))
                    numOutputBusChannels = 2;
            }
        }
        else
        {
            // (this really means the plugin will take any number of ins/outs as long
            // as they are the same)
            numInputBusChannels = numOutputBusChannels = 2;
        }
    }

    bool canProduceMidiOutput()
    {
        UInt32 dataSize = 0;
        Boolean isWritable = false;

        if (AudioUnitGetPropertyInfo (audioUnit, kAudioUnitProperty_MIDIOutputCallbackInfo,
                                      kAudioUnitScope_Global, 0, &dataSize, &isWritable) == noErr
             && dataSize != 0)
        {
            CFArrayRef midiArray;

            if (AudioUnitGetProperty (audioUnit, kAudioUnitProperty_MIDIOutputCallbackInfo,
                                      kAudioUnitScope_Global, 0, &midiArray, &dataSize) == noErr)
            {
                bool result = (CFArrayGetCount (midiArray) > 0);
                CFRelease (midiArray);
                return result;
            }
        }

        return false;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioUnitPluginInstance)
};

//==============================================================================
class AudioUnitPluginWindowCocoa    : public AudioProcessorEditor,
                                      public Timer
{
public:
    AudioUnitPluginWindowCocoa (AudioUnitPluginInstance& p, const bool createGenericViewIfNeeded)
        : AudioProcessorEditor (&p),
          plugin (p)
    {
        addAndMakeVisible (&wrapper);

        setOpaque (true);
        setVisible (true);
        setSize (100, 100);

        createView (createGenericViewIfNeeded);
    }

    ~AudioUnitPluginWindowCocoa()
    {
        if (isValid())
        {
            wrapper.setVisible (false);
            removeChildComponent (&wrapper);
            wrapper.setView (nil);
            plugin.editorBeingDeleted (this);
        }
    }

    bool isValid() const        { return wrapper.getView() != nil; }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::white);
    }

    void resized()
    {
        wrapper.setSize (getWidth(), getHeight());
    }

    void timerCallback()
    {
        wrapper.resizeToFitView();
        startTimer (jmin (713, getTimerInterval() + 51));
    }

    void childBoundsChanged (Component* child)
    {
        setSize (wrapper.getWidth(), wrapper.getHeight());
        startTimer (70);
    }

private:
    AudioUnitPluginInstance& plugin;
    NSViewComponent wrapper;

    bool createView (const bool createGenericViewIfNeeded)
    {
        NSView* pluginView = nil;
        UInt32 dataSize = 0;
        Boolean isWritable = false;

        AudioUnitInitialize (plugin.audioUnit);

        if (AudioUnitGetPropertyInfo (plugin.audioUnit, kAudioUnitProperty_CocoaUI, kAudioUnitScope_Global,
                                      0, &dataSize, &isWritable) == noErr
             && dataSize != 0
             && AudioUnitGetPropertyInfo (plugin.audioUnit, kAudioUnitProperty_CocoaUI, kAudioUnitScope_Global,
                                          0, &dataSize, &isWritable) == noErr)
        {
            HeapBlock <AudioUnitCocoaViewInfo> info;
            info.calloc (dataSize, 1);

            if (AudioUnitGetProperty (plugin.audioUnit, kAudioUnitProperty_CocoaUI, kAudioUnitScope_Global,
                                      0, info, &dataSize) == noErr)
            {
                NSString* viewClassName = (NSString*) (info->mCocoaAUViewClass[0]);
                CFStringRef path = CFURLCopyPath (info->mCocoaAUViewBundleLocation);
                NSString* unescapedPath = (NSString*) CFURLCreateStringByReplacingPercentEscapes (0, path, CFSTR (""));
                CFRelease (path);
                NSBundle* viewBundle = [NSBundle bundleWithPath: [unescapedPath autorelease]];
                Class viewClass = [viewBundle classNamed: viewClassName];

                if ([viewClass conformsToProtocol: @protocol (AUCocoaUIBase)]
                     && [viewClass instancesRespondToSelector: @selector (interfaceVersion)]
                     && [viewClass instancesRespondToSelector: @selector (uiViewForAudioUnit: withSize:)])
                {
                    id factory = [[[viewClass alloc] init] autorelease];
                    pluginView = [factory uiViewForAudioUnit: plugin.audioUnit
                                                    withSize: NSMakeSize (getWidth(), getHeight())];
                }

                for (int i = (dataSize - sizeof (CFURLRef)) / sizeof (CFStringRef); --i >= 0;)
                    CFRelease (info->mCocoaAUViewClass[i]);

                CFRelease (info->mCocoaAUViewBundleLocation);
            }
        }

        if (createGenericViewIfNeeded && (pluginView == nil))
        {
            {
                // This forces CoreAudio.component to be loaded, otherwise the AUGenericView will assert
                ComponentDescription desc;
                String name, version, manufacturer;
                AudioUnitFormatHelpers::getComponentDescFromIdentifier ("AudioUnit:Output/auou,genr,appl",
                                                                        desc, name, version, manufacturer);
            }

            pluginView = [[AUGenericView alloc] initWithAudioUnit: plugin.audioUnit];
        }

        wrapper.setView (pluginView);

        if (pluginView != nil)
        {
            timerCallback();
            startTimer (70);
        }

        return pluginView != nil;
    }
};

#if JUCE_SUPPORT_CARBON

//==============================================================================
class AudioUnitPluginWindowCarbon   : public AudioProcessorEditor
{
public:
    AudioUnitPluginWindowCarbon (AudioUnitPluginInstance& plugin_)
        : AudioProcessorEditor (&plugin_),
          plugin (plugin_),
          componentRecord (nullptr),
          viewComponent (0)
    {
        addAndMakeVisible (innerWrapper = new InnerWrapperComponent (*this));

        setOpaque (true);
        setVisible (true);
        setSize (400, 300);

        UInt32 propertySize;
        if (AudioUnitGetPropertyInfo (plugin.audioUnit, kAudioUnitProperty_GetUIComponentList,
                                      kAudioUnitScope_Global, 0, &propertySize, NULL) == noErr
             && propertySize > 0)
        {
            HeapBlock<ComponentDescription> views (propertySize / sizeof (ComponentDescription));

            if (AudioUnitGetProperty (plugin.audioUnit, kAudioUnitProperty_GetUIComponentList,
                                      kAudioUnitScope_Global, 0, &views[0], &propertySize) == noErr)
            {
                componentRecord = FindNextComponent (0, &views[0]);
            }
        }
    }

    ~AudioUnitPluginWindowCarbon()
    {
        innerWrapper = nullptr;

        if (isValid())
            plugin.editorBeingDeleted (this);
    }

    bool isValid() const noexcept           { return componentRecord != nullptr; }

    //==============================================================================
    void paint (Graphics& g)
    {
        g.fillAll (Colours::black);
    }

    void resized()
    {
        if (innerWrapper != nullptr)
            innerWrapper->setSize (getWidth(), getHeight());
    }

    //==============================================================================
    bool keyStateChanged (bool)         { return false; }
    bool keyPressed (const KeyPress&)   { return false; }

    //==============================================================================
    AudioUnit getAudioUnit() const      { return plugin.audioUnit; }

    AudioUnitCarbonView getViewComponent()
    {
        if (viewComponent == 0 && componentRecord != nullptr)
            viewComponent = (AudioUnitCarbonView) OpenComponent (componentRecord);

        return viewComponent;
    }

    void closeViewComponent()
    {
        if (viewComponent != 0)
        {
            log ("Closing AU GUI: " + plugin.getName());

            CloseComponent (viewComponent);
            viewComponent = 0;
        }
    }

private:
    //==============================================================================
    AudioUnitPluginInstance& plugin;
    ComponentRecord* componentRecord;
    AudioUnitCarbonView viewComponent;

    //==============================================================================
    class InnerWrapperComponent   : public CarbonViewWrapperComponent
    {
    public:
        InnerWrapperComponent (AudioUnitPluginWindowCarbon& owner_)
            : owner (owner_)
        {
        }

        ~InnerWrapperComponent()
        {
            deleteWindow();
        }

        HIViewRef attachView (WindowRef windowRef, HIViewRef rootView)
        {
            log ("Opening AU GUI: " + owner.plugin.getName());

            AudioUnitCarbonView carbonView = owner.getViewComponent();

            if (carbonView == 0)
                return 0;

            Float32Point pos = { 0, 0 };
            Float32Point size = { 250, 200 };

            HIViewRef pluginView = 0;

            AudioUnitCarbonViewCreate (carbonView,
                                       owner.getAudioUnit(),
                                       windowRef,
                                       rootView,
                                       &pos,
                                       &size,
                                       (ControlRef*) &pluginView);

            return pluginView;
        }

        void removeView (HIViewRef)
        {
            owner.closeViewComponent();
        }

    private:
        AudioUnitPluginWindowCarbon& owner;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InnerWrapperComponent)
    };

    friend class InnerWrapperComponent;
    ScopedPointer<InnerWrapperComponent> innerWrapper;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioUnitPluginWindowCarbon)
};

#endif

//==============================================================================
AudioProcessorEditor* AudioUnitPluginInstance::createEditor()
{
    ScopedPointer<AudioProcessorEditor> w (new AudioUnitPluginWindowCocoa (*this, false));

    if (! static_cast <AudioUnitPluginWindowCocoa*> (w.get())->isValid())
        w = nullptr;

   #if JUCE_SUPPORT_CARBON
    if (w == nullptr)
    {
        w = new AudioUnitPluginWindowCarbon (*this);

        if (! static_cast <AudioUnitPluginWindowCarbon*> (w.get())->isValid())
            w = nullptr;
    }
   #endif

    if (w == nullptr)
        w = new AudioUnitPluginWindowCocoa (*this, true); // use AUGenericView as a fallback

    return w.release();
}


//==============================================================================
//==============================================================================
AudioUnitPluginFormat::AudioUnitPluginFormat()
{
}

AudioUnitPluginFormat::~AudioUnitPluginFormat()
{
}

void AudioUnitPluginFormat::findAllTypesForFile (OwnedArray <PluginDescription>& results,
                                                 const String& fileOrIdentifier)
{
    if (! fileMightContainThisPluginType (fileOrIdentifier))
        return;

    PluginDescription desc;
    desc.fileOrIdentifier = fileOrIdentifier;
    desc.uid = 0;

    try
    {
        ScopedPointer <AudioPluginInstance> createdInstance (createInstanceFromDescription (desc));

        if (AudioUnitPluginInstance* const auInstance = dynamic_cast <AudioUnitPluginInstance*> (createdInstance.get()))
        {
            auInstance->fillInPluginDescription (desc);
            results.add (new PluginDescription (desc));
        }
    }
    catch (...)
    {
        // crashed while loading...
    }
}

AudioPluginInstance* AudioUnitPluginFormat::createInstanceFromDescription (const PluginDescription& desc)
{
    if (fileMightContainThisPluginType (desc.fileOrIdentifier))
    {
        ScopedPointer <AudioUnitPluginInstance> result (new AudioUnitPluginInstance (desc.fileOrIdentifier));

        if (result->audioUnit != 0)
        {
            result->initialise();
            return result.release();
        }
    }

    return nullptr;
}

StringArray AudioUnitPluginFormat::searchPathsForPlugins (const FileSearchPath& /*directoriesToSearch*/,
                                                          const bool /*recursive*/)
{
    StringArray result;
    ComponentRecord* comp = nullptr;

    for (;;)
    {
        ComponentDescription desc;
        zerostruct (desc);

        comp = FindNextComponent (comp, &desc);

        if (comp == 0)
            break;

        GetComponentInfo (comp, &desc, 0, 0, 0);

        if (desc.componentType == kAudioUnitType_MusicDevice
             || desc.componentType == kAudioUnitType_MusicEffect
             || desc.componentType == kAudioUnitType_Effect
             || desc.componentType == kAudioUnitType_Generator
             || desc.componentType == kAudioUnitType_Panner)
        {
            const String s (AudioUnitFormatHelpers::createAUPluginIdentifier (desc));
            DBG (s);
            result.add (s);
        }
    }

    return result;
}

bool AudioUnitPluginFormat::fileMightContainThisPluginType (const String& fileOrIdentifier)
{
    ComponentDescription desc;

    String name, version, manufacturer;
    if (AudioUnitFormatHelpers::getComponentDescFromIdentifier (fileOrIdentifier, desc, name, version, manufacturer))
        return FindNextComponent (0, &desc) != 0;

    const File f (File::createFileWithoutCheckingPath (fileOrIdentifier));

    return f.hasFileExtension (".component")
             && f.isDirectory();
}

String AudioUnitPluginFormat::getNameOfPluginFromIdentifier (const String& fileOrIdentifier)
{
    ComponentDescription desc;
    String name, version, manufacturer;
    AudioUnitFormatHelpers::getComponentDescFromIdentifier (fileOrIdentifier, desc, name, version, manufacturer);

    if (name.isEmpty())
        name = fileOrIdentifier;

    return name;
}

bool AudioUnitPluginFormat::doesPluginStillExist (const PluginDescription& desc)
{
    if (desc.fileOrIdentifier.startsWithIgnoreCase (AudioUnitFormatHelpers::auIdentifierPrefix))
        return fileMightContainThisPluginType (desc.fileOrIdentifier);

    return File (desc.fileOrIdentifier).exists();
}

FileSearchPath AudioUnitPluginFormat::getDefaultLocationsToSearch()
{
    return FileSearchPath();
}

#undef log

#endif
