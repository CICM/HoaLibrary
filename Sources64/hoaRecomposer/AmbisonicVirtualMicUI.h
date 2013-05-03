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

#ifndef __hoa_recomposer__AmbisonicVirtualMicUI__
#define __hoa_recomposer__AmbisonicVirtualMicUI__

#include "CicmProjectHeader.h"

class AmbisonicVirtualMicUI
{
private:
    double m_angleInRadian;
    double m_distance;
    bool m_isSelected;
    
public:
    AmbisonicVirtualMicUI();
    ~AmbisonicVirtualMicUI();
    
    void setAngleInRadian(double _radian);
    inline void setAngleInDegree(double _degree) {setAngleInRadian(Tools::degToRad(_degree));}
    inline void setDistance(double _distance) {m_distance = Tools::clip_min(_distance, 0.);}
    void setSelected(int _selectedState);
    void rotateAngleInRadian(double _deltaRadian);
    
    inline bool isSelected() {return m_isSelected;}
    inline double getDistance() {return m_distance;}
    inline double getAngleInRadian() {return m_angleInRadian;}
    inline double getAngleInDegree() {return Tools::radToDeg(m_angleInRadian);}
};

#endif /* defined(__hoa_recomposer__AmbisonicVirtualMicUI__) */
