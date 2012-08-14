/*
 *  AmbisonicEncode.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef define DEF_AMBISONICENCODE
#define DEF_AMBISONICENCODE

#undef	check



#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>

class AmbisonicEncode {
	
private:
	int m_order;
	double sourceTheta;
	int *m_harmonicsIndex;
	std::vector<double>* ambiCoeffs;
	std::vector<double>* sourceAmbiCoeffs;
	long m_nbOfCirclePoints;
	double* m_cosLookUp;
	double* m_sinLookUp;
	

public:
	AmbisonicEncode(int order);
	
	void computeCoefs(double aTheta);
	const std::vector<double>& process(double aSample);
	const std::vector<double>& process(double aSample, double aTheta);
	const std::vector<double>& process(double* aSample);
	const std::vector<double>& process(double* aSample, double aTheta);
	~AmbisonicEncode();
	
};

#endif