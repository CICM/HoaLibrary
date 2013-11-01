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
