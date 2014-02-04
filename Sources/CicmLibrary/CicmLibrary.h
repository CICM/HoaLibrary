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

#ifndef DEF_CICM_LIBRARY
#define DEF_CICM_LIBRARY

#include "CicmDefine.h"
#include "CicmVector.h"

#ifdef _WINDOWS

#include "CicmFilters/CicmFilterDelay.h"
#include "CicmDelay/CicmDecorrelation.h"
#include "CicmGranular/CicmQSGS.h"
#include "CicmAmplitude/CicmRingModulation.h"
#include "CicmLines/CicmLine.h"
#include "CicmReverb/CicmFreeverb.h"

#endif

#ifdef __APPLE__

#include "CicmFilters/CicmFilterDelay.h"
#include "CicmDelay/CicmDecorrelation.h"
#include "CicmGranular/CicmQSGS.h"
#include "CicmAmplitude/CicmRingModulation.h"
#include "CicmLines/CicmLine.h"
#include "CicmReverb/CicmFreeverb.h"
#endif


#endif


