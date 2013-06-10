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

#ifndef DEF_AMBISONICSFREEVERB
#define DEF_AMBISONICSFREEVERB

#include "../HoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmReverb/CicmFreeverb.h"

class AmbisonicsFreeverb : public Ambisonics
{
private:
    
	double	m_gain;
    double  m_wet;
    double  m_dry;
	double	roomsize;
	double	damp;
	double	mode;
    double  m_diffuse;
    vector <Freeverb*> m_freeverb;
    double  m_diffuse_spread;
    double  m_directional_spread;
    
	void	update();

public:
	AmbisonicsFreeverb(long anOrder = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
    
    void	setVectorSize(long aVectorSize);
    void	setSamplingRate(long aSamplingRate);
    
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
    void	setSpread(double value);
    void	setDiffuseSpread(double value);
    void	setDirectionalSpread(double value);
	double	getDiffuseSpread();
    double  getDirectionalSpread();

	inline void	process(float **anInput, float **anOutput)
    {
        float* input;
        float* output;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            input = anInput[i];
            output = anOutput[i];
            m_freeverb[i]->process(input, output);
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
            m_freeverb[i]->process(input, output);
        }
    }
    
	~AmbisonicsFreeverb();
};


#endif
