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