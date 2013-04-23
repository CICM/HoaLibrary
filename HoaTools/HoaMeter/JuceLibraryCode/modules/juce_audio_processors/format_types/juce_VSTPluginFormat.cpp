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

#if JUCE_PLUGINHOST_VST

//==============================================================================
#if JUCE_MAC && JUCE_SUPPORT_CARBON
 #include "../../juce_gui_extra/native/juce_mac_CarbonViewWrapperComponent.h"
#endif

#if JUCE_MAC
 static bool makeFSRefFromPath (FSRef* destFSRef, const String& path)
 {
     return FSPathMakeRef (reinterpret_cast <const UInt8*> (path.toUTF8().getAddress()), destFSRef, 0) == noErr;
 }
#endif

//==============================================================================
#undef PRAGMA_ALIGN_SUPPORTED
#define VST_FORCE_DEPRECATED 0

#if JUCE_MSVC
 #pragma warning (push)
 #pragma warning (disable: 4996)
#elif ! JUCE_MINGW
 #define __cdecl
#endif

/*  Obviously you're going to need the Steinberg vstsdk2.4 folder in
    your include path if you want to add VST support.

    If you're not interested in VSTs, you can disable them by setting the
    JUCE_PLUGINHOST_VST flag to 0.
*/
#include "pluginterfaces/vst2.x/aeffectx.h"

#if JUCE_MSVC
 #pragma warning (pop)
 #pragma warning (disable: 4355) // ("this" used in initialiser list warning)
#endif

//==============================================================================
#include "juce_VSTMidiEventList.h"

#if JUCE_MINGW
 extern "C" void _fpreset();
 extern "C" void _clearfp();
#elif ! JUCE_WINDOWS
 static void _fpreset() {}
 static void _clearfp() {}
#endif

#ifndef JUCE_VST_WRAPPER_LOAD_CUSTOM_MAIN
 #define JUCE_VST_WRAPPER_LOAD_CUSTOM_MAIN
#endif

#ifndef JUCE_VST_WRAPPER_INVOKE_MAIN
 #define JUCE_VST_WRAPPER_INVOKE_MAIN  effect = module->moduleMain (&audioMaster);
#endif

//==============================================================================
const int fxbVersionNum = 1;

struct fxProgram
{
    long chunkMagic;        // 'CcnK'
    long byteSize;          // of this chunk, excl. magic + byteSize
    long fxMagic;           // 'FxCk'
    long version;
    long fxID;              // fx unique id
    long fxVersion;
    long numParams;
    char prgName[28];
    float params[1];        // variable no. of parameters
};

struct fxSet
{
    long chunkMagic;        // 'CcnK'
    long byteSize;          // of this chunk, excl. magic + byteSize
    long fxMagic;           // 'FxBk'
    long version;
    long fxID;              // fx unique id
    long fxVersion;
    long numPrograms;
    char future[128];
    fxProgram programs[1];  // variable no. of programs
};

struct fxChunkSet
{
    long chunkMagic;        // 'CcnK'
    long byteSize;          // of this chunk, excl. magic + byteSize
    long fxMagic;           // 'FxCh', 'FPCh', or 'FBCh'
    long version;
    long fxID;              // fx unique id
    long fxVersion;
    long numPrograms;
    char future[128];
    long chunkSize;
    char chunk[8];          // variable
};

struct fxProgramSet
{
    long chunkMagic;        // 'CcnK'
    long byteSize;          // of this chunk, excl. magic + byteSize
    long fxMagic;           // 'FxCh', 'FPCh', or 'FBCh'
    long version;
    long fxID;              // fx unique id
    long fxVersion;
    long numPrograms;
    char name[28];
    long chunkSize;
    char chunk[8];          // variable
};

namespace
{
    long vst_swap (const long x) noexcept
    {
       #ifdef JUCE_LITTLE_ENDIAN
        return (long) ByteOrder::swap ((uint32) x);
       #else
        return x;
       #endif
    }

    float vst_swapFloat (const float x) noexcept
    {
       #ifdef JUCE_LITTLE_ENDIAN
        union { uint32 asInt; float asFloat; } n;
        n.asFloat = x;
        n.asInt = ByteOrder::swap (n.asInt);
        return n.asFloat;
       #else
        return x;
       #endif
    }

    double getVSTHostTimeNanoseconds()
    {
       #if JUCE_WINDOWS
        return timeGetTime() * 1000000.0;
       #elif JUCE_LINUX
        timeval micro;
        gettimeofday (&micro, 0);
        return micro.tv_usec * 1000.0;
       #elif JUCE_MAC
        UnsignedWide micro;
        Microseconds (&micro);
        return micro.lo * 1000.0;
       #endif
    }
}

//==============================================================================
typedef AEffect* (VSTCALLBACK *MainCall) (audioMasterCallback);

static VstIntPtr VSTCALLBACK audioMaster (AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt);

static int shellUIDToCreate = 0;
static int insideVSTCallback = 0;

class IdleCallRecursionPreventer
{
public:
    IdleCallRecursionPreventer()
        : isMessageThread (MessageManager::getInstance()->isThisTheMessageThread())
    {
        if (isMessageThread)
            ++insideVSTCallback;
    }

    ~IdleCallRecursionPreventer()
    {
        if (isMessageThread)
            --insideVSTCallback;
    }

private:
    const bool isMessageThread;

    JUCE_DECLARE_NON_COPYABLE (IdleCallRecursionPreventer)
};

class VSTPluginWindow;

//==============================================================================
// Change this to disable logging of various VST activities
#ifndef VST_LOGGING
 #define VST_LOGGING 1
#endif

#if VST_LOGGING
 #define JUCE_VST_LOG(a) Logger::writeToLog(a);
#else
 #define JUCE_VST_LOG(a)
#endif

//==============================================================================
#if JUCE_MAC && JUCE_PPC
static void* NewCFMFromMachO (void* const machofp) noexcept
{
    void* result = (void*) new char[8];

    ((void**) result)[0] = machofp;
    ((void**) result)[1] = result;

    return result;
}
#endif

//==============================================================================
#if JUCE_LINUX

extern Display* display;
extern XContext windowHandleXContext;

typedef void (*EventProcPtr) (XEvent* ev);

namespace
{
    static bool xErrorTriggered = false;

    int temporaryErrorHandler (Display*, XErrorEvent*)
    {
        xErrorTriggered = true;
        return 0;
    }

    EventProcPtr getPropertyFromXWindow (Window handle, Atom atom)
    {
        XErrorHandler oldErrorHandler = XSetErrorHandler (temporaryErrorHandler);
        xErrorTriggered = false;

        int userSize;
        unsigned long bytes, userCount;
        unsigned char* data;
        Atom userType;

        XGetWindowProperty (display, handle, atom, 0, 1, false, AnyPropertyType,
                            &userType,  &userSize, &userCount, &bytes, &data);

        XSetErrorHandler (oldErrorHandler);

        return (userCount == 1 && ! xErrorTriggered) ? *reinterpret_cast<EventProcPtr*> (data)
                                                     : 0;
    }

    Window getChildWindow (Window windowToCheck)
    {
        Window rootWindow, parentWindow;
        Window* childWindows;
        unsigned int numChildren = 0;

        XQueryTree (display,
                    windowToCheck,
                    &rootWindow,
                    &parentWindow,
                    &childWindows,
                    &numChildren);

        if (numChildren > 0)
            return childWindows [0];

        return 0;
    }

    void translateJuceToXButtonModifiers (const MouseEvent& e, XEvent& ev) noexcept
    {
        if (e.mods.isLeftButtonDown())
        {
            ev.xbutton.button = Button1;
            ev.xbutton.state |= Button1Mask;
        }
        else if (e.mods.isRightButtonDown())
        {
            ev.xbutton.button = Button3;
            ev.xbutton.state |= Button3Mask;
        }
        else if (e.mods.isMiddleButtonDown())
        {
            ev.xbutton.button = Button2;
            ev.xbutton.state |= Button2Mask;
        }
    }

    void translateJuceToXMotionModifiers (const MouseEvent& e, XEvent& ev) noexcept
    {
        if (e.mods.isLeftButtonDown())          ev.xmotion.state |= Button1Mask;
        else if (e.mods.isRightButtonDown())    ev.xmotion.state |= Button3Mask;
        else if (e.mods.isMiddleButtonDown())   ev.xmotion.state |= Button2Mask;
    }

    void translateJuceToXCrossingModifiers (const MouseEvent& e, XEvent& ev) noexcept
    {
        if (e.mods.isLeftButtonDown())          ev.xcrossing.state |= Button1Mask;
        else if (e.mods.isRightButtonDown())    ev.xcrossing.state |= Button3Mask;
        else if (e.mods.isMiddleButtonDown())   ev.xcrossing.state |= Button2Mask;
    }

    void translateJuceToXMouseWheelModifiers (const MouseEvent& e, const float increment, XEvent& ev) noexcept
    {
        if (increment < 0)
        {
            ev.xbutton.button = Button5;
            ev.xbutton.state |= Button5Mask;
        }
        else if (increment > 0)
        {
            ev.xbutton.button = Button4;
            ev.xbutton.state |= Button4Mask;
        }
    }
}

#endif

//==============================================================================
class ModuleHandle    : public ReferenceCountedObject
{
public:
    //==============================================================================
    File file;
    MainCall moduleMain, customMain;
    String pluginName;
    ScopedPointer<XmlElement> vstXml;

    typedef ReferenceCountedObjectPtr<ModuleHandle> Ptr;

    static Array <ModuleHandle*>& getActiveModules()
    {
        static Array <ModuleHandle*> activeModules;
        return activeModules;
    }

    //==============================================================================
    static ModuleHandle* findOrCreateModule (const File& file)
    {
        for (int i = getActiveModules().size(); --i >= 0;)
        {
            ModuleHandle* const module = getActiveModules().getUnchecked(i);

            if (module->file == file)
                return module;
        }

        _fpreset(); // (doesn't do any harm)

        const IdleCallRecursionPreventer icrp;
        shellUIDToCreate = 0;

        JUCE_VST_LOG ("Attempting to load VST: " + file.getFullPathName());

        ScopedPointer <ModuleHandle> m (new ModuleHandle (file));

        if (! m->open())
            m = nullptr;

        _fpreset(); // (doesn't do any harm)

        return m.release();
    }

    //==============================================================================
    ModuleHandle (const File& file_)
        : file (file_),
          moduleMain (nullptr),
          customMain (nullptr)
         #if JUCE_MAC
          #if JUCE_PPC
           , fragId (0)
          #endif
           , resHandle (0), bundleRef (0), resFileId (0)
         #endif
    {
        getActiveModules().add (this);

       #if JUCE_WINDOWS || JUCE_LINUX
        fullParentDirectoryPathName = file_.getParentDirectory().getFullPathName();
       #elif JUCE_MAC
        FSRef ref;
        makeFSRefFromPath (&ref, file_.getParentDirectory().getFullPathName());
        FSGetCatalogInfo (&ref, kFSCatInfoNone, 0, 0, &parentDirFSSpec, 0);
       #endif
    }

