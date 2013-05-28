/*
 * AmbisonicSourcesTrajectory.h
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
