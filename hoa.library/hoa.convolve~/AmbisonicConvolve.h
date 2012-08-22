/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef define DEF_AMBISONICCONVOLVE
#define DEF_AMBISONICCONVOLVE

#undef	check

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>


class AmbisonicConvolve {
	
private:
	int m_order;
	int *m_harmonicsIndex;
	std::vector<double>* sourceAmbiCoeffs;
	
public:
	AmbisonicConvolve(int order);
	const std::vector<double>& process(double* aSample);
	~AmbisonicConvolve();
	
};

#endif