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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsMultiDecoder.h"

AmbisonicsMultiDecoder::AmbisonicsMultiDecoder(long anOrder, long aNumberOfLoudspeakers, long aMode, long aPinnaeSize, std::string aRootPath, long aVectorSize, long aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
	m_decoder = new AmbisonicsDecoder(m_order, aNumberOfLoudspeakers, m_vector_size);
    m_binaural = new AmbisonicsBinaural(m_order, aRootPath, aPinnaeSize, m_vector_size, m_sampling_rate);
    m_restitution = new AmbisonicsRestitution(m_order, aNumberOfLoudspeakers, Hoa_Amplitude_Panning, m_vector_size);
    setMode(aMode);
}

void AmbisonicsMultiDecoder::setMode(long aMode)
{
    if(aMode == Hoa_Restitution)
    {
        m_mode = Hoa_Restitution;
        m_restitution->Ambisonics::setVectorSize(m_vector_size);
        m_restitution->Ambisonics::setSamplingRate(m_sampling_rate);
        m_number_of_outputs = m_restitution->Planewaves::getNumberOfOutputs();
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

void AmbisonicsMultiDecoder::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{    
    if(m_mode == Hoa_Ambisonics)
    {
        m_decoder->setNumberOfLoudspeakers(aNumberOfLoudspeakers);
        m_number_of_outputs = m_decoder->getNumberOfOutputs();
    }
    else if (m_mode == Hoa_Restitution)
    {
        m_restitution->setNumberOfLoudspeakers(aNumberOfLoudspeakers);
        m_number_of_outputs = m_restitution->Planewaves::getNumberOfOutputs();
    }
    else
        m_number_of_outputs = 2;
}

long AmbisonicsMultiDecoder::getNumberOfLoudspeakers()
{
    return m_number_of_outputs;
}

void AmbisonicsMultiDecoder::setPinnaeSize(long aPinnaeSize)
{
    m_binaural->setPinnaeSize(aPinnaeSize);
}

long AmbisonicsMultiDecoder::getPinnaeSize()
{
    return m_binaural->getPinnaeSize();
}

void AmbisonicsMultiDecoder::setRestitutionMode(long aResitutionMode)
{
    m_restitution->setRestitutionMode(aResitutionMode);
}

long AmbisonicsMultiDecoder::getRestitutionMode()
{
    return m_restitution->getRestitutionMode();
}

void AmbisonicsMultiDecoder::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(m_mode == Hoa_Restitution)
        m_restitution->setLoudspeakerAngle(anIndex, anAngle);
}

double AmbisonicsMultiDecoder::getLoudspeakerAngle(long anIndex)
{
    if(m_mode == Hoa_Ambisonics)
        return m_decoder->getLoudspeakerAngle(anIndex);
    else if(m_mode == Hoa_Restitution)
        return m_restitution->getLoudspeakerAngle(anIndex);
    else
        return m_binaural->getLoudspeakerAngle(anIndex);
}

/* GENERAL */

void AmbisonicsMultiDecoder::setVectorSize(long aVectorSize)
{
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    if(m_mode == Hoa_Restitution)
    {
        m_restitution->Ambisonics::setVectorSize(m_vector_size);
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
        m_restitution->Ambisonics::setSamplingRate(m_vector_size);
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

