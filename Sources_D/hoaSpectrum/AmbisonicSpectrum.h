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

#ifndef DEF_AMBISONICSPECTRUM
#define DEF_AMBISONICSPECTRUM

#include "../hoaAmbisonics/Planewaves.h"
#include "../hoaVector/AmbisonicVector.h"
#include "../CicmLibrary/CicmFilters/CicmFilterBiquad.h"

class AmbisonicSpectrum : public Planewaves
{
	
private:
    AmbisonicVector*                   m_vector;
 
    vector <vector <FilterBiquad*> >    m_filter;
    cicm_vector_float**                 m_filtered_signal_float;
    cicm_vector_double**                m_filtered_signal_double;
    cicm_vector_double                  m_frequency;
    
    cicm_vector_double                  m_amplitude;
    cicm_vector_double                  m_abscissa;
    cicm_vector_double                  m_ordinate;
    
    double                              m_vector_values[2];
    double*                             m_loudspeakers_values;
    cicm_vector_double                  m_temp_amplitude_value;
    void initializeFrequencyBands();
    
public:
	AmbisonicSpectrum(long aNumberOfLoudspeakers = 1, long aNumberOfBands = 3, long aVectorSize = 0, long aSamplingRate = 44100);
    
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 0);
    void setLoudspeakerAngle(long anIndex, double anAngle);
    void setFrequencyBand(long anIndex, double aFrequency);
    void setNumberOfBands(long aNumberOfBands);
    
    double getAmplitude(long aBandIndex);
    double getAbscissa(long aBandIndex);
    double getOrdinate(long aBandIndex);
    double getRadius(long aBandIndex);
    double getAngle(long aBandIndex);
    
    double getLogAmplitude(long aBandIndex);
    double getLogAbscissa(long aBandIndex);
    double getLogOrdinate(long aBandIndex);
    double getLogRadius(long aBandIndex);
    double getLogAngle(long aBandIndex);
    
    double getFrequencyBand(long anIndex);
    long   getNumberOfBands();
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    
	~AmbisonicSpectrum();
	
	/* Perform block sample */
    
	inline void process(const double* const* inputs)
	{
        cicm_vector_double* tab_point;
        for(int i = 0; i < m_filter.size(); i++)
        {
            tab_point = m_filtered_signal_double[i];
            for(int j = 0; j < m_number_of_loudspeakers; j++)
            {
                m_filter[i][j]->process(inputs[j], tab_point[j]);
            }
        }
        
        double amplitude;
        cicm_vector_double* vect_point;
        for(int i = 0; i < m_filter.size(); i++)
        {
            vect_point = m_filtered_signal_double[i];
            for(int k = 0; k < m_vector_size; k++)
            {
                amplitude = 0.;
                for(int j = 0; j < m_number_of_loudspeakers; j++)
                {
                    amplitude += fabs(vect_point[j][k]);
                }
                if(amplitude > m_temp_amplitude_value[i])
                    m_temp_amplitude_value[i] = amplitude;
            }
        }
    }
    
    inline void tick()
    {
        cicm_vector_double* vect_point;
        for(int i = 0; i < m_filter.size(); i++)
        {
            vect_point = m_filtered_signal_double[i];
            for(int j = 0; j < m_number_of_loudspeakers; j++)
            {
                m_loudspeakers_values[j] = vect_point[j][m_vector_size-1];
            }
            m_vector->processEnergy(m_loudspeakers_values, m_vector_values);
            m_abscissa[i]   = m_vector_values[0];
            m_ordinate[i]   = m_vector_values[1];
            m_amplitude[i]  = m_temp_amplitude_value[i];
            m_temp_amplitude_value[i] = 0.;
        }
    }

};

#endif