/*
 *
 * Copyright (C) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, Universite Paris 8, CICM
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

#include "cicmTools.h"

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
    void setAzimuthInDegree(double aDegree);
	void setVectorSize(long aVectorSize);
	~AmbisonicRotate();

	void process(float** anInput)
	{
        float aNegativeHarmonic;
        float aPositiveHarmonic;
		for(int j = 0; j < m_vector_size; j++)
		{
			for (int i = 1; i <= m_order; i++)
			{
                aNegativeHarmonic = anInput[2*i][j];
                aPositiveHarmonic = anInput[2*i-1][j];
				anInput[2*i][j]	= m_harmonicCos[i-1] * aNegativeHarmonic- m_harmonicSin[i-1] * aPositiveHarmonic;
				anInput[2*i-1][j]	= m_harmonicSin[i-1] * aNegativeHarmonic + m_harmonicCos[i-1] * aPositiveHarmonic;
			}
		}
	}
	
};

#endif