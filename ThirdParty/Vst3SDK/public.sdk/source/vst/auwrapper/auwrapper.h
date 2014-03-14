//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/auwrapper/auwrapper.h
// Created by  : Steinberg, 12/2007
// Description : VST 3 -> AU Wrapper
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2013, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// This Software Development Kit may not be distributed in parts or its entirety  
// without prior written agreement by Steinberg Media Technologies GmbH. 
// This SDK must not be used to re-engineer or manipulate any technology used  
// in any Steinberg or Third-party application or software module, 
// unless permitted by law.
// Neither the name of the Steinberg Media Technologies nor the names of its
// contributors may be used to endorse or promote products derived from this 
// software without specific prior written permission.
// 
// THIS SDK IS PROVIDED BY STEINBERG MEDIA TECHNOLOGIES GMBH "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL STEINBERG MEDIA TECHNOLOGIES GMBH BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------------

/**
***************************
\page auwrapper AudioUnit Wrapper
***************************
\section Introduction
***************************
The VST 3 SDK comes with an AudioUnit wrapper, which can wrap one VST 3 Audio Processor and Edit Controller as an AudioUnit effect/instrument.

The wrapper is a small dynamic library which loads the VST 3 Plug-in.
As AudioUnits store some important information in their resource fork, this library must be compiled for every VST 3 Plug-in.
\n\n
***************************
\section howdoesitwork How does it work ?
***************************

- build the auwrapper project (public.sdk/source/vst/auwrapper/auwrapper.xcodeproj)
- create a copy of the again AU wrapper example project directory (public.sdk/source/vst/auwrapper/again/)
- rename the copy to your needs
- edit the target settings of the project and change
	- Product Name
	- Library search path so that it points to the directory where libauwrapper.a exists
	- architecture setting so that it only includes architectures the VST 3 Plug-in supports

- search in the project for AUWRAPPER_CHANGE and change the settings to your needs, especially in :
	- edit audiounitconfig.h see comments there
	- edit Info.plist see comments there
- edit the "Make Links Script" for easier debugging/development
- build your project
- done... that is all!

For the release version, you must place a copy or an alias of your VST 3 Plug-in in the resource folder of the bundle named "plugin.vst3"

 */
/// \cond ignore

#ifndef __auwrapper__
#define __auwrapper__

#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7
#include "AudioUnits/AUPublic/AUBase/AUBase.h"
#define AUWRAPPER_BASE_CLASS AUBase
#else
#include "AudioUnits/AUPublic/OtherBases/MusicDeviceBase.h"
#define AUWRAPPER_BASE_CLASS MusicDeviceBase
#endif
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"
#include "pluginterfaces/vst/ivstunits.h"
#include "public.sdk/source/vst/hosting/parameterchanges.h"
#include "public.sdk/source/vst/hosting/processdata.h"
#include "public.sdk/source/vst/hosting/eventlist.h"
#include "base/source/timer.h"
#include "base/source/tdictionary.h"
#include "base/source/tarray.h"
#include "base/source/fstring.h"
#include "base/source/fthread.h"
#include <Cocoa/Cocoa.h>
#include <AudioToolbox/AudioToolbox.h>

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
class AUWrapper
: public AUWRAPPER_BASE_CLASS
, public IComponentHandler
, public ITimerCallback
{
public:
	AUWrapper (ComponentInstanceRecord* ci);
	~AUWrapper ();

	//---ComponentBase---------------------
	ComponentResult	Version ();
	void PostConstructor ();

	//---AUBase-----------------------------
	void Cleanup ();
	ComponentResult Initialize ();
	AUElement* CreateElement (AudioUnitScope scope, AudioUnitElement element);
	UInt32 SupportedNumChannels (const AUChannelInfo** outInfo);
	bool StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element);
	ComponentResult ChangeStreamFormat (AudioUnitScope inScope, AudioUnitElement inElement, const CAStreamBasicDescription& inPrevFormat, const CAStreamBasicDescription& inNewFormat);
	ComponentResult SetConnection (const AudioUnitConnection& inConnection);
	ComponentResult GetParameterInfo (AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo& outParameterInfo);
	ComponentResult SetParameter (AudioUnitParameterID inID, AudioUnitScope inScope, AudioUnitElement inElement, AudioUnitParameterValue inValue, UInt32 inBufferOffsetInFrames);

	ComponentResult SaveState (CFPropertyListRef* outData);
	ComponentResult RestoreState (CFPropertyListRef inData);

	ComponentResult Render (AudioUnitRenderActionFlags &ioActionFlags, const AudioTimeStamp &inTimeStamp, UInt32 inNumberFrames);

	int GetNumCustomUIComponents ();
	void GetUIComponentDescs (ComponentDescription* inDescArray);

	ComponentResult GetPropertyInfo (AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, UInt32 &outDataSize, Boolean &outWritable);
	ComponentResult GetProperty (AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, void* outData);
	ComponentResult SetProperty (AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, const void* inData, UInt32 inDataSize);

	Float64 GetLatency ();
	Float64 GetTailTime ();

	//---Factory presets
	OSStatus GetPresets (CFArrayRef* outData) const;
	OSStatus NewFactoryPresetSet (const AUPreset& inNewFactoryPreset);

	//---MusicDeviceBase-------------------------
	ComponentResult StartNote (MusicDeviceInstrumentID inInstrument, MusicDeviceGroupID inGroupID, NoteInstanceID* outNoteInstanceID, UInt32 inOffsetSampleFrame, const MusicDeviceNoteParams &inParams);
	ComponentResult StopNote (MusicDeviceGroupID inGroupID, NoteInstanceID inNoteInstanceID, UInt32 inOffsetSampleFrame);
	OSStatus GetInstrumentCount (UInt32 &outInstCount) const;

	//---AUMIDIBase------------------------------
	OSStatus HandleNonNoteEvent (UInt8 status, UInt8 channel, UInt8	data1, UInt8 data2, UInt32 inStartFrame);
	
	//---custom----------------------------------
	void setControllerParameter (ParamID pid, ParamValue value);

	// return for a given midiChannel the unitID and the ProgramListID
	bool getProgramListAndUnit (int32 midiChannel, UnitID& unitId, ProgramListID& programListId);

	//------------------------------------------------------------------------
