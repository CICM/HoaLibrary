/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_HOA_3D_AMBISONIC
#define DEF_HOA_3D_AMBISONIC

#include "../CicmLibrary/CicmLibrary.h"

//!
/**
 */

//! The 3D ambisonic classes.
/**
 All the 3D ambisonic classes will be part of this namespace
 */
namespace Hoa3D
{
    //! The ambisonic class.
    /**
     Most of the ambisonic classes inherit from this classe. It computes the number of harmonics, their indices and their orders depending of the decomposition order. etc...
     */
    class Ambisonic
    {
    protected:
        long	m_order;
        long	m_number_of_harmonics;
        long	m_number_of_inputs;
        long	m_number_of_outputs;
        
        long*    m_harmonics_indices;
        long*    m_harmonics_orders;
        
    public:
        
        //! The ambisonic constructor.
        /** The ambisonic constructor allocates and initializes the generale member values depending of a decomposition order.
         @param     order	The order, must be at least 1.
         */
        Ambisonic(unsigned int order = 1);
        
        /** The ambisonic destructor.
         */
        ~Ambisonic();
        
        /** Retrieve the decomposition order.
         */
        long getOrder();
        
        /** Retrieve the number of harmonics.
         */
        long getNumberOfHarmonics();
        
        /** Retrieve the number of inputs.
         */
        long getNumberOfInputs();
        
        /** Retrieve the number of outputs.
         */
        long getNumberOfOutputs();
        
        //! Retrieve the argument of an harmonic.
        /** The argument of an harmonic is in the range -band to band. The harmonics are sorted by their bands, from 0 to the decomposition order and, in each band, they are sorted by their arguments in the range -band to band. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the argument of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicBand()
         */
        long getHarmonicArgument(unsigned int index);
        
        //! Retrieve the band of an harmonic.
        /** The bands of the harmonics are in the range 0 to the decomposition order. Each band contains 2 * band + 1 harmonics in the range -band to band. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the band of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicArgument()
         */
        long getHarmonicBand(unsigned int index);
        
        //! Retrieve a good name for an harmonic.
        /** Retrieve a good name for an harmonic.
         
         @param     index	The global index of an harmonic.
         */
        std::string getHarmonicsName(unsigned int index);
    };
}

namespace nv
{
    float legendrePolynomial(int l, int m, float x);
    
	// Basic integer factorial.
	inline static int factorial( int v )
	{
		if (v == 0) {
			return 1;
		}
        
		int result = v;
		while (--v > 0) {
			result *= v;
		}
		return result;
	}
	
	
	// Double factorial.
	// Defined as: n!! = n*(n - 2)*(n - 4)..., n!!(0,-1) = 1.
	inline static int doubleFactorial( int x )
	{
		if (x == 0 || x == -1) {
			return 1;
		}
        
		int result = x;
		while ((x -= 2) > 0) {
			result *= x;
		}
        
		return result;
	}
    
	/// Evaluate Legendre polynomial. */
	static float legendre( int l, int m, float x )
	{
        //	piDebugCheck( m >= 0 );
        //	piDebugCheck( m <= l );
        //	piDebugCheck( fabs(x) <= 1 );
        
		// Rule 2 needs no previous results
		if (l == m) {
			return powf(-1.0f, float(m)) * doubleFactorial(2 * m - 1) * powf(1 - x*x, 0.5f * m);
		}
        
		// Rule 3 requires the result for the same argument of the previous band
		if (l == m + 1) {
			return x * (2 * m + 1) * legendrePolynomial(m, m, x);
		}
        
		// Main reccurence used by rule 1 that uses result of the same argument from
		// the previous two bands
		return (x * (2 * l - 1) * legendrePolynomial(l - 1, m, x) - (l + m - 1) * legendrePolynomial(l - 2, m, x)) / (l - m);
	}
	
	
	template <int l, int m> float legendre(float x);
	
	template <> float legendre<0, 0>(float x) {
		return 1;
	}
	
	template <> float legendre<1, 0>(float x) {
		return x;
	}
	template <> float legendre<1, 1>(float x) {
		return -sqrtf(1 - x * x);
	}
	
	template <> float legendre<2, 0>(float x) {
		return -0.5f + (3 * x * x) / 2;
	}
	template <> float legendre<2, 1>(float x) {
		return -3 * x * sqrtf(1 - x * x);
	}
	template <> float legendre<2, 2>(float x) {
		return -3 * (-1 + x * x);
	}
	
	template <> float legendre<3, 0>(float x) {
		return -(3 * x) / 2 + (5 * x * x * x) / 2;
	}
	template <> float legendre<3, 1>(float x) {
		return -3 * sqrtf(1 - x * x) / 2 * (-1 + 5 * x * x);
	}
	template <> float legendre<3, 2>(float x) {
		return -15 * (-x + x * x * x);
	}
	template <> float legendre<3, 3>(float x) {
		return -15 * powf(1 - x * x, 1.5f);
	}
	
	template <> float legendre<4, 0>(float x) {
		return 0.125f * (3.0f - 30.0f * x * x + 35.0f * x * x * x * x);
	}
	template <> float legendre<4, 1>(float x) {
		return -2.5f * x * sqrtf(1.0f - x * x) * (7.0f * x * x - 3.0f);
	}
	template <> float legendre<4, 2>(float x) {
		return -7.5f * (1.0f - 8.0f * x * x + 7.0f * x * x * x * x);
	}
	template <> float legendre<4, 3>(float x) {
		return -105.0f * x * powf(1 - x * x, 1.5f);
	}
	template <> float legendre<4, 4>(float x) {
		return 105.0f * (x * x - 1.0f) * (x * x - 1.0f);
	}
} // namespace

float nv::legendrePolynomial(int l, int m, float x)
{
	switch(l)
	{
		case 0:
			return legendre<0, 0>(x);
		case 1:
			if(m == 0) return legendre<1, 0>(x);
			return legendre<1, 1>(x);
		case 2:
			if(m == 0) return legendre<2, 0>(x);
			else if(m == 1) return legendre<2, 1>(x);
			return legendre<2, 2>(x);
		case 3:
			if(m == 0) return legendre<3, 0>(x);
			else if(m == 1) return legendre<3, 1>(x);
			else if(m == 2) return legendre<3, 2>(x);
			return legendre<3, 3>(x);
		case 4:
			if(m == 0) return legendre<4, 0>(x);
			else if(m == 1) return legendre<4, 1>(x);
			else if(m == 2) return legendre<4, 2>(x);
			else if(m == 3) return legendre<4, 3>(x);
			else return legendre<4, 4>(x);
	}
	
	// Fallback to the expensive version.
	return legendre(l, m, x);
}


#endif


