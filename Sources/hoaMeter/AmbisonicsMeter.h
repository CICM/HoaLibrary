/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_AMBISONICSMETER
#define DEF_AMBISONICSMETER

#include "../hoaVector/AmbisonicVector.h"

class AmbisonicsMeter : public Planewaves
{
protected:
    AmbisonicVector*   m_vectors;
    
    cicm_vector_double m_loudspeakers_amplitudes;
    cicm_vector_double m_loudspeakers_peaks;
    cicm_vector_double m_loudspeakers_energies;
    double        m_vector_coordinates_double[4];
    float         m_vector_coordinates_float[4];
    
    cicm_vector_double m_loudspeakers_angles_mapped;
    cicm_vector_double m_loudspeakers_angles_width;
    
public:
	AmbisonicsMeter(long aNumberOfChannel = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
    
    void         setNumberOfLoudspeakers(long aNumberOfChannels);
    void         setVectorSize(long aVectorSize);
    void         setLoudspeakerAngleDegrees(long anIndex, double anAngle);
    void         setLoudspeakerAnglesDegrees(long aSize, double* angles);
    
    double       getLoudspeakerPeaks(long anIndex);
    double       getLoudspeakerEnergy(long anIndex);
    double       getEnergyVectorAbscissa();
    double       getEnergyVectorOrdinate();
    double       getEnergyVectorAngle();
    double       getEnergyVectorRadius();
    double       getVelocityVectorAbscissa();
    double       getVelocityVectorOrdinate();
    double       getVelocityVectorAngle();
    double       getVelocityVectorRadius();
    
    double       getLoudspeakerAngleMapped(long anIndex);
    double       getLoudspeakerWidth(long anIndex);
    double       getLoudspeakerAngleRadian(long anIndex);
    double       getLoudspeakerAngleMappedRadian(long anIndex);
    double       getLoudspeakerWidthRadian(long anIndex);
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


