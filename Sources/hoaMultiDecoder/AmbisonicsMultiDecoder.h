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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICSMULTIDECODER
#define DEF_AMBISONICSMULTIDECODER

#include "../hoaBinaural/AmbisonicsBinaural.h"
#include "../hoaRestitution/AmbisonicsRestitution.h"

enum
{
    Hoa_Ambisonics = 0,
    Hoa_Binaural,
    Hoa_Restitution
};

class AmbisonicsMultiDecoder : public Ambisonic
{
	
private:
    long                    m_mode;
    
    AmbisonicsBinaural*     m_binaural;
    AmbisonicsDecoder*      m_decoder;
    AmbisonicsRestitution*  m_restitution;

public:
	AmbisonicsMultiDecoder(long anOrder = 1, long aNumberOfLoudspeakers = 4, long aMode = Hoa_Ambisonics, long aPinnaSize = Hoa_Small, std::string aRootPath = "", long aVectorSize = 0, long aSamplingRate = 44100);
    
    void    setMode(long aMode);
    long    getMode();
    
    void    setNumberOfLoudspeakers(long aConfiguration);
    long    getNumberOfLoudspeakers();
    
    void    setPinnaeSize(long aPinnaSize);
    long    getPinnaeSize();
	long    getGetHrtfLoaded(){return m_binaural->getGetHrtfLoaded();};
	long    getHrtfSize(){return m_binaural->getHrtfSize();};
    
    void    setRestitutionMode(long aResitutionMode);
    long    getRestitutionMode();
    
    void    setLoudspeakerAngle(long anIndex, double anAngle);
    double  getLoudspeakerAngle(long anIndex);
    
    std::string  getLoudspeakerName(long anIndex);
    
    void    setVectorSize(long aVectorSize);
    void    setSamplingRate(long aSamplingRate);
	~AmbisonicsMultiDecoder();
	
	/* Perform block sample */
	inline void process(double** aInputs, double** aOutputs)
	{
        if(m_mode == Hoa_Ambisonics)
            m_decoder->process(aInputs, aOutputs);
        else if(m_mode == Hoa_Binaural)
            m_binaural->process(aInputs, aOutputs);
        else
			m_restitution->process(aInputs, aOutputs);
	}
    
    inline void process(float** aInputs, float** aOutputs)
	{
        if(m_mode == Hoa_Ambisonics)
            m_decoder->process(aInputs, aOutputs);
        else if(m_mode == Hoa_Binaural)
            m_binaural->process(aInputs, aOutputs);
        else
           m_restitution->process(aInputs, aOutputs);
	}
};



#endif


