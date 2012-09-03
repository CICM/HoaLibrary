/*
 *  ambisonicDecode.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "ambisonicDecode.h"

ambisonicDecode::ambisonicDecode(int anOrder, int aSamplingRate, int aVectorSize, int aNumberOfChannels, std::string anOptimMode)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= aNumberOfChannels;
	m_sampling_rate			= aSamplingRate;
	m_vector_size			= aVectorSize;
	if(m_number_of_outputs < m_number_of_harmonics)
		m_number_of_outputs = m_number_of_harmonics;
	
	m_output_vector		= gsl_vector_alloc (m_number_of_outputs);
	m_optimVector		= gsl_vector_alloc (m_number_of_harmonics );
	
	computeIndex();
	computeAngles();
	setOptimMode(anOptimMode);
	computePseudoInverse();
}

int	ambisonicDecode::getParameters(std::string aParameter) const
{
	int value = 0;
	
	if (aParameter == "order") 
		value = m_order;
	else if (aParameter == "samplingRate") 
		value =  m_sampling_rate;
	else if (aParameter == "vectorSize") 
		value =  m_vector_size;
	else if (aParameter == "numberOfInputs") 
		value =  m_number_of_inputs;
	else if (aParameter == "numberOfOutputs") 
		value =  m_number_of_outputs;
	
	return value;
}

void ambisonicDecode::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = floor((i - 1) / 2) + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void ambisonicDecode::computeAngles()
{
	m_speakers_angles		= new double[m_number_of_outputs];
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		m_speakers_angles[i] = (2. * PI / (double)m_number_of_harmonics) * (double)i;
	}
}

void ambisonicDecode::setOptimMode(std::string anOptim)
{
	if(anOptim != m_optimMode)
	{
		if(anOptim == "inPhase")
			computeInPhaseOptim();
		else if(anOptim == "maxRe")
			computeReOptim();
		else
			computeBasicOptim();
	}
}

void ambisonicDecode::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
		gsl_vector_set(m_optimVector, i, 1.);
}

void ambisonicDecode::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_number_of_harmonics ; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector,i,cos(abs(m_index_of_harmonics[i]) * PI / (2*m_order+2)));
	}	
}

void ambisonicDecode::computeInPhaseOptim()
{
	m_optimMode = "inPhase"; 
	
	for (int i = 0; i < m_number_of_harmonics ; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector, i, pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])) ) );
	}
}

void ambisonicDecode::computePseudoInverse()
{
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_number_of_harmonics , m_number_of_outputs); 
	
	for (int i = 0; i < m_number_of_outputs; i++)
	{
		for (int j=0; j < m_number_of_harmonics ; j++) 
		{
			if (m_index_of_harmonics[j] < 0)
				gsl_matrix_set(reencod_Mat,j,i,sin(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j,i,cos(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
		}
	}
	m_decoder_matrix = GenericSvdPseudoInverse(reencod_Mat);
	gsl_matrix_free(reencod_Mat);
}

void ambisonicDecode::setSpkrsAngles(double* someSpkrsAngles, int size)
{
	if (size > m_number_of_outputs) 
		size = m_number_of_outputs;
	
	memcpy(m_speakers_angles, someSpkrsAngles, sizeof(double)*size);
	computePseudoInverse();
}

double*  ambisonicDecode::process(double* input)
{
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_number_of_harmonics );
	gsl_vector_mul(&input_vec.vector, m_optimVector);

	gsl_blas_dgemv(CblasNoTrans,1.0, m_decoder_matrix, &input_vec.vector, 0.0,m_output_vector);
	return m_output_vector->data;
}

ambisonicDecode::~ambisonicDecode()
{
	gsl_matrix_free(m_decoder_matrix);
	gsl_vector_free(m_output_vector);
	delete m_index_of_harmonics;
	delete m_speakers_angles;
	delete m_optimVector;
}

