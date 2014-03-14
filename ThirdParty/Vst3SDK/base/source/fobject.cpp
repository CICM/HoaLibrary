//------------------------------------------------------------------------
// Project     : SDK Base
// Version     : 1.0
//
// Category    : Helpers
// Filename    : base/source/fobject.cpp
// Created by  : Steinberg, 2008
// Description : Basic Object implementing FUnknown
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

#include "base/source/fobject.h"
#include "base/source/fatomic.h"
#include "base/source/tarray.h"

namespace Steinberg {

IUpdateHandler* FObject::gUpdateHandler = 0;

//------------------------------------------------------------------------
const FUID FObject::iid;

//------------------------------------------------------------------------
struct FObjectIIDInitializer
{
	// the object iid is always generated so that different components
	// only can cast to their own objects
	// this initializer must be after the definition of FObject::iid, otherwise
	//  the default constructor of FUID will clear the generated iid
	FObjectIIDInitializer () 
	{ 
		const_cast<FUID&> (FObject::iid).generate (); 
	}
} gFObjectIidInitializer;

//------------------------------------------------------------------------
uint32 PLUGIN_API FObject::addRef ()  
{                                      
	FAtomicIncrement (refCount);
	return refCount;
}                                             

//------------------------------------------------------------------------
uint32 PLUGIN_API FObject::release () 
{                                              
	if (FAtomicDecrement (refCount) == 1)
	{
		refCount = -1000;
		delete this;
		return 0;
	}                                   
	return refCount;                 
}

//------------------------------------------------------------------------
tresult PLUGIN_API FObject::queryInterface (const TUID iid, void** obj)
{
	QUERY_INTERFACE (iid, obj, FUnknown::iid, FUnknown)             
	QUERY_INTERFACE (iid, obj, IDependent::iid, IDependent)             
	QUERY_INTERFACE (iid, obj, FObject::iid, FObject)             
	*obj = 0;
	return kNoInterface; 
}

//------------------------------------------------------------------------
void FObject::addDependent (IDependent* dep)
{
	if (gUpdateHandler)
		gUpdateHandler->addDependent (unknownCast (), dep);
}

//------------------------------------------------------------------------
void FObject::removeDependent (IDependent* dep)
{
	if (gUpdateHandler)
		gUpdateHandler->removeDependent (unknownCast (), dep);
}

//------------------------------------------------------------------------
void FObject::changed (int32 msg)
{
	if (gUpdateHandler)
		gUpdateHandler->triggerUpdates (unknownCast (), msg);
	else
		updateDone (msg);
}

//------------------------------------------------------------------------
void FObject::deferUpdate (int32 msg)
{
	if (gUpdateHandler)
		gUpdateHandler->deferUpdates (unknownCast (), msg);
	else
		updateDone (msg);
}

//------------------------------------------------------------------------
/** Automatic creation and destruction of singleton instances. */
//------------------------------------------------------------------------
namespace Singleton 
{
	TArray<FObject**>* singletonInstances = 0;
	bool singletonsTerminated = false;

	bool isTerminated () {return singletonsTerminated;}

	void registerInstance (FObject** o)
	{
		ASSERT (singletonsTerminated == false)
		if (singletonsTerminated == false)
		{
			if (singletonInstances == 0)
				singletonInstances = NEW TArray<FObject**>;
			singletonInstances->add (o);
		}
	}

	struct Deleter
	{
		~Deleter ()
		{
			singletonsTerminated = true;
			if (singletonInstances)
			{
				FOREACH_T (FObject**, inst, *singletonInstances)
					(*inst)->release ();
					*inst = 0;
				ENDFOR

				delete singletonInstances;
				singletonInstances = 0;
			}
		}
	} deleter;
}

} // namespace Steinberg
