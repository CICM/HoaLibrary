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
m_order(order), m_numberOfComponents(order*2+1), m_channelNumber(channelNumber)
{
	spkrsAngles = new double[m_channelNumber];
	m_output_vec = gsl_vector_alloc (m_channelNumber);
	for(int i = 0; i < channelNumber; i++)
	{
		spkrsAngles[i] = (2*PI/channelNumber)*i;
	}
	
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_numberOfComponents,m_channelNumber); 
	
	for (int i = 0; i < m_channelNumber; i++){
		for (int j=-m_order; j <= m_order; j++) {
			if (j<0)
				gsl_matrix_set(reencod_Mat,j+m_order,i,sin(abs(j)*spkrsAngles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j+m_order,i,cos(abs(j)*spkrsAngles[i]));
		}
	}
	m_regularizedDecod_mat = GenericSvdPseudoInverse(reencod_Mat);
}

//std::vector<double>*  ambisonicDecode::process()
//{
//
//	std::vector<double>* blabla = new std::vector<double>(3);
//	return blabla;
//}

double*  ambisonicDecode::process(double* input)
{
	input_vec = gsl_vector_view_array(input, m_numberOfComponents);
	
	gsl_blas_dgemv(CblasNoTrans,1.0, m_regularizedDecod_mat, &input_vec.vector, 0.0,m_output_vec);
	return m_output_vec->data;
}


//void ambisonicDecode::record(double harmonic, int index)
//{
//
//}
