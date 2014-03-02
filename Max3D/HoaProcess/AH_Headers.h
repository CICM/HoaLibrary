/**
 * Alexander Harker concatenated headers needed for dynamicdsp~ suite (Atomic.h + Types.h + VectorOps.h + Memory_Swap.h)
 */

#ifndef DEF_AH_HEADERS
#define DEF_AH_HEADERS

// ========================================================================================================================================== //
// AH_Atomic.h
// ========================================================================================================================================== //

// In case we are compiing for Max 4, or outside of the Max SDK we have to check fot a SDK number and provide the expected atomic macros if bit oresent or less than 5

#if (defined C74_MAX_SDK_VERSION && (C74_MAX_SDK_VERSION >= 0x0500))

// Use Max SDK macros

#include <ext_atomic.h>

#else

// Local macros

#ifdef __APPLE__	// Apple

#include <libkern/OSAtomic.h>

typedef int32_t t_int32_atomic;

#define ATOMIC_INCREMENT OSAtomicIncrement32
#define ATOMIC_DECREMENT OSAtomicDecrement32
#define ATOMIC_INCREMENT_BARRIER OSAtomicIncrement32Barrier
#define ATOMIC_DECREMENT_BARRIER OSAtomicDecrement32Barrier

#else				// Windows

#include <intrin.h>

typedef volatile long t_int32_atomic;

#define ATOMIC_INCREMENT				_InterlockedIncrement
#define ATOMIC_DECREMENT				_InterlockedDecrement
#define ATOMIC_INCREMENT_BARRIER		_InterlockedIncrement
#define ATOMIC_DECREMENT_BARRIER		_InterlockedDecrement

#endif		/* __APPLE__ */
#endif		/* (C74_MAX_SDK_VERSION && (C74_MAX_SDK_VERSION >= 0x0500)) */


static __inline long Atomic_Compare_And_Swap (t_int32_atomic Comparand, t_int32_atomic Exchange, t_int32_atomic *Destination)
{
#ifdef __APPLE__
	if (OSAtomicCompareAndSwap32(Comparand, Exchange, (int32_t *) Destination))
#else
		if (InterlockedCompareExchange  (Destination, Exchange, Comparand) == Comparand)
#endif
			return 1;
	return 0;
}

static __inline long Atomic_Compare_And_Swap_Barrier (t_int32_atomic Comparand, t_int32_atomic Exchange, t_int32_atomic *Destination)
{
#ifdef __APPLE__
	if (OSAtomicCompareAndSwap32Barrier(Comparand, Exchange, (int32_t *) Destination))
#else
		if (InterlockedCompareExchange  (Destination, Exchange, Comparand) == Comparand)
#endif
			return 1;
	return 0;
}

static __inline long Atomic_Get_And_Zero (t_int32_atomic *theValue, t_int32_atomic *theOldValue)
{
	t_int32_atomic compare_value;
	long exchanged;
	
	compare_value = *theValue;
	exchanged = Atomic_Compare_And_Swap_Barrier (compare_value, 0, theValue);
	
	if (exchanged)
	{
		*theOldValue = compare_value;
		return 1;
	}
	
	return 0;
}

// ========================================================================================================================================== //
// AH_Types.h
// ========================================================================================================================================== //

// This needs to be altered to cope with platforms other than windows/mac and compilers other than visual studio and GCC

#ifdef __APPLE__
#if __LP64__
#define AH_64BIT
#endif
#else
#ifdef _WIN64
#define AH_64BIT
#endif
#endif


// Pointer-sized Integer definitions

#ifdef AH_64BIT
typedef unsigned long long AH_UIntPtr;
typedef long long AH_SIntPtr;
#else
typedef unsigned long AH_UIntPtr;
typedef long AH_SIntPtr;
#endif

// Integer definitions for given bit sizes

typedef unsigned long long AH_UInt64;
typedef long long AH_SInt64;
typedef unsigned int AH_UInt32;
typedef int AH_SInt32;
typedef unsigned short AH_UInt16;
typedef short AH_SInt16;
typedef unsigned char AH_UInt8;
typedef char AH_SInt8;


// Boolean

typedef int AH_Boolean;

#undef true
#define true 1
#undef false
#define false 0


// ========================================================================================================================================== //
// AH_VectorOps.h
// ========================================================================================================================================== //

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>