    ~ModuleHandle()
    {
        getActiveModules().removeFirstMatchingValue (this);
        close();
    }

    //==============================================================================
#if JUCE_WINDOWS || JUCE_LINUX
    DynamicLibrary module;
    String fullParentDirectoryPathName;

    bool open()
    {
        pluginName = file.getFileNameWithoutExtension();

        module.open (file.getFullPathName());

        moduleMain = (MainCall) module.getFunction ("VSTPluginMain");

        if (moduleMain == nullptr)
            moduleMain = (MainCall) module.getFunction ("main");

        JUCE_VST_WRAPPER_LOAD_CUSTOM_MAIN

        if (moduleMain != nullptr)
        {
            vstXml = XmlDocument::parse (file.withFileExtension ("vstxml"));

           #if JUCE_WINDOWS
            if (vstXml == nullptr)
                vstXml = XmlDocument::parse (getDLLResource (file, "VSTXML", 1));
           #endif
        }

        return moduleMain != nullptr;
    }

    void close()
    {
        _fpreset(); // (doesn't do any harm)

        module.close();
    }

    void closeEffect (AEffect* eff)
    {
        eff->dispatcher (eff, effClose, 0, 0, 0, 0);
    }

   #if JUCE_WINDOWS
    static String getDLLResource (const File& dllFile, const String& type, int resID)
    {
        DynamicLibrary dll (dllFile.getFullPathName());
        HMODULE dllModule = (HMODULE) dll.getNativeHandle();

        if (dllModule != INVALID_HANDLE_VALUE)
        {
            if (HRSRC res = FindResource (dllModule, MAKEINTRESOURCE (resID), type.toWideCharPointer()))
            {
                if (HGLOBAL hGlob = LoadResource (dllModule, res))
                {
                    const char* data = static_cast <const char*> (LockResource (hGlob));
                    return String::fromUTF8 (data, SizeofResource (dllModule, res));
                }
            }
        }

        return String::empty;
    }
   #endif
#else
   #if JUCE_PPC
    CFragConnectionID fragId;
   #endif
    Handle resHandle;
    CFBundleRef bundleRef;
    FSSpec parentDirFSSpec;
    short resFileId;

    bool open()
    {
        bool ok = false;

        if (file.hasFileExtension (".vst"))
        {
            const char* const utf8 = file.getFullPathName().toUTF8().getAddress();

            if (CFURLRef url = CFURLCreateFromFileSystemRepresentation (0, (const UInt8*) utf8,
                                                                        strlen (utf8), file.isDirectory()))
            {
                bundleRef = CFBundleCreate (kCFAllocatorDefault, url);
                CFRelease (url);

                if (bundleRef != 0)
                {
                    if (CFBundleLoadExecutable (bundleRef))
                    {
                        moduleMain = (MainCall) CFBundleGetFunctionPointerForName (bundleRef, CFSTR("main_macho"));

                        if (moduleMain == nullptr)
                            moduleMain = (MainCall) CFBundleGetFunctionPointerForName (bundleRef, CFSTR("VSTPluginMain"));

                        JUCE_VST_WRAPPER_LOAD_CUSTOM_MAIN

                        if (moduleMain != nullptr)
                        {
                            if (CFTypeRef name = CFBundleGetValueForInfoDictionaryKey (bundleRef, CFSTR("CFBundleName")))
                            {
                                if (CFGetTypeID (name) == CFStringGetTypeID())
                                {
                                    char buffer[1024];

                                    if (CFStringGetCString ((CFStringRef) name, buffer, sizeof (buffer), CFStringGetSystemEncoding()))
                                        pluginName = buffer;
                                }
                            }

                            if (pluginName.isEmpty())
                                pluginName = file.getFileNameWithoutExtension();

                            resFileId = CFBundleOpenBundleResourceMap (bundleRef);

                            ok = true;

                            Array<File> vstXmlFiles;
                            file.getChildFile ("Contents")
                                .getChildFile ("Resources")
                                .findChildFiles (vstXmlFiles, File::findFiles, false, "*.vstxml");

                            if (vstXmlFiles.size() > 0)
                                vstXml = XmlDocument::parse (vstXmlFiles.getReference(0));
                        }
                    }

                    if (! ok)
                    {
                        CFBundleUnloadExecutable (bundleRef);
                        CFRelease (bundleRef);
                        bundleRef = 0;
                    }
                }
            }
        }
#if JUCE_PPC
        else
        {
            FSRef fn;

            if (FSPathMakeRef ((UInt8*) file.getFullPathName().toUTF8().getAddress(), &fn, 0) == noErr)
            {
                resFileId = FSOpenResFile (&fn, fsRdPerm);

                if (resFileId != -1)
                {
                    const int numEffs = Count1Resources ('aEff');

                    for (int i = 0; i < numEffs; ++i)
                    {
                        resHandle = Get1IndResource ('aEff', i + 1);

                        if (resHandle != 0)
                        {
                            OSType type;
                            Str255 name;
                            SInt16 id;
                            GetResInfo (resHandle, &id, &type, name);
                            pluginName = String ((const char*) name + 1, name[0]);
                            DetachResource (resHandle);
                            HLock (resHandle);

                            Ptr ptr;
                            Str255 errorText;

                            OSErr err = GetMemFragment (*resHandle, GetHandleSize (resHandle),
                                                        name, kPrivateCFragCopy,
                                                        &fragId, &ptr, errorText);

                            if (err == noErr)
                            {
                                moduleMain = (MainCall) newMachOFromCFM (ptr);
                                ok = true;
                            }
                            else
                            {
                                HUnlock (resHandle);
                            }

                            break;
                        }
                    }

                    if (! ok)
                        CloseResFile (resFileId);
                }
            }
        }
#endif

        return ok;
    }

    void close()
    {
       #if JUCE_PPC
        if (fragId != 0)
        {
            if (moduleMain != nullptr)
                disposeMachOFromCFM ((void*) moduleMain);

            CloseConnection (&fragId);
            HUnlock (resHandle);

            if (resFileId != 0)
                CloseResFile (resFileId);
        }
        else
       #endif
        if (bundleRef != 0)
        {
            CFBundleCloseBundleResourceMap (bundleRef, resFileId);

            if (CFGetRetainCount (bundleRef) == 1)
                CFBundleUnloadExecutable (bundleRef);

            if (CFGetRetainCount (bundleRef) > 0)
                CFRelease (bundleRef);
        }
    }

    void closeEffect (AEffect* eff)
    {
       #if JUCE_PPC
        if (fragId != 0)
        {
            Array<void*> thingsToDelete;
            thingsToDelete.add ((void*) eff->dispatcher);
            thingsToDelete.add ((void*) eff->process);
            thingsToDelete.add ((void*) eff->setParameter);
            thingsToDelete.add ((void*) eff->getParameter);
            thingsToDelete.add ((void*) eff->processReplacing);

            eff->dispatcher (eff, effClose, 0, 0, 0, 0);

            for (int i = thingsToDelete.size(); --i >= 0;)
                disposeMachOFromCFM (thingsToDelete[i]);
        }
        else
       #endif
        {
            eff->dispatcher (eff, effClose, 0, 0, 0, 0);
        }
    }

   #if JUCE_PPC
    static void* newMachOFromCFM (void* cfmfp)
    {
        if (cfmfp == 0)
            return nullptr;

        UInt32* const mfp = new UInt32[6];

        mfp[0] = 0x3d800000 | ((UInt32) cfmfp >> 16);
        mfp[1] = 0x618c0000 | ((UInt32) cfmfp & 0xffff);
        mfp[2] = 0x800c0000;
        mfp[3] = 0x804c0004;
        mfp[4] = 0x7c0903a6;
        mfp[5] = 0x4e800420;

        MakeDataExecutable (mfp, sizeof (UInt32) * 6);
        return mfp;
    }

    static void disposeMachOFromCFM (void* ptr)
    {
        delete[] static_cast <UInt32*> (ptr);
    }

    void coerceAEffectFunctionCalls (AEffect* eff)
    {
        if (fragId != 0)
        {
            eff->dispatcher       = (AEffectDispatcherProc)   newMachOFromCFM ((void*) eff->dispatcher);
            eff->process          = (AEffectProcessProc)      newMachOFromCFM ((void*) eff->process);
            eff->setParameter     = (AEffectSetParameterProc) newMachOFromCFM ((void*) eff->setParameter);
            eff->getParameter     = (AEffectGetParameterProc) newMachOFromCFM ((void*) eff->getParameter);
            eff->processReplacing = (AEffectProcessProc)      newMachOFromCFM ((void*) eff->processReplacing);
        }
    }
   #endif

#endif

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleHandle)
};

static const int defaultVSTSampleRateValue = 44100;
static const int defaultVSTBlockSizeValue = 512;

