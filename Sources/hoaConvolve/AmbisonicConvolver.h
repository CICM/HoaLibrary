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

#ifndef DEF_AMBISONICCONVOLUTION
#define DEF_AMBISONICCONVOLUTION

#include "../hoaAmbisonics/Ambisonic.h"
#include "../CicmLibrary/CicmLines/CicmLine.h"
#include "../CicmLibrary/CicmFilters/CicmFilterConvolutionZero.h"

class AmbisonicConvolver : public Ambisonic
{
	
private:
    
	double		m_wet;
	double		m_dry;
    double*		m_wet_vector;
	double*		m_dry_vector;
    CicmLine*   m_wet_line;
    CicmLine*   m_dry_line;
    
    float*      m_impulse_response;
    long        m_impulse_response_size;
    
	vector <FilterConvolutionZero*> m_convolution;
    
    void        computeAmbisonicsImpulseResponses();
public:
	AmbisonicConvolver(long anOrder = 4, long aSamplingFrequency = 44100, long aVectorSize = 0);

	void	setVectorSize(long aVectorSize);

    void	setWetValue(double aGain);
	double	getWetValue();
    void	setDryValue(double aGain);
	double	getDryValue();
    void    clear();
    
    long getNumberOfFFTs(){return m_convolution[0]->getNumberOfFFTs();};
    long getNumberOfInstance(){return m_convolution[0]->getNumberOfInstance();};
    
	void	setImpulseResponse(float* anImpulResponse, long aSize);
	~AmbisonicConvolver();

	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* inputs, double* outputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
        {
			outputs[j] = m_convolution[j]->process(inputs[j]) * m_wet_line->process() + m_dry_line->process() * inputs[j];
        }
	}
    
	inline void process(const float* inputs, float* outputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
        {
			outputs[j] = m_convolution[j]->process(inputs[j]) * m_wet_line->process() + m_dry_line->process() * inputs[j];
        }
	}
	
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
    {
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
			ioVector[j] = m_convolution[j]->process(ioVector[j]) * m_wet_line->process() + m_dry_line->process() * ioVector[j];
        }
    }
    
    inline void process(float* ioVector)
    {
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
			ioVector[j] = m_convolution[j]->process(ioVector[j]) * m_wet_line->process() + m_dry_line->process() * ioVector[j];
        }
    }
    
	/************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* const* inputs, double** outputs)
	{
        const double* input;
        double* output;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            input = inputs[i];
            output = outputs[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				output[j] = m_convolution[i]->process(input[j]) * m_wet_vector[j] + m_dry_vector[j] * input[j];
            }
		}
	}
    
	inline void process(const float* const* inputs, float** outputs)
	{
        const float* input;
        float* output;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            input = inputs[i];
            output = outputs[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				output[j] = m_convolution[i]->process(input[j]) * m_wet_vector[j] + m_dry_vector[j] * input[j];
            }
		}
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double** ioVector)
    {
        double* vec;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            vec = ioVector[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				vec[j] = m_convolution[i]->process(vec[j]) * m_wet_vector[j] + m_dry_vector[j] * vec[j];
            }
		}
    }
    
    inline void process(float** ioVector)
    {
        float* vec;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            vec = ioVector[i];
			for(int j = 0; j < m_vector_size; j++)
            {
				vec[j] = m_convolution[i]->process(vec[j]) * m_wet_vector[j] + m_dry_vector[j] * vec[j];
            }
		}
    }
	
};



#endif


