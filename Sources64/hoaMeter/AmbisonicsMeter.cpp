/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "AmbisonicsMeter.h"

AmbisonicsMeter::AmbisonicsMeter(long aVectorSize, double aSamplingRate, long aNumberofChannels) : Planewaves(<#args#>)
{

	m_number_of_inputs		= Tools::clip_min(aNumberofChannels, (long)1);
	m_number_of_outputs		= 0;
	
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
}

void AmbisonicsMeter::setNumberOfChannels(long aNumberofChannels)
{
    m_number_of_inputs = Tools::clip_min(aNumberofChannels, (long)1);
}

std::string AmbisonicsMeter::getChannelName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return "Channel " + Tools::intToString(anIndex);
    else
        return "No harmonic";
}

double AmbisonicsMeter::getLoudspeakerAmplitude(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return m_loudspeakers_amplitudes[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerEnergy(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return m_loudspeakers_amplitudes[anIndex];
    else
        return 0.;
}

double       getEnergyVectorAbscissa();
double       getEnergyVectorOrdinate();
double       getVelocityVectorAbscissa();
double       getVelocityVectorOrdinate();


AmbisonicsMeter::~AmbisonicsMeter()
{
	;
}

