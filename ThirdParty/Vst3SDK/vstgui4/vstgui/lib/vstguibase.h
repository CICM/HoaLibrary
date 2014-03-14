//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins :
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

#ifndef __vstguibase__
#define __vstguibase__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------
// VSTGUI Version
//-----------------------------------------------------------------------------
#define VSTGUI_VERSION_MAJOR  4
#define VSTGUI_VERSION_MINOR  2

//-----------------------------------------------------------------------------
// Platform definitions
//-----------------------------------------------------------------------------
#if __APPLE_CC__
	#include <stdint.h>
	#include <AvailabilityMacros.h>
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#ifndef MAC
			#define MAC 1
		#endif
		#ifndef MAC_COCOA
			#define MAC_COCOA 1
		#endif
		#define VSTGUI_OPENGL_SUPPORT 0	// there's an implementation, but not yet tested, so this is zero
		#define VSTGUI_TOUCH_EVENT_HANDLING 1
	#else
		#ifndef MAC_OS_X_VERSION_10_5
			#define MAC_OS_X_VERSION_10_5 1050
		#endif
		#ifndef MAC_COCOA
			#define MAC_COCOA (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5)
		#endif
		#ifndef MAC
			#define MAC 1
		#endif
		#if !__LP64__ && !defined (MAC_CARBON)
			#define MAC_CARBON 1
			#ifndef TARGET_API_MAC_CARBON
				#define TARGET_API_MAC_CARBON 1
			#endif
			#ifndef __CF_USE_FRAMEWORK_INCLUDES__
				#define __CF_USE_FRAMEWORK_INCLUDES__ 1
			#endif
		#endif
	#endif
	#ifdef __has_feature
		#define VSTGUI_RVALUE_REF_SUPPORT __has_feature (cxx_rvalue_references)
		#define VSTGUI_RANGE_BASED_FOR_LOOP_SUPPORT __has_feature (cxx_range_for)
		#if VSTGUI_RVALUE_REF_SUPPORT
			#include <type_traits>
		#endif
		#if __has_feature (cxx_override_control)
			#define VSTGUI_OVERRIDE_VMETHOD	override
		#endif
	#endif

#elif WIN32 || WINDOWS
	#include <sdkddkver.h>
	#if _WIN32_WINNT < 0x600
		#error unsupported Platform SDK you need at least the Vista Platform SDK to compile VSTGUI
	#endif
	#if defined (_WIN32_WINNT_WIN7) && !defined (VSTGUI_DIRECT2D_SUPPORT)
		#define VSTGUI_DIRECT2D_SUPPORT	1
	#endif
	#if _MSC_VER >=	1600
		#define VSTGUI_OVERRIDE_VMETHOD	override
		#define VSTGUI_RVALUE_REF_SUPPORT 1
		#include <type_traits>
		#include <stdint.h>
	#else
		typedef char				int8_t;
		typedef unsigned char		uint8_t;
		typedef short				int16_t;
		typedef unsigned short		uint16_t;
		typedef long				int32_t;
		typedef unsigned long		uint32_t;
		typedef __int64				int64_t;
		typedef unsigned __int64	uint64_t;
	#endif
	#ifndef WINDOWS
		#define WINDOWS 1
	#endif
#else // GCC/Clang based builds on non Windows and non Mac
	#include <stdint.h>
	#include <limits.h>
	#pragma GCC diagnostic ignored "-Wreorder"
	#pragma GCC diagnostic ignored "-Wmultichar"
	#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

#ifdef UNICODE
	#undef UNICODE
#endif
#define UNICODE 1

//----------------------------------------------------
// C++11 features
//----------------------------------------------------
#ifndef VSTGUI_RVALUE_REF_SUPPORT
	#define VSTGUI_RVALUE_REF_SUPPORT 0
#endif

#ifndef VSTGUI_OVERRIDE_VMETHOD
	#define VSTGUI_OVERRIDE_VMETHOD
#endif

#ifndef VSTGUI_RANGE_BASED_FOR_LOOP_SUPPORT
	#define VSTGUI_RANGE_BASED_FOR_LOOP_SUPPORT 0
#endif

//----------------------------------------------------
// Helper Macro for range based for loops
//----------------------------------------------------
#if VSTGUI_RANGE_BASED_FOR_LOOP_SUPPORT
	#define VSTGUI_RANGE_BASED_FOR_LOOP(ContainerType, container, varType, varName) for (auto& varName : container) {
#else
	#define VSTGUI_RANGE_BASED_FOR_LOOP(ContainerType, container, varType, varName) for (ContainerType::iterator it = container.begin (); it != container.end (); it++) { varType varName = (*it);
#endif
#define VSTGUI_RANGE_BASED_FOR_LOOP_END }

