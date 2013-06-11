/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef DEF_HOAHEADER
#define DEF_HOAHEADER

// Private Variables / Functions / Etc.
void hoa_postcredits();

// Initialize Hoa
void hoa_init(void)
{
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void hoa_postcredits(){
	post("hoa.library (version 1.3) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
	post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
}

#endif