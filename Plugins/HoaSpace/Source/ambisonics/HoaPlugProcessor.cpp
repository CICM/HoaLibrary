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

#include "HoaPlugProcessor.h"

HoaPlugProcessor::HoaPlugProcessor(long _order, Modes _mode, long _vectorSize, long _samplingRate)
{
    setOrder(_order, false);
    setMode(_mode, false);
    m_vectorSize = _vectorSize;
    m_sampleRate = _samplingRate;
    setupIO();
}
HoaPlugProcessor::~HoaPlugProcessor()
{
}
void HoaPlugProcessor::setOrderWithNumberOfLoudspeakers(const long _nbLoudSpeakers)
{
    long order = 0;
    if (_nbLoudSpeakers%2 == 0) // nombre pair de HP
        order = _nbLoudSpeakers*0.5-1;
    else
        order = floor(_nbLoudSpeakers*0.5);
    setOrder(order, true);
}
void HoaPlugProcessor::setOrder(long _order, bool _doSetupIO)
{
    m_order = Tools::clip_min(_order, (long)0);
    if (_doSetupIO) setupIO();
}
void HoaPlugProcessor::setVectorSize(long _vectorSize)
{
    if (m_vectorSize != _vectorSize) {
        m_vectorSize = Tools::clip_min(_vectorSize, (long)0);
        DSPChangeCallback();
    }
}
void HoaPlugProcessor::setSampleRate(long _sampleRate)
{
    if (m_sampleRate != _sampleRate)
    {
        m_sampleRate = Tools::clip_min(_sampleRate, (long)0);
        DSPChangeCallback();
    }
}

void HoaPlugProcessor::setMode(Modes _mode, bool _doSetupIO)
{
    m_mode = _mode;
    if (_doSetupIO) setupIO();
}
void HoaPlugProcessor::setupIO()
{
    switch (m_mode) {
        case NO: {
            m_number_of_inputs = 1;
            m_number_of_harmonics = m_number_of_outputs = m_order*2+1;
            break;
        }
        case PRE: {
            m_number_of_inputs = 1;
            m_number_of_harmonics = m_number_of_outputs = m_order+1;
            break;
        }
        case POST: {
            m_number_of_harmonics = m_number_of_inputs = m_number_of_outputs = m_order+1;
            break;
        }
        case OUT: {
            m_number_of_harmonics = m_number_of_inputs = m_number_of_outputs = m_order;
            break;
        }
        default: break;
    }
    IOChangeCallback();
}