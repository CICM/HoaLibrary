/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Legendre.h"

namespace Hoa3D
{
	int Factorial( int v )
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
	
	int DoubleFactorial( int x )
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
    
	float Legendre( int l, int m, float x )
	{
		if (l == m) {
			return powf(-1.0f, float(m)) * DoubleFactorial(2 * m - 1) * powf(1 - x*x, 0.5f * m);
		}

		if (l == m + 1) {
			return x * (2 * m + 1) * LegendrePolynomial(m, m, x);
		}
        
		return (x * (2 * l - 1) * LegendrePolynomial(l - 1, m, x) - (l + m - 1) * LegendrePolynomial(l - 2, m, x)) / (l - m);
	}
	
	
	template <int l, int m> float Legendre(float x);
	
	template <> float Legendre<0, 0>(float x) {
		return 1;
	}
	
	template <> float Legendre<1, 0>(float x) {
		return x;
	}
	template <> float Legendre<1, 1>(float x) {
		return -sqrtf(1 - x * x);
	}
	
	template <> float Legendre<2, 0>(float x) {
		return -0.5f + (3 * x * x) / 2;
	}
	template <> float Legendre<2, 1>(float x) {
		return -3 * x * sqrtf(1 - x * x);
	}
	template <> float Legendre<2, 2>(float x) {
		return -3 * (-1 + x * x);
	}
	
	template <> float Legendre<3, 0>(float x) {
		return -(3 * x) / 2 + (5 * x * x * x) / 2;
	}
	template <> float Legendre<3, 1>(float x) {
		return -3 * sqrtf(1 - x * x) / 2 * (-1 + 5 * x * x);
	}
	template <> float Legendre<3, 2>(float x) {
		return -15 * (-x + x * x * x);
	}
	template <> float Legendre<3, 3>(float x) {
		return -15 * powf(1 - x * x, 1.5f);
	}
	
	template <> float Legendre<4, 0>(float x) {
		return 0.125f * (3.0f - 30.0f * x * x + 35.0f * x * x * x * x);
	}
	template <> float Legendre<4, 1>(float x) {
		return -2.5f * x * sqrtf(1.0f - x * x) * (7.0f * x * x - 3.0f);
	}
	template <> float Legendre<4, 2>(float x) {
		return -7.5f * (1.0f - 8.0f * x * x + 7.0f * x * x * x * x);
	}
	template <> float Legendre<4, 3>(float x) {
		return -105.0f * x * powf(1 - x * x, 1.5f);
	}
	template <> float Legendre<4, 4>(float x) {
		return 105.0f * (x * x - 1.0f) * (x * x - 1.0f);
	}
}

float Hoa3D::LegendrePolynomial(int l, int m, float x)
{
	switch(l)
	{
		case 0:
			return Legendre<0, 0>(x);
		case 1:
			if(m == 0) return Legendre<1, 0>(x);
			return Legendre<1, 1>(x);
		case 2:
			if(m == 0) return Legendre<2, 0>(x);
			else if(m == 1) return Legendre<2, 1>(x);
			return Legendre<2, 2>(x);
		case 3:
			if(m == 0) return Legendre<3, 0>(x);
			else if(m == 1) return Legendre<3, 1>(x);
			else if(m == 2) return Legendre<3, 2>(x);
			return Legendre<3, 3>(x);
		case 4:
			if(m == 0) return Legendre<4, 0>(x);
			else if(m == 1) return Legendre<4, 1>(x);
			else if(m == 2) return Legendre<4, 2>(x);
			else if(m == 3) return Legendre<4, 3>(x);
			else return Legendre<4, 4>(x);
	}

	return Legendre(l, m, x);
}
