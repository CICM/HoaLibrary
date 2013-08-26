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

#define MAX_SPEAKER 256

#include "../MaxConverter.h"

typedef struct _HoaVector
{
	t_pxobject				f_ob;
	AmbisonicVector        *f_ambiVector;
    long                    f_argc;
    t_atom*                 f_argv;
    
    t_symbol*               f_vector_mode;
    t_atom_long             f_number_of_loudspeakers;
    double                  f_angles_of_loudspeakers[MAX_SPEAKER];
} t_HoaVector;

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv);
void HoaVector_free(t_HoaVector* x);
void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s);

t_max_err vector_set(t_HoaVector *x, t_object *attr, long ac, t_atom *av);
t_max_err loudspeakers_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);

void HoaVector_dsp64(t_HoaVector* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaVector_perform64_both(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaVector_perform64_vel(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaVector_perform64_ene(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaVector_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.vector~", (method)HoaVector_new, (method)HoaVector_free, (long)sizeof(t_HoaVector), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaVector_dsp64,     "dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaVector_assist,    "assist",	A_CANT, 0);
    
    CLASS_ATTR_SYM                  (c, "vector", 0, t_HoaVector, f_vector_mode);
    CLASS_ATTR_CATEGORY				(c, "vector", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "vector", 0, "Vectors");
    CLASS_ATTR_ENUM                 (c, "vector", 0, "both velocity energy")
	CLASS_ATTR_ACCESSORS            (c, "vector", NULL, vector_set);
    CLASS_ATTR_ORDER                (c, "vector", 0, "1");
	CLASS_ATTR_SAVE					(c, "vector", 1);
    
    CLASS_ATTR_LONG                 (c, "loudspeakers", 0, t_HoaVector, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER                (c, "loudspeakers", 0, "2");
    CLASS_ATTR_SAVE                 (c, "loudspeakers", 1);
    
    CLASS_ATTR_DOUBLE_VARSIZE       (c, "angles", 0, t_HoaVector, f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_CATEGORY             (c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER                (c, "angles", 0, "3");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaVector_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaVector* x = (t_HoaVector*)object_alloc(HoaVector_class);
    t_dictionary *d;

	if (x)
	{       
        x->f_vector_mode = gensym("both");
        x->f_number_of_loudspeakers = 4;
        
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = atom_getfloat(argv);
        
		x->f_ambiVector = new AmbisonicVector(x->f_number_of_loudspeakers, sys_getblksize());
        
		x->f_number_of_loudspeakers = x->f_ambiVector->getNumberOfLoudspeakers();
        for(int i = 0; i < x->f_number_of_loudspeakers; i++)
        {
            x->f_angles_of_loudspeakers[i] = x->f_ambiVector->getLoudspeakerAngle(i);
        }
    
		dsp_setup((t_pxobject *)x, x->f_ambiVector->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiVector->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");

		x->f_ob.z_misc = Z_NO_INPLACE;
        
        attr_args_process(x, argc, argv);
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        
        x->f_argc = argc;
        x->f_argv = new t_atom[x->f_argc];
        for(int i = 0; i < x->f_argc; i++)
            x->f_argv[i] = argv[i];        
	}
	return (x);
}

void HoaVector_dsp64(t_HoaVector* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiVector->setVectorSize(maxvectorsize);
    if(x->f_vector_mode == gensym("both"))
        object_method(dsp64, gensym("dsp_add64"), x, HoaVector_perform64_both, 0, NULL);
    else if(x->f_vector_mode == gensym("velocity"))
        object_method(dsp64, gensym("dsp_add64"), x, HoaVector_perform64_vel, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaVector_perform64_ene, 0, NULL);
}

void HoaVector_perform64_both(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiVector->process(ins, outs);
}

void HoaVector_perform64_vel(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiVector->processVelocity(ins, outs);
}

void HoaVector_perform64_ene(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiVector->processEnergy(ins, outs);
}

void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_ambiVector->getLoudspeakerName(a).c_str());
    else
        sprintf(s,"(Signal) %s", x->f_ambiVector->getVectorName(a).c_str());
}

void HoaVector_free(t_HoaVector* x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiVector;
    free(x->f_argv);
}

t_max_err vector_set(t_HoaVector *x, t_object *attr, long ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_LONG || atom_gettype(av) == A_FLOAT)
        {
            if(atom_getfloat(av) == 0)
                atom_setsym(av, gensym("both"));
            else if(atom_getfloat(av) == 1)
                atom_setsym(av, gensym("velocity"));
            else if(atom_getfloat(av) == 2)
                atom_setsym(av, gensym("energy"));
        }
        if(atom_gettype(av) == A_SYM && x->f_vector_mode != atom_getsym(av))
        {
            t_atom* state = CicmMax::dsp_stop((t_object *)x);
            
            if(atom_getsym(av) == gensym("both") || atom_getsym(av) == gensym("velocity") || atom_getsym(av) == gensym("energy"))
                x->f_vector_mode = atom_getsym(av);
            else
                x->f_vector_mode = gensym("both");
            if(x->f_vector_mode == gensym("both"))
                CicmMax::resize_outlet((t_object *)x, 4);
            else
                CicmMax::resize_outlet((t_object *)x, 2);
            
            for(int i = 0; i < x->f_argc; i++)
            {
                if(atom_gettype(x->f_argv+i) == A_SYM && x->f_argc > i && atom_getsym(x->f_argv+i) == gensym("@vector") && atom_gettype(x->f_argv+i+1) == A_SYM)
                {
                    atom_setsym(x->f_argv+i+1, x->f_vector_mode);
                }
            }
            CicmMax::rename_object((t_object *)x, x->f_argc, x->f_argv);
            CicmMax::dsp_start(state);
        }
    }
    return MAX_ERR_NONE;
}

t_max_err loudspeakers_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    t_atom* state = CicmMax::dsp_stop((t_object *)x);
    
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        x->f_ambiVector->setNumberOfLoudspeakers(atom_getfloat(argv));
    x->f_number_of_loudspeakers = x->f_ambiVector->getNumberOfLoudspeakers();
    
    CicmMax::resize_inlet((t_object *)x, x->f_ambiVector->getNumberOfInputs());
    
    if(atom_gettype(x->f_argv) == A_LONG)
        atom_setlong(x->f_argv, x->f_ambiVector->getNumberOfLoudspeakers());
    else if(atom_gettype(x->f_argv) == A_FLOAT)
        atom_setfloat(x->f_argv, (float)x->f_ambiVector->getNumberOfLoudspeakers());
    
    CicmMax::rename_object((t_object *)x, x->f_argc, x->f_argv);
    CicmMax::dsp_start(state);
    
    return MAX_ERR_NONE;
}

t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_LONG || atom_gettype(argv+i) == A_FLOAT)
                x->f_ambiVector->setLoudspeakerAngle(i, atom_getfloat(argv+i));
        }
    }
    
    for(int i = 0; i < x->f_number_of_loudspeakers; i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_ambiVector->getLoudspeakerAngle(i);
    }
    
    return MAX_ERR_NONE;
}