//==============================================================================
//==============================================================================
class VSTPluginInstance     : public AudioPluginInstance,
                              private Timer,
                              private AsyncUpdater
{
public:
    VSTPluginInstance (const ModuleHandle::Ptr& module_)
        : effect (nullptr),
          module (module_),
          name (module_->pluginName),
          wantsMidiMessages (false),
          initialised (false),
          isPowerOn (false),
          tempBuffer (1, 1)
    {
        try
        {
            const IdleCallRecursionPreventer icrp;
            _fpreset();

            JUCE_VST_LOG ("Creating VST instance: " + name);

          #if JUCE_MAC
            if (module->resFileId != 0)
                UseResFile (module->resFileId);

           #if JUCE_PPC
            if (module->fragId != 0)
            {
                static void* audioMasterCoerced = nullptr;
                if (audioMasterCoerced == nullptr)
                    audioMasterCoerced = NewCFMFromMachO ((void*) &audioMaster);

                effect = module->moduleMain ((audioMasterCallback) audioMasterCoerced);
            }
            else
           #endif
          #endif
            {
                JUCE_VST_WRAPPER_INVOKE_MAIN
            }

            if (effect != nullptr && effect->magic == kEffectMagic)
            {
               #if JUCE_PPC
                module->coerceAEffectFunctionCalls (effect);
               #endif

                jassert (effect->resvd2 == 0);
                jassert (effect->object != 0);

                _fpreset(); // some dodgy plugs fuck around with this
            }
            else
            {
                effect = nullptr;
            }
        }
        catch (...)
        {}
    }

    ~VSTPluginInstance()
    {
        const ScopedLock sl (lock);

        if (effect != nullptr && effect->magic == kEffectMagic)
        {
            try
            {
               #if JUCE_MAC
                if (module->resFileId != 0)
                    UseResFile (module->resFileId);
               #endif

                // Must delete any editors before deleting the plugin instance!
                jassert (getActiveEditor() == 0);

                _fpreset(); // some dodgy plugs fuck around with this

                module->closeEffect (effect);
            }
            catch (...)
            {}
        }

        module = nullptr;
        effect = nullptr;
    }

    void fillInPluginDescription (PluginDescription& desc) const
    {
        desc.name = name;

        {
            char buffer [512] = { 0 };
            dispatch (effGetEffectName, 0, 0, buffer, 0);

            desc.descriptiveName = String (buffer).trim();

            if (desc.descriptiveName.isEmpty())
                desc.descriptiveName = name;
        }

        desc.fileOrIdentifier = module->file.getFullPathName();
        desc.uid = getUID();
        desc.lastFileModTime = module->file.getLastModificationTime();
        desc.pluginFormatName = "VST";
        desc.category = getCategory();

        {
            char buffer [kVstMaxVendorStrLen + 8] = { 0 };
            dispatch (effGetVendorString, 0, 0, buffer, 0);
            desc.manufacturerName = buffer;
        }

        desc.version = getVersion();
        desc.numInputChannels = getNumInputChannels();
        desc.numOutputChannels = getNumOutputChannels();
        desc.isInstrument = (effect != nullptr && (effect->flags & effFlagsIsSynth) != 0);
    }

    void initialise()
    {
        if (initialised || effect == 0)
            return;

       #if JUCE_WINDOWS
        // On Windows it's highly advisable to create your plugins using the message thread,
        // because many plugins need a chance to create HWNDs that will get their
        // messages delivered by the main message thread, and that's not possible from
        // a background thread.
        jassert (MessageManager::getInstance()->isThisTheMessageThread());
       #endif

        JUCE_VST_LOG ("Initialising VST: " + module->pluginName);
        initialised = true;

        dispatch (effIdentify, 0, 0, 0, 0);

        if (getSampleRate() > 0)
            dispatch (effSetSampleRate, 0, 0, 0, (float) getSampleRate());

        if (getBlockSize() > 0)
            dispatch (effSetBlockSize, 0, jmax (32, getBlockSize()), 0, 0);

        dispatch (effOpen, 0, 0, 0, 0);

        setPlayConfigDetails (effect->numInputs, effect->numOutputs,
                              getSampleRate(), getBlockSize());

        if (getNumPrograms() > 1)
            setCurrentProgram (0);
        else
            dispatch (effSetProgram, 0, 0, 0, 0);

        for (int i = effect->numInputs;  --i >= 0;)  dispatch (effConnectInput,  i, 1, 0, 0);
        for (int i = effect->numOutputs; --i >= 0;)  dispatch (effConnectOutput, i, 1, 0, 0);

        updateStoredProgramNames();

        wantsMidiMessages = dispatch (effCanDo, 0, 0, (void*) "receiveVstMidiEvent", 0) > 0;

        setLatencySamples (effect->initialDelay);
    }

    void* getPlatformSpecificData()  { return effect; }
    const String getName() const     { return name; }

    int getUID() const
    {
        int uid = effect != nullptr ? effect->uniqueID : 0;

        if (uid == 0)
            uid = module->file.hashCode();

        return uid;
    }

    bool silenceInProducesSilenceOut() const
    {
        return effect == nullptr || (effect->flags & effFlagsNoSoundInStop) != 0;
    }

    double getTailLengthSeconds() const
    {
        if (effect == nullptr)
            return 0.0;

        const double sampleRate = getSampleRate();

        if (sampleRate <= 0)
            return 0.0;

        VstIntPtr samples = dispatch (effGetTailSize, 0, 0, 0, 0);
        return samples / sampleRate;
    }

    bool acceptsMidi() const    { return wantsMidiMessages; }
    bool producesMidi() const   { return dispatch (effCanDo, 0, 0, (void*) "sendVstMidiEvent", 0) > 0; }

    //==============================================================================
    void prepareToPlay (double rate, int samplesPerBlockExpected)
    {
        setPlayConfigDetails (effect->numInputs, effect->numOutputs, rate, samplesPerBlockExpected);

        vstHostTime.tempo = 120.0;
        vstHostTime.timeSigNumerator = 4;
        vstHostTime.timeSigDenominator = 4;
        vstHostTime.sampleRate = rate;
        vstHostTime.samplePos = 0;
        vstHostTime.flags = kVstNanosValid | kVstAutomationWriting | kVstAutomationReading;

        initialise();

        if (initialised)
        {
            wantsMidiMessages = wantsMidiMessages
                                    || (dispatch (effCanDo, 0, 0, (void*) "receiveVstMidiEvent", 0) > 0);

            if (wantsMidiMessages)
                midiEventsToSend.ensureSize (256);
            else
                midiEventsToSend.freeEvents();

            incomingMidi.clear();

            dispatch (effSetSampleRate, 0, 0, 0, (float) rate);
            dispatch (effSetBlockSize, 0, jmax (16, samplesPerBlockExpected), 0, 0);

            tempBuffer.setSize (jmax (1, effect->numOutputs), samplesPerBlockExpected);

            if (! isPowerOn)
                setPower (true);

            // dodgy hack to force some plugins to initialise the sample rate..
            if ((! hasEditor()) && getNumParameters() > 0)
            {
                const float old = getParameter (0);
                setParameter (0, (old < 0.5f) ? 1.0f : 0.0f);
                setParameter (0, old);
            }

            dispatch (effStartProcess, 0, 0, 0, 0);

            setLatencySamples (effect->initialDelay);
        }
    }

    void releaseResources()
    {
        if (initialised)
        {
            dispatch (effStopProcess, 0, 0, 0, 0);
            setPower (false);
        }

        tempBuffer.setSize (1, 1);
        incomingMidi.clear();

        midiEventsToSend.freeEvents();
    }

    void reset()
    {
        if (isPowerOn)
        {
            setPower (false);
            setPower (true);
        }
    }

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
    {
        const int numSamples = buffer.getNumSamples();

        if (initialised)
        {
            if (AudioPlayHead* const playHead = getPlayHead())
            {
                AudioPlayHead::CurrentPositionInfo position;
                playHead->getCurrentPosition (position);

                vstHostTime.samplePos          = (double) position.timeInSamples;
                vstHostTime.tempo              = position.bpm;
                vstHostTime.timeSigNumerator   = position.timeSigNumerator;
                vstHostTime.timeSigDenominator = position.timeSigDenominator;
                vstHostTime.ppqPos             = position.ppqPosition;
                vstHostTime.barStartPos        = position.ppqPositionOfLastBarStart;
                vstHostTime.flags |= kVstTempoValid | kVstTimeSigValid | kVstPpqPosValid | kVstBarsValid;

                VstInt32 newTransportFlags = 0;
                if (position.isPlaying)     newTransportFlags |= kVstTransportPlaying;
                if (position.isRecording)   newTransportFlags |= kVstTransportRecording;

                if (newTransportFlags != (vstHostTime.flags & (kVstTransportPlaying | kVstTransportRecording)))
                    vstHostTime.flags = (vstHostTime.flags & ~(kVstTransportPlaying | kVstTransportRecording)) | newTransportFlags | kVstTransportChanged;
                else
                    vstHostTime.flags &= ~kVstTransportChanged;

                switch (position.frameRate)
                {
                    case AudioPlayHead::fps24:       setHostTimeFrameRate (0, 24.0,  position.timeInSeconds); break;
                    case AudioPlayHead::fps25:       setHostTimeFrameRate (1, 25.0,  position.timeInSeconds); break;
                    case AudioPlayHead::fps2997:     setHostTimeFrameRate (2, 29.97, position.timeInSeconds); break;
                    case AudioPlayHead::fps30:       setHostTimeFrameRate (3, 30.0,  position.timeInSeconds); break;
                    case AudioPlayHead::fps2997drop: setHostTimeFrameRate (4, 29.97, position.timeInSeconds); break;
                    case AudioPlayHead::fps30drop:   setHostTimeFrameRate (5, 29.97, position.timeInSeconds); break;
                    default: break;
                }

                if (position.isLooping)
                {
                    vstHostTime.cycleStartPos = position.ppqLoopStart;
                    vstHostTime.cycleEndPos = position.ppqLoopEnd;
                    vstHostTime.flags |= kVstCyclePosValid;
                }
                else
                {
                    vstHostTime.flags &= ~kVstCyclePosValid;
                }
            }

            vstHostTime.nanoSeconds = getVSTHostTimeNanoseconds();

            if (wantsMidiMessages)
            {
                midiEventsToSend.clear();
                midiEventsToSend.ensureSize (1);

                MidiBuffer::Iterator iter (midiMessages);
                const uint8* midiData;
                int numBytesOfMidiData, samplePosition;

                while (iter.getNextEvent (midiData, numBytesOfMidiData, samplePosition))
                {
                    midiEventsToSend.addEvent (midiData, numBytesOfMidiData,
                                               jlimit (0, numSamples - 1, samplePosition));
                }

                try
                {
                    effect->dispatcher (effect, effProcessEvents, 0, 0, midiEventsToSend.events, 0);
                }
                catch (...)
                {}
            }

            _clearfp();

            if ((effect->flags & effFlagsCanReplacing) != 0)
            {
                try
                {
                    effect->processReplacing (effect, buffer.getArrayOfChannels(), buffer.getArrayOfChannels(), numSamples);
                }
                catch (...)
                {}
            }
            else
            {
                tempBuffer.setSize (effect->numOutputs, numSamples);
                tempBuffer.clear();

                try
                {
                    effect->process (effect, buffer.getArrayOfChannels(), tempBuffer.getArrayOfChannels(), numSamples);
                }
                catch (...)
                {}

                for (int i = effect->numOutputs; --i >= 0;)
                    buffer.copyFrom (i, 0, tempBuffer.getSampleData (i), numSamples);
            }
        }
        else
        {
            // Not initialised, so just bypass..
            for (int i = 0; i < getNumOutputChannels(); ++i)
                buffer.clear (i, 0, buffer.getNumSamples());
        }

        {
            // copy any incoming midi..
            const ScopedLock sl (midiInLock);

            midiMessages.swapWith (incomingMidi);
            incomingMidi.clear();
        }
    }

    //==============================================================================
    bool hasEditor() const                  { return effect != nullptr && (effect->flags & effFlagsHasEditor) != 0; }
    AudioProcessorEditor* createEditor();

    //==============================================================================
    const String getInputChannelName (int index) const
    {
        if (index >= 0 && index < getNumInputChannels())
        {
            VstPinProperties pinProps;
            if (dispatch (effGetInputProperties, index, 0, &pinProps, 0.0f) != 0)
                return String (pinProps.label, sizeof (pinProps.label));
        }

        return String::empty;
    }

    bool isInputChannelStereoPair (int index) const
    {
        if (index < 0 || index >= getNumInputChannels())
            return false;

        VstPinProperties pinProps;
        if (dispatch (effGetInputProperties, index, 0, &pinProps, 0.0f) != 0)
            return (pinProps.flags & kVstPinIsStereo) != 0;

        return true;
    }

    const String getOutputChannelName (int index) const
    {
        if (index >= 0 && index < getNumOutputChannels())
        {
            VstPinProperties pinProps;
            if (dispatch (effGetOutputProperties, index, 0, &pinProps, 0.0f) != 0)
                return String (pinProps.label, sizeof (pinProps.label));
        }

        return String::empty;
    }

    bool isOutputChannelStereoPair (int index) const
    {
        if (index < 0 || index >= getNumOutputChannels())
            return false;

        VstPinProperties pinProps;
        if (dispatch (effGetOutputProperties, index, 0, &pinProps, 0.0f) != 0)
            return (pinProps.flags & kVstPinIsStereo) != 0;

        return true;
    }

    bool isValidChannel (int index, bool isInput) const
    {
        return isInput ? (index < getNumInputChannels())
                       : (index < getNumOutputChannels());
    }

    //==============================================================================
    int getNumParameters()      { return effect != nullptr ? effect->numParams : 0; }

    float getParameter (int index)
    {
        if (effect != nullptr && isPositiveAndBelow (index, (int) effect->numParams))
        {
            try
            {
                const ScopedLock sl (lock);
                return effect->getParameter (effect, index);
            }
            catch (...)
            {
            }
        }

        return 0.0f;
    }

    void setParameter (int index, float newValue)
    {
        if (effect != nullptr && isPositiveAndBelow (index, (int) effect->numParams))
        {
            try
            {
                const ScopedLock sl (lock);

                if (effect->getParameter (effect, index) != newValue)
                    effect->setParameter (effect, index, newValue);
            }
            catch (...)
            {
            }
        }
    }

    const String getParameterName (int index)       { return getTextForOpcode (index, effGetParamName); }
    const String getParameterText (int index)       { return getTextForOpcode (index, effGetParamDisplay); }
    String getParameterLabel (int index) const      { return getTextForOpcode (index, effGetParamLabel); }

    bool isParameterAutomatable (int index) const
    {
        if (effect != nullptr)
        {
            jassert (index >= 0 && index < effect->numParams);
            return dispatch (effCanBeAutomated, index, 0, 0, 0) != 0;
        }

        return false;
    }

    //==============================================================================
    int getNumPrograms()          { return effect != nullptr ? effect->numPrograms : 0; }
    int getCurrentProgram()       { return (int) dispatch (effGetProgram, 0, 0, 0, 0); }

    void setCurrentProgram (int newIndex)
    {
        if (getNumPrograms() > 0 && newIndex != getCurrentProgram())
            dispatch (effSetProgram, 0, jlimit (0, getNumPrograms() - 1, newIndex), 0, 0);
    }

    const String getProgramName (int index)
    {
        if (index == getCurrentProgram())
            return getCurrentProgramName();

        if (effect != nullptr)
        {
            char nm [256] = { 0 };

            if (dispatch (effGetProgramNameIndexed,
                          jlimit (0, getNumPrograms(), index),
                          -1, nm, 0) != 0)
            {
                return String (CharPointer_UTF8 (nm)).trim();
            }
        }

        return programNames [index];
    }

    void changeProgramName (int index, const String& newName)
    {
        if (index == getCurrentProgram())
        {
            if (getNumPrograms() > 0 && newName != getCurrentProgramName())
                dispatch (effSetProgramName, 0, 0, (void*) newName.substring (0, 24).toUTF8().getAddress(), 0.0f);
        }
        else
        {
            jassertfalse; // xxx not implemented!
        }
    }

    //==============================================================================
    void getStateInformation (MemoryBlock& mb)                  { saveToFXBFile (mb, true); }
    void getCurrentProgramStateInformation (MemoryBlock& mb)    { saveToFXBFile (mb, false); }

    void setStateInformation (const void* data, int size)               { loadFromFXBFile (data, size); }
    void setCurrentProgramStateInformation (const void* data, int size) { loadFromFXBFile (data, size); }

    //==============================================================================
    void timerCallback()
    {
        if (dispatch (effIdle, 0, 0, 0, 0) == 0)
            stopTimer();
    }

    void handleAsyncUpdate()
    {
        // indicates that something about the plugin has changed..
        updateHostDisplay();
    }

    VstIntPtr handleCallback (VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt)
    {
        switch (opcode)
        {
            case audioMasterAutomate:           sendParamChangeMessageToListeners (index, opt); break;
            case audioMasterProcessEvents:      handleMidiFromPlugin ((const VstEvents*) ptr); break;

           #if JUCE_MSVC
            #pragma warning (push)
            #pragma warning (disable: 4311)
           #endif
            case audioMasterGetTime:            return (VstIntPtr) &vstHostTime;
           #if JUCE_MSVC
            #pragma warning (pop)
           #endif

            case audioMasterIdle:
                if (insideVSTCallback == 0 && MessageManager::getInstance()->isThisTheMessageThread())
                {
                    const IdleCallRecursionPreventer icrp;

                   #if JUCE_MAC
                    if (getActiveEditor() != nullptr)
                        dispatch (effEditIdle, 0, 0, 0, 0);
                   #endif

                    Timer::callPendingTimersSynchronously();

                    handleUpdateNowIfNeeded();

                    for (int i = ComponentPeer::getNumPeers(); --i >= 0;)
                        ComponentPeer::getPeer(i)->performAnyPendingRepaintsNow();
                }
                break;

            case audioMasterSizeWindow:
                if (AudioProcessorEditor* ed = getActiveEditor())
                    ed->setSize (index, (int) value);

                return 1;

            case audioMasterUpdateDisplay:      triggerAsyncUpdate(); break;
            case audioMasterIOChanged:          setLatencySamples (effect->initialDelay); break;
            case audioMasterNeedIdle:           startTimer (50); break;

            case audioMasterGetSampleRate:      return (VstIntPtr) (getSampleRate() > 0 ? getSampleRate() : defaultVSTSampleRateValue);
            case audioMasterGetBlockSize:       return (VstIntPtr) (getBlockSize() > 0  ? getBlockSize()  : defaultVSTBlockSizeValue);
            case audioMasterWantMidi:           wantsMidiMessages = true; break;
            case audioMasterGetDirectory:       return getVstDirectory();

            case audioMasterTempoAt:
                if (extraFunctions != nullptr)
                    return (VstIntPtr) extraFunctions->getTempoAt ((int64) value);

                break;

            case audioMasterGetAutomationState:
                if (extraFunctions != nullptr)
                    return (VstIntPtr) extraFunctions->getAutomationState();

                break;

            case audioMasterPinConnected:
                return isValidChannel (index, value == 0) ? 0 : 1; // (yes, 0 = true)

            case audioMasterGetCurrentProcessLevel:
                return isNonRealtime() ? 4 : 0;

            // none of these are handled (yet)..
            case audioMasterBeginEdit:
            case audioMasterEndEdit:
            case audioMasterSetTime:
            case audioMasterGetParameterQuantization:
            case audioMasterGetInputLatency:
            case audioMasterGetOutputLatency:
            case audioMasterGetPreviousPlug:
            case audioMasterGetNextPlug:
            case audioMasterWillReplaceOrAccumulate:
            case audioMasterOfflineStart:
            case audioMasterOfflineRead:
            case audioMasterOfflineWrite:
            case audioMasterOfflineGetCurrentPass:
            case audioMasterOfflineGetCurrentMetaPass:
            case audioMasterVendorSpecific:
            case audioMasterSetIcon:
            case audioMasterGetLanguage:
            case audioMasterOpenWindow:
            case audioMasterCloseWindow:
                break;

            default:
                return handleGeneralCallback (opcode, index, value, ptr, opt);
        }

        return 0;
    }

    // handles non plugin-specific callbacks..
    static VstIntPtr handleGeneralCallback (VstInt32 opcode, VstInt32 /*index*/, VstIntPtr /*value*/, void *ptr, float /*opt*/)
    {
        switch (opcode)
        {
            case audioMasterCanDo:
            {
                static const char* canDos[] = { "supplyIdle",
                                                "sendVstEvents",
                                                "sendVstMidiEvent",
                                                "sendVstTimeInfo",
                                                "receiveVstEvents",
                                                "receiveVstMidiEvent",
                                                "supportShell",
                                                "shellCategory" };

                for (int i = 0; i < numElementsInArray (canDos); ++i)
                    if (strcmp (canDos[i], (const char*) ptr) == 0)
                        return 1;

                return 0;
            }

            case audioMasterVersion:                        return 2400;
            case audioMasterCurrentId:                      return shellUIDToCreate;
            case audioMasterGetNumAutomatableParameters:    return 0;
            case audioMasterGetAutomationState:             return 1;
            case audioMasterGetVendorVersion:               return 0x0101;

            case audioMasterGetVendorString:
            case audioMasterGetProductString:
            {
                String hostName ("Juce VST Host");

                if (JUCEApplication* app = JUCEApplication::getInstance())
                    hostName = app->getApplicationName();

                hostName.copyToUTF8 ((char*) ptr, (size_t) jmin (kVstMaxVendorStrLen, kVstMaxProductStrLen) - 1);
                break;
            }

            case audioMasterGetSampleRate:          return (VstIntPtr) defaultVSTSampleRateValue;
            case audioMasterGetBlockSize:           return (VstIntPtr) defaultVSTBlockSizeValue;
            case audioMasterSetOutputSampleRate:    return 0;

            default:
                DBG ("*** Unhandled VST Callback: " + String ((int) opcode));
                break;
        }

        return 0;
    }

    //==============================================================================
    VstIntPtr dispatch (const int opcode, const int index, const int value, void* const ptr, float opt) const
    {
        VstIntPtr result = 0;

        if (effect != nullptr)
        {
            const ScopedLock sl (lock);
            const IdleCallRecursionPreventer icrp;

            try
            {
               #if JUCE_MAC
                const ResFileRefNum oldResFile = CurResFile();

                if (module->resFileId != 0)
                    UseResFile (module->resFileId);
               #endif

                result = effect->dispatcher (effect, opcode, index, value, ptr, opt);

               #if JUCE_MAC
                const ResFileRefNum newResFile = CurResFile();
                if (newResFile != oldResFile)  // avoid confusing the parent app's resource file with the plug-in's
                {
                    module->resFileId = newResFile;
                    UseResFile (oldResFile);
                }
               #endif
            }
            catch (...)
            {}
        }

        return result;
    }

    bool loadFromFXBFile (const void* const data, const size_t dataSize)
    {
        if (dataSize < 28)
            return false;

        const fxSet* const set = (const fxSet*) data;

        if ((vst_swap (set->chunkMagic) != 'CcnK' && vst_swap (set->chunkMagic) != 'KncC')
             || vst_swap (set->version) > fxbVersionNum)
            return false;

        if (vst_swap (set->fxMagic) == 'FxBk')
        {
            // bank of programs
            if (vst_swap (set->numPrograms) >= 0)
            {
                const int oldProg = getCurrentProgram();
                const int numParams = vst_swap (((const fxProgram*) (set->programs))->numParams);
                const int progLen = sizeof (fxProgram) + (numParams - 1) * sizeof (float);

                for (int i = 0; i < vst_swap (set->numPrograms); ++i)
                {
                    if (i != oldProg)
                    {
                        const fxProgram* const prog = (const fxProgram*) (((const char*) (set->programs)) + i * progLen);
                        if (((const char*) prog) - ((const char*) set) >= (ssize_t) dataSize)
                            return false;

                        if (vst_swap (set->numPrograms) > 0)
                            setCurrentProgram (i);

                        if (! restoreProgramSettings (prog))
                            return false;
                    }
                }

                if (vst_swap (set->numPrograms) > 0)
                    setCurrentProgram (oldProg);

                const fxProgram* const prog = (const fxProgram*) (((const char*) (set->programs)) + oldProg * progLen);
                if (((const char*) prog) - ((const char*) set) >= (ssize_t) dataSize)
                    return false;

                if (! restoreProgramSettings (prog))
                    return false;
            }
        }
        else if (vst_swap (set->fxMagic) == 'FxCk')
        {
            // single program
            const fxProgram* const prog = (const fxProgram*) data;

            if (vst_swap (prog->chunkMagic) != 'CcnK')
                return false;

            changeProgramName (getCurrentProgram(), prog->prgName);

            for (int i = 0; i < vst_swap (prog->numParams); ++i)
                setParameter (i, vst_swapFloat (prog->params[i]));
        }
        else if (vst_swap (set->fxMagic) == 'FBCh' || vst_swap (set->fxMagic) == 'hCBF')
        {
            // non-preset chunk
            const fxChunkSet* const cset = (const fxChunkSet*) data;

            if (vst_swap (cset->chunkSize) + sizeof (fxChunkSet) - 8 > (unsigned int) dataSize)
                return false;

            setChunkData (cset->chunk, vst_swap (cset->chunkSize), false);
        }
        else if (vst_swap (set->fxMagic) == 'FPCh' || vst_swap (set->fxMagic) == 'hCPF')
        {
            // preset chunk
            const fxProgramSet* const cset = (const fxProgramSet*) data;

            if (vst_swap (cset->chunkSize) + sizeof (fxProgramSet) - 8 > (unsigned int) dataSize)
                return false;

            setChunkData (cset->chunk, vst_swap (cset->chunkSize), true);

            changeProgramName (getCurrentProgram(), cset->name);
        }
        else
        {
            return false;
        }

        return true;
    }

    bool saveToFXBFile (MemoryBlock& dest, bool isFXB, int maxSizeMB = 128)
    {
        const int numPrograms = getNumPrograms();
        const int numParams = getNumParameters();

        if (usesChunks())
        {
            MemoryBlock chunk;
            getChunkData (chunk, ! isFXB, maxSizeMB);

            if (isFXB)
            {
                const size_t totalLen = sizeof (fxChunkSet) + chunk.getSize() - 8;
                dest.setSize (totalLen, true);

                fxChunkSet* const set = (fxChunkSet*) dest.getData();
                set->chunkMagic = vst_swap ('CcnK');
                set->byteSize = 0;
                set->fxMagic = vst_swap ('FBCh');
                set->version = vst_swap (fxbVersionNum);
                set->fxID = vst_swap (getUID());
                set->fxVersion = vst_swap (getVersionNumber());
                set->numPrograms = vst_swap (numPrograms);
                set->chunkSize = vst_swap ((long) chunk.getSize());

                chunk.copyTo (set->chunk, 0, chunk.getSize());
            }
            else
            {
                const size_t totalLen = sizeof (fxProgramSet) + chunk.getSize() - 8;
                dest.setSize (totalLen, true);

                fxProgramSet* const set = (fxProgramSet*) dest.getData();
                set->chunkMagic = vst_swap ('CcnK');
                set->byteSize = 0;
                set->fxMagic = vst_swap ('FPCh');
                set->version = vst_swap (fxbVersionNum);
                set->fxID = vst_swap (getUID());
                set->fxVersion = vst_swap (getVersionNumber());
                set->numPrograms = vst_swap (numPrograms);
                set->chunkSize = vst_swap ((long) chunk.getSize());

                getCurrentProgramName().copyToUTF8 (set->name, sizeof (set->name) - 1);
                chunk.copyTo (set->chunk, 0, chunk.getSize());
            }
        }
        else
        {
            if (isFXB)
            {
                const int progLen = sizeof (fxProgram) + (numParams - 1) * sizeof (float);
                const int len = (sizeof (fxSet) - sizeof (fxProgram)) + progLen * jmax (1, numPrograms);
                dest.setSize (len, true);

                fxSet* const set = (fxSet*) dest.getData();
                set->chunkMagic = vst_swap ('CcnK');
                set->byteSize = 0;
                set->fxMagic = vst_swap ('FxBk');
                set->version = vst_swap (fxbVersionNum);
                set->fxID = vst_swap (getUID());
                set->fxVersion = vst_swap (getVersionNumber());
                set->numPrograms = vst_swap (numPrograms);

                const int oldProgram = getCurrentProgram();
                MemoryBlock oldSettings;
                createTempParameterStore (oldSettings);

                setParamsInProgramBlock ((fxProgram*) (((char*) (set->programs)) + oldProgram * progLen));

                for (int i = 0; i < numPrograms; ++i)
                {
                    if (i != oldProgram)
                    {
                        setCurrentProgram (i);
                        setParamsInProgramBlock ((fxProgram*) (((char*) (set->programs)) + i * progLen));
                    }
                }

                setCurrentProgram (oldProgram);
                restoreFromTempParameterStore (oldSettings);
            }
            else
            {
                const int totalLen = sizeof (fxProgram) + (numParams - 1) * sizeof (float);
                dest.setSize (totalLen, true);

                setParamsInProgramBlock ((fxProgram*) dest.getData());
            }
        }

        return true;
    }

    bool usesChunks() const noexcept        { return effect != nullptr && (effect->flags & effFlagsProgramChunks) != 0; }

    bool getChunkData (MemoryBlock& mb, bool isPreset, int maxSizeMB) const
    {
        if (usesChunks())
        {
            void* data = nullptr;
            const VstIntPtr bytes = dispatch (effGetChunk, isPreset ? 1 : 0, 0, &data, 0.0f);

            if (data != nullptr && bytes <= maxSizeMB * 1024 * 1024)
            {
                mb.setSize (bytes);
                mb.copyFrom (data, 0, bytes);

                return true;
            }
        }

        return false;
    }

    bool setChunkData (const void* data, const int size, bool isPreset)
    {
        if (size > 0 && usesChunks())
        {
            dispatch (effSetChunk, isPreset ? 1 : 0, size, (void*) data, 0.0f);

            if (! isPreset)
                updateStoredProgramNames();

            return true;
        }

        return false;
    }

    AEffect* effect;
    ModuleHandle::Ptr module;

    ScopedPointer<VSTPluginFormat::ExtraFunctions> extraFunctions;

private:
    String name;
    CriticalSection lock;
    bool wantsMidiMessages, initialised, isPowerOn;
    mutable StringArray programNames;
    AudioSampleBuffer tempBuffer;
    CriticalSection midiInLock;
    MidiBuffer incomingMidi;
    VSTMidiEventList midiEventsToSend;
    VstTimeInfo vstHostTime;

    //==============================================================================
    void setHostTimeFrameRate (long frameRateIndex, double frameRate, double currentTime) noexcept
    {
        vstHostTime.flags |= kVstSmpteValid;
        vstHostTime.smpteFrameRate  = frameRateIndex;
        vstHostTime.smpteOffset     = (long) (currentTime * 80.0 * frameRate + 0.5);
    }

    bool restoreProgramSettings (const fxProgram* const prog)
    {
        if (vst_swap (prog->chunkMagic) == 'CcnK' && vst_swap (prog->fxMagic) == 'FxCk')
        {
            changeProgramName (getCurrentProgram(), prog->prgName);

            for (int i = 0; i < vst_swap (prog->numParams); ++i)
                setParameter (i, vst_swapFloat (prog->params[i]));

            return true;
        }

        return false;
    }

    String getTextForOpcode (const int index, const AEffectOpcodes opcode) const
    {
        if (effect == nullptr)
            return String::empty;

        jassert (index >= 0 && index < effect->numParams);
        char nm [256] = { 0 };
        dispatch (opcode, index, 0, nm, 0);
        return String (CharPointer_UTF8 (nm)).trim();
    }

    String getCurrentProgramName()
    {
        String progName;

        if (effect != nullptr)
        {
            {
                char nm[256] = { 0 };
                dispatch (effGetProgramName, 0, 0, nm, 0);
                progName = String (CharPointer_UTF8 (nm)).trim();
            }

            const int index = getCurrentProgram();

            if (programNames[index].isEmpty())
            {
                while (programNames.size() < index)
                    programNames.add (String::empty);

                programNames.set (index, progName);
            }
        }

        return progName;
    }

    void setParamsInProgramBlock (fxProgram* const prog)
    {
        const int numParams = getNumParameters();

        prog->chunkMagic = vst_swap ('CcnK');
        prog->byteSize = 0;
        prog->fxMagic = vst_swap ('FxCk');
        prog->version = vst_swap (fxbVersionNum);
        prog->fxID = vst_swap (getUID());
        prog->fxVersion = vst_swap (getVersionNumber());
        prog->numParams = vst_swap (numParams);

        getCurrentProgramName().copyToUTF8 (prog->prgName, sizeof (prog->prgName) - 1);

        for (int i = 0; i < numParams; ++i)
            prog->params[i] = vst_swapFloat (getParameter (i));
    }

    void updateStoredProgramNames()
    {
        if (effect != nullptr && getNumPrograms() > 0)
        {
            char nm[256] = { 0 };

            // only do this if the plugin can't use indexed names..
            if (dispatch (effGetProgramNameIndexed, 0, -1, nm, 0) == 0)
            {
                const int oldProgram = getCurrentProgram();
                MemoryBlock oldSettings;
                createTempParameterStore (oldSettings);

                for (int i = 0; i < getNumPrograms(); ++i)
                {
                    setCurrentProgram (i);
                    getCurrentProgramName();  // (this updates the list)
                }

                setCurrentProgram (oldProgram);
                restoreFromTempParameterStore (oldSettings);
            }
        }
    }

    void handleMidiFromPlugin (const VstEvents* const events)
    {
        if (events != nullptr)
        {
            const ScopedLock sl (midiInLock);
            VSTMidiEventList::addEventsToMidiBuffer (events, incomingMidi);
        }
    }

    //==============================================================================
    void createTempParameterStore (MemoryBlock& dest)
    {
        dest.setSize (64 + 4 * getNumParameters());
        dest.fillWith (0);

        getCurrentProgramName().copyToUTF8 ((char*) dest.getData(), 63);

        float* const p = (float*) (((char*) dest.getData()) + 64);
        for (int i = 0; i < getNumParameters(); ++i)
            p[i] = getParameter(i);
    }

    void restoreFromTempParameterStore (const MemoryBlock& m)
    {
        changeProgramName (getCurrentProgram(), (const char*) m.getData());

        float* p = (float*) (((char*) m.getData()) + 64);
        for (int i = 0; i < getNumParameters(); ++i)
            setParameter (i, p[i]);
    }

    VstIntPtr getVstDirectory() const
    {
       #if JUCE_MAC
        return (VstIntPtr) (void*) &module->parentDirFSSpec;
       #else
        return (VstIntPtr) (pointer_sized_uint) module->fullParentDirectoryPathName.toUTF8().getAddress();
       #endif
    }

    //==============================================================================
    int getVersionNumber() const noexcept   { return effect != nullptr ? effect->version : 0; }

    String getVersion() const
    {
        unsigned int v = (unsigned int) dispatch (effGetVendorVersion, 0, 0, 0, 0);

        String s;

        if (v == 0 || (int) v == -1)
            v = getVersionNumber();

        if (v != 0)
        {
            int versionBits[32];
            int n = 0;

            while (v != 0)
            {
                versionBits [n++] = v % 10;
                v /= 10;
            }

            s << 'V';

            while (n > 1 && versionBits [n - 1] == 0)
                --n;

            while (n > 0)
            {
                s << versionBits [--n];

                if (n > 0)
                    s << '.';
            }
        }

        return s;
    }

    const char* getCategory() const
    {
        switch (dispatch (effGetPlugCategory, 0, 0, 0, 0))
        {
            case kPlugCategEffect:       return "Effect";
            case kPlugCategSynth:        return "Synth";
            case kPlugCategAnalysis:     return "Analysis";
            case kPlugCategMastering:    return "Mastering";
            case kPlugCategSpacializer:  return "Spacial";
            case kPlugCategRoomFx:       return "Reverb";
            case kPlugSurroundFx:        return "Surround";
            case kPlugCategRestoration:  return "Restoration";
            case kPlugCategGenerator:    return "Tone generation";
            default:                     break;
        }

        return nullptr;
    }

    void setPower (const bool on)
    {
        dispatch (effMainsChanged, 0, on ? 1 : 0, 0, 0);
        isPowerOn = on;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VSTPluginInstance)
};

