/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "VirtualMicManager.h"

namespace Hoa2D
{
	VirtualMicManager::VirtualMicManager(long number_of_mics)
	{
		m_defaultAngles = NULL;
		setNumberOfMics(number_of_mics);
		resetAngles(-1);
	}
	VirtualMicManager::~VirtualMicManager()
	{
		m_mics.clear();
		if(m_defaultAngles)
			free(m_defaultAngles);
	}
	
	void VirtualMicManager::setNumberOfMics(long number_of_mics)
	{
		long order = 0;
		number_of_mics = clip_min(number_of_mics, 3);
		
		if (number_of_mics % 2 == 0)
			order = number_of_mics / 2 - 1;
		else
			order = number_of_mics / 2;
		
		if(m_mics.size() > number_of_mics)
		{
			while (m_mics.size() != number_of_mics)
				m_mics.pop_back();
		}
		else if(m_mics.size() < number_of_mics)
		{
			while (m_mics.size() != number_of_mics)
				m_mics.push_back(new VirtualMic());
		}
		
		for (int i = 0; i < m_mics.size(); i++)
		{
			m_mics[i]->setSelected(0);
		}
		
		setDefaultAngles();
	}
	
	void VirtualMicManager::setDefaultAngles()
	{
		if(m_defaultAngles)
			delete m_defaultAngles;
		
		m_defaultAngles = new double[m_mics.size()];
		
		for(int i = 0; i < m_mics.size(); i++)
			m_defaultAngles[i] = HOA_2PI / (double)m_mics.size() * (double)i;
	}
	
	void VirtualMicManager::resetAngles(const int index)
	{
		if(index == -1)
		{
			for(int i = 0; i < m_mics.size(); i++)
				m_mics[i]->setAngleInRadian(m_defaultAngles[i]);
		}
		else if(isInside(long(index), long(0), long(m_mics.size())))
			m_mics[index]->setAngleInRadian(m_defaultAngles[index]);
	}
	
	void VirtualMicManager::resetWides(const int index)
	{
		if(index == -1) // tous les angles
		{
			for (int i = 0; i < m_mics.size(); i++)
				m_mics[i]->setWiderValue(1);
		}
		else if(isInside(long(index), long(0), long(m_mics.size())))
			m_mics[index]->setWiderValue(1);
	}
	
	void VirtualMicManager::setAnglesInRadian(double* angles, long size)
	{
		for(int i = 0; i < size && i < m_mics.size(); i++)
			m_mics[i]->setAngleInRadian(angles[i]);
	}
	
	void VirtualMicManager::setAnglesInDegree(double* angles, long size)
	{
		for(int i = 0; i < size && i < m_mics.size(); i++)
			m_mics[i]->setAngleInDegree(angles[i]);
	}
	
