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
    inline int Factorial( int v )
	{
        int result = v;
		if(v == 0)
			return 1;
        
		while(--v > 0)
			result *= v;
        
		return result;
	}
    
    inline int DoubleFactorial( int x )
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
    
    
	inline double Legendre(int band, int argument, double angle)
	{
        band = abs(band);
        argument = abs(argument);
        
		if(band == argument)
        {
			return pow(-1.0f, float(argument)) * pow(1. - angle * angle, 0.5 * argument);
		}
		else if(band == argument + 1)
        {
			return angle * (2 * argument + 1) * Legendre(argument, argument, angle);
		}
        else
        {
            return (angle * (double)(2 * band - 1) * Legendre(band - 1, argument, angle) - (double)(band + argument - 1.) * Legendre(band - 2, argument, angle)) / (double)(band - argument);
        }
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
