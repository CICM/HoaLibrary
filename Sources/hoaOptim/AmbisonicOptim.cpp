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

#include "AmbisonicOptim.h"

AmbisonicOptim::AmbisonicOptim(long anOrder, long anOptimMode, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
    m_optimMode = -1;
	cicm_malloc_vec_f(m_optim_vector_float, m_number_of_harmonics);
    cicm_malloc_vec_d(m_optim_vector_double, m_number_of_harmonics);
	setOptimMode(Tools::clip(anOptimMode, Hoa_Basic_Optim, Hoa_InPhase_Optim));
}

double AmbisonicOptim::getCoefficient(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_harmonics)
    {
        return m_optim_vector_double[anIndex];
    }
    else
    {
        return 0.;
    }
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
        for (int i = 0; i < m_number_of_harmonics; i++)
        {
            m_optim_vector_float[i] = m_optim_vector_double[i];
        }

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
	cicm_free(m_optim_vector_float);
    cicm_free(m_optim_vector_double);
}

