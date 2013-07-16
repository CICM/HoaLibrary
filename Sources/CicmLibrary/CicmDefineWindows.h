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


#ifndef DEF_CICM_DEFINE
#define DEF_CICM_DEFINE

#include <ipps.h>
#include <ippm.h>
#include <mkl.h>

static Ipp32f	float_filled_1[16384] = {1};
static Ipp64f	double_filled_1[16384] = {1};

static void intel_init()
{
	for(int i = 0; i < 16384; i++)
	{
		float_filled_1[i] = 1.;
		double_filled_1[i] = 1.;
	}
}

#define Cicm_Float			Ipp32f
#define Cicm_Vector_Float	Ipp32f*
#define Cicm_Matrix_Float	Ipp32f*

#define Cicm_Double			Ipp64f
#define Cicm_Vector_Double	Ipp64f*
#define Cicm_Matrix_Double  Ipp64f*

#define Cicm_Float_Packed			Ipp32f
#define Cicm_Float_Fft_Handle		IppsFFTSpec_R_32f
#define Cicm_Float_Fft_Buffer		Ipp8u

#define Cicm_Double_Packed	Ipp64f
#define Cicm_Fft_Handle		IppsFFTSpec_R_64f
#define Cicm_Fft_Buffer		Ipp8u


/**************** ALLOCATION *****************/
#define	Cicm_Vector_Float_Malloc(pointeur, length) pointeur = ippsMalloc_32f(length)
#define	Cicm_Vector_Double_Malloc(pointeur, length) pointeur = ippsMalloc_64f(length)

#define	Cicm_Matrix_Float_Malloc(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Float)ippsMalloc_32f(number_of_rows * columns_size);
#define	Cicm_Matrix_Double_Malloc(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Double)ippsMalloc_64f(number_of_rows * columns_size);


/**************** FREE *****************/
#define Cicm_Free(pointor) ippsFree(pointor); pointor = NULL;

/**************** SET ******************/
#define Cicm_Matrix_Float_Set(matrix, i, j, column_size, value) matrix[i * column_size + j] = value
#define Cicm_Matrix_Double_Set(matrix, i, j, column_size, value) matrix[i * column_size + j] = value
/*
#define Cicm_packed_mul(source1, source2, dest, length) ippsMulPack_32f(source1, source2, dest, length)

#define Cicm_fft_get_size(order, spectrumSize, initSize, bufferSize) ippsFFTGetSize_R_32f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectrumSize, initSize, bufferSize)
#define Cicm_fft_init_handle(handle, order, spectBuffer, initBuffer) ippsFFTInit_R_32f(handle, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectBuffer, initBuffer)
#define Cicm_fft_forward(signal, complex, fft_handle, buffer) ippsFFTFwd_RToPack_32f(signal, complex, fft_handle, buffer)
#define Cicm_fft_inverse(complex, dest, fft_handle, buffer) ippsFFTInv_PackToR_32f(complex, dest, fft_handle, buffer)
#define Cicm_fft_free_handle ippsFFTFree_R_32f

/**************** COPY *****************/

#define Cicm_Vector_Float_Copy(vectorSource, vectorDest, size) ippsCopy_32f(vectorSource, vectorDest, size)
#define Cicm_Vector_Double_Copy(vectorSource, vectorDest, size) ippsCopy_64f(vectorSource, vectorDest, size)
/*
#define Cicm_Vector_Matrix_Float_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmov(vectorSource, matrixDest+ row_number * size, size, 1, size, size)
#define Cicm_Vector_Matrix_Double_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmovD(vectorSource, matrixDest+row_number * size, size, 1, size, size)

#define Cicm_Matrix_Vector_Float_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmov(matrixSource+row_number * size, vectorDest, size, 1, size, size)
#define Cicm_Matrix_Vector_Double_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmovD(matrixSource+row_number * size, vectorDest, size, 1, size, size)

/**************** PRODUCT *************/
#define Cicm_Matrix_Vector_Float_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) int sizeOfType = sizeof(Ipp32f); ippmMul_mv_32f(matrix, sizeOfType * column_size, sizeOfType, column_size, number_of_rows, vectorSource, sizeOfType, column_size, vectorDest, sizeOfType)
#define Cicm_Matrix_Vector_Double_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) int sizeOfType = sizeof(Ipp64f); ippmMul_mv_64f(matrix, sizeOfType * column_size, sizeOfType, column_size, number_of_rows, vectorSource, sizeOfType, column_size, vectorDest, sizeOfType)

#define Cicm_Matrix_Matrix_Float_Product(matrixOne, matrixTwo, matrixDest, number_of_rowsOne, column_sizetwo, column_sizeOne) int sizeOfType = sizeof(Ipp32f); ippmMul_mm_32f(matrixOne, sizeOfType * column_sizetwo, sizeOfType, column_sizetwo, number_of_rowsOne, matrixTwo, sizeOfType, sizeOfType, 

/**************** DOT PRODUCT *********/

