/*
 * SourceManager.h
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



#ifndef DEF_SOURCEMANAGER_HEADER
#define DEF_SOURCEMANAGER_HEADER

#include "cicmTools.h"
#include "SourcePoint.h"
#include <vector>

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
}

class SourceManager
{
	
private:
	vector <SourcePoint*> m_sources;
	vector <int> m_accessIndex;
	unsigned m_maxSources;
	unsigned m_nbSources;
	
	int get_index(int _sourceIndex);
	
public:
	SourceManager();
	
	int addSource(double _x = 0, double _y = 0);
	int addSource(string* name, double _x = 0, double _y = 0);
	
	int get_smallest_free_accessIndex();
	int clear();
	int removeLastSource();
	
	// setters :
	void set_pos(int _sourceIndex, double _x, double _y);
	void set_pos(int _sourceIndex, t_pt _car_coords);
	void set_x(int _sourceIndex, double _x);
	void set_y(int _sourceIndex, double _y);
	void set_polPos(int _sourceIndex, double _angle, double _radius);
	void set_angle(int _sourceIndex, double _angle);
	void set_radius(int _sourceIndex, double _radius);
	void set_selected(int _sourceIndex, int _selected);
	void set_focus(int _sourceIndex, int _focus);
	void set_name(int _sourceIndex, string* description);
	
	// getters :
	
	unsigned get_number_of_sources() { return m_nbSources; }
	
	int sourceExist(int _sourceIndex);
	
	t_pt get_pos(int _sourceIndex);
	double get_x(int _sourceIndex);
	double get_y(int _sourceIndex);
	double get_angle(int _sourceIndex);
	double get_radius(int _sourceIndex);
	int get_selected(int _sourceIndex);
	int	get_focus(int _sourceIndex);
	
	~SourceManager();
};

#endif
