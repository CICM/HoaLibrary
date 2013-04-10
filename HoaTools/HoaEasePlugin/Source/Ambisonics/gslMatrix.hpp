/*
 *  test.h
 *  hoa.decoder~
 *
 *  Created by julien colafrancesco on 06/08/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */


#ifndef DEF_GSLMATRIX
#define DEF_GSLMATRIX

#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

void printMat(gsl_matrix* A);
void printVec(gsl_vector* a);
void resizeVector(gsl_vector** vector, unsigned int size);
void resizeMatrix(gsl_matrix** matrix, unsigned int nbOfRow, unsigned int nbOfColumn);
void invertVector(gsl_vector* vector);
void transposeMatrix(gsl_matrix** matrix);
int numberOfSingularValues(gsl_vector* S, double threshold);
void SingularValueRegularization(gsl_matrix** U, gsl_matrix** V, gsl_vector** S);
gsl_matrix * diagFromVector(gsl_vector * X);
gsl_matrix* pinvFromSVD(gsl_matrix* U, gsl_matrix* V, gsl_vector* S);
gsl_matrix* formatedSvdPseudoInverse(gsl_matrix* A);
gsl_matrix* GenericSvdPseudoInverse(gsl_matrix* A);

#endif