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
	ambiCoeffs = new double
	ambiCoeffs = new std::vector<double>(order*2+1,0);
	sourceAmbiCoeffs = new std::vector<double>(order*2+1,0);
}

void AmbisonicEncode::computeCoefs(double aTheta)
{
	for (int i = -m_order; i<= m_order; i++) 
	{
		if (i < 0) 
		{
			(*ambiCoeffs)[i+m_order] = sin(-i * aTheta);
		}
		else 
		{
			(*ambiCoeffs)[i+m_order] = cos(i * aTheta);	
		}
	}
}

const std::vector<double>& AmbisonicEncode::process(double aSample)
{
	for (int i = -m_order; i<= m_order; i++) 
	{
		(*sourceAmbiCoeffs)[i+m_order] = (*ambiCoeffs)[i+m_order] * aSample;
	}
	
	return *(sourceAmbiCoeffs);
}

const std::vector<double>& AmbisonicEncode::process(double aSample, double aTheta)
{
	
	computeCoefs(aTheta);

	for (int i = -m_order; i<= m_order; i++) 
	{
		(*sourceAmbiCoeffs)[i+m_order] = (*ambiCoeffs)[i+m_order] * aSample;
	}
	
	return *(sourceAmbiCoeffs);
}


AmbisonicEncode::~AmbisonicEncode()
{
	delete ambiCoeffs;
	delete sourceAmbiCoeffs;
}