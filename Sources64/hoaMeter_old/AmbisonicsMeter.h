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
    Cicm_Vector_Double m_loudspeakers_energies;
    Cicm_Double        m_vector_coordinates_double[4];
    Cicm_Float         m_vector_coordinates_float[4];
    
public:
	AmbisonicsMeter(double aConfiguration = 1., long aVectorSize = 0, double aSamplingRate = 44100.);
    
    double       getLoudspeakerAmplitude(long anIndex);
    double       getLoudspeakerEnergy(long anIndex);
    double       getEnergyVectorAbscissa();
    double       getEnergyVectorOrdinate();
    double       getVelocityVectorAbscissa();
    double       getVelocityVectorOrdinate();

	~AmbisonicsMeter();
	
	/* Perform block sample */
	inline void process(float** inputs)
	{
        for(int i = 0; i < m_number_of_inputs; i++)
        {
            m_loudspeakers_amplitudes[i] = inputs[i][0];
            for(int j = 0; j < m_vector_size; j++)
            {
                if(fabs(inputs[i][j]) > fabs(m_loudspeakers_amplitudes[i]))
                    m_loudspeakers_amplitudes[i] = inputs[i][j];
            }
        }
        for(int i = 0; i < m_vector_size; i++)
        {
            m_vectors->process(inputs[i], m_vector_coordinates_float);
            for(int j = 0; j < 4; j++)
            {
                m_vector_coordinates_double[j] = m_vector_coordinates_float[j];
            }
        }
	}
    
    /* Perform block sample */
	inline void process(double** inputs)
	{
        for(int i = 0; i < m_number_of_inputs; i++)
        {
            m_loudspeakers_amplitudes[i] = inputs[i][0];
            for(int j = 0; j < m_vector_size; j++)
            {
                if(fabs(inputs[i][j]) > fabs(m_loudspeakers_amplitudes[i]))
                    m_loudspeakers_amplitudes[i] = inputs[i][j];
            }
        }
        for(int i = 0; i < m_vector_size; i++)
        {
            m_vectors->process(inputs[i], m_vector_coordinates_double);
        }
	}
};



#endif


