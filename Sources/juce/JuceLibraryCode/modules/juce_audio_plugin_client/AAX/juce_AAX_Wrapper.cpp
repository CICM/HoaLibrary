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

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "../utility/juce_CheckSettingMacros.h"

#if JucePlugin_Build_AAX && (JUCE_INCLUDED_AAX_IN_MM || defined (_WIN32) || defined (_WIN64))

#ifdef _MSC_VER
 #include <windows.h>
#else
 #include <Cocoa/Cocoa.h>
#endif

#include "../utility/juce_IncludeModuleHeaders.h"
#undef Component

#ifdef __clang__
 #pragma clang diagnostic push
 #pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#include "AAX_Exports.cpp"
#include "AAX_ICollection.h"
#include "AAX_IComponentDescriptor.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_CEffectParameters.h"
#include "AAX_Errors.h"
#include "AAX_CBinaryTaperDelegate.h"
#include "AAX_CBinaryDisplayDelegate.h"
#include "AAX_CLinearTaperDelegate.h"
#include "AAX_CNumberDisplayDelegate.h"
#include "AAX_CEffectGUI.h"
#include "AAX_IViewContainer.h"
#include "AAX_ITransport.h"
#include "AAX_IMIDINode.h"
#include "AAX_UtilsNative.h"

#ifdef __clang__
 #pragma clang diagnostic pop
#endif

#if JUCE_WINDOWS
 #ifndef JucePlugin_AAXLibs_path
  #error "You need to define the JucePlugin_AAXLibs_path macro. (This is best done via the introjucer)"
 #endif

 #if JUCE_64BIT
  #define JUCE_AAX_LIB "AAXLibrary_x64"
 #else
  #define JUCE_AAX_LIB "AAXLibrary"
 #endif

 #if JUCE_DEBUG
  #define JUCE_AAX_LIB_PATH   "\\Debug\\"
  #define JUCE_AAX_LIB_SUFFIX "_D"
 #else
  #define JUCE_AAX_LIB_PATH   "\\Release\\"
  #define JUCE_AAX_LIB_SUFFIX ""
 #endif

 #pragma comment(lib, JucePlugin_AAXLibs_path JUCE_AAX_LIB_PATH JUCE_AAX_LIB JUCE_AAX_LIB_SUFFIX ".lib")
#endif

using juce::Component;

const int32_t juceChunkType = 'juce';

//==============================================================================
struct AAXClasses
{
    static void check (AAX_Result result)
    {
        jassert (result == AAX_SUCCESS); (void) result;
    }

    static AAX_EStemFormat getFormatForChans (const int numChans) noexcept
    {
        switch (numChans)
        {
            case 0:   return AAX_eStemFormat_None;
            case 1:   return AAX_eStemFormat_Mono;
            case 2:   return AAX_eStemFormat_Stereo;
            case 3:   return AAX_eStemFormat_LCR;
            case 4:   return AAX_eStemFormat_Quad;
            case 5:   return AAX_eStemFormat_5_0;
            case 6:   return AAX_eStemFormat_5_1;
            case 7:   return AAX_eStemFormat_6_1;
            case 8:   return AAX_eStemFormat_7_1_DTS;

            default:  jassertfalse; break; // hmm - not a valid number of chans..
        }

        return AAX_eStemFormat_None;
    }

    static int getNumChannelsForStemFormat (AAX_EStemFormat format) noexcept
    {
        switch (format)
        {
            case AAX_eStemFormat_None:      return 0;
            case AAX_eStemFormat_Mono:      return 1;
            case AAX_eStemFormat_Stereo:    return 2;
            case AAX_eStemFormat_LCR:       return 3;
            case AAX_eStemFormat_Quad:      return 4;
            case AAX_eStemFormat_5_0:       return 5;
            case AAX_eStemFormat_5_1:       return 6;
            case AAX_eStemFormat_6_1:       return 7;
            case AAX_eStemFormat_7_1_DTS:   return 8;
            default:  jassertfalse; break; // hmm - not a valid number of chans..
        }

        return 0;
    }

