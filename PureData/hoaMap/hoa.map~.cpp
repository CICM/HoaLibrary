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

#include "hoa.map.h"

extern "C" void setup_hoa0x2emap_tilde(void)
{
    t_eclass* c;
    
    c = class_new("hoa.map~", (method)hoa_map_new, (method)hoa_map_free, (short)sizeof(t_hoa_map), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    
	class_addmethod(c, (method)hoa_map_dsp,     "dsp",      A_CANT, 0);
    class_addmethod(c, (method)hoa_map_list,    "list",     A_GIMME, 0);
    
    CLASS_ATTR_LONG             (c, "mode", 0, t_hoa_map, f_mode_bool);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Optim mode");
	CLASS_ATTR_FILTER_CLIP      (c, "mode", 0, 1);
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "0");
    
    class_register(CLASS_BOX, c);
    hoa_map_class = c;
}

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_map *x = NULL;
    t_dictionary *d;
	int	order = 4;
    int numberOfSources = 2;
    
    x = (t_hoa_map *)object_alloc(hoa_map_class);
    
    order = atom_getint(argv);
    numberOfSources = atom_getint(argv+1);
    x->f_ambi_map = new AmbisonicsMultiMaps(order, numberOfSources, 4100, sys_getblksize());
    x->f_ambi_map->setRamp(4100);
    dsp_setupjbox((t_jbox *)x, x->f_ambi_map->getNumberOfInputs(), x->f_ambi_map->getNumberOfOutputs());
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
    
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
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_map);
}
