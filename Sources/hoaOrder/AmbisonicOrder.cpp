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

#include "AmbisonicOrder.h"

AmbisonicOrder::AmbisonicOrder(long anOrderIn, long anOrderOut, long aVectorSize)
{	
	m_order_in				= Tools::clip_min(anOrderIn, (long)1);
    m_order_out				= Tools::clip_min(anOrderOut, (long)1);
    
	m_number_of_harmonics_in= m_order_in * 2 + 1;
    m_number_of_harmonics_out= m_order_out * 2 + 1;
    
    m_number_of_inputs		= m_number_of_harmonics_in;
	m_number_of_outputs		= m_number_of_harmonics_out;
	
    if(m_number_of_harmonics_in > m_number_of_harmonics_out)
        m_number_of_loudspeakers = m_number_of_harmonics_in + 1;
    else
        m_number_of_loudspeakers = m_number_of_harmonics_out + 1;
    
	m_projector				= new ambisonicProjector(m_order_in, m_number_of_loudspeakers);
	m_recomposer			= new ambisonicRecomposer(m_order_out, m_number_of_loudspeakers);
    m_vector                = new double[m_number_of_loudspeakers];
    m_vector_block          = new double*[m_number_of_loudspeakers];
	setVectorSize(aVectorSize);
}

long AmbisonicOrder::getOrderIn()
{
	return m_order_in;
}

long AmbisonicOrder::getOrderOut()
{
	return m_order_out;
}

long AmbisonicOrder::getNumberOfHarmonicsIn()
{
	return m_number_of_harmonics_in;
}

long AmbisonicOrder::getNumberOfHarmonicsOut()
{
	return m_number_of_harmonics_out;
}

long AmbisonicOrder::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicOrder::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicOrder::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicOrder::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
    m_projector->setVectorSize(m_vector_size);
    m_recomposer->setVectorSize(m_vector_size);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        delete m_vector_block[i];
        m_vector_block[i] = new double[m_vector_size];
    }
    
}

AmbisonicOrder::~AmbisonicOrder()
{
	delete m_projector;
    delete m_recomposer;
    delete m_vector;
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        delete m_vector_block[i];
    }
    delete m_vector_block;
}