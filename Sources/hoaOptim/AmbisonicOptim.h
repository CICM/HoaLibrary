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


#ifndef DEF_AmbisonicOptim
#define DEF_AMBISONICDECODE

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <gsl/gsl_sf.h>
#include "cicmTools.h"

class AmbisonicOptim
{
	
private:
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;

	std::string m_optimMode;
	
	long*		m_index_of_harmonics;
	double*		m_optimVector;

	void computeIndex();
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();
	
public:
	AmbisonicOptim(long anOrder, std::string anOptimMode = "basic", long aVectorSize = 0);
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	std::string getMode();
	
	void setVectorSize(long aVectorSize);
	void setOptimMode(std::string anOptim);


	~AmbisonicOptim();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
			aOutputs[i] = m_optimVector[i] * aInputs[i];
	}
	
	/* Perform block sample */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			for(int j = 0; j < m_vector_size; j++)
			{
				aOutputs[i][j] = m_optimVector[i] * aInputs[i][j];
			}
		}
	}
};



#endif


