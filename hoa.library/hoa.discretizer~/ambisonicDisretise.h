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

#ifndef define DEF_AMBISONICDISCRETISE
#define DEF_AMBISONICDISCRETISE

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.h"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicDiscretise{
	
private:
	int m_order;
	int m_nHarmonics;
	int m_nMicrophones;
	std::string m_optimId;
	
	int *m_harmonicsIndex;
	
	gsl_matrix* m_microphones_mat;
	gsl_vector* m_output_vec;
	gsl_vector* m_optimVector;
	
public:
	ambisonicDiscretise(int channelNumber, int order);
	void computeMicrophones();
	void computeMaxReOptim();
	void computeInPhaseOptim();
	void setOptimMethod(std::string anOptimId);
	double*  process(double* input);
};



#endif


