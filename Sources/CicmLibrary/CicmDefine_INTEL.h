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

/****************************************/
/**************** TYPES *****************/
/****************************************/

#define Cicm_Float              Ipp32f
#define Cicm_Vector_Float       Ipp32f*
#define Cicm_Matrix_Float       Ipp32f*

#define Cicm_Double             Ipp64f
#define Cicm_Vector_Double      Ipp64f*
#define Cicm_Matrix_Double      Ipp64f*

#define Cicm_Float_Packed       Ipp32f
#define Cicm_Float_Fft_Handle	IppsFFTSpec_R_32f
#define Cicm_Float_Fft_Buffer	Ipp8u

#define Cicm_Double_Packed      Ipp64f
#define Cicm_Fft_Handle         IppsFFTSpec_R_64f
#define Cicm_Fft_Buffer         Ipp8u

/****************************************/
/************* ALLOCATION ***************/
/****************************************/

#define	cicm_malloc_vec_f(vector, length) vector = ippsMalloc_32f(length)
#define	cicm_malloc_vec_d(vector, length) vector = ippsMalloc_64f(length)

#define	cicm_malloc_mat_f(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Float)ippsMalloc_32f(number_of_rows * columns_size); cicm_clear_vec_f(matrix, number_of_rows * columns_size);
#define	cicm_malloc_mat_d(matrix, number_of_rows, columns_size) matrix = (Cicm_Matrix_Double)ippsMalloc_64f(number_of_rows * columns_size); cicm_clear_vec_d(matrix, number_of_rows * columns_size);

/****************************************/
/**************** FREE *****************/
/****************************************/

#define cicm_free(pointor) ippsFree(pointor); pointor = NULL;
#define cicm_free_Complex_Packed(pointor) ippsFree(pointor); pointor = NULL;

/****************************************/
/***************** SET ******************/
/****************************************/

#define cicm_set_mat_f(matrix, i, j, column_size, value) matrix[i * column_size + j] = value
#define cicm_set_mat_d(matrix, i, j, column_size, value) matrix[i * column_size + j] = value

/****************************************/
/***************** COPY *****************/
/****************************************/

#define cicm_copy_vec_vec_f(vectorSource, vectorDest, size) ippsCopy_32f(vectorSource, vectorDest, size)
#define cicm_copy_vec_vec_d(vectorSource, vectorDest, size) ippsCopy_64f(vectorSource, vectorDest, size)

#define cicm_copy_vec_mat_f(vectorSource, matrixDest, row_number, size) ippsCopy_32f(vectorSource, matrixDest+ row_number * size, size)
#define cicm_copy_vec_mat_d(vectorSource, matrixDest, row_number, size) ippsCopy_32f(vectorSource, matrixDest+row_number * size, size)

#define cicm_copy_mat_vec_f(matrixSource, vectorDest, row_number, size) vDSP_mmov(matrixSource+row_number * size, vectorDest, size)
#define cicm_copy_mat_vec_d(matrixSource, vectorDest, row_number, size) vDSP_mmovD(matrixSource+row_number * size, vectorDest, size)

/****************************************/
/**************** PRODUCT ***************/
/****************************************/

#define cicm_product_mat_vec_f(matrix, vectorSource, vectorDest, number_of_rows, column_size) int sizeOfType = sizeof(Ipp32f); ippmMul_mv_32f(matrix, sizeOfType * column_size, sizeOfType, column_size, number_of_rows, vectorSource, sizeOfType, column_size, vectorDest, sizeOfType)
#define cicm_product_mat_vec_d(matrix, vectorSource, vectorDest, number_of_rows, column_size) int sizeOfType = sizeof(Ipp64f); ippmMul_mv_64f(matrix, sizeOfType * column_size, sizeOfType, column_size, number_of_rows, vectorSource, sizeOfType, column_size, vectorDest, sizeOfType)

#define cicm_product_mat_mat_f(matrixOne, matrixTwo, matrixDest, number_of_rowsOne, column_sizetwo, column_sizeOne) int sizeOfType = sizeof(Ipp32f);

/****************************************/
/**************** DOT PRODUCT ***********/
/****************************************/

#define cicm_dot_product_f(vectorOne, vectorTwo, scalarDest, size) ippsDotProd_32f(vectorOne, vectorTwo, size, scalarDest)
#define cicm_dot_product_d(vectorOne, vectorTwo, scalarDest, size) ippsDotProd_64f(vectorOne, vectorTwo, size, scalarDest)

/****************************************/
/****************** MUL *****************/
/****************************************/

#define cicm_product_vec_vec_f(vectorOne, vectorTwo, vectorDest, size) ippsMul_32f(vectorOne, vectorTwo, vectorDest, size);
#define cicm_product_vec_vec_d(vectorOne, vectorTwo, vectorDest, size) ippsMul_64f(vectorOne, vectorTwo, vectorDest, size);

