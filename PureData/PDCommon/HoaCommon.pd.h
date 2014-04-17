/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_COMMON_PD
#define DEF_HOA_COMMON_PD


#include "../hoa.pd.h"
#include "../../Sources/Hoa2D/Hoa2D.h"
#include "../../Sources/Hoa3D/Hoa3D.h"

using namespace Hoa2D;

extern "C" void setup_hoa0x2econnect(void);
extern "C" void setup_hoa0x2econverter_tilde(void);
extern "C" void setup_hoa0x2edac_tilde(void);
extern "C" void setup_hoa0x2ein(void);
extern "C" void setup_hoa0x2ein_tilde(void);
extern "C" void setup_hoa0x2eout(void);
extern "C" void setup_hoa0x2eout_tilde(void);
extern "C" void setup_hoa0x2epi(void);
extern "C" void setup_hoa0x2epi_tilde(void);
extern "C" void setup_hoa0x2eprocess_tilde(void);
extern "C" void setup_hoa0x2ethisprocess_tilde(void);

#endif
