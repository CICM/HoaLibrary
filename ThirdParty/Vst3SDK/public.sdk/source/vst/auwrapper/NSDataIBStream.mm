//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/auwrapper/NSDataIBStream.mm
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

/// \cond ignore

#include "NSDataIBStream.h"
#include <algorithm>

#if __has_feature(objc_arc) && __clang_major__ >= 3
#define ARC_ENABLED 1
#endif // __has_feature(objc_arc)

namespace Steinberg {
namespace Vst {

IMPLEMENT_FUNKNOWN_METHODS (NSDataIBStream, IBStream, IBStream::iid)

//--------------------------------------------------------------------------------------------------------------
NSDataIBStream::NSDataIBStream (NSData* data)
: data (data)
, currentPos (0)
{
	FUNKNOWN_CTOR
#if !ARC_ENABLED
	[data retain];
#endif
}

//--------------------------------------------------------------------------------------------------------------
NSDataIBStream::~NSDataIBStream ()
{
#if !ARC_ENABLED
	[data release];
#endif
	FUNKNOWN_DTOR
}

//--------------------------------------------------------------------------------------------------------------
tresult PLUGIN_API NSDataIBStream::read  (void* buffer, int32 numBytes, int32* numBytesRead)
{
	int32 useBytes = std::min (numBytes, (int32)([data length] - currentPos));
	if (useBytes > 0)
	{
		[data getBytes: buffer range: NSMakeRange (currentPos, useBytes)];
		if (numBytesRead)
			*numBytesRead = useBytes;
		currentPos += useBytes;
		return kResultTrue;
	}
	return kResultFalse;
}

//--------------------------------------------------------------------------------------------------------------
tresult PLUGIN_API NSDataIBStream::write (void* buffer, int32 numBytes, int32* numBytesWritten)
{
	return kResultFalse;
}

//--------------------------------------------------------------------------------------------------------------
tresult PLUGIN_API NSDataIBStream::seek  (int64 pos, int32 mode, int64* result)
{
	switch (mode)
	{
		case kIBSeekSet:
		{
			if (pos <= [data length])
			{
				currentPos = pos;
				if (result)
					tell (result);
				return kResultTrue;
			}
			break;
		}
		case kIBSeekCur:
		{
			if (currentPos + pos <= [data length])
			{
				currentPos += pos;
				if (result)
					tell (result);
				return kResultTrue;
			}
			break;
		}
		case kIBSeekEnd:
		{
			if ([data length] + pos <= [data length])
			{
				currentPos = [data length] + pos;
				if (result)
					tell (result);
				return kResultTrue;
			}
			break;
		}
	}
	return kResultFalse;
}

//--------------------------------------------------------------------------------------------------------------
tresult PLUGIN_API NSDataIBStream::tell  (int64* pos)
{
	if (pos)
	{
		*pos = currentPos;
		return kResultTrue;
	}
	return kResultFalse;
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
NSMutableDataIBStream::NSMutableDataIBStream (NSMutableData* data)
: NSDataIBStream (data)
, mdata (data)
{
}

//--------------------------------------------------------------------------------------------------------------
NSMutableDataIBStream::~NSMutableDataIBStream ()
{
	[mdata setLength:currentPos];
}

//--------------------------------------------------------------------------------------------------------------
tresult PLUGIN_API NSMutableDataIBStream::write (void* buffer, int32 numBytes, int32* numBytesWritten)
{
	[mdata replaceBytesInRange:NSMakeRange (currentPos, numBytes) withBytes:buffer];
	if (numBytesWritten)
		*numBytesWritten = numBytes;
	currentPos += numBytes;
	return kResultTrue;
}

}} // namespaces

/// \endcond
