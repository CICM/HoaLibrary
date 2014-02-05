/*
// Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_LEGENDRE
#define DEF_HOA_3D_LEGENDRE

namespace Hoa3D
{
	// Basic integer factorial.
	inline static int factorial( int v );
	// Double factorial.
	// Defined as: n!! = n*(n - 2)*(n - 4)..., n!!(0,-1) = 1.
	inline static int doubleFactorial( int x );
	/// Evaluate Legendre polynomial. */
	template <int l, int m> float legendre(float x);
    float legendrePolynomial(int l, int m, float x);
} // namespace



#endif
