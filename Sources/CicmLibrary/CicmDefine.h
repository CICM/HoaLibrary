/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef DEF_CICM_DEFINE
#define DEF_CICM_DEFINE

#include "CicmTools.h"

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>
#include "CicmDefine_VDSP.h"

#endif

#ifdef _WINDOWS

#include <ipps.h>
#include <ippm.h>
#include <mkl.h>
#include <mkl_cblas.h>

#endif
/************************************************************************************/
/************************************* TYPES ****************************************/
/************************************************************************************/

#define cicm_vector_float  float*
#define cicm_matrix_float  float*

#define cicm_vector_double  double*
#define cicm_matrix_double  double*

/************************************************************************************/
/************************************* MALLOC ***************************************/
/************************************************************************************/

/******************************* Vector *********************************************/

#define	cicm_malloc_vec_f(vector, vector_size) vector = (cicm_vector_float)calloc(vector_size, sizeof(float))
#define	cicm_malloc_vec_d(vector, vector_size) vector = (cicm_vector_double)calloc(vector_size, sizeof(double))

/******************************* Matrix *********************************************/

#define	cicm_malloc_mat_f(matrix, number_of_rows, columns_size) matrix = (cicm_matrix_float)calloc(number_of_rows * columns_size, sizeof(float) )
#define	cicm_malloc_mat_d(matrix, number_of_rows, columns_size) matrix = (cicm_matrix_double)calloc(number_of_rows * columns_size, sizeof(double))

/************************************************************************************/
/************************************* FREE *****************************************/
/************************************************************************************/

#define cicm_free(pointor) free(pointor); pointor = NULL

/************************************************************************************/
/************************************* SET ******************************************/
/************************************************************************************/

/******************************* Matrix *********************************************/

#define cicm_set_mat_f(matrix, row, column_index, columns_size, value) matrix[row * columns_size + column_index] = value
#define cicm_set_mat_d(matrix, row, column_index, columns_size, value) matrix[row * columns_size + column_index] = value

/************************************************************************************/
/************************************* CLEAR ****************************************/
/************************************************************************************/

/******************************* Vector *********************************************/
#ifdef _ATLAS
#define cicm_clear_vec_f(vector, vector_size) catlas_sset(vector_size, 0.f, vector, 1)
#define cicm_clear_vec_d(vector, vector_size) catlas_dset(vector_size, 0., vector, 1)
#else
#define cicm_clear_vec_f(vector, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++) \
{ \
    *(vector+cicm_i) = 0.f; \
}

#define cicm_clear_vec_d(vector, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++) \
{ \
    *(vector+cicm_i) = 0.; \
}
#endif
/******************************* Matrix *********************************************/
#ifdef _ATLAS
#define cicm_clear_mat_f(matrix, row_number, columns_size) catlas_sset(row_number * columns_size, 0.f, vector, 1)
#define cicm_clear_mat_d(matrix, row_number, columns_size) catlas_dset(row_number * columns_size, 0., vector, 1)
#endif

/************************************************************************************/
/************************************* COPY *****************************************/
/************************************************************************************/

/******************************* Vector To Vector ***********************************/

#define cicm_copy_vec_vec_f(vector_source, vector_destination, vector_size) cblas_scopy(vector_size, vector_source, 1, vector_destination, 1);
#define cicm_copy_vec_vec_d(vector_source, vector_destination, vector_size) cblas_dcopy(vector_size, vector_source, 1, vector_destination, 1);

/******************************* Vector To Matrix ***********************************/

#define cicm_copy_vec_mat_f(vector_source, matrix_destination, row_number, columns_size) cblas_scopy(columns_size, vector_source, 1, matrix_destination + row_number * size, 1)
#define cicm_copy_vec_mat_d(vector_source, matrix_destination, row_number, columns_size) cblas_dcopy(columns_size, vector_source, 1, matrix_destination + row_number * size, 1)

/******************************* Matrix To Vector ***********************************/

#define cicm_copy_mat_vec_f(matrix_source, vector_destination, row_number, columns_size) cblas_scopy(columns_size, matrix_source+row_number * size, 1, vector_destination, 1)
#define cicm_copy_mat_vec_d(matrix_source, vector_destination, row_number, columns_size) cblas_dcopy(columns_size, matrix_source+row_number * size, 1, vector_destination, 1)

/******************************* Matrix To Matrix ***********************************/

#define cicm_copy_mat_mat_f(matrix_source, matrix_destination, row_number, columns_size) cblas_scopy(row_number * columns_size, matrix_source, 1, matrix_destination, 1)
#define cicm_copy_mat_mat_d(matrix_source, matrix_destination, row_number, columns_size) cblas_dcopy(row_number * columns_size, matrix_source, 1, matrix_destination, 1)

/************************************************************************************/
/*********************************** ADD ********************************************/
/************************************************************************************/

/******************************* Scalar To Vector ***********************************/

#define cicm_add_sca_vec_vec_f(vector_source, scalar, vector_destination, vector_size) {catlas_sset(vector_size, scalar, vector_destination, 1); cblas_saxpy(vector_size, 1.f, vector_source, 1, vector_destination, 1);}
#define cicm_add_sca_vec_vec_d(vector_source, scalar, vector_destination, vector_size)  {catlas_dset(vector_size, scalar, vector_destination, 1); cblas_daxpy(vector_size, 1.f, vector_source, 1, vector_destination, 1);}

