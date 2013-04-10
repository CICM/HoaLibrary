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
#include "AmbisonicEncoder.h"
#include "AmbisonicWider.h"
#include "AmbisonicOptim.h"
#include "AmbisonicDecoder.h"

class AmbisonicTool
{
	
private:
    vector <AmbisonicEncoder*> m_encoders;
    vector <AmbisonicWider*> m_widers;
    AmbisonicDecode* m_decoder;
    
    long    m_number_of_loudspeakers;
    long    m_number_of_sources;
	long	m_order;
	long	m_number_of_harmonics;
	long	m_number_of_inputs;
	long	m_number_of_outputs;
	long	m_vector_size;
    
    float  m_weight_values[64];
    float  m_harmonics_vector[63];
    float* m_harmonics_block_vector[63];
    float* m_harmonics_block_copy[63];
    
    float  m_radius[64];
    float  m_azimuth[64];
    
    void    freeSources();
    void    freeLoudspeakers();
public:
	AmbisonicTool(long aNumberOfLoudspeakers = 4, long aNumberOfSources = 1, long aVectorSize = 0);
    
	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();
	long getNumberOfLoudspeakers();
    long getNumberOfSources();
    float getRadius(long aSourceIndex);
    float getAzimuth(long aSourceIndex);
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers);
    void setNumberOfSources(long aNumberOfSources);
	void setVectorSize(long aVectorSize);
    void setCartesianCoordinates(long aSourceIndex, double anAbscissa, double anOrdinate);
    void setPolarCoordinates(long aSourceIndex, double aRadius, double anAzimuth);
    
	~AmbisonicTool();
	
	/* Perform sample by sample */
	void process(float* aInputs, float* aOutputs)
	{	
		for(int i = 0; i < m_number_of_sources; i++)
            m_widers[i]->process(aInputs[i], m_harmonics_vector);
        
        m_decoder->process(m_harmonics_vector, aOutputs);
	}
	
	/* Perform block sample */
	void process(float** aInputs, float** aOutputs)
	{
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
            for(int k = 0; k < m_vector_size; k++)
            {
                m_harmonics_block_vector[j][k] = 0;
            }
        }
		for(int i = 0; i < m_number_of_sources; i++)
        {
            m_widers[i]->process(aInputs[i], m_harmonics_block_copy);
            for(int j = 0; j < m_number_of_harmonics; j++)
            {
                for(int k = 0; k < m_vector_size; k++)
                {
                    m_harmonics_block_vector[j][k] += m_harmonics_block_copy[j][k];
                }
            }
        }
        m_decoder->process(m_harmonics_block_vector, aOutputs);
	}
};



#endif


