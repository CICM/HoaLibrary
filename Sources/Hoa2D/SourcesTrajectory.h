/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_SOURCESTRAJECTORY
#define DEF_SOURCESTRAJECTORY

#include "SourcesPreset.h"

namespace Hoa2D
{
	//! The sources trajectory
    /** The SourcesTrajectory should be used to manage sources trajectory
     */
	class SourcesTrajectory : public SourcesPreset
	{
		
	private:
		
		long    m_recording;
		long    m_limited;
		
	public:
		
		//! The source trajectory constructor.
		/**	The source trajectory constructor allocates and initialize the member values.
		 */
		SourcesTrajectory();
		
		//! The source trajectory destructor free the memory.
		~SourcesTrajectory();
		
		//! Set the recording state
		/**
		 * @param     isRecording		The recording state
         */
		void setRecording(bool isRecording);
		
		//! Set the limited state
		/**
		 * @param     isLimited		The limited state
         */
		void setLimited(bool isLimited);
		
		//! Record a source in trajectory
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     sourceIndex			The index of the source.
         */
		void recordSourceInTrajectory(SourcesManager* sourcesManager, long sourceIndex);
		
		//! Record a group in trajectory
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     groupIndex			The index of the source.
         */
		void recordGroupInTrajectory(SourcesManager* sourcesManager,  long groupIndex);
		
		//! Play a trajectory at a fractionnal index
		/**
		 * @param     sourcesManager		A SourcesManager object pointer.
		 * @param     fractionnalValue		The fractionnal value (between 0. and 1.).
         */
		void playTrajectory(SourcesManager* sourcesManager, double fractionnalValue);
		
		//! Erase all of the trajectory.
		void erase();
		
		//! Erase a part of a trajectory
		/**
		 * @param     fractionnalValueBegin		The fractionnal begin value of the trajectory (between 0. and 1.).
		 * @param     fractionnalValueEnd		The fractionnal end value of the trajectory (between 0. and 1.).
         */
		void erase(double fractionnalValueBegin, double fractionnalValueEnd);
		
		//! Is the sources trajectory limited
		/**
		 * @return     The limited state
         */
		bool getLimited()		const {return m_limited;}
		
		//! Get the recording state
		/**
		 * @return     The recording state
         */
		bool getRecording()		const {return m_recording;}
	};
}
#endif
