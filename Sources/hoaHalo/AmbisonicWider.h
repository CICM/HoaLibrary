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


#ifndef DEF_AMBISONICWIDER
#define DEF_AMBISONICWIDER

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
//#include <gsl/gsl_sf.h>
#include "cicmTools.h"

class AmbisonicWider
{
private:
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;
	long*	m_index_of_harmonics;

	double	m_widen_value;
	double	m_order_weight;
	double*	m_minus_vector;
	double*	m_dot_vector;

	void computeIndex();
	void computeWidenVector();
public:
	AmbisonicWider(long anOrderlong, long aVectorSize = 0);
	void setWidenValue(double aWidenValue);
	void setVectorSize(long aVectorSize);

	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();

	~AmbisonicWider();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		double weight = (1. - m_widen_value) * m_order_weight + 1.;
		aOutputs[0] = aInputs[0] * weight;
		for(int i = 1; i < m_number_of_harmonics; i++)
			aOutputs[i] = aInputs[i] * weight 
			* Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
	}
	
	template<typename Type> void process(Type* aInputs, Type* aOutputs, Type aWidenValues)
	{			
		setWidenValue(aWidenValues);
		double weight = (1. - m_widen_value) * m_order_weight + 1.;
		aOutputs[0] = aInputs[0] * weight;
		for(int i = 1; i < m_number_of_harmonics; i++)
			aOutputs[i] = aInputs[i] * weight * Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
	}

	/* Perform block sample */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		double weight;
		for(int j = 0; j < m_vector_size; j++)
		{
			weight = (1. - m_widen_value) * m_order_weight + 1.;
			aOutputs[0][j] = aInputs[0][j] * weight;
			for(int i = 1; i < m_number_of_harmonics; i++)
			{
				aOutputs[i][j] = aInputs[i][j] * weight * Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
			}
		}
	}

	template<typename Type> void process(Type** aInputs, Type** aOutputs, Type* aWidenValues)
	{	
		double weight;
		for(int j = 0; j < m_vector_size; j++)
		{
			setWidenValue(aWidenValues[j]);
			weight = (1. - m_widen_value) * m_order_weight + 1.;
			aOutputs[0][j] = aInputs[0][j] * weight;
			for(int i = 1; i < m_number_of_harmonics; i++)
			{
				aOutputs[i][j] = aInputs[i][j] * weight * Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
			}
		}
	}
};



#endif


