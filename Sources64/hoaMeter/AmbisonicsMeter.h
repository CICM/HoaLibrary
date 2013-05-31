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
	AmbisonicsMeter(long aNumberOfChannel = 1., long aVectorSize = 0, double aSamplingRate = 44100.);
    
    void         setNumberOfChannels(long aNumberofChannels);
    void         setVectorSize(long aVectorSize);
    void         setLoudspeakerAngle(long anIndex, double anAngle);
    void         setLoudspeakerAngles(long len, double* angles);
    
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


