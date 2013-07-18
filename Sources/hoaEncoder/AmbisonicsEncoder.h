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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICSENCODER
#define DEF_AMBISONICSENCODER

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsEncoder : public Ambisonics
{
	
private:
	long m_mode;
	
	Cicm_Vector_Float	m_ambisonics_coeffs_float;
    Cicm_Vector_Double	m_ambisonics_coeffs_double;
    
	Cicm_Vector_Float	m_angles_float;
	Cicm_Vector_Float	m_cos_float;
    Cicm_Vector_Float	m_sin_float;
    
    Cicm_Vector_Double	m_angles_double;
	Cicm_Vector_Double	m_cos_double;
    Cicm_Vector_Double	m_sin_double;
    
public:
	AmbisonicsEncoder(long anOrder = 1, long aMode = Hoa_Basic, long aVectorSize = 0);

	long    getMode();
    
    void    setVectorSize(long aVectorSize);
	void	setAzimuth(double anAngle);
    void    setAzimuth(float anAngle);
    void	setAzimuthBoth(double anAngle);

	~AmbisonicsEncoder();
    
    /********************************************************************/
    /**************************** Basic Mode ****************************/
    /********************************************************************/
    
    /****************************/
	/* Perform sample by sample */
	/****************************/
    
	inline void process(double anInput, double* anOutputs, double anAngle)
	{
		setAzimuth((double)anAngle);
		return process(anInput, anOutputs);
	}
	
	inline void process(double anInput, double* anOutputs)
	{
        Cicm_Vector_Scalar_Double_Mul(m_ambisonics_coeffs_double, anInput, anOutputs, m_number_of_harmonics);
	}
    
    inline void process(float anInput, float* anOutputs, float anAngle)
	{
		setAzimuth((float)anAngle);
		return process(anInput, anOutputs);
	}
	
	inline void process(float anInput, float* anOutputs)
	{
        Cicm_Vector_Scalar_Float_Mul(m_ambisonics_coeffs_float, anInput, anOutputs, m_number_of_harmonics);
	}
	
    /****************************/
    /*** Perform sample block ***/
    /****************************/
    
	inline void process(double* anInput, double** anOutputs, double* anAngle)
	{
        Cicm_Vector_Double_Copy(anInput, anOutputs[0], m_vector_size);
        double j = 1;
        int size = m_vector_size;
        for (int i = 2; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(anAngle, j, m_angles_double, size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, size);
            Cicm_Vector_Vector_Double_Mul(anInput, m_sin_double, anOutputs[i-1], size);
            Cicm_Vector_Vector_Double_Mul(anInput, m_cos_double, anOutputs[i], size);
        }
	}
	
	inline void process(double* anInput, double** anOutputs)
	{
		Cicm_Vector_Double_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 1; i < m_number_of_harmonics; i ++)
        {
            Cicm_Vector_Scalar_Double_Mul(anInput, m_ambisonics_coeffs_double[i], anOutputs[i], m_vector_size);
        }
	}
    
    inline void process(float* anInput, float** anOutputs, float* anAngle)
	{
        Cicm_Vector_Float_Copy(anInput, anOutputs[0], m_vector_size);
        float j = 1;
        int size = m_vector_size;
        for (int i = 2; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(anAngle, j, m_angles_float, size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, size);
            Cicm_Vector_Vector_Float_Mul(anInput, m_sin_float, anOutputs[i-1], size);
            Cicm_Vector_Vector_Float_Mul(anInput, m_cos_float, anOutputs[i], size);
        }
	}
	
	inline void process(float* anInput, float** anOutputs)
	{
		Cicm_Vector_Float_Copy(anInput, anOutputs[0], m_vector_size);
        for (int i = 1; i < m_number_of_harmonics; i ++)
        {
            Cicm_Vector_Scalar_Float_Mul(anInput, m_ambisonics_coeffs_float[i], anOutputs[i], m_vector_size);
        }
	}
    
    /****************************/
    /* Perform add sample block */
    /****************************/
    
	inline void processAdd(double* anInput, double** anOutputs, double* anAngle)
	{
        Cicm_Vector_Double_Add(anInput, anOutputs[0], m_vector_size);
        double j = 1;
        for (int i = 2, size = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(anAngle, j, m_angles_double, size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, size);
            Cicm_Vector_Vector_Double_Mul_And_Add(anInput, m_sin_double, anOutputs[i-1], size);
            Cicm_Vector_Vector_Double_Mul_And_Add(anInput, m_cos_double, anOutputs[i], size);
        }
	}
    
    inline void processAdd(double* anInput, double** anOutputs)
	{
		Cicm_Vector_Double_Add(anInput, anOutputs[0], m_vector_size);
        for (int i = 2; i < m_number_of_harmonics; i += 2)
        {
            /* Trick for INTEL where scalar mul and add don't exist for double precision */
            Cicm_Vector_Scalar_Double_Mul(anInput, m_ambisonics_coeffs_double[i], m_cos_double, m_vector_size);
            Cicm_Vector_Double_Add(m_cos_double, anOutputs[i], m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(anInput, m_ambisonics_coeffs_double[i-1], m_sin_double, m_vector_size);
            Cicm_Vector_Double_Add(m_sin_double, anOutputs[i-1], m_vector_size);
        }
	}
    
    inline void processAdd(float* anInput, float** anOutputs, float* anAngle)
	{
        Cicm_Vector_Float_Add(anInput, anOutputs[0], m_vector_size);
        float j = 1;
        for (int i = 2, size = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(anAngle, j, m_angles_float, size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, size);
            Cicm_Vector_Vector_Float_Mul_And_Add(anInput, m_sin_float, anOutputs[i-1], size);
            Cicm_Vector_Vector_Float_Mul_And_Add(anInput, m_cos_float, anOutputs[i], size);
        }
	}
    
    inline void processAdd(float* anInput, float** anOutputs)
	{
		Cicm_Vector_Float_Add(anInput, anOutputs[0], m_vector_size);
        for (int i = 1; i < m_number_of_harmonics; i ++)
        {
            Cicm_Vector_Scalar_Float_Mul_And_Add(anInput, m_ambisonics_coeffs_float[i], anOutputs[i], m_vector_size);
        }
	}
    
    /********** SPLIT ************************/
    /* Perform sample by sample - Split Mode */
	inline void process(double* anInputs, double* anOutputs, double anAngle)
	{
		setAzimuth((double)anAngle);
		return process(anInputs, anOutputs);
	}
	
	inline void process(double* anInputs, double* anOutputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			anOutputs[i] = m_ambisonics_coeffs_double[i] * anInputs[abs(getHarmonicIndex(i))];
	}
    
    inline void process(float* anInputs, float* anOutputs, float anAngle)
	{
		setAzimuth((float)anAngle);
		return process(anInputs, anOutputs);
	}
	
	inline void process(float* anInputs, float* anOutputs)
	{
		for (int i = 0; i < m_number_of_harmonics; i++)
			anOutputs[i] = m_ambisonics_coeffs_float[i] * anInputs[abs(getHarmonicIndex(i))];
	}
    
    /*************************************/
	/* Perform sample block - Split Mode */
    /*************************************/
    
	inline void process(double** anInputs, double** anOutputs, double* anAngle)
	{
        Cicm_Vector_Double_Copy(anInputs[0], anOutputs[0], m_vector_size);
        double j = 1;
        for (int i = 2, size = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(anAngle, j, m_angles_double, m_vector_size);
            Cicm_Vector_Double_SinCos(m_sin_double, m_cos_double, m_angles_double, size);
            Cicm_Vector_Vector_Double_Mul(anInputs[(int)j], m_sin_double, anOutputs[i-1], size);
            Cicm_Vector_Vector_Double_Mul(anInputs[(int)j], m_cos_double, anOutputs[i], size);
        }
	}
	
	inline void process(double** anInputs, double** anOutputs)
	{
		Cicm_Vector_Double_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Double_Mul(anInputs[j], m_ambisonics_coeffs_double[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(anInputs[j], m_ambisonics_coeffs_double[i], anOutputs[i], m_vector_size);
        }
	}
    
    inline void process(float** anInputs, float** anOutputs, float* anAngle)
	{
        Cicm_Vector_Float_Copy(anInputs[0], anOutputs[0], m_vector_size);
        float j = 1;
        for (int i = 2, size  = m_vector_size; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(anAngle, j, m_angles_float, m_vector_size);
            Cicm_Vector_Float_SinCos(m_sin_float, m_cos_float, m_angles_float, size);
            Cicm_Vector_Vector_Float_Mul(anInputs[(int)j], m_sin_float, anOutputs[i-1], size);
            Cicm_Vector_Vector_Float_Mul(anInputs[(int)j], m_cos_float, anOutputs[i], size);
        }
	}
	
	inline void process(float** anInputs, float** anOutputs)
	{
        Cicm_Vector_Float_Copy(anInputs[0], anOutputs[0], m_vector_size);
        for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
        {
            Cicm_Vector_Scalar_Float_Mul(anInputs[j], m_ambisonics_coeffs_float[i-1], anOutputs[i-1], m_vector_size);
            Cicm_Vector_Scalar_Float_Mul(anInputs[j], m_ambisonics_coeffs_float[i], anOutputs[i], m_vector_size);
        }
	}
	
};

#endif