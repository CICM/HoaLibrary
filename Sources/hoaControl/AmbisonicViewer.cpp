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
#include "cicmTools.h"
#include "AmbisonicViewer.h"

AmbisonicViewer::AmbisonicViewer(long anOrder)
{	
	m_order					= Tools::clip_min(anOrder, long(1));
	m_number_of_harmonics	= m_order * 2 + 1;
	computeTrigo();
	computeBasis();

	m_contributions = new double[NUMBEROFCIRCLEPOINTS];
	m_vector_x		= new double[NUMBEROFCIRCLEPOINTS];
	m_vector_y		= new double[NUMBEROFCIRCLEPOINTS];
	m_harmonics_values = new double[NUMBEROFCIRCLEPOINTS];
	m_vector_color	= new int[NUMBEROFCIRCLEPOINTS];
}

void AmbisonicViewer::computeTrigo()
{
	m_cosinus_buffer	= new double[NUMBEROFCIRCLEPOINTS];
	m_sinus_buffer		= new double[NUMBEROFCIRCLEPOINTS];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++) 
	{
		m_cosinus_buffer[i] = cos((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinus_buffer[i]	= sin((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
}

void AmbisonicViewer::computeBasis()
{
	m_harmonics_basis		= new double*[m_number_of_harmonics];
	for (int i = 0; i <= m_number_of_harmonics ; i++)
		m_harmonics_basis[i]	= new double[NUMBEROFCIRCLEPOINTS];

	for(int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
		m_harmonics_basis[0][i] = 0.5;
		
	for (int j = 1; j <= m_order; j++)
	{
		for(int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
		{
			double angularStep = (M_2PI / NUMBEROFCIRCLEPOINTS) * (double)i;
			m_harmonics_basis[j*2][i]	= cos((double)j * angularStep);
			m_harmonics_basis[j*2-1][i] = sin((double)j * angularStep);
		}
	}
}

void AmbisonicViewer::computeRepresentation()
{
	m_vector_x[0] = m_sinus_buffer[0] * fabs(m_contributions[0]);
	m_vector_y[0] = m_cosinus_buffer[0] * fabs(m_contributions[0]);
	m_vector_color[0] = 1;
	for(int i = 1; i < NUMBEROFCIRCLEPOINTS - 1; i++)
	{
		m_vector_x[i] = m_sinus_buffer[i] * fabs(m_contributions[i]);
		m_vector_y[i] = m_cosinus_buffer[i] * fabs(m_contributions[i]);
		if(m_contributions[i] > 0)
			m_vector_color[i] = 1;
		else
			m_vector_color[i] = -1;

		if(m_contributions[i] < 0. && m_contributions[i-1] >= 0.)
        {
			m_vector_x[i] = 0.;
			m_vector_y[i] = 0.;
        }
        else if(m_contributions[i] >= 0. && m_contributions[i-1] < 0.)
        {
			m_vector_x[i] = 0.;
			m_vector_y[i] = 0.;
        }
	}
	m_vector_x[NUMBEROFCIRCLEPOINTS - 1] = m_vector_x[0];
	m_vector_y[NUMBEROFCIRCLEPOINTS - 1] = m_vector_y[0];
	m_vector_color[NUMBEROFCIRCLEPOINTS - 1] = m_vector_color[0];
}

void AmbisonicViewer::computeContribution()
{
	m_biggest_contribution = 0;
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
	{    
		m_contributions[i] = 0.;		
		for(int j = 0; j < m_number_of_harmonics; j++)
			m_contributions[i] += m_harmonics_basis[j][i] * m_harmonics_values[j];
			
		if (fabs(m_contributions[i]) >m_biggest_contribution)
		{
			m_biggest_contribution = fabs(m_contributions[i]);
			//biggestcontrib = (x->f_biggestContrib + 0.5 * x->f_harmonicsValues[0]) / ((double)(x->f_order + 1) * 4.);
		}
	}
}

AmbisonicViewer::~AmbisonicViewer()
{
	free(m_sinus_buffer);
	free(m_cosinus_buffer);
	free(m_contributions);
	free(m_vector_x);
	free(m_vector_y);
	free(m_vector_color);
	free(m_harmonics_values);
	for (int i = 0; i <= m_number_of_harmonics ; i++)
		free(m_harmonics_basis[i]);
	free(m_harmonics_basis);
}