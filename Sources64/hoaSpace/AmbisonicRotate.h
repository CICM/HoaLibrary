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

#ifndef DEF_AmbisonicRotate
#define DEF_AmbisonicRotate

#include "../cicmTools.h"

class AmbisonicRotate{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	long		m_vector_size;
	
	double		m_azimuth;
	long*		m_index_of_harmonics;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	double*		m_harmonicSin;
	double*		m_harmonicCos;
	
	void	computeIndex();
	
public:
	AmbisonicRotate(long anOrder, long aVectorSize = 0);
	
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	double getAzimuth();

	void setAzimuth(double aTheta);
	void setVectorSize(long aVectorSize);
	~AmbisonicRotate();
	
	/* Perform sample by sample */
	void process(double* anInput, double *anOutput, double aTheta)
	{
        anOutput[0] = anInput[0];
		for (int i = 1; i < m_order; i++)
		{
			anOutput[2*i]	= cos((long double)(i * aTheta)) * anInput[2*i] - sin((long double)(i * aTheta)) * anInput[2*i-1];
			anOutput[2*i-1]	= sin((long double)(i * aTheta)) * anInput[2*i] + cos((long double)(i * aTheta)) * anInput[2*i-1];
        }
   }

	
	
};

#endif