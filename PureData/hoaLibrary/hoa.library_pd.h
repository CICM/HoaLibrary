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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_HOA_LIBRARY_PD
#define DEF_HOA_LIBRARY_PD

extern "C"
{
#include "../../../PdEnhanced/Sources/pd_enhanced.h"
}
#include "../../Sources/HoaLibrary.h"

extern "C" void hoa_setup(void);

extern "C" void setup_hoa0x2edecoder_tilde(void);   // hoa.decoder~
extern "C" void setup_hoa0x2edelay_tilde(void);     // hoa.delay~
extern "C" void setup_hoa0x2eencoder_tilde(void);   // hoa.encoder~
extern "C" void setup_hoa0x2efreeverb_tilde(void);  // hoa.freeverb~
extern "C" void setup_hoa0x2egrain_tilde(void);     // hoa.grain~
extern "C" void setup_hoa0x2emap_tilde(void);       // hoa.map~
extern "C" void setup_hoa0x2emeter_tilde(void);     // hoa.meter~
extern "C" void setup_hoa0x2eprojector_tilde(void); // hoa.projector~
extern "C" void setup_hoa0x2erecomposer_tilde(void);// hoa.recomposer~
extern "C" void setup_hoa0x2epi(void);              // hoa.pi
extern "C" void setup_hoa0x2eringmod_tilde(void);   // hoa.ringmod~
extern "C" void setup_hoa0x2espace_tilde(void);     // hoa.space~
extern "C" void setup_hoa0x2ewider_tilde(void);     // hoa.wider~
extern "C" void setup_hoa0x2espace(void);           // hoa.space 
extern "C" void setup_hoa0x2emap(void);              // hoa.map
extern "C" void setup_hoa0x2erotate_tilde(void);    // hoa.rotate~
extern "C" void setup_hoa0x2escope_tilde(void);     // hoa.scope~
extern "C" void setup_hoa0x2eoptim_tilde(void);     // hoa.optim~

#endif