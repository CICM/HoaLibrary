/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define CICM_VDSP
#define CICM_FLOAT
//#define CICM_FFTW_GSL
//#define CICM_IPPS

//#define CICM_DOUBLE

#ifndef DEF_CICM_DEFINE
#define DEF_CICM_DEFINE

#ifdef CICM_VDSP

#include <Accelerate/Accelerate.h>

#ifdef CICM_FLOAT

#define Cicm_Float float
#define Cicm_Vector_Float  float*
#define Cicm_Matrix_Float  float*

#define Cicm_Double double
#define Cicm_Vector_Double  double*
#define Cicm_Matrix_Double  double*

#define Cicm_Complex_Float DSPComplex
#define Cicm_Complex_Packed_Float DSPSplitComplex
#define Cicm_Fft_Handle FFTSetup

#define Cicm_Complex_Double DSPComplexD
#define Cicm_Complex_Packed_Double DSPSplitComplexD

/**************** ALLOCATION *****************/
#define	Cicm_Vector_Float_Malloc(vector, size) vector = (Cicm_Vector_Float)calloc(size, sizeof(Cicm_Float))
#define	Cicm_Vector_Double_Malloc(vector, size) vector = (Cicm_Vector_Double)calloc(size, sizeof(Cicm_Double))

#define	Cicm_Matrix_Float_Malloc(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Float)calloc(number_of_rows * columns_size, sizeof(Cicm_Float) );
#define	Cicm_Matrix_Double_Malloc(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Double)calloc(number_of_rows * columns_size, sizeof(Cicm_Double));

#define	Cicm_Complex_Packed_Float_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Float *)malloc(sizeof(Cicm_Complex_Packed_Float)); packedComplex[0].realp = (Cicm_Vector_Float)malloc(size * sizeof(Cicm_Float)); packedComplex[0].imagp = (Cicm_Vector_Float)malloc(size * sizeof(Cicm_Float));

#define	Cicm_Complex_Packed_Double_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Double *)malloc(sizeof(Cicm_Complex_Packed_Double)); packedComplex[0].realp = (Cicm_Vector_Double)malloc(size * sizeof(Cicm_Double)); packedComplex[0].imagp = (Cicm__Vector_Double *)malloc(size * sizeof(Cicm_Double));

/**************** FREE *****************/
#define Cicm_Free(pointor) free(pointor); pointor = NULL;
#define Cicm_Free_Complex_Packed(vector) free(vector[0].realp); free(vector[0].imagp);

/**************** SET ******************/
#define Cicm_Matrix_Float_Set(matrix, i, j, column_size, value) matrix[i * column_size + j] = value
#define Cicm_Matrix_Double_Set(matrix, i, j, column_size, value) matrix[i * column_size + j] = value

/**************** COPY *****************/
#define Cicm_Vector_Float_Copy(vectorSource, vectorDest, size) vDSP_mmov(vectorSource, vectorDest, size, 1, size, size)
#define Cicm_Vector_Double_Copy(vectorSource, vectorDest, size) vDSP_mmovD(vectorSource, vectorDest, size, 1, size, size)

#define Cicm_Vector_Matrix_Float_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmov(vectorSource, matrixDest+ row_number * size, size, 1, size, size)
#define Cicm_Vector_Matrix_Double_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmovD(vectorSource, matrixDest+row_number * size, size, 1, size, size)

#define Cicm_Matrix_Vector_Float_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmov(matrixSource+row_number * size, vectorDest, size, 1, size, size)
#define Cicm_Matrix_Vector_Double_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmovD(matrixSource+row_number * size, vectorDest, size, 1, size, size)

/**************** PRODUCT *************/
#define Cicm_Matrix_Vector_Float_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) cblas_sgemv(CblasRowMajor, CblasNoTrans, number_of_rows, column_size, 1.f, matrix, column_size, vectorSource, 1, 0.f, vectorDest, 1)
#define Cicm_Matrix_Vector_Double_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) cblas_dgemv(CblasRowMajor, CblasNoTrans, number_of_rows, column_size, 1., matrix, column_size, vectorSource, 1, 0., vectorDest, 1)

