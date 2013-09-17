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

#ifndef DEF_HOA_LIBRARY
#define DEF_HOA_LIBRARY

#ifdef _WINDOWS
#include "hoaAmbisonics/AmbisonicsViewer.h"
//#include "hoaConvolve/AmbisonicConvolver.h"
#include "hoaEncoder/AmbisonicsEncoder.h"
#include "hoaFreeverb/AmbisonicFreeverb.h"
#include "hoaRotate/AmbisonicRotate.h"
#include "hoaMultiDecoder/AmbisonicsMultiDecoder.h"
#include "hoaMap/AmbisonicMultiMaps.h"
#include "hoaMap/AmbisonicSourcesTrajectory.h"
#include "hoaMeter/AmbisonicsMeter.h"
#include "hoaOptim/AmbisonicsOptim.h"
#include "hoaProjector/AmbisonicProjector.h"
#include "hoaRecomposer/AmbisonicsRecomposer.h"
#include "hoaRecomposer/AmbisonicVirtualMicUIManager.h"
#include "hoaSpace/AmbisonicSpace.h"
#include "hoaVector/AmbisonicVector.h"
#include "hoaWider/AmbisonicsWider.h"
#endif

#ifdef __APPLE__
/*
#include "hoaAmbisonics/Ambisonic3D.h"
#include "hoaDecoder/AmbisonicDecoder3D.h"
#include "hoaEncoder/AmbisonicEncoder3D.h"
*/
#include "hoaAmbisonics/AmbisonicsViewer.h"
#include "hoaConvolve/AmbisonicConvolver.h"
#include "hoaDelay/AmbisonicsDelay.h"
#include "hoaEncoder/AmbisonicEncoder.h"
#include "hoaFreeverb/AmbisonicFreeverb.h"
#include "hoaFilter/AmbisonicsFilter.h"
#include "hoaGrain/AmbisonicsGrain.h"
#include "hoaMap/AmbisonicMultiMaps.h"
#include "hoaMap/AmbisonicSourcesManager.h"
#include "hoaMap/AmbisonicSourcesPreset.h"
#include "hoaMap/AmbisonicSourcesTrajectory.h"
#include "hoaMeter/AmbisonicsMeter.h"
#include "hoaMultiDecoder/AmbisonicsMultiDecoder.h"
#include "hoaOptim/AmbisonicOptim.h"
#include "hoaProjector/AmbisonicProjector.h"
#include "hoaRecomposer/AmbisonicRecomposer.h"
#include "hoaRingModulation/AmbisonicsRingModulation.h"
#include "hoaRecomposer/AmbisonicVirtualMicUIManager.h"
#include "hoaRotate/AmbisonicRotate.h"
#include "hoaSpace/AmbisonicSpace.h"
#include "hoaGalaxy/AmbisonicsGalaxy.h"
#include "hoaSpectrum/AmbisonicSpectrum.h"
#include "hoaWider/AmbisonicWider.h"
#include "hoaVector/AmbisonicVector.h"

#endif
#endif


