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

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"

void *dac_class;

void *dac_new(t_symbol *s, int argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.dac~", (method)dac_new, (method)NULL, (short)sizeof(0), 0L, A_GIMME, 0);
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	dac_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
}

void *dac_new(t_symbol *s, int argc, t_atom *argv)
{
	int i, j, count;
	t_object *x;
	t_atom channels[512];
	int min, max;
	count = 0;
    
    int symPrepend = 0;
    
    if (argc && atom_gettype(argv) == A_SYM)
    {
        char *dac_bus_name = atom_getsym(argv)->s_name;
        if (isalpha(dac_bus_name[0])) // only works if the first letter isn't a number
        {
            symPrepend = 1;
            atom_setsym(channels, atom_getsym(argv));
        }
    }
    
	for(i = 0; i < (argc-symPrepend); i++)
	{
		if(atom_gettype(argv+i+symPrepend) == A_SYM)
		{
			min = atoi(atom_getsym(argv+i+symPrepend)->s_name);
			if (min < 10)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+2);
			else if (min < 100)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+3);
			else if (min < 1000)
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+4);
			else
				max = atoi(atom_getsym(argv+i+symPrepend)->s_name+5);
			if (max > min) 
			{
				for(j = min; j <= max; j++)
				{
					atom_setlong(channels + symPrepend + count++, j);
				}
			}
			else 
			{
				for(j = min; j >= max; j--)
				{
					atom_setlong(channels + symPrepend + count++, j);
				}
			}

		}	
		else if(atom_gettype(argv + symPrepend + i) == A_LONG)
		{
            atom_setlong(channels + symPrepend + count++, atom_getlong(argv + symPrepend + i));
			//channels[count++] = argv[i];
		}
	}
	x = (t_object *)object_new_typed(CLASS_BOX, gensym("dac~"), count + symPrepend, channels);
	
	return x;
}	


