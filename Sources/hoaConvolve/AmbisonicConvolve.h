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

#ifndef DEF_AMBISONICCONVOLUTION
#define DEF_AMBISONICCONVOLUTION

#include "cicmTools.h"
#include "revConvolve.h"

class AmbisonicConvolve
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	long		m_sampling_rate;
	long		m_vector_size;
	double		m_gain;
	
	vector <GardnerConvolution*> m_convolution;
public:
	AmbisonicConvolve(long anOrder = 4, long aVectorSize = 0);
	long	getOrder();
	long	getNumberOfHarmonics();
	long	getNumberOfInputs();
	long	getNumberOfOutputs();
	void	setVectorSize(long aVectorSize);
	long	getVectorSize();
	void	setGain(double aGain);
	double	getGain();

	void	setImpulseResponse(long aInstance, double* anImpulResponse, long aSize);
	~AmbisonicConvolve();

	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
			aOutputs[j] = m_convolution[j]->process(aInputs[j]) * m_gain + (1. - m_gain) * aInputs[j];
	}
	
	template<typename Type> void process(Type* aInputs, Type* aOutputs, Type aGain)
	{
		setGain(aGain);
		for(int j = 0; j < m_number_of_harmonics; j++)
			aOutputs[j] = m_convolution[j]->process(aInputs[j]) * m_gain + (1. - m_gain) * aInputs[j];
	}
	
	/* Perform sample block */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_harmonics; j++)
				aOutputs[j][i] = m_convolution[j]->process(aInputs[j][i]) + (1. - m_gain) * aInputs[j][i];
		}
	}
	
	template<typename Type> void process(Type** aInputs, Type** aOutputs, Type* aGain)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			setGain(aGain[i]);
			for(int j = 0; j < m_number_of_harmonics; j++)
				aOutputs[j][i] = m_convolution[j]->process(aInputs[j][i]) + (1. - m_gain) * aInputs[j][i];
		}
	}
};



#endif


