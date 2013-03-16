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


#ifndef define DEF_AMBISONICDIGGER
#define DEF_AMBISONICDIGGER

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <gsl/gsl_sf.h>
#include "mkl.h"

class ambisonicDigger
{
	
private:
	int m_order;
	int m_number_of_harmonics;
	int	m_number_of_microphones;
	int	m_sampling_rate;
	int	m_vector_size;
	std::string m_optimMode;
	
	int*		m_index_of_harmonics;
	double*		m_optimVector;
	
	AmbisonicEncode*	m_encoder;
	ambisonicDecode*	m_decoder;
	gsl_matrix*			m_weights;
	
public:
	ambisonicDigger(int aNumberOfMicrophone, std::string anOptimMode = "basic", int aVectorSize = 0);
	int	 getParameters(std::string aParameter) const;
	void computeIndex();
	void setVectorSize(int aVectorSize);
	void setOptimMode(std::string anOptim);
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();

	~ambisonicDigger();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		vdmul(m_number_of_harmonics, aInputs, m_optimVector, aOutputs);
	}
	
	/* Perform block sample */
	void process(double** aInputs, double** aOutputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			cblas_dcopy(m_vector_size, aInputs[i], 1, aOutputs[i], 1);
			cblas_dscal(m_vector_size, m_optimVector[i], aOutputs[i], 1);
		}
	}
	
	void process(float** aInputs, float** aOutputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			cblas_scopy(m_vector_size, aInputs[i], 1, aOutputs[i], 1);
			cblas_sscal(m_vector_size, m_optimVector[i], aOutputs[i], 1);
		}
	}
};



#endif