//==============================================================================
static Array <VSTPluginWindow*> activeVSTWindows;

//==============================================================================
class VSTPluginWindow   : public AudioProcessorEditor,
                         #if ! JUCE_MAC
                          public ComponentMovementWatcher,
                         #endif
                          public Timer
{
public:
    //==============================================================================
    VSTPluginWindow (VSTPluginInstance& plugin_)
        : AudioProcessorEditor (&plugin_),
         #if ! JUCE_MAC
          ComponentMovementWatcher (this),
         #endif
          plugin (plugin_),
          isOpen (false),
          recursiveResize (false),
          pluginWantsKeys (false),
          pluginRefusesToResize (false),
          alreadyInside (false)
    {
       #if JUCE_WINDOWS
        sizeCheckCount = 0;
        pluginHWND = 0;
       #elif JUCE_LINUX
        pluginWindow = None;
        pluginProc = None;
       #elif JUCE_MAC && JUCE_SUPPORT_CARBON
        addAndMakeVisible (innerWrapper = new InnerWrapperComponent (*this));
       #elif JUCE_MAC
        addAndMakeVisible (innerWrapper = new NSViewComponent());
        NSView* innerView = [[NSView alloc] init];
        innerWrapper->setView (innerView);
        [innerView release];
       #endif

        activeVSTWindows.add (this);

        setSize (1, 1);
        setOpaque (true);
        setVisible (true);
    }

    ~VSTPluginWindow()
    {
        closePluginWindow();

       #if JUCE_MAC
        innerWrapper = nullptr;
       #endif

        activeVSTWindows.removeFirstMatchingValue (this);
        plugin.editorBeingDeleted (this);
    }

    //==============================================================================
   #if ! JUCE_MAC
    void componentMovedOrResized (bool /*wasMoved*/, bool /*wasResized*/)
    {
        if (recursiveResize)
            return;

        Component* const topComp = getTopLevelComponent();

        if (topComp->getPeer() != nullptr)
        {
            const Point<int> pos (topComp->getLocalPoint (this, Point<int>()));

            recursiveResize = true;

           #if JUCE_WINDOWS
            if (pluginHWND != 0)
                MoveWindow (pluginHWND, pos.getX(), pos.getY(), getWidth(), getHeight(), TRUE);
           #elif JUCE_LINUX
            if (pluginWindow != 0)
            {
                XResizeWindow (display, pluginWindow, getWidth(), getHeight());
                XMoveWindow (display, pluginWindow, pos.getX(), pos.getY());
                XMapRaised (display, pluginWindow);
            }
           #endif

            recursiveResize = false;
        }
    }

    void componentVisibilityChanged()
    {
        if (isShowing())
            openPluginWindow();
        else
            closePluginWindow();

        componentMovedOrResized (true, true);
    }

    void componentPeerChanged()
    {
        closePluginWindow();
        openPluginWindow();
    }
   #endif

   #if JUCE_MAC && ! JUCE_SUPPORT_CARBON
    void visibilityChanged()
    {
        if (isVisible())
            openPluginWindow();
        else
            closePluginWindow();
    }

    void childBoundsChanged (Component*)
    {
        if (innerWrapper != nullptr)
            setSize (innerWrapper->getWidth(),
                     innerWrapper->getHeight());
    }
   #endif

    //==============================================================================
    bool keyStateChanged (bool)                 { return pluginWantsKeys; }
    bool keyPressed (const juce::KeyPress&)     { return pluginWantsKeys; }

    //==============================================================================
   #if JUCE_MAC
    void paint (Graphics& g)
    {
        g.fillAll (Colours::black);
    }
   #else
    void paint (Graphics& g)
    {
        if (isOpen)
        {
            if (ComponentPeer* const peer = getPeer())
            {
                peer->addMaskedRegion (getScreenBounds() - peer->getScreenPosition());

               #if JUCE_LINUX
                if (pluginWindow != 0)
                {
                    const Rectangle<int> clip (g.getClipBounds());

                    XEvent ev = { 0 };
                    ev.xexpose.type = Expose;
                    ev.xexpose.display = display;
                    ev.xexpose.window = pluginWindow;
                    ev.xexpose.x = clip.getX();
                    ev.xexpose.y = clip.getY();
                    ev.xexpose.width = clip.getWidth();
                    ev.xexpose.height = clip.getHeight();

                    sendEventToChild (&ev);
                }
               #endif
            }
        }
        else
        {
            g.fillAll (Colours::black);
        }
    }
   #endif

    //==============================================================================
    void timerCallback()
    {
       #if JUCE_WINDOWS
        if (--sizeCheckCount <= 0)
        {
            sizeCheckCount = 10;

            checkPluginWindowSize();
        }
       #endif

        try
        {
            static bool reentrant = false;

            if (! reentrant)
            {
                reentrant = true;
                plugin.dispatch (effEditIdle, 0, 0, 0, 0);
                reentrant = false;
            }
        }
        catch (...)
        {}
    }

    //==============================================================================
    void mouseDown (const MouseEvent& e)
    {
       #if JUCE_LINUX
        if (pluginWindow == 0)
            return;

        toFront (true);

        XEvent ev = { 0 };
        ev.xbutton.display = display;
        ev.xbutton.type = ButtonPress;
        ev.xbutton.window = pluginWindow;
        ev.xbutton.root = RootWindow (display, DefaultScreen (display));
        ev.xbutton.time = CurrentTime;
        ev.xbutton.x = e.x;
        ev.xbutton.y = e.y;
        ev.xbutton.x_root = e.getScreenX();
        ev.xbutton.y_root = e.getScreenY();

        translateJuceToXButtonModifiers (e, ev);

        sendEventToChild (&ev);

       #elif JUCE_WINDOWS
        (void) e;

        toFront (true);
       #endif
    }

    void broughtToFront()
    {
        activeVSTWindows.removeFirstMatchingValue (this);
        activeVSTWindows.add (this);

       #if JUCE_MAC
        dispatch (effEditTop, 0, 0, 0, 0);
       #endif
    }

    //==============================================================================
private:
    VSTPluginInstance& plugin;
    bool isOpen, recursiveResize;
    bool pluginWantsKeys, pluginRefusesToResize, alreadyInside;

   #if JUCE_WINDOWS
    HWND pluginHWND;
    void* originalWndProc;
    int sizeCheckCount;
   #elif JUCE_LINUX
    Window pluginWindow;
    EventProcPtr pluginProc;
   #endif

    //==============================================================================
#if JUCE_MAC
   #if JUCE_SUPPORT_CARBON
    void openPluginWindow (WindowRef parentWindow)
    {
   #else
    void openPluginWindow()
    {
        NSView* parentWindow = (NSView*) innerWrapper->getView();
   #endif

        if (isOpen || parentWindow == 0)
            return;

        isOpen = true;

        ERect* rect = nullptr;
        dispatch (effEditGetRect, 0, 0, &rect, 0);
        dispatch (effEditOpen, 0, 0, parentWindow, 0);

        // do this before and after like in the steinberg example
        dispatch (effEditGetRect, 0, 0, &rect, 0);
        dispatch (effGetProgram, 0, 0, 0, 0); // also in steinberg code

        // Install keyboard hooks
        pluginWantsKeys = (dispatch (effKeysRequired, 0, 0, 0, 0) == 0);

        // double-check it's not too tiny
        int w = 250, h = 150;

        if (rect != nullptr)
        {
            w = rect->right - rect->left;
            h = rect->bottom - rect->top;

            if (w == 0 || h == 0)
            {
                w = 250;
                h = 150;
            }
        }

        w = jmax (w, 32);
        h = jmax (h, 32);

        setSize (w, h);

        startTimer (18 + juce::Random::getSystemRandom().nextInt (5));
        repaint();
    }

#else
    void openPluginWindow()
    {
        if (isOpen || getWindowHandle() == 0)
            return;

        JUCE_VST_LOG ("Opening VST UI: " + plugin.getName());
        isOpen = true;

        ERect* rect = nullptr;
        dispatch (effEditGetRect, 0, 0, &rect, 0);
        dispatch (effEditOpen, 0, 0, getWindowHandle(), 0);

        // do this before and after like in the steinberg example
        dispatch (effEditGetRect, 0, 0, &rect, 0);
        dispatch (effGetProgram, 0, 0, 0, 0); // also in steinberg code

        // Install keyboard hooks
        pluginWantsKeys = (dispatch (effKeysRequired, 0, 0, 0, 0) == 0);

       #if JUCE_WINDOWS
        originalWndProc = 0;
        pluginHWND = GetWindow ((HWND) getWindowHandle(), GW_CHILD);

        if (pluginHWND == 0)
        {
            isOpen = false;
            setSize (300, 150);
            return;
        }

        #pragma warning (push)
        #pragma warning (disable: 4244)

        originalWndProc = (void*) GetWindowLongPtr (pluginHWND, GWLP_WNDPROC);

        if (! pluginWantsKeys)
            SetWindowLongPtr (pluginHWND, GWLP_WNDPROC, (LONG_PTR) vstHookWndProc);

        #pragma warning (pop)

        RECT r;
        GetWindowRect (pluginHWND, &r);
        int w = r.right - r.left;
        int h = r.bottom - r.top;

        if (rect != nullptr)
        {
            const int rw = rect->right - rect->left;
            const int rh = rect->bottom - rect->top;

            if ((rw > 50 && rh > 50 && rw < 2000 && rh < 2000 && rw != w && rh != h)
                || ((w == 0 && rw > 0) || (h == 0 && rh > 0)))
            {
                // very dodgy logic to decide which size is right.
                if (abs (rw - w) > 350 || abs (rh - h) > 350)
                {
                    SetWindowPos (pluginHWND, 0,
                                  0, 0, rw, rh,
                                  SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

                    GetWindowRect (pluginHWND, &r);

                    w = r.right - r.left;
                    h = r.bottom - r.top;

                    pluginRefusesToResize = (w != rw) || (h != rh);

                    w = rw;
                    h = rh;
                }
            }
        }

       #elif JUCE_LINUX
        pluginWindow = getChildWindow ((Window) getWindowHandle());

        if (pluginWindow != 0)
            pluginProc = (EventProcPtr) getPropertyFromXWindow (pluginWindow,
                                                                XInternAtom (display, "_XEventProc", False));

        int w = 250, h = 150;

        if (rect != nullptr)
        {
            w = rect->right - rect->left;
            h = rect->bottom - rect->top;

            if (w == 0 || h == 0)
            {
                w = 250;
                h = 150;
            }
        }

        if (pluginWindow != 0)
            XMapRaised (display, pluginWindow);
       #endif

        // double-check it's not too tiny
        w = jmax (w, 32);
        h = jmax (h, 32);

        setSize (w, h);

       #if JUCE_WINDOWS
        checkPluginWindowSize();
       #endif

        startTimer (18 + juce::Random::getSystemRandom().nextInt (5));
        repaint();
    }
#endif

    //==============================================================================
    void closePluginWindow()
    {
        if (isOpen)
        {
           #if ! (JUCE_MAC && JUCE_SUPPORT_CARBON)
            JUCE_VST_LOG ("Closing VST UI: " + plugin.getName());
            isOpen = false;

            dispatch (effEditClose, 0, 0, 0, 0);
            stopTimer();

           #if JUCE_WINDOWS
            #pragma warning (push)
            #pragma warning (disable: 4244)
            if (pluginHWND != 0 && IsWindow (pluginHWND))
                SetWindowLongPtr (pluginHWND, GWLP_WNDPROC, (LONG_PTR) originalWndProc);
            #pragma warning (pop)

            pluginHWND = 0;
           #elif JUCE_LINUX
            pluginWindow = 0;
            pluginProc = 0;
           #endif
           #endif
        }
    }

    //==============================================================================
    VstIntPtr dispatch (const int opcode, const int index, const int value, void* const ptr, float opt)
    {
        return plugin.dispatch (opcode, index, value, ptr, opt);
    }

    //==============================================================================
#if JUCE_WINDOWS
    void checkPluginWindowSize()
    {
        RECT r;
        GetWindowRect (pluginHWND, &r);
        const int w = r.right - r.left;
        const int h = r.bottom - r.top;

        if (isShowing() && w > 0 && h > 0
             && (w != getWidth() || h != getHeight())
             && ! pluginRefusesToResize)
        {
            setSize (w, h);
            sizeCheckCount = 0;
        }
    }

    // hooks to get keyboard events from VST windows..
    static LRESULT CALLBACK vstHookWndProc (HWND hW, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (int i = activeVSTWindows.size(); --i >= 0;)
        {
            const VSTPluginWindow* const w = activeVSTWindows.getUnchecked (i);

            if (w->pluginHWND == hW)
            {
                if (message == WM_CHAR
                    || message == WM_KEYDOWN
                    || message == WM_SYSKEYDOWN
                    || message == WM_KEYUP
                    || message == WM_SYSKEYUP
                    || message == WM_APPCOMMAND)
                {
                    SendMessage ((HWND) w->getTopLevelComponent()->getWindowHandle(),
                                 message, wParam, lParam);
                }

                return CallWindowProc ((WNDPROC) (w->originalWndProc),
                                       (HWND) w->pluginHWND,
                                       message,
                                       wParam,
                                       lParam);
            }
        }

        return DefWindowProc (hW, message, wParam, lParam);
    }
#endif

#if JUCE_LINUX
    //==============================================================================
    // overload mouse/keyboard events to forward them to the plugin's inner window..
    void sendEventToChild (XEvent* event)
    {
        if (pluginProc != 0)
        {
            // if the plugin publishes an event procedure, pass the event directly..
            pluginProc (event);
        }
        else if (pluginWindow != 0)
        {
            // if the plugin has a window, then send the event to the window so that
            // its message thread will pick it up..
            XSendEvent (display, pluginWindow, False, 0L, event);
            XFlush (display);
        }
    }

    void mouseEnter (const MouseEvent& e)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xcrossing.display = display;
            ev.xcrossing.type = EnterNotify;
            ev.xcrossing.window = pluginWindow;
            ev.xcrossing.root = RootWindow (display, DefaultScreen (display));
            ev.xcrossing.time = CurrentTime;
            ev.xcrossing.x = e.x;
            ev.xcrossing.y = e.y;
            ev.xcrossing.x_root = e.getScreenX();
            ev.xcrossing.y_root = e.getScreenY();
            ev.xcrossing.mode = NotifyNormal; // NotifyGrab, NotifyUngrab
            ev.xcrossing.detail = NotifyAncestor; // NotifyVirtual, NotifyInferior, NotifyNonlinear,NotifyNonlinearVirtual

            translateJuceToXCrossingModifiers (e, ev);

            sendEventToChild (&ev);
        }
    }

    void mouseExit (const MouseEvent& e)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xcrossing.display = display;
            ev.xcrossing.type = LeaveNotify;
            ev.xcrossing.window = pluginWindow;
            ev.xcrossing.root = RootWindow (display, DefaultScreen (display));
            ev.xcrossing.time = CurrentTime;
            ev.xcrossing.x = e.x;
            ev.xcrossing.y = e.y;
            ev.xcrossing.x_root = e.getScreenX();
            ev.xcrossing.y_root = e.getScreenY();
            ev.xcrossing.mode = NotifyNormal; // NotifyGrab, NotifyUngrab
            ev.xcrossing.detail = NotifyAncestor; // NotifyVirtual, NotifyInferior, NotifyNonlinear,NotifyNonlinearVirtual
            ev.xcrossing.focus = hasKeyboardFocus (true); // TODO - yes ?

            translateJuceToXCrossingModifiers (e, ev);

            sendEventToChild (&ev);
        }
    }

    void mouseMove (const MouseEvent& e)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xmotion.display = display;
            ev.xmotion.type = MotionNotify;
            ev.xmotion.window = pluginWindow;
            ev.xmotion.root = RootWindow (display, DefaultScreen (display));
            ev.xmotion.time = CurrentTime;
            ev.xmotion.is_hint = NotifyNormal;
            ev.xmotion.x = e.x;
            ev.xmotion.y = e.y;
            ev.xmotion.x_root = e.getScreenX();
            ev.xmotion.y_root = e.getScreenY();

            sendEventToChild (&ev);
        }
    }

    void mouseDrag (const MouseEvent& e)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xmotion.display = display;
            ev.xmotion.type = MotionNotify;
            ev.xmotion.window = pluginWindow;
            ev.xmotion.root = RootWindow (display, DefaultScreen (display));
            ev.xmotion.time = CurrentTime;
            ev.xmotion.x = e.x ;
            ev.xmotion.y = e.y;
            ev.xmotion.x_root = e.getScreenX();
            ev.xmotion.y_root = e.getScreenY();
            ev.xmotion.is_hint = NotifyNormal;

            translateJuceToXMotionModifiers (e, ev);
            sendEventToChild (&ev);
        }
    }

    void mouseUp (const MouseEvent& e)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xbutton.display = display;
            ev.xbutton.type = ButtonRelease;
            ev.xbutton.window = pluginWindow;
            ev.xbutton.root = RootWindow (display, DefaultScreen (display));
            ev.xbutton.time = CurrentTime;
            ev.xbutton.x = e.x;
            ev.xbutton.y = e.y;
            ev.xbutton.x_root = e.getScreenX();
            ev.xbutton.y_root = e.getScreenY();

            translateJuceToXButtonModifiers (e, ev);
            sendEventToChild (&ev);
        }
    }

    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
    {
        if (pluginWindow != 0)
        {
            XEvent ev = { 0 };
            ev.xbutton.display = display;
            ev.xbutton.type = ButtonPress;
            ev.xbutton.window = pluginWindow;
            ev.xbutton.root = RootWindow (display, DefaultScreen (display));
            ev.xbutton.time = CurrentTime;
            ev.xbutton.x = e.x;
            ev.xbutton.y = e.y;
            ev.xbutton.x_root = e.getScreenX();
            ev.xbutton.y_root = e.getScreenY();

            translateJuceToXMouseWheelModifiers (e, wheel.deltaY, ev);
            sendEventToChild (&ev);

            // TODO - put a usleep here ?

            ev.xbutton.type = ButtonRelease;
            sendEventToChild (&ev);
        }
    }
