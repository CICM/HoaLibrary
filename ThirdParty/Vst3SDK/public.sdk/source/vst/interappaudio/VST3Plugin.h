//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/interappaudio/VST3Plugin.h
// Created by  : Steinberg, 08/2013.
// Description : VST 3 InterAppAudio
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
//-----------------------------------------------------------------------------

#ifndef __VST3Plugin__
#define __VST3Plugin__

/// \cond ignore

#import "AudioIO.h"
#import "base/source/fobject.h"
#import "base/source/timer.h"
#import "base/source/tringbuffer.h"
#import "pluginterfaces/vst/ivstaudioprocessor.h"
#import "pluginterfaces/vst/ivsteditcontroller.h"
#import "pluginterfaces/vst/ivstprocesscontext.h"
#import "public.sdk/source/vst/hosting/processdata.h"
#import "public.sdk/source/vst/hosting/parameterchanges.h"
#import "public.sdk/source/vst/hosting/eventlist.h"
#import <map>

#ifndef __OBJC__
struct NSData;
#endif

namespace Steinberg {
namespace Vst {
namespace InterAppAudio {

static const int32 kMaxUIEvents = 100;

//------------------------------------------------------------------------
class VST3Plugin : public FObject, public IComponentHandler, public IAudioIOProcessor, public ITimerCallback
{
public:
//------------------------------------------------------------------------
	VST3Plugin ();
	virtual ~VST3Plugin ();

	bool init ();

	IEditController* getEditController () const { return editController; }
	IAudioProcessor* getAudioProcessor () const { return processor; }

	tresult scheduleEventFromUI (Event& event);

	NSData* getProcessorState ();
	bool setProcessorState (NSData* data);

	NSData* getControllerState ();
	bool setControllerState (NSData* data);

	OBJ_METHODS(VST3Plugin, FObject)
	REFCOUNT_METHODS(FObject)
	DEFINE_INTERFACES
		DEF_INTERFACE(IComponentHandler)
	END_DEFINE_INTERFACES(FObject)
protected:
	typedef std::map<uint32, uint32> NoteIDPitchMap;
	typedef uint32 ChannelAndCtrlNumber;
	typedef std::map<ChannelAndCtrlNumber, ParamID> MIDIControllerToParamIDMap;

	void createProcessorAndController ();

	void updateProcessContext (AudioIO* audioIO);
	MIDIControllerToParamIDMap createMIDIControllerToParamIDMap ();

	// IComponentHandler
	tresult PLUGIN_API beginEdit (ParamID id) override;
	tresult PLUGIN_API performEdit (ParamID id, ParamValue valueNormalized) override;
	tresult PLUGIN_API endEdit (ParamID id) override;
	tresult PLUGIN_API restartComponent (int32 flags) override;

	// IAudioIOProcessor
	void willStartAudio (AudioIO* audioIO) override;
	void didStopAudio (AudioIO* audioIO) override;
	void onMIDIEvent (UInt32 status, UInt32 data1, UInt32 data2, UInt32 sampleOffset, bool withinRealtimeThread) override;
	void process (const AudioTimeStamp* timeStamp, UInt32 busNumber, UInt32 numFrames, AudioBufferList* ioData, bool& outputIsSilence, AudioIO* audioIO) override;

	// ITimerCallback
	void onTimer (Timer* timer) override;

	IAudioProcessor* processor;
	IEditController* editController;
	Timer* timer;
	
	HostProcessData processData;
	ProcessContext processContext;
	ParameterChangeTransfer inputParamChangeTransfer;
	ParameterChangeTransfer outputParamChangeTransfer;
	ParameterChanges inputParamChanges;
	ParameterChanges outputParamChanges;
	EventList inputEvents;
	
	NoteIDPitchMap noteIDPitchMap;
	volatile int32 lastNodeID;
	
	bool processing;
	
	MIDIControllerToParamIDMap midiControllerToParamIDMap;

	TRingBuffer<Event> uiScheduledEvents;
	
	static ChannelAndCtrlNumber channelAndCtrlNumber (uint16 channel, CtrlNumber ctrler) { return (channel << 16) + ctrler; }
};

}}} // namespaces

/// \endcond

#endif // __VST3Plugin__
