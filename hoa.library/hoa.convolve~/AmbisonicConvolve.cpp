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

#include "AmbisonicConvolve.h"

AmbisonicConvolve::AmbisonicConvolve(int order)
{	
	m_order = order;
	sourceAmbiCoeffs = new std::vector<double>(order*2+1,0);
	m_harmonicsIndex = new int[2*m_order+1];
	
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < 2*m_order+1; i++)
	{
		m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
		if (i%2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}
}

const std::vector<double>& AmbisonicConvolve::process(double* aSample, double* aSample)
{
	for (int i = 0; i< 2*m_order+1; i++) 
	{
		(*sourceAmbiCoeffs)[i] = (*ambiCoeffs)[i] * aSample[abs(m_harmonicsIndex[i])];
	}
	
	return *(sourceAmbiCoeffs);
}


AmbisonicConvolve::~AmbisonicConvolve()
{
	delete m_harmonicsIndex;
	delete sourceAmbiCoeffs;
}