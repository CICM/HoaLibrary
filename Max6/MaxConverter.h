/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_MAX_CONVERTER
#define DEF_MAX_CONVERTER

#include "../Sources/HoaLibrary.h"
extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "commonsyms.h"
#include "ext_parameter.h"
}

class CicmMax {
public:
    static t_jrgba cicmColorToMaxColor(color aCicmColor)
    {
        t_jrgba maxColor;
        maxColor.red = aCicmColor.red;
        maxColor.green = aCicmColor.green;
        maxColor.blue = aCicmColor.blue;
        maxColor.alpha = aCicmColor.alpha;
        return maxColor;
    }
    
    static t_jrgba jrgba_addContrast(t_jrgba baseColor, double contrast, bool preserveAlpha = true)
    {
        t_jrgba maxColor = baseColor;
        maxColor.red = Tools::clip(maxColor.red += contrast, 0., 1.);
        maxColor.green = Tools::clip(maxColor.green += contrast, 0., 1.);
        maxColor.blue = Tools::clip(maxColor.blue += contrast, 0., 1.);
        if(!preserveAlpha)
            maxColor.alpha = Tools::clip(maxColor.alpha += contrast, 0., 1.);
        return maxColor;
    }
    
    static double cicmAbscissaToMaxAbscissa(double aCicmAbscissa, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        return aMaxRect->width / 2. + aZoomfactor * aCicmAbscissa * aMaxRect->width / 2.;
    }
    
    static double cicmAbscissaToMaxOrdinate(double aCicmOrdinate, t_rect* aMaxRect, double aZoomfactor = 1.)
    {
        return aMaxRect->height / 2. + aZoomfactor * aCicmOrdinate * aMaxRect->height / -2.;
    }
    
};

#endif /* defined(DEF_MAX_CONVERTER) */