#endif

    //==============================================================================
#if JUCE_MAC
   #if JUCE_SUPPORT_CARBON
    class InnerWrapperComponent   : public CarbonViewWrapperComponent
    {
    public:
        InnerWrapperComponent (VSTPluginWindow& owner_)
            : owner (owner_), alreadyInside (false)
        {
        }

        ~InnerWrapperComponent()
        {
            deleteWindow();
        }

        HIViewRef attachView (WindowRef windowRef, HIViewRef rootView)
        {
            owner.openPluginWindow (windowRef);
            return 0;
        }

        void removeView (HIViewRef)
        {
            if (owner.isOpen)
            {
                owner.isOpen = false;
                owner.dispatch (effEditClose, 0, 0, 0, 0);
                owner.dispatch (effEditSleep, 0, 0, 0, 0);
            }
        }

        bool getEmbeddedViewSize (int& w, int& h)
        {
            ERect* rect = nullptr;
            owner.dispatch (effEditGetRect, 0, 0, &rect, 0);
            w = rect->right - rect->left;
            h = rect->bottom - rect->top;
            return true;
        }

        void handleMouseDown (int x, int y)
        {
            if (! alreadyInside)
            {
                alreadyInside = true;
                getTopLevelComponent()->toFront (true);
                owner.dispatch (effEditMouse, x, y, 0, 0);
                alreadyInside = false;
            }
            else
            {
                PostEvent (::mouseDown, 0);
            }
        }

        void handlePaint()
        {
            if (ComponentPeer* const peer = getPeer())
            {
                const Point<int> pos (getScreenPosition() - peer->getScreenPosition());
                ERect r;
                r.left   = (VstInt16) pos.getX();
                r.top    = (VstInt16) pos.getY();
                r.right  = (VstInt16) (r.left + getWidth());
                r.bottom = (VstInt16) (r.top + getHeight());

                owner.dispatch (effEditDraw, 0, 0, &r, 0);
            }
        }

    private:
        VSTPluginWindow& owner;
        bool alreadyInside;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InnerWrapperComponent)
    };

    friend class InnerWrapperComponent;
    ScopedPointer <InnerWrapperComponent> innerWrapper;

   #else
    ScopedPointer <NSViewComponent> innerWrapper;
   #endif

    void resized()
    {
        if (innerWrapper != nullptr)
            innerWrapper->setSize (getWidth(), getHeight());
    }
