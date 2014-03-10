/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "VirtualMicManager.h"

namespace Hoa2D
{
	VirtualMicManager::VirtualMicManager(unsigned int number_of_mics)
	{
		m_defaultAngles = NULL;
		setNumberOfMics(number_of_mics);
		resetAzimuth(-1);
	}
	VirtualMicManager::~VirtualMicManager()
	{
		m_mics.clear();
		if(m_defaultAngles)
			free(m_defaultAngles);
	}
	
	void VirtualMicManager::setNumberOfMics(unsigned int number_of_mics)
	{
		number_of_mics = clip_min(number_of_mics, 3);
		
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
			m_mics[i]->setSelected(0);
		
		setDefaultAzimuth();
	}
	
	void VirtualMicManager::setDefaultAzimuth()
	{
		if(m_defaultAngles)
			delete m_defaultAngles;
		
		m_defaultAngles = new double[m_mics.size()];
		
		for(int i = 0; i < m_mics.size(); i++)
			m_defaultAngles[i] = HOA_2PI / (double)m_mics.size() * (double)i;
	}
	
	void VirtualMicManager::resetAzimuth(const int index)
	{
		if(index == -1)
		{
			for(int i = 0; i < m_mics.size(); i++)
				m_mics[i]->setAzimuth(m_defaultAngles[i]);
		}
		else if(isInside(long(index), long(0), long(m_mics.size())))
			m_mics[index]->setAzimuth(m_defaultAngles[index]);
	}
	
	void VirtualMicManager::resetDirectivity(const int index)
	{
		if(index == -1) // tous les angles
		{
			for (int i = 0; i < m_mics.size(); i++)
				m_mics[i]->setDirectivity(1);
		}
		else if(isInside(long(index), long(0), long(m_mics.size())))
			m_mics[index]->setDirectivity(1);
	}
	
	void VirtualMicManager::setAzimuthList(double* angles, long size)
	{
		for(int i = 0; i < size && i < m_mics.size(); i++)
			m_mics[i]->setAzimuth(angles[i]);
	}
	
	void VirtualMicManager::setAzimuth(const int index, double angle)
	{
		if(index == -1)
		{
			for(int i = 0; i< m_mics.size(); i++)
				m_mics[i]->setAzimuth(angle);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setAzimuth(angle);
	}
	
	void VirtualMicManager::setDirectivityList(double* directivities, long size)
	{
		for (int i=0; i < size && i < m_mics.size(); i++)
			m_mics[i]->setDirectivity(directivities[i]);
	}
	
	void VirtualMicManager::setDirectivity(const int index, double widerValue)
	{
		if (index == -1)
		{
			for (int i=0; i < m_mics.size(); i++)
				m_mics[i]->setDirectivity(widerValue);
		}
		else
			m_mics[(int)clip_minmax(index, 0, m_mics.size())]->setDirectivity(widerValue);
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
	
	void VirtualMicManager::rotateSelectedMics(double newRadian, int sourceBeingDragged, int magnet)
	{
		if (!isInside(sourceBeingDragged, int(0), int(m_mics.size())))
			return;
		
		double deltaAngle;
		double oldAngle = m_mics[sourceBeingDragged]->getAzimuth();
		deltaAngle = newRadian - m_mics[sourceBeingDragged]->getAzimuth();
		m_mics[sourceBeingDragged]->setAzimuth(newRadian);
		
		if (magnet == 1)
		{
			if ( getClosestDefMicDistance(sourceBeingDragged) < HOA_2PI / (double) m_mics.size() *0.1 )
			{
				m_mics[sourceBeingDragged]->setAzimuth(getClosestDefMicAzimuth(sourceBeingDragged));
				deltaAngle =  m_mics[sourceBeingDragged]->getAzimuth() - oldAngle;
			}
		}
		
		for (int i=0; i < m_mics.size(); i++)
		{
			if (isSelected(i) && i != sourceBeingDragged)
			{
				m_mics[i]->rotateAzimuth(deltaAngle);
			}
		}
	}
	
	/* ---- Fisheye ---- */
	
	void VirtualMicManager::setFisheyeDestAzimuth(double angle_radian)
	{
		m_fisheyeDestAzimuth = wrap_twopi(angle_radian);
		m_fisheyeStep = 0;
	}
	
	void VirtualMicManager::setFisheyeStepWithDelta(const int index, double delta)
	{
		m_fisheyeStep = clip_minmax(m_fisheyeStep + delta, 0, 1);
		setFisheyeStepDirect(index, m_fisheyeStep);
	}
	
	void VirtualMicManager::setFisheyeStepDirect(const int micIndex, double fisheyeStep)
	{
		int index = safeIndex(micIndex);
		m_fisheyeStep = clip_minmax(fisheyeStep, 0, 1);
		if (micIndex == -2)
		{
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setAzimuth(radianInterp(m_fisheyeStep, m_mics[i]->getFisheyeStartAzimuth(), m_fisheyeDestAzimuth));
		}
		else if (micIndex == -1)
		{
			for (int i=0; i < m_mics.size(); i++)
				m_mics[i]->setAzimuth(radianInterp(m_fisheyeStep, m_mics[i]->getFisheyeStartAzimuth(), m_fisheyeDestAzimuth));
		}
		else
			m_mics[index]->setAzimuth(radianInterp(m_fisheyeStep, m_mics[index]->getFisheyeStartAzimuth(), m_fisheyeDestAzimuth));
	}
	
	void VirtualMicManager::setFisheyeStartAzimuth(const int micIndex)
	{
		if (micIndex == -2)
		{
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setFisheyeStartAzimuth();
		}
		else if (micIndex == -1)
		{
			for (int i=0; i<m_mics.size(); i++)
				m_mics[i]->setFisheyeStartAzimuth();
		}
		else
			m_mics[(int)clip_minmax(micIndex, 0, m_mics.size())]->setFisheyeStartAzimuth();
	}
	
	void VirtualMicManager::setFisheyeStartAzimuth(const int micIndex, double angle_radian)
	{
		if (micIndex == -2) {
			for (int i=0; i < m_mics.size(); i++)
				if (isSelected(i))
					m_mics[i]->setFisheyeStartAzimuth(angle_radian);
		}
		else if (micIndex == -1)
			for (int i=0; i<m_mics.size(); i++)
				m_mics[i]->setFisheyeStartAzimuth(angle_radian);
		else
			m_mics[(int)clip_minmax(micIndex, 0, m_mics.size())]->setFisheyeStartAzimuth(angle_radian);
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
	
	double VirtualMicManager::getClosestDefMicAzimuth(const int micIndex)
	{
		return getClosestDefMicAzimuth(getAzimuth(micIndex));
	}
	
	double VirtualMicManager::getClosestDefMicAzimuth(double angle_radian)
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
	
	void VirtualMicManager::setAzimuthToClosestDefMicAzimuth(const int micIndex)
	{
		if (!isInside(micIndex, 0, m_mics.size())) return;
		m_mics[micIndex]->setAzimuth(getClosestDefMicAzimuth(micIndex));
	}
	
	long VirtualMicManager::getNumberOfSelectedMics()
	{
		long numberOfSelectedMics = 0;
		for (int i = 0; i < m_mics.size(); i++)
			if (m_mics[i]->isSelected()) numberOfSelectedMics++;
		return numberOfSelectedMics;
	}
}
