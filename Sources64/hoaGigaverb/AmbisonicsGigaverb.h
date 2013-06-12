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

#ifndef DEF_AMBISONICSGIGAVERB
#define DEF_AMBISONICSGIGAVERB

#include "../HoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmReverb/CicmGigaverb.h"

class AmbisonicsGigaverb : public Ambisonics
{
private:
    
    double  m_wet;
    double  m_dry;
    vector <Gigaverb*> m_gigaverb;

	void	update();
public:
	AmbisonicsGigaverb(long anOrder = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
    
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
    
	~AmbisonicsGigaverb();
};


#endif
