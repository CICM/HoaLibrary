/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PDCommon/HoaCommon.pd.h"
#include "PD2D/Hoa2D.pd.h"

extern "C"
{
    typedef struct _namelist    /* element in a linked list of stored strings */
    {
        struct _namelist *nl_next;  /* next in list */
        char *nl_string;            /* the string */
    } t_namelist;
    
    extern t_namelist *sys_externlist;
    extern t_namelist *sys_searchpath;
    extern t_namelist *sys_staticpath;
    extern t_namelist *sys_helppath;
    extern t_namelist *namelist_append_files(t_namelist *listwas, const char *s);
}

extern "C" void setup_hoa0x2elibrary(void)
{
    char path[MAXPDSTRING];
    t_namelist* var;
    
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
    
    // HOA 2D //
    setup_hoa0x2e2d0x2edecoder_tilde();
    setup_hoa0x2e2d0x2eencoder_tilde();;
    setup_hoa0x2e2d0x2emap();
    setup_hoa0x2e2d0x2emap_tilde();
    setup_hoa0x2e2d0x2emeter_tilde();
    setup_hoa0x2e2d0x2eoptim_tilde();
    setup_hoa0x2e2d0x2eprojector_tilde();
    setup_hoa0x2e2d0x2erecomposer_tilde();
    setup_hoa0x2e2d0x2erotate_tilde();
    setup_hoa0x2e2d0x2escope_tilde();
    setup_hoa0x2e2d0x2espace();
    setup_hoa0x2e2d0x2ewider_tilde();

    var = sys_searchpath;
    while (var)
    {
        sprintf(path, "%s/HoaLibrary",var->nl_string);
        if(strncmp(var->nl_string, "HoaLibrary", 10) == 0)
        {
            sprintf(path, "%s/patchers", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/clippings", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/dependencies", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/media", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/misc", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            return;
        }
        else if(access(path, O_RDONLY) != -1)
        {
            sprintf(path, "%s/HoaLibrary/patchers", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/HoaLibrary/clippings", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/HoaLibrary/dependencies", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/HoaLibrary/media", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            sprintf(path, "%s/HoaLibrary/misc", var->nl_string);
            namelist_append_files(sys_searchpath, path);
            return;
        }
        var = var->nl_next;
    }
}