//----------------------------------------------------
// Feature setting
//----------------------------------------------------
#ifndef VSTGUI_OPENGL_SUPPORT
	#define VSTGUI_OPENGL_SUPPORT 1
#endif

#ifndef VSTGUI_TOUCH_EVENT_HANDLING
	#define VSTGUI_TOUCH_EVENT_HANDLING 0
#endif

#ifndef VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO
	#define VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO 1
#endif

//----------------------------------------------------
// Deprecation setting
//----------------------------------------------------
#ifndef VSTGUI_ENABLE_DEPRECATED_METHODS
	#define VSTGUI_ENABLE_DEPRECATED_METHODS 1
#endif

#ifndef DEPRECATED_ATTRIBUTE
	#define DEPRECATED_ATTRIBUTE
#endif

#if VSTGUI_ENABLE_DEPRECATED_METHODS
	#define VSTGUI_DEPRECATED(x)	DEPRECATED_ATTRIBUTE	x
#else
	#define VSTGUI_DEPRECATED(x)
#endif

//----------------------------------------------------
// Helper makros
//----------------------------------------------------
#define	VSTGUI_MAKE_STRING_PRIVATE_DONT_USE(x)	# x
#define	VSTGUI_MAKE_STRING(x)					VSTGUI_MAKE_STRING_PRIVATE_DONT_USE(x)

//----------------------------------------------------
#if DEVELOPMENT
	#ifndef DEBUG
		#define DEBUG	1
	#endif
#else
	#if !defined(NDEBUG) && !defined(DEBUG)
		#define NDEBUG	1
	#endif
#endif