#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VSTPluginWindow)
};

//==============================================================================
AudioProcessorEditor* VSTPluginInstance::createEditor()
{
    return hasEditor() ? new VSTPluginWindow (*this)
                       : nullptr;
}

//==============================================================================
// entry point for all callbacks from the plugin
static VstIntPtr VSTCALLBACK audioMaster (AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt)
{
    try
    {
        if (effect != nullptr)
            if (VSTPluginInstance* instance = (VSTPluginInstance*) (effect->resvd2))
                return instance->handleCallback (opcode, index, value, ptr, opt);

        return VSTPluginInstance::handleGeneralCallback (opcode, index, value, ptr, opt);
    }
    catch (...)
    {
        return 0;
    }
}

//==============================================================================
VSTPluginFormat::VSTPluginFormat() {}
VSTPluginFormat::~VSTPluginFormat() {}

void VSTPluginFormat::findAllTypesForFile (OwnedArray <PluginDescription>& results,
                                           const String& fileOrIdentifier)
{
    if (! fileMightContainThisPluginType (fileOrIdentifier))
        return;

    PluginDescription desc;
    desc.fileOrIdentifier = fileOrIdentifier;
    desc.uid = 0;

    ScopedPointer <VSTPluginInstance> instance (dynamic_cast <VSTPluginInstance*> (createInstanceFromDescription (desc)));

    if (instance == nullptr)
        return;

    try
    {
       #if JUCE_MAC
        if (instance->module->resFileId != 0)
            UseResFile (instance->module->resFileId);
       #endif

        instance->fillInPluginDescription (desc);

        VstPlugCategory category = (VstPlugCategory) instance->dispatch (effGetPlugCategory, 0, 0, 0, 0);

        if (category != kPlugCategShell)
        {
            // Normal plugin...
            results.add (new PluginDescription (desc));

            instance->dispatch (effOpen, 0, 0, 0, 0);
        }
        else
        {
            // It's a shell plugin, so iterate all the subtypes...
            for (;;)
            {
                char shellEffectName [64] = { 0 };
                const int uid = (int) instance->dispatch (effShellGetNextPlugin, 0, 0, shellEffectName, 0);

                if (uid == 0)
                    break;

                desc.uid = uid;
                desc.name = shellEffectName;
                desc.descriptiveName = shellEffectName;

                bool alreadyThere = false;

                for (int i = results.size(); --i >= 0;)
                {
                    PluginDescription* const d = results.getUnchecked(i);

                    if (d->isDuplicateOf (desc))
                    {
                        alreadyThere = true;
                        break;
                    }
                }

                if (! alreadyThere)
                    results.add (new PluginDescription (desc));
            }
        }
    }
    catch (...)
    {
        // crashed while loading...
    }
}

