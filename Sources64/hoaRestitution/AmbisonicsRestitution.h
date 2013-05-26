/*
 *
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

#ifndef DEF_AMBISONICSSTEREO
#define DEF_AMBISONICSSTEREO

#include "../HoaAmbisonics/Ambisonics.h"
#include "../hoaDecoder/AmbisonicsDecoder.h"
#include "../hoaEncoder/AmbisonicsEncoder.h"

enum
{
    Hoa_Amplitude_Panning  = 0,
    Hoa_Microphone_Simulation
};

class AmbisonicsRestitution : public Ambisonics
{
	
private:
    long                m_restitution_mode;
    long                m_number_of_virtual_loudspeakers;
    long                m_number_of_real_loudspeakers;
    
    long                m_low_frequency_effect;
    double              m_configuation;
    double*             m_angles_of_loudspeakers;
    
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
	AmbisonicsRestitution(long anOrder = 1, double aConfiguration = 2, long aResitutionMode = Hoa_Amplitude_Panning,  long aVectorSize = 0);
    
    void    setRestitutionMode(long aResitutionMode);
    void    setConfiguration(double aConfiguration, bool standardOnOff = 1);
    void    setLoudspeakerAngle(long anIndex, double anAngle);
    void    setLoudspeakerAngles(long len, double* angles);
    
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
            Cicm_Vector_Double_Dot_Product(m_loudspeakers_vector_double, m_loudspeakers_gains_vector_double[i], &aOutputs[i], m_number_of_virtual_loudspeakers);
        }
        if(m_low_frequency_effect)
        {
            vDSP_sveD(m_loudspeakers_vector_double, 1, &aOutputs[m_number_of_real_loudspeakers], m_number_of_virtual_loudspeakers);            
        }
	}
    
    void process(float* aInputs, float* aOutputs)
	{
        m_decoder->process(aInputs, m_loudspeakers_vector_float);
        for(int i = 0; i < m_number_of_real_loudspeakers; i++)
        {
            Cicm_Vector_Float_Dot_Product(m_loudspeakers_vector_float, m_loudspeakers_gains_vector_float[i], &aOutputs[i], m_number_of_virtual_loudspeakers);
        }
        if(m_low_frequency_effect)
        {
            vDSP_sve(m_loudspeakers_vector_float, 1, &aOutputs[m_number_of_real_loudspeakers], m_number_of_virtual_loudspeakers);
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
                Cicm_Vector_Double_Dot_Product(m_loudspeakers_vector_double, m_loudspeakers_gains_vector_double[j], &aOutputs[j][i], m_number_of_virtual_loudspeakers);
            }
            if(m_low_frequency_effect)
            {
                vDSP_sveD(m_loudspeakers_vector_double, 1, &aOutputs[m_number_of_real_loudspeakers][i],m_number_of_virtual_loudspeakers);
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
                Cicm_Vector_Float_Dot_Product(m_loudspeakers_vector_float, m_loudspeakers_gains_vector_float[j], &aOutputs[j][i], m_number_of_virtual_loudspeakers);
            }
            if(m_low_frequency_effect)
            {
                vDSP_sve(m_loudspeakers_vector_float, 1, &aOutputs[m_number_of_real_loudspeakers][i], m_number_of_virtual_loudspeakers);
            }
        }
	}
};

#endif


