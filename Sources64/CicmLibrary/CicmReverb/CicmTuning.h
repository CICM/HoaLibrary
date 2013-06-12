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


