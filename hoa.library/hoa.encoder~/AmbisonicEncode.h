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


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "math.h"
#include <complex>
#include <stdio.h>

class AmbisonicEncode {
	
private:
	int			m_order;
	double		sourceTheta;
	double		*ambiCoeffs;
	double		*sourceAmbiCoeffs;


	

	
public:
	AmbisonicEncode(int order);
	
	void computeCoefs(double aTheta);
	const std::vector<double>& process(double aSample);
	const std::vector<double>& process(double aSample, double aTheta);
	
	~AmbisonicEncode();
	
};

#endif