#define Cicm_Matrix_Matrix_Float_Product(matrixOne, matrixTwo, matrixDest, number_of_rowsOne, column_sizetwo, column_sizeOne) cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rowsOne, column_sizetwo, column_sizeOne, 1.f, matrixOne, number_of_rowsOne, matrixTwo, number_of_rowsOne, 0.f, matrixDest, number_of_rowsOne);
#define Cicm_Matrix_Matrix_Double_Product(matrixOne, matrixTwo, matrixDest, number_of_rowsOne, column_sizetwo, column_sizeOne) cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rowsOne, column_sizetwo, column_sizeOne, 1., matrixOne, number_of_rowsOne, matrixTwo, column_sizeOne, 0., matrixDest, column_sizetwo);

/**************** DOT PRODUCT *********/
#define Cicm_Vector_Float_Dot_Product(vectorOne, vectorTwo, scalarDest, size) vDSP_dotpr(vectorOne, 1, vectorTwo, 1, scalarDest, size)
#define Cicm_Vector_Double_Dot_Product(vectorOne, vectorTwo, scalarDest, size) vDSP_dotprD(vectorOne, 1, vectorTwo, 1, scalarDest, size)

/**************** MUL *****************/
#define Cicm_Matrix_Vector_Float_Mul(vectorOne, vectorTwo, vectorDest, size) vDSP_vmul(vectorOne, 1, vectorTwo, 1, vectorDest, 1, size);
#define Cicm_Matrix_Vector_Double_Mul(vectorOne, vectorTwo, vectorDest, size) vDSP_vmulD(vectorOne, 1, vectorTwo, 1, vectorDest, 1, size);

#define Cicm_Vector_Scalar_Float_Mul(vectorSource, scalar, vectorDest, size) vDSP_vsmul(vectorSource, 1, &scalar, vectorDest, 1, size)
#define Cicm_Vector_Scalar_Double_Mul(vectorSource, scalar, vectorDest, size) vDSP_vsmulD(vectorSource, 1, &scalar, vectorDest, 1, size)

#define Cicm_Vector_Vector_Float_Mul(vectorOne, vectorDest, size) cblas_sdot(size, vectorOne, 1, vectorDest, 1)
#define Cicm_Vector_Vector_Double_Mul(vectorOne, vectorDest, size) cblas_ddot(size, vectorOne, 1, vectorDest, 1)

/**************** ADD *****************/
#define Cicm_Vector_Float_Add(vectorOne, vectorDest, size) cblas_saxpy(size, 1.f, vectorOne, 1, vectorDest, 1)
#define Cicm_Vector_Double_Add(vectorOne, vectorDest, size) cblas_daxpy(size, 1., vectorOne, 1, vectorDest, 1)

/**************** SUM *****************/
#define Cicm_Vector_Float_Sum(source1, source2, dest, length) vDSP_vadd(source1, 1, source2, 1, dest, 1, length)
#define Cicm_Vector_Double_Sum(source1, source2, dest, length) vDSP_vaddD(source1, 1, source2, 1, dest, 1, length)

#define Cicm_Vector_Scalar_Float_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsadd(vectorSource, 1, scalar, vectorDest, 1, size);
#define Cicm_Vector_Scalar_Double_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsaddD(vectorSource, 1, scalar, vectorDest, 1, size);


/************* MUL AND ADD ************/

#define Cicm_Vector_Vector_Float_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) vDSP_vma(vectorOne, 1, vectorTwo, 1, vectorDest, 1, vectorDest, 1, size)
#define Cicm_Vector_Vector_Double_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) vDSP_vmaD(vectorOne, 1, vectorTwo, 1, vectorDest, 1, vectorDest, 1, size)

#define Cicm_Vector_Scalar_Float_Mul_And_Add(vectorOne, scalar, vectorDest, size) vDSP_vmsa(vectorOne, 1, vectorDest, 1, &scalar, vectorDest, 1, size);
#define Cicm_Vector_Scalar_Double_Mul_And_Add(vectorOne, scalar, vectorDest, size) vDSP_vmsaD(vectorOne, 1, vectorDest, 1, &scalar, vectorDest, 1, size);

