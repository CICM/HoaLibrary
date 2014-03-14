//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/vstrepresentation.h
// Created by  : Steinberg, 08/2010
// Description : VST Representation Helper
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

#ifndef __vstrepresentation__
#define __vstrepresentation__


#include "pluginterfaces/vst/ivstrepresentation.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"

//------------------------------------------------------------------------
namespace Steinberg {
class IBStreamer;

namespace Vst {

//------------------------------------------------------------------------
/** Helper for XML Representation creation.
\ingroup vstClasses 

Here an example of how to use this helper:
\n
\code

// here the parameter ids used by this example 
enum {
	kGain = 129,
	kSize,
	kCutoff,
	kResonance,
	kMaster,
	kEnable1,
	kEnable2,
	kFrequency1,
	kFrequency2,
	kGain1,
	kGain2,
};

//------------------------------------------------------------------------
tresult PLUGIN_API MyPlugInController::getXmlRepresentationStream (Vst::RepresentationInfo& info, IBStream* stream)
{
	String name (info.name);
	if (name == GENERIC_8_CELLS)
	{
		Vst::XmlRepresentationHelper helper (info, "My Company Name", "My Product Name", gPlugProcessorClassID, stream);

		helper.startPage ("Main Page");
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kGain);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kSize);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kMaster);
		helper.startEndCell ();	// empty cell
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kCutoff);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kResonance);
		helper.startEndCell ();	// empty cell
		helper.startEndCell ();	// empty cell
		helper.endPage ();

		helper.startPage ("Page 2");
		helper.startEndCellOneLayer (Vst::LayerType::kSwitch, kEnable1);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kFrequency1);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kGain1);
		helper.startEndCell ();	// empty
		helper.startEndCellOneLayer (Vst::LayerType::kSwitch, kEnable2);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kFrequency2);
		helper.startEndCellOneLayer (Vst::LayerType::kKnob, kGain2);
		helper.startEndCell ();	// empty
		helper.endPage ();

		return kResultTrue;
	}
	return kResultFalse;
}
\endcode
*/
//------------------------------------------------------------------------
class XmlRepresentationHelper
{
public:
	XmlRepresentationHelper (RepresentationInfo& info, FIDString companyName, FIDString pluginName, TUID& pluginUID, IBStream* stream);
	virtual ~XmlRepresentationHelper ();

	bool startPage (FIDString name, int32 unitID = -1);	///< Starts a Page before adding a Cell.
	bool endPage ();									///< Ends a Page before opening a new one.
	bool startCell ();									///< Starts a Cell before adding a Layer.
	bool endCell ();									///< Ends a Cell when no more layer needed.
	bool startEndCell ();								///< Creates an empty cell (alignment for example).
	
	/** Starts a layer for a given type (Vst::LayerType), a parameter id, optionally a function (Vst::AttributesFunction)
		and a style (Vst::AttributesStyle). */
	bool startLayer (int32 type, int32 id, FIDString _function = 0, FIDString style = 0);

	/** Ends a layer before adding new one */
	bool endLayer ();

	/** Same than startLayer except that the layer will be ended automatically (no need to call endLayer). */
	bool startEndLayer (int32 type, int32 id, FIDString _function = 0, FIDString style = 0);
	
	/** Creates a Cell with 1 Layer and end it, could be only call after a call to startPage */
	bool startEndCellOneLayer (int32 type, int32 id, FIDString _function = 0, FIDString style = 0);

	/** Starts a layer for a given parameter info and an optional function (Vst::AttributesFunction). */
	bool startLayer (Vst::ParameterInfo& info, FIDString _function = 0);

	/** Same than startLayer with end created automatically. */
	bool startEndLayer (Vst::ParameterInfo& info, FIDString _function = 0);

	/** Creates a Cell with 1 Layer and end it, could be only call after a call to startPage. */
	bool startEndCellOneLayer (Vst::ParameterInfo& info, FIDString _function = 0);

	/** Creates a Cell with 1 Layer (with name) and end it, could be only call after a call to startPage. */
	bool startEndCellOneLayerWithParamName (Vst::ParameterInfo& info, FIDString _function = 0);

protected:
	enum {
		kInRepresentation = 0,
		kInPage,
		kInCell,
		kInLayer,
		kInTitleDisplay,
		kInName
	};

	bool startLayer (int32 type, int32 id, FIDString _function, FIDString style, bool ended);
	bool startLayer (Vst::ParameterInfo& info, FIDString _function, bool ended);

	bool startEndTitleDisplay (Vst::ParameterInfo& info);

	bool checkState (int32 newState);
	
	IBStreamer* streamer;
	int32 state;
};

//------------------------------------------------------------------------
}} // namespace

#endif	// __vstrepresentation__