    //==============================================================================
    struct JUCELibraryRefCount
    {
        JUCELibraryRefCount()    { if (getCount()++ == 0) initialise(); }
        ~JUCELibraryRefCount()   { if (--getCount() == 0) shutdown(); }

    private:
        static void initialise()
        {
            initialiseJuce_GUI();
        }

        static void shutdown()
        {
            shutdownJuce_GUI();
        }

        int& getCount() noexcept
        {
            static int count = 0;
            return count;
        }
    };

    //==============================================================================
    class JuceAAX_Processor;

    struct PluginInstanceInfo
    {
        PluginInstanceInfo (JuceAAX_Processor& p)  : parameters (p) {}

        JuceAAX_Processor& parameters;

        JUCE_DECLARE_NON_COPYABLE (PluginInstanceInfo)
    };

    //==============================================================================
    struct JUCEAlgorithmContext
    {
        float** inputChannels;
        float** outputChannels;
        int32_t* bufferSize;
        int32_t* bypass;
        AAX_IMIDINode* midiNodeIn;
        AAX_IMIDINode* midiNodeOut;

        PluginInstanceInfo* pluginInstance;
        int32_t* isPrepared;
    };

    struct JUCEAlgorithmIDs
    {
        enum
        {
            inputChannels   = AAX_FIELD_INDEX (JUCEAlgorithmContext, inputChannels),
            outputChannels  = AAX_FIELD_INDEX (JUCEAlgorithmContext, outputChannels),
            bufferSize      = AAX_FIELD_INDEX (JUCEAlgorithmContext, bufferSize),
            bypass          = AAX_FIELD_INDEX (JUCEAlgorithmContext, bypass),
            midiNodeIn      = AAX_FIELD_INDEX (JUCEAlgorithmContext, midiNodeIn),
            midiNodeOut     = AAX_FIELD_INDEX (JUCEAlgorithmContext, midiNodeOut),
            pluginInstance  = AAX_FIELD_INDEX (JUCEAlgorithmContext, pluginInstance),
            preparedFlag    = AAX_FIELD_INDEX (JUCEAlgorithmContext, isPrepared)
        };
    };

    //==============================================================================
    class JuceAAX_GUI   : public AAX_CEffectGUI
    {
    public:
        JuceAAX_GUI() {}
        virtual ~JuceAAX_GUI()  { DeleteViewContainer(); }

        static AAX_IEffectGUI* AAX_CALLBACK Create()   { return new JuceAAX_GUI(); }

        void CreateViewContents()
        {
            if (component == nullptr)
            {
                if (JuceAAX_Processor* params = dynamic_cast <JuceAAX_Processor*> (GetEffectParameters()))
                    component = new ContentWrapperComponent (*this, params->getPluginInstance());
                else
                    jassertfalse;
            }
        }

        void CreateViewContainer()
        {
            CreateViewContents();

            if (void* nativeViewToAttachTo = GetViewContainerPtr())
            {
               #if JUCE_MAC
                if (GetViewContainerType() == AAX_eViewContainer_Type_NSView)
               #else
                if (GetViewContainerType() == AAX_eViewContainer_Type_HWND)
               #endif
                {
                    component->setVisible (true);
                    component->addToDesktop (0, nativeViewToAttachTo);
                }
            }
        }

        void DeleteViewContainer()
        {
            if (component != nullptr)
            {
                JUCE_AUTORELEASEPOOL
                component->removeFromDesktop();
                component = nullptr;
            }
        }

        virtual AAX_Result GetViewSize (AAX_Point* viewSize) const
        {
            if (component != nullptr)
            {
                viewSize->horz = (float) component->getWidth();
                viewSize->vert = (float) component->getHeight();
                return AAX_SUCCESS;
            }

            return AAX_ERROR_NULL_OBJECT;
        }

        AAX_Result ParameterUpdated (AAX_CParamID /*paramID*/)
        {
            return AAX_SUCCESS;
        }

        AAX_Result SetControlHighlightInfo (AAX_CParamID /*paramID*/, AAX_CBoolean /*isHighlighted*/, AAX_EHighlightColor)
        {
            return AAX_SUCCESS;
        }

