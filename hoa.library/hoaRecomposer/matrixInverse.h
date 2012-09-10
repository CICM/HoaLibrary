/*
 *  matrixInverse.hpp
 *  BoostTest
 *
 *  Created by julien colafrancesco on 21/12/11.
 *  Copyright 2011 cicm. All rights reserved.
 *
 */

#ifndef DEF_INVERT
#define DEF_INVERT

using namespace boost::numeric::ublas;
using namespace std;

/* Matrix inversion routine.
 Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
template<class T>
bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
	typedef permutation_matrix<std::size_t> pmatrix;
	
	// create a working copy of the input
	matrix<T> A(input);
	
	// create a permutation matrix for the LU-factorization
	pmatrix pm(A.size1());
	
	// perform LU-factorization
	int res = lu_factorize(A, pm);
	if (res != 0)
		return false;
	
	// create identity matrix of "inverse"
	inverse.assign(identity_matrix<T> (A.size1()));
	
	// backsubstitute to get the inverse
	lu_substitute(A, pm, inverse);
	
	return true;
}

#endif