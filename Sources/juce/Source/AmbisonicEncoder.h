/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef DEF_AMBISONICENCODER
#define DEF_AMBISONICENCODER

#include "cicmTools.h"

class AmbisonicEncoder 
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_outputs;
	long		m_number_of_inputs;
	long		m_vector_size;

	std::string m_mode;
	
	long		*m_index_of_harmonics;
	double*		m_ambiCoeffs;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	

public:
	AmbisonicEncoder(long anOrder, std::string aMode = "basic", long aVectorSize = 0);

	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	std::string getMode();

	void	computeIndex();
	void	setVectorSize(int aVectorSize);
	void	setAzimtuh(double aTheta);

	~AmbisonicEncoder();
	
	/* Perform sample by sample - Basic Mode */
	template<typename Type> void process(Type anInput, Type* anOutputs, Type aTheta)
	{
		setAzimtuh(aTheta);
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
		setAzimtuh(aTheta);	
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
			setAzimtuh(aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInput[i] * m_ambiCoeffs[j];
		}
	}
	
	/*
	template<typename Type> void process(Type* anInput, Type** anOutputs)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInput[i] * m_ambiCoeffs[j];
		}
	}
	*/
	
	template<typename Type> void process(Type* anInput, Type** anOutputs)
	{
		Type* pointeur;
		for (int j = 0; j < m_number_of_harmonics; j++)
		{
			pointeur = anOutputs[j];
			for(int i  = 0; i < m_vector_size; i++)
				pointeur[i] = anInput[i] * m_ambiCoeffs[j];
		}
	}
	 
	/* Perform sample block - Split Mode */
	template<typename Type> void process(Type** anInputs, Type** anOutputs, Type* aTheta)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			setAzimtuh(aTheta[i]);
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