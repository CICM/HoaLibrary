/*
 *  ambisonicDecode.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "ambisonicDecode.h"

ambisonicDecode::ambisonicDecode(int channelNumber,int order): 
m_order(order), m_numberOfComponents(order*2+1), m_channelNumber(channelNumber), m_fishEyeFactor(1), m_nbOfSampledMatrix(3600)
{
	spkrsAngles = new double[m_channelNumber];
	m_harmonicsIndex = new int[m_numberOfComponents];
	recompMicCoefs = gsl_matrix_alloc(channelNumber, m_numberOfComponents);
	m_output_vec   = gsl_vector_alloc (m_numberOfComponents);
	m_recompMicCoefsSet = new gsl_matrix*[m_nbOfSampledMatrix];
	
	for (int i = 0; i < m_nbOfSampledMatrix; i++) {
		m_recompMicCoefsSet[i] = gsl_matrix_alloc(channelNumber, m_numberOfComponents);
	}
	
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < m_numberOfComponents; i++)
	{
		m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
		if (i%2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}

	
	for(int i = 0; i < m_channelNumber; i++)
	{
		spkrsAngles[i] = (2. * PI / (double)m_channelNumber) * (double)i;
		if(spkrsAngles[i] > PI)
			spkrsAngles[i] -= 2. * PI;
	}

	computeMicMatrixSet();

}

void ambisonicDecode::computeMicMatrix(gsl_matrix* resMatrix, double aFishFactor)
{
	for (int micIndex = 0; micIndex < m_channelNumber; micIndex++)
	{
		gsl_matrix_set(resMatrix, micIndex, 0, 1);
		for (int orderIndex = 1; orderIndex <= m_order; orderIndex++) 
		{
			gsl_matrix_set(resMatrix, micIndex, orderIndex * 2 -1, sin(orderIndex*spkrsAngles[micIndex]*aFishFactor));
			gsl_matrix_set(resMatrix, micIndex, orderIndex * 2   , cos(orderIndex*spkrsAngles[micIndex]*aFishFactor));
		}
	}
}

void ambisonicDecode::computeMicMatrixSet()
{
	double tmpFishEyeFactor;
	for (int matIndex = 0; matIndex < m_nbOfSampledMatrix; matIndex++) 
	{
		tmpFishEyeFactor = (float)matIndex/float(m_nbOfSampledMatrix-1);
		computeMicMatrix(m_recompMicCoefsSet[matIndex], tmpFishEyeFactor);
	}
}

double*  ambisonicDecode::process(double* input, double aFishEyeFactor)
{
	if (aFishEyeFactor > 1) 
		aFishEyeFactor = 1;
	else if (aFishEyeFactor < 0)
		aFishEyeFactor = 0;
		
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_channelNumber);
	gsl_blas_dgemv(CblasTrans,1.0, m_recompMicCoefsSet[(int)round(aFishEyeFactor*(m_nbOfSampledMatrix-1))], &input_vec.vector, 0.0,m_output_vec);
	return m_output_vec->data;
}


