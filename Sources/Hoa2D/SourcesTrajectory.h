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
		SourcesTrajectory();
		
		void setRecording(long aOnOffValue);
		void setLimited(long aOnOffValue);
		
		void recordSourceInTrajectory(SourcesManager* sourceManager, long sourceIndex);
		void recordGroupInTrajectory(SourcesManager* sourceManager,  long groupeIndex);
		void playTrajectory(SourcesManager* sourceManager, double aFractionnalValue);
		void erase();
		void erase(double aFractionnalValueBegin, double aFractionnalValueEnd);
		
		long getLimited();
		long getRecording();
		
		~SourcesTrajectory();
	};
}
#endif
