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

#include "AmbisonicVirtualMicUI.h"

AmbisonicVirtualMicUI::AmbisonicVirtualMicUI()
{
    m_angleInRadian = 0;
    m_fisheyeStartAngleInRadian = m_angleInRadian;
    m_widerValue = 1;
    m_distance = 1;
    m_isSelected = false;
    m_order = 7;
    
    m_encoder           = new AmbisonicsEncoder(m_order);
	m_viewer			= new AmbisonicsViewer(m_order, -CICM_PI2);
    m_optim				= new AmbisonicsOptim(m_order);
	m_wider				= new AmbisonicsWider(m_order);
	m_harmonicsValues	= new double[m_order * 2 + 1];
    
    compute();
}
AmbisonicVirtualMicUI::~AmbisonicVirtualMicUI()
{
    free (m_harmonicsValues);
	delete m_encoder;
	delete m_viewer;
	delete m_optim;
	delete m_wider;
}


void AmbisonicVirtualMicUI::compute()
{
    m_encoder->process(1., m_harmonicsValues, m_angleInRadian - CICM_PI2);
    m_wider->process(m_harmonicsValues, m_widerValue);
    m_optim->process(m_harmonicsValues);
    m_viewer->processBigLob(m_harmonicsValues);
}

void AmbisonicVirtualMicUI::setOrder(long _order)
{
    if (m_order == Tools::clip_min(_order, long(1)) ) return;
    
    free (m_harmonicsValues);
	delete m_encoder;
	delete m_viewer;
	delete m_optim;
	delete m_wider;
    
    m_order = Tools::clip_min(_order, long(1));
    m_encoder           = new AmbisonicsEncoder(m_order);
	m_viewer			= new AmbisonicsViewer(m_order, -CICM_PI2);
    m_optim				= new AmbisonicsOptim(m_order);
	m_wider				= new AmbisonicsWider(m_order);
	m_harmonicsValues	= new double[m_order * 2 + 1];
    
    compute();
}

void AmbisonicVirtualMicUI::setAngleInRadian(double _radian)
{
    m_angleInRadian = Tools::wrap(_radian, 0, CICM_2PI);
    compute();
}

void AmbisonicVirtualMicUI::rotateAngleInRadian(double _deltaRadian)
{
    m_angleInRadian = Tools::wrap(m_angleInRadian + _deltaRadian, 0, CICM_2PI);
    compute();
}

void AmbisonicVirtualMicUI::setAngleCartesianCoordinate(double _abscissa, double _ordinate)
{
    m_angleInRadian = Tools::angle(_abscissa, _ordinate);
    compute();
}

void AmbisonicVirtualMicUI::setWiderValue(double _widerValue)
{
    m_widerValue = Tools::clip(_widerValue, double(0), double(1));
    compute();
}

void AmbisonicVirtualMicUI::setFisheyeStartAngle()
{
    m_fisheyeStartAngleInRadian = m_angleInRadian;
}

void AmbisonicVirtualMicUI::setFisheyeStartAngle(double _radian)
{
    m_fisheyeStartAngleInRadian = Tools::wrap(_radian, 0, CICM_2PI);
}

void AmbisonicVirtualMicUI::setSelected(int _selectedState)
{
    if (_selectedState == -1) // toggle Mode
        m_isSelected = !m_isSelected;
    else if(_selectedState == 1)
        m_isSelected = true;
    else
        m_isSelected = false;
}