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

#ifndef DEF_AMBISONICORDER
#define DEF_AMBISONICORDER

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>

#include "cicmTools.h"
#include "AmbisonicProjector.h"
#include "AmbisonicRecomposer.h"

class AmbisonicOrder
{
	
private:
	long		m_order_in;
    long		m_order_out;
	long		m_number_of_harmonics_in;
    long		m_number_of_harmonics_out;
	long		m_number_of_outputs;
	long		m_number_of_inputs;
    long		m_number_of_loudspeakers;
	long		m_vector_size;


	ambisonicProjector*  m_projector;
	ambisonicRecomposer* m_recomposer;
    double*              m_vector;
    float*              m_vector_float;
    double**             m_vector_block;
    float**              m_vector_block_float;
public:
	AmbisonicOrder(long anOrderIn, long anOrderOut, long aVectorSize = 0);

	long getOrderIn();
    long getOrderOut();
	long getNumberOfHarmonicsIn();
    long getNumberOfHarmonicsOut();
	long getNumberOfInputs();
	long getNumberOfOutputs();
    long getVectorSize();

	void	setVectorSize(int aVectorSize);

	~AmbisonicOrder();
	
	/* Double */
	/* Perform sample by sample  */

	void process(double* anInputs, double* anOutputs)
	{
		m_projector->process(anInputs, m_vector);
        m_recomposer->process(m_vector, anOutputs);
	}
    
    void process(float* anInputs, float* anOutputs)
	{
		m_projector->process(anInputs, m_vector_float);
        m_recomposer->process(m_vector_float, anOutputs);
	}

	/* Perform sample block */
	void process(double** anInput, double** anOutputs)
	{
		m_projector->process(anInput, m_vector_block);
        m_recomposer->process(m_vector_block, anOutputs);
	}
    
    void process(float** anInput, float** anOutputs)
	{
		m_projector->process(anInput, m_vector_block_float);
        m_recomposer->process(m_vector_block_float, anOutputs);
	}
};

#endif