/**************** CLIP  ***************/
#define Cicm_Vector_Float_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclip(vectorsource, 1, low, high, vectorDest, 1, size);
#define Cicm_Vector_Double_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclipD(vectorsource, 1, low, high, vectorDest, 1, size);

/**************** CLEAR ***************/
#define Cicm_Vector_Float_Clear(source, length) vDSP_vclr(source, 1, length)
#define Cicm_Vector_Double_Clear(source, length) vDSP_vclrD(source, 1, length)

/* Matrix Transpose */
 #define  Cicm_Matrix_Transpose_Float(matrixSource, matrixDest, rowDest, columnDest) vDSP_mtrans(&matrixSource[0][0], 1, &matrixDest[0][0], 1, rowDest, columnDest);
 
 #define  Cicm_Matrix_Transpose_Double(matrixSource, matrixDest, rowDest, columnDest) vDSP_mtransD(matrixSource, 1, matrixDest, 1, rowDest, columnDest);
/***/

#define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
#define	Cicm_free_packed(pointeur) free(pointeur[0].realp) free(pointeur[0].imagp)

#define Cicm_fft_free_handle vDSP_destroy_fftsetup

#define Cicm_packed_mul(source1, source2, dest, length) vDSP_zvmul(source1, 1, source2, 1, dest, 1, length, 1)
#define Cicm_packed_clear(source, length) vDSP_vclr(source[0].imagp, 1, length); vDSP_vclr(source[0].realp, 1, length);

#define Cicm_fft_forward(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
#define Cicm_fft_inverse(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)

/* Sinus and Cosinus */
#define Cicm_Vector_Float_Cosinus vvcosf
#define Cicm_Vector_Float_Sinus vvsinf
#define Cicm_Vector_Double_Cosinus vvcos
#define Cicm_Vector_Double_Sinus vvsin
#define Cicm_Vector_Float_SinCos(sinVector, cosVector, angleVector, size) vvsincosf(sinVector, cosVector, angleVector, &size)
#define Cicm_Vector_Double_SinCos(sinVector, cosVector, angleVector, size) vvsincos(sinVector, cosVector, angleVector, &size)

#endif

#ifdef CICM_DOUBLE

#define Cicm_Signal float
#define Cicm_Packed DSPSplitComplex
#define Cicm_Complex DSPComplex
#define Cicm_Fft_Handle FFTSetup

#define	Cicm_signal_malloc(pointeur, length) pointeur = (Cicm_Signal *)malloc(length * sizeof(Cicm_Signal))
#define	Cicm_packed_malloc(pointeur, length) pointeur.realp = (Cicm_Signal *)malloc(length * sizeof(Cicm_Signal)); pointeur.imagp = (Cicm_Signal *)malloc(length * sizeof(Cicm_Signal));

#define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
#define	Cicm_free free
#define Cicm_fft_free_handle vDSP_destroy_fftsetup

#define Cicm_signal_copy(source, dest, length) vDSP_mmov(source, dest, length, 1, length, length)
#define Cicm_signal_clear(source, length) vDSP_vclr(source, 1, length)
#define Cicm_packed_mul(source1, source2, dest, length) zvmul(source1, 1, source2, 1, dest, 1, length, 1) // a revoir
#define Cicm_signal_dot(source1, source2, dest, length) vDSP_dotpr(source1, 1, source2, 1, dest, length)
#define Cicm_signal_add(source1, source2, dest, length) vDSP_vadd(source1, 1, source2, 1, dest, 1, length)
#define Cicm_fft_forward(fft_handle, complex, order) fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
#define Cicm_fft_inverse(fft_handle, complex, order) fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)

#endif
#endif

#ifdef CICM_IPPS

#include <ipps.h>

#ifdef CICM_FLOAT

#define Cicm_Signal			Ipp32f
#define Cicm_Packed			Ipp32f
#define Cicm_Fft_Handle		IppsFFTSpec_R_32f
#define Cicm_Fft_Buffer		Ipp8u

