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

#ifndef DEF_MAX_MANAGER
#define DEF_MAX_MANAGER

#include "../MaxAmbisonic.h"

class MaxManager : public MaxAmbisonic
{
private:
    
public:
    MaxManager(t_hoa_object* aParentObject, long argc = 0, t_atom* argv = NULL) : MaxAmbisonic(aParentObject, argc, argv){};
    void realloc_ambisonic()
    {m_parent->f_ambi = new AmbisonicWider(object_attr_getlong(m_parent, gensym("order")), sys_getblksize());}
    ~MaxManager(){};
};

#endif