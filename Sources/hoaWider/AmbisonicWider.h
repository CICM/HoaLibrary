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

#ifndef DEF_AMBISONICWIDER
#define DEF_AMBISONICWIDER

#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicWider : public Ambisonic
{
private:
    cicm_vector_double*	m_wider_matrix;

	cicm_vector_float	m_harmonics_vector_float;
    cicm_vector_double	m_harmonics_vector_double;
    
    int*				m_index_vector;
	cicm_vector_float	m_vector_float;
    cicm_vector_double	m_vector_double;
    
	void computeWidenVector();
public:
	AmbisonicWider(long anOrder = 1, long aVectorSize = 0);
    
	void setWidenValue(double aWidenValue);
	void setVectorSize(long aVectorSize);
    
    std::string  getInputName(long anIndex);
    std::string  getOutputName(long anIndex);
    
	~AmbisonicWider();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
		cicm_product_vec_vec_d(inputs, m_harmonics_vector_double, outputs, m_number_of_harmonics);
	}
    
    inline void process(float* inputs, float* outputs)
	{
		cicm_product_vec_vec_f(inputs, m_harmonics_vector_float, outputs, m_number_of_harmonics);
	}
    
	inline void process(double* inputs, double* outputs, const double aWidenValue)
	{
        double widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(inputs, outputs);
	}
    
    inline void process(float* inputs, float* outputs, const float aWidenValue)
	{
        float widenValue = Tools::clip(aWidenValue, 0., 1.);
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
		process(inputs, outputs);
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        cicm_product_vec_d(m_harmonics_vector_double, ioVector, m_number_of_harmonics);
	}
    
    inline void process(float* ioVector)
	{
        cicm_product_vec_f(m_harmonics_vector_float, ioVector, m_number_of_harmonics);
	}
    
    inline void process(double* ioVector, double aWidenValue)
	{
        double widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
           m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(ioVector);
	}

	inline void process(float* ioVector, float aWidenValue)
	{
        float widenValue = Tools::clip(aWidenValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(ioVector);
	}

    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* const* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(inputs[i], m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(inputs[i], m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}

	inline void process(const double* const* inputs, double** outputs, const double* widenValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			cicm_product_vec_vec_d(inputs[i], m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* const* inputs, float** outputs, const float* widenValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			cicm_product_vec_vec_f(inputs[i], m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(ioVectors[i], m_harmonics_vector_double[i], ioVectors[i], m_vector_size);
	}
    
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(ioVectors[i], m_harmonics_vector_float[i], ioVectors[i], m_vector_size);
	}
    
	inline void process(double** ioVectors, const double* widenValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			cicm_product_vec_d(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors, const float* widenValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(widenValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			cicm_product_vec_f(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
};



#endif


