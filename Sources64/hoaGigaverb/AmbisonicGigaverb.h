/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

#ifndef DEF_AMBISONICGIGAVERB
#define DEF_AMBISONICGIGAVERB

#include "cicmTools.h"
#include "revGigaverb.h"
#include "AmbisonicRecomposer.h"

class AmbisonicGigaverb
{
private:
    
    long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	long		m_sampling_rate;
	long		m_vector_size;
    
    long*   m_index_of_harmonics;
    double  m_wet;
    double  m_dry;
    vector <Gigaverb*> m_gigaverb;

	void	update();
    void    computeIndex();
public:
	AmbisonicGigaverb(long anOrder);
    
    long	getOrder();
	long	getNumberOfHarmonics();
	long	getNumberOfInputs();
	long	getNumberOfOutputs();
	long	getVectorSize();
    long	getSamplingRate();
    
    void	setVectorSize(long aVectorSize);
    void	setSamplingRate(long aSamplingRate);
    
    void	setDryValue(double value);
	double	getDryValue();
    void	setWetValue(double value);
	double	getWetValue();
 	void setRoomSize(double aRoomSize);
	double getRoomSize();
	void setReverberationTime(double aValue);
	double getReverberationTime();
	void setDamping(double aValue);
	double getDamping();
	void setInputBandwidth(double aValue);
	double getInputBandwidth();
	void setEarlyLevel(double aValue);
	double getEarlyLevel();
	void setTailLevel(double aValue);
	double getTailLevel();


	inline void	process(float **anInput, float **anOutput)
    {
        float* input;
        float* output;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input = anInput[i];
            output = anOutput[i];
            for(int j = 0; j < m_vector_size; j++)
                output[j] = m_gigaverb[i]->perform(input[j]) * m_wet + input[j] * m_dry;
        }
    };
    
    inline void	process(double **anInput, double **anOutput)
    {
        double* input;
        double* output;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input = anInput[i];
            output = anOutput[i];
            for(int j = 0; j < m_vector_size; j++)
                output[j] = m_gigaverb[i]->perform(input[j]) * m_wet + input[j] * m_dry;
        }
    }
    
	~AmbisonicGigaverb();
};


#endif
