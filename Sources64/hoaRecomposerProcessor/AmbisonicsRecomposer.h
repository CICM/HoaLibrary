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

#ifndef DEF_AMBISONICSRECOMPOSER
#define DEF_AMBISONICSRECOMPOSER

#include "../HoaAmbisonics/Ambisonics.h"
#include "../hoaEncoder/AmbisonicsEncoder.h"
#include "../HoaWider/AmbisonicsWider.h"

class AmbisonicsRecomposer : public Ambisonics
{
	
private:
    long                        m_number_of_microphones;
	Cicm_Vector_Float           m_harmonics_vector_float;
    Cicm_Vector_Double          m_harmonics_vector_double;
    
    Cicm_Vector_Float           m_angles_vector_float;
    Cicm_Vector_Double          m_angles_vector_double;
    
    Cicm_Vector_Float*          m_harmonics_matrix_float;
    Cicm_Vector_Double*         m_harmonics_matrix_double;
    
	vector<AmbisonicsEncoder*>  m_encoders;
    vector<CicmLine*>           m_lines;
    vector<AmbisonicsWider*>    m_widers;
    vector<CicmLine*>           m_wider_lines;
    
    long                        m_mode;
    double                      m_fishEyeFactor;
    
public:
	AmbisonicsRecomposer(long anOrder = 1, long aNumberOfMicrophones = 4, long aVectorSize = 0, long aMode = 0);
    
    void setVectorSize(long aVectorSize);
    void setRamp(long aNumberOfSample);
    void setMode(long aMode);
    void setFishEyeFactor(double aFishEyeFactor);
	void setMicrophoneAngle(long anIndex, double anAngle);
    void setMicrophoneWide(long anIndex, double aWidenValue);
    
    
    double getMicrophoneAngle(long anIndex);
    double getMicrophoneWide(long anIndex);
    inline double getFishEyeFactor() {return m_fishEyeFactor;}
    inline long getMode() {return m_mode;}

	~AmbisonicsRecomposer();
	
	/* Perform sample by sample */
	inline void process(double* aInputs, double* aOutputs)
	{
        if(m_mode == 0) // fixe
        {
            processFixe(aInputs, aOutputs);
            return;
        }
        double angle    = m_lines[0]->process();
        double wide     = m_wider_lines[0]->process();
        m_encoders[0]->process(aInputs[0], aOutputs, angle);
        m_widers[0]->process(aOutputs, aOutputs, wide);
		for(int i = 1; i < m_number_of_microphones; i++)
        {
            angle = m_lines[i]->process();
            wide  = m_wider_lines[i]->process();
            m_encoders[i]->process(aInputs[i], m_harmonics_vector_double, angle);
            m_widers[i]->process(m_harmonics_vector_double, m_harmonics_vector_double, wide);
            Cicm_Vector_Double_Add(m_harmonics_vector_double, aOutputs, m_number_of_harmonics);
        }
	}
    
    inline void process(float* aInputs, float* aOutputs)
	{
        if(m_mode == 0)
        {
            processFixe(aInputs, aOutputs);
            return;
        }
        float angle = m_lines[0]->process();
        float wide  = m_wider_lines[0]->process();
        m_encoders[0]->process(aInputs[0], aOutputs, angle);
        m_widers[0]->process(aOutputs, aOutputs, wide);
		for(int i = 1; i < m_number_of_microphones; i++)
        {
            angle = m_lines[i]->process();
            wide  = m_wider_lines[i]->process();
            m_encoders[i]->process(aInputs[i], m_harmonics_vector_float, angle);
            m_widers[i]->process(m_harmonics_vector_float, m_harmonics_vector_float, wide);
            Cicm_Vector_Float_Add(m_harmonics_vector_float, aOutputs, m_number_of_harmonics);
        }
	}
	
