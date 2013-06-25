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

#include "AmbisonicsRotate.h"

AmbisonicsRotate::AmbisonicsRotate(long anOrder, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
	m_number_of_inputs		= m_number_of_harmonics + 1;
	
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


double AmbisonicsRotate::getAzimuth()
{
	return m_azimuth;
}

void AmbisonicsRotate::setAzimuth(double aTheta)
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
}


AmbisonicsRotate::~AmbisonicsRotate()
{
	delete m_harmonicCos;
	delete m_harmonicSin;
	delete m_sinLookUp;
	delete m_cosLookUp;
}
