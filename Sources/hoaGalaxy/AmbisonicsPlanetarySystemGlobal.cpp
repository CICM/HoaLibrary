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
 *  - Redistributions in binary form must reproduce the above copyright notice,
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

#include "AmbisonicsPlanetarySystem.h"

/**************************************/
/********** GLOBAL FUNCTION ***********/
/**************************************/

PlanetarySystem::PlanetarySystem(double aSunRadius, double anSunAngle, double aGalaxyLimit)
{
    m_galaxy_limit = aGalaxyLimit;
    m_sun = new Sun(aSunRadius, anSunAngle, aGalaxyLimit);
}

void PlanetarySystem::setColor(double red, double green, double blue, double alpha)
{
    m_color.red =  Tools::clip(red, 0., 1.);
    m_color.green =  Tools::clip(green, 0., 1.);
    m_color.blue =  Tools::clip(blue, 0., 1.);
    m_color.alpha =  Tools::clip(alpha, 0., 1.);
}

void PlanetarySystem::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void PlanetarySystem::setMuted(bool muted)
{
    m_sun->setMuted(muted);
    for(m_iterator = m_satellites.begin(); m_iterator != m_satellites.end(); m_iterator++)
    {
        m_iterator->second->setMuted(muted);
    }
}

color PlanetarySystem::getColor()
{
    return m_color;
}

std::string PlanetarySystem::getDescription()
{
    return m_description;
}

bool PlanetarySystem::getMuted()
{
    if(!m_sun->getMuted())
        return 0;
    else
    {
        for (m_iterator = m_satellites.begin(); m_iterator != m_satellites.end(); m_iterator++)
        {
            if(m_iterator->second->getMuted() == 0)
                return 0;
        }
    }
    return 1;
}

PlanetarySystem::~PlanetarySystem()
{
    delete m_sun;
    m_satellites.clear();
}