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

#ifndef DEF_AMBISONICSDIFFUSER
#define DEF_AMBISONICSDIFFUSER

#include "Ambisonic.h"

enum
{
    Hoa_No_Encoding = 0,
    Hoa_Post_Encoding = 1,
};

class AmbisonicsDiffuser : public Ambisonic
{
protected:
    double  m_diffuse_factor;
    bool    m_mode;
    bool    m_encoding_compensation;

public:
	AmbisonicsDiffuser(long anOrder = 1, bool aMode = Hoa_Post_Encoding, long aVectorSize = 0, long aSamplingRate = 44100.);
    
    void    setDiffuseFactor(double aDiffuseValue);
    void    setEncodingCompensation(bool OnOff);
    
    bool    getMode();
    double  getDiffuseFactor();
    bool    getEncodingCompensation();
    
	~AmbisonicsDiffuser();
	
	/* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{	
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = inputs[i];
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			outputs[i] = inputs[i];
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
			for(int j = 0; j < m_vector_size; j++)
            {
				output_pointor[j] = input_pointor[j];
			}
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
			for(int j = 0; j < m_vector_size; j++)
            {
				output_pointor[j] = input_pointor[j];
			}
		}
	}
};



#endif


