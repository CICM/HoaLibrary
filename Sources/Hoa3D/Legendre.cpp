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
	
	int DoubleFactorial(int x)
	{
		if(x == 0 || x == -1)
        {
			return 1;
		}
        
		int result = x;
		while((x -= 2) > 0)
        {
			result *= x;
		}
        
		return result;
	}
    
	double Legendre(int band, int argument, double angle)
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
            return (angle * (2 * band - 1) * Legendre(band - 1, argument, angle) - (band + argument - 1) * Legendre(band - 2, argument, angle)) / (band - argument);
        }
	}
}

