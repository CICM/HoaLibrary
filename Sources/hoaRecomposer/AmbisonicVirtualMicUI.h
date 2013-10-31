/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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
 
#ifndef DEF_AMBISONICSVIRTUALMICUI
#define DEF_AMBISONICSVIRTUALMICUI

#include "../hoaEncoder/AmbisonicEncoder.h"
#include "../hoaAmbisonics/AmbisonicViewer.h"
#include "../hoaOptim/AmbisonicOptim.h"
#include "../hoaWider/AmbisonicWider.h"

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
    AmbisonicEncoder*   m_encoder;
	AmbisonicWider*     m_wider;
    AmbisonicViewer*    m_viewer;
    double*              m_harmonicsValues;
    
public:
    AmbisonicVirtualMicUI();
    ~AmbisonicVirtualMicUI();
    
    void setOrder(long _order);
    void setAngleInRadian(double anAngleInRadian);
    void setAngleInDegree(double anAngleInDegree);
    void setDistance(double _distance) {m_distance = Tools::clip_min(_distance, 0.);}
    void setWiderValue(double _widerValue);
    void setSelected(int _selectedState);
    void rotateAngleInRadian(double _deltaRadian);
    void setFisheyeStartAngle();
    void setFisheyeStartAngle(double _radian);
    void setFisheyeEndAngle();
    void setFisheyeEndAngle(double _radian);
    void setAngleCartesianCoordinate(double _abscissa, double _ordinate);
    
    void compute();
    
     bool   isSelected() {return m_isSelected;}
     double getDistance() {return m_distance;}
     double getAngleInRadian() {return m_angleInRadian;}
     double getAngleInDegree() {return Tools::radToDeg(m_angleInRadian);}
     double getWiderValue() {return m_widerValue;}
     double getFisheyeStartAngle() { return m_fisheyeStartAngleInRadian; }
     double getAbscissa() {return Tools::abscissa(m_distance, m_angleInRadian);}
     double getOrdinate() {return Tools::ordinate(m_distance, m_angleInRadian);}
    
    //viewer :
    double  getBiggestContribution() { return m_viewer->getBiggestContribution(); }
    long    getBiggestContributionIndex() { return m_viewer->getBiggestContributionIndex(); }
    double  getContributions(long anIndex) { return m_viewer->getContributions(anIndex); }
    double  getAbscisseValue(long anIndex) { return m_viewer->getAbscisseValue(anIndex); }
    double  getOrdinateValue(long anIndex) { return m_viewer->getOrdinateValue(anIndex); }
    int     getColor(long anIndex) { return m_viewer->getColor(anIndex); }
    double  getBiggestDistance() {return m_viewer->getBiggestDistance(); }
    long    getBiggestDistanceIndex1() { return m_viewer->getBiggestDistanceIndex1(); }
    long    getBiggestDistanceIndex2() { return m_viewer->getBiggestDistanceIndex2(); }
    long    getBiggestLobeNbPoint() { return m_viewer->getBiggestLobeNbPoint(); }
    double  getBiggestLobe_x(long anIndex) { return m_viewer->getBiggestLobe_x(anIndex); }
    double  getBiggestLobe_y(long anIndex) { return m_viewer->getBiggestLobe_y(anIndex); }
};

#endif
