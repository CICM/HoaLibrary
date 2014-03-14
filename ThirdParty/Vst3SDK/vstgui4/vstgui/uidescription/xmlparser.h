//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 4.2
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2013, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __xmlparser__
#define __xmlparser__

#include "../lib/vstguibase.h"
#include "cstream.h"

namespace VSTGUI {
namespace Xml {

class Parser;

//-----------------------------------------------------------------------------
class IContentProvider
{
public:
	virtual int32_t readRawXmlData (int8_t* buffer, int32_t size) = 0;
	virtual void rewind () = 0;
};

//-----------------------------------------------------------------------------
class IHandler
{
public:
	virtual void startXmlElement (Parser* parser, IdStringPtr elementName, UTF8StringPtr* elementAttributes) = 0;
	virtual void endXmlElement (Parser* parser, IdStringPtr name) = 0;
	virtual void xmlCharData (Parser* parser, const int8_t* data, int32_t length) = 0;
	virtual void xmlComment (Parser* parser, IdStringPtr comment) = 0;
};

//-----------------------------------------------------------------------------
class Parser
{
public:
	Parser ();
	virtual ~Parser ();

	bool parse (IContentProvider* provider, IHandler* handler);

	bool stop ();

	IHandler* getHandler () const { return handler; }
protected:
	void* parser;
	IHandler* handler;
};

//-----------------------------------------------------------------------------
class MemoryContentProvider : public CMemoryStream, public IContentProvider
{
public:
	MemoryContentProvider (const void* data, int32_t dataSize);		// data must be valid the whole lifetime of this object
	int32_t readRawXmlData (int8_t* buffer, int32_t size) VSTGUI_OVERRIDE_VMETHOD;
	void rewind () VSTGUI_OVERRIDE_VMETHOD;
};

//-----------------------------------------------------------------------------
class InputStreamContentProvider : public IContentProvider
{
public:
	InputStreamContentProvider (InputStream& stream);

	int32_t readRawXmlData (int8_t* buffer, int32_t size) VSTGUI_OVERRIDE_VMETHOD;
	void rewind () VSTGUI_OVERRIDE_VMETHOD;
protected:
	InputStream& stream;
	int64_t startPos;
};

}} // namespaces

#endif
