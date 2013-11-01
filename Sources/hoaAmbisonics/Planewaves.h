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

#ifndef DEF_PLANEWAVES
#define DEF_PLANEWAVES

#include "../CicmLibrary/CicmLibrary.h"

class Planewaves
{
protected:
	long	m_number_of_outputs;
	long	m_number_of_inputs;
    long    m_number_of_loudspeakers;
    
    cicm_vector_double     m_angles_of_loudspeakers_double;
    cicm_vector_double     m_abscissa_of_loudspeakers_double;
    cicm_vector_double     m_ordinate_of_loudspeakers_double;
    
    cicm_vector_float     m_angles_of_loudspeakers_float;
    cicm_vector_float     m_abscissa_of_loudspeakers_float;
    cicm_vector_float     m_ordinate_of_loudspeakers_float;
    
	long	m_vector_size;
    long	m_sampling_rate;
    
    void computeConfiguration(bool standardOnOff = 0);
public:
	Planewaves(long aNumberOfLoudspeakers = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
	
	long            getNumberOfInputs();
	long            getNumberOfOutputs();
    long            getNumberOfLoudspeakers();
    double          getLoudspeakerAngle(long anIndex);
    double          getLoudspeakerAbscissa(long anIndex);
    double          getLoudspeakerOrdinate(long anIndex);
    std::string     getLoudspeakerName(long anIndex);
	long            getVectorSize();
	long            getSamplingRate();

    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff = 0);
    void setLoudspeakerAngleDegrees(long anIndex, double anAngle);
    void setLoudspeakerAngleRadians(long anIndex, double anAngle);
    void setLoudspeakerAnglesDegrees(long aSize, double* angles);
    void setLoudspeakerAnglesRadians(long asize, double* angles);
    
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


