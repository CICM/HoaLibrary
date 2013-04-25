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

	m_harmonics_values = new double[m_number_of_harmonics];
	m_contributions = new double[NUMBEROFCIRCLEPOINTSDISPLAY];
	m_vector_x		= new double[NUMBEROFCIRCLEPOINTSDISPLAY];
	m_vector_y		= new double[NUMBEROFCIRCLEPOINTSDISPLAY];
	m_vector_color	= new int[NUMBEROFCIRCLEPOINTSDISPLAY];
	
	for(int i = 0; i < m_number_of_harmonics; i++)
		m_harmonics_values[i] = 0.;
	computeContribution();
	computeRepresentation();
}

void AmbisonicViewer::computeTrigo()
{
	m_cosinus_buffer	= new double[NUMBEROFCIRCLEPOINTSDISPLAY];
	m_sinus_buffer		= new double[NUMBEROFCIRCLEPOINTSDISPLAY];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY; i++) 
	{
		double azimuth = (double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTSDISPLAY;
		m_cosinus_buffer[i] = cos(CICM_2PI - azimuth);
		m_sinus_buffer[i]	= sin(CICM_2PI - azimuth);
	}
}

void AmbisonicViewer::computeBasis()
{
	m_harmonics_basis		= new double*[m_number_of_harmonics];
	for (int i = 0; i <= m_number_of_harmonics ; i++)
		m_harmonics_basis[i]	= new double[NUMBEROFCIRCLEPOINTSDISPLAY];

	for(int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY; i++)
		m_harmonics_basis[0][i] = 0.5;
		
	for (int j = 1; j <= m_order; j++)
	{
		for(int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY; i++)
		{
			double angularStep = (CICM_2PI / NUMBEROFCIRCLEPOINTSDISPLAY) * (double)i;
			m_harmonics_basis[j*2][i]	= cos((double)j * angularStep);
			m_harmonics_basis[j*2-1][i] = sin((double)j * angularStep);
		}
	}
}

void AmbisonicViewer::computeRepresentation()
{	
	for(int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY - 1; i++)
	{
		m_vector_x[i] = m_sinus_buffer[i] * fabs(m_contributions[i]);
		m_vector_y[i] = m_cosinus_buffer[i] * fabs(m_contributions[i]);
		if(m_contributions[i] > 0.)
			m_vector_color[i] = 1;
		else if (m_contributions[i] < 0.)
			m_vector_color[i] = -1;
		else m_vector_color[i] = 0;

	}
	m_vector_x[NUMBEROFCIRCLEPOINTSDISPLAY - 1] = m_vector_x[0];
	m_vector_y[NUMBEROFCIRCLEPOINTSDISPLAY - 1] = m_vector_y[0];
	m_vector_color[NUMBEROFCIRCLEPOINTSDISPLAY - 1] = m_vector_color[0];
}

void AmbisonicViewer::computeContribution()
{
	m_biggest_contribution = 0;
	m_biggest_contribution_index = 0;
	for (int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY; i++)
	{    
		m_contributions[i] = 0.;		
		for(int j = 0; j < m_number_of_harmonics; j++)
			m_contributions[i] += m_harmonics_basis[j][i] * m_harmonics_values[j];
			
		if (fabs(m_contributions[i]) > m_biggest_contribution)
		{
			m_biggest_contribution = fabs(m_contributions[i]);
			m_biggest_contribution_index = i;
		}
	}
}

void AmbisonicViewer::computeMaximumDistance()
{
	m_biggest_distance = 0;;
	double distanceMax = 0.;
	for (int i = 0; i < NUMBEROFCIRCLEPOINTSDISPLAY; i++)
	{    
		long indexPlu = m_biggest_contribution_index + i;
		if(indexPlu >= NUMBEROFCIRCLEPOINTSDISPLAY)
			indexPlu -= NUMBEROFCIRCLEPOINTSDISPLAY;
		long indexMin = m_biggest_contribution_index - i;
		if(indexMin < 0)
			indexMin += NUMBEROFCIRCLEPOINTSDISPLAY;

		distanceMax = Tools::distance_euclidean(m_vector_x[indexPlu], m_vector_y[indexPlu], m_vector_x[indexMin], m_vector_y[indexMin]);
		if (distanceMax > m_biggest_distance)
		{
			m_biggest_distance = distanceMax;
			m_biggest_distance_index1 = indexPlu;
			m_biggest_distance_index2 = indexMin;
		}
	}
}

double AmbisonicViewer::getContributions(long anIndex)
{
	return m_contributions[Tools::clip(anIndex, (long)0, (long)(NUMBEROFCIRCLEPOINTSDISPLAY - 1))];
}

double AmbisonicViewer::getAbscisseValue(long anIndex)
{
	return m_vector_x[Tools::clip(anIndex, (long)0, (long)(NUMBEROFCIRCLEPOINTSDISPLAY - 1))];
}

double AmbisonicViewer::getOrdinateValue(long anIndex)
{
	return m_vector_y[Tools::clip(anIndex, (long)0, (long)(NUMBEROFCIRCLEPOINTSDISPLAY - 1))];
}

double AmbisonicViewer::getBiggestContribution()
{
	return m_biggest_contribution;
}

long AmbisonicViewer::getBiggestContributionIndex()
{
	return m_biggest_contribution_index;
}

int	AmbisonicViewer::getColor(long anIndex)
{
	return m_vector_color[Tools::clip(anIndex, (long)0, (long)(NUMBEROFCIRCLEPOINTSDISPLAY - 1))];
}

double AmbisonicViewer::getBiggestDistance()
{
	return m_biggest_distance;
}

long AmbisonicViewer::getBiggestDistanceIndex1()
{
	return m_biggest_distance_index1;
}

long AmbisonicViewer::getBiggestDistanceIndex2()
{
	return m_biggest_distance_index2;
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