#define FORCE_INLINE				__attribute__ ((always_inline))
#define FORCE_INLINE_DEFINITION

#define ALIGNED_MALLOC malloc
#define ALIGNED_FREE free

#else

// Windows

#include <emmintrin.h>
#include <malloc.h>

#define FORCE_INLINE				__forceinline
#define FORCE_INLINE_DEFINITION		__forceinline;

#define ALIGNED_MALLOC(x)  _aligned_malloc(x, 16)
#define ALIGNED_FREE  _aligned_free

typedef	__m128i	vUInt8;
typedef __m128i vSInt8;
typedef	__m128i vUInt16;
typedef __m128i vSInt16;
typedef __m128i vUInt32;
typedef	__m128i vSInt32;
typedef	__m128i vBool32;
typedef __m128i vUInt64;
typedef __m128i vSInt64;
typedef	__m128  vFloat;
typedef	__m128d vDouble;

#endif

// Test for intel compilation

#ifndef TARGET_INTEL
#if defined( __i386__ ) || defined( __x86_64__ ) || defined(WIN_VERSION)
#define TARGET_INTEL
#endif
#endif

// Define for 64 bit float vector in 128bits (2 doubles)

#ifdef TARGET_INTEL
#ifndef VECTOR_F64_128BIT
#define VECTOR_F64_128BIT
#endif
#endif

// Runtime test for SSE2

