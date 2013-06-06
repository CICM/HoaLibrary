/*
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


#include "AmbisonicsOptim.h"

AmbisonicsOptim::AmbisonicsOptim(long anOrder, long anOptimMode, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
	Cicm_Vector_Float_Malloc(m_optim_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_optim_vector_double, m_number_of_harmonics);
	setOptimMode(anOptimMode);
}

long AmbisonicsOptim::getOptimMode()
{
    return m_optimMode;
}

void AmbisonicsOptim::setOptimMode(long anOptim)
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

void AmbisonicsOptim::computeBasicOptim()
{
	m_optimMode = Hoa_Basic_Optim;
	for (int i = 0; i < m_number_of_harmonics; i++) 
		m_optim_vector_double[i] = 1.;
}

void AmbisonicsOptim::computeReOptim()
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

void AmbisonicsOptim::computeInPhaseOptim()
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

AmbisonicsOptim::~AmbisonicsOptim()
{
	Cicm_Free(m_optim_vector_float);
    Cicm_Free(m_optim_vector_double);
}

