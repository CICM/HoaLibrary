/*
 *  ambisonicDecode.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "ambisonicDecode.hpp"

ambisonicDecode::ambisonicDecode(int channels,int order): m_order(order), m_harmonics(order*2+1), m_channels(channels), m_optimId("basic")
{
	m_spkrsAngles		= new double[m_channels];
	m_harmonicsIndex	= new int[m_harmonics];
	
	m_output_vec		= gsl_vector_alloc (channels);
	m_optimVector		= gsl_vector_alloc (m_harmonics);
	
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < m_harmonics; i++)
	{
		m_harmonicsIndex[i] = (int)floor((float)(i-1) / 2.) + 1;
		if (i % 2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}

	
	for(int i = 0; i < channels; i++)
	{
		m_spkrsAngles[i] = (2. * PI / (double)m_channels) * (double)i;
	}
	computePseudoInverse();
	computeMaxReOptim();

}

void ambisonicDecode::computeInPhaseOptim()
{
	for (int i = 0; i < m_harmonics; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector, i, pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_harmonicsIndex[i])) * gsl_sf_fact(m_order-abs(m_harmonicsIndex[i])) ) );
	}
}

void ambisonicDecode::computeMaxReOptim()
{
	for (int i = 0; i < m_harmonics; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector,i,cos(abs(m_harmonicsIndex[i]) * PI / (2*m_order+2)));
	}

}

void ambisonicDecode::setOptimMethod(std::string anOptimId)
{

	
	if(anOptimId == "maxRe" || anOptimId == "inPhase")
	{
		m_optimId = anOptimId;
		if(anOptimId == "maxRe")
			computeMaxReOptim();
		else
			computeInPhaseOptim();
	}
	else {
		m_optimId = "basic";
	}

}
void ambisonicDecode::computePseudoInverse()
{
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_harmonics, m_channels); 
	
	for (int i = 0; i < m_channels; i++)
	{
		for (int j=0; j < m_harmonics; j++) 
		{
			if (m_harmonicsIndex[j] < 0)
				gsl_matrix_set(reencod_Mat,j,i,sin(abs(m_harmonicsIndex[j]) * m_spkrsAngles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j,i,cos(abs(m_harmonicsIndex[j]) * m_spkrsAngles[i]));
		}
	}
	m_regularizedDecod_mat = GenericSvdPseudoInverse(reencod_Mat);
	gsl_matrix_free(reencod_Mat);
}

void ambisonicDecode::setSpkrsAngles(double* someSpkrsAngles, int size)
{
	if (size > m_channels) 
		size = m_channels;
	
	memcpy(m_spkrsAngles, someSpkrsAngles, sizeof(double)*size);
	computePseudoInverse();
}
double*  ambisonicDecode::process(double* input)
{
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_harmonics);
	if (m_optimId == "maxRe" || m_optimId == "inPhase") {
		gsl_vector_mul(&input_vec.vector, m_optimVector);
	}

	gsl_blas_dgemv(CblasNoTrans,1.0, m_regularizedDecod_mat, &input_vec.vector, 0.0,m_output_vec);
	return m_output_vec->data;
}



