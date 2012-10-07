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

#ifndef define DEF_AMBISONICENCODE
#define DEF_AMBISONICENCODE

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>


#define	M_PI 3.14159265358979323846264338327950288
#define M_2PI 2*M_PI
#define NUMBEROFCIRCLEPOINTS 360000

class AmbisonicEncode 
{
	
private:
	int			m_order;
	int			m_number_of_harmonics;
	int			m_number_of_outputs;
	int			m_number_of_inputs;
	int			m_vector_size;

	std::string m_mode;
	
	int			*m_index_of_harmonics;
	double*		m_ambiCoeffs;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	

public:
	AmbisonicEncode(int anOrder, std::string aMode = "basic", int aVectorSize = 0);
	int		getParameters(std::string aParameter) const;
	void	computeIndex();
	void	setVectorSize(int aVectorSize);
	void	computeCoefs(double aTheta);
	~AmbisonicEncode();
	
	/* Perform sample by sample - Basic Mode */
	template<typename Type> void process(Type anInput, Type* anOutputs, Type aTheta)
	{
		computeCoefs(aTheta);
		return process(anInput, anOutputs);
	}
	
	template<typename Type> void process(Type anInput, Type* anOutputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++) 
			anOutputs[i] = m_ambiCoeffs[i] * anInput;
	}
	
	/* Perform sample by sample - Split Mode */
	template<typename Type> void process(Type* anInputs, Type* anOutputs, Type aTheta)
	{
		computeCoefs(aTheta);	
		return process(anInputs, anOutputs);
	}
	
	template<typename Type> void process(Type* anInputs, Type* anOutputs)
	{
		for (int i = 0; i< m_number_of_harmonics; i++) 
			anOutputs[i] = m_ambiCoeffs[i] * anInputs[m_index_of_harmonics[i]];
	}

	/* Perform sample block - Basic Mode */
	template<typename Type> void process(Type* anInput, Type** anOutputs, Type* aTheta)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			computeCoefs(aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInput[i] * m_ambiCoeffs[j];
		}
	}
	
	template<typename Type> void process(Type* anInput, Type** anOutputs)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInput[i] * m_ambiCoeffs[j];
		}
	}
	
	/* Perform sample block - Split Mode */
	template<typename Type> void process(Type** anInputs, Type** anOutputs, Type* aTheta)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			computeCoefs(aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInputs[abs(m_index_of_harmonics[j])][i] * m_ambiCoeffs[j];
		}
	}
	
	template<typename Type> void process(Type** anInputs, Type** anOutputs)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInputs[abs(m_index_of_harmonics[j])][i] * m_ambiCoeffs[j];
		}
	}
	
	
};

#endif