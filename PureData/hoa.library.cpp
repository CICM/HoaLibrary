/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PDCommon/HoaCommon.pd.h"
#include "PD2D/Hoa2D.pd.h"
#include "PD3D/Hoa3D.pd.h"

extern "C" void setup_hoa0x2elibrary(void)
{
    // HOA COMMON //
    setup_hoa0x2econnect();
    setup_hoa0x2edac_tilde();
    setup_hoa0x2ein();
    setup_hoa0x2ein_tilde();
    setup_hoa0x2eout();
    setup_hoa0x2eout_tilde();
    setup_hoa0x2epi();
    setup_hoa0x2epi_tilde();
    setup_hoa0x2eprocess_tilde();
    setup_hoa0x2ethisprocess_tilde();
	//setup_hoa0x2emap();

    // HOA 2D //
	setup_hoa0x2e2d0x2ebinaural();
    setup_hoa0x2e2d0x2edecoder_tilde();
    setup_hoa0x2e2d0x2eencoder_tilde();
    setup_hoa0x2e2d0x2emap_tilde();
    setup_hoa0x2e2d0x2emeter_tilde();
    setup_hoa0x2e2d0x2eoptim_tilde();
    setup_hoa0x2e2d0x2eprojector_tilde();
    setup_hoa0x2e2d0x2erecomposer_tilde();
    setup_hoa0x2e2d0x2erotate_tilde();
    setup_hoa0x2e2d0x2escope_tilde();
    setup_hoa0x2e2d0x2espace();
    setup_hoa0x2e2d0x2ewider_tilde();
    
    // HOA 3D //
	setup_hoa0x2e3d0x2ebinaural(); 
    setup_hoa0x2e3d0x2edecoder_tilde();
    setup_hoa0x2e3d0x2eencoder_tilde();
    setup_hoa0x2e3d0x2eoptim_tilde();
    setup_hoa0x2e3d0x2ewider_tilde();
    setup_hoa0x2e3d0x2emap_tilde();
	setup_hoa0x2e3d0x2emeter_tilde();
    setup_hoa0x2e3d0x2escope_tilde();  

    post("HOA Library by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
    post("© 2012 - 2014  CICM | Paris 8 University");
    post("Version Beta 2.0");

    pd_library_add_folder("HoaLibrary", "patchers");
    pd_library_add_folder("HoaLibrary", "clippings");
    pd_library_add_folder("HoaLibrary", "dependencies");
    pd_library_add_folder("HoaLibrary", "media");
    pd_library_add_folder("HoaLibrary", "misc");
}

