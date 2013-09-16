/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#ifndef DEF_AMBISONICENCODER3D
#define DEF_AMBISONICENCODER3D

#include "../HoaAmbisonics/Ambisonic3D.h"

class AmbisonicEncoder3D : public Ambisonic3D
{
	
private:
    cicm_vector_double*  m_azimuth_matrix;
    cicm_vector_double*  m_elevation_matrix;
    
    cicm_vector_double  m_azimuth_double;
    cicm_vector_float   m_azimuth_float;
    
    cicm_vector_double  m_elevation_double;
    cicm_vector_float   m_elevation_float;
    
    int*                m_index_vector;
    cicm_vector_double  m_vector_double;
    cicm_vector_float   m_vector_float;
    
    void computeMatrices();
public:
	AmbisonicEncoder3D(long anOrder = 1, long aVectorSize = 2, long aSamlingRate = 44100);

	inline void	setAzimuth(double anAzimuth);
    inline void	setElevation(double anElevation);
    inline void setCoordinates(double anAzimuth, double anElevation);
    void setVectorSize(long aVectorSize);
    std::string  getInputName(long anIndex);
    
	~AmbisonicEncoder3D();
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/

    /*********************************** Out Of Place ***********************************/
    
    inline void processAzimtuhElevation(float anInput, float* anOutput, const float anAzimuth, const float anElevation)
    {
        setCoordinates(anAzimuth, anElevation);
        process(anInput, anOutput);
    }
    
	inline void processAzimtuhElevation(double anInput, double* anOutput, const double anAzimuth, const double anElevation)
    {
        setCoordinates(anAzimuth, anElevation);
        process(anInput, anOutput);
    }
    
    inline void processAzimtuh(float anInput, float* anOutput, const float anAzimuth)
    {
        setAzimuth(anAzimuth);
        process(anInput, anOutput);
    }
    
    inline void processAzimtuh(double anInput, double* anOutput, const double anAzimuth)
    {
        setAzimuth(anAzimuth);
        process(anInput, anOutput);
    }
    
    inline void processElevation(float anInput, float* anOutput, const float anElevation)
    {
        setElevation(anElevation);
        process(anInput, anOutput);
    }
    
    inline void processElevation(double anInput, double* anOutput, const double anElevation)
    {
        setElevation(anElevation);
        process(anInput, anOutput);
    }
    
    inline void process(float anInput, float* anOutput)
    {
        cicm_product_vec_sca_vec_f(m_azimuth_float, anInput, anOutput, m_number_of_harmonics);
        cicm_product_vec_f(m_elevation_float, anOutput, m_number_of_harmonics);
    }
    
    inline void process(double anInput, double* anOutput)
    {
        cicm_product_vec_sca_vec_d(m_azimuth_double, anInput, anOutput, m_number_of_harmonics);
        cicm_product_vec_d(m_elevation_double, anOutput, m_number_of_harmonics);
    }
    
    /************************************* In Place *************************************/
    
    inline void processAzimtuhElevation(float* anInputOutput, const float anAzimuth, const float anElevation)
    {
        setCoordinates(anAzimuth, anElevation);
        process(anInputOutput);
    }
    
	inline void processAzimtuhElevation(double* anInputOutput, const double anAzimuth, const double anElevation)
    {
        setCoordinates(anAzimuth, anElevation);
        process(anInputOutput);
    }
    
    inline void processAzimtuh(float* anInputOutput, const float anAzimuth)
    {
        setAzimuth(anAzimuth);
        process(anInputOutput);
    }
    
    inline void processAzimtuh(double* anInputOutput, const double anAzimuth)
    {
        setAzimuth(anAzimuth);
        process(anInputOutput);
    }
    
    inline void processElevation(float* anInputOutput, const float anElevation)
    {
        setElevation(anElevation);
        process(anInputOutput);
    }
    
    inline void processElevation(double* anInputOutput, const double anElevation)
    {
        setElevation(anElevation);
        process(anInputOutput);
    }
    
    inline void process(float* anInputOutput)
    {
        cicm_product_vec_sca_vec_f(m_azimuth_float, anInputOutput[0], anInputOutput, m_number_of_harmonics);
        cicm_product_vec_f(m_elevation_float, anInputOutput, m_number_of_harmonics);
    }
    
    inline void process(double* anInputOutput)
    {
        cicm_product_vec_sca_vec_d(m_azimuth_double, anInputOutput[0], anInputOutput, m_number_of_harmonics);
        cicm_product_vec_d(m_elevation_double, anInputOutput, m_number_of_harmonics);
    }
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processAzimtuhElevation(float* anInput, float** anOutput, const float* anAzimuth, const float* anElevation)
    {
        int index;
        cicm_vector_double vector1;
        cicm_vector_double vector2;
        cicm_copy_vec_vec_f(anInput, anOutput[0], m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            vector2 = m_elevation_matrix[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * vector2[index];
            }
            cicm_product_vec_vec_f(anInput, m_vector_float, anOutput[i], m_vector_size);
        }
    }
    
	inline void processAzimtuhElevation(double* anInput, double** anOutput, const double* anAzimuth, const double* anElevation)
    {
        int index;
        cicm_vector_double vector1;
        cicm_vector_double vector2;
        cicm_copy_vec_vec_d(anInput, anOutput[0], m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            vector2 = m_elevation_matrix[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * vector2[index];
            }
            cicm_product_vec_vec_d(anInput, m_vector_double, anOutput[i], m_vector_size);
        }
    }
    
