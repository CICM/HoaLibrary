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

#ifndef __cfont__
#define __cfont__

#include "vstguibase.h"
#include "cstring.h"
#include <string>
#include <list>

namespace VSTGUI {

class CDrawContext;
class IPlatformFont;
class IFontPainter;
struct CPoint;

//-----------
// @brief Text Face
//-----------
enum CTxtFace
{
	kNormalFace    = 0,
	kBoldFace      = 1 << 1,
	kItalicFace    = 1 << 2,
	kUnderlineFace = 1 << 3,
	kStrikethroughFace = 1 << 4
};

//-----------------------------------------------------------------------------
// CFontDesc Declaration
//! @brief font class
//-----------------------------------------------------------------------------
class CFontDesc : public CBaseObject
{
public:
	CFontDesc (UTF8StringPtr name = 0, const CCoord& size = 0, const int32_t style = 0);
	CFontDesc (const CFontDesc& font);
	~CFontDesc ();

	//-----------------------------------------------------------------------------
	/// @name Size, Name and Style Methods
	//-----------------------------------------------------------------------------
	//@{
	UTF8StringPtr getName () const { return name; }		///< get the name of the font
	const CCoord& getSize () const { return size; }		///< get the height of the font
	const int32_t& getStyle () const { return style; }		///< get the style of the font

	virtual void setName (UTF8StringPtr newName);			///< set the name of the font
	virtual void setSize (CCoord newSize);				///< set the height of the font
	virtual void setStyle (int32_t newStyle);				///< set the style of the font @sa CTxtFace
	//@}

	virtual IPlatformFont* getPlatformFont ();
	virtual IFontPainter* getFontPainter ();

	virtual CFontDesc& operator = (const CFontDesc&);
	virtual bool operator == (const CFontDesc&) const;
	
	static void cleanup ();

	CLASS_METHODS(CFontDesc, CBaseObject)
protected:
	IPlatformFont* platformFont;
	
	virtual void freePlatformFont ();
	UTF8StringBuffer name;
	CCoord size;
	int32_t style;
};

typedef CFontDesc*	CFontRef;

//-----------------------------------------------------------------------------
// Global fonts
//-----------------------------------------------------------------------------
extern const CFontRef kSystemFont;
extern const CFontRef kNormalFontVeryBig;
extern const CFontRef kNormalFontBig;
extern const CFontRef kNormalFont;
extern const CFontRef kNormalFontSmall;
extern const CFontRef kNormalFontSmaller;
extern const CFontRef kNormalFontVerySmall;
extern const CFontRef kSymbolFont;

//-----------------------------------------------------------------------------
// IFontPainter Declaration
//! @brief font paint interface
//-----------------------------------------------------------------------------
class IFontPainter
{
public:
	virtual ~IFontPainter () {}

	virtual void drawString (CDrawContext* context, const CString& string, const CPoint& p, bool antialias = true) = 0;
	virtual CCoord getStringWidth (CDrawContext* context, const CString& string, bool antialias = true) = 0;
};

//-----------------------------------------------------------------------------
// IPlatformFont declaration
//! @brief platform font class
///
/// Encapsulation of a platform font. You should never need to call IPlatformFont::create(..), instead use CFontDesc::getPlatformFont().
//-----------------------------------------------------------------------------
class IPlatformFont : public CBaseObject
{
public:
	static IPlatformFont* create (UTF8StringPtr name, const CCoord& size, const int32_t& style);
	static bool getAllPlatformFontFamilies (std::list<std::string>& fontFamilyNames);
	
	virtual double getAscent () const = 0;		///< returns the ascent line offset of the baseline of this font. If not supported returns -1
	virtual double getDescent () const = 0;		///< returns the descent line offset of the baseline of this font. If not supported returns -1
	virtual double getLeading () const = 0;		///< returns the space between lines for this font. If not supported returns -1
	virtual double getCapHeight () const = 0;	///< returns the height of the highest capital letter for this font. If not supported returns -1

	virtual IFontPainter* getPainter () = 0;
};

} // namespace

#endif