    private:
        class ContentWrapperComponent  : public juce::Component
        {
        public:
            ContentWrapperComponent (JuceAAX_GUI& gui, AudioProcessor& plugin)
                : owner (gui)
            {
                setOpaque (true);
                addAndMakeVisible (pluginEditor = plugin.createEditorIfNeeded());
                setBounds (pluginEditor->getLocalBounds());
                setBroughtToFrontOnMouseClick (true);
            }

            ~ContentWrapperComponent()
            {
                if (pluginEditor != nullptr)
                {
                    PopupMenu::dismissAllActiveMenus();
                    pluginEditor->getAudioProcessor()->editorBeingDeleted (pluginEditor);
                }
            }

            void paint (Graphics& g)
            {
                g.fillAll (Colours::black);
            }

            void childBoundsChanged (Component*)
            {
                if (pluginEditor != nullptr)
                {
                    const int w = pluginEditor->getWidth();
                    const int h = pluginEditor->getHeight();
                    setSize (w, h);

                    AAX_Point newSize ((float) h, (float) w);
                    owner.GetViewContainer()->SetViewSize (newSize);
                }
            }

        private:
            ScopedPointer<AudioProcessorEditor> pluginEditor;
            JuceAAX_GUI& owner;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContentWrapperComponent)
        };

        ScopedPointer<ContentWrapperComponent> component;

