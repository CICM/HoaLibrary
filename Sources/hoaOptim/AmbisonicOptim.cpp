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

#include "AmbisonicOptim.h"

AmbisonicOptim::AmbisonicOptim(long anOrder, long anOptimMode, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
	Cicm_Vector_Float_Malloc(m_optim_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_optim_vector_double, m_number_of_harmonics);
	setOptimMode(anOptimMode);
}

long AmbisonicOptim::getOptimMode()
{
    return m_optimMode;
}

void AmbisonicOptim::setOptimMode(long anOptim)
{
	if(anOptim != m_optimMode)
	{
		if(anOptim == Hoa_InPhase_Optim)
			computeInPhaseOptim();
		else if(anOptim == Hoa_MaxRe_Optim)
			computeReOptim();
		else
			computeBasicOptim();
	}
    for (int i = 0; i < m_number_of_harmonics; i++)
    {
        m_optim_vector_float[i] = m_optim_vector_double[i];
    }
}

void AmbisonicOptim::computeBasicOptim()
{
	m_optimMode = Hoa_Basic_Optim;
	for (int i = 0; i < m_number_of_harmonics; i++)
		m_optim_vector_double[i] = 1.;
}

void AmbisonicOptim::computeReOptim()
{
	m_optimMode = Hoa_MaxRe_Optim;
	for (int i = 0; i < m_number_of_harmonics; i++)
	{
		if (i == 0)
			m_optim_vector_double[i] = 1.;
		else
			m_optim_vector_double[i] = cos(abs(getHarmonicIndex(i)) * CICM_PI / (2 * m_order + 2));
	}
	
}

void AmbisonicOptim::computeInPhaseOptim()
{
	m_optimMode = Hoa_InPhase_Optim;

	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optim_vector_double[i] = 1.;
		else
        {
			m_optim_vector_double[i] = (long double)(Tools::factoriel(m_order) * (double)Tools::factoriel(m_order)) / (long double)(Tools::factoriel(m_order+getHarmonicOrder(i)) * Tools::factoriel(m_order-getHarmonicOrder(i)));
        }
	}
}

AmbisonicOptim::~AmbisonicOptim()
{
	Cicm_Free(m_optim_vector_float);
    Cicm_Free(m_optim_vector_double);
}

