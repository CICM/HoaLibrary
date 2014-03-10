/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_SOURCESPRESET
#define DEF_SOURCESPRESET

#include "../Hoa/Hoa.h"
#include "SourcesManager.h"

namespace Hoa2D
{
	//! The sources preset
    /** The SourcesPreset should be used to manage sources and group presets
     */
	class SourcesPreset
	{
		
	protected:
		long    m_last_slot_stored;
		std::vector <SourcesManager*> m_source_managers;
		
		void copySourceManager(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination);
		void copySource(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long sourceIndex);
		void copyGroup(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long groupeIndex);
		long interpolationSourceManager(SourcesManager* aSouceManagerSourceOne, SourcesManager* aSouceManagerSourceTwo, SourcesManager* aSouceManagerDestination, double aFrac);
		
	public:
		SourcesPreset();
		
		void storeSouceManagerAtSlot(SourcesManager* aSouceManager, long index);
		void storeSouceManagerAtFirstEmptySlot(SourcesManager* aSouceManager);
		void storeSouceManagerAtLastUsedSlot(SourcesManager* aSouceManager);
		void storeSouceManagerAtNewEndSlot(SourcesManager* aSouceManager);
		void storeSouceManagerAtNextSlot(SourcesManager* aSouceManager);
		void insertSlot(SourcesManager* aSouceManager, long index);
		void removeSlot(long index);
		void deleteSlot(long index);
		void copySlot(long anIndexSouce, long anIndexDestination);
		void renumber();
		void clear();
		
		void storeSourceAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long sourceIndex);
		void storeSourceAtNextSlot(SourcesManager* aSouceManager, long sourceIndex);
		void storeGroupAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long groupeIndex);
		void storeGroupAtNextSlot(SourcesManager* aSouceManager,long groupeIndex);
		
		void recallSlot(SourcesManager* aSouceManager, long index);
		void recallFractionalSlot(SourcesManager* aSouceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex);
		long recallFractionalSlot(SourcesManager* aSouceManager, double aFractionnalIndex);
		
		long getMaximumIndexOfSlot();
		long getSlotExistence(long index);
		
		~SourcesPreset();
	};
}
#endif
