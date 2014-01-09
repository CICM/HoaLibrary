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

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_map
{
    t_edspobj           f_ob;
    AmbisonicsMultiMaps *f_ambi_map;
    bool				f_mode_bool;
} t_hoa_map;

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv);
void hoa_map_free(t_hoa_map *x);
void hoa_map_list(t_hoa_map *x, t_symbol *s, long argc, t_atom *argv);

void hoa_map_dsp(t_hoa_map *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_map_perform(t_hoa_map *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_map_perform_onesource(t_hoa_map *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_map_class;

extern "C" void setup_hoa0x2emap_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.map~", (method)hoa_map_new, (method)hoa_map_free, (short)sizeof(t_hoa_map), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    
	eclass_addmethod(c, (method)hoa_map_dsp,     "dsp",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_map_list,    "list",     A_GIMME, 0);
    
    CLASS_ATTR_LONG             (c, "mode", 0, t_hoa_map, f_mode_bool);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Coordinate mode");
	CLASS_ATTR_FILTER_CLIP      (c, "mode", 0, 1);
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "0");
    
    eclass_register(CLASS_BOX, c);
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
    hoa_map_class = c;
}

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_map *x = NULL;
    t_binbuf *d;
	int	order = 4;
    int numberOfSources = 2;
    
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoa_map *)eobj_new(hoa_map_class);
    
    order = atom_getint(argv);
    numberOfSources = atom_getint(argv+1);
    x->f_ambi_map = new AmbisonicsMultiMaps(order, numberOfSources, 4100, sys_getblksize());
    x->f_ambi_map->setRamp(4100);
    eobj_dspsetup(x, x->f_ambi_map->getNumberOfInputs(), x->f_ambi_map->getNumberOfOutputs());
    
	x->f_ob.d_misc = E_NO_INPLACE;
    
    ebox_attrprocess_viabinbuf(x, d);
    
	return (x);
}

void hoa_map_dsp(t_hoa_map *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_map->setVectorSize(maxvectorsize);
    if (x->f_ambi_map->getNumberOfSources() == 1)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_map_perform_onesource, 0, NULL);
    else
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_map_perform, 0, NULL);
}

void hoa_map_perform(t_hoa_map *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_map->process(ins, outs);
}

void hoa_map_perform_onesource(t_hoa_map *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    if(x->f_mode_bool)
        x->f_ambi_map->processCartesian(ins[0], outs, ins[1], ins[2]);
    else
        x->f_ambi_map->processPolar(ins[0], outs, ins[1], ins[2]);
}

void hoa_map_list(t_hoa_map *x, t_symbol *s, long argc, t_atom *argv)
{
    if(atom_getsymbol(argv+1) == gensym("car") || atom_getsymbol(argv+1) == gensym("cartesian"))
        x->f_ambi_map->setCoordinatesCartesian(atom_getint(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if(atom_getsymbol(argv+1) == gensym("pol") || atom_getsymbol(argv+1) == gensym("polar"))
        x->f_ambi_map->setCoordinatesPolar(atom_getint(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if (atom_getsymbol(argv+1) == gensym("mute"))
        x->f_ambi_map->setMuted(atom_getint(argv), atom_getint(argv+2));
}

void hoa_map_free(t_hoa_map *x)
{
	eobj_dspfree(x);
	delete(x->f_ambi_map);
}
