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

#include "AmbisonicVector.h"

AmbisonicVector::AmbisonicVector(long aNumberOfLoudspeakers, long aVectorSize) : Planewaves(aNumberOfLoudspeakers, aVectorSize)
{
    m_number_of_outputs = 4;
    m_vector_float = NULL;
    m_vector_double = NULL;
    
    Cicm_Vector_Double_Malloc(m_loudspeakers_double, m_number_of_loudspeakers);
    Cicm_Vector_Float_Malloc(m_loudspeakers_float, m_number_of_loudspeakers);
}

std::string AmbisonicVector::getVectorName(long anIndex)
{
    if (anIndex == 0)
        return "Velocity vector abscissa";
    else if(anIndex == 1)
        return "Velocity vector ordinate";
    else if(anIndex == 2)
        return "Energy vector abscissa";
    else
        return "Energy vector ordinate";
}

void AmbisonicVector::setVectorSize(long aVectorSize)
{
	Planewaves::setVectorSize(aVectorSize);
	if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
	Cicm_Vector_Float_Malloc(m_vector_float, m_vector_size);
	Cicm_Vector_Double_Malloc(m_vector_double, m_vector_size);
}

AmbisonicVector::~AmbisonicVector()
{
    Cicm_Free(m_loudspeakers_double);
    Cicm_Free(m_loudspeakers_float);
    if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
}
