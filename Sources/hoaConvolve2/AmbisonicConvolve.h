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
#include "RevConvolve.h"

class AmbisonicConvolve
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	long		m_vector_size;
	double		m_wet;
	double		m_dry;
    
	vector <RevConvolution*> m_convolution;
public:
	AmbisonicConvolve(long anOrder = 4, long aVectorSize = 0);
	long	getOrder();
	long	getNumberOfHarmonics();
	long	getNumberOfInputs();
	long	getNumberOfOutputs();
	void	setVectorSize(long aVectorSize);
	long	getVectorSize();
    void	setWetValue(double aGain);
	double	getWetValue();
    void	setDryValue(double aGain);
	double	getDryValue();

    long getMinimumSize(){return m_convolution[0]->getMinimumSize();};
    long getMaximumSize(){return m_convolution[0]->getMaximumSize();};
    long getNumberOfFFT(){return m_convolution[0]->getNumberOfFFT();};
    
	void	setImpulseResponse(Cicm_Signal* anImpulseResponse, long aSize);
	~AmbisonicConvolve();

	/* Perform sample by sample */
	template<typename Type> inline void process(Type* aInputs, Type* aOutputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
			aOutputs[j] = m_convolution[j]->process(aInputs[j]) * m_wet + m_dry * aInputs[j];
	}
	
	/* Perform sample block */
	template<typename Type> inline void process(Type** aInputs, Type** aOutputs)
	{
        Type* In;
        Type* Out;
		for(int j = 0; j < m_number_of_harmonics; j++)
		{
            In = aInputs[j];
            Out  = aOutputs[j];
			for(int i = 0; i < m_vector_size; i++)
				Out[i] = m_convolution[j]->process(In[i])  * m_wet + m_dry * In[i];
		}
	}
	
};



#endif


