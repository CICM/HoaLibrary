/*
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

#include "SourcePoint.h"

SourcePoint::SourcePoint(double _x, double _y)
{
	m_pos.x	= _x;
	m_pos.y	= _y;
	m_selected = m_hasfocus = m_hasDescription = 0;
}

// utilities functions :
//wraping function :
double SourcePoint::wrapi(double _value)
{
	if (_value>0)
        _value = fmod(_value + CICM_PI, 2.0*CICM_PI)-CICM_PI;
    else
        _value = fmod(_value - CICM_PI, 2.0*CICM_PI)+CICM_PI;
	return _value;
}

void SourcePoint::set_pos(double _x, double _y){
	m_pos.x	= _x;
	m_pos.y	= _y;
	m_angle = Tools::angle(m_pos.x, m_pos.y);
	m_radius = Tools::radius(m_pos.x, m_pos.y);
}

void SourcePoint::set_pos(t_pt _car_coords){
	m_pos.x	= _car_coords.x;
	m_pos.y	= _car_coords.y;
	m_angle = Tools::angle_inverse(m_pos.x, m_pos.y);
	m_radius = Tools::radius(m_pos.x, m_pos.y);
}

void SourcePoint::set_x(double _x){
	m_pos.x	= _x;
	m_angle = Tools::angle_inverse(m_pos.x, m_pos.y);
	m_radius = Tools::radius(m_pos.x, m_pos.y);
}
void SourcePoint::set_y(double _y){
	m_pos.y	= _y;
	m_angle = Tools::angle_inverse(m_pos.x, m_pos.y);
	m_radius = Tools::radius(m_pos.x, m_pos.y);
}
void SourcePoint::set_polPos(double _angle, double _radius){
	m_angle = wrapi(_angle);
	m_radius = fabs(_radius);
	m_pos.x = Tools::ordinate(m_radius, m_angle);
	m_pos.y = Tools::abscisse(m_radius, m_angle);
}
void SourcePoint::set_angle(double _angle){
	m_angle = wrapi(_angle);
	m_pos.x = Tools::ordinate(m_radius, m_angle);
	m_pos.y = Tools::abscisse(m_radius, m_angle);	
}
void SourcePoint::set_radius(double _radius){
	m_radius = fabs(_radius);
	m_pos.x = Tools::ordinate(m_radius, m_angle);
	m_pos.y = Tools::abscisse(m_radius, m_angle);
}
void SourcePoint::set_selected(int _selected){
	m_selected = _selected;
}
void SourcePoint::set_focus(int _focus){
	m_hasfocus = _focus;
}

void setName(string *description){
	
}

SourcePoint::~SourcePoint()
{
	free(m_description);
}