static __inline int SSE2_check()
{
#ifdef __APPLE__
	return 1;
#else
	int SSE2_flag = 0;
	int CPUInfo[4] = {-1, 0, 0, 0};
	int nIds;
	
	__cpuid(CPUInfo, 0);
	nIds = CPUInfo[0];
	
	if (nIds > 0)
	{
		__cpuid(CPUInfo, 1);
		SSE2_flag = (CPUInfo[3] >> 26) & 0x1;
	}
	
	return SSE2_flag;
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// Utility macros (non platform-specific)  //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// The standard compare operations return all bits on, but for use in MSP we probably want values of one
// These routines can be used in this case

static const vFloat Vec_Ops_F32_One = {1.,1.,1.,1.};

#define F32_VEC_EQUAL_MSP_OP(a,b)		F32_VEC_AND_OP(Vec_Ops_F32_One, F32_VEC_EQUAL_OP(a,b))
#define F32_VEC_NOTEQUAL_MSP_OP(a,b)	F32_VEC_SUB_OP(Vec_Ops_F32_One, F32_VEC_AND_OP(F32_VEC_EQUAL_OP(a,b), Vec_Ops_F32_One))
#define F32_VEC_GT_MSP_OP(a,b)			F32_VEC_AND_OP(Vec_Ops_F32_One, F32_VEC_GT_OP(a,b))
#define F32_VEC_LT_MSP_OP(a,b)			F32_VEC_AND_OP(Vec_Ops_F32_One, F32_VEC_LT_OP(a,b))


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// Macros for platform-specific vector ops ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef TARGET_INTEL

// Intel

// Comparisons that return one or zero

static const vDouble Vec_Ops_F64_One = {1.,1.};

#define F64_VEC_EQUAL_MSP_OP(a,b)		F64_VEC_AND_OP(Vec_Ops_F64_One, F64_VEC_EQUAL_OP(a,b))
#define F64_VEC_NOTEQUAL_MSP_OP(a,b)	F64_VEC_SUB_OP(Vec_Ops_F64_One, F64_VEC_AND_OP(F64_VEC_EQUAL_OP(a,b), Vec_Ops_F64_One))
#define F64_VEC_GT_MSP_OP(a,b)			F64_VEC_AND_OP(Vec_Ops_F64_One, F64_VEC_GT_OP(a,b))
#define F64_VEC_LT_MSP_OP(a,b)			F64_VEC_AND_OP(Vec_Ops_F64_One, F64_VEC_LT_OP(a,b))

// Floating point single precision (32 bit) intrinsics or local functions

#define float2vector					_mm_set1_ps

#define F32_VEC_MUL_OP					_mm_mul_ps
#define F32_VEC_DIV_OP					_mm_div_ps
#define F32_VEC_ADD_OP					_mm_add_ps
#define F32_VEC_SUB_OP					_mm_sub_ps

#define F32_VEC_AND_OP					_mm_and_ps
#define F32_VEC_ANDNOT_OP				_mm_andnot_ps
#define F32_VEC_OR_OP					_mm_or_ps
#define F32_VEC_XOR_OP					_mm_xor_ps

#define F32_VEC_SEL_OP					_mm_sel_ps

#define F32_VEC_MIN_OP					_mm_min_ps
#define F32_VEC_MAX_OP					_mm_max_ps

#define F32_VEC_EQUAL_OP(a,b)			_mm_cmpeq_ps(a,b)
#define F32_VEC_NEQUAL_OP(a,b)			_mm_cmpneq_ps(a,b)
#define F32_VEC_GT_OP(a,b)				_mm_cmpgt_ps(a,b)
#define F32_VEC_LT_OP(a,b)				_mm_cmplt_ps(a,b)

#define F32_VEC_SQRT_OP					_mm_sqrt_ps

#define F32_VEC_ULOAD					_mm_loadu_ps
#define F32_VEC_USTORE					_mm_storeu_ps
#define F32_VEC_MOVE_LO					_mm_movelh_ps
#define F32_VEC_MOVE_HI					_mm_movehl_ps
#define F32_VEC_SHUFFLE					_mm_shuffle_ps

// Conversions from and to 32 bit floating point vectors

#define F32_VEC_FROM_I32				_mm_cvtepi32_ps
#define I32_VEC_FROM_F32_ROUND			_mm_cvtps_epi32
#define I32_VEC_FROM_F32_TRUNC			_mm_cvttps_epi32

// Floating-point double precision (64 bit) intrinsics or local functions (only available under intel)

#define double2vector					_mm_set1_pd

#define F64_VEC_MUL_OP					_mm_mul_pd
#define F64_VEC_DIV_OP					_mm_div_pd
#define F64_VEC_ADD_OP					_mm_add_pd
#define F64_VEC_SUB_OP					_mm_sub_pd

#define F64_VEC_AND_OP					_mm_and_pd
#define F64_VEC_ANDNOT_OP				_mm_andnot_pd
#define F64_VEC_OR_OP					_mm_or_pd
#define F64_VEC_XOR_OP					_mm_xor_pd

#define F64_VEC_SEL_OP					_mm_sel_pd

#define F64_VEC_MIN_OP					_mm_min_pd
#define F64_VEC_MAX_OP					_mm_max_pd

#define F64_VEC_EQUAL_OP(a,b)			_mm_cmpeq_pd(a,b)
#define F64_VEC_NEQUAL_OP(a,b)			_mm_cmpneq_pd(a,b)
#define F64_VEC_GT_OP					_mm_cmpgt_pd
#define F64_VEC_LT_OP					_mm_cmplt_pd

#define F64_VEC_SQRT_OP					_mm_sqrt_pd

#define F64_VEC_ULOAD					_mm_loadu_pd
#define F64_VEC_USTORE					_mm_storeu_pd
#define F64_VEC_UNPACK_LO				_mm_unpacklo_pd
#define F64_VEC_UNPACK_HI				_mm_unpackhi_pd
#define F64_VEC_STORE_HI				_mm_storeh_pd
#define F64_VEC_STORE_LO				_mm_storel_pd
#define F64_VEC_SET_BOTH				_mm_set1_pd
#define F64_VEC_SHUFFLE					_mm_shuffle_pd

// Conversions from and to 64 bit floating point vectors

#define F64_VEC_FROM_F32				_mm_cvtps_pd
#define F32_VEC_FROM_F64				_mm_cvtpd_ps

#define F64_VEC_FROM_I32				_mm_cvtepi32_pd
#define I32_VEC_FROM_F64_ROUND			_mm_cvtpd_epi32
#define I32_VEC_FROM_F64_TRUNC			_mm_cvttpd_epi32

// Integer 32 bit intrinsics

#define s32int2vector					_mm_set1_epi32

#define I32_VEC_ADD_OP					_mm_add_epi32
#define I32_VEC_SUB_OP					_mm_sub_epi32
#define I32_VEC_ADD_OP					_mm_add_epi32

#define I32_VEC_MIN_OP					_mm_min_epi32
#define I32_VEC_MAX_OP					_mm_max_epi32

#define I32_VEC_OR_OP					_mm_or_si128
#define I32_VEC_AND_OP					_mm_and_si128

#define I32_VEC_SHUFFLE_OP				_mm_shuffle_epi32

// Altivec has min / max intrinics for 32 bit signed integers, but on intel this must be done in software (although it is provided under windows)
// These routines are taken directly from the apple SSE migration guide
// The guide can be found at http://developer.apple.com/legacy/mac/library/documentation/Performance/Conceptual/Accelerate_sse_migration/Accelerate_sse_migration.pdf

#ifdef __APPLE__
static __inline vSInt32 _mm_min_epi32(vSInt32 a, vSInt32 b) FORCE_INLINE;
static __inline vSInt32 _mm_min_epi32(vSInt32 a, vSInt32 b)
{
	vSInt32 t = _mm_cmpgt_epi32(a,b);
	return _mm_or_si128( _mm_and_si128(t,b),_mm_andnot_si128(t,a));
}

static __inline vSInt32 _mm_max_epi32(vSInt32 a, vSInt32 b) FORCE_INLINE;
static __inline vSInt32 _mm_max_epi32(vSInt32 a, vSInt32 b)
{
	vSInt32 t = _mm_cmpgt_epi32(a,b);
	return _mm_or_si128( _mm_andnot_si128(t,b),_mm_and_si128(t,a));
}
#endif

// Altivec has selection intrinics for 32 bit floating point vectors, but on intel this must be done in software
// These routines are taken directly from the apple SSE migration guide
// The guide can be found at http://developer.apple.com/legacy/mac/library/documentation/Performance/Conceptual/Accelerate_sse_migration/Accelerate_sse_migration.pdf

#ifdef __APPLE__
static __inline vFloat _mm_sel_ps(vFloat a, vFloat b, vFloat mask) FORCE_INLINE;
static __inline vUInt32 _mm_sel_epi32(vUInt32 a, vUInt32 b, vUInt32 mask) FORCE_INLINE;
#endif

static __inline vFloat _mm_sel_ps(vFloat a, vFloat b, vFloat mask) FORCE_INLINE_DEFINITION
{
b = _mm_and_ps(b, mask);
a = _mm_andnot_ps(mask, a);
return _mm_or_ps(a, b);
}

static __inline vUInt32 _mm_sel_epi32(vUInt32 a, vUInt32 b, vUInt32 mask) FORCE_INLINE_DEFINITION
{
b = _mm_and_si128(b, mask);
a = _mm_andnot_si128(mask, a);
return _mm_or_si128(a, b);
}

static __inline vDouble _mm_sel_pd(vDouble a, vDouble b, vDouble mask) FORCE_INLINE_DEFINITION
{
b = _mm_and_pd(b, mask);
a = _mm_andnot_pd(mask, a);
return _mm_or_pd(a, b);
}

#else

// Altivec

static const vFloat Vec_Ops_F32_Zero = {0.f,0.f,0.f,0.f};

// Floating point 32 bit intrinsics or local functions

#define F32_VEC_MUL_OP(v1, v2)			vec_madd(v1,v2, Vec_Ops_F32_Zero)
#define F32_VEC_DIV_OP					vdivf
#define F32_VEC_ADD_OP					vec_add
#define F32_VEC_SUB_OP					vec_sub

#define F32_VEC_AND_OP					vec_and
#define F32_VEC_XOR_OP					vec_xor
#define F32_VEC_OR_OP					vec_or
#define F32_VEC_SEL_OP					vec_sel

#define F32_VEC_MIN_OP					vec_min
#define F32_VEC_MAX_OP					vec_max

#define F32_VEC_EQUAL_OP(a,b)			vec_cmpeq(a,b)
#define F32_VEC_NEQUAL_OP(a,b)			vec_xor(vec_cmpeq(a,b),Vec_Ops_F32_One)
#define F32_VEC_GT_OP(a,b)				vec_cmpgt(a,b)
#define F32_VEC_LT_OP(a,b)				vec_cmplt(a,b)

#define F32_VEC_ULOAD(p)				vec_uload((unsigned char *)p)
#define F32_VEC_USTORE(p, v)			vec_ustore((unsigned char *)p, (vector unsigned char)v)
#define F32_VEC_SHUFFLE					vec_permute

// Conversions from and to 32 bit floating point vectors

#define F32_VEC_FROM_I32(a)				vec_ctf(a, 0)
#define I32_VEC_FROM_F32_ROUND(a)		vec_cts(vec_round(a), 0)
#define I32_VEC_FROM_F32_TRUNC(a)		vec_cts(a, 0)

// Integer 32 bit intrinsics

#define I32_VEC_ADD_OP					vec_add
#define I32_VEC_SUB_OP					vec_sub

#define I32_VEC_AND_OP					vec_and

#define I32_VEC_MIN_OP					vec_min
#define I32_VEC_MAX_OP					vec_max

// Return a vector filled with a single signed integer value

static __inline vSInt32 s32int2vector (int s32int_val) FORCE_INLINE;
static __inline vSInt32 s32int2vector (int s32int_val) FORCE_INLINE_DEFINITION
{
vSInt32 TheVector = {s32int_val, s32int_val, s32int_val, s32int_val};
return TheVector;
}

// Return a vector filled with a single float value

static __inline vFloat float2vector (float floatval) FORCE_INLINE;
static __inline vFloat float2vector (float floatval) FORCE_INLINE_DEFINITION
{
vFloat TheVector;
float *TheFloatArray = (float *) &TheVector;

TheFloatArray[0] = floatval;
TheFloatArray[1] = floatval;
TheFloatArray[2] = floatval;
TheFloatArray[3] = floatval;

return TheVector;
}

// Provide altivec safe misaligned loads and stores (not sure how fast these are)
// These routines are taken directly from the apple SSE migration guide
// The guide can be found at http://developer.apple.com/legacy/mac/library/documentation/Performance/Conceptual/Accelerate_sse_migration/Accelerate_sse_migration.pdf


static inline vFloat vec_uload(unsigned char *target) FORCE_INLINE;
static inline vFloat vec_uload(unsigned char *target)
{
    vector unsigned char MSQ, LSQ;
    vector unsigned char mask;
	
    MSQ = vec_ld(0, target);						// most significant quadword
    LSQ = vec_ld(15, target);						// least significant quadword
    mask = vec_lvsl(0, target);						// create the permute mask
    return (vFloat) vec_perm(MSQ, LSQ, mask);		// align the data
}


static __inline void vec_ustore(unsigned char *target, vector unsigned char src) FORCE_INLINE;
static __inline void vec_ustore(unsigned char *target, vector unsigned char src)
{
    src = vec_perm( src, src, vec_lvsr( 0, target ) );
    vec_ste( (vector unsigned char) src, 0, (unsigned char*) target );
    vec_ste( (vector unsigned short)src,1,(unsigned short*) target );
    vec_ste( (vector unsigned int) src, 3, (unsigned int*) target );
    vec_ste( (vector unsigned int) src, 4, (unsigned int*) target );
    vec_ste( (vector unsigned int) src, 8, (unsigned int*) target );
    vec_ste( (vector unsigned int) src, 12, (unsigned int*) target );
    vec_ste( (vector unsigned short)src,14,(unsigned short*) target );
    vec_ste( (vector unsigned char) src,15,(unsigned char*) target );
}

#endif	/* TARGET_INTEL */


// ========================================================================================================================================== //
// AH_Memory_Swap.h
// ========================================================================================================================================== //

// All memory assignments are aligned in order that the memory is suitable for vector ops etc.
// Swap results

typedef enum
{
	
	SWAP_NONE,
	SWAP_DONE,
	SWAP_FAILED
	
} t_swap_status;


// Alloc and free routine prototypes


typedef void *(*alloc_method) (AH_UIntPtr size, AH_UIntPtr nom_size);
typedef void (*free_method) (void *);


// Safe memory swap structure


typedef struct _safe_mem_swap
{
	t_int32_atomic lock;
	
	void *new_ptr;
	void *current_ptr;
	
	free_method new_free_method;
	free_method current_free_method;
	
	AH_UIntPtr new_size;
	AH_UIntPtr current_size;
	
	AH_UIntPtr new_free;
	AH_UIntPtr current_free;
	
} t_safe_mem_swap;


// Internal deferred routine for freeing memory

static void free_temp_mem_swap (t_object *x, t_symbol *s, short argc, t_atom *argv)
{
	free_method free_method_ptr = 0;
	
	if (argc)
		free_method_ptr = (free_method) atom_getsym(argv);
	
	if (free_method_ptr)
		free_method_ptr((void *) s);
	else
		ALIGNED_FREE((void *)s);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Alloc / Free / Clear


// Alloc - You should only call this from the new routine to be thread-safe

static __inline long alloc_mem_swap (t_safe_mem_swap *mem_struct, AH_UIntPtr size, AH_UIntPtr nom_size)
{
	long fail = 0;
	
	mem_struct-> lock = 0;
	
	if (size)
		mem_struct->current_ptr = ALIGNED_MALLOC(size);
	else
		mem_struct->current_ptr = 0;
	
	if (size && mem_struct->current_ptr)
	{
		mem_struct->current_size = nom_size;
		mem_struct->current_free = 1;
		mem_struct->current_free_method = 0;
	}
	else
	{
		mem_struct->current_size = 0;
		mem_struct->current_free = 0;
		mem_struct->current_free_method = 0;
		
		if (size)
			fail = 1;
	}
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	return fail;
}


// Free - frees the memory immediately which is only safe in the object free routine - use clear if you want to clear the memory safely elsewhere

static __inline void free_mem_swap (t_safe_mem_swap *mem_struct)
{
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_free)
	{
		if (mem_struct->current_free_method)
			mem_struct->current_free_method(mem_struct->current_ptr);
		else
			ALIGNED_FREE(mem_struct->current_ptr);
	}
	
	
	if (mem_struct->new_free)
	{
		if (mem_struct->new_free_method)
			mem_struct->new_free_method(mem_struct->new_ptr);
		else
			ALIGNED_FREE(mem_struct->new_ptr);
	}
	
	mem_struct->current_ptr = 0;
	mem_struct->current_size = 0;
	mem_struct->current_free = 0;
	mem_struct->current_free_method = 0;
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
}


// Clear - this routine defers the freeing of memory so it should be thread-safe

static __inline void clear_mem_swap (t_safe_mem_swap *mem_struct)
{
	t_atom method_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_free)
	{
		atom_setsym(&method_ptr,(t_symbol *) mem_struct->current_free_method);
		defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->current_ptr, 1, &method_ptr);
	}
	
	if (mem_struct->new_free)
	{
		atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
		defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
	}
	
	mem_struct->current_ptr = 0;
	mem_struct->current_size = 0;
	mem_struct->current_free = 0;
	mem_struct->current_free_method = 0;
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Access and attempted swap routines - these routines are intended to pick up memory, but not allocate it


