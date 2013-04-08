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


#ifndef DEF_AMBISONICWIDER
#define DEF_AMBISONICWIDER
#define NUMBEROFCIRCLEPOINTS 3600
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <gsl/gsl_sf.h>
#include "cicmTools.h"

class AmbisonicEase
{
private:
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;
	long*	m_index_of_harmonics;

	double      m_widen_value;
	double      m_order_weight;
	double*     m_minus_vector;
	double*     m_dot_vector;
    double*     m_widen_vector;
    double*		m_ambiCoeffs;
    double*		m_optimVector;
	double		m_cosLookUp[NUMBEROFCIRCLEPOINTS];
	double		m_sinLookUp[NUMBEROFCIRCLEPOINTS];
    
	void computeVectors();
    void setWidenValue(double aWidenValue);
    void setAzimtuh(double anAngle);
public:
	AmbisonicEase(long anOrder, long aVectorSize = 0);
    
    void setPolarCoordinates(double aRadius, double anAzimuth);
    void setCartesianCoordinates(double anAbscissa, double anOrdinate);
    void setVectorSize(long aVectorSize);
    
    
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();

	~AmbisonicEase();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type aInputs, Type* aOutputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			aOutputs[i] += aInputs * m_ambiCoeffs[i];
	}

	/* Perform block sample */
	template<typename Type> void process(Type* aInputs, Type** aOutputs)
	{
        Type* outputs;
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            outputs = aOutputs[i];
			for(int j = 0; j < m_vector_size; j++)
                outputs[j] += aInputs[j] * m_ambiCoeffs[i];
		}
	}

};



#endif


