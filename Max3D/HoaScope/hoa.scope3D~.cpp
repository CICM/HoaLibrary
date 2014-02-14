/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../hoa.max.h"

typedef struct _hoa_scope 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Scope*           f_scope;
    int                     f_index;
    void*                   f_clock;
	int                     f_startclock;
    void*                   f_out;
} t_hoa_scope;

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);

void hoa_scope_tick(t_hoa_scope *x);

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_scope_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.scope3D~", (method)hoa_scope_new, (method)hoa_scope_free, (long)sizeof(t_hoa_scope), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_scope_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_assist,    "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_scope_class = c;
    hoa_credit();
    
	return 0;
}

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_scope *x = NULL;
	int	order = 1;
    x = (t_hoa_scope *)object_alloc(hoa_scope_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_scope = new Hoa3D::Scope(order, 15, 29);
		
		dsp_setup((t_pxobject *)x, x->f_scope->getNumberOfHarmonics());
        x->f_out = listout((t_object *)x);
        x->f_signals    =  new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_clock      = clock_new((void *)x, (method)hoa_scope_tick);
        x->f_startclock = 0;
        x->f_index = 0;
	}

	return (x);
}

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_index = 0;
    object_method(dsp64, gensym("dsp_add64"), x, hoa_scope_perform64, 0, NULL);
    x->f_startclock = 1;
}

void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
    }
    if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void hoa_scope_tick(t_hoa_scope *x)
{
    float value;
    float one, two;
    t_atom av[3];
    t_atom red[3];
    t_atom blue[3];
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, 500.);
    
    outlet_anything(x->f_out, gensym("reset"), 0, NULL);
    atom_setfloat(red, 1);
    atom_setfloat(red+1, 0);
    atom_setfloat(red+2, 0);
    atom_setfloat(blue, 0);
    atom_setfloat(blue+1, 0);
    atom_setfloat(blue+2, 1);

    for(int i = 0; i < x->f_scope->getNumberOfRows(); i++)
    {
        one  =   0;
        two = (double)i / (double)(x->f_scope->getNumberOfRows() - 1) * CICM_PI;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            outlet_anything(x->f_out, gensym("glcolor"), 3, blue);
            value= -value;
        }
        else
            outlet_anything(x->f_out, gensym("glcolor"), 3, red);
        
        atom_setfloat(av, value * sin(two) * cos(one));
        atom_setfloat(av+1, value * cos(two));
        atom_setfloat(av+2, value * sin(two) * sin(one));
        outlet_anything(x->f_out, gensym("moveto"), 3, av);
        for(int j = 1; j < x->f_scope->getNumberOfColumns(); j++)
        {
            one  =   (double)j / (double)x->f_scope->getNumberOfColumns() * CICM_2PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                outlet_anything(x->f_out, gensym("glcolor"), 3, blue);
                value= -value;
            }
            else
                outlet_anything(x->f_out, gensym("glcolor"), 3, red);
            atom_setfloat(av, value * sin(two) * cos(one));
            atom_setfloat(av+1, value * cos(two));
            atom_setfloat(av+2, value * sin(two) * sin(one));
            outlet_anything(x->f_out, gensym("lineto"), 3, av);
        }
        
        one  =   0;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            outlet_anything(x->f_out, gensym("glcolor"), 3, blue);
            value= -value;
        }
        else
            outlet_anything(x->f_out, gensym("glcolor"), 3, red);
        
        atom_setfloat(av, value * sin(two) * cos(one));
        atom_setfloat(av+1, value * cos(two));
        atom_setfloat(av+2, value * sin(two) * sin(one));
        outlet_anything(x->f_out, gensym("lineto"), 3, av);

    }
    
    for(int j = 0; j < x->f_scope->getNumberOfColumns(); j++)
    {
        one  =   (double)j / (double)x->f_scope->getNumberOfColumns() * CICM_2PI;
        two  = 0.;
        value = x->f_scope->getValue(0, j);
        if(value < 0)
        {
            outlet_anything(x->f_out, gensym("glcolor"), 3, blue);
            value= -value;
        }
        else
            outlet_anything(x->f_out, gensym("glcolor"), 3, red);
        atom_setfloat(av, value * sin(two) * cos(one));
        atom_setfloat(av+1, value * cos(two));
        atom_setfloat(av+2, value * sin(two) * sin(one));
        outlet_anything(x->f_out, gensym("moveto"), 3, av);
        for(int i = 1; i < x->f_scope->getNumberOfRows(); i++)
        {
            two = (double)i / (double)(x->f_scope->getNumberOfRows() - 1) * CICM_PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                outlet_anything(x->f_out, gensym("glcolor"), 3, blue);
                value= -value;
            }
            else
                outlet_anything(x->f_out, gensym("glcolor"), 3, red);
            atom_setfloat(av, value * sin(two) * cos(one));
            atom_setfloat(av+1, value * cos(two));
            atom_setfloat(av+2, value * sin(two) * sin(one));
            outlet_anything(x->f_out, gensym("lineto"), 3, av);
        }
    }
}

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

void hoa_scope_free(t_hoa_scope *x) 
{
    clock_free((t_object *)x->f_clock);
	dsp_free((t_pxobject *)x);
	delete x->f_scope;
    delete [] x->f_signals;
}

