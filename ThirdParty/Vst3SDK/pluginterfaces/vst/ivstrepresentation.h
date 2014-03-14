//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Interfaces
// Filename    : pluginterfaces/vst/ivstrepresentation.h
// Created by  : Steinberg, 08/2010
// Description : VST Representation Interface
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

#ifndef __ivstrepresentation__
#define __ivstrepresentation__


#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

//------------------------------------------------------------------------
#include "pluginterfaces/base/falignpush.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
namespace Steinberg {
class IBStream;

namespace Vst {

//------------------------------------------------------------------------
/** RepresentationInfo is the structure describing a representation
This structure is used in the function \see IXmlRepresentationController::getXmlRepresentationStream.
\see IXmlRepresentationController 
*/
struct RepresentationInfo
{
	RepresentationInfo ()
	{
		memset (vendor, 0, kNameSize);
		memset (name, 0, kNameSize);
		memset (version, 0, kNameSize);
		memset (host, 0, kNameSize); 
	}
	enum
	{
		kNameSize = 64
	};
	char8 vendor[kNameSize];	///< Vendor name of the associated representation (remote) (eg. "Yamaha").
	char8 name[kNameSize];		///< Representation (remote) Name (eg. "O2").
	char8 version[kNameSize];	///< Version of this "Remote" (eg. "1.0").
	char8 host[kNameSize];		///< Optional: used if the representation is for a given host only (eg. "Nuendo").
};


//------------------------------------------------------------------------
//------------------------------------------------------------------------
/** Extended IEditController interface for a component. 
\ingroup vstIPlug vst350
- [plug imp]
- [extends IEditController]
- [released: 3.5.0]
- [optional]

A Representation based on XML is a way to export and structure, group Plug-ins parameters for a specific remote (could be hardware or software rack (like quickcontrols)).
\n
It allows to describe more precisely each parameter (what is the best matching to a knob, different titles lengths matching limited remote display,...).\n See an \ref Example.
 \n\n
- A Representation is composed of Pages (this means that to see all exported parameters the user has to navigate through the pages).
- A Page is composed of Cells (for example 8 Cells per page).
- A Cell is composed of Layers (for example a cell could have a knob, a display and a button which are 3 Layers).
- A Layer is associated to a Plug-in parameter using the ParameterID as identifier:
	- it could be a knob with a display for Title and/or value, this display uses the same parameterId, but it could an another one.
	- Switch
	- link which allows to jump directly to a subpage (an another page) 
	- more... See Vst::LayerType
.

\n
This Representation is implemented as XML text following the Document Type Definition (DTD): http://dtd.steinberg.net/VST-Remote-1.1.dtd

\section Example
Here an example of what should be passed in the stream of getXmlRepresentationStream:

\code
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE vstXML PUBLIC "-//Steinberg//DTD VST Remote 1.1//EN" "http://dtd.steinberg.net/VST-Remote-1.1.dtd">
<vstXML version="1.0">
	<plugin classID="341FC5898AAA46A7A506BC0799E882AE" name="Chorus" vendor="Steinberg Media Technologies" />
	<originator>My name</originator>
	<date>2010-12-31</date>
	<comment>This is an example for 4 Cells per Page for the Remote named ProductRemote 
	         from company HardwareCompany.</comment>

	<!-- ===================================== -->
	<representation name="ProductRemote" vendor="HardwareCompany" version="1.0">
		<page name="Root">
			<cell>
				<layer type="knob" parameterID="0">
					<titleDisplay>
						<name>Mix dry/wet</name>
						<name>Mix</name>
					</titleDisplay>
				</layer>
			</cell>
			<cell>
				<layer type="display"></layer>
			</cell>
			<cell>
				<layer type="knob" parameterID="3">
					<titleDisplay>
						<name>Delay</name>
						<name>Dly</name>
					</titleDisplay>
				</layer>
			</cell>
			<cell>
				<layer type="knob" parameterID="15">
					<titleDisplay>
						<name>Spatial</name>
						<name>Spat</name>
					</titleDisplay>
				</layer>
			</cell>
		</page>
		<page name="Page 2">
			<cell>
				<layer type="LED" ledStyle="spread" parameterID="2">
					<titleDisplay>
						<name>Width +</name>
						<name>Widt</name>
					</titleDisplay>
				</layer>
				<!--this is the switch for shape A/B-->
				<layer type="switch" switchStyle="pushIncLooped" parameterID="4"></layer>
			</cell>
			<cell>
				<layer type="display"></layer>
			</cell>
			<cell>
				<layer type="LED" ledStyle="singleDot" parameterID="17">
					<titleDisplay>
						<name>Sync Note +</name>
						<name>Note</name>
					</titleDisplay>
				</layer>
				<!--this is the switch for sync to tempo on /off-->
				<layer type="switch" switchStyle="pushIncLooped" parameterID="16"></layer>
			</cell>
			<cell>
				<layer type="knob" parameterID="1">
					<titleDisplay>
						<name>Rate</name>
					</titleDisplay>
				</layer>
			</cell>
		</page>
	</representation>
</vstXML>
\endcode
*/
//------------------------------------------------------------------------
class IXmlRepresentationController: public FUnknown
{
public:
	/** Retrieves a stream containing a XmlRepresentation for a wanted representation info */
	virtual tresult PLUGIN_API getXmlRepresentationStream (RepresentationInfo& info /*in*/, IBStream* stream /*out*/) = 0;

