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

t_eclass *hoa_binaural_alias;

void *hoa_binaural_new(t_symbol *s, int argc, t_atom *argv)
{
    int i;
    t_canvas* realcnv;
    t_canvas* newcnv;
    t_atom av[7];
    int order = 1;
    int pinna = 0;
    int block = 256;
    long    n_argc;
    t_atom* n_argv;
    t_gobj *y = NULL;
    t_gobj *binaural = NULL;
    t_gobj **inlets = NULL;
    t_gobj *outlets[2];
    int inc, inc2;
    
    outlets[0] = NULL;
    outlets[1] = NULL;
    
    if(argc && argv && atom_gettype(argv) == A_FLOAT)
        order = atom_getfloat(argv);
    if(order < 1)
        order  = 1;
    
    atoms_get_attribute(argc, argv, gensym("@pinna"), &n_argc, &n_argv);
    if(n_argc && n_argv)
    {
        if(atom_gettype(n_argv) == A_FLOAT && atom_getfloat(n_argv) != 0)
            pinna = 1;
        else if(atom_gettype(n_argv) == A_SYM && atom_getsym(n_argv) == gensym("large"))
            pinna = 1;
        free(n_argv);
        n_argc = 0;
    }
    
    atoms_get_attribute(argc, argv, gensym("@block"), &n_argc, &n_argv);
    if(n_argc && n_argv)
    {
        if(atom_gettype(n_argv) == A_FLOAT)
            block = atom_getfloat(n_argv);
        free(n_argv);
        n_argc = 0;
    }
    
    realcnv = canvas_getcurrent();
    newcnv = canvas_new(0, 0, 0, NULL);
    newcnv->gl_owner = realcnv;
    canvas_vis(newcnv, 0);
    
    inlets = new t_gobj*[order * 2 + 1];
    if(!inlets)
        return NULL;
    
    for(i = 0; i < order * 2 + 1; i++)
    {
        atom_setfloat(av, i * 50);
        atom_setfloat(av+1, 10);
        atom_setsym(av+2, gensym("inlet~"));
        pd_typedmess((t_pd *)newcnv, gensym("obj"), 3, av);
        inlets[i] = NULL;
    }
    
    atom_setfloat(av, 0);
    atom_setfloat(av+1, 100);
    atom_setsym(av+2, gensym("hoa.2d.decoder~"));
    atom_setfloat(av+3, order);
    atom_setsym(av+4, gensym("binaural"));
    atom_setsym(av+5, gensym("@pinna"));
    if(!pinna)
        atom_setsym(av+6, gensym("small"));
    else
        atom_setsym(av+6, gensym("large"));
    pd_typedmess((t_pd *)newcnv, gensym("obj"), 7, av);
    
    atom_setfloat(av, 400);
    atom_setfloat(av+1, 100);
    atom_setsym(av+2, gensym("block~"));
    atom_setfloat(av+3, block);
    pd_typedmess((t_pd *)newcnv, gensym("obj"), 4, av);
    
    atom_setfloat(av, 0);
    atom_setfloat(av+1, 200);
    atom_setsym(av+2, gensym("outlet~"));
    pd_typedmess((t_pd *)newcnv, gensym("obj"), 3, av);
    
    atom_setfloat(av, 100);
    atom_setfloat(av+1, 200);
    atom_setsym(av+2, gensym("outlet~"));
    pd_typedmess((t_pd *)newcnv, gensym("obj"), 3, av);
    
    vmess((t_pd *)newcnv, gensym("pop"), "i", 1);
    
    inc = inc2 = 0;
    for(y = newcnv->gl_list; y; y = y->g_next)
    {
        if(eobj_getclassname(y) == gensym("hoa.2d.decoder~"))
        {
            binaural = y;
        }
        else if (eobj_getclassname(y) == gensym("inlet"))
        {
            inlets[inc] = y;
            inc++;
        }
        else if (eobj_getclassname(y) == gensym("outlet"))
        {
            outlets[inc2] = y;
            inc2++;
        }
    }
    if(inc != order * 2 +1 && inc2 != 2 && binaural == NULL)
        return NULL;
    
    obj_connect((t_object *)binaural, 0, (t_object *)outlets[0], 0);
    obj_connect((t_object *)binaural, 1, (t_object *)outlets[1], 0);
    for(i = 0; i < order * 2 + 1; i++)
    {
        obj_connect((t_object *)inlets[i], 0, (t_object *)binaural, i);
    }
    
    canvas_vis(newcnv, 0);
    canvas_setcurrent(realcnv);
    
    delete [] inlets;
	return newcnv;
}

extern "C" void setup_hoa0x2esubcanvas(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.binaural~", (method)hoa_binaural_new, (method)NULL, (short)sizeof(0), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_binaural_new, gensym("hoa.2d.binaural~"), A_GIMME);
    
	eclass_init(c, 0);
    eclass_register(CLASS_BOX, c);
	hoa_binaural_alias = c;
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

    // Alias /:
    setup_hoa0x2esubcanvas();
    
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

