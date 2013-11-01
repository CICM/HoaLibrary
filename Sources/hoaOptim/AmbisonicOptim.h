/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_AMBISONICOPTIMISAZION
#define DEF_AMBISONICOPTIMISAZION

enum
{
    Hoa_Basic_Optim  = 0,
    Hoa_MaxRe_Optim,
    Hoa_InPhase_Optim
};


#include "../HoaAmbisonics/Ambisonic.h"

class AmbisonicOptim : public Ambisonic
{
	
private:
	long m_optimMode;
	
    cicm_vector_float	m_optim_vector_float;
	cicm_vector_double	m_optim_vector_double;
    
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
        cicm_product_vec_vec_f(inputs, m_optim_vector_float, outputs, m_number_of_harmonics);
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		cicm_product_vec_vec_d(inputs, m_optim_vector_double, outputs, m_number_of_harmonics);
	}
    
    inline void process(double* ioVector)
	{
		cicm_product_vec_vec_d(ioVector, m_optim_vector_double, ioVector, m_number_of_harmonics);
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
            cicm_product_vec_sca_vec_f(input_pointor, m_optim_vector_float[i], output_pointor, m_vector_size);
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
			cicm_product_vec_sca_vec_d(input_pointor, m_optim_vector_double[i], output_pointor, m_vector_size);
		}
	}
    
    inline void process(float** ioVector)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            cicm_product_vec_sca_f(ioVector[i], m_optim_vector_float[i], m_vector_size);
		}
	}

};



#endif


