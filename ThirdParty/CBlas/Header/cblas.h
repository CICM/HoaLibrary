/* cblas.h
 *
 * This header defines C bindings for the Basic Linear Algebra Subprograms,
 * providing optimized basic operations on vectors and matrices.  Single-
 * and double-precision, real and complex data formats are supported by this
 * library.
 *
 * A note on complex data layouts:
 *
 * In order to allow straightforward interoperation with other libraries and
 * complex types in C and C++, complex data in BLAS is passed through an opaque
 * pointer (void *).  The layout requirements on this complex data are that
 * the real and imaginary parts are stored consecutively in memory, and have
 * the alignment of the corresponding real type (float or double).  The BLAS
 * complex interfaces are compatible with the following types:
 *
 *     - The C complex types, defined in <complex.h>.
 *     - The C++ std::complex types, defined in <complex>.
 *     - The LAPACK complex types, defined in <Accelerate/vecLib/clapack.h>.
 *     - The vDSP types DSPComplex and DSPDoubleComplex, defined in <Accelerate/vecLib/vDSP.h>.
 *     - An array of size two of the corresponding real type.
 *     - A structure containing two elements, each of the corresponding real type.
 * 
 */
 
#ifndef CBLAS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef CBLAS_ENUM_DEFINED_H
#define CBLAS_ENUM_DEFINED_H
enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102 };
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113,
	AtlasConj=114};
