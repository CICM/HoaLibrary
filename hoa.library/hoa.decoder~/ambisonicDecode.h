
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

#undef check


#define PI 3.1415926535897932384626433832795

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "math.h"
#include "matrixInverse.h"
#include <complex>
#include <stdio.h>

class ambisonicDecode{
	
private:
	int m_order;
	int m_channelNumber;	
	
	double *spkrsAngles;
	
	boost::numeric::ublas::matrix<double> *m;
	boost::numeric::ublas::matrix<double> *sourceMatrix;
	boost::numeric::ublas::matrix<double> *pseudoInvertedSpkrsMatrix;
	boost::numeric::ublas::matrix<double,row_major,std::vector<double> > *outputVector;
	
public:
	
	ambisonicDecode(int channelNumber, int order);
	std::vector<double>* process(const double* encodedSignals);

};

#endif