
/*
 *  ambisonicDecode.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef define DEF_AMBISONICDECODE
#define DEF_AMBISONICDECODE

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.hpp"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicDecode{
	
private:
	int m_order;
	int m_harmonics;
	int m_channels;
	std::string m_optimId;
	
	double		*m_spkrsAngles;
	int			*m_harmonicsIndex;
	
	gsl_matrix	*m_regularizedDecod_mat;
	gsl_vector	*m_output_vec;
	gsl_vector	*m_optimVector;
	
public:
	ambisonicDecode(int channels, int order);
	void computePseudoInverse();
	void computeMaxReOptim();
	void computeInPhaseOptim();
	void setOptimMethod(std::string anOptimId);
	void setSpkrsAngles(double* someSpkrsAngles, int size);
	double*  process(double* input);
};



#endif


