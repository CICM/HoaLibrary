/*
 *  HoaDistance.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 05/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_HOADISTANCE
#define DEF_HOADISTANCE
#undef check


#include <stdio.h>
#include <iostream>
#include <complex>
#include <MiscMath.h>
#include "SignalVec.h"
#include "FftConvolution.h"
#define PI 3.1415926535897932384626433832795


class HoaDistance{
private:
	int m_order;	
	long m_fftSize;
	long m_fftHalfSize;
	long m_sampleRate;
	
	double m_speakersDistance;
	double m_sourceDistance;
	double m_theta;
	
	double* m_outputArray;
	double* m_tmpOutputArray;
	double* m_frequencyVector;
	std::complex<double>** m_impulseResponses;
	SignalVec* m_halfComplexImpulseResponses;
	
	FftConvolution** ConvolutionArray;
	
public:
	HoaDistance(int order, double speakersDistance, double sourceDistance = 1);
	double* process(double aSample);
	void ComputeResponses();
	void ChangeSourceDistance(double sourceDistance);
	void setTheta(double aTheta);
	
};
#endif