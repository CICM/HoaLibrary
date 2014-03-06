/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef DEF_SOURCESPRESET
#define DEF_SOURCESPRESET

#include "../Hoa/Hoa.h"
#include "SourcesManager.h"

class SourcesPreset
{
	
protected: 
    long    m_last_slot_stored;
    std::vector <SourcesManager*> m_source_managers;
    
    void copySourceManager(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination);
    void copySource(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aSourceIndex);
    void copyGroup(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aGroupIndex);
    long interpolationSourceManager(SourcesManager* aSouceManagerSourceOne, SourcesManager* aSouceManagerSourceTwo, SourcesManager* aSouceManagerDestination, double aFrac);
    
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
    void recallFractionalSlot(SourcesManager* aSouceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex);
    long recallFractionalSlot(SourcesManager* aSouceManager, double aFractionnalIndex);
    
    long getMaximumIndexOfSlot();
    long getSlotExistence(long anIndex);
    
	~SourcesPreset();
};

#endif
