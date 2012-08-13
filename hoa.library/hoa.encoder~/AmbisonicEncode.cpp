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

const std::vector<double>& AmbisonicEncode::process(double aSample, double aTheta)
{
	
	computeCoefs(aTheta);	
	return process(aSample);
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