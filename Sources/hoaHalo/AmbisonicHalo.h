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

#ifndef DEF_AMBISONICHALO
#define DEF_AMBISONICHALO

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>

#include "AmbisonicEncode.h"
#include "AmbisonicOptim.h"

class AmbisonicHalo 
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_outputs;
	long		m_number_of_inputs;
	long		m_vector_size;
	
	double		m_spread;

	AmbisonicEncode	*m_encoder;
	AmbisonicOptim	*m_optim;

	double	*m_input_vector;
	double	*m_output_vector;
public:
	AmbisonicHalo(long anOrder, long aVectorSize = 0);

	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	double getSpread();

	void	setVectorSize(int aVectorSize);
	void	setAzimuth(double aTheta);
	void	setSpread(double aSpread);

	~AmbisonicHalo();
	
	/* Perform sample by sample  */
	void process(double *anInputs, double* anOutputs, double aTheta)
	{
		m_encoder->setAzimtuh(aTheta);
		process(anInputs, anOutputs);
	}

	void process(float *anInputs, float* anOutputs, float aTheta)
	{
		m_encoder->setAzimtuh(aTheta);
		process(anInputs, anOutputs);
	}
	
	void process(double* anInputs, double* anOutputs)
	{
		double sum = 0.;
		m_encoder->process(0.5, anOutputs);
		anOutputs[0] /= 2.;
		m_optim->process(anOutputs, anOutputs);
		for(int i = 0; i < m_number_of_harmonics; i++)
			sum += anOutputs[i] * anInputs[i];
		m_encoder->process(sum, anOutputs);
	}

	void process(float* anInputs, float* anOutputs)
	{
		float sum = 0.;
		m_encoder->process(0.5f, anOutputs);
		anOutputs[0] /= 2.;
		m_optim->process(anOutputs, anOutputs);
		for(int i = 0; i < m_number_of_harmonics; i++)
			sum += anOutputs[i] * anInputs[i];
		m_encoder->process(sum, anOutputs);
	}

	/* Perform sample block */
	void process(double** anInput, double** anOutputs, double* aTheta)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				m_input_vector[i] = anInput[i][j];
			}
			process(m_input_vector, m_output_vector, aTheta[j]);
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				anOutputs[i][j] = m_output_vector[i];
			}
		}
	}

	void process(float** anInput, float** anOutputs, float* aTheta)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				m_input_vector[i] = anInput[i][j];
			}
			process(m_input_vector, m_output_vector, (double)aTheta[j]);
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				anOutputs[i][j] = m_output_vector[i];
			}
		}
	}
	
	void process(double** anInput, double** anOutputs)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				m_input_vector[i] = anInput[i][j];
			}
			process(m_input_vector, m_output_vector);
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				anOutputs[i][j] = m_output_vector[i];
			}
		}
	}

	void process(float** anInput, float** anOutputs)
	{
		for(int j = 0; j < m_vector_size; j++)
		{
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				m_input_vector[j] = anInput[j][i];
			}
			process(m_input_vector, m_output_vector);
			for(int i = 0; i < m_number_of_harmonics; i++)
			{
				anOutputs[i][j] = m_output_vector[i];
			}
		}
	}
};

#endif