/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "SourcesTrajectory.h"

namespace Hoa2D
{
	SourcesTrajectory::SourcesTrajectory()
	{
		m_recording = 0;
		m_limited = 0;
	}
	
	void SourcesTrajectory::setRecording(bool isRecording)
	{
		m_recording = isRecording;
	}
	
	void SourcesTrajectory::setLimited(bool isLimited)
	{
		m_limited = isLimited;
	}
	
	void SourcesTrajectory::recordSourceInTrajectory(SourcesManager* sourcesManager, long sourceIndex)
	{
		if(m_recording)
		{
			if(m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot())
			{
				if(m_last_slot_stored <= getMaximumIndexOfSlot() && getMaximumIndexOfSlot() > 0)
				{
					storeSourceAtNextSlot(sourcesManager, sourceIndex);
					recallSlot(sourcesManager, m_last_slot_stored);
				}
				else
					storeSourceAtNextSlot(sourcesManager, sourceIndex);
			}
		}
	}
	
	void SourcesTrajectory::recordGroupInTrajectory(SourcesManager* sourcesManager, long groupIndex)
	{
		if(m_recording && (m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot()))
		{
			if(m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot())
			{
				if(m_last_slot_stored <= getMaximumIndexOfSlot() && getMaximumIndexOfSlot() > 0)
				{
					storeGroupAtNextSlot(sourcesManager, groupIndex);
					recallSlot(sourcesManager, m_last_slot_stored);
				}
				else
					storeGroupAtNextSlot(sourcesManager, groupIndex);
			}
		}
	}
	
	void SourcesTrajectory::playTrajectory(SourcesManager* sourcesManager, double fractionnalValue)
	{
		fractionnalValue = clip_minmax(fractionnalValue, 0., 1.);
		double aFractionalIndex = fractionnalValue * (double)getMaximumIndexOfSlot();
		
		recallFractionalSlot(sourcesManager, aFractionalIndex);
		m_last_slot_stored = aFractionalIndex-1;
	}
	
	void SourcesTrajectory::erase()
	{
		clear();
		m_last_slot_stored = -1;
	}
	
	void SourcesTrajectory::erase(double fractionnalValueBegin, double fractionnalValueEnd)
	{
		long indexBegin = clip_minmax(fractionnalValueBegin, 0., 1.) * (double)getMaximumIndexOfSlot();
		long indexEnd = clip_minmax(fractionnalValueEnd, 0., 1.) * (double)getMaximumIndexOfSlot();
		for(long i = indexBegin; i < indexEnd; i++)
		{
			deleteSlot(i);
		}
	}
	
	SourcesTrajectory::~SourcesTrajectory()
	{
		clear();
	}
}