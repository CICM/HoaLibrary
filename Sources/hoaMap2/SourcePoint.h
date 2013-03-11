/**
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


#ifndef DEF_SOURCEPOINT_HEADER
#define DEF_SOURCEPOINT_HEADER

#include "cicmTools.h"

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

class SourcePoint
{
	
private:
	t_pt		m_pos; // position de la source en données cartesiennes (x,y).
	double		m_angle; // angle (en radian de -pi à pi) de la source par rapport au centre (head)
	double		m_degree; // angle (en degree de -180 à 180) de la source par rapport au centre (head)
	double		m_radius; // distance de la source par rapport au centre (head) en metres
	t_jrgba		m_color;
	t_jrgba		m_selectedColor; // essayer peut-etre k32RGBAPixelFormat
	int			m_selected;
	int			m_hasfocus;
	int			m_hasDescription;
	string		*m_description; // t_symbol
	
	double wrapi(double _value);
		
public:
	SourcePoint(double _x = 0, double _y = 0);
	//void moveTo(double _x, double _y);
	//void moveToPol(double _angle, double _degree);
	
	// setters :
	
	void set_pos(double _x, double _y);
	void set_pos(t_pt _car_coords);
	void set_x(double _x);
	void set_y(double _y);
	void set_polPos(double _angle, double _radius);
	void set_angle(double _angle);
	void set_radius(double _radius);
	void set_selected(int _selected);
	void set_focus(int _focus);
	void set_name(string *description);
	
	// getters :
	t_pt get_pos() {return m_pos;}
	double get_x() {return m_pos.x;}
	double get_y() {return m_pos.y;}
	double get_angle() {return m_angle;}
	double get_radius() {return m_radius;}
	int get_selected() {return m_selected;}
	int	get_focus() {return m_hasfocus;}
	
	~SourcePoint();
};

#endif