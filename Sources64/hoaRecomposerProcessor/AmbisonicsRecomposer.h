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
	AmbisonicsRecomposer(long anOrder = 1, long aNumberOfMicrophones = 4, long aVectorSize = 0, long fixedOrNot = 0);
    
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