        JUCELibraryRefCount juceCount;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceAAX_GUI)
    };

    //==============================================================================
    class JuceAAX_Processor   : public AAX_CEffectParameters,
                                public juce::AudioPlayHead,
                                public AudioProcessorListener
    {
    public:
        JuceAAX_Processor()
        {
            pluginInstance = createPluginFilterOfType (AudioProcessor::wrapperType_AAX);
            pluginInstance->setPlayHead (this);
            pluginInstance->addListener (this);

            AAX_CEffectParameters::GetNumberOfChunks (&juceChunkIndex);
        }

        static AAX_CEffectParameters* AAX_CALLBACK Create()   { return new JuceAAX_Processor(); }

        AAX_Result EffectInit()
        {
            addBypassParameter();
            addAudioProcessorParameters();
            preparePlugin();

            return AAX_SUCCESS;
        }

        AAX_Result GetNumberOfChunks (int32_t* numChunks) const
        {
            // The juceChunk is the last chunk.
            *numChunks = juceChunkIndex + 1;
            return AAX_SUCCESS;
        }

        AAX_Result GetChunkIDFromIndex (int32_t index, AAX_CTypeID* chunkID) const
        {
            if (index != juceChunkIndex)
                return AAX_CEffectParameters::GetChunkIDFromIndex (index, chunkID);

            *chunkID = juceChunkType;
            return AAX_SUCCESS;
        }

        AAX_Result GetChunkSize (AAX_CTypeID chunkID, uint32_t* oSize) const
        {
            if (chunkID != juceChunkType)
                return AAX_CEffectParameters::GetChunkSize (chunkID, oSize);

            tempFilterData.setSize (0);
            pluginInstance->getStateInformation (tempFilterData);
            *oSize = (uint32_t) tempFilterData.getSize();
            return AAX_SUCCESS;
        }

        AAX_Result GetChunk (AAX_CTypeID chunkID, AAX_SPlugInChunk* oChunk) const
        {
            if (chunkID != juceChunkType)
                return AAX_CEffectParameters::GetChunk (chunkID, oChunk);

            if (tempFilterData.getSize() == 0)
                pluginInstance->getStateInformation (tempFilterData);

            oChunk->fSize = (uint32_t) tempFilterData.getSize();
            tempFilterData.copyTo (oChunk->fData, 0, tempFilterData.getSize());
            tempFilterData.setSize (0);

            return AAX_SUCCESS;
        }

        AAX_Result SetChunk (AAX_CTypeID chunkID, const AAX_SPlugInChunk* chunk)
        {
            if (chunkID != juceChunkType)
                return AAX_CEffectParameters::SetChunk (chunkID, chunk);

            pluginInstance->setStateInformation ((void*) chunk->fData, chunk->fSize);
            return AAX_SUCCESS;
        }

        AAX_Result ResetFieldData (AAX_CFieldIndex fieldIndex, void* data, uint32_t dataSize) const
        {
            switch (fieldIndex)
            {
                case JUCEAlgorithmIDs::pluginInstance:
                {
                    const size_t numObjects = dataSize / sizeof (PluginInstanceInfo);
                    PluginInstanceInfo* const objects = static_cast <PluginInstanceInfo*> (data);

                    jassert (numObjects == 1); // not sure how to handle more than one..

                    for (size_t i = 0; i < numObjects; ++i)
                        new (objects + i) PluginInstanceInfo (const_cast<JuceAAX_Processor&> (*this));

                    break;
                }

                case JUCEAlgorithmIDs::preparedFlag:
                {
                    const_cast<JuceAAX_Processor*>(this)->preparePlugin();

                    const size_t numObjects = dataSize / sizeof (uint32_t);
                    uint32_t* const objects = static_cast <uint32_t*> (data);

                    for (size_t i = 0; i < numObjects; ++i)
                        new (objects + i) uint32_t (1);

                    break;
                }
            }

            return AAX_SUCCESS;
            //return AAX_ERROR_INVALID_FIELD_INDEX;
        }

        AAX_Result UpdateParameterNormalizedValue (AAX_CParamID paramID, double value, AAX_EUpdateSource source)
        {
            AAX_Result result = AAX_CEffectParameters::UpdateParameterNormalizedValue (paramID, value, source);

            if (AAX::IsParameterIDEqual (paramID, cDefaultMasterBypassID) == false)
            {
                const int parameterIndex = atoi (paramID);
                pluginInstance->setParameter (parameterIndex, (float) value);
            }

            return result;
        }

        AudioProcessor& getPluginInstance() const noexcept   { return *pluginInstance; }

        bool getCurrentPosition (juce::AudioPlayHead::CurrentPositionInfo& info)
        {
            const AAX_ITransport& transport = *Transport();
            check (transport.GetCurrentTempo (&info.bpm));

            int32_t num, denom;
            transport.GetCurrentMeter (&num, &denom);
            info.timeSigNumerator = num;
            info.timeSigDenominator = denom;

            check (transport.GetCurrentNativeSampleLocation (&info.timeInSamples));
            info.timeInSeconds = info.timeInSamples / getSampleRate();

            int64_t ticks;
            check (transport.GetCurrentTickPosition (&ticks));
            info.ppqPosition = ticks / 960000.0;

            int64_t loopStartTick, loopEndTick;
            check (transport.GetCurrentLoopPosition (&info.isLooping, &loopStartTick, &loopEndTick));
            info.ppqLoopStart = loopStartTick / 960000.0;
            info.ppqLoopEnd   = loopEndTick   / 960000.0;

            // No way to get these: (?)
            info.isRecording = false;
            info.ppqPositionOfLastBarStart = 0;
            info.editOriginTime = 0;

            return true;
        }

        void audioProcessorParameterChanged (AudioProcessor* /*processor*/, int parameterIndex, float newValue)
        {
            SetParameterNormalizedValue (IndexAsParamID (parameterIndex), (double) newValue);
        }

        void audioProcessorChanged (AudioProcessor* /*processor*/)
        {
            // TODO
        }

        void audioProcessorParameterChangeGestureBegin (AudioProcessor* /*processor*/, int parameterIndex)
        {
            TouchParameter (IndexAsParamID (parameterIndex));
        }

        void audioProcessorParameterChangeGestureEnd (AudioProcessor* /*processor*/, int parameterIndex)
        {
            ReleaseParameter (IndexAsParamID (parameterIndex));
        }

        void process (const float* const* inputs, float* const* outputs, const int bufferSize,
                      const bool bypass, AAX_IMIDINode* midiNodeIn, AAX_IMIDINode* midiNodeOut)
        {
            const int numIns  = pluginInstance->getNumInputChannels();
            const int numOuts = pluginInstance->getNumOutputChannels();

            if (numOuts >= numIns)
            {
                for (int i = 0; i < numIns; ++i)
                    memcpy (outputs[i], inputs[i], bufferSize * sizeof (float));

                process (outputs, numOuts, bufferSize, bypass, midiNodeIn, midiNodeOut);
            }
            else
            {
                if (channelList.size() <= numIns)
                    channelList.insertMultiple (-1, nullptr, 1 + numIns - channelList.size());

                float** channels = channelList.getRawDataPointer();

                for (int i = 0; i < numOuts; ++i)
                {
                    memcpy (outputs[i], inputs[i], bufferSize * sizeof (float));
                    channels[i] = outputs[i];
                }

                for (int i = numOuts; i < numIns; ++i)
                    channels[i] = const_cast <float*> (inputs[i]);

                process (channels, numIns, bufferSize, bypass, midiNodeIn, midiNodeOut);
            }
        }

    private:
        struct IndexAsParamID
        {
            inline explicit IndexAsParamID (int i) noexcept : index (i) {}

            operator AAX_CParamID() noexcept
            {
                jassert (index >= 0);

                char* t = name + sizeof (name);
                *--t = 0;
                int v = index;

                do
                {
                    *--t = (char) ('0' + (v % 10));
                    v /= 10;

                } while (v > 0);

                return static_cast <AAX_CParamID> (t);
            }

        private:
            int index;
            char name[32];

            JUCE_DECLARE_NON_COPYABLE (IndexAsParamID)
        };

        void process (float* const* channels, const int numChans, const int bufferSize,
                      const bool bypass, AAX_IMIDINode* midiNodeIn, AAX_IMIDINode* midiNodeOut)
        {
            AudioSampleBuffer buffer (channels, numChans, bufferSize);

            midiBuffer.clear();

           #if JucePlugin_WantsMidiInput
            {
                AAX_CMidiStream* const midiStream = midiNodeIn->GetNodeBuffer();
                const uint32_t numMidiEvents = midiStream->mBufferSize;

                for (uint32_t i = 0; i < numMidiEvents; ++i)
                {
                    // (This 8-byte alignment is a workaround to a bug in the AAX SDK. Hopefully can be
                    // removed in future when the packet structure size is fixed)
                    const AAX_CMidiPacket& m = *addBytesToPointer (midiStream->mBuffer,
                                                                   i * ((sizeof (AAX_CMidiPacket) + 7) & ~7));
                    jassert ((int) m.mTimestamp < bufferSize);
                    midiBuffer.addEvent (m.mData, (int) m.mLength,
                                         jlimit (0, (int) bufferSize - 1, (int) m.mTimestamp));
                }
            }
           #endif

            {
                const ScopedLock sl (pluginInstance->getCallbackLock());

                if (bypass)
                    pluginInstance->processBlockBypassed (buffer, midiBuffer);
                else
                    pluginInstance->processBlock (buffer, midiBuffer);
            }

           #if JucePlugin_ProducesMidiOutput
            {
                const juce::uint8* midiEventData;
                int midiEventSize, midiEventPosition;
                MidiBuffer::Iterator i (midiBuffer);

                AAX_CMidiPacket packet;
                packet.mIsImmediate = false;

                while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
                {
                    jassert (isPositiveAndBelow (midiEventPosition, bufferSize));

                    if (midiEventSize <= 4)
                    {
                        packet.mTimestamp   = (uint32_t) midiEventPosition;
                        packet.mLength      = (uint32_t) midiEventSize;
                        memcpy (packet.mData, midiEventData, midiEventSize);

                        check (midiNodeOut->PostMIDIPacket (&packet));
                    }
                }
            }
           #endif
        }

        void addBypassParameter()
        {
            AAX_IParameter* masterBypass = new AAX_CParameter<bool> (cDefaultMasterBypassID,
                                                                     AAX_CString ("Master Bypass"),
                                                                     false,
                                                                     AAX_CBinaryTaperDelegate<bool>(),
                                                                     AAX_CBinaryDisplayDelegate<bool> ("bypass", "on"),
                                                                     true);
            masterBypass->SetNumberOfSteps (2);
            masterBypass->SetType (AAX_eParameterType_Discrete);
            mParameterManager.AddParameter (masterBypass);
            mPacketDispatcher.RegisterPacket (cDefaultMasterBypassID, JUCEAlgorithmIDs::bypass);
        }

        void addAudioProcessorParameters()
        {
            AudioProcessor& audioProcessor = getPluginInstance();
            const int numParameters = audioProcessor.getNumParameters();

            for (int parameterIndex = 0; parameterIndex < numParameters; ++parameterIndex)
            {
                if (audioProcessor.isParameterAutomatable (parameterIndex))
                {
                    AAX_IParameter* parameter
                        = new AAX_CParameter<float> (IndexAsParamID (parameterIndex),
                                                     audioProcessor.getParameterName (parameterIndex).toUTF8().getAddress(),
                                                     audioProcessor.getParameter (parameterIndex),
                                                     AAX_CLinearTaperDelegate<float, 0>(),
                                                     AAX_CNumberDisplayDelegate<float, 3>(),
                                                     true);

                    parameter->SetNumberOfSteps (0x7fffffff);
                    parameter->SetType (AAX_eParameterType_Continuous);
                    mParameterManager.AddParameter (parameter);
                }
            }
        }

        void preparePlugin()
        {
            AAX_EStemFormat inputStemFormat = AAX_eStemFormat_None;
            check (Controller()->GetInputStemFormat (&inputStemFormat));
            const int numberOfInputChannels = getNumChannelsForStemFormat (inputStemFormat);

            AAX_EStemFormat outputStemFormat = AAX_eStemFormat_None;
            check (Controller()->GetOutputStemFormat (&outputStemFormat));
            const int numberOfOutputChannels = getNumChannelsForStemFormat (outputStemFormat);

            AudioProcessor& audioProcessor = getPluginInstance();

            const AAX_CSampleRate sampleRate = getSampleRate();
            const int bufferSize = 0; // how to get this?
            audioProcessor.setPlayConfigDetails (numberOfInputChannels, numberOfOutputChannels, sampleRate, bufferSize);
            audioProcessor.prepareToPlay (sampleRate, bufferSize);

            check (Controller()->SetSignalLatency (audioProcessor.getLatencySamples()));
        }

        AAX_CSampleRate getSampleRate() const
        {
            AAX_CSampleRate sampleRate;
            check (Controller()->GetSampleRate (&sampleRate));
            return sampleRate;
        }

        JUCELibraryRefCount juceCount;

        ScopedPointer<AudioProcessor> pluginInstance;
        MidiBuffer midiBuffer;
        Array<float*> channelList;
        int32_t juceChunkIndex;

        // tempFilterData is initialized in GetChunkSize.
        // To avoid generating it again in GetChunk, we keep it as a member.
        mutable juce::MemoryBlock tempFilterData;

        JUCE_DECLARE_NON_COPYABLE (JuceAAX_Processor)
    };

    //==============================================================================
    static void AAX_CALLBACK algorithmProcessCallback (JUCEAlgorithmContext* const instancesBegin[],
                                                       const void* const instancesEnd)
    {
        for (JUCEAlgorithmContext* const* iter = instancesBegin; iter < instancesEnd; ++iter)
        {
            const JUCEAlgorithmContext& i = **iter;

            i.pluginInstance->parameters.process (i.inputChannels, i.outputChannels,
                                                  *(i.bufferSize), *(i.bypass) != 0,
                                                  i.midiNodeIn, i.midiNodeOut);
        }
    }

    //==============================================================================
    static void createDescriptor (AAX_IComponentDescriptor& desc, int channelConfigIndex,
                                  int numInputs, int numOutputs)
    {
        check (desc.AddAudioIn  (JUCEAlgorithmIDs::inputChannels));
        check (desc.AddAudioOut (JUCEAlgorithmIDs::outputChannels));
        check (desc.AddAudioBufferLength (JUCEAlgorithmIDs::bufferSize));
        check (desc.AddDataInPort (JUCEAlgorithmIDs::bypass, sizeof (int32_t)));

       #if JucePlugin_WantsMidiInput
        check (desc.AddMIDINode (JUCEAlgorithmIDs::midiNodeIn, AAX_eMIDINodeType_LocalInput,
                                 JucePlugin_Name, 0xffff));
       #endif

       #if JucePlugin_ProducesMidiOutput
        check (desc.AddMIDINode (JUCEAlgorithmIDs::midiNodeOut, AAX_eMIDINodeType_LocalOutput,
                                 JucePlugin_Name " Out", 0xffff));
       #endif

        check (desc.AddPrivateData (JUCEAlgorithmIDs::pluginInstance, sizeof (PluginInstanceInfo)));

        // Create a property map
        AAX_IPropertyMap* const properties = desc.NewPropertyMap();
        jassert (properties != nullptr);

        properties->AddProperty (AAX_eProperty_ManufacturerID,      JucePlugin_AAXManufacturerCode);
        properties->AddProperty (AAX_eProperty_ProductID,           JucePlugin_AAXProductId);

       #if JucePlugin_AAXDisableBypass
        properties->AddProperty (AAX_eProperty_CanBypass,           false);
       #else
        properties->AddProperty (AAX_eProperty_CanBypass,           true);
       #endif

        properties->AddProperty (AAX_eProperty_InputStemFormat,     getFormatForChans (numInputs));
        properties->AddProperty (AAX_eProperty_OutputStemFormat,    getFormatForChans (numOutputs));

        // This value needs to match the RTAS wrapper's Type ID, so that
        // the host knows that the RTAS/AAX plugins are equivalent.
        properties->AddProperty (AAX_eProperty_PlugInID_Native,     'jcaa' + channelConfigIndex);

        check (desc.AddProcessProc_Native (algorithmProcessCallback, properties));
    }

    static void getPlugInDescription (AAX_IEffectDescriptor& descriptor)
    {
        descriptor.AddName (JucePlugin_Desc);
        descriptor.AddName (JucePlugin_Name);
        descriptor.AddCategory (JucePlugin_AAXCategory);

        check (descriptor.AddProcPtr ((void*) JuceAAX_GUI::Create,        kAAX_ProcPtrID_Create_EffectGUI));
        check (descriptor.AddProcPtr ((void*) JuceAAX_Processor::Create,  kAAX_ProcPtrID_Create_EffectParameters));

        const short channelConfigs[][2] = { JucePlugin_PreferredChannelConfigurations };
        const int numConfigs = numElementsInArray (channelConfigs);

        // You need to actually add some configurations to the JucePlugin_PreferredChannelConfigurations
        // value in your JucePluginCharacteristics.h file..
        jassert (numConfigs > 0);

        for (int i = 0; i < numConfigs; ++i)
        {
            if (AAX_IComponentDescriptor* const desc = descriptor.NewComponentDescriptor())
            {
                createDescriptor (*desc, i,
                                  channelConfigs [i][0],
                                  channelConfigs [i][1]);

                check (descriptor.AddComponent (desc));
            }
        }
    }
};

//==============================================================================
AAX_Result JUCE_CDECL GetEffectDescriptions (AAX_ICollection*);
AAX_Result JUCE_CDECL GetEffectDescriptions (AAX_ICollection* collection)
{
    AAXClasses::JUCELibraryRefCount libraryRefCount;

    if (AAX_IEffectDescriptor* const descriptor = collection->NewDescriptor())
    {
        AAXClasses::getPlugInDescription (*descriptor);
        collection->AddEffect (JUCE_STRINGIFY (JucePlugin_AAXIdentifier), descriptor);

        collection->SetManufacturerName (JucePlugin_Manufacturer);
        collection->AddPackageName (JucePlugin_Desc);
        collection->AddPackageName (JucePlugin_Name);
        collection->SetPackageVersion (JucePlugin_VersionCode);

        return AAX_SUCCESS;
    }

    return AAX_ERROR_NULL_OBJECT;
}

#endif
