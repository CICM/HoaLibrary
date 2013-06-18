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