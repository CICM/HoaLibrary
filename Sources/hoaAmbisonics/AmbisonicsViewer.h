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

#ifndef DEF_AmbisonicsViewer
#define DEF_AmbisonicsViewer

#include "../CicmLibrary/CicmLibrary.h"

class AmbisonicsViewer
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
    double      m_representation_offset;

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

	double*		m_harmonics_values;
	double		m_vector_x[NUMBEROFCIRCLEPOINTS_UI];
	double		m_vector_y[NUMBEROFCIRCLEPOINTS_UI];
	int         m_vector_color[NUMBEROFCIRCLEPOINTS_UI];
    		
	void	computeTrigo();
	void	computeBasis();
	void	computeRepresentation();
	void	computeContribution();
	void	computeMaximumDistance();
    void	computeBiggestLobe();
	
public:
	AmbisonicsViewer(long anOrder, double offset = 0.);
    inline long getOrder() {return m_order;}
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
    
    template<typename Type> void processAll(Type* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
        computeBiggestLobe();
	}
    
    template<typename Type> inline void processContribAndRep(Type* anInputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
    }
    
    template<typename Type> void processMaxDist(Type* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
		computeMaximumDistance();
	}
    
    template<typename Type> void processBigLob(Type* anInputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			m_harmonics_values[i] = anInputs[i];
        
		computeContribution();
		computeRepresentation();
        computeBiggestLobe();
	}
};

#endif