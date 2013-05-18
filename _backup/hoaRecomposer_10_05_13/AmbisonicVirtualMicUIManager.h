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

#ifndef __hoa_recomposer__AmbisonicVirtualMicUIManager__
#define __hoa_recomposer__AmbisonicVirtualMicUIManager__

#include "CicmProjectHeader.h"
#include "AmbisonicVirtualMicUI.h"

class AmbisonicVirtualMicUIManager
{
private:
    long m_numberOfMics;
    AmbisonicVirtualMicUI m_mic[MAX_MICS];
    double  m_fisheyeStep;
    double  m_fisheyeDestAngleInRadian;
    double* m_defaultAngles;
    double  m_distanceBetweenTwoDefMics;
    
    inline int safeIndex(const int _index) {return Tools::clip(_index, 0, MAX_MICS-1);}
    double radianInterp(double _step, double _startRad, double _endRad);
    void setDefaultAngles();
public:
    AmbisonicVirtualMicUIManager(long _numberOfMics = 0);
    ~AmbisonicVirtualMicUIManager();
    
    void setFisheyeDestAngle(double _angleInRadian);
    void resetAngles(const int _index);
    void setNumberOfMics(long _numberOfMics);
    void setAnglesInRadian(double* _radians, long _len);
    void setAnglesInDegree(double* _degrees, long _len);
    void setAngleInRadian(const int _index, double _radian);
    void setAngleInDegree(const int _index, double _degree);
    void setWiderValues(double* _widerValues, long _len);
    void setWiderValue(const int _index, double _widerValue);
    void setDistance(const int _index, double _distance);
    void setSelected(const int _index, int _selectedState);
    void selectMicsBetweenMics(int _micIndex1, int _micIndex2);
    void rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged, int magnet = 0);
    void setSelectedMicsWiderValueWithRadiusDelta(double _deltaRadius);
    void setFisheyeStartAngle(const int _micIndex); // take current angle
    void setFisheyeStartAngle(const int _micIndex, double _radian); // take an angle
    void setAngleCartesianCoordinate(const int _micIndex, double _abscissa, double _ordinate);
    void setSelectedMicsFisheyeStepWithDelta(const int _micIndex, double _delta); // _micIndex : -1 = all | -2 = selectedMics | >= 0 = micIndex
    void setFisheyeStepDirect(const int _micIndex, double _fisheyeStep); // _micIndex : -1 = all | -2 = selectedMics | >= 0 = micIndex
    void setAngleToClosestDefMicAngle(const int _micIndex);
    
    double        getClosestDefMicAngle(const int _micIndex);
    double        getClosestDefMicAngle(double _angleInRadian);
    double        getClosestDefMicDistance(const int _micIndex);
    double        getClosestDefMicDistance(double _angleInRadian);
    inline double getDistanceBetweenTwoDefMics() { return m_distanceBetweenTwoDefMics; }
    inline double getFisheyeDestAngle() { return m_fisheyeDestAngleInRadian; }
    inline long   getNumberOfMics(){ return m_numberOfMics; }
    inline double getFisheyeStep() { return m_fisheyeStep; }
    inline bool   isSelected(const int _micIndex) {return m_mic[safeIndex(_micIndex)].isSelected(); }
    inline double getDistance(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getDistance(); }
    inline double getAngleInRadian(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getAngleInRadian(); }
    inline double getAngleInDegree(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getAngleInDegree(); }
    inline double getWiderValue(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getWiderValue(); }
    inline double getFisheyeStartAngle(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getFisheyeStartAngle(); }
    inline double getAbscissa(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getAbscissa(); }
    inline double getOrdinate(const int _micIndex) {return m_mic[safeIndex(_micIndex)].getOrdinate(); }
    
    //viewer :
    inline double  getBiggestContribution(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestContribution(); }
	inline long    getBiggestContributionIndex(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestContributionIndex(); }
	inline double  getContributions(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getContributions(anIndex); }
	inline double  getAbscisseValue(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getAbscisseValue(anIndex); }
	inline double  getOrdinateValue(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getOrdinateValue(anIndex); }
	inline int     getColor(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getColor(anIndex); }
	inline double  getBiggestDistance(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestDistance(); }
	inline long    getBiggestDistanceIndex1(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestDistanceIndex1(); }
	inline long    getBiggestDistanceIndex2(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestDistanceIndex2(); }
    inline long    getBiggestLobeNbPoint(const int _micIndex) { return m_mic[safeIndex(_micIndex)].getBiggestLobeNbPoint(); }
    inline double  getBiggestLobe_x(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getBiggestLobe_x(anIndex); }
    inline double  getBiggestLobe_y(const int _micIndex, long anIndex) { return m_mic[safeIndex(_micIndex)].getBiggestLobe_y(anIndex); }
};

#endif /* defined(__hoa_recomposer__AmbisonicVirtualMicManager__) */
