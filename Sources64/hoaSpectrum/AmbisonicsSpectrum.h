/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#ifndef DEF_AMBISONICSSPECTRUM
#define DEF_AMBISONICSSPECTRUM

#include "../hoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmFft/CicmFft.h"

class AmbisonicsSpectrum : public Ambisonics
{
	
private:
    Cicm_Fft*   m_fft;

	
public:
	AmbisonicsSpectrum(long anOrder = 1, long aVectorSize = 0, double aSamplingRate = 44100.);
	~AmbisonicsSpectrum();
};

#endif