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

#include "AmbisonicViewer.h"

AmbisonicViewer::AmbisonicViewer(long anOrder, long aVectorSize, long aSamplingRate) : Ambisonic(anOrder, aVectorSize, aSamplingRate)
{	
    m_biggest_contribution = 0;
    m_harmonics_basis = new double*[m_number_of_harmonics];
    m_number_of_outputs = 0;
	for (int i = 0; i < m_number_of_harmonics ; i++)
		m_harmonics_basis[i] = new double[NUMBEROFCIRCLEPOINTS_UI];

	m_harmonics_values = new double[m_number_of_harmonics];
    for(int i = 0; i < m_number_of_harmonics; i++)
		m_harmonics_values[i] = 0.;

	computeTrigo();
	computeBasis();
    
	computeContribution();
	computeRepresentation();
}

void AmbisonicViewer::computeTrigo()
{	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++) 
	{
		double azimuth = (double)i * CICM_2PI / (double)(NUMBEROFCIRCLEPOINTS_UI);
        m_cosinus_buffer[i] = cos(CICM_2PI - azimuth);
		m_sinus_buffer[i]	= sin(CICM_2PI - azimuth);
	}
}

void AmbisonicViewer::computeBasis()
{	
	for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		m_harmonics_basis[0][i] = 0.5;
		
	for (int j = 1; j <= m_order; j++)
	{
		for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		{
			double angularStep = CICM_2PI / (double)(NUMBEROFCIRCLEPOINTS_UI) * (double)i;
			m_harmonics_basis[j*2][i]	= cos((double)j * angularStep);
			m_harmonics_basis[j*2-1][i] = sin((double)j * angularStep);
		}
	}
}

void AmbisonicViewer::computeContribution()
{
	m_biggest_contribution = 1.;
    m_biggest_contribution_index = 0;
    double fabscontrib = 0.;
    for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
    {
        m_contributions[i] = 0.;
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
            m_contributions[i] += m_harmonics_basis[j][i] * m_harmonics_values[j];
        }
        fabscontrib = fabs(m_contributions[i]);
        if (fabscontrib > m_biggest_contribution)
        {
            m_biggest_contribution = fabscontrib;
            m_biggest_contribution_index = i;
        }
    }
}

void AmbisonicViewer::computeRepresentation()
{
    double fabscontrib = 0.;
	if(m_biggest_contribution == 0.)
	{
		for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		{
			m_vector_x[i] = m_vector_y[i] = 0.;
			m_vector_color[i] = -1;
		}
	}
	else
	{
		for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		{
			fabscontrib = fabs(m_contributions[i]);
		
			m_vector_x[i] = (m_sinus_buffer[i] * fabscontrib) / m_biggest_contribution;
			m_vector_y[i] = (m_cosinus_buffer[i] * fabscontrib) / m_biggest_contribution;
        
			if(m_contributions[i] > 0.)
				m_vector_color[i] = 1;
			else
				m_vector_color[i] = -1;
		}
	}
}

void AmbisonicViewer::computeMaximumDistance()
{
	m_biggest_distance = 0;;
	double distanceMax = 0.;
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
	{    
		long indexPlu = m_biggest_contribution_index + i;
		if(indexPlu >= NUMBEROFCIRCLEPOINTS_UI)
			indexPlu -= NUMBEROFCIRCLEPOINTS_UI;
		long indexMin = m_biggest_contribution_index - i;
		if(indexMin < 0)
			indexMin += NUMBEROFCIRCLEPOINTS_UI;

		distanceMax = Tools::distance_euclidean(m_vector_x[indexPlu], m_vector_y[indexPlu], m_vector_x[indexMin], m_vector_y[indexMin]);
		if (distanceMax > m_biggest_distance)
		{
			m_biggest_distance = distanceMax;
			m_biggest_distance_index1 = indexPlu;
			m_biggest_distance_index2 = indexMin;
		}
	}
}

void AmbisonicViewer::computeBiggestLobe()
{
    long index;
    long vectorSize = 0;

    for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
	{
		index = m_biggest_contribution_index - i;
		if(index < 0)
			index += NUMBEROFCIRCLEPOINTS_UI;
        
        if (m_contributions[index] < 0.)
		{
			m_biggest_lobe_index1 = index+1;
            break;
		}
	}
    
    for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
	{
		index = m_biggest_lobe_index1 + i;
		if(index >= NUMBEROFCIRCLEPOINTS_UI)
			index -= NUMBEROFCIRCLEPOINTS_UI;
        vectorSize++;
        if (m_contributions[index] < 0.)
            break;
	}
    
    m_biggest_lobe_vector_size = vectorSize;
}

long AmbisonicViewer::getBiggestLobeNbPoint()
{
    return m_biggest_lobe_vector_size;
}

double AmbisonicViewer::getBiggestLobe_x(long anIndex)
{
    long index = m_biggest_lobe_index1 + anIndex;
    if(index >= NUMBEROFCIRCLEPOINTS_UI)
        index -= NUMBEROFCIRCLEPOINTS_UI;
	return m_vector_x[(int)Tools::clip(index, 0, (NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicViewer::getBiggestLobe_y(long anIndex)
{
	long index = m_biggest_lobe_index1 + anIndex;
    if(index >= NUMBEROFCIRCLEPOINTS_UI)
        index -= NUMBEROFCIRCLEPOINTS_UI;
	return m_vector_y[(int)Tools::clip(index, 0, (NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicViewer::getContributions(long anIndex)
{
	return m_contributions[(int)Tools::clip(anIndex, 0, (NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicViewer::getAbscisseValue(long anIndex)
{
    anIndex = Tools::clip(anIndex, (long)0, (long)NUMBEROFCIRCLEPOINTS_UI - 1);
	return m_vector_x[anIndex];
}

double AmbisonicViewer::getOrdinateValue(long anIndex)
{
    anIndex = Tools::clip(anIndex, (long)0, (long)NUMBEROFCIRCLEPOINTS_UI - 1);
	return m_vector_y[anIndex];
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
    anIndex = Tools::clip(anIndex, (long)0, (long)NUMBEROFCIRCLEPOINTS_UI - 1);
	return m_vector_color[anIndex];
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
	free(m_harmonics_values);
	for (int i = 0; i < m_number_of_harmonics ; i++)
		free(m_harmonics_basis[i]);
	free(m_harmonics_basis);
}