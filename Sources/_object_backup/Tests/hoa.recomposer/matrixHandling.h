/*
 *  matrixHandling.h
 *  hoa.decoder~
 *
 *  Created by julien colafrancesco on 02/08/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_MATRIXGSL
#define DEF_MATRIXGSL

#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <math.h>


//void printMat(gsl_matrix* A);
//void printVec(gsl_vector* a);
//void resizeVector(gsl_vector** vector, int size);
//void resizeMatrix(gsl_matrix** matrix, int nbOfRow, int nbOfColumn);
//void invertVector(gsl_vector* vector);
//void transposeMatrix(gsl_matrix** matrix);
int numberOfSingularValues(gsl_vector* S, double threshold);
//void SingularValueRegularization(gsl_matrix** U, gsl_matrix** V, gsl_vector** S);
//gsl_matrix * diagFromVector(gsl_vector * X);
//gsl_matrix* pinvFromSVD(gsl_matrix* U, gsl_matrix* V, gsl_vector* S);
//gsl_matrix* formatedSvdPseudoInverse(gsl_matrix* A);
//gsl_matrix* GenericSvdPseudoInverse(gsl_matrix* A);

//gsl_matrix * diagFromVector(gsl_vector * X)
//{
//    gsl_matrix * mat = gsl_matrix_alloc(X->size, X->size);
//    gsl_vector_view diag = gsl_matrix_diagonal(mat);
//    gsl_matrix_set_all(mat, 0.0); //or whatever number you like
//    gsl_vector_memcpy(&diag.vector, X);
//    return mat;
//}

int numberOfSingularValues(gsl_vector* S, double threshold)
{
	int numberOfValues = 0;
	int vectorSize = S->size;
	
	for(int i = 0; i < vectorSize ; i++)
	{
		if (gsl_vector_get(S,numberOfValues) > threshold)
			numberOfValues++;	
		else 
			break;
	}
	
	return numberOfValues;
}
//
//void invertVector(gsl_vector* vector)
//{
//	double tmpValue;
//	for (int i = 0; i < vector->size; i++) {
//		tmpValue = gsl_vector_get(vector, i);
//		if (tmpValue != 0) {
//			gsl_vector_set(vector, i, 1/tmpValue);
//		}
//	}
//}
//
//
//
//void printMat(gsl_matrix* A)
//{
//	int M = A->size1;
//	int N = A->size2;
//	for (int i=0;i<M;i++)
//    {
//		for (int j=0;j<N;j++)
//		{
//			printf("%g ",gsl_matrix_get(A,i,j));
//		}
//		printf("\n");
//    }
//	printf("\n");
//}
//
//void printVec(gsl_vector* a)
//{
//	int N = a->size;
//	for(int i = 0; i < N; i++)
//	{
//		printf("%f ", gsl_vector_get(a, i));
//	}
//	printf("\n");
//}
//
//void resizeVector(gsl_vector** vector, int size)
//{
//	gsl_vector* resizedVector = gsl_vector_alloc(size);
//	if ((*vector)->size < size ) {
//		size = (*vector)->size;
//	}
//	
//	for (int i = 0; i < size; i++) {
//		gsl_vector_set(resizedVector, i, gsl_vector_get((*vector), i));
//	}
//	gsl_vector_free(*vector);
//	*vector = resizedVector;
//}
//
//void resizeMatrix(gsl_matrix** matrix, int nbOfRow, int nbOfColumn)
//{
//	gsl_matrix* resizedMatrix = gsl_matrix_alloc(nbOfRow, nbOfColumn);
//	
//	if ((*matrix)->size1 < nbOfRow) 
//		nbOfRow = (*matrix)->size1;
//	if ((*matrix)->size2 < nbOfColumn) 
//		nbOfColumn = (*matrix)->size2;
//	
//	for (int i = 0; i < nbOfRow; i++) {
//		for (int j = 0; j < nbOfColumn; j++) {
//			gsl_matrix_set(resizedMatrix, i, j, gsl_matrix_get(*matrix, i, j));
//		}
//	}
//	gsl_matrix_free(*matrix);
//	*matrix = resizedMatrix;
//}
//
//void SingularValueRegularization(gsl_matrix** U, gsl_matrix** V, gsl_vector** S)
//{
//	int numberOfSingValues;
//	printVec(*S);
//	numberOfSingValues = numberOfSingularValues(*S, 0.01);
//	
//	resizeVector(S, numberOfSingValues);
//	resizeMatrix(U, (*U)->size1, numberOfSingValues);
//	resizeMatrix(V, (*V)->size1, numberOfSingValues);
//}
//
//void transposeMatrix(gsl_matrix** A)
//{
//	gsl_matrix* transposedMatrix = gsl_matrix_alloc((*A)->size2, (*A)->size1);
//	gsl_matrix_transpose_memcpy(transposedMatrix, *A);
//	gsl_matrix_free(*A);
//	*A = transposedMatrix;
//}
//gsl_matrix* pinvFromSVD(gsl_matrix* U, gsl_matrix* V, gsl_vector* S)
//{
//	gsl_matrix* tmpMat	 = gsl_matrix_alloc(V->size1,S->size); 
//	gsl_matrix* resMat	 = gsl_matrix_alloc(V->size1,U->size1); 
//	
//	invertVector(S);
//	gsl_matrix* Sdiag = diagFromVector(S);
//	
//	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, V, Sdiag, 0.0, tmpMat);
//	gsl_blas_dgemm (CblasNoTrans, CblasTrans, 1.0, tmpMat, U, 0.0, resMat);
//	
//	gsl_matrix_free(tmpMat);
//	
//	return resMat;
//}
//
//gsl_matrix* formatedSvdPseudoInverse(gsl_matrix* A)
//{
//	int N = A->size2;
//	gsl_matrix* V	 = gsl_matrix_alloc(N,N); 
//	gsl_vector* S	 = gsl_vector_alloc(N);
//	
//	gsl_linalg_SV_decomp_jacobi(A,V,S);
//	//SingularValueRegularization(&A, &V, &S);
//	gsl_matrix* result = pinvFromSVD(A, V, S);
//	return result;
//}
//
//gsl_matrix* GenericSvdPseudoInverse(gsl_matrix* A)
//{
//	int M = A->size1;
//	int N = A->size2;
//	
//	gsl_matrix* matrixToInvert;
//	gsl_matrix* resultMatrix;
//	
//	
//	if (M >= N) {
//		matrixToInvert = gsl_matrix_alloc(M, N);
//		gsl_matrix_memcpy(matrixToInvert, A);
//		resultMatrix = formatedSvdPseudoInverse(matrixToInvert);
//	}
//	else {
//		matrixToInvert = gsl_matrix_alloc(N,M);
//		gsl_matrix_transpose_memcpy(matrixToInvert, A);
//		resultMatrix = formatedSvdPseudoInverse(matrixToInvert);
//		transposeMatrix(&resultMatrix);
//	}
//	
//	return resultMatrix;
//}
#endif