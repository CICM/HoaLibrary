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

#ifndef DEF_AMBISONICSDECODER
#define DEF_AMBISONICSDECODER

#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicsDecoder : public Ambisonic
{
	
private:
    long                 m_number_of_loudspeakers;
	Cicm_Matrix_Float    m_decoder_matrix_float;
    Cicm_Matrix_Double   m_decoder_matrix_double;
    Cicm_Vector_Float    m_vector_float_input;
    Cicm_Vector_Float    m_vector_float_output;
    Cicm_Vector_Double   m_vector_double_input;
    Cicm_Vector_Double   m_vector_double_output;
    
	void computeMatrix();

public:
	AmbisonicsDecoder(long anOrder = 1, long aNumberOfLoudspeakers = 0, long aVectorSize = 0);
    
    void        setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    long        getNumberOfLoudspeakers();
    
    double       getLoudspeakerAngle(long anIndex);
    std::string  getLoudspeakerName(long anIndex);
    
	~AmbisonicsDecoder();
	
	/* Perform sample by sample */    
	inline void process(double* anInput, double* anOutput)
	{
        Cicm_Matrix_Vector_Double_Product(m_decoder_matrix_double, anInput, anOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    inline void process(float* anInput, float* anOutput)
	{
        Cicm_Matrix_Vector_Float_Product(m_decoder_matrix_float, anInput, anOutput,  m_number_of_outputs, m_number_of_harmonics);
	}
	
	/* Perform block sample */
	inline void process(double** aInputs, double** aOutputs)
	{
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_vector_float_input[j] = aInputs[j][i];
            }
            process(m_vector_float_input, m_vector_float_output);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                aOutputs[j][i] = m_vector_float_output[j];
            }
        }
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_vector_float_input[j] = aInputs[j][i];
            }
            process(m_vector_float_input, m_vector_float_output);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                aOutputs[j][i] = m_vector_float_output[j];
            }
		}
	}
};



#endif


