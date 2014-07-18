#ifndef OPENBLAS_CONFIG_H
#define OPENBLAS_CONFIG_H
#define OS_LINUX	1
#define ARCH_X86_64	1
#define C_GCC	1
#define __64BIT__	1
#define PTHREAD_CREATE_FUNC	pthread_create
#define BUNDERSCORE	_
#define NEEDBUNDERSCORE	1
#define SANDYBRIDGE
#define L2_SIZE 262144
#define L2_ASSOCIATIVE 6
#define L2_LINESIZE 64
#define ITB_SIZE 4096
#define ITB_ASSOCIATIVE 4
#define ITB_ENTRIES 64
#define DTB_SIZE 4096
#define DTB_ASSOCIATIVE 4
#define DTB_DEFAULT_ENTRIES 64
#define HAVE_CMOV
#define HAVE_MMX
#define HAVE_SSE
#define HAVE_SSE2
#define HAVE_SSE3
#define HAVE_SSSE3
#define HAVE_SSE4_1
#define HAVE_SSE4_2
#define HAVE_AVX
#define HAVE_CFLUSH
#define NUM_SHAREDCACHE 1
#define NUM_CORES 1
#define CORE_SANDYBRIDGE
#define SLOCAL_BUFFER_SIZE	32768
#define DLOCAL_BUFFER_SIZE	16384
#define CLOCAL_BUFFER_SIZE	32768
#define ZLOCAL_BUFFER_SIZE	24576
#define GEMM_MULTITHREAD_THRESHOLD	4
#define EXPRECISION
#define VERSION " OpenBLAS 0.2.8 "
/*This is only for "make install" target.*/

#if defined(OS_WINNT) || defined(OS_CYGWIN_NT) || defined(OS_INTERIX)
#define WINDOWS_ABI
#define OS_WINDOWS

#ifdef DOUBLE
#define DOUBLE_DEFINED DOUBLE
#undef  DOUBLE
#endif
#endif

#ifdef NEEDBUNDERSCORE
#define BLASFUNC(FUNC) FUNC##_
#else
#define BLASFUNC(FUNC) FUNC
#endif

#ifdef QUAD_PRECISION
typedef struct {
  unsigned long x[2];
}  xdouble;
#elif defined EXPRECISION
#define xdouble long double
#else
#define xdouble double
#endif

#if defined(OS_WINDOWS) && defined(__64BIT__)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef USE64BITINT
typedef BLASLONG blasint;
#else
typedef int blasint;
#endif

#if defined(XDOUBLE) || defined(DOUBLE)
#define FLOATRET	FLOAT
#else
#ifdef NEED_F2CCONV
#define FLOATRET	double
#else
#define FLOATRET	float
#endif
#endif

/* Inclusion of a standard header file is needed for definition of __STDC_*
   predefined macros with some compilers (e.g. GCC 4.7 on Linux).  This occurs
   as a side effect of including either <features.h> or <stdc-predef.h>. */
#include <stdio.h>

/* C99 supports complex floating numbers natively, which GCC also offers as an
   extension since version 3.0.  If neither are available, use a compatible
   structure as fallback (see Clause 6.2.5.13 of the C99 standard). */
#if (defined(__STDC_IEC_559_COMPLEX__) || __STDC_VERSION__ >= 199901L || \
     (__GNUC__ >= 3 && !defined(__cplusplus)))
  #define OPENBLAS_COMPLEX_C99
#ifndef __cplusplus
  #include <complex.h>
#endif
  typedef float _Complex openblas_complex_float;
  typedef double _Complex openblas_complex_double;
  typedef xdouble _Complex openblas_complex_xdouble;
  #define openblas_make_complex_float(real, imag)    ((real) + ((imag) * _Complex_I))
  #define openblas_make_complex_double(real, imag)   ((real) + ((imag) * _Complex_I))
  #define openblas_make_complex_xdouble(real, imag)  ((real) + ((imag) * _Complex_I))
  #define openblas_complex_float_real(z)             (creal(z))
  #define openblas_complex_float_imag(z)             (cimag(z))
  #define openblas_complex_double_real(z)            (creal(z))
  #define openblas_complex_double_imag(z)            (cimag(z))
  #define openblas_complex_xdouble_real(z)           (creal(z))
  #define openblas_complex_xdouble_imag(z)           (cimag(z))
#else
  #define OPENBLAS_COMPLEX_STRUCT
  typedef struct { float real, imag; } openblas_complex_float;
  typedef struct { double real, imag; } openblas_complex_double;
  typedef struct { xdouble real, imag; } openblas_complex_xdouble;
  #define openblas_make_complex_float(real, imag)    {(real), (imag)}
  #define openblas_make_complex_double(real, imag)   {(real), (imag)}
  #define openblas_make_complex_xdouble(real, imag)  {(real), (imag)}
  #define openblas_complex_float_real(z)             ((z).real)
  #define openblas_complex_float_imag(z)             ((z).imag)
  #define openblas_complex_double_real(z)            ((z).real)
  #define openblas_complex_double_imag(z)            ((z).imag)
  #define openblas_complex_xdouble_real(z)           ((z).real)
  #define openblas_complex_xdouble_imag(z)           ((z).imag)
#endif
#endif /* OPENBLAS_CONFIG_H */
