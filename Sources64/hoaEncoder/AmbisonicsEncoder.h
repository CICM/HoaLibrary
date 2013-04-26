/*
 *
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

#ifndef DEF_AMBISONICSENCODER
#define DEF_AMBISONICSENCODER

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsEncoder : public Ambisonics
{
	
private:

	std::string m_mode;
	
	Cicm_Signal_Vector_Float	m_ambisonics_coeffs_float;
    Cicm_Signal_Vector_Double	m_ambisonics_coeffs_double;
    
	Cicm_Signal_Vector_Double	m_cosinus_table;
	Cicm_Signal_Vector_Double	m_sinus_table;
	
public:
	AmbisonicsEncoder(long anOrder = 1, std::string aMode = "basic", long aVectorSize = 0);

	std::string getMode();
	void	setAzimtuh(double aTheta);
    void    setAzimtuh(float aTheta);
    void	setAzimtuhBoth(double aTheta);

	~AmbisonicsEncoder();
    
    /**************************** Basic Mode ****************************/
	/* Perform sample by sample */
	
	inline void process(double anInput, double* anOutputs, double aTheta)
	{
		setAzimtuh((double)aTheta);
		return process(anInput, anOutputs);
	}
	
	inline void process(double anInput, double* anOutputs)
	{
        Cicm_Matrix_Vector_Scalar_Double_Mul(m_ambisonics_coeffs_double, &anInput, anOutputs, m_number_of_harmonics);
	}
    
    inline void process(float anInput, float* anOutputs, float aTheta)
	{
		setAzimtuh((float)aTheta);
		return process(anInput, anOutputs);
	}
	
	inline void process(float anInput, float* anOutputs)
	{
        Cicm_Matrix_Vector_Scalar_Float_Mul(m_ambisonics_coeffs_float, &anInput, anOutputs, m_number_of_harmonics);
	}
	
    /* Perform sample block */    
	inline void process(double* anInput, double** anOutputs, double* aTheta)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			setAzimtuh((double)aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInput[i] * m_ambisonics_coeffs_double[j];
		}
	}
	
	inline void process(double* anInput, double** anOutputs)
	{
		for (int j = 0; j < m_number_of_harmonics; j++)
		{
            Cicm_Matrix_Vector_Scalar_Double_Mul(anInput, m_ambisonics_coeffs_double+j, anOutputs[j], m_vector_size);
		}
	}
    
    inline void process(float* anInput, float** anOutputs, float* aTheta)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			setAzimtuh((float)aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInput[i] * m_ambisonics_coeffs_float[j];
		}
	}
	
	inline void process(float* anInput, float** anOutputs)
	{
		for (int j = 0; j < m_number_of_harmonics; j++)
		{
            Cicm_Matrix_Vector_Scalar_Float_Mul(anInput, m_ambisonics_coeffs_float+j, anOutputs[j], m_vector_size);
		}
	}
    
    /********** SPLIT ************************/
    /* Perform sample by sample - Split Mode */
	inline void process(double* anInputs, double* anOutputs, double aTheta)
	{
		setAzimtuh((double)aTheta);
		return process(anInputs, anOutputs);
	}
	
	inline void process(double* anInputs, double* anOutputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			anOutputs[i] = m_ambisonics_coeffs_double[i] * anInputs[abs(getHarmonicIndex(i))];
	}
    
    inline void process(float* anInputs, float* anOutputs, float aTheta)
	{
		setAzimtuh((float)aTheta);
		return process(anInputs, anOutputs);
	}
	
	inline void process(float* anInputs, float* anOutputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			anOutputs[i] = m_ambisonics_coeffs_float[i] * anInputs[abs(getHarmonicIndex(i))];
	}
    
	/* Perform sample block - Split Mode */
	inline void process(double** anInputs, double** anOutputs, double* aTheta)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			setAzimtuh((double)aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInputs[abs(getHarmonicIndex(j))][i] * m_ambisonics_coeffs_double[j];
		}
	}
	
	inline void process(double** anInputs, double** anOutputs)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			for (int j = 0; j < m_number_of_harmonics; j++) 
				anOutputs[j][i] = anInputs[abs(getHarmonicIndex(j))][i] * m_ambisonics_coeffs_double[j];
		}
	}
    
    inline void process(float** anInputs, float** anOutputs, float* aTheta)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			setAzimtuh((float)aTheta[i]);
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInputs[abs(getHarmonicIndex(j))][i] * m_ambisonics_coeffs_float[j];
		}
	}
	
	inline void process(float** anInputs, float** anOutputs)
	{
		for(int i  = 0; i < m_vector_size; i++)
		{
			for (int j = 0; j < m_number_of_harmonics; j++)
				anOutputs[j][i] = anInputs[abs(getHarmonicIndex(j))][i] * m_ambisonics_coeffs_float[j];
		}
	}
	
	
};

#endif