#define Cicm_Vector_Float_Dot_Product(vectorOne, vectorTwo, scalarDest, size) ippsDotProd_32f(vectorOne, vectorTwo, size, scalarDest)
#define Cicm_Vector_Double_Dot_Product(vectorOne, vectorTwo, scalarDest, size) ippsDotProd_64f(vectorOne, vectorTwo, size, scalarDest)

/**************** MUL *****************/
#define Cicm_Matrix_Vector_Float_Mul(vectorOne, vectorTwo, vectorDest, size) ippsMul_32f(vectorOne, vectorTwo, vectorDest, size);
#define Cicm_Matrix_Vector_Double_Mul(vectorOne, vectorTwo, vectorDest, size) ippsMul_64f(vectorOne, vectorTwo, vectorDest, size);

#define Cicm_Vector_Scalar_Float_Mul(vectorSource, scalar, vectorDest, size) ippsMulC_32f(vectorSource, scalar, vectorDest, size)
#define Cicm_Vector_Scalar_Double_Mul(vectorSource, scalar, vectorDest, size) ippsMulC_64f(vectorSource, scalar, vectorDest, size)
/*
#define Cicm_Vector_Vector_Float_Mul(vectorOne, vectorDest, size) cblas_sdot(size, vectorOne, 1, vectorDest, 1)
#define Cicm_Vector_Vector_Double_Mul(vectorOne, vectorDest, size) cblas_ddot(size, vectorOne, 1, vectorDest, 1)

/**************** ADD *****************/

#define Cicm_Vector_Float_Add(vectorOne, vectorDest, size) ippsAdd_32f_I(vectorOne, vectorDest, size)
#define Cicm_Vector_Double_Add(vectorOne, vectorDest, size) ippsAdd_64f_I(vectorOne, vectorDest, size)

/************* MUL AND ADD ************/

#define Cicm_Vector_Vector_Float_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) ippsAddProduct_32f(vectorOne, vectorTwo, vectorDest, size)
#define Cicm_Vector_Vector_Double_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) ippsAddProduct_64f(vectorOne, vectorTwo, vectorDest, size)

#define Cicm_Vector_Scalar_Float_Mul_And_Add(vectorOne, scalar, vectorDest, size) ippsAddProductC_32f(vectorOne, scalar, vectorDest, size)
#define Cicm_Vector_Scalar_Double_Mul_And_Add(vectorOne, scalar, vectorDest, size)// Cicm_Vector_Scalar_Double_Mul(vectorOne, scalar, vectorDest, size);

/**************** SUM *****************
#define Cicm_Vector_Float_Sum(source1, source2, dest, length) vDSP_vadd(source1, 1, source2, 1, dest, 1, length)
#define Cicm_Vector_Double_Sum(source1, source2, dest, length) vDSP_vaddD(source1, 1, source2, 1, dest, 1, length)

#define Cicm_Vector_Scalar_Float_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsadd(vectorSource, 1, scalar, vectorDest, 1, size);
#define Cicm_Vector_Scalar_Double_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsaddD(vectorSource, 1, scalar, vectorDest, 1, size);

/**************** CLIP  ***************
#define Cicm_Vector_Float_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclip(vectorsource, 1, low, high, vectorDest, 1, size);
#define Cicm_Vector_Double_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclipD(vectorsource, 1, low, high, vectorDest, 1, size);

/**************** CLEAR ***************/

#define Cicm_Vector_Float_Clear(source, length) ippsZero_32f(source, length)
#define Cicm_Vector_Double_Clear(source, length) ippsZero_64f(source, length)

/* Matrix Transpose *
 #define  Cicm_Matrix_Transpose_Float(matrixSource, matrixDest, rowDest, columnDest) vDSP_mtrans(&matrixSource[0][0], 1, &matrixDest[0][0], 1, rowDest, columnDest);
 
 #define  Cicm_Matrix_Transpose_Double(matrixSource, matrixDest, rowDest, columnDest) vDSP_mtransD(matrixSource, 1, matrixDest, 1, rowDest, columnDest);
/***

#define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
#define	Cicm_free_packed(pointeur) free(pointeur[0].realp) free(pointeur[0].imagp)

#define Cicm_fft_free_handle vDSP_destroy_fftsetup

#define Cicm_packed_mul(source1, source2, dest, length) vDSP_zvmul(source1, 1, source2, 1, dest, 1, length, 1)
#define Cicm_packed_clear(source, length) vDSP_vclr(source[0].imagp, 1, length); vDSP_vclr(source[0].realp, 1, length);

#define Cicm_fft_forward(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
#define Cicm_fft_inverse(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)

/* Sinus and Cosinus *
#define Cicm_Vector_Float_Cosinus vvcosf
#define Cicm_Vector_Float_Sinus vvsinf
#define Cicm_Vector_Double_Cosinus vvcos
#define Cicm_Vector_Double_Sinus vvsin
*/
#define Cicm_Vector_Float_SinCos(sinResult, cosResult, angle, size) ippsPolarToCart_32f(float_filled_1, angle, sinResult, cosResult, size);
#define Cicm_Vector_Double_SinCos(sinResult, cosResult, angle, size) ippsPolarToCart_64f(double_filled_1, angle, sinResult, cosResult, size);

#endif

