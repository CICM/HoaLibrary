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

#ifndef DEF_AMBISONICSDECODER
#define DEF_AMBISONICSDECODER

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsDecoder : public Ambisonics
{
	
private:
    long                 m_number_of_loudspeakers;
    double               m_offset;
	Cicm_Matrix_Float    m_decoder_matrix_float;
    Cicm_Matrix_Double   m_decoder_matrix_double;
    Cicm_Vector_Float    m_vector_float_input;
    Cicm_Vector_Float    m_vector_float_output;
    Cicm_Vector_Double   m_vector_double_input;
    Cicm_Vector_Double   m_vector_double_output;
    
	void computeMatrix();

public:
	AmbisonicsDecoder(long anOrder = 1, long aNumberOfLoudspeakers = 0, double anOffset = 0., long aVectorSize = 0);
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    long getNumberOfLoudspeakers();
    
    void setOffset(double anOffset);
    double getOffset();
    double getLoudspeakerAngle(long anIndex);
    std::string  getLoudspeakerName(long anIndex);
    
	~AmbisonicsDecoder();
	
	/* Perform sample by sample */    
	inline void process(double* aHarmonicsInputVector, double* aLoudspeakersOutputVector)
	{
        Cicm_Matrix_Vector_Double_Product(m_decoder_matrix_double, aHarmonicsInputVector, aLoudspeakersOutputVector, m_number_of_outputs, m_number_of_harmonics);
    }
    
    inline void process(float* anHarmonicsInputVector, float* aLoudspeakersOutputVector)
	{
        Cicm_Matrix_Vector_Float_Product(m_decoder_matrix_float, anHarmonicsInputVector, aLoudspeakersOutputVector,  m_number_of_outputs, m_number_of_harmonics);
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


