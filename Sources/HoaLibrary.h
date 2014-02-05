/* ==
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEF_HOA_LIBRARY
#define DEF_HOA_LIBRARY

#include "hoaDelay/AmbisonicsDelay.h"
#include "hoaEncoder/AmbisonicEncoder.h"
#include "hoaFreeverb/AmbisonicFreeverb.h"
#include "hoaFilter/AmbisonicsFilter.h"
#include "hoaGrain/AmbisonicsGrain.h"
#include "hoaAmbisonics/AmbisonicViewer.h"
#include "hoaRotate/AmbisonicRotate.h"
#include "hoaMultiDecoder/AmbisonicsMultiDecoder.h"
#include "hoaMap/AmbisonicMultiMaps.h"
#include "hoaMap/AmbisonicSourcesManager.h"
#include "hoaMap/AmbisonicSourcesPreset.h"
#include "hoaMap/AmbisonicSourcesTrajectory.h"
#include "hoaMeter/AmbisonicsMeter.h"
#include "hoaOptim/AmbisonicOptim.h"
#include "hoaProjector/AmbisonicProjector.h"
#include "hoaRecomposer/AmbisonicRecomposer.h"
#include "hoaRingModulation/AmbisonicsRingModulation.h"
#include "hoaRecomposer/AmbisonicVirtualMicUIManager.h"
#include "hoaSpace/AmbisonicSpace.h"
#include "hoaWider/AmbisonicWider.h"
#include "hoaVector/AmbisonicVector.h"

#ifdef __APPLE__

#include "hoaAmbisonics/Hoa3DAmbisonic.h"
#include "hoaDecoder/Hoa3DDecoder.h"
#include "hoaEncoder/Hoa3DEncoder.h"
#include "hoaConvolve/AmbisonicConvolver.h"
#include "hoaGalaxy/AmbisonicsGalaxy.h"
#include "hoaSpectrum/AmbisonicSpectrum.h"

#endif

#ifdef _HOA3D_



 
#endif

#endif


