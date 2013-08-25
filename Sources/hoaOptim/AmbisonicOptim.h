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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICOPTIMISAZION
#define DEF_AMBISONICOPTIMISAZION

enum
{
    Hoa_Basic_Optim  = 0,
    Hoa_MaxRe_Optim,
    Hoa_InPhase_Optim
};


#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicOptim : public Ambisonics
{
	
private:
	long m_optimMode;
	
    Cicm_Vector_Float	m_optim_vector_float;
	Cicm_Vector_Double	m_optim_vector_double;
    
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();
	
public:
	AmbisonicOptim(long anOrder = 1, long anOptimMode = Hoa_InPhase_Optim, long aVectorSize = 0);
    
    double getCoefficient(long anIndex);
	long getOptimMode();
	void setOptimMode(long anOptim);
    
	~AmbisonicOptim();
	
    /* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{
        Cicm_Vector_Vector_Float_Mul(inputs, m_optim_vector_float, outputs, m_number_of_harmonics);
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		Cicm_Vector_Vector_Double_Mul(inputs, m_optim_vector_double, outputs, m_number_of_harmonics);
	}
    
    inline void process(double* ioVector)
	{
		Cicm_Vector_Vector_Double_Mul(ioVector, m_optim_vector_double, ioVector, m_number_of_harmonics);
	}
	
	/* Perform block sample */
	inline void process(float** inputs, float** outputs)
	{
        float* input_pointor;
        float* output_pointor;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input_pointor = inputs[i];
            output_pointor = outputs[i];
            Cicm_Vector_Scalar_Float_Mul(input_pointor, m_optim_vector_float[i], output_pointor, m_vector_size);
		}
	}
    
    /* Perform block sample */
	inline void process(double** inputs, double** outputs)
	{
        double* input_pointor;
        double* output_pointor;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input_pointor = inputs[i];
            output_pointor = outputs[i];
			Cicm_Vector_Scalar_Double_Mul(input_pointor, m_optim_vector_double[i], output_pointor, m_vector_size);
		}
	}
};



#endif


