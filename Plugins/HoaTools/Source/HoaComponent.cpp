/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaComponent.h"

#define MIN_ZOOM 0.05

HoaProcessor::HoaProcessor()
{
    m_order                 = 1;
    m_number_of_sources     = 1;
    m_number_of_harmonics   = 3;
    m_number_of_channels	= 4;
	m_decoding_mode         = DecoderMulti::Mode::Regular;
    m_optimization          = Optim::Mode::InPhase;
    m_offset_of_channels    = 0.;
    m_maximum_order         = 1;
    m_maximum_number_of_channels = 64;
    m_minimum_number_of_channels = 3;
    
    for(int i = 0; i < 256; i++)
    {
        m_angles_of_channels[i] = 0;
    }
    for(int i = 0; i < m_number_of_channels; i++)
    {
        m_angles_of_channels[i] = i * 360. / m_number_of_channels;
    }
    
    m_sources_manager       = new SourcesManager(1. / (double)MIN_ZOOM - 5., 1);
    m_map                   = new Map(m_order, 2);
    m_rotate                = new Rotate(m_order);
    m_optim                 = new Optim(m_order);
    m_decoder               = new DecoderMulti(m_order);
    m_meter                 = new Meter(m_number_of_channels);
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
    m_order = clip_minmax(anOrder, 1, m_maximum_order);
}

void HoaProcessor::setNumberOfSources(long aNumberOfSources)
{
    m_number_of_sources = clip_minmax(aNumberOfSources, 1, 64);
    if(m_number_of_sources != m_sources_manager->getNumberOfSources())
    {
        if(m_number_of_sources > m_sources_manager->getNumberOfSources())
        {
            while(m_sources_manager->getNumberOfSources() != m_number_of_sources)
            {
                m_sources_manager->sourceNewPolar(1., Random().nextDouble() * HOA_2PI);
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

void HoaProcessor::setNumberOfChannels(long aNumberOfChannels)
{
    m_number_of_channels = clip_minmax(aNumberOfChannels, m_minimum_number_of_channels, m_maximum_number_of_channels);
    if(m_decoding_mode == DecoderMulti::Mode::Regular)
    {
        if(m_number_of_channels % 2)
            m_maximum_order = m_number_of_channels / 2 - 1;
        else
            m_maximum_order = m_number_of_channels / 2;
    }
}

void HoaProcessor::setDecodingMode(long aDecodingMode)
{
    m_decoding_mode = clip_minmax(aDecodingMode, DecoderMulti::Mode::Regular, DecoderMulti::Mode::Irregular);
}

void HoaProcessor::setOptimization(long optimization)
{
    m_optimization = clip_minmax(optimization, Optim::Mode::Basic, Optim::Mode::InPhase);
}

void HoaProcessor::setOffsetOfChannels(double anOffset)
{
    m_offset_of_channels = wrap_360(anOffset);
    m_rotate->setYaw(m_offset_of_channels / 360. * HOA_2PI + HOA_PI2);
}

void HoaProcessor::setAngleOfChannel(long anIndex, double anAngle)
{
    
}

void HoaProcessor::prepareToPlay(long aSampleRate, long aVectorSize)
{
	/*
    m_map->setSamplingRate(aSampleRate);
    m_map->setVectorSize(aVectorSize);
    m_map->setRamp(aVectorSize);
    m_rotate->setSamplingRate(aSampleRate);
    m_rotate->setVectorSize(aVectorSize);
    m_rotate->setAzimuth(m_offset_of_channels / 360. * HOA_2PI + HOA_PI2);
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
	*/
}

void HoaProcessor::process(float** iovector)
{
	/*
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
    m_rotate->setAzimuth(m_offset_of_channels / 360. * HOA_2PI + HOA_PI2);
    m_optim->setOptimMode(m_optimization);
	*/
}

void HoaProcessor::postProcess()
{
    if(m_sources_manager->getNumberOfSources() != m_number_of_sources)
    {
        m_number_of_sources = m_sources_manager->getNumberOfSources();
    }
    if(m_order != m_decoder->getOrder())
    {
        delete m_map;
        delete m_rotate;
        delete m_optim;
        delete m_decoder;
        
        m_map       = new Map(m_order, m_number_of_sources);
        m_rotate    = new Rotate(m_order);
        m_optim     = new Optim(m_order, Optim::Mode::InPhase);
        m_decoder   = new DecoderMulti(m_order);
    }
    if(m_number_of_sources != m_map->getNumberOfSources())
    {
        //m_map->setNumberOfSources(m_number_of_sources);
    }
    if(m_number_of_channels != m_meter->getNumberOfChannels())
    {
        m_decoder->setNumberOfChannels(m_number_of_channels);
        //m_meter->setNumberOfChannels(m_number_of_channels);
    }    
}

void HoaProcessor::releaseResources()
{
    for(int i = 0; i < 64; i++)
    {
        free(m_harmonics_matrix[i]);
    }
}







