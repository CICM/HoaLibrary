/*
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

#ifndef define DEF_AMBISONICDECODE
#define DEF_AMBISONICDECODE

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.h"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicWeight
{
	
private:
	int			m_order;
	int			m_number_of_harmonics;
	int			m_number_of_outputs;
	int			m_number_of_inputs;
	int			m_vector_size;
	
	int*		m_index_of_harmonics;
	double*		m_speakers_angles;
	double*		m_optimVector;
	std::string m_optimMode;
	
	gsl_vector		*m_input_vector;
	gsl_vector_view *m_input_vector_view;
	gsl_matrix		*m_decoder_matrix;
	gsl_vector		*m_output_vector;
	gsl_vector_view *m_output_vector_view;
	
	
public:
	ambisonicWeight(int anOrder, int aVectorSize = 0, std::string anOptimMode = "basic" );
	int		getParameters(std::string aParameter) const;
	void	computeIndex();
	void	computeAngles();
	void	computePseudoInverse();
	
	void	setOptimMode(std::string anOptim);
	void	computeBasicOptim();
	void	computeReOptim();
	void	computeInPhaseOptim();

	~ambisonicWeight();
	
	/* Perform Method */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for (int j = 0; j < m_vector_size; j++)
		{
			for (int i = 0; i < m_number_of_harmonics; i++)
			{
				gsl_vector_set(&m_input_vector_view[i].vector, i, aInputs[i][j] * m_optimVector[i]);
			}
			
			for (int i = 0; i < m_number_of_harmonics; i++)
			{
				gsl_blas_dgemv(CblasNoTrans, 1.0, m_decoder_matrix, &m_input_vector_view[i].vector, 0.0, &m_output_vector_view[i].vector);
				aOutputs[i][j] = 0.;
				for (int k = 0; k < m_number_of_harmonics; k++)
				{
					aOutputs[i][j] += gsl_vector_get(&m_output_vector_view[i].vector, k);
				}
			}
		}
	}
};



#endif


