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

#ifndef DEF_AMBISONICSRESTITUTION
#define DEF_AMBISONICSRESTITUTION

#include "../hoaDecoder/AmbisonicsDecoder.h"

enum
{
    Hoa_Amplitude_Panning  = 0,
    Hoa_Microphone_Simulation
};

class AmbisonicsRestitution : public Ambisonic
{
	
private:
    long                m_restitution_mode;
    long                m_number_of_virtual_loudspeakers;
    long                m_number_of_real_loudspeakers;
    
    Cicm_Vector_Double  m_angles_of_loudspeakers;
    
	AmbisonicsDecoder*  m_decoder;
    
    Cicm_Vector_Float   m_vector_float_input;
    Cicm_Vector_Double  m_vector_double_input;
    Cicm_Vector_Float   m_loudspeakers_vector_float;
    Cicm_Vector_Double  m_loudspeakers_vector_double;
    
    Cicm_Vector_Float*  m_loudspeakers_gains_vector_float;
    Cicm_Vector_Double* m_loudspeakers_gains_vector_double;
    
    void computeAmplitudePanning();
    void computeMicrophoneSimulation();
public:
	AmbisonicsRestitution(long anOrder = 1, long aNumberOfLoudspeakers = 5, long aResitutionMode = Hoa_Amplitude_Panning,  long aVectorSize = 0);
    
    void    setRestitutionMode(long aResitutionMode);
    void    setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 1);
    void    setLoudspeakerAngle(long anIndex, double anAngle);
    
    long    getRestitutionMode();
    double  getConfiguration();
    double  getLoudspeakerAngle(long anIndex);
    
    std::string  getLoudspeakerName(long anIndex);
    
	~AmbisonicsRestitution();
	
	/* Perform sample by sample*/
	void process(double* aInputs, double* aOutputs)
	{
        m_decoder->process(aInputs, m_loudspeakers_vector_double);
        for(int i = 0; i < m_number_of_real_loudspeakers; i++)
        {
            cicm_dot_product_d(m_loudspeakers_vector_double, m_loudspeakers_gains_vector_double[i], aOutputs[i], m_number_of_virtual_loudspeakers);
        }
	}
    
    void process(float* aInputs, float* aOutputs)
	{
        m_decoder->process(aInputs, m_loudspeakers_vector_float);
        for(int i = 0; i < m_number_of_real_loudspeakers; i++)
        {
            cicm_dot_product_f(m_loudspeakers_vector_float, m_loudspeakers_gains_vector_float[i], aOutputs[i], m_number_of_virtual_loudspeakers);
        }
	}
	
	/* Perform block samples */
	void process(double** aInputs, double** aOutputs)
	{
        for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_vector_double_input[j] = aInputs[j][i];
            }
            m_decoder->process(m_vector_double_input, m_loudspeakers_vector_double);
            for(int j = 0; j < m_number_of_real_loudspeakers; j++)
            {
                cicm_dot_product_d(m_loudspeakers_vector_double, m_loudspeakers_gains_vector_double[j], aOutputs[j][i], m_number_of_virtual_loudspeakers);
            }
        }
	}
    
	void process(float** aInputs, float** aOutputs)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                m_vector_float_input[j] = aInputs[j][i];
            }
            m_decoder->process(m_vector_float_input, m_loudspeakers_vector_float);
            for(int j = 0; j < m_number_of_real_loudspeakers; j++)
            {
                cicm_dot_product_f(m_loudspeakers_vector_float, m_loudspeakers_gains_vector_float[j], aOutputs[j][i], m_number_of_virtual_loudspeakers);
            }
        }
	}
};

#endif

