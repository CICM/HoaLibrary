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
#include "ZeroLatencyConvolver.h"
#include "AmbisonicLine.h"

class AmbisonicConvolver
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
    
    long		m_sampling_frequency;
	long		m_vector_size;
    
	double		m_wet;
	double		m_dry;
    double*		m_wet_vector;
	double*		m_dry_vector;
    AmbisonicLine* m_wet_line;
    AmbisonicLine* m_dry_line;
    
    float*      m_impulse_response;
    long        m_impulse_response_size;
    
	vector <ZeroLatencyConvolver*> m_convolution;
    
    void        computeAmbisonicsImpulseResponses();
public:
	AmbisonicConvolver(long anOrder = 4, long aSamplingFrequency = 44100, long aVectorSize = 0);
	long	getOrder();
	long	getNumberOfHarmonics();
	long	getNumberOfInputs();
	long	getNumberOfOutputs();
	void	setVectorSize(long aVectorSize);
	long	getVectorSize();
    void	setSamplingFrequency(long aSamplingFrequency);
	long	getSamplingFrequency();
    void	setWetValue(double aGain);
	double	getWetValue();
    void	setDryValue(double aGain);
	double	getDryValue();
    void    clear();
    
    long getNumberOfFFTs(){return m_convolution[0]->getNumberOfFFTs();};
    long getNumberOfInstance(){return m_convolution[0]->getNumberOfInstance();};
    
	void	setImpulseResponse(float* anImpulResponse, long aSize);
	~AmbisonicConvolver();

	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
			aOutputs[j] = m_convolution[j]->process(aInputs[j]) * m_wet_line->process() + m_dry_line->process() * aInputs[j];
	}
	
	/* Perform sample block */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
        Type *InputVector, *OutputVector;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            InputVector = aInputs[i];
            OutputVector = aOutputs[i];
			for(int j = 0; j < m_vector_size; j++)
				OutputVector[j] = m_convolution[i]->process(InputVector[j]) * m_wet_vector[j] + m_dry_vector[j] * InputVector[j];
		}
	}
	
};



#endif


