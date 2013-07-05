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

#ifndef DEF_PLANEWAVES
#define DEF_PLANEWAVES

#include "../CicmLibrary/CicmDefine.h"
#include "../CicmLibrary/CicmTools.h"
#include "../CicmLibrary/CicmLines/CicmLine.h"

class Planewaves
{
protected:
	long	m_number_of_outputs;
	long	m_number_of_inputs;
    long    m_number_of_loudspeakers;
    
    double*     m_angles_of_loudspeakers;
    double*     m_abscissa_of_loudspeakers;
    double*     m_ordinate_of_loudspeakers;
    
	long	m_vector_size;
    long	m_sampling_rate;
    
    void computeConfiguration(bool standardOnOff = 0);
public:
	Planewaves(long aNumberOfLoudspeakers = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
	
	long            getNumberOfInputs();
	long            getNumberOfOutputs();
    long            getNumberOfLoudspeakers();
    double          getLoudspeakerAngle(long anIndex);
    std::string     getLoudspeakerName(long anIndex);
	long            getVectorSize();
	long            getSamplingRate();

    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 0);
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


