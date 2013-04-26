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
    
	Cicm_Signal_Vector_Float	m_angles_float;
	Cicm_Signal_Vector_Float	m_coeffs_float;
    Cicm_Signal_Vector_Double	m_angles_double;
	Cicm_Signal_Vector_Double	m_coeffs_double;
    
public:
	AmbisonicsEncoder(long anOrder = 1, std::string aMode = "basic", long aVectorSize = 0);

	std::string getMode();
    
    void    setVectorSize(long aVectorSize);
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
        double j = 1;
        Cicm_Signal_Vector_Double_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Matrix_Vector_Scalar_Double_Mul(aTheta, &j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_Sinus(m_coeffs_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInput, m_coeffs_double, anOutputs[i-1], size);

            Cicm_Vector_Double_Cosinus(m_coeffs_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInput, m_coeffs_double, anOutputs[i], size);
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
		float j = 1;
        Cicm_Signal_Vector_Float_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Matrix_Vector_Scalar_Float_Mul(aTheta, &j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_Sinus(m_coeffs_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInput, m_coeffs_float, anOutputs[i-1], size);
            
            Cicm_Vector_Float_Cosinus(m_coeffs_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInput, m_coeffs_float, anOutputs[i], size);
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
		double j = 1;
        Cicm_Signal_Vector_Double_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Matrix_Vector_Scalar_Double_Mul(aTheta, &j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_Sinus(m_coeffs_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInputs[(int)j], m_coeffs_double, anOutputs[i-1], size);
            
            Cicm_Vector_Double_Cosinus(m_coeffs_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInputs[(int)j], m_coeffs_double, anOutputs[i], size);
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
		float j = 1;
        Cicm_Signal_Vector_Float_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Matrix_Vector_Scalar_Float_Mul(aTheta, &j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_Sinus(m_coeffs_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInputs[(int)j], m_coeffs_float, anOutputs[i-1], size);
            
            Cicm_Vector_Float_Cosinus(m_coeffs_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInputs[(int)j], m_coeffs_float, anOutputs[i], size);
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