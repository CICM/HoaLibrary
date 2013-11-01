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

#ifndef DEF_HOA_LIBRARY_PD
#define DEF_HOA_LIBRARY_PD

#ifdef _WIN32
#define MSW
#endif

#ifndef _WIN32
#define sprintf_s sprintf
#endif

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