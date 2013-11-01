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

#include "AmbisonicRotate.h"

AmbisonicRotate::AmbisonicRotate(long anOrder, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
	m_number_of_inputs		= m_number_of_harmonics + 1;
	m_azimuth       = -1.;
	m_harmonicCos   = new double[m_order];
	m_harmonicSin   = new double[m_order];
	m_cosLookUp     = new double[NUMBEROFCIRCLEPOINTS];
	m_sinLookUp     = new double[NUMBEROFCIRCLEPOINTS];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++) 
	{
		m_cosLookUp[i] = cos((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinLookUp[i] = sin((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
	setAzimuth(0.);
}


double AmbisonicRotate::getAzimuth()
{
	return m_azimuth;
}

void AmbisonicRotate::setAzimuth(double aTheta)
{
    if(aTheta != m_azimuth)
    {
        long tmpAngle;
        if (aTheta < 0)
            aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;
        double tmpTheta = aTheta;
        m_azimuth = fmod(aTheta + CICM_2PI, CICM_2PI);
        for(int i = 0; i < m_order; i++)
        {
            double angleFactor = tmpTheta*NUMBEROFCIRCLEPOINTS/(CICM_2PI);
            
            tmpAngle = (long)(angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
            m_harmonicSin[i] = m_sinLookUp[tmpAngle];
            m_harmonicCos[i] = m_cosLookUp[tmpAngle];
            
            tmpTheta += aTheta;
        }
        m_azimuth = aTheta;
    }
}


AmbisonicRotate::~AmbisonicRotate()
{
	delete m_harmonicCos;
	delete m_harmonicSin;
	delete m_sinLookUp;
	delete m_cosLookUp;
}
