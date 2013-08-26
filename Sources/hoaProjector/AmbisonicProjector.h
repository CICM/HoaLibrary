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

#include "../HoaAmbisonics/Ambisonics.h"
#include "../HoaAmbisonics/Planewaves.h"

class AmbisonicProjector : public Ambisonics, public Planewaves
{
	
private:
	
	Cicm_Matrix_Float    m_decoder_matrix_float;
    Cicm_Matrix_Double   m_decoder_matrix_double;
    
    Cicm_Matrix_Float    m_input_matrix_float;
    Cicm_Matrix_Double   m_input_matrix_double;
    Cicm_Matrix_Float    m_output_matrix_float;
    Cicm_Matrix_Double   m_output_matrix_double;
    
	void computeMatrix();
    
public:
	AmbisonicProjector(long anOrder = 1, long aNumberOfLoudspeakers = 3, long aVectorSize = 0);
    
    void    setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    void    setVectorSize(long aVectorSize);
	~AmbisonicProjector();
	
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
        Cicm_Matrix_Vector_Double_Product(m_decoder_matrix_double, inputs, outputs,m_number_of_loudspeakers,m_number_of_harmonics);
    }
    
    inline void process(const float* inputs, float* outputs)
	{
        Cicm_Matrix_Vector_Float_Product(m_decoder_matrix_float, inputs, outputs, m_number_of_loudspeakers, m_number_of_harmonics);
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double* ioVectors)
    {
        Cicm_Vector_Double_Copy(ioVectors, m_input_matrix_double, m_number_of_harmonics);
        process(m_input_matrix_double, ioVectors);
    }
    
    inline void process(float* ioVectors)
    {
        Cicm_Vector_Float_Copy(ioVectors, m_input_matrix_float, m_number_of_harmonics);
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
            Cicm_Vector_Double_Copy(inputs[i], m_input_matrix_double+i*Ambisonics::m_vector_size, Ambisonics::m_vector_size);
        }
        Cicm_Matrix_Matrix_Double_Product(m_decoder_matrix_double, m_input_matrix_double, m_output_matrix_double, m_number_of_loudspeakers, Ambisonics::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            Cicm_Vector_Double_Copy(m_output_matrix_double+i*Ambisonics::m_vector_size, outputs[i], Ambisonics::m_vector_size);
        }        
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Float_Copy(inputs[i], m_input_matrix_float+i*Ambisonics::m_vector_size, Ambisonics::m_vector_size);
        }
        Cicm_Matrix_Matrix_Float_Product(m_decoder_matrix_float, m_input_matrix_float, m_output_matrix_float, m_number_of_loudspeakers, Ambisonics::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            Cicm_Vector_Float_Copy(m_output_matrix_float+i*Ambisonics::m_vector_size, outputs[i], Ambisonics::m_vector_size);
        }
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVectors)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Double_Copy(ioVectors[i], m_input_matrix_double+i*Ambisonics::m_vector_size, Ambisonics::m_vector_size);
        }
        Cicm_Matrix_Matrix_Double_Product(m_decoder_matrix_double, m_input_matrix_double, m_output_matrix_double, m_number_of_loudspeakers, Ambisonics::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            Cicm_Vector_Double_Copy(m_output_matrix_double+i*Ambisonics::m_vector_size, ioVectors[i], Ambisonics::m_vector_size);
        }
    }
    
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Float_Copy(ioVectors[i], m_input_matrix_float+i*Ambisonics::m_vector_size, Ambisonics::m_vector_size);
        }
        Cicm_Matrix_Matrix_Float_Product(m_decoder_matrix_float, m_input_matrix_float, m_output_matrix_float, m_number_of_loudspeakers, Ambisonics::m_vector_size, m_number_of_harmonics);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            Cicm_Vector_Float_Copy(m_output_matrix_float+i*Ambisonics::m_vector_size, ioVectors[i], Ambisonics::m_vector_size);
        }
	}
};



#endif