	/* Perform sample block */
	inline void process(double** aInputs, double** aOutputs)
	{
        if(m_mode == 0)
        {
            processFixe(aInputs, aOutputs);
            return;
        }
        m_lines[0]->process(m_angles_vector_double);
        m_encoders[0]->process(aInputs[0], aOutputs, m_angles_vector_double);
        m_wider_lines[0]->process(m_angles_vector_double);
        m_widers[0]->process(aOutputs, aOutputs, m_angles_vector_double);
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_lines[i]->process(m_angles_vector_double);
            m_encoders[i]->process(aInputs[i], m_harmonics_matrix_double, m_angles_vector_double);
            m_wider_lines[i]->process(m_angles_vector_double);
            m_widers[i]->process(m_harmonics_matrix_double, m_harmonics_matrix_double, m_angles_vector_double);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Double_Add(m_harmonics_matrix_double[k], aOutputs[k], m_vector_size);
            }
        }
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
        if(m_mode == 0)
        {
            processFixe(aInputs, aOutputs);
            return;
        }
        m_lines[0]->process(m_angles_vector_float);
        m_encoders[0]->process(aInputs[0], aOutputs, m_angles_vector_float);
        m_wider_lines[0]->process(m_angles_vector_float);
        m_widers[0]->process(aOutputs, aOutputs, m_angles_vector_float);
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_lines[i]->process(m_angles_vector_float);
            m_encoders[i]->process(aInputs[i], m_harmonics_matrix_float, m_angles_vector_float);
            m_wider_lines[i]->process(m_angles_vector_double);
            m_widers[i]->process(m_harmonics_matrix_float, m_harmonics_matrix_float, m_angles_vector_float);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Float_Add(m_harmonics_matrix_float[k], aOutputs[k], m_vector_size);
            }
        }
	}
    
    /* Perform sample block - with wide fixed and angle set by fisheye factor*/
	inline void process(double** aInputs, double** aOutputs, double* fisheyeFactor)
	{
        double clip[2] = {0.,1.};
        Cicm_Vector_Double_Clip(fisheyeFactor, &clip[0], &clip[1], fisheyeFactor, m_vector_size);
        double distanceBetwenTwoDefMics = CICM_2PI / m_number_of_microphones;

        for (int v=0; v<m_vector_size; v++)
        {
            m_angles_vector_double[v] = 0.;
        }
        m_encoders[0]->process(aInputs[0], aOutputs, m_angles_vector_double);
        m_wider_lines[0]->process(m_angles_vector_double);
        m_widers[0]->process(aOutputs, aOutputs, m_angles_vector_double);
        
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            for (int v=0; v<m_vector_size; v++)
            {
                m_angles_vector_double[v] = Tools::radianInterp(1-fisheyeFactor[v], distanceBetwenTwoDefMics*i, 0.);
            }
            m_encoders[i]->process(aInputs[i], m_harmonics_matrix_double, m_angles_vector_double);
            m_wider_lines[i]->process(m_angles_vector_double);
            m_widers[i]->process(m_harmonics_matrix_double, m_harmonics_matrix_double, m_angles_vector_double);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Double_Add(m_harmonics_matrix_double[k], aOutputs[k], m_vector_size);
            }
        }
	}
    
    inline void process(float** aInputs, float** aOutputs, float* fisheyeFactor)
	{
        float clip[2] = {0.,1.};
        Cicm_Vector_Float_Clip(fisheyeFactor, &clip[0], &clip[1], fisheyeFactor, m_vector_size);
        double distanceBetwenTwoDefMics = CICM_2PI / m_number_of_microphones;
        
        for (int v=0; v<m_vector_size; v++)
        {
            m_angles_vector_double[v] = 0.;
        }
        m_encoders[0]->process(aInputs[0], aOutputs, m_angles_vector_float);
        m_wider_lines[0]->process(m_angles_vector_double);
        m_widers[0]->process(m_harmonics_matrix_float, m_harmonics_matrix_float, m_angles_vector_float);
        
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            for (int v=0; v<m_vector_size; v++)
            {
                m_angles_vector_double[v] = Tools::radianInterp(1-fisheyeFactor[v], distanceBetwenTwoDefMics*i, 0.);
            }
            m_encoders[i]->process(aInputs[i], m_harmonics_matrix_float, m_angles_vector_float);
            m_wider_lines[i]->process(m_angles_vector_double);
            m_widers[i]->process(m_harmonics_matrix_float, m_harmonics_matrix_float, m_angles_vector_float);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Float_Add(m_harmonics_matrix_float[k], aOutputs[k], m_vector_size);
            }
        }
	}
    
    /* Perform sample by sample - angle and wide fixed */
    inline void processFixe(double* aInputs, double* aOutputs)
	{
        m_encoders[0]->process(aInputs[0], aOutputs);
        m_widers[0]->process(aOutputs, aOutputs);
		for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_encoders[i]->process(aInputs[i], m_harmonics_vector_double);
            m_widers[i]->process(m_harmonics_vector_double, m_harmonics_vector_double);
            Cicm_Vector_Double_Add(m_harmonics_vector_double, aOutputs, m_number_of_harmonics);
        }
	}
    
    inline void processFixe(float* aInputs, float* aOutputs)
	{
        m_encoders[0]->process(aInputs[0], aOutputs);
        m_widers[0]->process(aOutputs, aOutputs);
		for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_encoders[i]->process(aInputs[i], m_harmonics_vector_float);
            m_widers[i]->process(m_harmonics_vector_float, m_harmonics_vector_float);
            Cicm_Vector_Float_Add(m_harmonics_vector_float, aOutputs, m_number_of_harmonics);
        }
	}
    
    /* Perform sample block - angle and wide fixed */
	inline void processFixe(double** aInputs, double** aOutputs)
	{
        m_encoders[0]->process(aInputs[0], aOutputs);
        m_widers[0]->process(aOutputs, aOutputs);
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_encoders[i]->process(aInputs[i], m_harmonics_matrix_double);
            m_widers[0]->process(m_harmonics_matrix_double, m_harmonics_matrix_double);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Double_Add(m_harmonics_matrix_double[k], aOutputs[k], m_vector_size);
            }
        }
	}
    
    inline void processFixe(float** aInputs, float** aOutputs)
	{
        m_encoders[0]->process(aInputs[0], aOutputs);
        m_widers[0]->process(aOutputs, aOutputs);
        for(int i = 1; i < m_number_of_microphones; i++)
        {
            m_encoders[i]->processAdd(aInputs[i], m_harmonics_matrix_float);
            m_widers[0]->process(m_harmonics_matrix_float, m_harmonics_matrix_float);
            for(int k = 0; k < m_number_of_harmonics; k++)
            {
                Cicm_Vector_Float_Add(m_harmonics_matrix_float[k], aOutputs[k], m_vector_size);
            }

        }
	}
};



#endif


