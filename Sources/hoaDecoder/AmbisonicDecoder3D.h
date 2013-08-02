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

#ifndef DEF_AMBISONICDECODER3D
#define DEF_AMBISONICDECODER3D

#include "../hoaEncoder/AmbisonicEncoder3D.h"
#include "../HoaAmbisonics/Ambisonic3D.h"

enum
{
    Hoa_Half_Sphere = 0,
    Hoa_Full_Sphere,
};

class AmbisonicDecoder3D : public Ambisonic3D
{
	
private:
    bool                m_shape;
    Cicm_Matrix_Double  m_decoder_matrix_double;
    Cicm_Matrix_Float   m_decoder_matrix_float;
    
    Cicm_Matrix_Double  m_harmonics_vector_double;
    Cicm_Vector_Float   m_harmonics_vector_float;
    
    Cicm_Matrix_Double  m_outputs_vector_double;
    Cicm_Vector_Float   m_outputs_vector_float;
    
    void computeMatrices();
public:
	AmbisonicDecoder3D(long anOrder = 1, long aNumberOfLoudspeakers = 4, bool aShape = Hoa_Full_Sphere, long aVectorSize = 2, long aSamlingRate = 44100);
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool aShape = Hoa_Full_Sphere);
    void setLoudspeakerPosition(long anIndex, double anAzimuth, double anElevation);
    
	~AmbisonicDecoder3D();
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/

    /*********************************** Out Of Place ***********************************/
    
    inline void process(const float* anInput, float* anOutput)
    {
       Cicm_Matrix_Vector_Float_Product(m_decoder_matrix_float, anInput, anOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    inline void process(const double* anInput, double* anOutput)
    {
        Cicm_Matrix_Vector_Double_Product(m_decoder_matrix_double, anInput, anOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    /************************************* In Place *************************************/

    
    inline void process(float* anInputOutput)
    {
        Cicm_Vector_Float_Copy(anInputOutput, m_harmonics_vector_float, m_number_of_harmonics);
        Cicm_Matrix_Vector_Float_Product(m_decoder_matrix_float, m_harmonics_vector_float, anInputOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    inline void process(double* anInputOutput)
    {
        Cicm_Vector_Double_Copy(anInputOutput, m_harmonics_vector_double, m_number_of_harmonics);
        Cicm_Matrix_Vector_Double_Product(m_decoder_matrix_double, m_harmonics_vector_double, anInputOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(float** anInput, float** anOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_harmonics_vector_float[j] = anInput[j][i];
            }
            process(m_harmonics_vector_float, m_outputs_vector_float);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                anOutput[j][i] = m_outputs_vector_float[j];
            }
		}
    }
    
    inline void process(double** anInput, double** anOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_harmonics_vector_double[j] = anInput[j][i];
            }
            process(m_harmonics_vector_double, m_outputs_vector_double);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                anOutput[j][i] = m_outputs_vector_double[j];
            }
		}
    }
    
    /************************************* In Place *************************************/
    
       
    inline void process(float** anInputOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_harmonics_vector_float[j] = anInputOutput[j][i];
            }
            process(m_harmonics_vector_float, m_outputs_vector_float);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                anInputOutput[j][i] = m_outputs_vector_float[j];
            }
		}
    }
    
    inline void process(double** anInputOutput)
    {
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_harmonics_vector_double[j] = anInputOutput[j][i];
            }
            process(m_harmonics_vector_double, m_outputs_vector_double);
            for(int j = 0; j < m_number_of_outputs; j++)
            {
                anInputOutput[j][i] = m_outputs_vector_double[j];
            }
		}
    }
};
#endif