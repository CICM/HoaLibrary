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

#ifndef DEF_AMBISONICSOURCESPRESET
#define DEF_AMBISONICSOURCESPRESET

#include "cicmTools.h"
#include "AmbisonicSourcesManager.h"

class SourcesPreset
{
	
protected: 
    long    m_last_slot_stored;
    std::vector <SourcesManager*> m_source_managers;
    
    void copySourceManager(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination);
    void copySource(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aSourceIndex);
    void copyGroup(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aGroupIndex);
    void interpolationSourceManager(SourcesManager* aSouceManagerSourceOne, SourcesManager* aSouceManagerSourceTwo, SourcesManager* aSouceManagerDestination, double aFrac);
    
public:
	SourcesPreset();
    
    void storeSouceManagerAtSlot(SourcesManager* aSouceManager, long anIndex);
    void storeSouceManagerAtFirstEmptySlot(SourcesManager* aSouceManager);
    void storeSouceManagerAtLastUsedSlot(SourcesManager* aSouceManager);
    void storeSouceManagerAtNewEndSlot(SourcesManager* aSouceManager);
    void storeSouceManagerAtNextSlot(SourcesManager* aSouceManager);
    void insertSlot(SourcesManager* aSouceManager, long anIndex);
    void removeSlot(long anIndex);
    void deleteSlot(long anIndex);
    void copySlot(long anIndexSouce, long anIndexDestination);
    void renumber();
    void clear();
    
    void storeSourceAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long aSourceIndex);
    void storeSourceAtNextSlot(SourcesManager* aSouceManager, long aSourceIndex);
    void storeGroupAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long aGroupIndex);
    void storeGroupAtNextSlot(SourcesManager* aSouceManager,long aGroupIndex);
    
    void recallSlot(SourcesManager* aSouceManager, long anIndex);
    void RecallFractionalSlot(SourcesManager* aSouceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex);
    void recallFractionalSlot(SourcesManager* aSouceManager, double aFractionnalIndex);
    
    long getMaximumIndexOfSlot();
    long getSlotExistence(long anIndex);
    
	~SourcesPreset();
};

#endif
