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

#ifndef DEF_AMBISONICPROJECTOR
#define DEF_AMBISONICPROJECTOR

#include "../HoaAmbisonics/Ambisonic.h"
#include "../HoaAmbisonics/Planewaves.h"

class AmbisonicProjector : public Ambisonic, public Planewaves
{
	
private:
	
	cicm_matrix_float    m_decoder_matrix_float;
    cicm_matrix_double   m_decoder_matrix_double;
    
    cicm_matrix_float    m_input_matrix_float;
    cicm_matrix_double   m_input_matrix_double;
    cicm_matrix_float    m_output_matrix_float;
    cicm_matrix_double   m_output_matrix_double;
    
	void computeMatrix();
    
public:
	AmbisonicProjector(long anOrder = 1, long aNumberOfLoudspeakers = 3, long aVectorSize = 0);
    
    long    getNumberOfInputs();
	long    getNumberOfOutputs();
    void    setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    void    setVectorSize(long aVectorSize);
	~AmbisonicProjector();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
        cicm_product_mat_vec_d(m_decoder_matrix_double, inputs, outputs,m_number_of_loudspeakers,m_number_of_harmonics);
    }
    
    inline void process(const float* inputs, float* outputs)
	{
        cicm_product_mat_vec_f(m_decoder_matrix_float, inputs, outputs, m_number_of_loudspeakers, m_number_of_harmonics);
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double* ioVectors)
    {
        cicm_copy_vec_vec_d(ioVectors, m_input_matrix_double, m_number_of_harmonics);
        process(m_input_matrix_double, ioVectors);
    }
    
    inline void process(float* ioVectors)
    {
        cicm_copy_vec_vec_f(ioVectors, m_input_matrix_float, m_number_of_harmonics);
        process(m_input_matrix_float, ioVectors);
    }
	
	/************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* const* inputs, double** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            cicm_copy_vec_vec_d(inputs[i], m_input_matrix_double+i*Ambisonic::m_vector_size, Ambisonic::m_vector_size);
        }
        cicm_product_mat_mat_d(m_decoder_matrix_double, m_input_matrix_double, m_output_matrix_double, m_number_of_loudspeakers, Ambisonic::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            cicm_copy_vec_vec_d(m_output_matrix_double+i*Ambisonic::m_vector_size, outputs[i], Ambisonic::m_vector_size);
        }        
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            cicm_copy_vec_vec_f(inputs[i], m_input_matrix_float+i*Ambisonic::m_vector_size, Ambisonic::m_vector_size);
        }
        cicm_product_mat_mat_f(m_decoder_matrix_float, m_input_matrix_float, m_output_matrix_float, m_number_of_loudspeakers, Ambisonic::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            cicm_copy_vec_vec_f(m_output_matrix_float+i*Ambisonic::m_vector_size, outputs[i], Ambisonic::m_vector_size);
        }
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            cicm_copy_vec_vec_d(ioVectors[i], m_input_matrix_double+i*Ambisonic::m_vector_size, Ambisonic::m_vector_size);
        }
        cicm_product_mat_mat_d(m_decoder_matrix_double, m_input_matrix_double, m_output_matrix_double, m_number_of_loudspeakers, Ambisonic::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            cicm_copy_vec_vec_d(m_output_matrix_double+i*Ambisonic::m_vector_size, ioVectors[i], Ambisonic::m_vector_size);
        }
    }
    
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            cicm_copy_vec_vec_f(ioVectors[i], m_input_matrix_float+i*Ambisonic::m_vector_size, Ambisonic::m_vector_size);
        }
        cicm_product_mat_mat_f(m_decoder_matrix_float, m_input_matrix_float, m_output_matrix_float, m_number_of_loudspeakers, Ambisonic::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            cicm_copy_vec_vec_f(m_output_matrix_float+i*Ambisonic::m_vector_size, ioVectors[i], Ambisonic::m_vector_size);
        }
	}
};



#endif