/******************************* Vector To Vector ***********************************/

#define cicm_add_vec_vec_f(vector_source, vector_destination, vector_size) cblas_saxpy(vector_size, 1.f, vector_source, 1, vector_destination, 1)
#define cicm_add_vec_vec_d(vector_source, vector_destination, vector_size) cblas_daxpy(vector_size, 1., vector_source, 1, vector_destination, 1)

/************************************************************************************/
/*********************************** PRODUCT ****************************************/
/************************************************************************************/

/******************************* Dot Product ****************************************/

#define cicm_dot_product_f(vector_source_1, vector_source_2, scalar_destination, vector_size) scalar_destination = cblas_sdot(vector_size, vector_source_1, 1, vector_source_2, 1)

#define cicm_dot_product_d(vector_source_1, vector_source_2, scalar_destination, vector_size) scalar_destination = cblas_ddot(vector_size, vector_source_1, 1, vector_source_2, 1)

/******************************* Vector And Scalar In Place *************************/

#define cicm_product_vec_sca_f(vector_source, scalar, vector_size) cblas_sscal(vector_size, scalar, vector_source, 1)
#define cicm_product_vec_sca_d(vector_source, scalar, vector_size) cblas_dscal(vector_size, scalar, vector_source, 1)

/******************************* Vector And Scalar **********************************/

#define cicm_product_vec_sca_vec_f(vector_source, scalar, vector_destination, vector_size) {cicm_copy_vec_vec_f(vector_source, vector_destination, vector_size); cicm_product_vec_sca_f(vector_destination, scalar, vector_size);}
#define cicm_product_vec_sca_vec_d(vector_source, scalar, vector_destination, vector_size) {cicm_copy_vec_vec_d(vector_source, vector_destination, vector_size); cicm_product_vec_sca_d(vector_destination, scalar, vector_size);}

/******************************* Vector and Vector In Place ************************************/

#define cicm_product_vec_f(vector_source, vector_destination, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++){*(vector_destination+cicm_i) *= *(vector_source+cicm_i);}
#define cicm_product_vec_d(vector_source, vector_destination, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++){*(vector_destination+cicm_i) *= *(vector_source+cicm_i);}

/******************************* Vector And Vector **********************************/

#define cicm_product_vec_vec_f(vector_source_1, vector_source_2, vector_destination, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++) \
{ \
    *(vector_destination+cicm_i) = *(vector_source_1+cicm_i) * *(vector_source_2+cicm_i); \
}

#define cicm_product_vec_vec_d(vector_source_1, vector_source_2, vector_destination, vector_size) \
for(int cicm_i = 0; cicm_i < vector_size; cicm_i++){*(vector_destination+cicm_i) = *(vector_source_1+cicm_i) * *(vector_source_2+cicm_i);}

/******************************* Vector And Matrix **********************************/

#define cicm_product_mat_vec_f(matrix_source, vector_source, vector_destination, number_of_rows, columns_size) cblas_sgemv(CblasRowMajor, CblasNoTrans, number_of_rows, columns_size, 1.f, matrix_source, columns_size, vector_source, 1, 0.f, vector_destination, 1)

#define cicm_product_mat_vec_d(matrix_source, vector_source, vector_destination, number_of_rows, columns_size) cblas_dgemv(CblasRowMajor, CblasNoTrans, number_of_rows, columns_size, 1.f, matrix_source, columns_size, vector_source, 1, 0.f, vector_destination, 1)

/******************************* Matrix And Matrix **********************************/

#define cicm_product_mat_mat_f(matrix_source_1, matrix_source_2, matrix_destination, number_of_rows, columns_size_1, columns_size_2) cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rows, columns_size_1, columns_size_2, 1., matrix_source_1, columns_size_2, matrix_source_2, columns_size_1, 0., matrix_destination, columns_size_1)

#define cicm_product_mat_mat_d(matrix_source_1, matrix_source_2, matrix_destination, number_of_rows, columns_size_1, columns_size_2) cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, number_of_rows, columns_size_1, columns_size_2, 1., matrix_source_1, columns_size_2, matrix_source_2, columns_size_1, 0., matrix_destination, columns_size_1)


/************************************************************************************/
/*********************************** PRODUCT AND SUM ********************************/
/************************************************************************************/

/******************************* Vector And Vector Product Sum To Vector ************/

//#define cicm_product_sum_vec_vec_vec_f(vector_source_1, vector_source_2, vector_destination, vector_size) vDSP_vma(vector_source_1, 1, vector_source_2, 1, vector_destination, 1, vector_destination, 1, vector_size)
//#define cicm_product_sum_vec_vec_vec_d(vector_source_1, vector_source_2, vector_destination, vector_size) vDSP_vmaD(vector_source_1, 1, vector_source_2, 1, vector_destination, 1, vector_destination, 1, vector_size)

/******************************* Vector And Scalar Product Sum To Vector ************/

#define cicm_product_sum_vec_sca_vec_f(vector_source, scalar, vector_destination, vector_size) cblas_saxpy(vector_size, scalar, vector_source, 1, vector_destination, 1)
#define cicm_product_sum_vec_sca_vec_d(vector_source, scalar, vector_destination, vector_size) cblas_daxpy(vector_size, scalar, vector_source, 1, vector_destination, 1)

#endif