AudioPluginInstance* VSTPluginFormat::createInstanceFromDescription (const PluginDescription& desc)
{
    ScopedPointer <VSTPluginInstance> result;

    if (fileMightContainThisPluginType (desc.fileOrIdentifier))
    {
        File file (desc.fileOrIdentifier);

        const File previousWorkingDirectory (File::getCurrentWorkingDirectory());
        file.getParentDirectory().setAsCurrentWorkingDirectory();

        const ModuleHandle::Ptr module (ModuleHandle::findOrCreateModule (file));

        if (module != nullptr)
        {
            shellUIDToCreate = desc.uid;

            result = new VSTPluginInstance (module);

            if (result->effect != nullptr)
            {
                result->effect->resvd2 = (VstIntPtr) (pointer_sized_int) (VSTPluginInstance*) result;
                result->initialise();
            }
            else
            {
                result = nullptr;
            }
        }

        previousWorkingDirectory.setAsCurrentWorkingDirectory();
    }

    return result.release();
}

bool VSTPluginFormat::fileMightContainThisPluginType (const String& fileOrIdentifier)
{
    const File f (fileOrIdentifier);

  #if JUCE_MAC
    if (f.isDirectory() && f.hasFileExtension (".vst"))
        return true;

   #if JUCE_PPC
    FSRef fileRef;
    if (makeFSRefFromPath (&fileRef, f.getFullPathName()))
    {
        const short resFileId = FSOpenResFile (&fileRef, fsRdPerm);

        if (resFileId != -1)
        {
            const int numEffects = Count1Resources ('aEff');
            CloseResFile (resFileId);

            if (numEffects > 0)
                return true;
        }
    }
   #endif

    return false;
  #elif JUCE_WINDOWS
    return f.existsAsFile() && f.hasFileExtension (".dll");
  #elif JUCE_LINUX
    return f.existsAsFile() && f.hasFileExtension (".so");
  #endif
}

