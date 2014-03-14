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
        m_azimuth_of_channels[i] = 0;
    }
    for(int i = 0; i < m_number_of_channels; i++)
    {
        m_azimuth_of_channels[i] = i * 360. / m_number_of_channels;
    }
	
	m_hoa_manager			= new KitSources(m_order);
    m_meter                 = new Meter(m_number_of_channels);
}

HoaProcessor::~HoaProcessor()
{
	delete m_hoa_manager;
    delete m_meter;
}

void HoaProcessor::setOrder(long anOrder)
{
    m_order = clip_minmax(anOrder, 1, m_maximum_order);
	m_hoa_manager->setOrder(m_order);
	m_order = m_hoa_manager->getOrder();
}

void HoaProcessor::setNumberOfSources(long aNumberOfSources)
{
    m_number_of_sources = clip_minmax(aNumberOfSources, 1, 64);
	m_hoa_manager->setNumberOfSources(m_number_of_sources);
	m_number_of_sources = m_hoa_manager->getNumberOfSources();
}

void HoaProcessor::setNumberOfChannels(long aNumberOfChannels)
{
    m_number_of_channels = clip_minmax(aNumberOfChannels, m_minimum_number_of_channels, m_maximum_number_of_channels);
	m_hoa_manager->setNumberOfChannels(m_number_of_channels);
	m_number_of_channels = m_hoa_manager->getNumberOfChannels();
	
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
	m_hoa_manager->setDecodingMode(m_decoding_mode);
	m_decoding_mode = m_hoa_manager->getDecodingMode();
}

void HoaProcessor::setOptimization(long optimization)
{
	m_hoa_manager->setDecodingMode(m_decoding_mode);
    m_optimization = m_hoa_manager->getOptimMode();
}

void HoaProcessor::setOffsetOfChannels(double anOffset)
{
    m_offset_of_channels = wrap_360(anOffset);
	m_hoa_manager->setChannelsOffset(m_offset_of_channels / 360. * HOA_2PI + HOA_PI2);
	m_offset_of_channels = radToDeg(m_hoa_manager->getChannelsOffset());
}

void HoaProcessor::setAzimuthOfChannel(long index, double anAngle)
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
	m_hoa_manager->applyChanges();
	
	m_order = m_hoa_manager->getOrder();
	m_number_of_sources = m_hoa_manager->getNumberOfSources();
	m_number_of_channels = m_hoa_manager->getNumberOfChannels();
	m_decoding_mode = m_hoa_manager->getDecodingMode();
	m_optimization = m_hoa_manager->getOptimMode();
	m_offset_of_channels = radToDeg(m_hoa_manager->getChannelsOffset());
	
	/*
    if(m_number_of_channels != m_meter->getNumberOfChannels())
        m_meter->setNumberOfChannels(m_number_of_channels);
	*/
}

void HoaProcessor::releaseResources()
{
    for(int i = 0; i < 64; i++)
    {
        free(m_harmonics_matrix[i]);
    }
}







