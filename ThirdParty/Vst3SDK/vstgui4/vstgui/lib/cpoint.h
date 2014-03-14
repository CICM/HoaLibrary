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

#ifndef __cpoint__
#define __cpoint__

#include "vstguibase.h"
#include "crect.h"

namespace VSTGUI {

//-----------------------------------------------------------------------------
//! @brief Point structure
//-----------------------------------------------------------------------------
struct CPoint
{
	CPoint (CCoord h = 0, CCoord v = 0) : h (h), v (v) {}
	CPoint& operator () (CCoord h, CCoord v) { this->h = h; this->v = v; return *this; }

	bool isInside (const CRect& r) const { return h >= r.left && h <= r.right && v >= r.top && v <= r.bottom; } 

	bool operator != (const CPoint &other) const { return (h != other.h || v != other.v); }
	bool operator == (const CPoint &other) const { return (h == other.h && v == other.v); }

	CPoint& operator += (const CPoint& other) { x += other.x; y += other.y; return *this; }
	CPoint& operator -= (const CPoint& other) { x -= other.x; y -= other.y; return *this; }
	CPoint operator + (const CPoint& other) const { return CPoint (x + other.x, y + other.y); }
	CPoint operator - (const CPoint& other) const { return CPoint (x - other.x, y - other.y); }

	CPoint& offset (const CCoord h, const CCoord v) { *this += CPoint (h, v); return *this; }

	void makeIntegral ();

	union { CCoord h; CCoord x;};
	union { CCoord v; CCoord y;};
};

} // namespace

#endif
