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

const long   numcombs		= 4;
const long   numallpasses	= 3;
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
const long      DelayCombTuning[4]      = {1687, 1601, 2053, 2251};
const double    FeedbackCombTuning[4]   = {0.773, 0.802, 0.753, 0.733};
const long      allpasstuning[3]        = {247, 113, 37};

#endif


