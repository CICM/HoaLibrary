/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_DEFS__
#define __DEF_HOA_DEFS__

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

namespace Hoa
{
	enum
	{
		Hoa_Polar  = 0,
		Hoa_Cartesian
	};
	
	typedef struct  coordinatesPolar
	{
		double		radius;
		double		angle;
	} coordinatesPolar;
	
	typedef struct  coordinatesCartesian
	{
		double		x;
		double		y;
	} coordinatesCartesian;
	
	typedef struct  _hoa_rgba
	{
		double      red;
		double      green;
		double      blue;
		double      alpha;
	} t_hoa_rgba;
	
	typedef struct  _hoa_rgb
	{
		double      red;
		double      green;
		double      blue;
	} t_hoa_rgb;
}

#endif


