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

#ifndef DEF_AMBISONICSMETER
#define DEF_AMBISONICSMETER

#include "../hoaVector/AmbisonicsVector.h"

class AmbisonicsMeter : public Planewaves
{
protected:
    Ambisonicsvector*   m_vectors;
    
    Cicm_Vector_Double m_loudspeakers_amplitudes;
    Cicm_Vector_Double m_loudspeakers_peaks;
    Cicm_Vector_Double m_loudspeakers_energies;
    Cicm_Double        m_vector_coordinates_double[4];
    Cicm_Float         m_vector_coordinates_float[4];
    
public:
	AmbisonicsMeter(long aNumberOfChannel = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
    
    void         setNumberOfLoudspeakers(long aNumberOfChannels);
    void         setVectorSize(long aVectorSize);
    void         setLoudspeakerAngle(long anIndex, double anAngle);
    //void         setLoudspeakerAngles(long len, double* angles);
    
    double       getLoudspeakerPeaks(long anIndex);
    double       getLoudspeakerEnergy(long anIndex);
    double       getEnergyVectorAbscissa();
    double       getEnergyVectorOrdinate();
    double       getEnergyVectorAngle();
    double       getVelocityVectorAbscissa();
    double       getVelocityVectorOrdinate();
    double       getVelocityVectorAngle();
    std::string  getChannelName(long anIndex);

	~AmbisonicsMeter();
	
	/* Perform block sample */
	inline void process(float** inputs)
	{
        for(int i = 0; i < m_number_of_inputs; i++)
        {
            m_loudspeakers_amplitudes[i] = inputs[i][0];
            m_loudspeakers_peaks[i] = inputs[i][0];
            for(int j = 0; j < m_vector_size; j++)
            {
                if(fabs(inputs[i][j]) > fabs(m_loudspeakers_peaks[i]))
                    m_loudspeakers_peaks[i] = inputs[i][j];
            }
        }
	}
    
    /* Perform block sample */
	inline void process(double** inputs)
	{
        for(int i = 0; i < m_number_of_inputs; i++)
        {
            m_loudspeakers_amplitudes[i] = inputs[i][0];
            m_loudspeakers_peaks[i] = inputs[i][0];
            for(int j = 0; j < m_vector_size; j++)
            {
                if(fabs(inputs[i][j]) > fabs(m_loudspeakers_peaks[i]))
                    m_loudspeakers_peaks[i] = inputs[i][j];
            }
        }
	}
    
    inline void processEnergy()
	{
        for(int i = 0; i < m_number_of_inputs; i++)
            m_loudspeakers_energies[i] = 20. * log10(fabs(m_loudspeakers_peaks[i]));
	}
    
    inline void processVectors()
	{
        m_vectors->process(m_loudspeakers_amplitudes, m_vector_coordinates_double);
	}
};



#endif


