/*
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


#ifndef DEF_AMBISONITOOL
#define DEF_AMBISONITOOL

#include "cicmTools.h"
#include "AmbisonicEase.h"
#include "AmbisonicLine.h"
class AmbisonicPolyEase
{
	
private:
    vector <AmbisonicEase*> m_eases;
    vector <long>           m_mute;
    long    m_number_of_sources;
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;
    
    double   m_radius[64];
    double   m_azimuth[64];

public:
	AmbisonicPolyEase(long anOrder = 4, long aNumberOfSources = 1, long aVectorSize = 0);
    
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
    long getNumberOfSources();
    float getRadius(long aSourceIndex);
    float getAzimuth(long aSourceIndex);
    long getMuted(long aSourceIndex);
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    void setNumberOfSources(long aNumberOfSources);
	void setVectorSize(long aVectorSize);
    void setCartesianCoordinates(long aSourceIndex, double anAbscissa, double anOrdinate);
    void setPolarCoordinates(long aSourceIndex, double aRadius, double anAzimuth);
    void setMuted(long aSourceIndex, long aValue);
    
	~AmbisonicPolyEase();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
            aOutputs[i] = 0.;
		for(int i = 0; i < m_number_of_sources; i++)
        {
            if(m_mute[i] != 1)
            {
                m_eases[i]->process(aInputs[i], aOutputs);
            }
        }
    }
	
	/* Perform block sample */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
        Type* outputs;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            outputs = aOutputs[i];
            for(int j = 0; j < m_vector_size; j++)
                outputs[j] = 0.;
        }
        
		for(int i = 0; i < m_number_of_sources; i++)
        {
            if(m_mute[i] != 1)
            {
                m_eases[i]->process(aInputs[i], aOutputs);
            }
        }
	}
};



#endif


