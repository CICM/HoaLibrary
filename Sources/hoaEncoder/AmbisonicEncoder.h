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

#ifndef DEF_AMBISONICENCODER
#define DEF_AMBISONICENCODER

#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicEncoder : public Ambisonic
{
	
private:
	cicm_vector_double*	m_encoder_matrix;
    
	cicm_vector_float	m_harmonics_vector_float;
    cicm_vector_double	m_harmonics_vector_double;
    
    int*				m_index_vector;
	cicm_vector_float	m_vector_float;
    cicm_vector_double	m_vector_double;
    
public:
	AmbisonicEncoder(long anOrder = 1, long aVectorSize = 0);

    void    setVectorSize(long aVectorSize);
	void	setAngle(double anAngle);
    
	~AmbisonicEncoder();
    
    /********************************************************************/
    /**************************** Basic Mode ****************************/
    /********************************************************************/
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double input, double* outputs)
	{
        cicm_product_vec_sca_vec_d(m_harmonics_vector_double, input, outputs, m_number_of_harmonics);
	}

    inline void process(const float input, float* outputs)
	{
        cicm_product_vec_sca_vec_f(m_harmonics_vector_float, input, outputs, m_number_of_harmonics);
	}
    
    inline void process(const double input, double* outputs, const double angle)
	{
		int index = Tools::radian_wrap(angle) * CICM_1OVER2PI_RATIO;
		for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_harmonics_vector_double[i] = m_encoder_matrix[i][index];
        }
		process(input, outputs);
	}
    
    inline void process(const float input, float* outputs, const float angle)
	{
        int index = Tools::radian_wrap(angle) * CICM_1OVER2PI_RATIO;
		for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_harmonics_vector_float[i] = m_encoder_matrix[i][index];
        }
		process(input, outputs);
	}
		
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        double input = ioVector[0];
        process(input, ioVector);
	}
    
    inline void process(float* ioVector)
	{
        float input = ioVector[0];
        process(input, ioVector);
	}
    
    inline void process(double* ioVector, const double angle)
	{
		double input = ioVector[0];
        process(input, ioVector, angle);
	}
    
    inline void process(float* ioVector, const float angle)
	{
        float input = ioVector[0];
        process(input, ioVector, angle);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(inputs, m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void process(const float* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(inputs, m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}
    
	inline void process(const double* inputs, double** outputs, const double* angles)
	{
		int index;
		cicm_vector_double pointor;
        
		for(int i = 0; i < m_vector_size; i++)
        {
			*(m_index_vector+i) = Tools::radian_wrap(*(angles+i)) * CICM_1OVER2PI_RATIO;
        }
        
        cicm_copy_vec_vec_d((double* )inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				outputs[i][j] = pointor[index] * inputs[j];
			}
			//cicm_product_vec_vec_d(inputs, m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* inputs, float** outputs, const float* angles)
	{
		int index;
		cicm_vector_double pointor;
        cicm_vector_float out;	
		for(int i = 0; i < m_vector_size; i++)
        {
			*(m_index_vector+i) = Tools::radian_wrap(*(angles+i)) * CICM_1OVER2PI_RATIO;
        }
        
        cicm_copy_vec_vec_f(inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			out		= outputs[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				//m_vector_float[j] = pointor[index];
				out[j] = pointor[index] * inputs[j];
			}
			//cicm_product_vec_vec_f(inputs, m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
	{
		for(int i = 1; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(ioVectors[0], m_harmonics_vector_double[i], ioVectors[i], m_vector_size);
	}
    
    inline void process(float** ioVectors)
	{
        for(int i = 1; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(ioVectors[0], m_harmonics_vector_float[i], ioVectors[i], m_vector_size);
	}
    
	inline void process(double** ioVectors, const double* angles)
	{
		int index;
		cicm_vector_double pointor;
        
		for(int i = 0; i < m_vector_size; i++)
        {
			m_index_vector[i] = Tools::radian_wrap(angles[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        }
        
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
            cicm_copy_vec_vec_d(ioVectors[0], ioVectors[i], m_vector_size);
			cicm_product_vec_d(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors, const float* angles)
	{
		int index;
		cicm_vector_double pointor;
        
		for(int i = 0; i < m_vector_size; i++)
        {
			m_index_vector[i] = Tools::radian_wrap(angles[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        }
        
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
            cicm_copy_vec_vec_f(ioVectors[0], ioVectors[i], m_vector_size);
			cicm_product_vec_f(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
    
    /********************************************************************/
    /**************************** Add Mode ******************************/
    /********************************************************************/
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processAdd(double anInput, double* outputs)
	{
        cicm_product_sum_vec_sca_vec_d(m_harmonics_vector_double, anInput, outputs, m_number_of_harmonics);
	}
    
    inline void processAdd(float anInput, float* outputs)
	{
        cicm_product_sum_vec_sca_vec_f(m_harmonics_vector_float, anInput, outputs, m_number_of_harmonics);
	}
    
    inline void processAdd(const double anInput, double* outputs, const double angle)
	{
		float angle_value = Tools::radian_wrap(angle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_encoder_matrix[i][(int)(angle_value*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
    
    inline void processAdd(const float anInput, float* outputs, const float angle)
	{
        double angle_value = Tools::radian_wrap(angle) / CICM_2PI;
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_encoder_matrix[i][(int)(angle_value*(double)(NUMBEROFCIRCLEPOINTS-1))];
		process(anInput, outputs);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processAdd(double* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_sum_vec_sca_vec_d(inputs, m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void processAdd(float* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_sum_vec_sca_vec_f(inputs, m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}
    
	inline void processAdd(const double* inputs, double** outputs, const double* angles)
	{
		int index;
		cicm_vector_double pointor;
        
		for(int i = 0; i < m_vector_size; i++)
        {
			m_index_vector[i] = Tools::radian_wrap(angles[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        }
        
        cicm_add_vec_vec_d(inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			cicm_product_vec_d(inputs, m_vector_double, m_vector_size);
            cicm_add_vec_vec_d(m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void processAdd(const float* inputs, float** outputs, const float* angles)
	{
		int index;
		cicm_vector_double pointor;
        
		for(int i = 0; i < m_vector_size; i++)
        {
			m_index_vector[i] = Tools::radian_wrap(angles[i]) / CICM_2PI * (double)(NUMBEROFCIRCLEPOINTS-1);
        }
        
        cicm_add_vec_vec_f(inputs, outputs[0], m_vector_size);
		for(int i = 1; i < m_number_of_harmonics; i++)
		{
			pointor = m_encoder_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			cicm_product_vec_f(inputs, m_vector_float, m_vector_size);
            cicm_add_vec_vec_f(m_vector_float, outputs[i], m_vector_size);
		}
	}    
};

#endif