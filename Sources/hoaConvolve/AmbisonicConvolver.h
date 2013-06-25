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

#ifndef DEF_AMBISONICCONVOLUTION
#define DEF_AMBISONICCONVOLUTION

#include "../hoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmLine.h"
#include "../CicmLibrary/CicmFilters/CicmFilterConvolutionZero.h"

class AmbisonicConvolver : public Ambisonics
{
	
private:
    
	double		m_wet;
	double		m_dry;
    double*		m_wet_vector;
	double*		m_dry_vector;
    CicmLine* m_wet_line;
    CicmLine* m_dry_line;
    
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

	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
		for(int j = 0; j < m_number_of_harmonics; j++)
			aOutputs[j] = m_convolution[j]->process(aInputs[j]) * m_wet_line->process() + m_dry_line->process() * aInputs[j];
	}
	
	/* Perform sample block */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
        Type *InputVector, *OutputVector;
        m_wet_line->process(m_wet_vector);
        m_dry_line->process(m_dry_vector);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
            InputVector = aInputs[i];
            OutputVector = aOutputs[i];
			for(int j = 0; j < m_vector_size; j++)
				OutputVector[j] = m_convolution[i]->process(InputVector[j]) * m_wet_vector[j] + m_dry_vector[j] * InputVector[j];
		}
	}
	
};



#endif