#define	Cicm_signal_malloc(pointeur, length) pointeur = ippsMalloc_32f(length)
#define	Cicm_packed_malloc(pointeur, length) pointeur = ippsMalloc_32f(length)

#define	Cicm_buffer_malloc ippsMalloc_8u
#define	Cicm_free ippsFree

#define Cicm_signal_clear(source, length) ippsZero_32f(source, length)
#define Cicm_signal_add(source1, source2, dest, length) ippsAdd_32f(source1, source2, dest, length)
#define Cicm_signal_copy(source, dest, length) ippsCopy_32f(source, dest, length)
#define Cicm_signal_dot(source1, source2, dest, length) ippsDotProd_32f(source1, source2, length, dest)
#define Cicm_packed_mul(source1, source2, dest, length) ippsMulPack_32f(source1, source2, dest, length)

#define Cicm_fft_get_size(order, spectrumSize, initSize, bufferSize) ippsFFTGetSize_R_32f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectrumSize, initSize, bufferSize)
#define Cicm_fft_init_handle(handle, order, spectBuffer, initBuffer) ippsFFTInit_R_32f(handle, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectBuffer, initBuffer)
#define Cicm_fft_forward(signal, complex, fft_handle, buffer) ippsFFTFwd_RToPack_32f(signal, complex, fft_handle, buffer)
#define Cicm_fft_inverse(complex, dest, fft_handle, buffer) ippsFFTInv_PackToR_32f(complex, dest, fft_handle, buffer)
#define Cicm_fft_free_handle ippsFFTFree_R_32f
#endif

#ifdef CICM_DOUBLE

#define Cicm_Signal			Ipp64f
#define Cicm_Packed			Ipp64f
#define Cicm_Fft_Handle		IppsFFTSpec_R_64f
#define Cicm_Fft_Buffer		Ipp8u

#define	Cicm_signal_malloc(pointeur, length) pointeur = ippsMalloc_64f(length)
#define	Cicm_packed_malloc(pointeur, length) pointeur = ippsMalloc_64f(length)

#define	Cicm_buffer_malloc ippsMalloc_8u
#define	Cicm_free ippsFree

#define Cicm_signal_clear(source, length) ippsZero_64f(source, length)
#define Cicm_signal_add(source1, source2, dest, length) ippsAdd_64f(source1, source2, dest, length)
#define Cicm_signal_copy(source, dest, length) ippsCopy_64f(source, dest, length)
#define Cicm_signal_dot(source1, source2, dest, length) ippsDotProd_64f(source1, source2, length, dest)
#define Cicm_packed_mul(source1, source2, dest, length) ippsMulPack_64f(source1, source2, dest, length)

#define Cicm_fft_get_size(order, spectrumSize, initSize, bufferSize) ippsFFTGetSize_R_64f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectrumSize, initSize, bufferSize)
#define Cicm_fft_init_handle(handle, order, spectBuffer, initBuffer) ippsFFTInit_R_64f(handle, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectBuffer, initBuffer)
#define Cicm_fft_forward(signal, complex, fft_handle, buffer) ippsFFTFwd_RToPack_64f(signal, complex, fft_handle, buffer)
#define Cicm_fft_inverse(complex, dest, fft_handle, buffer) ippsFFTInv_PackToR_64f(complex, dest, fft_handle, buffer)
#define Cicm_fft_free_handle ippsFFTFree_R_64f
#endif
#endif

#ifdef CICM_FFTW_GSL

#include <fftw3.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#ifdef CICM_FLOAT
#include <fftw3.h>
static void packed_mul(float* x, float* y, float* out, long aLength)
{
	float a, b, c, d;
	long n = 2 * aLength;
	out[0] = x[0] * y[0];
	out[n/2] = x[n/2] * y[n/2];
	for (int j = 1; j < n/2; j++)
	{
        a = x[j];
        b = x[n - j];
        c = y[j];
        d = y[n - j];
        out[j] = a*c-b*d;
        out[n - j] = a*d+b*c;
	}
};

#define Cicm_Signal			float
#define Cicm_Packed			float
#define Cicm_Fft_Handle		fftwf_plan