// Access - this routine will lock to get access to the memory struct and safely return the most recent useable values (either current or swap - BUT does not perform a swap)
// This routine can be used in any thread, and must be used if you are using grow_mem_swap to swap the memory anywhere in your code

static __inline void *access_mem_swap (t_safe_mem_swap *mem_struct, AH_UIntPtr *nom_size)
{
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->new_ptr)
	{
		*nom_size = mem_struct->new_size;
		return_ptr = mem_struct->new_ptr;
	}
	else
	{
		*nom_size = mem_struct->current_size;
		return_ptr = mem_struct->current_ptr;
	}
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


// Attempt - This non-blocking routine will attempt to swap the pointers but fail if the pointer is being altered
// Use this in one thread only (typically the audio thread)
// Returns 0 on no swap, 1 on swap and -1 on swap failed

static __inline t_swap_status attempt_mem_swap (t_safe_mem_swap *mem_struct)
{
	t_atom method_ptr;
	
	t_swap_status swap = SWAP_NONE;
	
	if (Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct->lock))
	{
		if (mem_struct->new_ptr)
		{
			if (mem_struct->current_free)
			{
				atom_setsym(&method_ptr,(t_symbol *) mem_struct->current_free_method);
				defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->current_ptr, 1, &method_ptr);
			}
			
			// Swap
			
			mem_struct->current_ptr				= mem_struct->new_ptr;
			mem_struct->current_size			= mem_struct->new_size;
			mem_struct->current_free			= mem_struct->new_free;
			mem_struct->current_free_method		= mem_struct->new_free_method;
			
			// Zero
			
			mem_struct->new_ptr				= 0;
			mem_struct->new_size			= 0;
			mem_struct->new_free			= 0;
			mem_struct->new_free_method		= 0;
			
			swap = SWAP_DONE;
		}
		
		// This should never fail as this thread has the lock
		
		Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	}
	else
		swap = SWAP_FAILED;
	
	return swap;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Re-allocation routines - these routines allow threadsafe re-allocation of memory