	void VirtualMicManager::setAngleInRadian(const int index, double angle)
	{
		if(index == -1)
		{
			for(int i = 0; i< m_mics.size(); i++)
				m_mics[i]->setAngleInRadian(angle);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setAngleInRadian(angle);
	}
	
	void VirtualMicManager::setAngleInDegree(const int index, double angle)
	{
		if (index == -1)
		{
			for(int i = 0; i<m_mics.size(); i++)
				m_mics[i]->setAngleInDegree(angle);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setAngleInDegree(angle);
	}
	
	void VirtualMicManager::setDistance(const int index, double _distance)
	{
		if(index == -1)
		{
			for(int i = 0; i<m_mics.size(); i++)
				m_mics[i]->setDistance(_distance);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setDistance(_distance);
	}
	
	void VirtualMicManager::setWiderValues(double* widerValues, long size)
	{
		for (int i=0; i < size && i < m_mics.size(); i++)
			m_mics[i]->setWiderValue(widerValues[i]);
	}
	
	void VirtualMicManager::setWiderValue(const int index, double widerValue)
	{
		if (index == -1)
		{
			for (int i=0; i < m_mics.size(); i++)
				m_mics[i]->setWiderValue(widerValue);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setWiderValue(widerValue);
	}
	
	void VirtualMicManager::setSelected(const int index, int _selectedState)
	{
		if (index == -1)
		{
			for (int i = 0; i < m_mics.size(); i++)
				m_mics[i]->setSelected(_selectedState);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setSelected(_selectedState);
	}
	
	void VirtualMicManager::selectMicsBetweenMics(int indexOne, int indexTwo)
	{
		double angle1 = getAzimuth(indexOne);
		double angle2 = getAzimuth(indexTwo);
		
		for (int i=0; i<m_mics.size(); i++)
			if (isInsideRad(getAzimuth(i), angle1, angle2))
				setSelected(i, 1);
	}
	
	void VirtualMicManager::rotateSelectedMicsWithRadian(double newRadian, int sourceBeingDragged, int magnet)
	{
		if (!isInside(sourceBeingDragged, int(0), int(m_mics.size())))
			return;
		
		double deltaAngle;
		double oldAngle = m_mics[sourceBeingDragged]->getAzimuth();
		deltaAngle = newRadian - m_mics[sourceBeingDragged]->getAzimuth();
		m_mics[sourceBeingDragged]->setAngleInRadian(newRadian);
		
		if (magnet == 1)
		{
			if ( getClosestDefMicDistance(sourceBeingDragged) < HOA_2PI / (double) m_mics.size() *0.1 )
			{
				m_mics[sourceBeingDragged]->setAngleInRadian(getClosestDefMicAngle(sourceBeingDragged));
				deltaAngle =  m_mics[sourceBeingDragged]->getAzimuth() - oldAngle;
			}
		}
		
		for (int i=0; i < m_mics.size(); i++)
		{
			if (isSelected(i) && i != sourceBeingDragged)
			{
				m_mics[i]->rotateAngleInRadian(deltaAngle);
			}
		}
	}
	
	void VirtualMicManager::setSelectedMicsWiderValueWithRadiusDelta(double deltaRadius)
	{
		for (int i=0; i < m_mics.size(); i++) {
			if (isSelected(i)) {
				m_mics[i]->setWiderValue( m_mics[i]->getWiderValue() + deltaRadius);
			}
		}
	}
	
	/* ---- Fisheye ---- */
	
	void VirtualMicManager::setFisheyeDestAngle(double angle_radian)
	{
		m_fisheyeDestAngleInRadian = wrap_twopi(angle_radian);
		m_fisheyeStep = 0;
	}
	
	void VirtualMicManager::setSelectedMicsFisheyeStepWithDelta(const int micIndex, double _delta)
	{
		m_fisheyeStep = clip_minmax(m_fisheyeStep + _delta, double(0), double(1));
		setFisheyeStepDirect(micIndex, m_fisheyeStep);
	}
	
	void VirtualMicManager::setFisheyeStepDirect(const int micIndex, double fisheyeStep)
	{
		int index = safeIndex(micIndex);
		m_fisheyeStep = clip_minmax(fisheyeStep, 0, 1);
		if (micIndex == -2)
		{
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mics[i]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
		}
		else if (micIndex == -1)
		{
			for (int i=0; i < m_mics.size(); i++)
				m_mics[i]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mics[i]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
		}
		else
			m_mics[index]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mics[index]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
	}
	
	void VirtualMicManager::setFisheyeStartAngle(const int micIndex)
	{
		if (micIndex == -2)
		{
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setFisheyeStartAngle();
		}
		else if (micIndex == -1)
		{
			for (int i=0; i<m_mics.size(); i++)
				m_mics[i]->setFisheyeStartAngle();
		}
		else
			m_mics[(int)clip_minmax(micIndex, 0, m_mics.size())]->setFisheyeStartAngle();
	}
	
	void VirtualMicManager::setFisheyeStartAngle(const int micIndex, double angle_radian)
	{
		if (micIndex == -2) {
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setFisheyeStartAngle(angle_radian);
		}
		else if (micIndex == -1)
			for (int i=0; i<m_mics.size(); i++)
				m_mics[i]->setFisheyeStartAngle(angle_radian);
		else
			m_mics[(int)clip_minmax(micIndex, 0, m_mics.size())]->setFisheyeStartAngle(angle_radian);
	}
	
	void VirtualMicManager::setAngleCartesianCoordinate(const int micIndex, double abscissa, double ordinate)
	{
		if (micIndex == -1)
			for (int i=0; i<m_mics.size(); i++)
				m_mics[i]->setAngleCartesianCoordinate(abscissa, ordinate);
		else
			m_mics[(int)clip_minmax(micIndex, 0, m_mics.size())]->setAngleCartesianCoordinate(abscissa, ordinate);
	}
	
	
	/* --- Utility --- */
	
	double VirtualMicManager::radianInterp(double step, double startRad, double endRad)
	{
		double start = wrap_twopi(startRad);
		double end   = wrap_twopi(endRad);
		
		// anti-clockwise
		
		if ( wrap_twopi(end - start) <= HOA_PI )
		{
			if (end - start >= 0)
				return wrap_twopi( start + step*(end - start) );
			else
				return wrap_twopi( start + step*( (end + HOA_2PI) - start) );
		}
		
		// clockwise
		
		else
		{
			if (end - start <= 0)
				return wrap_twopi( start + step*(end - start) );
			else
				return wrap_twopi( start - step*( (start + HOA_2PI) - end) );
		}
	}
	
	double VirtualMicManager::getClosestDefMicAngle(const int micIndex)
	{
		return getClosestDefMicAngle(getAzimuth(micIndex));
	}
	
	double VirtualMicManager::getClosestDefMicAngle(double angle_radian)
	{
		double angle = wrap_twopi(angle_radian);
		double distance = HOA_2PI;
		double tempDistance, closestAngle;
		closestAngle = angle;
		
		for (int i = 0; i < m_mics.size(); i++)
		{
			tempDistance = radianClosestDistance(angle, m_defaultAngles[i]);
			if (tempDistance < distance) {
				distance = tempDistance;
				closestAngle = m_defaultAngles[i];
			}
		}
		
		return closestAngle;
	}
	
	double VirtualMicManager::getClosestDefMicDistance(const int micIndex)
	{
		return getClosestDefMicDistance(getAzimuth(micIndex));
	}
	
	double VirtualMicManager::getClosestDefMicDistance(double angle_radian)
	{
		double angle = wrap_twopi(angle_radian);
		double distance = HOA_2PI;
		
		for (int i = 0; i < m_mics.size(); i++)
			distance = min(distance, radianClosestDistance(angle, m_defaultAngles[i]));
		
		return distance;
	}
	
	void VirtualMicManager::setAngleToClosestDefMicAngle(const int micIndex)
	{
		if (!isInside(micIndex, int(0), int(m_mics.size()))) return;
		m_mics[micIndex]->setAngleInRadian(getClosestDefMicAngle(micIndex));
	}
	
	long VirtualMicManager::getNumberOfSelectedMics()
	{
		long numberOfSelectedMics = 0;
		for (int i = 0; i < m_mics.size(); i++)
			if (m_mics[i]->isSelected()) numberOfSelectedMics++;
		return numberOfSelectedMics;
	}
}
