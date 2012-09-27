/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot, Eliott Paris Universite Paris 8
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

#include "ext.h"
#include "ext_obex.h"


int hoaWelcomePosted = 0;
void *HoaLoader_class;

int main(void)
{	
	t_class *c;
	c = class_new("hoa.loader", (method)NULL, (method)NULL, 0, 0L, NULL, 0);
	class_register(CLASS_NOBOX, c);	
	HoaLoader_class = c;
	
	if (hoaWelcomePosted == 0) {
		post("hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris",0);
		post("Copyright (C) 2012, CICM / Universite Paris 8");
		hoaWelcomePosted = 1;
	}
	return 0;
}