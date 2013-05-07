/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef DEF_AMBISONICSMULTIDECODER
#define DEF_AMBISONICSMULTIDECODER

enum
{
    Hoa_Ambisonics = 0,
    Hoa_Binaural,
    Hoa_Restitution
};

#include "../HoaAmbisonics/Ambisonics.h"
#include "../hoaBinaural/AmbisonicsBinaural.h"
#include "../hoaDecoder/AmbisonicsDecoder.h"
#include "../hoaRestitution/AmbisonicsRestitution.h"

class AmbisonicsMultiDecoder : public Ambisonics
{
	
private:
    long                    m_mode;
    
    AmbisonicsBinaural*     m_binaural;
    AmbisonicsDecoder*      m_decoder;
    AmbisonicsRestitution*  m_restitution;

public:
	AmbisonicsMultiDecoder(long anOrder = 1, std::string aRootPath = "", long aPinnaSize = Hoa_Small, long aVectorSize = 0, long aSamplingRate = 44100, long aMode = Hoa_Ambisonics, long aNumberOfLoudspeakers = 4, double aConfiguration = 5.1, double anOffset = 0.);
    
    void    setMode(long aMode);
    long    getMode();
    
    void    setNumberOfLoudspeakers(long aConfiguration);
    long    getNumberOfLoudspeakers();
    void    setOffset(double anOffset);
    double  getOffset();
    
    void    setPinnaSize(long aPinnaSize);
    long    getPinnaSize();
    
    void    setRestitutionMode(long aResitutionMode);
    long    getRestitutionMode();
    void    setConfiguration(double aConfiguration, bool standardOnOff = 1);
    double  getConfiguration();
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


