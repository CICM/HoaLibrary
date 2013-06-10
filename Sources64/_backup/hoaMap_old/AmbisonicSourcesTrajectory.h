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

#ifndef DEF_AMBISONICSOURCESTRAJECTORY
#define DEF_AMBISONICSOURCESTRAJECTORY

#include "cicmTools.h"
#include "AmbisonicSourcesPreset.h"

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