#if !CA_USE_AUDIO_PLUGIN_ONLY
	static ComponentResult ComponentEntryDispatch (ComponentParameters* params, AUWrapper* This);
#endif
	//------------------------------------------------------------------------
	static CFBundleRef gBundleRef;
	//------------------------------------------------------------------------
	DECLARE_FUNKNOWN_METHODS

protected:
	//---from IComponentHandler-------------------
	tresult PLUGIN_API beginEdit (ParamID tag);
	tresult PLUGIN_API performEdit (ParamID tag, ParamValue valueNormalized);
	tresult PLUGIN_API endEdit (ParamID tag);
	tresult PLUGIN_API restartComponent (int32 flags);

	//---from ITimerCallback----------------------
	void onTimer (Timer* timer);

	// internal helpers
	double getSampleRate () const { return sampleRate; }
	void updateProcessContext ();
	void syncParameterValues ();
	void cacheParameterValues ();
	void clearParameterValueCache ();
	
	virtual IPluginFactory* getFactory ();
	void loadVST3Module ();
	void unloadVST3Module ();
	bool validateChannelPair (int inChannelsIn, int inChannelsOut, const AUChannelInfo* info, UInt32 numChanInfo) const;


	IAudioProcessor* audioProcessor;
	IEditController* editController;
	IMidiMapping* midiMapping;

	Timer* timer;
	
	HostProcessData processData;
	ParameterChanges processParamChanges;
	ParameterChanges outputParamChanges;
	ParameterChangeTransfer transferParamChanges;
	ParameterChangeTransfer outputParamTransfer;
	ProcessContext processContext;
	EventList eventList;

	TDictionary<UnitID, UnitInfo> unitInfos;
	TArray<String> clumpGroups;
	TDictionary<uint32, AudioUnitParameterInfo> cachedParameterInfos;
	FLock parameterCacheChanging;

	NoteInstanceID noteCounter;
	double sampleRate;
	ParamID bypassParamID;
	
	AUPreset* presets;
	int32 numPresets;
	ParamID factoryProgramChangedID;
	
	bool isInstrument;
	bool isBypassed;

	AUParameterListenerRef paramListenerRef;
	static const int32 kMaxProgramChangeParameters = 16;
	ParamID programChangeParameters[kMaxProgramChangeParameters]; // for each midi channel
};

//--------------------------------------------------------------------------------------------------------------
class AutoreleasePool
{
public:
	AutoreleasePool () { ap = [[NSAutoreleasePool alloc] init]; }
	~AutoreleasePool () { [ap drain]; }
//--------------------------------------------------------------------------------------------------------------
protected:
	NSAutoreleasePool* ap;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg

/// \endcond

#endif // __auwrapper__
