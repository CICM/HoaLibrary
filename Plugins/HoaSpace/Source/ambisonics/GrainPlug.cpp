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

GrainPlug::GrainPlug(long _order, double _grainsize, double _delay, double _feedback, double _rarefaction) : HoaPlugProcessor(_order, NO), genGrain(0)
{
    genGrain = (CommonState *)create(getSampleRate(), 512);
    nParams = genGrain->numparams;
}
GrainPlug::~GrainPlug()
{
    if(genGrain) destroy(genGrain);
}

void GrainPlug::setPlugIO(int _numberOfInputs, int _numberOfOutputs)
{
}

void GrainPlug::DSPChangeCallback()
{
    genGrain->sr = m_sampleRate;
    genGrain->vs = m_vectorSize;
    reset(genGrain);
}


void GrainPlug::IOChangeCallback()
{
    ;
}


void GrainPlug::setGrainSize(double _grainSize)
{
    m_grainSize = Tools::clip(_grainSize, double(10), double(2000));
    setparameter(genGrain, 3, m_grainSize, NULL);
}
void GrainPlug::setDelay(double _delay)
{
    m_delay = Tools::clip(_delay, double(0), double(4000));
    setparameter(genGrain, 2, m_delay, NULL);
}
void GrainPlug::setFeedback(double _feedback)
{
    m_feedback = Tools::clip(_feedback, double(0), double(1));
    setparameter(genGrain, 1, m_feedback, NULL);
}
void GrainPlug::setRarefaction(double _rarefaction)
{
    m_rarefaction = Tools::clip(_rarefaction, double(0), double(1));
    setparameter(genGrain, 0, m_rarefaction, NULL);
}

//=====================================

void GrainPlug::process(float** aInputs, float** aOutputs)
{
}

void GrainPlug::process(float** aInputs, int nbInput, float** aOutputs, int nbOutput)
{
    perform(genGrain, aInputs, nbInput, aOutputs, nbOutput, getVectorSize());
}


