/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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