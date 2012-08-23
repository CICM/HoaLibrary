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

#include "AmbisonicCentralize.h"

AmbisonicCentralize::AmbisonicCentralize(int order)
{	
	m_order = order;
	ambiCoeffs = new std::vector<double>(order*2+1,0);
	sourceAmbiCoeffs = new std::vector<double>(order*2+1,0);
	m_harmonicsIndex = new int[2*m_order+1];
	weightSources = new double[2*m_order+1];
	
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
	computeCoefs(0.);
}

void AmbisonicCentralize::computeCoefs(double aTheta)
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

const std::vector<double>& AmbisonicCentralize::process(double* aSample)
{
	for (int i = 0; i< 2*m_order+1; i++) 
	{
		(*sourceAmbiCoeffs)[i] = (*ambiCoeffs)[i] * aSample[abs(i)] ;
	}
	
	return *(sourceAmbiCoeffs);
}

const std::vector<double>& AmbisonicCentralize::process(double* aSample, double aRatio, double aTheta)
{
	if(aRatio < 0.) aRatio = 0.;
	else if(aRatio > 1.) aRatio = 1.;
	
	double invRatio = 1.- aRatio;
	double volume = 1. / (1. + aRatio);
	int harmonics = 2 * m_order + 1;
	
	computeCoefs(aTheta);
	
	weightSources[0] = 0.;
	for (int i = 0; i < harmonics; i++) 
		weightSources[0] += aSample[i] * volume;
	
	for (int i = 0; i < harmonics; i++) 
		(*sourceAmbiCoeffs)[i] = (*ambiCoeffs)[i] * weightSources[0] * aRatio + aSample[i] * invRatio;
	
	return *(sourceAmbiCoeffs);
}


AmbisonicCentralize::~AmbisonicCentralize()
{
	delete weightSources;
	delete m_harmonicsIndex;
	delete ambiCoeffs;
	delete sourceAmbiCoeffs;
}