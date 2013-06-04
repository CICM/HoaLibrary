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

#ifndef DEF_AMBISONICSWIDER
#define DEF_AMBISONICSWIDER

#include "../CicmLibrary/CicmLine.h"
#include "../HoaAmbisonics/Ambisonics.h"
#include "../hoaEncoder/AmbisonicsEncoder.h"
#include "../hoaWider/AmbisonicsWider.h"

class AmbisonicsMap : public Ambisonics
{
private:
    AmbisonicsEncoder*  m_encoder;
    AmbisonicsWider*    m_wider;
    CicmLine*           m_lineAbscissa;
    CicmLine*           m_lineOrdinate;
    
public:
	AmbisonicsMap(long anOrder = 1, long aVectorSize = 0);
    
    void setPolarCoordinates(double aRadius, double anAzimuth);
    void setCartesianCoordinates(double anAbscissa, double anOrdinate);
    void setCartesianCoordinatesLine(double anAbscissa, double anOrdinate);
    void setVectorSize(long aVectorSize);

	~AmbisonicsMap();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type aInputs, Type* aOutputs)
	{
        setCartesianCoordinates(m_lineAbscissa->process(), m_lineOrdinate->process());
		for(int i = 0; i < m_number_of_harmonics; i++)
			aOutputs[i] += aInputs * m_ambiCoeffs[i];
	}

	/* Perform block sample */
	template<typename Type> void process(Type* aInputs, Type** aOutputs)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
            setCartesianCoordinates(m_lineAbscissa->process(), m_lineOrdinate->process());
			for(int j = 0; j < m_number_of_harmonics; j++)
            {
                aOutputs[j][i] += aInputs[i] * m_ambiCoeffs[j];
            }
		}
	}

};



#endif


