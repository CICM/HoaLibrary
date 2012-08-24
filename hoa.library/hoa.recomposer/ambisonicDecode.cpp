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
m_order(order), m_numberOfComponents(order*2+1), m_channelNumber(channelNumber), m_fishEyeFactor(1)
{
	spkrsAngles = new double[m_channelNumber];
	m_harmonicsIndex = new int[m_numberOfComponents];
	recompMicCoefs = gsl_matrix_alloc(channelNumber, m_numberOfComponents);
	m_output_vec   = gsl_vector_alloc (m_numberOfComponents);
	
	
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < m_numberOfComponents; i++)
	{
		m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
		if (i%2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}

	
	for(int i = 0; i < channelNumber; i++)
	{
		spkrsAngles[i] = (2*PI/channelNumber)*i;
		if(spkrsAngles[i] > PI)
			spkrsAngles[i] -= 2*PI;
	}
	computeMicMatrix();

}
void ambisonicDecode::SetFishEyeFactor(double aFishEyeFactor)
{
	m_fishEyeFactor = aFishEyeFactor;
	computeMicMatrix();
}
void ambisonicDecode::computeMicMatrix()
{
	for (int micIndex = 0; micIndex < m_channelNumber; micIndex++)
	{
		gsl_matrix_set(recompMicCoefs, micIndex, 0, 1);
		for (int orderIndex = 1; orderIndex <= m_order; orderIndex++) 
		{
			//gsl_matrix_set(recompMicCoefs, micIndex, orderIndex * 2 -1, sin(orderIndex*spkrsAngles[micIndex]*m_fishEyeFactor));
			//gsl_matrix_set(recompMicCoefs, micIndex, orderIndex * 2   , cos(orderIndex*spkrsAngles[micIndex]*m_fishEyeFactor));
			gsl_matrix_set(recompMicCoefs, micIndex, orderIndex * 2 -1, 1);
			gsl_matrix_set(recompMicCoefs, micIndex, orderIndex * 2   , 1);
		}
	}
}

double*  ambisonicDecode::process(double* input)
{
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_channelNumber);
	
	gsl_blas_dgemv(CblasTrans,1.0, recompMicCoefs, &input_vec.vector, 0.0,m_output_vec);
	return m_output_vec->data;
	
	return  input;
}



