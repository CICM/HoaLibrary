/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "SourcesTrajectory.h"

SourcesTrajectory::SourcesTrajectory()
{
    m_recording = 0;
    m_limited = 0;
}

void SourcesTrajectory::setRecording(long isRecording)
{
    m_recording = isRecording != 0;
}

void SourcesTrajectory::setLimited(long isLimited)
{
    m_limited = isLimited != 0;
}

void SourcesTrajectory::recordSourceInTrajectory(SourcesManager* aSouceManager, long aSourceIndex)
{
    if(m_recording)
    {
        if(m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot())
        {
            if(m_last_slot_stored <= getMaximumIndexOfSlot() && getMaximumIndexOfSlot() > 0)
            {
                storeSourceAtNextSlot(aSouceManager, aSourceIndex);
                recallSlot(aSouceManager, m_last_slot_stored);
            }
            else
                storeSourceAtNextSlot(aSouceManager, aSourceIndex);
        }
    }
}

void SourcesTrajectory::recordGroupInTrajectory(SourcesManager* aSouceManager, long aGroupIndex)
{
    if(m_recording && (m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot()))
    {
        if(m_limited == 0 || m_last_slot_stored+1 <= getMaximumIndexOfSlot())
        {
            if(m_last_slot_stored <= getMaximumIndexOfSlot() && getMaximumIndexOfSlot() > 0)
            {
                storeGroupAtNextSlot(aSouceManager, aGroupIndex);
                recallSlot(aSouceManager, m_last_slot_stored);
            }
            else
                storeSourceAtNextSlot(aSouceManager, aGroupIndex);
        }
    }
}

void SourcesTrajectory::playTrajectory(SourcesManager* aSouceManager, double aFractionnalValue)
{
    aFractionnalValue = clip_minmax(aFractionnalValue, 0., 1.);
    double aFractionalIndex = aFractionnalValue * (double)getMaximumIndexOfSlot();
  
    recallFractionalSlot(aSouceManager, aFractionalIndex);
    m_last_slot_stored = aFractionalIndex-1;
}

void SourcesTrajectory::erase()
{
    clear();
    m_last_slot_stored = -1;
}

void SourcesTrajectory::erase(double aFractionnalValueBegin, double aFractionnalValueEnd)
{
    long anIndexBegin = clip_minmax(aFractionnalValueBegin, 0., 1.) * (double)getMaximumIndexOfSlot();
    long anIndexEnd = clip_minmax(aFractionnalValueEnd, 0., 1.) * (double)getMaximumIndexOfSlot();
    for(long i = anIndexBegin; i < anIndexEnd; i++)
    {
        deleteSlot(i);
    }
}

long SourcesTrajectory::getRecording()
{
    return m_recording;
}

long SourcesTrajectory::getLimited()
{
    return m_limited;
}

SourcesTrajectory::~SourcesTrajectory()
{
    clear();
}