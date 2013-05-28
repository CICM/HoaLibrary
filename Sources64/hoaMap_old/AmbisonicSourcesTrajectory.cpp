/*
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

#include "AmbisonicSourcesTrajectory.h"

SourcesTrajectory::SourcesTrajectory()
{
    m_recording = 0;
    m_limited = 0;
}

void SourcesTrajectory::setRecording(long aOnOffValue)
{
    m_recording = Tools::clip(aOnOffValue, (long)0, (long)1);
}

void SourcesTrajectory::setLimited(long aOnOffValue)
{
    m_limited = Tools::clip(aOnOffValue, (long)0, (long)1);
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
    aFractionnalValue = Tools::clip(aFractionnalValue, 0., 1.);
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
    long anIndexBegin = Tools::clip(aFractionnalValueBegin, 0., 1.) * (double)getMaximumIndexOfSlot();
    long anIndexEnd = Tools::clip(aFractionnalValueEnd, 0., 1.) * (double)getMaximumIndexOfSlot();
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