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
 
#ifndef DEF_AMBISONICSVIRTUALMICUI
#define DEF_AMBISONICSVIRTUALMICUI

#include "../hoaEncoder/AmbisonicEncoder.h"
#include "../hoaAmbisonics/AmbisonicsViewer.h"
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
    AmbisonicsViewer*    m_viewer;
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