enum CBLAS_UPLO  {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG  {CblasNonUnit=131, CblasUnit=132};
enum CBLAS_SIDE  {CblasLeft=141, CblasRight=142};
#endif  /* CBLAS_ENUM_DEFINED_H */

#ifndef CBLAS_ENUM_ONLY
#define CBLAS_H
#define CBLAS_INDEX int

#include <Availability.h>

int cblas_errprn(int ierr, int info, char *form, ...) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_xerbla(int p, char *rout, char *form, ...) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS functions (complex are recast as routines)
 * ===========================================================================
 */
float  cblas_sdsdot(const int N, const float alpha, const float *X,
                    const int incX, const float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
double cblas_dsdot(const int N, const float *X, const int incX, const float *Y,
                   const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
float  cblas_sdot(const int N, const float  *X, const int incX,
                  const float  *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
double cblas_ddot(const int N, const double *X, const int incX,
                  const double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
/*
 * Functions having prefixes Z and C only
 */
void   cblas_cdotu_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotu) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void   cblas_cdotc_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void   cblas_zdotu_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotu) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void   cblas_zdotc_sub(const int N, const void *X, const int incX,
                       const void *Y, const int incY, void *dotc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Functions having prefixes S D SC DZ
 */
float  cblas_snrm2(const int N, const float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
float  cblas_sasum(const int N, const float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

double cblas_dnrm2(const int N, const double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
double cblas_dasum(const int N, const double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

float  cblas_scnrm2(const int N, const void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
float  cblas_scasum(const int N, const void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

double cblas_dznrm2(const int N, const void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
double cblas_dzasum(const int N, const void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Functions having standard 4 prefixes (S D C Z)
 */
CBLAS_INDEX cblas_isamax(const int N, const float  *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
CBLAS_INDEX cblas_idamax(const int N, const double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
CBLAS_INDEX cblas_icamax(const int N, const void   *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
CBLAS_INDEX cblas_izamax(const int N, const void   *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS routines
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (s, d, c, z)
 */
void cblas_sswap(const int N, float *X, const int incX,
                 float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_scopy(const int N, const float *X, const int incX,
                 float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_saxpy(const int N, const float alpha, const float *X,
                 const int incX, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_saxpby(const int N, const float alpha, const float *X,
				   const int incX, const float beta, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_sset
(const int N, const float alpha, float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_dswap(const int N, double *X, const int incX,
                 double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dcopy(const int N, const double *X, const int incX,
                 double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_daxpy(const int N, const double alpha, const double *X,
                 const int incX, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_daxpby(const int N, const double alpha, const double *X,
				   const int incX, const double beta, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_dset
(const int N, const double alpha, double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_cswap(const int N, void *X, const int incX,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ccopy(const int N, const void *X, const int incX,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_caxpy(const int N, const void *alpha, const void *X,
                 const int incX, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_caxpby(const int N, const void *alpha, const void *X,
				   const int incX, const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_cset
(const int N, const void *alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_zswap(const int N, void *X, const int incX,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zcopy(const int N, const void *X, const int incX,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zaxpy(const int N, const void *alpha, const void *X,
                 const int incX, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_zaxpby(const int N, const void *alpha, const void *X,
				   const int incX, const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void catlas_zset
(const int N, const void *alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Routines with S and D prefix only
 */
void cblas_srotg(float *a, float *b, float *c, float *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_srotmg(float *d1, float *d2, float *b1, const float b2, float *P) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_srot(const int N, float *X, const int incX,
                float *Y, const int incY, const float c, const float s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_srotm(const int N, float *X, const int incX,
				 float *Y, const int incY, const float *P) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_drotg(double *a, double *b, double *c, double *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_drotmg(double *d1, double *d2, double *b1, const double b2, double *P) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_drot(const int N, double *X, const int incX,
                double *Y, const int incY, const double c, const double s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_drotm(const int N, double *X, const int incX,
				 double *Y, const int incY, const double *P) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Routines with S D C Z CS and ZD prefixes
 */
void cblas_sscal(const int N, const float alpha, float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dscal(const int N, const double alpha, double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cscal(const int N, const void *alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zscal(const int N, const void *alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_csscal(const int N, const float alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zdscal(const int N, const double alpha, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 * Extra reference routines provided by ATLAS, but not mandated by the standard
 */
void cblas_crotg(void *a, void *b, void *c, void *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zrotg(void *a, void *b, void *c, void *s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_csrot(const int N, void *X, const int incX, void *Y, const int incY,
                 const float c, const float s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zdrot(const int N, void *X, const int incX, void *Y, const int incY,
                 const double c, const double s) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 * ===========================================================================
 * Prototypes for level 2 BLAS
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
void cblas_sgemv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const float alpha, const float *A, const int lda,
                 const float *X, const int incX, const float beta,
                 float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_sgbmv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const float alpha,
                 const float *A, const int lda, const float *X,
                 const int incX, const float beta, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_strmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const float *A, const int lda,
                 float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_stbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const float *A, const int lda,
                 float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_stpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const float *Ap, float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_strsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const float *A, const int lda, float *X,
                 const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_stbsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const float *A, const int lda,
                 float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_stpsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const float *Ap, float *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_dgemv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 const double *X, const int incX, const double beta,
                 double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dgbmv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const double alpha,
                 const double *A, const int lda, const double *X,
                 const int incX, const double beta, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtrmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *A, const int lda,
                 double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const double *A, const int lda,
                 double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *Ap, double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtrsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *A, const int lda, double *X,
                 const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtbsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const double *A, const int lda,
                 double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtpsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *Ap, double *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_cgemv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *X, const int incX, const void *beta,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cgbmv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const void *alpha,
                 const void *A, const int lda, const void *X,
                 const int incX, const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctrmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctrsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda, void *X,
                 const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctbsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctpsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_zgemv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *X, const int incX, const void *beta,
                 void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zgbmv(const enum CBLAS_ORDER Order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const int KL, const int KU, const void *alpha,
                 const void *A, const int lda, const void *X,
                 const int incX, const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztrmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztrsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *A, const int lda, void *X,
                 const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztbsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const int K, const void *A, const int lda,
                 void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztpsv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const void *Ap, void *X, const int incX) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Routines with S and D prefixes only
 */
void cblas_ssymv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const float alpha, const float *A,
                 const int lda, const float *X, const int incX,
                 const float beta, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const float alpha, const float *A,
                 const int lda, const float *X, const int incX,
                 const float beta, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_sspmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const float alpha, const float *Ap,
                 const float *X, const int incX,
                 const float beta, float *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_sger(const enum CBLAS_ORDER Order, const int M, const int N,
                const float alpha, const float *X, const int incX,
                const float *Y, const int incY, float *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssyr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const float alpha, const float *X,
                const int incX, float *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_sspr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const float alpha, const float *X,
                const int incX, float *Ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssyr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
				 const int N, const float alpha, const float *X,
				 const int incX, const float *Y, const int incY, float *A,
				 const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_sspr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
				 const int N, const float alpha, const float *X,
				 const int incX, const float *Y, const int incY, float *A) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_dsymv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const double alpha, const double *A,
                 const int lda, const double *X, const int incX,
                 const double beta, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const double alpha, const double *A,
                 const int lda, const double *X, const int incX,
                 const double beta, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dspmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const double alpha, const double *Ap,
                 const double *X, const int incX,
                 const double beta, double *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dger(const enum CBLAS_ORDER Order, const int M, const int N,
                const double alpha, const double *X, const int incX,
                const double *Y, const int incY, double *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsyr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, double *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dspr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const double *X,
                const int incX, double *Ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsyr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
				 const int N, const double alpha, const double *X,
				 const int incX, const double *Y, const int incY, double *A,
				 const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dspr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
				 const int N, const double alpha, const double *X,
				 const int incX, const double *Y, const int incY, double *A) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Routines with C and Z prefixes only
 */
void cblas_chemv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_chbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_chpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *Ap,
                 const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cgeru(const enum CBLAS_ORDER Order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cgerc(const enum CBLAS_ORDER Order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cher(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const float alpha, const void *X, const int incX,
                void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_chpr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const float alpha, const void *X,
                const int incX, void *A) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cher2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo, const int N,
				 const void *alpha, const void *X, const int incX,
				 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_chpr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo, const int N,
				 const void *alpha, const void *X, const int incX,
				 const void *Y, const int incY, void *Ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_zhemv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zhbmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const int K, const void *alpha, const void *A,
                 const int lda, const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zhpmv(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const int N, const void *alpha, const void *Ap,
                 const void *X, const int incX,
                 const void *beta, void *Y, const int incY) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zgeru(const enum CBLAS_ORDER Order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zgerc(const enum CBLAS_ORDER Order, const int M, const int N,
                 const void *alpha, const void *X, const int incX,
                 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zher(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const void *X, const int incX,
                void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zhpr(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                const int N, const double alpha, const void *X,
                const int incX, void *A) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zher2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo, const int N,
				 const void *alpha, const void *X, const int incX,
				 const void *Y, const int incY, void *A, const int lda) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zhpr2(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo, const int N,
				 const void *alpha, const void *X, const int incX,
				 const void *Y, const int incY, void *Ap) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 * ===========================================================================
 * Prototypes for level 3 BLAS
 * ===========================================================================
 */

/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */
void cblas_sgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const float alpha, const float *A,
                 const int lda, const float *B, const int ldb,
                 const float beta, float *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const float alpha, const float *A, const int lda,
                 const float *B, const int ldb, const float beta,
                 float *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const float alpha, const float *A, const int lda,
                 const float beta, float *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ssyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const float alpha, const float *A, const int lda,
                  const float *B, const int ldb, const float beta,
                  float *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_strmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const float alpha, const float *A, const int lda,
                 float *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_strsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const float alpha, const float *A, const int lda,
                 float *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_dgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const double alpha, const double *A,
                 const int lda, const double *B, const int ldb,
                 const double beta, double *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 const double *B, const int ldb, const double beta,
                 double *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const double alpha, const double *A, const int lda,
                 const double beta, double *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const double alpha, const double *A, const int lda,
                  const double *B, const int ldb, const double beta,
                  double *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 double *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_dtrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 double *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_cgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const void *alpha, const void *A,
                 const int lda, const void *B, const int ldb,
                 const void *beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_csymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_csyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const void *alpha, const void *A, const int lda,
                 const void *beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_csyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const void *beta,
                  void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ctrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

void cblas_zgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const void *alpha, const void *A,
                 const int lda, const void *B, const int ldb,
                 const void *beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const void *alpha, const void *A, const int lda,
                 const void *beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const void *beta,
                  void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_ztrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 void *B, const int ldb) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);


/*
 * Routines with prefixes C and Z only
 */
void cblas_chemm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cherk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const float alpha, const void *A, const int lda,
                 const float beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_cher2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const float beta,
                  void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zhemm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                 const void *B, const int ldb, const void *beta,
                 void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zherk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const double alpha, const void *A, const int lda,
                 const double beta, void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
void cblas_zher2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                  const void *alpha, const void *A, const int lda,
                  const void *B, const int ldb, const double beta,
                  void *C, const int ldc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);

/*
 Apple extensions follow.
 */

/*
 Historically, the ATLAS-based BLAS in OS X allocated thread-local temp
 buffers, and this routine existed to free that memory.  The Apple BLAS
 is no longer based on ATLAS, and there are no scratch buffers to release,
 so this routine has been deprecated.  It has been a no-op since OS X
 10.7, and calls to it may be safely removed.
 
 On iOS, this routine has never done anything, so there is no risk in removing
 these calls.
 */

extern void ATLU_DestroyThreadMemory() __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2, __MAC_10_9, __IPHONE_4_0, __IPHONE_NA);

/*
 -------------------------------------------------------------------------------------------------
 The BLAS standard requires that parameter errors be reported and cause the program to terminate.
 The default behavior for the Mac OS implementation of the BLAS is to print a message in English
 to stdout using printf and call exit with EXIT_FAILURE as the status.  If this is adequate, then
 you need do nothing more or worry about error handling.
 The BLAS standard also mentions a function, cblas_xerbla, suggesting that a program provide its
 own implementation to override the default error handling.  This will not work in the shared
 library environment of Mac OS.  Instead the Mac OS implementation provides a means to install
 an error handler.  There can only be one active error handler, installing a new one causes any
 previous handler to be forgotten.  Passing a null function pointer installs the default handler.
 The default handler is automatically installed at startup and implements the default behavior
 defined above.
 An error handler may return, it need not abort the program.  If the error handler returns, the
 BLAS routine also returns immediately without performing any processing.  Level 1 functions that
 return a numeric value return zero if the error handler returns.
 -------------------------------------------------------------------------------------------------
 */

typedef void (*BLASParamErrorProc)(const char *funcName, const char *paramName,
                                   const int *paramPos,  const int *paramValue);
void SetBLASParamErrorProc(BLASParamErrorProc ErrorProc) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_4_0);
    
#if defined __SSE__
    
    typedef float __M128  __attribute__((vector_size (16)));
    typedef __M128  VectorFloat;
    typedef VectorFloat ConstVectorFloat;
    
    /*
     -------------------------------------------------------------------------------------------------
     These routines provide optimized, SIMD-only support for common small matrix multiplications.
     They do not check for the availability of SIMD instructions or parameter errors.  They just do
     the multiplication as fast as possible.  Matrices are presumed to use row major storage.  Because
     these are all square, column major matrices can be multiplied by simply reversing the parameters.
     -------------------------------------------------------------------------------------------------
     */
    
    void vMultVecMat_4x4(ConstVectorFloat X[1], ConstVectorFloat A[4][1], VectorFloat Y[1]);
    void vMultMatVec_4x4(ConstVectorFloat A[4][1], ConstVectorFloat X[1], VectorFloat Y[1]);
    void vMultMatMat_4x4(ConstVectorFloat A[4][1], ConstVectorFloat   B[4][1], VectorFloat C[4][1]);
    void vMultVecMat_8x8(ConstVectorFloat X[2], ConstVectorFloat A[8][2], VectorFloat Y[2]);
    void vMultMatVec_8x8(ConstVectorFloat A[8][2], ConstVectorFloat X[2], VectorFloat Y[2]);
    void vMultMatMat_8x8(ConstVectorFloat A[8][2], ConstVectorFloat   B[8][2], VectorFloat C[8][2]);
    void vMultVecMat_16x16(ConstVectorFloat X[4], ConstVectorFloat A[16][4], VectorFloat Y[4]);
    void vMultMatVec_16x16(ConstVectorFloat A[16][4], ConstVectorFloat X[4], VectorFloat Y[4]);
    void vMultMatMat_16x16(ConstVectorFloat A[16][4], ConstVectorFloat   B[16][4], VectorFloat C[16][4]);
    void vMultVecMat_32x32(ConstVectorFloat X[8], ConstVectorFloat A[32][8], VectorFloat Y[8]);
    void vMultMatVec_32x32(ConstVectorFloat A[32][8], ConstVectorFloat X[8], VectorFloat Y[8]);
    void vMultMatMat_32x32(ConstVectorFloat A[32][8], ConstVectorFloat   B[32][8], VectorFloat C[32][8]);
    
    /*
     -------------------------------------------------------------------------------------------------
     These routines provide optimized support for common small matrix multiplications. They use
     the scalar floating point unit and have no dependancy on SIMD instructions. They are intended
     as complements to the AltiVec-only routines above. They do not check for parameter errors.  They just do
     the multiplication as fast as possible.  Matrices are presumed to use row major storage.  Because
     these are all square, column major matrices can be multiplied by simply reversing the parameters.
     -------------------------------------------------------------------------------------------------
     */
    
    void sMultVecMat_4x4(ConstVectorFloat X[1], ConstVectorFloat A[4][1], VectorFloat Y[1]);
    void sMultMatVec_4x4(ConstVectorFloat A[4][1], ConstVectorFloat X[1], VectorFloat Y[1]);
    void sMultMatMat_4x4(ConstVectorFloat A[4][1], ConstVectorFloat   B[4][1], VectorFloat C[4][1]);
    void sMultVecMat_8x8(ConstVectorFloat X[2], ConstVectorFloat A[8][2], VectorFloat Y[2]);
    void sMultMatVec_8x8(ConstVectorFloat A[8][2], ConstVectorFloat X[2], VectorFloat Y[2]);
    void sMultMatMat_8x8(ConstVectorFloat A[8][2], ConstVectorFloat   B[8][2], VectorFloat C[8][2]);
    void sMultVecMat_16x16(ConstVectorFloat X[4], ConstVectorFloat A[16][4], VectorFloat Y[4]);
    void sMultMatVec_16x16(ConstVectorFloat A[16][4], ConstVectorFloat X[4], VectorFloat Y[4]);
    void sMultMatMat_16x16(ConstVectorFloat A[16][4], ConstVectorFloat   B[16][4], VectorFloat C[16][4]);
    void sMultVecMat_32x32(ConstVectorFloat X[8], ConstVectorFloat A[32][8], VectorFloat Y[8]);
    void sMultMatVec_32x32(ConstVectorFloat A[32][8], ConstVectorFloat X[8], VectorFloat Y[8]);
    void sMultMatMat_32x32(ConstVectorFloat A[32][8], ConstVectorFloat   B[32][8], VectorFloat C[32][8]);
    
    void dMultVecMat_4x4(const double X[4], const double A[4][4], double Y[4]);
    void dMultMatVec_4x4(const double A[4][4], const double X[4], double Y[4]);
    void dMultMatMat_4x4(const double A[4][4], const double B[4][4], double C[4][4]);
    void dMultVecMat_8x8(const double X[8], const double A[8][8], double Y[8]);
    void dMultMatVec_8x8(const double A[8][8], const double X[8], double Y[8]);
    void dMultMatMat_8x8(const double A[8][8], const double B[8][8], double C[8][8]);
    void dMultVecMat_16x16(const double X[16], const double A[16][16], double Y[16]);
    void dMultMatVec_16x16(const double A[16][16], const double X[16], double Y[16]);
    void dMultMatMat_16x16(const double A[16][16], const double B[16][16], double C[16][16]);
    void dMultVecMat_32x32(const double X[32], const double A[32][32], double Y[32]);
    void dMultMatVec_32x32(const double A[32][32], const double X[32], double Y[32]);
    void dMultMatMat_32x32(const double A[32][32], const double B[32][32], double C[32][32]);
    
#endif /* defined __SSE__ */
#endif /* CBLAS_ENUM_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* CBLAS_H */
