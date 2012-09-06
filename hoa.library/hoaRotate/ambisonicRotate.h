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

#ifndef define DEF_AMBIROTATE
#define DEF_AMBIROTATE


#undef check
#include "math.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#define M_2PI 2*M_PI
#define NUMBEROFCIRCLEPOINTS 100000

class ambisonicRotate{
	
private:
	int m_order;
	int m_number_of_harmonics;
	int m_number_of_inputs;
	int m_number_of_outputs;
	int	m_sampling_rate;
	int	m_vector_size;
	
	int			*m_index_of_harmonics;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	double*		m_harmonicSin;
	double*		m_harmonicCos;
	
public:
	ambisonicRotate(int anOrder, int aVectorSize = 0);
	int		getParameters(std::string aParameter) const;
	void	computeIndex();
	void	setVectorSize(int aVectorSize);
	void	computeTrigo(double aTheta);
	~ambisonicRotate();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* anInput, Type *anOutput, Type aTheta)
	{
		computeTrigo(aTheta);
		process(anInput, anOutput);
	}
	
	template<typename Type> void process(Type* anInput, Type *anOutput)
	{
		anOutput[0] = anInput[0];
		for (int i = 1; i < m_order; i++)
		{
			anOutput[2*i]	= m_harmonicCos[i-1] * anInput[2*i] - m_harmonicSin[i-1] * anInput[2*i-1];
			anOutput[2*i-1]	= m_harmonicSin[i-1] * anInput[2*i] + m_harmonicCos[i-1] * anInput[2*i-1];
		}
	}
	
	/* Perform sample block */
	template<typename Type> void process(Type** anInput, Type **anOutput, Type *aTheta)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			computeTrigo(aTheta[j]);
			anOutput[0][j] = anInput[0][j];
			for (int i = 1; i <= m_order; i++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
	
	template<typename Type> void process(Type** anInput, Type **anOutput)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			anOutput[0][j] = anInput[0][j];
			for (int i = 1; i <= m_order; i++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
	
};

#endif