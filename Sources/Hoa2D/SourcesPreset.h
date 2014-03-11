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
		
		void copySourceManager(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination);
		void copySource(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination, long sourceIndex);
		void copyGroup(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination, long groupeIndex);
		long interpolationSourceManager(SourcesManager* sourceManagerSourceOne, SourcesManager* sourceManagerSourceTwo, SourcesManager* sourceManagerDestination, double aFrac);
		
	public:
		SourcesPreset();
		
		void storeSourceManagerAtSlot(SourcesManager* sourceManager, long index);
		void storeSourceManagerAtFirstEmptySlot(SourcesManager* sourceManager);
		void storeSourceManagerAtLastUsedSlot(SourcesManager* sourceManager);
		void storeSourceManagerAtNewEndSlot(SourcesManager* sourceManager);
		void storeSourceManagerAtNextSlot(SourcesManager* sourceManager);
		void insertSlot(SourcesManager* sourceManager, long index);
		void removeSlot(long index);
		void deleteSlot(long index);
		void copySlot(long anIndexSouce, long anIndexDestination);
		void renumber();
		void clear();
		
		void storeSourceAtSlot(SourcesManager* sourceManager, long aSlotIndex, long sourceIndex);
		void storeSourceAtNextSlot(SourcesManager* sourceManager, long sourceIndex);
		void storeGroupAtSlot(SourcesManager* sourceManager, long aSlotIndex, long groupeIndex);
		void storeGroupAtNextSlot(SourcesManager* sourceManager,long groupeIndex);
		
		void recallSlot(SourcesManager* sourceManager, long index);
		void recallFractionalSlot(SourcesManager* sourceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex);
		long recallFractionalSlot(SourcesManager* sourceManager, double aFractionnalIndex);
		
		long getMaximumIndexOfSlot();
		long getSlotExistence(long index);
		
		~SourcesPreset();
	};
}
#endif
