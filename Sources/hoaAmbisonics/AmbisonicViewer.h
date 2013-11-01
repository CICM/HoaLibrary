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

#ifndef DEF_AMBISONICVIEWER
#define DEF_AMBISONICVIEWER

#include "Ambisonic.h"

class AmbisonicViewer : public Ambisonic
{
	
private:

	long		m_biggest_contribution_index;
	long		m_biggest_distance_index1;
	long		m_biggest_distance_index2;

	double		m_cosinus_buffer[NUMBEROFCIRCLEPOINTS_UI];
	double		m_sinus_buffer[NUMBEROFCIRCLEPOINTS_UI];
	double**	m_harmonics_basis;

	double		m_contributions[NUMBEROFCIRCLEPOINTS_UI];
	double		m_biggest_contribution;
	double		m_biggest_distance;
    
    long        m_biggest_lobe_index1;
    long        m_biggest_lobe_vector_size;

	double		m_vector_x[NUMBEROFCIRCLEPOINTS_UI];
	double		m_vector_y[NUMBEROFCIRCLEPOINTS_UI];
	int         m_vector_color[NUMBEROFCIRCLEPOINTS_UI];
    		
	void	computeTrigo();
	void	computeBasis();
	void	computeRepresentation();
	void	computeContribution();
	void	computeMaximumDistance();
    void	computeBiggestLobe();
    
protected :
    cicm_vector_double	m_harmonics_values;
	
public:
	AmbisonicViewer(long anOrder, long aVectorSize = 2, long aSamplingRate = 44100);
    
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
    
	~AmbisonicViewer();

	inline void process(float* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];

		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
        computeBiggestLobe();
	}

	inline void process(double* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];

		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
        computeBiggestLobe();
	}
    
    void processAll(float* anInputs)
	{
		process(anInputs);
	}

	void processAll(double* anInputs)
	{
		process(anInputs);
	}
    
    inline void processContribAndRep(float* anInputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
    }
    
	inline void processContribAndRep(double* anInputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
    }

    inline void processMaxDist(float* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
	}

	inline void processMaxDist(double* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
	}
    
    inline void processBigLob(float* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
        computeBiggestLobe();
	}

	inline void processBigLob(double* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
        computeBiggestLobe();
	}
};

#endif