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

