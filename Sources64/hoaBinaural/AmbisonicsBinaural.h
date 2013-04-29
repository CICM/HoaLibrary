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

#ifndef DEF_AMBISONICSBINAURAL
#define DEF_AMBISONICSBINAURAL

#include "../HoaAmbisonics/Ambisonics.h"
#include "../HoaDecoder/AmbisonicsDecoder.h"

class AmbisonicsBinaural : public Ambisonics
{
	
private:
    long        m_number_of_loudspeakers;
    long        m_loudspeakers_configurations[10] = {3, 4, 6, 8, 9, 12, 18, 24, 36, 72};
    
    std::string m_hrtf_root_path;
    std::string m_pinna_size;
    std::string m_hrtf_full_path;
	bool		m_hrtf_loaded;
    
	double**            m_impulse_left;
	double**            m_impulse_right;
	long                m_impulse_size;
	AmbisonicsDecoder* m_decoder;

    Cicm_Matrix_Float   m_input_matrix;
    Cicm_Matrix_Float   m_impluse_matrix;
    Cicm_Matrix_Float   m_result_matrix;
    
    Cicm_Matrix_Float   m_result_matrix_left;
    Cicm_Matrix_Float   m_result_matrix_right;
    
    Cicm_Vector_Float   m_linear_vector_left;
    Cicm_Vector_Float   m_linear_vector_right;

    long	loadImpulses();
	long	matrixResize(long aVectorSize);
public:
	
	AmbisonicsBinaural(long anOrder = 1, std::string aRootPath = "", std::string aPinnaSize = "Small", double aSamplingRate = 44100, long aVectorSize = 0);
	
    void    setPinnaSize(std::string pinnaSize);
	void    setVectorSize(long aVectorSize);
    void    setSamplingRate(long aSamplingRate);
    long    getGetHrtfLoaded(){return m_hrtf_loaded;};
    long    getHrtfSize(){return m_impulse_size;};
    std::string getPinnaSize(){return m_pinna_size;};
    
	~AmbisonicsBinaural();
	
	/* Perform Method */

	inline void process(double** aInputs, double** aOutputs)
	{
        if(m_hrtf_loaded == 1)
        {
            /* Record Inputs vectors In The Matrix */
            for (int i = 0; i < m_number_of_harmonics; i++)
            {
                for (int j = 0; j < m_vector_size; j++)
                {
                    m_input_matrix[i*m_vector_size+j] = aInputs[i][j];
                }
            }
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (m_impulse_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                        m_impluse_matrix, m_number_of_harmonics,
                        m_input_matrix,  m_vector_size,
                        0., m_result_matrix,  m_vector_size);
            
            /* Write On The Tempory Vectors And The Outputs Vectors */
            for (int j = 0; j < m_vector_size; j++)
            {
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j, m_vector_size, m_linear_vector_left  + j, 1);
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j+m_vector_size*m_impulse_size, m_vector_size, m_linear_vector_right + j, 1);

                aOutputs[0][j] = m_linear_vector_left[j];
                aOutputs[1][j] = m_linear_vector_right[j];
            }
            /* Record The Tempory Vectors */
            cblas_scopy(m_impulse_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
            cblas_scopy(m_impulse_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);

            Cicm_Vector_Float_Clear(m_linear_vector_left+m_impulse_size-1, m_vector_size);
            Cicm_Vector_Float_Clear(m_linear_vector_right+m_impulse_size-1, m_vector_size);
        }
        else
        {
            for (int j = 0; j < m_vector_size; j++)
            {
                aOutputs[0][j] = 0.;
                aOutputs[1][j] = 0.;
            }
        }
	}
    
	inline void process(float** aInputs, float** aOutputs)
	{
        if(m_hrtf_loaded == 1)
        {
            /* Record Inputs vectors In The Matrix */
            for (int i = 0; i < m_number_of_harmonics; i++)
            {
                for (int j = 0; j < m_vector_size; j++)
                {
                    m_input_matrix[i*m_vector_size+j] = aInputs[i][j];
                }
            }
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (int)(m_impulse_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                        m_impluse_matrix, m_number_of_harmonics,
                        m_input_matrix,  m_vector_size,
                        0., m_result_matrix,  m_vector_size);
            
            /* Write On The Tempory Vectors And The Outputs Vectors */
            for (int j = 0; j < m_vector_size; j++)
            {
                
                cblas_saxpy(m_impulse_size, 1.f, m_result_matrix_left + j, m_vector_size, m_linear_vector_left + j, 1);
                cblas_saxpy(m_impulse_size, 1.f, m_result_matrix_right + j, m_vector_size, m_linear_vector_right + j, 1);
                
                aOutputs[0][j] = m_linear_vector_left[j];
                aOutputs[1][j] = m_linear_vector_right[j];
            }
            /* Record The Tempory Vectors */
            cblas_scopy(m_impulse_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
            cblas_scopy(m_impulse_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);
            
            Cicm_Vector_Float_Clear(m_linear_vector_left+m_impulse_size-1, m_vector_size);
            Cicm_Vector_Float_Clear(m_linear_vector_right+m_impulse_size-1, m_vector_size);
        }
        else
        {
            for (int j = 0; j < m_vector_size; j++)
            {
                aOutputs[0][j] = 0.;
                aOutputs[1][j] = 0.;
            }
        }
	}

};

#endif