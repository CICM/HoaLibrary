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

#ifndef DEF_AMBISONICSPACE
#define DEF_AMBISONICSPACE

#include "cicmTools.h"

class AmbisonicSpace{
	
private:
	long		m_number_of_microphones;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	long		m_vector_size;
    
    double*      m_microphones_coefficients_old;
	double*      m_microphones_coefficients_new;
    double*      m_microphones_coefficients_step;
    long        m_counter;
public:
	AmbisonicSpace(long aNumberOfMicrophones, long aVectorSize = 0);
	
	long getNumberOfMicrophones();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
    double  getCoefficient(long anIndex);

    void setCoefficient(long anIndex, double aCoefficient);
    void setCoefficient(double* aCoefficientVector);
    void setCoefficient(float* aCoefficientVector);
	void setVectorSize(long aVectorSize);
	~AmbisonicSpace();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* anInput, Type *anOutput)
	{
		for (int i = 0; i < m_number_of_microphones; i++)
		{
			anOutput[i]	= anInput[i] * m_microphones_coefficients_old[i];
            m_microphones_coefficients_old[i] += m_microphones_coefficients_step[i];
		}
        if(m_counter++ == m_vector_size)
        {
            for (int i = 0; i < m_number_of_microphones; i++)
            {
                m_microphones_coefficients_step[i] = 0.;
                m_microphones_coefficients_old[i] = m_microphones_coefficients_new[i];
            }
            m_counter = 0;
        }
	}
	
	/* Perform sample block */	
	template<typename Type> void process(Type** anInputVector, Type** anOutputVector)
	{
        Type* anInput;
        Type* anOutput;
		for (int i = 0; i < m_number_of_microphones; i++)
		{
            anInput = anInputVector[i];
            anOutput= anOutputVector[i];
			for(int j = 0; j < m_vector_size; j++)
            {
                anOutput[j]	= anInput[j] * m_microphones_coefficients_old[i];
                m_microphones_coefficients_old[i] += m_microphones_coefficients_step[i];
            }
            m_microphones_coefficients_step[i] = 0.;
            m_microphones_coefficients_old[i] = m_microphones_coefficients_new[i];
		}
	}
	
};

#endif