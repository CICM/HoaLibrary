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

#include "AmbisonicsDiffuser.h"

AmbisonicsDiffuser::AmbisonicsDiffuser(long anOrder, bool aMode, long aVectorSize, long aSamplingRate) : Ambisonic(anOrder, aVectorSize, aSamplingRate)
{
    m_mode = Tools::clip(aMode, Hoa_No_Encoding, Hoa_Post_Encoding);
    if(m_mode == Hoa_No_Encoding)
        m_number_of_inputs = 1;

    m_encoding_compensation = 0;
    m_diffuse_factor = 1.;
}

bool AmbisonicsDiffuser::getMode()
{
    return m_mode;
}

double AmbisonicsDiffuser::getDiffuseFactor()
{
    return m_diffuse_factor;
}

bool AmbisonicsDiffuser::getEncodingCompensation()
{
    return m_encoding_compensation;
}

void AmbisonicsDiffuser::setDiffuseFactor(double aDiffuseValue)
{
    if(m_mode == Hoa_Post_Encoding)
        m_diffuse_factor = Tools::clip(aDiffuseValue, 0., 1.);
}

void AmbisonicsDiffuser::setEncodingCompensation(bool OnOff)
{
    if(m_mode == Hoa_Post_Encoding)
        m_encoding_compensation = Tools::clip(OnOff, 0, 1);
}

AmbisonicsDiffuser::~AmbisonicsDiffuser()
{
	;
}

