/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

#include "CicmFilterFir.h"

FilterFir::FilterFir(long anImpulseSize)
{
	m_fir_size		= anImpulseSize;
	m_input_size	= m_fir_size * 2 - 1;

	Cicm_Vector_Float_Malloc(m_fir_vector, m_fir_size);
	Cicm_Vector_Float_Malloc(m_input_vector, m_input_size);
	m_index = m_fir_size;
}

void FilterFir::setImpulseResponse(Cicm_Vector_Float anImpulseResponse)
{
	Cicm_Vector_Float_Copy(anImpulseResponse, m_fir_vector, m_fir_size);
}

FilterFir::~FilterFir()
{
	Cicm_Free(m_fir_vector);
	Cicm_Free(m_input_vector);
}
