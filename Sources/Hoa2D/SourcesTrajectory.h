/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef DEF_SOURCESTRAJECTORY
#define DEF_SOURCESTRAJECTORY

#include "SourcesPreset.h"

class SourcesTrajectory : public SourcesPreset
{
	
private:
    long    m_recording;
    long    m_limited;
    
public:
	SourcesTrajectory();
    
    void setRecording(long aOnOffValue);
    void setLimited(long aOnOffValue);
    
    void recordSourceInTrajectory(SourcesManager* aSouceManager, long aSourceIndex);
    void recordGroupInTrajectory(SourcesManager* aSouceManager,  long aGroupIndex);
    void playTrajectory(SourcesManager* aSouceManager, double aFractionnalValue);
    void erase();
    void erase(double aFractionnalValueBegin, double aFractionnalValueEnd);
    
    long getLimited();
    long getRecording();    
    
	~SourcesTrajectory();
};

#endif
