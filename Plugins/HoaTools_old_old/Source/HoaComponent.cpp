/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "HoaComponent.h"

#define MIN_ZOOM 0.05

HoaProcessor::HoaProcessor()
{
    m_order                 = 1;
    m_number_of_sources     = 1;
    m_number_of_harmonics   = 3;
    m_number_of_loudspeakers= 4;
    m_decoding_mode         = Hoa_Dec_Ambisonic;
    m_optimization          = Hoa_InPhase_Optim;
    m_offset_of_loudspeakers= 0.;
    m_maximum_order         = 1;
    m_maximum_number_of_loudspeakers = 64;
    m_minimum_number_of_loudspeakers = 3;
    
    for(int i = 0; i < 256; i++)
    {
        m_angles_of_loudspeakers[i] = 0;
    }
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers[i] = i * 360. / m_number_of_loudspeakers;
    }
    
    m_sources_manager       = new SourcesManager(1. / (double)MIN_ZOOM - 5., 1);
    m_map                   = new AmbisonicsMultiMaps(1);
    m_rotate                = new AmbisonicRotate(1);
    m_optim                 = new AmbisonicOptim(1);
    m_decoder               = new AmbisonicsMultiDecoder(1, 4);
    m_meter                 = new AmbisonicsMeter(1);
}

HoaProcessor::~HoaProcessor()
{
    delete m_sources_manager;
    delete m_map;
    delete m_rotate;
    delete m_decoder;
    delete m_meter;
    delete m_optim;
}

void HoaProcessor::setOrder(long anOrder)
{
    m_order = Tools::clip(anOrder, 1, m_maximum_order);
}

void HoaProcessor::setNumberOfSources(long aNumberOfSources)
{
    m_number_of_sources = Tools::clip(aNumberOfSources, 1, 64);
    if(m_number_of_sources != m_sources_manager->getNumberOfSources())
    {
        if(m_number_of_sources > m_sources_manager->getNumberOfSources())
        {
            while(m_sources_manager->getNumberOfSources() != m_number_of_sources)
            {
                m_sources_manager->sourceNewPolar(1., Random().nextDouble() * CICM_2PI);
            }

        }
        else
        {
            while(m_sources_manager->getNumberOfSources() != m_number_of_sources+1)
            {
                m_sources_manager->sourceRemove(m_sources_manager->getMaximumIndexOfSource());
            }
        }
    }
}

void HoaProcessor::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{
    m_number_of_loudspeakers = Tools::clip(aNumberOfLoudspeakers, m_minimum_number_of_loudspeakers, m_maximum_number_of_loudspeakers);
    if(m_decoding_mode == Hoa_Dec_Ambisonic)
    {
        if(m_number_of_loudspeakers % 2)
            m_maximum_order = m_number_of_loudspeakers / 2 - 1;
        else
            m_maximum_order = m_number_of_loudspeakers / 2;
    }
}

void HoaProcessor::setDecodingMode(long aDecodingMode)
{
    m_decoding_mode = Tools::clip(aDecodingMode, Hoa_Dec_Ambisonic, Hoa_Dec_Irregular);
}

void HoaProcessor::setOptimization(long anOptimization)
{
    m_optimization = Tools::clip(anOptimization, Hoa_Basic_Optim, Hoa_InPhase_Optim);
}

void HoaProcessor::setOffsetOfLoudspeakers(double anOffset)
{
    m_offset_of_loudspeakers = Tools::degreeWrap(anOffset);
    m_rotate->setAzimuth(m_offset_of_loudspeakers / 360. * CICM_2PI + CICM_PI2);
}

void HoaProcessor::setAngleOfLoudspeaker(long anIndex, double anAngle)
{
    
}

void HoaProcessor::prepareToPlay(long aSampleRate, long aVectorSize)
{
    m_map->setSamplingRate(aSampleRate);
    m_map->setVectorSize(aVectorSize);
    m_map->setRamp(aVectorSize);
    m_rotate->setSamplingRate(aSampleRate);
    m_rotate->setVectorSize(aVectorSize);
    m_rotate->setAzimuth(m_offset_of_loudspeakers / 360. * CICM_2PI + CICM_PI2);
    m_optim->setSamplingRate(aSampleRate);
    m_optim->setVectorSize(aVectorSize);
    m_decoder->setSamplingRate(aSampleRate);
    m_decoder->setVectorSize(aVectorSize);
    m_meter->setSamplingRate(aSampleRate);
    m_meter->setVectorSize(aVectorSize);
    for(int i = 0; i < 64; i++)
    {
        m_harmonics_matrix[i] = new float[aVectorSize];
    }
}

void HoaProcessor::process(float** iovector)
{
    m_map->process(iovector, m_harmonics_matrix);
    m_rotate->process(m_harmonics_matrix);
    m_optim->process(m_harmonics_matrix);
    m_decoder->process(m_harmonics_matrix, iovector);
    m_meter->process(iovector);
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_map->setCoordinatesCartesian(i, m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
        m_map->setMuted(i, m_sources_manager->sourceGetMute(i));
    }
    m_rotate->setAzimuth(m_offset_of_loudspeakers / 360. * CICM_2PI + CICM_PI2);
    m_optim->setOptimMode(m_optimization);
}

void HoaProcessor::postProcess()
{
    if(m_sources_manager->getNumberOfSources() != m_number_of_sources)
    {
        m_number_of_sources = m_sources_manager->getNumberOfSources();
    }
    if(m_order != m_decoder->getDecompositionOrder())
    {
        delete m_map;
        delete m_rotate;
        delete m_optim;
        delete m_decoder;
        
        m_map       = new AmbisonicsMultiMaps(m_order, m_number_of_sources, 0, 512, 44100);
        m_rotate    = new AmbisonicRotate(m_order);
        m_optim     = new AmbisonicOptim(m_order, Hoa_InPhase_Optim);
        m_decoder   = new AmbisonicsMultiDecoder(m_order, m_number_of_loudspeakers);
    }
    if(m_number_of_sources != m_map->getNumberOfSources())
    {
        m_map->setNumberOfSources(m_number_of_sources);
    }
    if(m_number_of_loudspeakers != m_meter->getNumberOfLoudspeakers())
    {
        m_decoder->setNumberOfLoudspeakers(m_number_of_loudspeakers);
        m_meter->setNumberOfLoudspeakers(m_number_of_loudspeakers);
    }    
}

void HoaProcessor::releaseResources()
{
    for(int i = 0; i < 64; i++)
    {
        free(m_harmonics_matrix[i]);
    }
}