    inline void processAzimtuh(float* anInput, float** anOutput, const float* anAzimuth)
    {
        int index;
        float elevation;
        cicm_vector_double vector1;
        cicm_copy_vec_vec_f(anInput, anOutput[0], m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anAzimuth[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            elevation = m_elevation_double[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * elevation;
            }
            cicm_product_vec_vec_f(anInput, m_vector_float, anOutput[i], m_vector_size);
        }
    }
    
    inline void processAzimtuh(double* anInput, double** anOutput, const double* anAzimuth)
    {
        int index;
        double elevation;
        cicm_vector_double vector1;
        cicm_copy_vec_vec_d(anInput, anOutput[0], m_vector_size);
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anAzimuth[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            elevation = m_elevation_double[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * elevation;
            }
            cicm_product_vec_vec_d(anInput, m_vector_double, anOutput[i], m_vector_size);
        }
    }
    
    inline void processElevation(float* anInput, float** anOutput, const float* anElevation)
    {
        int index;
        float azimtuh;
        cicm_vector_double vector1;
        cicm_copy_vec_vec_f(anInput, anOutput[0], m_vector_size);
        for(long i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_elevation_matrix[i];
            azimtuh = m_azimuth_double[i];
            for(long j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * azimtuh;
            }
            cicm_product_vec_vec_f(anInput, m_vector_float, anOutput[i], m_vector_size);
        }
    }
    
    inline void processElevation(double* anInput, double** anOutput, const double* anElevation)
    {
        int index;
        double azimtuh;
        cicm_vector_double vector1;
        cicm_copy_vec_vec_d(anInput, anOutput[0], m_vector_size);
        for(long i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_elevation_matrix[i];
            azimtuh = m_azimuth_double[i];
            for(long j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * azimtuh;
            }
            cicm_product_vec_vec_d(anInput, m_vector_double, anOutput[i], m_vector_size);
        }
    }

    inline void process(float* anInput, float** anOutput)
    {
        float factor;
        cicm_copy_vec_vec_f(anInput, anOutput[0], m_vector_size);
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            factor = m_azimuth_double[i] * m_elevation_double[i];
            cicm_product_vec_sca_vec_f(anInput, factor, anOutput[i], m_vector_size);
        }
    }
    
    inline void process(double* anInput, double** anOutput)
    {
        double factor;
        cicm_copy_vec_vec_d(anInput, anOutput[0], m_vector_size);
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            factor = m_azimuth_double[i] * m_elevation_double[i];
            cicm_product_vec_sca_vec_d(anInput, factor, anOutput[i], m_vector_size);
        }
    }
    
    /************************************* In Place *************************************/
    
    inline void processAzimtuhElevation(float** anInputOutput, const float* anAzimuth, const float* anElevation)
    {
        int index;
        cicm_vector_double vector1;
        cicm_vector_double vector2;
        cicm_vector_float intput = anInputOutput[0];
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            vector2 = m_elevation_matrix[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * vector2[index];
            }
            cicm_product_vec_vec_f(intput, m_vector_float, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void processAzimtuhElevation(double** anInputOutput, const double* anAzimuth, const double* anElevation)
    {
        int index;
        cicm_vector_double vector1;
        cicm_vector_double vector2;
        cicm_vector_double intput = anInputOutput[0];
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            vector2 = m_elevation_matrix[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * vector2[index];
            }
            cicm_product_vec_vec_d(intput, m_vector_double, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void processAzimtuh(float** anInputOutput, const float* anAzimuth)
    {
        int index;
        float elevation;
        cicm_vector_double vector1;
        cicm_vector_float intput = anInputOutput[0];
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anAzimuth[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            elevation = m_elevation_double[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * elevation;
            }
            cicm_product_vec_vec_f(intput, m_vector_float, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void processAzimtuh(double** anInputOutput, const double* anAzimuth)
    {
        int index;
        double elevation;
        cicm_vector_double vector1;
        cicm_vector_double intput = anInputOutput[0];
        for(int i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anAzimuth[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(int i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_azimuth_matrix[i];
            elevation = m_elevation_double[i];
            for(int j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * elevation;
            }
            cicm_product_vec_vec_d(intput, m_vector_double, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void processElevation(float** anInputOutput, const float* anElevation)
    {
        int index;
        float azimtuh;
        cicm_vector_double vector1;
        cicm_vector_float intput = anInputOutput[0];
        for(long i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_elevation_matrix[i];
            azimtuh = m_azimuth_double[i];
            for(long j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_float[j] = vector1[index] * azimtuh;
            }
            cicm_product_vec_vec_f(intput, m_vector_float, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void processElevation(double** anInputOutput, const double* anElevation)
    {
        int index;
        double azimtuh;
        cicm_vector_double vector1;
        cicm_vector_double intput = anInputOutput[0];
        for(long i = 0; i < m_vector_size; i++)
        {
            m_index_vector[i] = (Tools::radian_wrap(anElevation[i]) / CICM_2PI) * NUMBEROFCIRCLEPOINTS;
        }
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            vector1 = m_elevation_matrix[i];
            azimtuh = m_azimuth_double[i];
            for(long j = 0; j < m_vector_size; j++)
            {
                index = m_index_vector[j];
                m_vector_double[j] = vector1[index] * azimtuh;
            }
            cicm_product_vec_vec_d(intput, m_vector_double, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void process(float** anInputOutput)
    {
        float factor;
        cicm_vector_float intput = anInputOutput[0];
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            factor = m_azimuth_double[i] * m_elevation_double[i];
            cicm_product_vec_sca_vec_f(intput, factor, anInputOutput[i], m_vector_size);
        }
    }
    
    inline void process(double** anInputOutput)
    {
        double factor;
        cicm_vector_double intput = anInputOutput[0];
        for(long i = 1; i < m_number_of_harmonics; i++)
        {
            factor = m_azimuth_double[i] * m_elevation_double[i];
            cicm_product_vec_sca_vec_d(intput, factor, anInputOutput[i], m_vector_size);
        }
    }
};
#endif