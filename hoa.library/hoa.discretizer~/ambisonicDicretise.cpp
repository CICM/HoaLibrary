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

#include "ambisonicDiscretise.h"

ambisonicDiscretise::ambisonicDiscretise(int nMicrophones,int order): m_order(order), m_nHarmonics(order * 2 + 1), m_nMicrophones(nMicrophones), m_optimId("basic")
{
	m_output_vec	= gsl_vector_alloc (m_nMicrophones);
	m_optimVector   = gsl_vector_alloc (m_nHarmonics);

	computeMicrophones();
	setOptimMethod(m_optimId);
}

void ambisonicDiscretise::computeInPhaseOptim()
{
	for (int i = 0; i < m_nHarmonics; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector, i, pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_harmonicsIndex[i])) * gsl_sf_fact(m_order-abs(m_harmonicsIndex[i])) ) );
	}
}

void ambisonicDiscretise::computeMaxReOptim()
{
	for (int i = 0; i < m_nHarmonics; i++) 
	{
		if (i == 0) 
			gsl_vector_set(m_optimVector, i, 1);
		else 
			gsl_vector_set(m_optimVector,i,cos(abs(m_harmonicsIndex[i]) * PI / (2*m_order+2)));
	}

}

void ambisonicDiscretise::setOptimMethod(std::string anOptimId)
{
	if(anOptimId == "maxRe" || anOptimId == "inPhase")
	{
		m_optimId = anOptimId;
		if(anOptimId == "maxRe")
			computeMaxReOptim();
		else
			computeInPhaseOptim();
	}
	else 
	{
		m_optimId = "basic";
	}

}

void ambisonicDiscretise::computeMicrophones()
{
	m_microphones_mat = gsl_matrix_alloc(m_nHarmonics, m_nMicrophones); 
	double aTheta;
	int aIndex;
	
	for (int i = 0; i < m_nMicrophones; i++)
	{
		aTheta = ((double)i / (double)m_nMicrophones) * PI * 2.;
		for (int j = 0; j < m_nHarmonics; j++) 
		{
			aIndex = (int)((j - 1) / 2) + 1;
			if (j % 2 == 1)
				aIndex = -aIndex;
			
			if (aIndex < 0)
				gsl_matrix_set(m_microphones_mat, j, i,sin((double)abs(aIndex) * aTheta));
			else 
				gsl_matrix_set(m_microphones_mat, j, i,cos((double)abs(aIndex) * aTheta));
		}
	}
}

double*  ambisonicDiscretise::process(double* input)
{
	gsl_vector_view input_vec = gsl_vector_view_array(input, m_nHarmonics);
	
	if (m_optimId == "maxRe" || m_optimId == "inPhase") 
		gsl_vector_mul(&input_vec.vector, m_optimVector);

	gsl_blas_dgemv(CblasNoTrans, 1.0, m_microphones_mat, &input_vec.vector, 0.0, m_output_vec);
	return m_output_vec->data;
}



