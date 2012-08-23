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

#ifndef define DEF_AMBISONICENTRALIZE
#define DEF_AMBISONICENTRALIZE

#undef	check

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>

#define M_2PI 2*M_PI

class AmbisonicCentralize {
	
private:
	int m_order;
	double sourceTheta;
	int *m_harmonicsIndex;
	std::vector<double>* ambiCoeffs;
	std::vector<double>* sourceAmbiCoeffs;
	double *weightSources;
	long m_nbOfCirclePoints;
	double* m_cosLookUp;
	double* m_sinLookUp;
	

public:
	AmbisonicCentralize(int order);
	
	void computeCoefs(double aTheta);
	const std::vector<double>& process(double* aSample);
	const std::vector<double>& process(double* aSample, double aRatio, double aTheta);
	~AmbisonicCentralize();
	
};

#endif