/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_CICM_TOOLS
#define DEF_CICM_TOOLS

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
using namespace std;

#define CICM_PI 3.141592653589793238462643383279502884
#define CICM_2PI CICM_PI * 2.
#define CICM_PI2 CICM_PI / 2.
#define CICM_PI4 CICM_PI / 4.

#define round(x) ((fabs(ceil(x) - (x)) < fabs(floor(x) - (x))) ? ceil(x) : floor(x))

class Tools
{
public:
	Tools();
	~Tools();
	template<typename Type> static Type clip(Type aValue, Type aMinimum = 0, Type aMaximum = 1)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		else if(aValue > aMaximum)
			aValue = aMaximum;
		return aValue;
	}

	template<typename Type> static Type clip_min(Type aValue, Type aMinimum = 0)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		return aValue;
	}

	template<typename Type> static Type clip_max(Type aValue, Type aMinimum = 0)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		return aValue;
	}

	template<typename Type> static Type clip_power_of_two(Type aValue)
	{
		if(aValue < 2)
		aValue = 2;
		else if(aValue&(aValue-1) != 0)
		{
			while (aValue&(aValue-1) != 0) 
				aValue--;
		}
		return aValue;
	}

	template<typename Type> static Type log2(Type n)
	{
		return log((double)n) / log(2.);
	}

	template<typename Type> static Type radius(Type x, Type y)
	{
		return sqrt(x*x + y*y);
	}

	template<typename Type> static Type angle(Type x, Type y)
	{
		return atan2(y, x);
	}

	template<typename Type> static Type ordinate(Type radius, Type angle)
	{
		return radius * sin(angle);
	}

	template<typename Type> static Type abscisse(Type radius, Type angle)
	{
		return radius * cos(angle);
	}
	
	template<typename Type> static Type distance_euclidean(Type x1, Type y1, Type x2, Type y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
	
};

#endif