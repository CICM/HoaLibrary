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
		
		void copySourceManager(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination);
		void copySource(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination, long sourceIndex);
		void copyGroup(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination, long groupIndex);
		long interpolationSourceManager(SourcesManager* sourcesManagerSourceOne, SourcesManager* sourcesManagerSourceTwo, SourcesManager* sourcesManagerDestination, double aFrac);
		
	public:
		
		//! The source preset constructor.
		/**	The source preset constructor allocates and initialize the member values.
		 */
		SourcesPreset();
		
		//! The source preset destructor free the memory.
		~SourcesPreset();
		
		//! Store a SourcesManager object at a particular slot index.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     index				The index of the slot.
         */
		void storeSourceManagerAtSlot(SourcesManager* sourcesManager, long index);
		
		//! Store a SourcesManager object at the first empty slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
         */
		void storeSourceManagerAtFirstEmptySlot(SourcesManager* sourcesManager);
		
		//! Store a SourcesManager object at the last used slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
         */
		void storeSourceManagerAtLastUsedSlot(SourcesManager* sourcesManager);
		
		//! Store a SourcesManager object in a new slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
         */
		void storeSourceManagerAtNewEndSlot(SourcesManager* sourcesManager);
		
		//! Store a SourcesManager object at the next slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
         */
		void storeSourceManagerAtNextSlot(SourcesManager* sourcesManager);
		
		//! Store a SourcesManager object by inserting it at a particular slot index.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     index					The index of the slot.
         */
		void insertSlot(SourcesManager* sourcesManager, long index);
		
		//! Delete the content of a slot.
		/**
		 * @param     index					The index of the slot.
         */
		void removeSlot(long index);
		
		//! Delete the slot and its content.
		/**
		 * @param     index					The index of the slot.
         */
		void deleteSlot(long index);
		
		//! Copy the content of a slot into another slot
		/**
		 * @param     sourceIndex			The index of the slot to copy.
		 * @param     destinationIndex		The index of the slot to copy in.
         */
		void copySlot(long sourceIndex, long destinationIndex);
		
		//! Renumber all slots
		void renumber();
		
		//! Clear all slots
		void clear();
		
		//! Store a source at a given slot index.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     slotIndex				The index of the slot.
		 * @param     sourceIndex			The index of the source to store.
         */
		void storeSourceAtSlot(SourcesManager* sourcesManager, long slotIndex, long sourceIndex);
		
		//! Store a source at the next slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     slotIndex				The index of the slot.
		 * @param     sourceIndex			The index of the source to store.
         */
		void storeSourceAtNextSlot(SourcesManager* sourcesManager, long sourceIndex);
		
		//! Store a group of source at a given slot index.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     slotIndex				The index of the slot.
		 * @param     groupIndex			The index of the group to store.
         */
		void storeGroupAtSlot(SourcesManager* sourcesManager, long slotIndex, long groupIndex);
		
		//! Store a group at the next slot.
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     slotIndex				The index of the slot.
		 * @param     groupIndex			The index of the group to store.
         */
		void storeGroupAtNextSlot(SourcesManager* sourcesManager,long groupIndex);
		
		//! Recall a given slot.
		/** Recall SourcesManager state directly
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     index					The index of the slot.
		 * @see recallFractionalSlot
         */
		void recallSlot(SourcesManager* sourcesManager, long index);
		
		//! Recall a given slot at a fractionnal index between two slot index.
		/** Interpolate between two SourcesManager's states.
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     sourceIndex			Index of the first slot.
		 * @param     destinationIndex		Index of the second slot.
		 * @param     fractionnalIndex		The fractionnal index (between 0 and 1).
		 * @see recallFractionalSlot
         */
		void recallFractionalSlot(SourcesManager* sourcesManager, long sourceIndex, long destinationIndex, double fractionnalIndex);
		
		//! Recall a given slot at a fractionnal index between two consecutive slot.
		/** Interpolate between two SourcesManager's states.
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     fractionnalIndex		The fractionnal index. (ex. 2.3 will interpolate between the slot 2 and slot 3)
		 * @see recallFractionalSlot
         */
		long recallFractionalSlot(SourcesManager* sourcesManager, double fractionnalIndex);
		
		//! Get The maximum index of slots.
		long getMaximumIndexOfSlot();
		
		//! Get the existence state of a given slot.
		/**
		 * @param     index					The index of the slot.
         */
		long getSlotExistence(long index);
	};
}
#endif