// Schedule Swap Pointer - this routine will lock to get access to the memory struct and place a given ptr and nominal size in the new slots
// This pointer will *NOT* be freed by the mem_swap routines
// This routine should only be called from max threads

static __inline void schedule_swap_mem_swap (t_safe_mem_swap *mem_struct, void *ptr, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->new_free)
	{
		atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
		defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
	}
	
	mem_struct->new_ptr = ptr;
	mem_struct->new_size = nom_size;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct->lock);
}


// Schedule Grow - this routine will lock to get access to the memory struct and allocate new memory if required, to be swapped in later
// This routine should only be called from max threads

static __inline void *schedule_grow_mem_swap (t_safe_mem_swap *mem_struct,  AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct->lock));
	
	if ((mem_struct->current_size < nom_size) && (mem_struct->new_size < nom_size))
	{
		if (mem_struct->new_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
		}
		
		mem_struct->new_ptr = return_ptr = ALIGNED_MALLOC(size);
		mem_struct->new_size = return_ptr ? nom_size: 0;
		mem_struct->new_free = 1;
		mem_struct->new_free_method = 0;
	}
	else
	{
		if (mem_struct->new_size >= nom_size)
			return_ptr = mem_struct->new_ptr;
		else
			return_ptr = mem_struct->current_ptr;
	}
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


