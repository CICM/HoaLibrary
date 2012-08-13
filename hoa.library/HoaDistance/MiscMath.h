/*
 *  MiscMath.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 15/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_MISC_MATH
#define DEF_MISC_MATH

#include "math.h"
#undef nil
#undef msg
#include <boost/math/special_functions/bessel.hpp>
#include <complex>

inline int factoriel (int n);
inline long nextPow2(long n);
inline std::complex<double> secHankel(int order,double x);
inline std::complex<double> distanceCompensation(int order, double k, double sourceDistance, double speakerDistance);

int factoriel (int n)
{
	int facto, i;
	facto=1;
	i=1;
	
	while (i<=n)
	{
		facto=facto*i;
		i=i+1;
	}
	return facto;
}

long nextPow2(long n)
{
	
	n--;
	n |= n >> 1;   // Divide by 2^k for consecutive doublings of k up to 32,
	n |= n >> 2;   // and then or the results.
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;
	return n;
}

std::complex<double> secHankel(int order,double x)
{
	std::complex<double> result;
	
	result.real() =  boost::math::sph_bessel(order,x);
	result.imag() = -boost::math::sph_neumann(order,x); 
	
	return result;
}

std::complex<double> distanceCompensation(int order, double k, double sourceDistance, double speakerDistance)
{
	std::complex<double> result;
	std::complex<double> numerator;
	std::complex<double> denominator;
	
	numerator = secHankel(order, k*sourceDistance) /secHankel(0, k*sourceDistance);
	denominator = secHankel(order, k*speakerDistance)/secHankel(0, k*speakerDistance);
	result = numerator/denominator;
	
	//result *= 2/(1+ abs(result) * abs(result));
	
	if(k*sourceDistance > order)
		result *= (cos(order*3.14159265/(k*sourceDistance))+1)/2;
	else 
		result =0;
	
//	if (order!= 0) {
//		double klim = order/sourceDistance;
//		result *= pow(k/klim, 4*order)/ (1 + pow(k/klim, 4*order));
//	}

	
	return result;
}

#endif