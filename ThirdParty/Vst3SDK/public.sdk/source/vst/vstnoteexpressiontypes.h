//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/vstnoteexpressiontypes.h
// Created by  : Steinberg, 12/2010
// Description : VST Note Expression Type Info Implementation
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

#ifndef __vstnoteexpressiontypes__
#define __vstnoteexpressiontypes__

#include "pluginterfaces/vst/ivstnoteexpression.h"
#include "base/source/fobject.h"
#include "base/source/tdictionary.h"

namespace Steinberg {
namespace Vst {
class Parameter;

//------------------------------------------------------------------------
/** Note expression type object.
\ingroup vstClasses */
//-----------------------------------------------------------------------------
class NoteExpressionType : public FObject
{
public:
	NoteExpressionType ();
	NoteExpressionType (const NoteExpressionTypeInfo& info);
	NoteExpressionType (NoteExpressionTypeID typeId, const TChar* title, const TChar* shortTitle, const TChar* units,
						int32 unitId, NoteExpressionValue defaultValue, NoteExpressionValue minimum, NoteExpressionValue maximum,
						int32 stepCount, int32 flags = 0, int32 precision = 4);
	NoteExpressionType (NoteExpressionTypeID typeId, const TChar* title, const TChar* shortTitle, const TChar* units,
						int32 unitId, Parameter* associatedParameter, int32 flags = 0);

	/** get the underlying NoteExpressionTypeInfo struct */
	NoteExpressionTypeInfo& getInfo () { return info; }

	/** convert a note expression value to a readable string */
	virtual tresult getStringByValue (NoteExpressionValue valueNormalized /*in*/, String128 string /*out*/);
	/** convert a readable string to a note expression value */
	virtual tresult getValueByString (const TChar* string /*in*/, NoteExpressionValue& valueNormalized /*out*/);

	/** gets the current precision (used for string representation of float) */
	int32 getPrecision () const { return precision;}
	/** Sets the precision for string representation of float value (for example 4.34 with 2 as precision) */
	void setPrecision (int32 val) { precision = val;}
//-----------------------------------------------------------------------------
	OBJ_METHODS(NoteExpressionType, FObject)
protected:
	NoteExpressionTypeInfo info;
	IPtr<Parameter> associatedParameter;
	int32 precision;
};

//------------------------------------------------------------------------
/** Note expression type object representing a custom range.
\ingroup vstClasses */
//-----------------------------------------------------------------------------
class RangeNoteExpressionType : public NoteExpressionType
{
public:
	RangeNoteExpressionType (NoteExpressionTypeID typeId, const TChar* title, const TChar* shortTitle, const TChar* units,
							 int32 unitId, NoteExpressionValue defaultPlainValue, NoteExpressionValue plainMin, NoteExpressionValue plainMax,
							 int32 flags = 0, int32 precision = 4);

	/** Gets the minimum plain value */
	virtual ParamValue getMin () const {return plainMin;}
	/** Sets the minimum plain value */
	virtual void setMin (ParamValue value) {plainMin = value;}
	/** Gets the maximum plain value */
	virtual ParamValue getMax () const {return plainMax;}
	/** Sets the maximum plain value */
	virtual void setMax (ParamValue value) {plainMax = value;}

	virtual tresult getStringByValue (NoteExpressionValue valueNormalized /*in*/, String128 string /*out*/);
	virtual tresult getValueByString (const TChar* string /*in*/, NoteExpressionValue& valueNormalized /*out*/);
//-----------------------------------------------------------------------------
	OBJ_METHODS(RangeNoteExpressionType, NoteExpressionType)
protected:
	NoteExpressionValue plainMin;
	NoteExpressionValue plainMax;
};

//------------------------------------------------------------------------
/** Collection of note expression types.
\ingroup vstClasses */
//------------------------------------------------------------------------
class NoteExpressionTypeContainer : public FObject
{
public:
	/** default constructor */
	NoteExpressionTypeContainer ();

	/** add a note expression type. The container owns the type. No need to release it afterwards. */
	bool addNoteExpressionType (NoteExpressionType* noteExpType);
	/** remove a note expression type */
	bool removeNoteExpressionType (NoteExpressionTypeID typeId);
	/** remove all note expression types */
	void removeAll ();

	/** get a note expression type object by ID */
	NoteExpressionType* getNoteExpressionType (NoteExpressionTypeID typeId);

	/** get the number of note expression types */
	int32 getNoteExpressionCount ();

	/** get note expression info */
	tresult getNoteExpressionInfo (int32 noteExpressionIndex, NoteExpressionTypeInfo& info /*out*/);
	/** convert a note expression value to a readable string */
	tresult getNoteExpressionStringByValue (NoteExpressionTypeID id, NoteExpressionValue valueNormalized /*in*/, String128 string /*out*/);
	/** convert a string to a note expression value */
	tresult getNoteExpressionValueByString (NoteExpressionTypeID id, const TChar* string /*in*/, NoteExpressionValue& valueNormalized /*out*/);
//-----------------------------------------------------------------------------
	OBJ_METHODS(NoteExpressionTypeContainer, FObject)
protected:
	TDictionary<NoteExpressionTypeID, IPtr<NoteExpressionType> > noteExps;
};
}} // namespaces

#endif // __vstnoteexpressiontypes__
