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

#ifndef DEF_AmbisonicsViewer
#define DEF_AmbisonicsViewer

#include "../CicmLibrary/CicmTools.h"

#include <complex>
#include <stdio.h>
#include <vector>

class AmbisonicsViewer
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;

	long		m_biggest_contribution_index;
	long		m_biggest_distance_index1;
	long		m_biggest_distance_index2;

	double*		m_cosinus_buffer;
	double*		m_sinus_buffer;
	double**	m_harmonics_basis;

	double*		m_contributions;
	double		m_biggest_contribution;
	double		m_biggest_distance;
    
    long        m_biggest_lobe_index1;
    long        m_biggest_lobe_vector_size;

	double*		m_harmonics_values;
	double*		m_vector_x;
	double*		m_vector_y;
	int*		m_vector_color;
		
	void	computeTrigo();
	void	computeBasis();
	void	computeRepresentation();
	void	computeContribution();
	void	computeMaximumDistance();
    void	computeBiggestLobe();
	
public:
	AmbisonicsViewer(long anOrder);
	double  getBiggestContribution();
	long    getBiggestContributionIndex();
	double  getContributions(long anIndex);
	double  getAbscisseValue(long anIndex);
	double  getOrdinateValue(long anIndex);
	int     getColor(long anIndex);
	double  getBiggestDistance();
	long    getBiggestDistanceIndex1();
	long    getBiggestDistanceIndex2();
    long    getBiggestLobeNbPoint();
    double  getBiggestLobe_x(long anIndex);
    double  getBiggestLobe_y(long anIndex);
	~AmbisonicsViewer();
	
	template<typename Type> void process(Type* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];

		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
        computeBiggestLobe();
	}
};

#endif