// Schedule Equal - This routine will lock to get access to the memory struct and allocate new memory unless the sizes are equal, placing the memory in the new slots
// This routine should only be called from max threads

static __inline void *schedule_equal_mem_swap (t_safe_mem_swap *mem_struct,  AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_size == nom_size)
	{
		if (mem_struct->new_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
		}
		
		mem_struct->new_ptr = 0;
		mem_struct->new_size = 0;
		mem_struct->new_free = 0;
		mem_struct->new_free_method = 0;
		
		return_ptr = mem_struct->current_ptr;
	}
	else
	{
		if (mem_struct->new_size != nom_size)
		{
			if (mem_struct->new_free)
			{
				atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
				defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
			}
			
			mem_struct->new_ptr = return_ptr = ALIGNED_MALLOC(size);
			mem_struct->new_size = return_ptr ? nom_size: 0;
			mem_struct->new_free = 1;
			mem_struct->new_free_method = 0;
		}
		else
			return_ptr = mem_struct->new_ptr;
	}
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


// Grow Immediate - this routine will lock to get access to the memory struct, and if necessary free the old memory and assign new memory - swapping pointers immediately
// This routine should only be called from max threads and must be used in combination with safe access (access_mem_swap)

static __inline void *grow_mem_swap (t_safe_mem_swap *mem_struct,  AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_size < nom_size)
	{
		if (mem_struct->current_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->current_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->current_ptr, 1, &method_ptr);
		}
		
		if (mem_struct->new_size < nom_size)
		{
			if (mem_struct->new_free)
			{
				atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
				defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
			}
			
			mem_struct->current_ptr = ALIGNED_MALLOC(size);
			mem_struct->current_size = mem_struct->current_ptr ? nom_size : 0;
			mem_struct->current_free = 1;
			mem_struct->current_free_method = 0;
		}
		else
		{
			mem_struct->current_ptr = mem_struct->new_ptr;
			mem_struct->current_size = mem_struct->new_size;
			mem_struct->current_free = mem_struct->new_free;
			mem_struct->current_free_method = mem_struct->new_free_method;
		}
	}
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	return_ptr = mem_struct->current_ptr;
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Custom allocation and reallocation functions


