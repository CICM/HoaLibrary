/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef __hoa_granulate___GrainPlug__
#define __hoa_granulate___GrainPlug__

#include "HoaPlugProcessor.h"
#include "genlib_common.h"
#include <vector>

class GrainPlug : public HoaPlugProcessor
{
private:
    double m_grainSize;
    double m_delay;
    double m_feedback;
    double m_rarefaction;
    
    CommonState *genGrain;
	int nParams;
    
public:
    GrainPlug(const long _order = 0, const double _grainsize = 100, const double _delay = 1000, const double _feedback = 0, const double _rarefaction = 0);
    ~GrainPlug();
    
    void IOChangeCallback();
    void DSPChangeCallback();
    
    void setGrainSize(double _grainSize);
    void setDelay(double _delay);
    void setFeedback(double _feedback);
    void setRarefaction(double _rarefaction);
    
    void setPlugIO(int _numberOfInputs, int _numberOfOutputs);
    void process(float** aInputs, float** aOutputs);
    void process(float** aInputs, int nbInput, float** aOutputs, int nbOutput);
    
    int bufferSize;
	vector< t_sample * > inputBuffers;
	vector< t_sample * > outputBuffers;
    //t_sample** inputBuffers;
    //t_sample** outputBuffers;
    
    /* Perform sample by sample */
    /*
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
            aOutputs[i] = 0.;
		for(int i = 0; i < m_number_of_sources; i++)
            m_eases[i]->process(aInputs[i], aOutputs);
	}
    */
	
	/* Perform block sample */
    /*
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
        Type* outputs;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            outputs = aOutputs[i];
            for(int j = 0; j < m_vector_size; j++)
                outputs[j] = 0.;
        }
        
		for(int i = 0; i < m_number_of_sources; i++)
            m_eases[i]->process(aInputs[i], aOutputs);
	}
    */
//    void process(float** aInputs, float** aOutputs)
//	{
//        perform(genGrain, (t_sample**)aInputs, getNumberOfInputs(), (t_sample**)aOutputs, getNumberOfOutputs(), getVectorSize());
//	}
    
};

#endif /* defined(__hoa_granulate___GrainPlug__) */
