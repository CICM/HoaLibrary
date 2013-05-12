/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#ifndef DEF_PLANEWAVES
#define DEF_PLANEWAVES

#include "../CicmLibrary/CicmDefine.h"
#include "../CicmLibrary/CicmTools.h"
#include "../CicmLibrary/CicmLine.h"

class Planewaves
{
protected:
	long	m_number_of_outputs;
	long	m_number_of_inputs;
    double  m_configuration;
    long    m_low_frequency_effect;
	long	m_vector_size;
    long	m_sampling_rate;
    double* m_angles_of_loudspeakers;

    void computeConfiguration(bool standardOnOff = 1);
public:
	Planewaves(double aConfiguration = 1., long aVectorSize = 0, double aSamplingRate = 44100.);
	
	long            getNumberOfInputs();
	long            getNumberOfOutputs();
    double          getConfiguration();
    double          getLoudspeakerAngle(long anIndex);
    std::string     getLoudspeakerName(long anIndex);
	long            getVectorSize();
	long            getSamplingRate();

    void setConfiguration(double aConfiguration, bool standardOnOff = 1);
    void setLoudspeakerAngle(long anIndex, double anAngle);
	void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);

	~Planewaves();
	
	/* Perform sample by sample */
	inline void process(float* inputs, float* outputs)
	{	
		;
	}
    
    /* Perform sample by sample */
	inline void process(double* inputs, double* outputs)
	{
		;
	}
	
	/* Perform block sample */
	inline void process(float** inputs, float** outputs)
	{
        ;
	}
    
    /* Perform block sample */
	inline void process(double** inputs, double** outputs)
	{
        ;
	}
};



#endif