// Alloc Custom - you should only call this from the new routine to be thread-safe

static __inline long alloc_mem_swap_custom (t_safe_mem_swap *mem_struct, alloc_method alloc_method_ptr, free_method free_method_ptr, AH_UIntPtr size, AH_UIntPtr nom_size)
{
	long fail = 0;
	
	mem_struct-> lock = 0;
	
	if (size)
		mem_struct->current_ptr = alloc_method_ptr(size, nom_size);
	else
		mem_struct->current_ptr = 0;
	
	if (size && mem_struct->current_ptr)
	{
		mem_struct->current_size = nom_size;
		mem_struct->current_free = 1;
		mem_struct->current_free_method = free_method_ptr;
	}
	else
	{
		mem_struct->current_size = 0;
		mem_struct->current_free = 0;
		mem_struct->current_free_method = 0;
		
		if (size)
			fail = 1;
	}
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	return fail;
}


// This routine will lock to get access to the memory struct and allocate new memory if required
// This routine should only be called from max threads

static __inline void *schedule_grow_mem_swap_custom (t_safe_mem_swap *mem_struct, alloc_method alloc_method_ptr, free_method free_method_ptr, AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if ((mem_struct->current_size < nom_size) && (mem_struct->new_size < nom_size))
	{
		if (mem_struct->new_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
		}
		
		mem_struct->new_ptr = return_ptr = alloc_method_ptr(size, nom_size);
		mem_struct->new_size = return_ptr ? nom_size: 0;
		mem_struct->new_free = 1;
		mem_struct->new_free_method = free_method_ptr;
	}
	else
	{
		if (mem_struct->new_size >= nom_size)
			return_ptr = mem_struct->new_ptr;
		else
			return_ptr = mem_struct->current_ptr;
	}
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


// This routine will lock to get access to the memory struct and allocate new memory unless the sizes are equal
// This routine should only be called from max threads

static __inline void *schedule_equal_mem_swap_custom (t_safe_mem_swap *mem_struct, alloc_method alloc_method_ptr, free_method free_method_ptr,  AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_size == nom_size)
	{
		if (mem_struct->new_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
		}
		
		mem_struct->new_ptr = 0;
		mem_struct->new_size = 0;
		mem_struct->new_free = 0;
		mem_struct->new_free_method = 0;
		
		return_ptr = mem_struct->current_ptr;
	}
	else
	{
		if (mem_struct->new_size != nom_size)
		{
			if (mem_struct->new_free)
			{
				atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
				defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
			}
			
			mem_struct->new_ptr = return_ptr = alloc_method_ptr(size, nom_size);
			mem_struct->new_size = return_ptr ? nom_size: 0;
			mem_struct->new_free = 1;
			mem_struct->new_free_method = free_method_ptr;
		}
		else
			return_ptr = mem_struct->new_ptr;
	}
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}


