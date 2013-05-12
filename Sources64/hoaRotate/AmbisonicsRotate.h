/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef DEF_AMBISONICSROTATE
#define DEF_AMBISONICSROTATE

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsRotate : public Ambisonics
{
	
private:
	
	double		m_azimuth;
	long*		m_index_of_harmonics;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	double*		m_harmonicSin;
	double*		m_harmonicCos;
	
	void	computeIndex();
	
public:
	AmbisonicsRotate(long anOrder = 1, long aVectorSize = 0);
	
	double getAzimuth();
	void setAzimuth(double aTheta);
	~AmbisonicsRotate();
	
	/* Perform sample by sample */
	void process(float* anInput, float *anOutput, float aTheta)
	{
		setAzimuth(aTheta);
		process(anInput, anOutput);
	}
    
    void process(double* anInput, double *anOutput, double aTheta)
	{
		setAzimuth(aTheta);
		process(anInput, anOutput);
	}
	
	void process(float* anInput, float *anOutput)
	{
		anOutput[0] = anInput[0];
		for (int i = 1; i < m_order; i++)
		{
			anOutput[2*i]	= m_harmonicCos[i-1] * anInput[2*i] - m_harmonicSin[i-1] * anInput[2*i-1];
			anOutput[2*i-1]	= m_harmonicSin[i-1] * anInput[2*i] + m_harmonicCos[i-1] * anInput[2*i-1];
		}
	}
    
    void process(double* anInput, double *anOutput)
	{
		anOutput[0] = anInput[0];
		for (int i = 1; i < m_order; i++)
		{
			anOutput[2*i]	= m_harmonicCos[i-1] * anInput[2*i] - m_harmonicSin[i-1] * anInput[2*i-1];
			anOutput[2*i-1]	= m_harmonicSin[i-1] * anInput[2*i] + m_harmonicCos[i-1] * anInput[2*i-1];
		}
	}
	
	/* Perform sample block */
	void process(double** anInput, double** anOutput, double *aTheta)
	{
        Cicm_Vector_Double_Copy(anInput[0], anOutput[0], m_vector_size);
		for(int j = 0; j < m_vector_size; j++)
		{
			setAzimuth(aTheta[j]);
			for (int i = 1; i <= m_order; i++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
	
	void process(double** anInput, double **anOutput)
	{
        Cicm_Vector_Double_Copy(anInput[0], anOutput[0], m_vector_size);
		for (int i = 1; i <= m_order; i++)
		{
			for(int j = 0; j < m_vector_size; j++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
    
    
    void process(float** anInput, float **anOutput, float *aTheta)
	{
        Cicm_Vector_Float_Copy(anInput[0], anOutput[0], m_vector_size);
        for(int j = 0; j < m_vector_size; j++)
		{
			setAzimuth(aTheta[j]);
			for (int i = 1; i <= m_order; i++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
    
    void process(float** anInput, float **anOutput)
	{
        Cicm_Vector_Float_Copy(anInput[0], anOutput[0], m_vector_size);
		for (int i = 1; i <= m_order; i++)
		{
			for(int j = 0; j < m_vector_size; j++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
	
};

#endif