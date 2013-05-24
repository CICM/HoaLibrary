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
	
	Cicm_Vector_Float	m_ambisonics_coeffs_float;
    Cicm_Vector_Double	m_ambisonics_coeffs_double;
    
	Cicm_Vector_Float	m_angles_float;
	Cicm_Vector_Float	m_cos_float;
    Cicm_Vector_Float	m_sin_float;
    Cicm_Vector_Double	m_angles_double;
	Cicm_Vector_Double	m_cos_double;
    Cicm_Vector_Double	m_sin_double;
    
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
        Cicm_Vector_Scalar_Double_Mul(m_ambisonics_coeffs_double, &anInput, anOutputs, m_number_of_harmonics);
        anOutputs[0] = anInput;
	}
    
    inline void process(float anInput, float* anOutputs, float aTheta)
	{
		setAzimtuh((float)aTheta);
		return process(anInput, anOutputs);
	}
	
	inline void process(float anInput, float* anOutputs)
	{
        Cicm_Vector_Scalar_Float_Mul(m_ambisonics_coeffs_float, &anInput, anOutputs, m_number_of_harmonics);
        anOutputs[0] = anInput;
	}
	
    /* Perform sample block */    
	inline void process(double* anInput, double** anOutputs, double* aTheta)
	{
        Cicm_Vector_Double_Copy(anInput, anOutputs[0], m_vector_size);
        double j = 1;
        int size = m_vector_size;
        for (int i = 2; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(aTheta, &j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInput, m_sin_double, anOutputs[i-1], size);
            Cicm_Matrix_Vector_Double_Mul(anInput, m_cos_double, anOutputs[i], size);
        }
	}
	
	inline void process(double* anInput, double** anOutputs)
	{
		Cicm_Vector_Double_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 2; i < m_number_of_harmonics; i += 2)
        {
            Cicm_Vector_Scalar_Double_Mul(anInput, &m_ambisonics_coeffs_double[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(anInput, &m_ambisonics_coeffs_double[i], anOutputs[i], m_vector_size);
        }
	}
    
    inline void process(float* anInput, float** anOutputs, float* aTheta)
	{
        Cicm_Vector_Float_Copy(anInput, anOutputs[0], m_vector_size);
        float j = 1;
        int size = m_vector_size;
        for (int i = 2; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(aTheta, &j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInput, m_sin_float, anOutputs[i-1], size);
            Cicm_Matrix_Vector_Float_Mul(anInput, m_cos_float, anOutputs[i], size);
        }
	}
	
	inline void process(float* anInput, float** anOutputs)
	{
		Cicm_Vector_Float_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 2; i < m_number_of_harmonics; i += 2)
        {
            Cicm_Vector_Scalar_Float_Mul(anInput, &m_ambisonics_coeffs_float[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Float_Mul(anInput, &m_ambisonics_coeffs_float[i], anOutputs[i], m_vector_size);
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
        Cicm_Vector_Double_Copy(anInputs[0], anOutputs[0], m_vector_size);
        double j = 1;
        for (int i = 2, size = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(aTheta, &j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, &size);
            Cicm_Matrix_Vector_Double_Mul(anInputs[(int)j], m_sin_double, anOutputs[i-1], size);
            Cicm_Matrix_Vector_Double_Mul(anInputs[(int)j], m_cos_double, anOutputs[i], size);
        }
	}
	
	inline void process(double** anInputs, double** anOutputs)
	{
		Cicm_Vector_Double_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(anInputs[j], &m_ambisonics_coeffs_double[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(anInputs[j], &m_ambisonics_coeffs_double[i], anOutputs[i], m_vector_size);
        }
	}
    
    inline void process(float** anInputs, float** anOutputs, float* aTheta)
	{
        Cicm_Vector_Float_Copy(anInputs[0], anOutputs[0], m_vector_size);
        float j = 1;
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(aTheta, &j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, &size);
            Cicm_Matrix_Vector_Float_Mul(anInputs[(int)j], m_sin_float, anOutputs[i-1], size);
            Cicm_Matrix_Vector_Float_Mul(anInputs[(int)j], m_cos_float, anOutputs[i], size);
        }
	}
	
	inline void process(float** anInputs, float** anOutputs)
	{
        Cicm_Vector_Float_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(anInputs[j], &m_ambisonics_coeffs_float[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Float_Mul(anInputs[j], &m_ambisonics_coeffs_float[i], anOutputs[i], m_vector_size);
        }
	}
	
    /* Perform add sample block */
	inline void processAdd(double* anInput, double** anOutputs, double* aTheta)
	{
        Cicm_Vector_Double_Add(anInput, anOutputs[0], m_vector_size);
        double j = 1;
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(aTheta, &j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, &size);
            vDSP_vmaD(anInput, 1, m_sin_double, 1, anOutputs[i-1], 1, anOutputs[i-1], 1, size);
            vDSP_vmaD(anInput, 1, m_cos_double, 1, anOutputs[i], 1, anOutputs[i], 1, size);
        }
	}
    
    inline void processAdd(double* anInput, double** anOutputs)
	{
		Cicm_Vector_Double_Add(anInput, anOutputs[0], m_vector_size);
        for (int i = 2; i < m_number_of_harmonics; i += 2)
        {
            vDSP_vsmaD(anInput, 1, &m_ambisonics_coeffs_double[i-1], anOutputs[i-1], 1, anOutputs[i-1], 1, m_vector_size);
            vDSP_vsmaD(anInput, 1, &m_ambisonics_coeffs_double[i], anOutputs[i], 1, anOutputs[i], 1, m_vector_size);
        }
	}
    
    inline void processAdd(float* anInput, float** anOutputs, float* aTheta)
	{
        Cicm_Vector_Float_Add(anInput, anOutputs[0], m_vector_size);
        float j = 1;
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(aTheta, &j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, &size);
            vDSP_vma(anInput, 1, m_sin_float, 1, anOutputs[i-1], 1, anOutputs[i-1], 1, size);
            vDSP_vma(anInput, 1, m_cos_float, 1, anOutputs[i], 1, anOutputs[i], 1, size);
        }
	}
    
    inline void processAdd(float* anInput, float** anOutputs)
	{
		Cicm_Vector_Float_Add(anInput, anOutputs[0], m_vector_size);
        for (int i = 2; i < m_number_of_harmonics; i += 2)
        {
            vDSP_vsma(anInput, 1, &m_ambisonics_coeffs_float[i-1], anOutputs[i-1], 1, anOutputs[i-1], 1, m_vector_size);
            vDSP_vsma(anInput, 1, &m_ambisonics_coeffs_float[i], anOutputs[i], 1, anOutputs[i], 1, m_vector_size);
        }
	}	
};

#endif