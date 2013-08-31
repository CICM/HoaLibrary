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

#ifndef DEF_AMBISONICSBINAURAL
#define DEF_AMBISONICSBINAURAL

#include "../HoaDecoder/AmbisonicsDecoder.h"

enum
{
    Hoa_Small  = 0,
    Hoa_Large
};

class AmbisonicsBinaural : public Ambisonic
{
	
private:
    long m_Pinnae_size;
    long        m_number_of_loudspeakers;
    long        m_loudspeakers_configurations[10]; 
    
    std::string m_hrtf_root_path;
    std::string m_hrtf_full_path;
    
	bool		m_hrtf_loaded;
    
	cicm_vector_double* m_impulse_left;
	cicm_vector_double* m_impulse_right;
	long                m_impulse_size;
	AmbisonicsDecoder* m_decoder;

    cicm_matrix_float   m_input_matrix;
    cicm_matrix_float   m_impluse_matrix;
    cicm_matrix_float   m_result_matrix;
    
    cicm_matrix_float   m_result_matrix_left;
    cicm_matrix_float   m_result_matrix_right;
    
    cicm_vector_float   m_linear_vector_left;
    cicm_vector_float   m_linear_vector_right;

    long	loadImpulses();
	long	matrixResize(long aVectorSize);
public:
	
	AmbisonicsBinaural(long anOrder = 1, std::string aRootPath = "", long aPinnaeSize = Hoa_Small, double aSamplingRate = 44100, long aVectorSize = 0);
	
    void    setPinnaeSize(long PinnaeSize);
	void    setVectorSize(long aVectorSize);
    void    setSamplingRate(long aSamplingRate);
    long    getGetHrtfLoaded(){return m_hrtf_loaded;};
    long    getHrtfSize(){return m_impulse_size;};
    long    getPinnaeSize(){return m_Pinnae_size;};
    double       getLoudspeakerAngle(long anIndex);
    std::string  getLoudspeakerName(long anIndex);
    
	~AmbisonicsBinaural();
	
	/* Perform Method */

	inline void process(double** aInputs, double** aOutputs)
	{
        if(m_hrtf_loaded == 1)
        {
            double* input;
            /* Record Inputs vectors In The Matrix */
            for (int i = 0; i < m_number_of_harmonics; i++)
            {
                input = aInputs[i];
                for (int j = 0; j < m_vector_size; j++)
                {
                    m_input_matrix[i*m_vector_size+j] = input[j];
                }
            }
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (m_impulse_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                        m_impluse_matrix, m_number_of_harmonics,
                        m_input_matrix,  m_vector_size,
                        0., m_result_matrix,  m_vector_size);
            /* Write On The Tempory Vectors And The Outputs Vectors */
            for (int j = 0; j < m_vector_size; j++)
            {
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j+m_vector_size*m_impulse_size, m_vector_size, m_linear_vector_left  + j, 1);
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j, m_vector_size, m_linear_vector_right + j, 1);

                aOutputs[0][j] = m_linear_vector_left[j];
                aOutputs[1][j] = m_linear_vector_right[j];
            }
			//cicm_add_vec_vec_d(m_linear_vector_left+m_vector_size, m_linear_vector_left, m_impulse_size-1);
			//cicm_add_vec_vec_d(m_linear_vector_right+m_vector_size, m_linear_vector_right, m_impulse_size-1);
            cblas_scopy(m_impulse_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
            cblas_scopy(m_impulse_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);

            cicm_clear_vec_f(m_linear_vector_left+m_impulse_size-1, m_vector_size);
            cicm_clear_vec_f(m_linear_vector_right+m_impulse_size-1, m_vector_size);
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
            float* input;
            /* Record Inputs vectors In The Matrix */
            for (int i = 0; i < m_number_of_harmonics; i++)
            {
                input = aInputs[i];
                for (int j = 0; j < m_vector_size; j++)
                {
                    m_input_matrix[i*m_vector_size+j] = input[j];
                }
            }
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (m_impulse_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                        m_impluse_matrix, m_number_of_harmonics,
                        m_input_matrix,  m_vector_size,
                        0., m_result_matrix,  m_vector_size);
            
            /* Write On The Tempory Vectors And The Outputs Vectors */
            for (int j = 0; j < m_vector_size; j++)
            {
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j+m_vector_size*m_impulse_size, m_vector_size, m_linear_vector_left  + j, 1);
                cblas_saxpy(m_impulse_size,1.f, m_result_matrix+j, m_vector_size, m_linear_vector_right + j, 1);
                
                aOutputs[0][j] = m_linear_vector_left[j];
                aOutputs[1][j] = m_linear_vector_right[j];
            }
            /* Record The Tempory Vectors */
            cblas_scopy(m_impulse_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
            cblas_scopy(m_impulse_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);
            
            cicm_clear_vec_f(m_linear_vector_left+m_impulse_size-1, m_vector_size);
            cicm_clear_vec_f(m_linear_vector_right+m_impulse_size-1, m_vector_size);
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