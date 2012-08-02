/*
 * Copyright (C) 2012 Pierre Guillot & Julien Colafransceco, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "hoa.readPatcher.h"

void plug_read(t_object *x, t_symbol *s, t_dictionary *d) 
{
	long filetype = 'JSON';
	long outtype; 
	char filename[512]; 
	short path;
	
	strcpy(filename, s->s_name);
	if(locatefile_extended(filename, &path, &outtype, &filetype, 1)) 
	{
		object_error((t_object *)x, "%s: not found", s->s_name); 
		return;
	}
	
	dictionary_read(filename, path, &d);
}