// This routine will lock to get access to the memory struct, freeing the old memory and assigning new memory
// This routine should only be called from max threads and must be used in combination with safe access (access_mem_swap)

static __inline void *grow_mem_swap_custom (t_safe_mem_swap *mem_struct, alloc_method alloc_method_ptr, free_method free_method_ptr, AH_UIntPtr size, AH_UIntPtr nom_size)
{
	t_atom method_ptr;
	
	void *return_ptr;
	
	// Spin on the lock
	
	while (!Atomic_Compare_And_Swap_Barrier(0, 1, &mem_struct-> lock));
	
	if (mem_struct->current_size < nom_size)
	{
		if (mem_struct->current_free)
		{
			atom_setsym(&method_ptr,(t_symbol *) mem_struct->current_free_method);
			defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->current_ptr, 1, &method_ptr);
		}
		
		if (mem_struct->new_size < nom_size)
		{
			if (mem_struct->new_free)
			{
				atom_setsym(&method_ptr,(t_symbol *) mem_struct->new_free_method);
				defer_low(0, (method)free_temp_mem_swap, (t_symbol *) mem_struct->new_ptr, 1, &method_ptr);
			}
			
			mem_struct->current_ptr = alloc_method_ptr(size, nom_size);
			mem_struct->current_size = mem_struct->current_ptr ? nom_size : 0;
			mem_struct->current_free = 1;
			mem_struct->current_free_method = free_method_ptr;
		}
		else
		{
			mem_struct->current_ptr = mem_struct->new_ptr;
			mem_struct->current_size = mem_struct->new_size;
			mem_struct->current_free = mem_struct->new_free;
			mem_struct->current_free_method = mem_struct->new_free_method;
		}
	}
	
	mem_struct->new_ptr = 0;
	mem_struct->new_size = 0;
	mem_struct->new_free = 0;
	mem_struct->new_free_method = 0;
	
	return_ptr = mem_struct->current_ptr;
	
	// This should never fail as this thread has the lock
	
	Atomic_Compare_And_Swap_Barrier(1, 0, &mem_struct-> lock);
	
	return return_ptr;
}




#endif		/* DEF_AH_HEADERS	*/