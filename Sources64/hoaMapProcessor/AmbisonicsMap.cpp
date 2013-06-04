/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#include "AmbisonicsMap.h"

AmbisonicsMap::AmbisonicsMap(long anOrder, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
	m_number_of_inputs		= 1;

    m_encoder   = new AmbisonicsEncoder(m_order);
    m_wider     = new AmbisonicsWider(m_order);
    m_lineAbscissa = new CicmLine(aVectorSize);
    m_lineOrdinate = new CicmLine(aVectorSize);
    
    
	setPolarCoordinates(1., 0.);
    setVectorSize(aVectorSize);
    m_lineAbscissa->setCoefficientDirect(0.);
    m_lineOrdinate->setCoefficientDirect(1.);
}


void AmbisonicsMap::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_lineAbscissa->setVectorSize(m_vector_size);
    m_lineOrdinate->setVectorSize(m_vector_size);
}


void AmbisonicsMap::setPolarCoordinates(double aRadius, double anAzimuth)
{
    setAzimtuh(anAzimuth);
    if(aRadius >= 1)
    {
        setWidenValue(1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_widen_vector[i] *= (2. / (aRadius*aRadius + 1.));
    }
    else
    {
        setWidenValue(aRadius);
    }
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_ambiCoeffs[i] *= m_widen_vector[i];
}

void AmbisonicsMap::setCartesianCoordinates(double anAbscissa, double anOrdinate)
{
    setPolarCoordinates(Tools::radius(anAbscissa, anOrdinate), Tools::angle(anAbscissa, anOrdinate) - CICM_PI2);
}

void AmbisonicsMap::setCartesianCoordinatesLine(double anAbscissa, double anOrdinate)
{
    m_lineAbscissa->setCoefficient(anAbscissa);
    m_lineOrdinate->setCoefficient(anOrdinate);
}

AmbisonicsMap::~AmbisonicsMap()
{
    delete m_encoder;
    delete m_wider;
    delete m_lineAbscissa;
    delete m_lineOrdinate;
}