#define	Cicm_signal_malloc(pointeur, length) pointeur = (Cicm_Signal *)malloc(length * sizeof(Cicm_Signal))
#define	Cicm_packed_malloc(pointeur, length) pointeur = (Cicm_Packed *)malloc(length * sizeof(Cicm_Packed))
#define	Cicm_free free

#define Cicm_signal_clear(source, length) gsl_vector_float_set_zero(&gsl_vector_float_view_array(source, length).vector)
#define Cicm_signal_add(source1, dest, none, length) gsl_vector_float_add(&gsl_vector_float_view_array(dest, length).vector,&gsl_vector_float_view_array(source1, length).vector)
#define Cicm_signal_copy(source, dest, length) gsl_vector_float_memcpy(&gsl_vector_float_view_array(dest, length).vector,&gsl_vector_float_view_array(source, length).vector)
#define Cicm_signal_dot(source1, source2, dest, length) double result; gsl_blas_dsdot(&gsl_vector_float_view_array(source1, length).vector, &gsl_vector_float_view_array(source2, length).vector, &result); *dest = result
#define Cicm_packed_mul(source1, source2, dest, length) packed_mul(source1, source2, dest, length)

#define Cicm_packed_clear(source, length) gsl_vector_float_set_zero(&gsl_vector_float_view_array(source, length).vector)

#define Cicm_fft_init_handle_forward(length, real, packed) fftwf_plan_r2r_1d(length, real, packed, FFTW_R2HC, FFTW_ESTIMATE)
#define Cicm_fft_init_handle_inverse(length, packed, real) fftwf_plan_r2r_1d(length, packed, real, FFTW_HC2R, FFTW_ESTIMATE)
#define Cicm_fft_forward fftwf_execute
#define Cicm_fft_inverse fftwf_execute
#define Cicm_fft_free_handle fftwf_destroy_plan

#endif

#ifdef CICM_DOUBLE
static void packed_mul(double* x, double* y, double* out, long aLength)
{
	double a, b, c, d;
	long n = 2 * aLength;
	out[0] = x[0] * y[0];
	out[n/2] = x[n/2] * y[n/2];
	for (int j = 1; j < n/2; j++)
	{
        a = x[j];
        b = x[n - j];
        c = y[j];
        d = y[n - j];
        out[j] = a*c-b*d;
        out[n - j] = a*d+b*c;
	}
};

#define Cicm_Signal			double
#define Cicm_Packed			double
#define Cicm_Fft_Handle		fftw_plan

#define	Cicm_signal_malloc(pointeur, length) pointeur = (Cicm_Signal *)malloc(length * sizeof(Cicm_Signal))
#define	Cicm_packed_malloc(pointeur, length) pointeur = (Cicm_Packed *)malloc(length * sizeof(Cicm_Packed))
#define	Cicm_free free

#define Cicm_signal_clear(source, length) gsl_vector_set_zero(&gsl_vector_view_array(source, length).vector)
#define Cicm_signal_add(source1, dest, none, length) gsl_vector_add(&gsl_vector_view_array(dest, length).vector,&gsl_vector_view_array(source1, length).vector)
#define Cicm_signal_copy(source, dest, length) gsl_vector_memcpy(&gsl_vector_view_array(dest, length).vector,&gsl_vector_view_array(source, length).vector)
#define Cicm_signal_dot(source1, source2, dest, length) gsl_blas_ddot(&gsl_vector_view_array(source1, length).vector, &gsl_vector_view_array(source2, length).vector, dest)
#define Cicm_packed_mul(source1, source2, dest, length) packed_mul(source1, source2, dest, length)

#define Cicm_fft_init_handle_forward(length, real, packed) fftw_plan_r2r_1d(length, real, packed, FFTW_R2HC, FFTW_ESTIMATE)
#define Cicm_fft_init_handle_inverse(length, packed, real) fftw_plan_r2r_1d(length, packed, real, FFTW_HC2R, FFTW_ESTIMATE)
#define Cicm_fft_forward fftw_execute
#define Cicm_fft_inverse fftw_execute
#define Cicm_fft_free_handle fftw_destroy_plan
#endif
#endif

#endif