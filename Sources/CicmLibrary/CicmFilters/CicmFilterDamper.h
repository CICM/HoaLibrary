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

#ifndef DEF_FILTERDAMPER
#define DEF_FILTERDAMPER

#include "CicmFilter.h"

class FilterDamper : public Filter
{
private:
	double m_coefficient;
	double m_buffer;

public:
	FilterDamper(double aCoefficient) : Filter()
    {
        setCoefficient(aCoefficient);
    }
    
	void setCoefficient(double aCoefficient)
    {
        m_coefficient = Tools::clip(aCoefficient, 0., 1.);
    }
    
	inline double process(double aValue)
    {
        m_buffer = aValue * (1. - m_coefficient) + m_buffer * m_coefficient;
        return(m_buffer);
    }
    
	~FilterDamper(){};
};


#endif