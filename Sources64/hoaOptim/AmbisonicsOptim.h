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

#ifndef DEF_AMBISONICSOPTIM
#define DEF_AMBISONICSOPTIM

#include "../HoaAmbisonics/Ambisonics.h"

class AmbisonicsOptim : public Ambisonics
{
	
private:
	std::string m_optimMode;
	
    Cicm_Signal_Vector_Float	m_optim_vector_float;
	Cicm_Signal_Vector_Double	m_optim_vector_double;
    
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();
	
public:
	AmbisonicsOptim(long anOrder = 1, std::string anOptimMode = "basic", long aVectorSize = 0);
	std::string getOptimMode();
	void setOptimMode(std::string anOptim);

	~AmbisonicsOptim();
	
    /* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{
        Cicm_Matrix_Vector_Float_Mul(inputs, m_optim_vector_float, outputs, m_number_of_harmonics);
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		Cicm_Matrix_Vector_Double_Mul(inputs, m_optim_vector_double, outputs, m_number_of_harmonics);
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
            Cicm_Matrix_Vector_Scalar_Float_Mul(input_pointor, m_optim_vector_float+i, output_pointor, m_vector_size);
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
			Cicm_Matrix_Vector_Scalar_Double_Mul(input_pointor, m_optim_vector_double+i, output_pointor, m_vector_size);
		}
	}
};



#endif


