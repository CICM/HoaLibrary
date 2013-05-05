/*
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

#include "AmbisonicsMultiDecoder.h"

AmbisonicsMultiDecoder::AmbisonicsMultiDecoder(long anOrder, std::string aRootPath, long aPinnaSize, long aVectorSize, long aSamplingRate, long aMode, long aNumberOfLoudspeakers, double aConfiguration, double anOffset) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
	m_decoder = new AmbisonicsDecoder(m_order, aNumberOfLoudspeakers, anOffset, m_vector_size);
    m_binaural = new AmbisonicsBinaural(m_order, aRootPath, aPinnaSize, m_vector_size, m_sampling_rate);
    m_restitution = new AmbisonicsRestitution(m_order, aConfiguration, m_vector_size);
    setMode(aMode);
    setOffset(anOffset);
}

void AmbisonicsMultiDecoder::setMode(long aMode)
{
    if(aMode == Hoa_Restitution)
    {
        m_mode = Hoa_Restitution;
        m_restitution->setVectorSize(m_vector_size);
        m_restitution->setSamplingRate(m_sampling_rate);
        m_number_of_outputs = m_restitution->getNumberOfOutputs();
    }
    else if(aMode == Hoa_Binaural)
    {
        m_mode = Hoa_Binaural;
        m_binaural->setVectorSize(m_vector_size);
        m_binaural->setSamplingRate(m_sampling_rate);
        m_number_of_outputs = 2;
    }
    else
    {
        m_mode = Hoa_Ambisonics;
        m_decoder->setVectorSize(m_vector_size);
        m_decoder->setSamplingRate(m_sampling_rate);
        m_number_of_outputs = m_decoder->getNumberOfOutputs();
    }
}

long AmbisonicsMultiDecoder::getMode()
{
    return m_mode;
}

/* ANBISONICS */
void AmbisonicsMultiDecoder::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{
    m_decoder->setNumberOfLoudspeakers(aNumberOfLoudspeakers);
    if(m_mode == Hoa_Ambisonics)
        m_number_of_outputs = m_decoder->getNumberOfOutputs();
}

long AmbisonicsMultiDecoder::getNumberOfLoudspeakers()
{
    return m_decoder->getNumberOfOutputs();
}

void AmbisonicsMultiDecoder::setOffset(double anOffset)
{
    m_decoder->setOffset(anOffset);
}

double AmbisonicsMultiDecoder::getOffset()
{
    return m_decoder->getOffset();
}

/* BINAURAL */
void AmbisonicsMultiDecoder::setPinnaSize(long aPinnaSize)
{
    m_binaural->setPinnaSize(aPinnaSize);
}

long AmbisonicsMultiDecoder::getPinnaSize()
{
    return m_binaural->getPinnaSize();
}

/* RESTITUTION */
void AmbisonicsMultiDecoder::setConfiguration(double aConfiguration)
{
    m_restitution->setConfiguration(aConfiguration);
    if(m_mode == Hoa_Restitution)
        m_number_of_outputs = m_restitution->getNumberOfOutputs();
}

double AmbisonicsMultiDecoder::getConfiguration()
{
    return m_restitution->getConfiguration();
}

void AmbisonicsMultiDecoder::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(m_mode == Hoa_Restitution)
        m_restitution->setLoudspeakerAngle(anIndex, anAngle);
}

double AmbisonicsMultiDecoder::getLoudspeakerAngle(long anIndex)
{
    return m_restitution->getLoudspeakerAngle(anIndex);
}

void AmbisonicsMultiDecoder::setVectorSize(long aVectorSize)
{
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    if(m_mode == Hoa_Restitution)
    {
        m_restitution->setVectorSize(m_vector_size);
    }
    else if(m_mode == Hoa_Binaural)
    {
        m_binaural->setVectorSize(m_vector_size);
    }
    else
    {
        m_decoder->setVectorSize(m_vector_size);
    }
}

void AmbisonicsMultiDecoder::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
    if(m_mode == Hoa_Restitution)
    {
        m_restitution->setSamplingRate(m_vector_size);
    }
    else if(m_mode == Hoa_Binaural)
    {
        m_binaural->setSamplingRate(m_vector_size);
    }
    else
    {
        m_decoder->setSamplingRate(m_vector_size);
    }
}

std::string  AmbisonicsMultiDecoder::getLoudspeakerName(long anIndex)
{
    if(m_mode == Hoa_Restitution)
    {
        return m_restitution->getLoudspeakerName(anIndex);
    }
    else if(m_mode == Hoa_Binaural)
    {
        return m_binaural->getLoudspeakerName(anIndex);
    }
    else
    {
        return m_decoder->getLoudspeakerName(anIndex);
    }
}

AmbisonicsMultiDecoder::~AmbisonicsMultiDecoder()
{
    delete m_decoder;
    delete m_binaural;
    delete m_restitution;
}