String VSTPluginFormat::getNameOfPluginFromIdentifier (const String& fileOrIdentifier)
{
    return fileOrIdentifier;
}

bool VSTPluginFormat::doesPluginStillExist (const PluginDescription& desc)
{
    return File (desc.fileOrIdentifier).exists();
}

StringArray VSTPluginFormat::searchPathsForPlugins (const FileSearchPath& directoriesToSearch, const bool recursive)
{
    StringArray results;

    for (int j = 0; j < directoriesToSearch.getNumPaths(); ++j)
        recursiveFileSearch (results, directoriesToSearch [j], recursive);

    return results;
}

void VSTPluginFormat::recursiveFileSearch (StringArray& results, const File& dir, const bool recursive)
{
    // avoid allowing the dir iterator to be recursive, because we want to avoid letting it delve inside
    // .component or .vst directories.
    DirectoryIterator iter (dir, false, "*", File::findFilesAndDirectories);

    while (iter.next())
    {
        const File f (iter.getFile());
        bool isPlugin = false;

        if (fileMightContainThisPluginType (f.getFullPathName()))
        {
            isPlugin = true;
            results.add (f.getFullPathName());
        }

        if (recursive && (! isPlugin) && f.isDirectory())
            recursiveFileSearch (results, f, true);
    }
}

FileSearchPath VSTPluginFormat::getDefaultLocationsToSearch()
{
   #if JUCE_MAC
    return FileSearchPath ("~/Library/Audio/Plug-Ins/VST;/Library/Audio/Plug-Ins/VST");
   #elif JUCE_LINUX
    return FileSearchPath ("/usr/lib/vst");
   #elif JUCE_WINDOWS
    const String programFiles (File::getSpecialLocation (File::globalApplicationsDirectory).getFullPathName());

    FileSearchPath paths;
    paths.add (WindowsRegistry::getValue ("HKLM\\Software\\VST\\VSTPluginsPath",
                                          programFiles + "\\Steinberg\\VstPlugins"));
    paths.removeNonExistentPaths();

    paths.add (WindowsRegistry::getValue ("HKLM\\Software\\VST\\VSTPluginsPath",
                                          programFiles + "\\VstPlugins"));
    return paths;
   #endif
}

const XmlElement* VSTPluginFormat::getVSTXML (AudioPluginInstance* plugin)
{
    if (VSTPluginInstance* const vst = dynamic_cast <VSTPluginInstance*> (plugin))
        if (vst->module != nullptr)
            return vst->module->vstXml.get();

    return nullptr;
}

bool VSTPluginFormat::loadFromFXBFile (AudioPluginInstance* plugin, const void* data, size_t dataSize)
{
    if (VSTPluginInstance* vst = dynamic_cast <VSTPluginInstance*> (plugin))
        return vst->loadFromFXBFile (data, dataSize);

    return false;
}

bool VSTPluginFormat::saveToFXBFile (AudioPluginInstance* plugin, MemoryBlock& dest, bool asFXB)
{
    if (VSTPluginInstance* vst = dynamic_cast <VSTPluginInstance*> (plugin))
        return vst->saveToFXBFile (dest, asFXB);

    return false;
}

bool VSTPluginFormat::getChunkData (AudioPluginInstance* plugin, MemoryBlock& result, bool isPreset)
{
    if (VSTPluginInstance* vst = dynamic_cast <VSTPluginInstance*> (plugin))
        return vst->getChunkData (result, isPreset, 128);

    return false;
}

bool VSTPluginFormat::setChunkData (AudioPluginInstance* plugin, const void* data, int size, bool isPreset)
{
    if (VSTPluginInstance* vst = dynamic_cast <VSTPluginInstance*> (plugin))
        return vst->setChunkData (data, size, isPreset);

    return false;
}

void VSTPluginFormat::setExtraFunctions (AudioPluginInstance* plugin, ExtraFunctions* functions)
{
    ScopedPointer<ExtraFunctions> f (functions);

    if (VSTPluginInstance* vst = dynamic_cast <VSTPluginInstance*> (plugin))
        vst->extraFunctions = f;
}

#endif
