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

#include "SourceManager.h"

SourceManager::SourceManager()
{
	m_maxSources = 100;
	m_nbSources = 0;
}

int SourceManager::addSource(double _x, double _y)
{
	int sourceAccessIndex;
	if (m_nbSources < m_maxSources) 
	{
		SourcePoint* newpoint = new SourcePoint( _x , _y );
		m_sources.push_back(newpoint);
		sourceAccessIndex = get_smallest_free_accessIndex();
		m_accessIndex.push_back( sourceAccessIndex );
		m_nbSources++;
		return sourceAccessIndex;
	}
	return -1;
}

int SourceManager::addSource(int _sourceIndex, double _x, double _y)
{
	if (!source_exist(_sourceIndex) && m_nbSources < m_maxSources) {
		SourcePoint* newpoint = new SourcePoint( _x , _y );
		m_sources.push_back(newpoint);
		m_accessIndex.push_back( _sourceIndex );
		m_nbSources++;
		return _sourceIndex;
	}
	return -1;
}

int SourceManager::get_smallest_free_accessIndex()
{
	int smallest = 0;
	int counter = -1;
	if (m_nbSources > 0)
	{
		while (counter != 0) {
			counter = count(m_accessIndex.begin(), m_accessIndex.end(), smallest);
			if (counter != 0) smallest++;
			else return smallest;
		}
	}
	return 0;
}

int SourceManager::source_exist(int _sourceIndex)
{
	if ( count(m_accessIndex.begin(), m_accessIndex.end(), _sourceIndex) ) {
		return 1;
	}
	return 0;
}

int SourceManager::clear()
{
	if (m_nbSources > 0) {
		m_sources.clear();
		m_accessIndex.clear();
		m_nbSources = 0;
	}
	return 1;
}

int SourceManager::removeLastSource()
{
	if (m_nbSources > 0) {
		m_sources.pop_back();
		m_accessIndex.pop_back();
		m_nbSources--;
		return 1;
	}
	return 0;
}

int SourceManager::get_index(int _sourceIndex)
{
	if (_sourceIndex >= 0 && _sourceIndex < (int)m_nbSources) return m_accessIndex[_sourceIndex];
	return -1;
}
int SourceManager::sourceExist(int _sourceIndex)
{
	if (get_index(_sourceIndex) >= 0) return 1;
	else return 0;
}

//---
void SourceManager::set_pos(int _sourceIndex, double _x, double _y) 
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_pos(_x,_y);
	}
}
void SourceManager::set_pos(int _sourceIndex, t_pt _car_coords) 
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_pos(_car_coords);
	}
}

t_pt SourceManager::get_pos(int _sourceIndex) {
	t_pt point = {0,0};
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_pos();
	}
	return point;
}

//---
void SourceManager::set_x(int _sourceIndex, double _x)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_x(_x);
	}
}
double SourceManager::get_x(int _sourceIndex){
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_x();
	}
	return 0;
}

//---
void SourceManager::set_y(int _sourceIndex, double _y)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_y(_y);
	}
}
double SourceManager::get_y(int _sourceIndex)
{
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_y();
	}
	return 0;
}

//---
void SourceManager::set_polPos(int _sourceIndex, double _angle, double _radius)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_polPos(_angle, _radius);
	}
}
void SourceManager::set_angle(int _sourceIndex, double _angle)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_angle(_angle);
	}
}
double SourceManager::get_angle(int _sourceIndex)
{
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_angle();
	}
	return 0;
}
void SourceManager::set_radius(int _sourceIndex, double _radius)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_radius(_radius);
	}
}
double SourceManager::get_radius(int _sourceIndex) {
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_radius();
	}
	return 0;
}

//---
void SourceManager::set_selected(int _sourceIndex, int _selected)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_selected(_selected);
	}
}
int SourceManager::get_selected(int _sourceIndex) {
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_selected();
	}
	return 0;
}

//---
void SourceManager::set_focus(int _sourceIndex, int _focus)
{
	if (get_index(_sourceIndex) >= 0) {
		m_sources[get_index(_sourceIndex)]->set_focus(_focus);
	}
}
int	SourceManager::get_focus(int _sourceIndex) {
	if (get_index(_sourceIndex) >= 0) {
		return m_sources[get_index(_sourceIndex)]->get_focus();
	}
	return 0;
}

//-----------------------------
SourceManager::~SourceManager()
{
	/*
	uint i;
	for(i = 0; i < m_sources.size(); i++)
	{
		delete m_sources[i];
	}
	*/
	
	m_sources.clear();
	m_accessIndex.clear();
	
	//delete m_sources;
	
	//free(m_sources);
	//delete m_accessIndex;
	//free(m_description);
}