#define cicm_product_vec_sca_vec_f(vectorSource, scalar, vectorDest, size) ippsMulC_32f(vectorSource, scalar, vectorDest, size)
#define cicm_product_vec_sca_vec_d(vectorSource, scalar, vectorDest, size) ippsMulC_64f(vectorSource, scalar, vectorDest, size)

#define cicm_product_vec_f(vectorOne, vectorDest, size) cblas_sdot(size, vectorOne, 1, vectorDest, 1)
#define cicm_product_vec_d(vectorOne, vectorDest, size) cblas_ddot(size, vectorOne, 1, vectorDest, 1)

/****************************************/
/***************** ADD ******************/
/****************************************/

#define cicm_add_vec_vec_f(vectorOne, vectorDest, size) ippsAdd_32f_I(vectorOne, vectorDest, size)
#define cicm_add_vec_vec_d(vectorOne, vectorDest, size) ippsAdd_64f_I(vectorOne, vectorDest, size)

/****************************************/
/****************** SUM *****************/
/****************************************/

 #define cicm_sum_vector_f(Vector_1, Vector_2, dest, size) ippsAdd_32f(Vector_1, Vector_2, dest, size)
 #define cicm_sum_vector_d(Vector_1, Vector_2, dest, size) ippsAdd_64f(Vector_1, Vector_2, dest, size)
 
 #define cicm_add_sca_vec_vec_f(vectorSource, scalar, vectorDest, size) ippsAddC_32f(vectorSource, scalar, vectorDest,size);
 #define cicm_add_sca_vec_vec_d(vectorSource, scalar, vectorDest, size) ippsAddC_64f(vectorSource, scalar, vectorDest, size);

/****************************************/
/************** MUL AND ADD *************/
/****************************************/

#define cicm_product_sum_vec_vec_vec_f(vectorOne, vectorTwo, vectorDest, size) ippsAddProduct_32f(vectorOne, vectorTwo, vectorDest, size)
#define cicm_product_sum_vec_vec_vec_d(vectorOne, vectorTwo, vectorDest, size) ippsAddProduct_64f(vectorOne, vectorTwo, vectorDest, size)

#define cicm_product_sum_vec_sca_vec_f(vectorOne, scalar, vectorDest, size) ippsAddProductC_32f(vectorOne, scalar, vectorDest, size)

/****************************************/
/***************** CLIP  ****************/
/****************************************/

#define Cicm_Vector_Float_Clip(vectorsource, low, high, vectorDest, size) ippsThreshold_LT_32f(vectorsource, vectorDest, size, low); ippsThreshold_GT_32f(vectorsource, vectorDest, high, low);
#define Cicm_Vector_Double_Clip(vectorsource, low, high, vectorDest, size) ippsThreshold_LT_64f(vectorsource, vectorDest, size, low); ippsThreshold_GT_64f(vectorsource, vectorDest, high, low);

/****************************************/
/***************** CLEAR ****************/
/****************************************/

#define cicm_clear_vec_f(source, length) ippsZero_32f(source, length)
#define cicm_clear_vec_d(source, length) ippsZero_64f(source, length)

/****************************************/
/**************** SIN COS ***************/
/****************************************/

#define Cicm_Vector_Float_SinCos(sinResult, cosResult, angle, size) vsSinCos(size, angle, sinResult, cosResult);
#define Cicm_Vector_Double_SinCos(sinResult, cosResult, angle, size) vdSinCos(size, angle, sinResult, cosResult);

/*
 
 #define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
 #define	cicm_free_packed(pointeur) free(pointeur[0].realp) free(pointeur[0].imagp)
 
 #define Cicm_fft_free_handle vDSP_destroy_fftsetup
 
 #define Cicm_packed_mul(source1, source2, dest, length) vDSP_zvmul(source1, 1, source2, 1, dest, 1, length, 1)
 #define Cicm_packed_clear(source, length) vDSP_vclr(source[0].imagp, 1, length); vDSP_vclr(source[0].realp, 1, length);
 
 #define Cicm_fft_forward(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
 #define Cicm_fft_inverse(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)
 
  */
 #define Cicm_packed_mul(source1, source2, dest, length) ippsMulPack_32f(source1, source2, dest, length)
 
 #define Cicm_fft_get_size(order, spectrumSize, initSize, bufferSize) ippsFFTGetSize_R_32f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectrumSize, initSize, bufferSize)
 #define Cicm_fft_init_handle(handle, order, spectBuffer, initBuffer) ippsFFTInit_R_32f(handle, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, spectBuffer, initBuffer)
 #define Cicm_fft_forward(signal, complex, fft_handle, buffer) ippsFFTFwd_RToPack_32f(signal, complex, fft_handle, buffer)
 #define Cicm_fft_inverse(complex, dest, fft_handle, buffer) ippsFFTInv_PackToR_32f(complex, dest, fft_handle, buffer)
 #define Cicm_fft_free_handle ippsFFTFree_R_32f

#endif

