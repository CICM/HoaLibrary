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
#include "../hoaEncoder/AmbisonicsEncoder.h"
#include "../hoaAmbisonics/AmbisonicsViewer.h"
#include "../hoaOptim/AmbisonicsOptim.h"
#include "../hoaWider/AmbisonicsWider.h"

class AmbisonicVirtualMicUI
{
private:
    double  m_widerValue;
    double  m_angleInRadian;
    double  m_distance;
    bool    m_isSelected;
    double  m_fisheyeStartAngleInRadian;
    double  m_fisheyeEndAngleInRadian;
    
    int                  m_order;
    AmbisonicsEncoder*   m_encoder;
	//AmbisonicsOptim*     m_optim;
	AmbisonicsWider*     m_wider;
    AmbisonicsViewer*    m_viewer;
    double*              m_harmonicsValues;
    
public:
    AmbisonicVirtualMicUI();
    ~AmbisonicVirtualMicUI();
    
    void setOrder(long _order);
    void setAngleInRadian(double _radian);
    inline void setAngleInDegree(double _degree) {setAngleInRadian(Tools::degToRad(_degree));}
    inline void setDistance(double _distance) {m_distance = Tools::clip_min(_distance, 0.);}
    void setWiderValue(double _widerValue);
    void setSelected(int _selectedState);
    void rotateAngleInRadian(double _deltaRadian);
    void setFisheyeStartAngle(); // take current angle
    void setFisheyeStartAngle(double _radian); // take a specified angle
    void setFisheyeEndAngle(); // take current angle
    void setFisheyeEndAngle(double _radian); // take a specified angle
    void setAngleCartesianCoordinate(double _abscissa, double _ordinate);
    
    void compute();
    
    inline bool   isSelected() {return m_isSelected;}
    inline double getDistance() {return m_distance;}
    inline double getAngleInRadian() {return m_angleInRadian;}
    inline double getAngleInDegree() {return Tools::radToDeg(m_angleInRadian);}
    inline double getWiderValue() {return m_widerValue;}
    inline double getFisheyeStartAngle() { return m_fisheyeStartAngleInRadian; }
    inline double getAbscissa() {return Tools::abscisse(m_distance, m_angleInRadian);}
    inline double getOrdinate() {return Tools::ordinate(m_distance, m_angleInRadian);}
    
    //viewer :
    inline double  getBiggestContribution() { return m_viewer->getBiggestContribution(); }
	inline long    getBiggestContributionIndex() { return m_viewer->getBiggestContributionIndex(); }
	inline double  getContributions(long anIndex) { return m_viewer->getContributions(anIndex); }
	inline double  getAbscisseValue(long anIndex) { return m_viewer->getAbscisseValue(anIndex); }
	inline double  getOrdinateValue(long anIndex) { return m_viewer->getOrdinateValue(anIndex); }
	inline int     getColor(long anIndex) { return m_viewer->getColor(anIndex); }
	inline double  getBiggestDistance() {return m_viewer->getBiggestDistance(); }
	inline long    getBiggestDistanceIndex1() { return m_viewer->getBiggestDistanceIndex1(); }
	inline long    getBiggestDistanceIndex2() { return m_viewer->getBiggestDistanceIndex2(); }
    inline long    getBiggestLobeNbPoint() { return m_viewer->getBiggestLobeNbPoint(); }
    inline double  getBiggestLobe_x(long anIndex) { return m_viewer->getBiggestLobe_x(anIndex); }
    inline double  getBiggestLobe_y(long anIndex) { return m_viewer->getBiggestLobe_y(anIndex); }
};

#endif /* defined(__hoa_recomposer__AmbisonicVirtualMicUI__) */