	//------------------------------------------------------------------------
	static const FUID iid;
};

DECLARE_CLASS_IID (IXmlRepresentationController, 0xA81A0471, 0x48C34DC4, 0xAC30C9E1, 0x3C8393D5)


//------------------------------------------------------------------------
/** Defines for XML representation Tags and Attributes */

#define ROOTXML_TAG			"vstXML"

#define COMMENT_TAG			"comment"
#define CELL_TAG			"cell"
#define CELLGROUP_TAG		"cellGroup"
#define CELLGROUPTEMPLATE_TAG	"cellGroupTemplate"
#define CURVE_TAG			"curve"
#define CURVETEMPLATE_TAG	"curveTemplate"
#define DATE_TAG			"date"
#define LAYER_TAG			"layer"
#define NAME_TAG			"name"
#define ORIGINATOR_TAG		"originator"
#define PAGE_TAG			"page"
#define PAGETEMPLATE_TAG	"pageTemplate"
#define PLUGIN_TAG			"plugin"
#define VALUE_TAG			"value"
#define VALUEDISPLAY_TAG	"valueDisplay"
#define VALUELIST_TAG		"valueList"
#define REPRESENTATION_TAG	"representation"
#define SEGMENT_TAG			"segment"
#define SEGMENTLIST_TAG		"segmentList"
#define TITLEDISPLAY_TAG	"titleDisplay"

#define ATTR_CATEGORY		"category"
#define ATTR_CLASSID		"classID"
#define ATTR_ENDPOINT		"endPoint"
#define ATTR_INDEX			"index"
#define ATTR_FLAGS			"flags"
#define ATTR_FUNCTION		"function"
#define ATTR_HOST			"host"
#define ATTR_LEDSTYLE		"ledStyle"
#define ATTR_LENGTH			"length"
#define ATTR_LINKEDTO		"linkedTo"
#define ATTR_NAME			"name"
#define ATTR_ORDER			"order"
#define ATTR_PAGE			"page"
#define ATTR_PARAMID		"parameterID"
#define ATTR_STARTPOINT		"startPoint"
#define ATTR_STYLE			"style"
#define ATTR_SWITCHSTYLE	"switchStyle"
#define ATTR_TEMPLATE		"template"
#define ATTR_TURNSPERFULLRANGE	"turnsPerFullRange"
#define ATTR_TYPE			"type"
#define ATTR_UNITID			"unitID"
#define ATTR_VARIABLES		"variables"
#define ATTR_VENDOR			"vendor"
#define ATTR_VERSION		"version"

//------------------------------------------------------------------------
/** Defines some predefined Representation Remote Names */
#define GENERIC 				"Generic"
#define GENERIC_4_CELLS			"Generic 4 Cells"
#define GENERIC_8_CELLS			"Generic 8 Cells"
#define GENERIC_12_CELLS		"Generic 12 Cells"
#define GENERIC_24_CELLS		"Generic 24 Cells"
#define GENERIC_N_CELLS			"Generic %d Cells"
#define QUICK_CONTROL_8_CELLS	"Quick Controls 8 Cells"

//------------------------------------------------------------------------
/** Layer Types used in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace LayerType
{
	enum 
	{
		kKnob = 0, 		///< a knob (encoder or not)
		kPressedKnob,  	///< a knob which is used by pressing and turning
		kSwitchKnob,	///< knob could be pressed to simulate a switch
		kSwitch,		///< a "on/off" button
		kLED,			///< LED like VU-meter or display around a knob
		kLink,			///< indicates that this layer is a folder linked to an another INode (page)
		kDisplay,		///< only for text display (not really a control)
		kFader,			///< a fader
		kEndOfLayerType
	};

	/** FIDString variant of the LayerType */
	static const FIDString layerTypeFIDString[] = {
		"knob"
		,"pressedKnob"
		,"switchKnob"
		,"switch"
		,"LED"
		,"link"
		,"display"
		,"fader"
		,0
	};
};

//------------------------------------------------------------------------
/** Curve Types used in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace CurveType
{
	const CString kSegment		= "segment";	///<
	const CString kValueList	= "valueList";	///<
};

//------------------------------------------------------------------------
/** Attributes used to defined a Layer in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace Attributes
{
	const CString kStyle		= ATTR_STYLE;			///< string attribute : See AttributesStyle for available string value
	const CString kLEDStyle		= ATTR_LEDSTYLE;		///< string attribute : See AttributesStyle for available string value
	const CString kSwitchStyle	= ATTR_SWITCHSTYLE;		///< string attribute : See AttributesStyle for available string value
	const CString kKnobTurnsPerFullRange = ATTR_TURNSPERFULLRANGE;	///< float attribute
	const CString kFunction		= ATTR_FUNCTION;		///< string attribute : See AttributesFunction for available string value
	const CString kFlags		= ATTR_FLAGS;			///< string attribute : See AttributesFlags for available string value
};

//------------------------------------------------------------------------
/** Attributes Function used to defined the function of a Layer in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace AttributesFunction
{
	/// Global Style
	const CString kPanPosCenterXFunc		= "PanPosCenterX";		///< Gravity point X-axis (L-R) (for stereo: middle between left and right)
	const CString kPanPosCenterYFunc		= "PanPosCenterY";		///< Gravity point Y-axis (Front-Rear)
	const CString kPanPosFrontLeftXFunc		= "PanPosFrontLeftX";	///< Left channel Position in X-axis
	const CString kPanPosFrontLeftYFunc		= "PanPosFrontLeftY";	///< Left channel Position in Y-axis
	const CString kPanPosFrontRightXFunc	= "PanPosFrontRightX";	///< Right channel Position in X-axis
	const CString kPanPosFrontRightYFunc	= "PanPosFrontRightY";	///< Right channel Position in Y-axis
	const CString kPanRotationFunc			= "PanRotation";		///< Rotation around the Center (gravity point)
	const CString kPanLawFunc				= "PanLaw";				///< Panning Law
	const CString kPanMirrorModeFunc		= "PanMirrorMode";		///< Panning Mirror Mode
	const CString kPanLfeGainFunc			= "PanLfeGain";			///< Panning LFE Gain
	const CString kGainReductionFunc		= "GainReduction";		///< Gain Reduction for compressor
	const CString kSoloFunc					= "Solo";				///< Solo
	const CString kMuteFunc					= "Mute";				///< Mute
	const CString kVolumeFunc				= "Volume";				///< Volume
};

//------------------------------------------------------------------------
/** Attributes Style associated a specific Layer Type in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace AttributesStyle
{
	/// Global Style
	const CString kInverseStyle			= "inverse";	///< the associated layer should use the inverse value of parameter (1 - x).

	/// LED Style
	const CString kLEDWrapLeftStyle		= "wrapLeft";	///< |======>----- (the default one if not specified)
	const CString kLEDWrapRightStyle	= "wrapRight";	///< -------<====|
	const CString kLEDSpreadStyle		= "spread";		///< ---<==|==>---
	const CString kLEDBoostCutStyle		= "boostCut";	///< ------|===>--
	const CString kLEDSingleDotStyle	= "singleDot";	///< --------|----

	/// Switch Style
	const CString kSwitchPushStyle		= "push";		///< Apply only when pressed, unpressed will reset the value to min.
	const CString kSwitchPushIncLoopedStyle	= "pushIncLooped";	///< Push will increment the value. When the max is reached it will restart with min.
																///< The default one if not specified (with 2 states values it is a OnOff switch).
	const CString kSwitchPushDecLoopedStyle	= "pushDecLooped";	///< Push will decrement the value. When the min is reached it will restart with max.
	const CString kSwitchPushIncStyle	= "pushInc";	///< Increment after each press (delta depends of the curve).
	const CString kSwitchPushDecStyle	= "pushDec";	///< Decrement after each press (delta depends of the curve).
	const CString kSwitchLatchStyle		= "latch";		///< Each push-release will change the value between min and max. 
														///< A timeout between push and release could be used to simulate a push style (if timeout is reached).
};

//------------------------------------------------------------------------
/** Attributes Flags defining a Layer in a VST XML Representation */ 
//------------------------------------------------------------------------
namespace AttributesFlags
{
	const CString kHideableFlag			= "hideable";	///< the associated layer marked as hideable allows a remote to hide or make it not usable a parameter when the associated value is inactive 
};


//------------------------------------------------------------------------
}} // namespace Vst

//------------------------------------------------------------------------
#include "pluginterfaces/base/falignpop.h"
//------------------------------------------------------------------------

#endif // __ivstrepresentation__
