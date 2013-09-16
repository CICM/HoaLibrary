/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#include "AmbisonicVector.h"

AmbisonicVector::AmbisonicVector(long aNumberOfLoudspeakers, long aVectorSize) : Planewaves(aNumberOfLoudspeakers, aVectorSize)
{
    m_number_of_outputs = 4;
    m_vector_float = NULL;
    m_vector_double = NULL;
    
    cicm_malloc_vec_d(m_loudspeakers_double, m_number_of_loudspeakers);
    cicm_malloc_vec_f(m_loudspeakers_float, m_number_of_loudspeakers);
}

std::string AmbisonicVector::getVectorName(long anIndex)
{
    if (anIndex == 0)
        return "Velocity vector abscissa";
    else if(anIndex == 1)
        return "Velocity vector ordinate";
    else if(anIndex == 2)
        return "Energy vector abscissa";
    else
        return "Energy vector ordinate";
}

void AmbisonicVector::setVectorSize(long aVectorSize)
{
	Planewaves::setVectorSize(aVectorSize);
	if(m_vector_double)
		cicm_free(m_vector_double);
	if(m_vector_float)
		cicm_free(m_vector_float);
	cicm_malloc_vec_f(m_vector_float, m_vector_size);
	cicm_malloc_vec_d(m_vector_double, m_vector_size);
}

AmbisonicVector::~AmbisonicVector()
{
    cicm_free(m_loudspeakers_double);
    cicm_free(m_loudspeakers_float);
    if(m_vector_double)
		cicm_free(m_vector_double);
	if(m_vector_float)
		cicm_free(m_vector_float);
}
