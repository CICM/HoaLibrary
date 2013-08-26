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

#include <Accelerate/Accelerate.h>

#define Cicm_Float float
#define Cicm_Vector_Float  float*
#define Cicm_Matrix_Float  float*

#define Cicm_Double double
#define Cicm_Vector_Double  double*
#define Cicm_Matrix_Double  double*

#define Cicm_Complex_Float DSPComplex
#define Cicm_Complex_Packed_Float DSPSplitComplex

#define Cicm_Complex_Double DSPComplexD
#define Cicm_Complex_Packed_Double DSPSplitComplexD

#define Cicm_Fft_Handle FFTSetup

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
#define Cicm_Vector_Float_Copy(vectorSource, vectorDest, size) cblas_scopy(size, vectorSource, 1, vectorDest, 1);
#define Cicm_Vector_Double_Copy(vectorSource, vectorDest, size) cblas_dcopy(size, vectorSource, 1, vectorDest, 1);

#define Cicm_Vector_Matrix_Float_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmov(vectorSource, matrixDest+ row_number * size, size, 1, size, size)
#define Cicm_Vector_Matrix_Double_Copy(vectorSource, matrixDest, row_number, size) vDSP_mmovD(vectorSource, matrixDest+row_number * size, size, 1, size, size)

#define Cicm_Matrix_Vector_Float_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmov(matrixSource+row_number * size, vectorDest, size, 1, size, size)
#define Cicm_Matrix_Vector_Double_Copy(matrixSource, vectorDest, row_number, size) vDSP_mmovD(matrixSource+row_number * size, vectorDest, size, 1, size, size)

/**************** PRODUCT *************/
#define Cicm_Matrix_Vector_Float_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) cblas_sgemv(CblasRowMajor, CblasNoTrans, number_of_rows, column_size, 1.f, matrix, column_size, vectorSource, 1, 0.f, vectorDest, 1)

#define Cicm_Matrix_Vector_Double_Product(matrix, vectorSource, vectorDest, number_of_rows, column_size) cblas_dgemv(CblasRowMajor, CblasNoTrans, number_of_rows, column_size, 1., matrix, column_size, vectorSource, 1, 0., vectorDest, 1)

#define Cicm_Matrix_Matrix_Float_Product(matrix, matrixIn, matrixOut, number_of_rows, column_size_1, column_size_2) cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rows, column_size_1, column_size_2, 1., matrix, column_size_2, matrixIn, column_size_1, 0., matrixOut, column_size_1)

#define Cicm_Matrix_Matrix_Double_Product(matrix, matrixIn, matrixOut, number_of_rows, column_size_1, column_size_2) cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rows, column_size_1, column_size_2, 1., matrix, column_size_2, matrixIn, column_size_1, 0., matrixOut, column_size_1)

/**************** DOT PRODUCT *********/
#define Cicm_Vector_Float_Dot_Product(vectorOne, vectorTwo, scalarDest, size) scalarDest = cblas_sdot(size, vectorOne, 1, vectorTwo, 1)

#define Cicm_Vector_Double_Dot_Product(vectorOne, vectorTwo, scalarDest, size) scalarDest = cblas_ddot(size, vectorOne, 1, vectorTwo, 1)
/**************** MUL *****************/
#define Cicm_Vector_Vector_Float_Mul(vectorOne, vectorTwo, vectorDest, size) vDSP_vmul(vectorOne, 1, vectorTwo, 1, vectorDest, 1, size);
#define Cicm_Vector_Vector_Double_Mul(vectorOne, vectorTwo, vectorDest, size) vDSP_vmulD(vectorOne, 1, vectorTwo, 1, vectorDest, 1, size);

#define Cicm_Vector_Scalar_Float_Mul(vectorSource, scalar, vectorDest, size) vDSP_vsmul(vectorSource, 1, &scalar, vectorDest, 1, size)
#define Cicm_Vector_Scalar_Double_Mul(vectorSource, scalar, vectorDest, size) vDSP_vsmulD(vectorSource, 1, &scalar, vectorDest, 1, size)

#define Cicm_Vector_Float_Mul(vectorOne, vectorDest, size) cblas_sdot(size, vectorOne, 1, vectorDest, 1)
#define Cicm_Vector_Double_Mul(vectorOne, vectorDest, size) cblas_ddot(size, vectorOne, 1, vectorDest, 1)

/**************** ADD *****************/
#define Cicm_Vector_Float_Add(vectorOne, vectorDest, size) cblas_saxpy(size, 1.f, vectorOne, 1, vectorDest, 1)
#define Cicm_Vector_Double_Add(vectorOne, vectorDest, size) cblas_daxpy(size, 1., vectorOne, 1, vectorDest, 1)

/**************** SUM *****************/

#define Cicm_Vector_Float_Sum(vector, dest, length)  vDSP_sve(vector, 1 , &dest, length)
#define Cicm_Vector_Double_Sum(vector, dest, length) vDSP_sveD(vector, 1 , &dest, length)

// A CHANGER DE NOM //
#define Cicm_Vector_Scalar_Float_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsadd(vectorSource, 1, &scalar, vectorDest, 1, size);
#define Cicm_Vector_Scalar_Double_Sum(vectorSource, scalar, vectorDest, size) vDSP_vsaddD(vectorSource, 1, &scalar, vectorDest, 1, size);


/************* MUL AND ADD ************/

#define Cicm_Vector_Vector_Float_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) vDSP_vma(vectorOne, 1, vectorTwo, 1, vectorDest, 1, vectorDest, 1, size)
#define Cicm_Vector_Vector_Double_Mul_And_Add(vectorOne, vectorTwo, vectorDest, size) vDSP_vmaD(vectorOne, 1, vectorTwo, 1, vectorDest, 1, vectorDest, 1, size)

#define Cicm_Vector_Scalar_Float_Mul_And_Add(vectorOne, scalar, vectorDest, size) vDSP_vmsa(vectorOne, 1, vectorDest, 1, &scalar, vectorDest, 1, size);
#define Cicm_Vector_Scalar_Double_Mul_And_Add(vectorOne, scalar, vectorDest, size) vDSP_vmsaD(vectorOne, 1, vectorDest, 1, &scalar, vectorDest, 1, size);

/**************** CLIP  ***************/
#define Cicm_Vector_Float_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclip(vectorsource, 1, &low, &high, vectorDest, 1, size);
#define Cicm_Vector_Double_Clip(vectorsource, low, high, vectorDest, size) vDSP_vclipD(vectorsource, 1, &low, &high, vectorDest, 1, size);

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

#endif
