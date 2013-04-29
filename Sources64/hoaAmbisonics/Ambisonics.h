/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#ifndef DEF_AMBISONICS
#define DEF_AMBISONICS

#include "../cicmDefine.h"
#include "../cicmTools.h"

class Ambisonics
{
protected:
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;
    long	m_sampling_rate;

public:
	Ambisonics(long anOrder = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	long getSamplingRate();
    long getHarmonicIndex(long anIndex);
    long getHarmonicOrder(long anIndex);
    
	void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);

	~Ambisonics();
	
	/* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = inputs[i];
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = inputs[i];
	}
	
	/* Perform block sample */
	inline void process(float** inputs, float** outputs)
	{
        float* input_pointor;
        float* output_pointor;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input_pointor = inputs[i];
            output_pointor = outputs[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				output_pointor[j] = input_pointor[j];
			}
		}
	}
    
    /* Perform block sample */
	inline void process(double** inputs, double** outputs)
	{
        double* input_pointor;
        double* output_pointor;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input_pointor = inputs[i];
            output_pointor = outputs[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				output_pointor[j] = input_pointor[j];
			}
		}
	}
};



#endif


