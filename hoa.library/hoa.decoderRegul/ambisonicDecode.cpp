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
m_order(order), m_numberOfComponents(order*2+1), m_channelNumber(channelNumber), m_optimId("basic")
{
	spkrsAngles = new double[m_channelNumber];
	m_output_vec = gsl_vector_alloc (m_channelNumber);
	m_optimVector   = gsl_vector_alloc (m_numberOfComponents);
	m_harmonicsIndex = new int[m_numberOfComponents];
	
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
	}
	computePseudoInverse();
	computeMaxReOptim();

}

void ambisonicDecode::computeInPhaseOptim()
{
	for (int i = 0; i < m_numberOfComponents; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector, i, pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_harmonicsIndex[i])) * gsl_sf_fact(m_order-abs(m_harmonicsIndex[i])) ) );
	}
}

void ambisonicDecode::computeMaxReOptim()
{
	for (int i = 0; i < m_numberOfComponents; i++) 
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
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_numberOfComponents,m_channelNumber); 
	
	for (int i = 0; i < m_channelNumber; i++){
		for (int j=0; j < m_numberOfComponents; j++) {
			if (m_harmonicsIndex[j]<0)
				gsl_matrix_set(reencod_Mat,j,i,sin(abs(m_harmonicsIndex[j])*spkrsAngles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j,i,cos(abs(m_harmonicsIndex[j])*spkrsAngles[i]));
		}
	}
	m_regularizedDecod_mat = GenericSvdPseudoInverse(reencod_Mat);
	gsl_matrix_free(reencod_Mat);
}

void ambisonicDecode::setSpkrsAngles(double* someSpkrsAngles, int size)
{
	if (size > m_channelNumber) 
		size = m_channelNumber;
	
	memcpy(spkrsAngles, someSpkrsAngles, sizeof(double)*size);
	computePseudoInverse();
}
double*  ambisonicDecode::process(double* input)
{
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_numberOfComponents);
	if (m_optimId == "maxRe" || m_optimId == "inPhase") {
		gsl_vector_mul(&input_vec.vector, m_optimVector);
	}

	gsl_blas_dgemv(CblasNoTrans,1.0, m_regularizedDecod_mat, &input_vec.vector, 0.0,m_output_vec);
	return m_output_vec->data;
}



