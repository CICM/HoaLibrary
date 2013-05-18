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

#include "AmbisonicsViewer.h"

AmbisonicsViewer::AmbisonicsViewer(long anOrder, double offset)
{	
	m_order					= Tools::clip_min(anOrder, long(1));
	m_number_of_harmonics	= m_order * 2 + 1;
    m_representation_offset = offset;
	computeTrigo();
	computeBasis();

	m_harmonics_values = new double[m_number_of_harmonics];
	m_contributions = new double[NUMBEROFCIRCLEPOINTS_UI];
	m_vector_x		= new double[NUMBEROFCIRCLEPOINTS_UI];
	m_vector_y		= new double[NUMBEROFCIRCLEPOINTS_UI];
	m_vector_color	= new int[NUMBEROFCIRCLEPOINTS_UI];
	
	for(int i = 0; i < m_number_of_harmonics; i++)
		m_harmonics_values[i] = 0.;
    
	computeContribution();
	computeRepresentation();
}

void AmbisonicsViewer::computeTrigo()
{
	m_cosinus_buffer	= new double[NUMBEROFCIRCLEPOINTS_UI];
	m_sinus_buffer		= new double[NUMBEROFCIRCLEPOINTS_UI];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++) 
	{
		double azimuth = double(i) * CICM_2PI / double(NUMBEROFCIRCLEPOINTS_UI);
        m_cosinus_buffer[i] = cos(CICM_2PI - azimuth + m_representation_offset);
		m_sinus_buffer[i]	= sin(CICM_2PI - azimuth + m_representation_offset);
        /*
		m_cosinus_buffer[i] = cos(CICM_2PI - azimuth - CICM_PI2);
		m_sinus_buffer[i]	= sin(CICM_2PI - azimuth - CICM_PI2);
        */
	}
}

void AmbisonicsViewer::computeBasis()
{
	m_harmonics_basis           = new double*[m_number_of_harmonics];
	for (int i = 0; i <= m_number_of_harmonics ; i++)
		m_harmonics_basis[i]	= new double[NUMBEROFCIRCLEPOINTS_UI];

	for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		m_harmonics_basis[0][i] = 0.5;
		
	for (int j = 1; j <= m_order; j++)
	{
		for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
		{
			double angularStep = (CICM_2PI / NUMBEROFCIRCLEPOINTS_UI) * double(i);
			m_harmonics_basis[j*2][i]	= cos(double(j) * angularStep);
			m_harmonics_basis[j*2-1][i] = sin(double(j) * angularStep);
		}
	}
}

void AmbisonicsViewer::computeContribution()
{
	m_biggest_contribution = 0;
	m_biggest_contribution_index = 0;
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
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

void AmbisonicsViewer::computeRepresentation()
{
	for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
	{
		m_vector_x[i] = m_sinus_buffer[i] * fabs(m_contributions[i]);
		m_vector_y[i] = m_cosinus_buffer[i] * fabs(m_contributions[i]);
		if(m_contributions[i] > 0.)
			m_vector_color[i] = 1;
		else if (m_contributions[i] < 0.)
			m_vector_color[i] = -1;
		else m_vector_color[i] = 0;
	}
}

void AmbisonicsViewer::computeMaximumDistance()
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

void AmbisonicsViewer::computeBiggestLobe()
{
    long index;
    double distance1, distance2;
    long vectorSize = 1;
    distance1 = Tools::radius(m_vector_x[m_biggest_contribution_index], m_vector_y[m_biggest_contribution_index]);
    
    // looking for the first index
    for (int i = 1; i < NUMBEROFCIRCLEPOINTS_UI; i++)
	{
		index = m_biggest_contribution_index - i;
		if(index < 0)
			index += NUMBEROFCIRCLEPOINTS_UI;
        
		distance2 = Tools::radius(m_vector_x[index], m_vector_y[index]);
        
		if ( (distance2 - distance1) <= 0)
		{
			m_biggest_lobe_index1 = index;
            vectorSize++;
		}
        else
            break;        
        distance1 = distance2;
	}
    
    if (vectorSize < NUMBEROFCIRCLEPOINTS_UI-1)
    {
        distance1 = Tools::radius(m_vector_x[m_biggest_contribution_index], m_vector_y[m_biggest_contribution_index]);
        
        for (int i = 1; i < NUMBEROFCIRCLEPOINTS_UI-1; i++)
        {
            index = m_biggest_contribution_index + i;
            if(index >= NUMBEROFCIRCLEPOINTS_UI)
                index -= NUMBEROFCIRCLEPOINTS_UI;
            
            distance2 = Tools::radius(m_vector_x[index], m_vector_y[index]);
            
            if ( (distance2 - distance1) <= 0)
                vectorSize++;
            else
                break;
            distance1 = distance2;
        }
    }
    else
    {
        m_biggest_lobe_index1 = 0;
    }
    
    m_biggest_lobe_vector_size = vectorSize;
}

long AmbisonicsViewer::getBiggestLobeNbPoint()
{
    return m_biggest_lobe_vector_size;
}

double AmbisonicsViewer::getBiggestLobe_x(long anIndex)
{
    long index = m_biggest_lobe_index1 + anIndex;
    if(index >= NUMBEROFCIRCLEPOINTS_UI)
        index -= NUMBEROFCIRCLEPOINTS_UI;
	return m_vector_x[Tools::clip(index, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getBiggestLobe_y(long anIndex)
{
	long index = m_biggest_lobe_index1 + anIndex;
    if(index >= NUMBEROFCIRCLEPOINTS_UI)
        index -= NUMBEROFCIRCLEPOINTS_UI;
	return m_vector_y[Tools::clip(index, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getContributions(long anIndex)
{
	return m_contributions[Tools::clip(anIndex, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getAbscisseValue(long anIndex)
{
	return m_vector_x[Tools::clip(anIndex, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getOrdinateValue(long anIndex)
{
	return m_vector_y[Tools::clip(anIndex, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getBiggestContribution()
{
	return m_biggest_contribution;
}

long AmbisonicsViewer::getBiggestContributionIndex()
{
	return m_biggest_contribution_index;
}

int	AmbisonicsViewer::getColor(long anIndex)
{
	return m_vector_color[Tools::clip(anIndex, long(0), long(NUMBEROFCIRCLEPOINTS_UI - 1))];
}

double AmbisonicsViewer::getBiggestDistance()
{
	return m_biggest_distance;
}

long AmbisonicsViewer::getBiggestDistanceIndex1()
{
	return m_biggest_distance_index1;
}

long AmbisonicsViewer::getBiggestDistanceIndex2()
{
	return m_biggest_distance_index2;
}

AmbisonicsViewer::~AmbisonicsViewer()
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