//----------------------------------------------------
#if VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO
	#if DEBUG
		#define CLASS_METHODS(name, parent)             \
			virtual bool isTypeOf (IdStringPtr s) const \
				{ return (!strcmp (s, (#name))) ? true : parent::isTypeOf (s); }\
			virtual IdStringPtr getClassName () const { return (#name); } \
			virtual CBaseObject* newCopy () const { return new name (*this); }
		#define CLASS_METHODS_NOCOPY(name, parent)             \
			virtual bool isTypeOf (IdStringPtr s) const \
				{ return (!strcmp (s, (#name))) ? true : parent::isTypeOf (s); }\
			virtual IdStringPtr getClassName () const { return (#name); } \
			virtual CBaseObject* newCopy () const { return 0; }
	#else
		#define CLASS_METHODS(name, parent)             \
			virtual bool isTypeOf (IdStringPtr s) const \
				{ return (!strcmp (s, (#name))) ? true : parent::isTypeOf (s); } \
			virtual CBaseObject* newCopy () const { return (CBaseObject*)new name (*this); }
		#define CLASS_METHODS_NOCOPY(name, parent)             \
			virtual bool isTypeOf (IdStringPtr s) const \
				{ return (!strcmp (s, (#name))) ? true : parent::isTypeOf (s); } \
			virtual CBaseObject* newCopy () const { return 0; }
	#endif // DEBUG
	#define CLASS_METHODS_VIRTUAL(name, parent)             \
		virtual bool isTypeOf (IdStringPtr s) const \
			{ return (!strcmp (s, (#name))) ? true : parent::isTypeOf (s); } \
		virtual CBaseObject* newCopy () const = 0;
#else
	#define CLASS_METHODS(name, parent) CBaseObject* newCopy () const VSTGUI_OVERRIDE_VMETHOD { return new name (*this); }
	#define CLASS_METHODS_NOCOPY(name, parent) CBaseObject* newCopy () const VSTGUI_OVERRIDE_VMETHOD { return 0; }
	#define CLASS_METHODS_VIRTUAL(name, parent) CBaseObject* newCopy () const VSTGUI_OVERRIDE_VMETHOD = 0;
#endif // VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO

//----------------------------------------------------
namespace VSTGUI {
	
typedef double		CCoord;				///< coordinate type
typedef const char* IdStringPtr;		///< ID String pointer
typedef const char* UTF8StringPtr;		///< UTF8 String pointer
typedef char*		UTF8StringBuffer;	///< UTF8 String buffer pointer

//-----------------------------------------------------------------------------
// @brief Byte Order
//-----------------------------------------------------------------------------
enum ByteOrder {
	kBigEndianByteOrder = 0,
	kLittleEndianByteOrder,
#if WINDOWS || defined (__LITTLE_ENDIAN__)
	kNativeByteOrder = kLittleEndianByteOrder
#else
	kNativeByteOrder = kBigEndianByteOrder
#endif
};

//-----------------------------------------------------------------------------
// @brief Message Results
//-----------------------------------------------------------------------------
enum CMessageResult
{
	kMessageUnknown = 0,
	kMessageNotified = 1
};

//-----------------------------------------------------------------------------
// CBaseObject Declaration
//! @brief Base Object with reference counter
//-----------------------------------------------------------------------------
class CBaseObject
{
public:
	CBaseObject () : nbReference (1) {}
	virtual ~CBaseObject () {}

	//-----------------------------------------------------------------------------
	/// @name Reference Counting Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual void forget () { nbReference--; if (nbReference == 0) delete this; }	///< decrease refcount and delete object if refcount == 0
	virtual void remember () { nbReference++; }										///< increase refcount
	virtual int32_t getNbReference () const { return nbReference; }					///< get refcount
	//@}

	//-----------------------------------------------------------------------------
	/// @name Message Methods
	//-----------------------------------------------------------------------------
	//@{
	virtual CMessageResult notify (CBaseObject* sender, IdStringPtr message) { return kMessageUnknown; }
	//@}

	/// @cond ignore
#if VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO
	virtual bool isTypeOf (IdStringPtr s) const { return (!strcmp (s, "CBaseObject")); }
	#if DEBUG
	virtual IdStringPtr getClassName () const { return "CBaseObject"; }
	#endif
#endif // VSTGUI_ENABLE_OLD_CLASS_TYPE_INFO
	virtual CBaseObject* newCopy () const { return 0; }
	/// @endcond

private:
	int32_t nbReference;
};

//-----------------------------------------------------------------------------
class CBaseObjectGuard
{
public:
	CBaseObjectGuard (CBaseObject* _obj) : obj (_obj) { if (obj) obj->remember (); }
	~CBaseObjectGuard () { if (obj) obj->forget (); }
protected:
	CBaseObject* obj;
};

//------------------------------------------------------------------------
template <class I>
class SharedPointer
{
public:
//------------------------------------------------------------------------
	inline SharedPointer (I* ptr, bool remember = true);
	inline SharedPointer (const SharedPointer&);
	inline SharedPointer ();
	inline ~SharedPointer ();

	inline I* operator=(I* ptr);
	inline SharedPointer<I>& operator=(const SharedPointer<I>& );

	inline operator I* ()  const { return ptr; }      // act as I*
	inline I* operator->() const { return ptr; }      // act as I*

	template<class T> T* cast () const { return dynamic_cast<T*> (ptr); }

#if VSTGUI_RVALUE_REF_SUPPORT
	inline SharedPointer (SharedPointer<I>&& mp);
	inline SharedPointer<I>& operator=(SharedPointer<I>&& mp);
#endif
//------------------------------------------------------------------------
protected:
	I* ptr;
};

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>::SharedPointer (I* _ptr, bool remember)
: ptr (_ptr)
{
	if (ptr && remember)
		ptr->remember ();
}

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>::SharedPointer (const SharedPointer<I>& other)
: ptr (other.ptr)
{
	if (ptr)
		ptr->remember ();
}

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>::SharedPointer ()
: ptr (0)
{}

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>::~SharedPointer ()
{
	if (ptr)
		ptr->forget ();
}

#if VSTGUI_RVALUE_REF_SUPPORT
//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>::SharedPointer (SharedPointer<I>&& mp)
{
	*this = std::move (mp);
}

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>& SharedPointer<I>::operator=(SharedPointer<I>&& mp)
{
	ptr = mp.ptr;
	mp.ptr = nullptr;
	return *this;
}
#endif

//------------------------------------------------------------------------
template <class I>
inline I* SharedPointer<I>::operator=(I* _ptr)
{
	if (_ptr != ptr)
	{
		if (ptr)
			ptr->forget ();
		ptr = _ptr;
		if (ptr)
			ptr->remember ();
	}
	return ptr;
}

//------------------------------------------------------------------------
template <class I>
inline SharedPointer<I>& SharedPointer<I>::operator=(const SharedPointer<I>& _ptr)
{
	operator= (_ptr.ptr);
	return *this;
}

//------------------------------------------------------------------------
template <class I>
class OwningPointer : public SharedPointer<I>
{
public:
//------------------------------------------------------------------------
	inline OwningPointer (I* p) : SharedPointer<I> (p, false) {}
	inline OwningPointer (const SharedPointer<I>& p) : SharedPointer<I> (p) {}
	inline OwningPointer (const OwningPointer<I>& p) : SharedPointer<I> (p) {}
	inline OwningPointer () : SharedPointer<I> () {}
	inline I* operator=(I* _ptr)
	{
		if (_ptr != this->ptr)
		{
			if (this->ptr)
				this->ptr->forget ();
			this->ptr = _ptr;
		}
		return this->ptr;
	}
};

} // namespace

//-----------------------------------------------------------------------------
#include "vstguidebug.h"

#endif
