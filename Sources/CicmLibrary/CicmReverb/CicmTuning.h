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

#ifndef DEF_TUNING
#define DEF_TUNING

const long   numcombs		= 8;
const long   numallpasses	= 4;
const double muted          = 0;
const double fixedgain      = 0.015;
const double scalewet		= 3;
const double scaledry		= 2;
const double scaledamp		= 0.4;
const double scaleroom		= 0.28;
const double offsetroom		= 0.7;
const double initialroom	= 0.5;
const double initialdamp	= 0.5;
const double initialwet		= 1./scalewet;
const double initialdry		= 0;
const double initialwidth	= 1;
const double initialmode	= 0;
const double freezemode		= 0.5;
const long   spread         = 23;


/* For 44100 Hz */
const long combtuning[8]	= {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};
const long allpasstuning[4]	= {556, 441, 341, 225};

#endif


