/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_AMBISONICROTATE
#define DEF_AMBISONICROTATE

#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicRotate : public Ambisonic
{
	
private:    
	double		m_azimuth;
	double*		m_cosLookUp;
	double*		m_sinLookUp;
	double*		m_harmonicSin;
	double*		m_harmonicCos;
	
public:
	AmbisonicRotate(long anOrder = 1, long aVectorSize = 0);
	
	double getAzimuth();
	void setAzimuth(double aTheta);
	~AmbisonicRotate();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
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
	
	
	
	/* Perform sample block */
	void process(double** anInput, double** anOutput, double *aTheta)
	{
        cicm_copy_vec_vec_d(anInput[0], anOutput[0], m_vector_size);
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
        cicm_copy_vec_vec_d(anInput[0], anOutput[0], m_vector_size);
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
        cicm_copy_vec_vec_f(anInput[0], anOutput[0], m_vector_size);
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
        cicm_copy_vec_vec_f(anInput[0], anOutput[0], m_vector_size);
		for (int i = 1; i <= m_order; i++)
		{
			for(int j = 0; j < m_vector_size; j++)
			{
				anOutput[2*i][j]	= m_harmonicCos[i-1] * anInput[2*i][j] - m_harmonicSin[i-1] * anInput[2*i-1][j];
				anOutput[2*i-1][j]	= m_harmonicSin[i-1] * anInput[2*i][j] + m_harmonicCos[i-1] * anInput[2*i-1][j];
			}
		}
	}
    
    inline void process(float** anIOvector)
	{
        float   *negVector, *posVector;
        float   negValue, posValue, cosinus, sinus;
		for (int i = 1; i <= m_order; i++)
		{
            cosinus = m_harmonicCos[i-1];
            sinus   = m_harmonicSin[i-1];
            negVector = anIOvector[2*i];
            posVector = anIOvector[2*i-1];
			for(int j = 0; j < m_vector_size; j++)
			{
                negValue = anIOvector[2*i][j];
                posValue = anIOvector[2*i-1][j];
				negVector[j]	= cosinus * negValue - sinus * posValue;
				posVector[j]	= sinus * negValue + cosinus * posValue;
			}
		}
	}
	
};

#endif