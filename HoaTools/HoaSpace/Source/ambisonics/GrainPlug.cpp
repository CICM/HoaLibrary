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

#include "GrainPlug.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

void toSample(t_sample *dst, const float *src, long n) {
	while (n--) *dst++ = *src++;
}

void fromSample(float *dst, const t_sample *src, long n) {
	while (n--) *dst++ = *src++;
}

void zeroBuffer(t_sample *dst, int n) {
	while (n--) *dst++ = 0;
}

GrainPlug::GrainPlug(long _order, double _grainsize, double _delay, double _feedback, double _rarefaction) : HoaPlugProcessor(_order, NO), genGrain(0)
{
    genGrain = (CommonState *)create(getSampleRate(), 512);
    nParams = genGrain->numparams;
    
    /*
    bufferSize = getVectorSize();
    inputBuffers.resize(getNumberOfInputs());
	outputBuffers.resize(getNumberOfOutputs());
	
	for(int i=0; i < inputBuffers.size(); i++) {
		inputBuffers[i] = new t_sample[bufferSize];
	}
	for(int i=0; i < outputBuffers.size(); i++) {
		outputBuffers[i] = new t_sample[bufferSize];
	}
    */
}
GrainPlug::~GrainPlug()
{
    if(genGrain) destroy(genGrain);
    
    for(int i=0; i < inputBuffers.size(); i++) {
		delete[] inputBuffers[i];
	}
	for(int i=0; i < outputBuffers.size(); i++) {
		delete[] outputBuffers[i];
	}
}

void GrainPlug::setPlugIO(int _numberOfInputs, int _numberOfOutputs)
{
    bufferSize = getVectorSize();
    inputBuffers.resize(_numberOfInputs);
	outputBuffers.resize(_numberOfOutputs);
	
	for(int i=0; i < inputBuffers.size(); i++) {
		inputBuffers[i] = new t_sample[bufferSize];
	}
	for(int i=0; i < outputBuffers.size(); i++) {
		outputBuffers[i] = new t_sample[bufferSize];
	};
}

void GrainPlug::DSPChangeCallback()
{
    genGrain->sr = m_sampleRate;
    genGrain->vs = m_vectorSize;
}


void GrainPlug::IOChangeCallback()
{
    ;
}


void GrainPlug::setGrainSize(double _grainSize)
{
    m_grainSize = Tools::clip(_grainSize, double(10), double(2000));
    //genGrain->params->
}
void GrainPlug::setDelay(double _delay)
{
    m_delay = Tools::clip(_delay, double(0), double(4000));
}
void GrainPlug::setFeedback(double _feedback)
{
    m_feedback = Tools::clip(_feedback, double(0), double(1));
}
void GrainPlug::setRarefaction(double _rarefaction)
{
    m_rarefaction = Tools::clip(_rarefaction, double(0), double(1));
}

//=====================================

void GrainPlug::process(float** aInputs, float** aOutputs)
{
}

void GrainPlug::process(float** aInputs, int nbInput, float** aOutputs, int nbOutput)
{
    perform(genGrain, aInputs, nbInput, aOutputs, nbOutput, getVectorSize());
    
    //perform(genGrain, inputBuffers, nbInput, outputBuffers, nbOutput, getVectorSize());
    //    int nin = (int)MIN(inSourceP.size(), inputBuffers.size());
    //    int nout = (int)MIN(inDestP.size(), outputBuffers.size());
    //int nin = inputBuffers.size();
    //int nout = outputBuffers.size();
    /*
    int nin = (int)MIN(nbInput, inputBuffers.size());
    int nout = (int)MIN(nbOutput, outputBuffers.size());
    int inFramesToProcess = getVectorSize();
    int n = 0;
    
    while(n < inFramesToProcess) {
        int toprocess = MIN(bufferSize, (inFramesToProcess-n));
        
        for(int i=0; i < nin; i++) {
            //toSample(inputBuffers[i], aInputs[i]+n, toprocess);
            toSample(inputBuffers[i], aInputs[i]+n, toprocess);
        }
        for(int i=nin; i < inputBuffers.size(); i++) {
            zeroBuffer(inputBuffers[i], toprocess);
        }
        
        perform(
				genGrain,
				&(inputBuffers[0]), inputBuffers.size(),
				&(outputBuffers[0]), outputBuffers.size(),
				toprocess
                );
        
        for(int i=0; i < nout; i++) {
            fromSample(aOutputs[i]+n, outputBuffers[i], toprocess);
        }
        
        n += toprocess;
    }
     
    */
    
    //perform(genGrain, (t_sample**)aInputs, nbInput, (t_sample**)aOutputs, nbOutput, getVectorSize());
}


