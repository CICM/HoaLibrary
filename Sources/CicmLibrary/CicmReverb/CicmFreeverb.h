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

#ifndef DEF_FREEVERB
#define DEF_FREEVERB


#include "CicmTuning.h"
#include "../CicmFilters/CicmFilterAllpass.h"
#include "../CicmFilters/CicmFilterComb.h"

class Freeverb
{
private:
    long    m_sampling_rate;
    long    m_vector_size;
    
	double	m_gain;
    double  m_wet;
    double  m_dry;
	double	roomsize, roomsize1;
	double	damp, damp1;
	double	mode;
    
    double  m_diffuse_spread;
    double  m_directional_spread;
    vector <FilterComb*>    m_comb_filter;
    vector <FilterAllpass*> m_allpass_filter;

	void	update();

public:
	Freeverb();

    void	setSamplingRate(long aSamplingRate);
	long	getSamplingRate();
    void	setVectorSize(long aVectorSize);
    long	getVectorSize();
    
    void	setDryValue(double value);
	double	getDryValue();
    void	setWetValue(double value);
	double	getWetValue();
	void	setroomsize(double value);
	double	getroomsize();
	void	setdamp(double value);
	double	getdamp();
	void	setmode(double value);
	double	getmode();
    void	setAllpassFeedback(double value);
	double	getAllpassFeedback();
    void	setSpread(double value);
    void	setDiffuseSpread(double value);
    void	setDirectionalSpread(double value);
	double	getDiffuseSpread();
    double  getDirectionalSpread();

    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline float process(const float input)
    {
        float input_val;
        float output = 0.f;
        input_val = input;
        input_val *= m_gain;

        for(int j = 0; j < numcombs; j++)
            output += m_comb_filter[j]->process(input_val);
        
        for(int j = 0; j < numallpasses; j++)
            output = m_allpass_filter[j]->process(output);
        output *= m_wet;
        output += input * m_dry;
        return output;
    };
    
    inline double process(const double input)
    {
        double input_val;
        double output = 0.;
        input_val = input;
        input_val *= m_gain;

        for(int j = 0; j < numcombs; j++)
            output += m_comb_filter[j]->process(input_val);
        
        for(int j = 0; j < numallpasses; j++)
            output = m_allpass_filter[j]->process(output);
        output *= m_wet;
        output += input * m_dry;
        return output;
    };
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void	process(const float* input, float* output)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            output[i] = process(input[i]);
        }
    };
    
    inline void	process(const double* input, double* output)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            output[i] = process(input[i]);
        }
    };
    
    /************************************* In Place *************************************/
    
    inline void	process(float* ioVectors)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            ioVectors[i] = process(ioVectors[i]);
        }
    };
    
    inline void	process(double* ioVectors)
    {
        for(int i = 0; i < m_vector_size; i++)
        {
            ioVectors[i] = process(ioVectors[i]);
        }
    };
    
	~Freeverb();
};


#endif
