/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef DEF_HOA_3D_TOOLS
#define DEF_HOA_3D_TOOLS

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>

#endif

#ifdef _WINDOWS

#include <ipps.h>
#include <ippm.h>
#include <mkl.h>
#include <mkl_cblas.h>

#endif
    
#define CICM_PI  (3.141592653589793238462643383279502884)
#define CICM_2PI (6.283185307179586476925286766559005)
#define CICM_PI2 (1.57079632679489661923132169163975144)
#define CICM_PI4 (0.785398163397448309615660845819875721)

#define NUMBEROFLINEARPOINTS 10000
#define NUMBEROFCIRCLEPOINTS 36000
#define NUMBEROFCIRCLEPOINTS_UI 360

namespace Hoa3D
{
    inline int factorial( int v )
	{
        int result = v;
		if(v == 0)
			return 1;
        
		while(--v > 0)
			result *= v;
        
		return result;
	}
    
    inline int double_factorial( int x )
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
    
    //! The associated Legendre polynomials
    /**	The function computes the associated Legendre polynomial \f$P(l, m)\f$ P(l, m) that is a part of the formula that compute the spherical harmonic coefficient where l is the band and the m is the argument of a spherical harmonic and x is the cosinus of the elevation. It uses three recurrence formulas : \n
        P(l, l)(x) = (-1)^l * (2l - 1)!! * (1 - x * x )^(l * 0.5), \n
        P(l + 1, l)(x) = x * (2l + 1) * P(l, l) and \n
        P(l + 1, m)(x) = ((2l + 1) * x * P(m, l) - (l + m) * P(m, l - 1)) / (l - m + 1).
     
        @param     band     The band of the spherical harmonic.
        @param     argument	The argument of the spherical harmonic.
        @param     x        The cosinus of the elevation.
        @return    The function return the associated Legendre polynomial P(l, m)(x).
     
        @see    spherical_harmonic_elevation
        @see    spherical_harmonic_azimuth
        @see    spherical_harmonic
     */
	inline double associated_legendre(int band, int argument, double x)
	{
        band = abs(band);
        argument = abs(argument);
        
		if(band == argument)
        {
			return pow(-1.0f, (double)argument) * double_factorial(2. * argument - 1) * pow(1. - x * x, 0.5 * argument);
		}
		else if(band == argument + 1)
        {
			return x * (2 * argument + 1) * associated_legendre(argument, argument, x);
		}
        else
        {
            return ((double)(2 * band - 1) * x *  associated_legendre(band - 1, argument, x) - (double)(band + argument - 1.) * associated_legendre(band - 2, argument, x)) / (double)(band - argument);
        }
	}
    
    inline double K(int l, int m)
	{
        l = abs(l);
        m = abs(m);
        if(m == 0)
            return sqrt((double)factorial(l - m) / (double)factorial(l + m));
        else
            return sqrt(2. * (double)factorial(l - m) / (double)factorial(l + m));
	}
    
    //! The spherical harmonic elevation coefficient
    /**	The funtion computes the elevation coefficients of spherical harmonics. It use the associated Legendre polynomials and normalize the result
     
     @param     band     The band of the spherical harmonic.
     @param     argument	The argument of the spherical harmonic.
     @param     x        The cosinus of the elevation.
     @return    The function return the associated Legendre polynomial P(l, m)(x).
     
     @see    spherical_harmonic_elevation
     @see    spherical_harmonic_azimuth
     @see    spherical_harmonic
     */
    inline double spherical_harmonic_elevation(int band, int argument, double elevation) // With l = band and m the argument
	{
        // Yel(l, m)(x, y) = sqrt(((2l + 1) / 4Pi) * (l - m)! / (l + m)!) P(l, m)(cos(elevation))

        double normalize;
        if(abs(argument) == 0)
			normalize = sqrt( ((2. * band + 1) / (4*CICM_PI)));
            //normalize = sqrt((2. * band + 1) * (double)factorial(band - abs(argument)) / (double)factorial(band + abs(argument)));
       else
			normalize = sqrt( ((2. * band + 1) / (4*CICM_PI)) * (double)factorial(band - abs(argument)) / (double)factorial(band + abs(argument))) * sqrt(2.);
		//if (band == 0)
		//	normalize /= sqrt(2)*0.5;
		
			//normalize = sqrt((double)factorial(band - abs(argument)) / (double)factorial(band + abs(argument)));
        
		
        return  normalize * associated_legendre(band, argument, cos(elevation));
	}
    
    inline double spherical_harmonic_azimuth(int band, int argument, double azimuth) // With l = band and m the argument
	{
        return 0;
	}
    
    inline double spherical_harmonic(int band, int argument, double azimuth, double elevation) // With l = band and m the argument
	{
        // Y(l, m)(x, y) = Yel(l, m)(y) * Yaz(l, m)(x)
        return spherical_harmonic_elevation(band, argument, elevation) * spherical_harmonic_azimuth(band, argument, azimuth);
	}
    
    inline double wrap(const double value, const double low, const double high)
    {
        double new_value = value;
        double increment = high - low;
        while(new_value < low)
        {
            new_value += increment;
        }
        
        while(new_value > high)
        {
            new_value -= increment;
        }
        
        return new_value;
    }
    
    inline double wrap_twopi(const double value)
    {
        double new_value = value;
        while(new_value < 0.)
        {
            new_value += CICM_2PI;
        }
        
        while(new_value > CICM_2PI)
        {
            new_value -= CICM_2PI;
        }
        return new_value;
    }
    
    inline double clip_minmax(const double value, const double low, const double high)
    {
        if(value < low)
            return low;
        else if(value > high)
            return high;
        else
            return value;
    }
    
    inline double clip_min(const double value, const double low)
    {
        if(value < low)
            return low;
        else
            return value;
    }
    
    inline double clip_max(const double value, const double high)
    {
        if(value > high)
            return high;
        else
            return value;
    }
    
    inline std::string intToString(int aValue)
    {
        char number[256];
        sprintf(number, "%i", aValue);
        return number;
    }
    
    inline double radius(const double x, const double y)
	{
		return sqrt(x*x + y*y);
	}
    
	inline double angle(const double x, const double y)
	{
		return atan2(y, x) + CICM_PI2;
	}
    
	inline double ordinate(const double radius, const double angle)
	{
		return radius * sin(angle - CICM_PI2);
	}
    
    inline double abscissa(const double radius, const double angle)
	{
		return radius * cos(angle - CICM_PI2);
	}
}



#endif
