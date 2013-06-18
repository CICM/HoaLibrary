/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicVirtualMicUI.h"

AmbisonicVirtualMicUI::AmbisonicVirtualMicUI()
{
    m_angleInRadian = 0;
    m_fisheyeEndAngleInRadian = m_fisheyeStartAngleInRadian = m_angleInRadian;
    m_widerValue = 1;
    m_distance = 1;
    m_isSelected = false;
    m_order = 7;
    
    m_encoder           = new AmbisonicsEncoder(m_order);
	m_viewer			= new AmbisonicsViewer(m_order, -CICM_PI2);
    //m_optim				= new AmbisonicsOptim(m_order);
	m_wider				= new AmbisonicsWider(m_order);
	m_harmonicsValues	= new double[m_order * 2 + 1];
    
    compute();
}
AmbisonicVirtualMicUI::~AmbisonicVirtualMicUI()
{
    free (m_harmonicsValues);
	delete m_encoder;
	delete m_viewer;
	//delete m_optim;
	delete m_wider;
}


void AmbisonicVirtualMicUI::compute()
{
    m_encoder->process(1., m_harmonicsValues, m_angleInRadian - CICM_PI2);
    m_wider->process(m_harmonicsValues, Tools::clip(m_widerValue, double(0.0000001), double(1)));
    //m_optim->process(m_harmonicsValues);
    m_viewer->processBigLob(m_harmonicsValues);
}

void AmbisonicVirtualMicUI::setOrder(long _order)
{
    if (m_order == Tools::clip_min(_order, long(1)) ) return;
    
    free (m_harmonicsValues);
	delete m_encoder;
	delete m_viewer;
	//delete m_optim;
	delete m_wider;
    
    m_order = Tools::clip_min(_order, long(1));
    m_encoder           = new AmbisonicsEncoder(m_order);
	m_viewer			= new AmbisonicsViewer(m_order, -CICM_PI2);
    //m_optim				= new AmbisonicsOptim(m_order);
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

void AmbisonicVirtualMicUI::setFisheyeEndAngle()
{
    m_fisheyeEndAngleInRadian = m_angleInRadian;
}

void AmbisonicVirtualMicUI::setFisheyeEndAngle(double _radian)
{
    m_fisheyeEndAngleInRadian = Tools::wrap(_radian, 0, CICM_2PI);
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