/*
 *  AmbisonicEncode.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "AmbisonicEncode.h"

AmbisonicEncode::AmbisonicEncode(int order)
{	
	m_order = order;
	ambiCoeffs = new std::vector<double>(order*2+1,0);
	sourceAmbiCoeffs = new std::vector<double>(order*2+1,0);
	m_harmonicsIndex = new int[2*m_order+1];
	
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < 2*m_order+1; i++)
	{
		m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
		if (i%2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}
	
	
	m_nbOfCirclePoints = 100000;
	m_cosLookUp = new double[m_nbOfCirclePoints];
	m_sinLookUp = new double[m_nbOfCirclePoints];
	
	for (int i = 0; i < m_nbOfCirclePoints; i++) {
		m_cosLookUp[i] = cos(i*2*M_PI/m_nbOfCirclePoints);
		m_sinLookUp[i] = sin(i*2*M_PI/m_nbOfCirclePoints);
	}
	
}

void AmbisonicEncode::computeCoefs(double aTheta)
{

	
	for (int i = 0; i< m_order*2+1; i++) 
	{
		if (m_harmonicsIndex[i] < 0) 
		{
			(*ambiCoeffs)[i] = sin(abs(m_harmonicsIndex[i]) * aTheta);
		}
		else 
		{
			(*ambiCoeffs)[i] = cos(abs(m_harmonicsIndex[i]) * aTheta);	
		}
	}
}

const std::vector<double>& AmbisonicEncode::process(double aSample)
{
	for (int i = 0; i< 2*m_order+1; i++) 
	{
		(*sourceAmbiCoeffs)[i] = (*ambiCoeffs)[i] * aSample;
	}
	
	return *(sourceAmbiCoeffs);
}

const std::vector<double>& AmbisonicEncode::process(double* aSample)
{
	for (int i = 0; i< 2*m_order+1; i++) 
	{
		(*sourceAmbiCoeffs)[i] = (*ambiCoeffs)[i] * aSample[abs(m_harmonicsIndex[i])];
	}
	
	return *(sourceAmbiCoeffs);
}

//const std::vector<double>& AmbisonicEncode::process(double aSample, double aTheta)
//{
//	static double tmpValue;
//	
//	*(sourceAmbiCoeffs)[0] = aSample;
//	
//	for (int i = 1; i < m_order; i++) {
//		tmpValue = cos(i*aTheta);
//	}
//	
//	computeCoefs(aTheta);	
//	return process(aSample);
//}

const std::vector<double>& AmbisonicEncode::process(double aSample, double aTheta)
{
	
	(*sourceAmbiCoeffs)[0] = aSample;
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0) {
		aTheta = aTheta + ( -floor(aTheta/M_2PI)) * M_2PI;
	}
	double angleFactor = aTheta*m_nbOfCirclePoints/(M_2PI);
	
	for (int i = 1; i <= m_order; i++) {
		
//		(*sourceAmbiCoeffs)[tmpIndex]   = cos(i*aTheta);
//		(*sourceAmbiCoeffs)[tmpIndex-1] = aSample * sqrt(1. - (*sourceAmbiCoeffs)[tmpIndex] * (*sourceAmbiCoeffs)[tmpIndex]);
//		(*sourceAmbiCoeffs)[tmpIndex]  *= aSample;
//		(*sourceAmbiCoeffs)[tmpIndex]   = aSample * cos(i*aTheta);
//		(*sourceAmbiCoeffs)[tmpIndex-1] = aSample * sin(i*aTheta);
		tmpAngle = (long)(i*angleFactor)%(m_nbOfCirclePoints-1);
		(*sourceAmbiCoeffs)[tmpIndex-1] = aSample * m_sinLookUp[tmpAngle];
		(*sourceAmbiCoeffs)[tmpIndex]   = aSample * m_cosLookUp[tmpAngle];

		tmpIndex += 2;
	}
	

	return *(sourceAmbiCoeffs);
}

const std::vector<double>& AmbisonicEncode::process(double* aSample, double aTheta)
{
	
	computeCoefs(aTheta);	
	return process(aSample);
}


AmbisonicEncode::~AmbisonicEncode()
{
	delete ambiCoeffs;
	delete sourceAmbiCoeffs;
}