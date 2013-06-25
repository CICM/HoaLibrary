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
 
#ifndef __hoa_recomposer__AmbisonicVirtualMicUI__
#define __hoa_recomposer__AmbisonicVirtualMicUI__

#define MAX_MICS 64
#define MIN_MICS 3
#define DEF_MICS 8

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
