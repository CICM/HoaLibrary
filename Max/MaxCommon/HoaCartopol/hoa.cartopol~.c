/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"

#include "../hoa.max.h"

typedef struct _hoa_cartopol
{
	t_pxobject			f_ob;
	double				f_offset;
} t_hoa_cartopol;

t_class *hoa_cartopol_class;

void *hoa_cartopol_new(t_symbol *s, int ac, t_atom *av);
void hoa_cartopol_free(t_hoa_cartopol *x);
void hoa_cartopol_assist(t_hoa_cartopol *x, void *b, long m, long a, char *s);
void hoa_cartopol_dsp64(t_hoa_cartopol *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_cartopol_perform64(t_hoa_cartopol *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_cartopol_int(t_hoa_cartopol *x, long l);
void hoa_cartopol_float(t_hoa_cartopol *x, double f);
void hoa_cartopol_list(t_hoa_cartopol *x, t_symbol *s, long argc, t_atom *argv);
void hoa_cartopol_anything(t_hoa_cartopol *x, t_symbol *s, long ac, t_atom *av);

t_max_err hoa_cartopol_setattr_offset(t_hoa_cartopol *x, void *attr, long ac, t_atom *av);

t_hoa_err hoa_getinfos(t_hoa_cartopol* x, t_hoa_boxinfos* boxinfos);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.cartopol~", (method)hoa_cartopol_new, (method)hoa_cartopol_free, (short)sizeof(t_hoa_cartopol), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_cartopol_dsp64,		"dsp64",		A_CANT,  0);
	class_addmethod(c, (method)hoa_cartopol_assist,		"assist",		A_CANT,	 0);
	class_addmethod(c, (method)hoa_cartopol_int,		"int",			A_LONG,  0);
	class_addmethod(c, (method)hoa_cartopol_float,		"float",		A_FLOAT, 0);
	class_addmethod(c, (method)hoa_cartopol_list,		"list",			A_GIMME, 0);
	
	CLASS_ATTR_DOUBLE	(c, "offset", 0, t_hoa_cartopol, f_offset);
	CLASS_ATTR_ACCESSORS(c, "offset", NULL, hoa_cartopol_setattr_offset);
	CLASS_ATTR_SAVE		(c, "offset", 1);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_cartopol_class = c;
	return 0;
}

void *hoa_cartopol_new(t_symbol *s, int ac, t_atom *av)
{
	t_hoa_cartopol *x = (t_hoa_cartopol *)object_alloc(hoa_cartopol_class);

	if (x)
	{
		x->f_offset = CICM_PI2;
		dsp_setup((t_pxobject *)x, 3);
		for (int i = 0; i < 3; i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		
		attr_args_process(x, ac, av);
	}
	
	return x;
}

void hoa_cartopol_free(t_hoa_cartopol *x)
{
	dsp_free((t_pxobject *)x);
}

t_hoa_err hoa_getinfos(t_hoa_cartopol* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

t_max_err hoa_cartopol_setattr_offset(t_hoa_cartopol *x, void *attr, long ac, t_atom *av)
{
	if (ac && av)
	{
		if (atom_gettype(av) == A_FLOAT || atom_gettype(av) == A_LONG)
			x->f_offset = Hoa3D::wrap_twopi(atom_getfloat(av));
	}
	return MAX_ERR_NONE;
}

void hoa_cartopol_dsp64(t_hoa_cartopol *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoa_cartopol_perform64, 0, NULL);
}

void hoa_cartopol_perform64(t_hoa_cartopol *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
		// azimuth(x, y, z) = atan2(y, x) + CICM_PI2;
		outs[0][i] = atan2(ins[1][i], ins[0][i]) + x->f_offset;
		
		// radius(x, y, z) = sqrt(x*x + y*y + z*z);
		outs[2][i] = sqrt( ins[0][i]*ins[0][i] + ins[1][i]*ins[1][i] + ins[2][i]*ins[2][i] );
		
		// elevation(x, y, z) = acos(z / radius(x, y, z));
		outs[1][i] = acos(ins[2][i] / outs[2][i]);
    }
}

void hoa_cartopol_int(t_hoa_cartopol *x, long l)
{
	;
}

void hoa_cartopol_float(t_hoa_cartopol *x, double f)
{
	;
}

void hoa_cartopol_list(t_hoa_cartopol *x, t_symbol *s, long argc, t_atom *argv)
{
	;
}

void hoa_cartopol_assist(t_hoa_cartopol *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		switch (a)
		{
			case 0:
				sprintf(s,"(Signal/Float) X");
				break;
			case 1:
				sprintf(s,"(Signal/Float) Y");
				break;
			case 2:
				sprintf(s,"(Signal/Float) Z");
				break;
		}
	}
    else
	{
		switch (a)
		{
			case 0:
				sprintf(s,"(Signal) Azimuth value");
				break;
			case 1:
				sprintf(s,"(Signal) Elevation value");
				break;
			case 2:
				sprintf(s,"(Signal) Distance value");
				break;
		}
    }
}


