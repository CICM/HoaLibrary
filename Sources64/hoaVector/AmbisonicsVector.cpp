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

#include "AmbisonicsVector.h"

Ambisonicsvector::Ambisonicsvector(double aConfiguration, long aMode, long aVectorSize) : Planewaves(aConfiguration, aVectorSize)
{
    m_abscissa_of_loudspeakers = NULL;
    m_ordinate_of_loudspeakers = NULL;
    setConfiguration(m_configuration);
    setMode(aMode);
}

void Ambisonicsvector::setConfiguration(double aConfiguration, bool standardOnOff)
{
    m_configuration  = (long)Tools::clip_min(aConfiguration, 1.);
    m_number_of_inputs		= m_configuration;
	m_number_of_outputs		= 4;
    if(aConfiguration - (long)aConfiguration != 0.)
    {
        m_low_frequency_effect = 1;
        m_configuration += 0.1;
    }
    else
        m_low_frequency_effect = 0;
    
    if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    if(m_abscissa_of_loudspeakers)
        free(m_abscissa_of_loudspeakers);
    if(m_ordinate_of_loudspeakers)
        free(m_ordinate_of_loudspeakers);
    
    /* Define standard configuration */
    m_angles_of_loudspeakers = new double[(long)m_configuration];
    m_abscissa_of_loudspeakers = new double[(long)m_configuration];
    m_ordinate_of_loudspeakers = new double[(long)m_configuration];
    computeConfiguration(standardOnOff);
   
    for (int i = 0; i < (long)m_configuration; i++)
    {
        m_abscissa_of_loudspeakers[i] = Tools::abscisse(1., m_angles_of_loudspeakers[i]);
        m_ordinate_of_loudspeakers[i] = Tools::ordinate(1., m_angles_of_loudspeakers[i]);
    }

}

void Ambisonicsvector::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < (long)m_configuration)
    {
        anAngle = Tools::radianWrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, (long)m_configuration);
    
    for(int i = 0; i < (long)m_configuration; i++)
    {
        m_abscissa_of_loudspeakers[i] = cos(m_angles_of_loudspeakers[i]);
        m_ordinate_of_loudspeakers[i] = sin(m_angles_of_loudspeakers[i]);
    }
}

void Ambisonicsvector::setLoudspeakerAngles(long len, double* angles)
{
    for (int i=0; i<len && i<m_number_of_inputs; i++) {
        m_angles_of_loudspeakers[i] = Tools::radianWrap(angles[i] / 360. * CICM_2PI);
    }
    Tools::sortVector(m_angles_of_loudspeakers, (long)m_configuration);
    
    for(int i = 0; i < (long)m_configuration; i++)
    {
        m_abscissa_of_loudspeakers[i] = cos(m_angles_of_loudspeakers[i]);
        m_ordinate_of_loudspeakers[i] = sin(m_angles_of_loudspeakers[i]);
    }
}

std::string Ambisonicsvector::getVectorName(long anIndex)
{
    if(!m_mode)        
    {
        if (anIndex == 0)
            return "Velocity vector radius";
        else if(anIndex == 1)
            return "Velocity vector angle";
        else if(anIndex == 2)
            return "Energy vector radius";
        else
            return "Energy vector angle";
    }
    else
    {
        if (anIndex == 0)
            return "Velocity vector abscissa";
        else if(anIndex == 1)
            return "Velocity vector ordinate";
        else if(anIndex == 2)
            return "Energy vector abscissa";
        else
            return "Energy vector ordinate";
    }
}

long Ambisonicsvector::getMode()
{
    return m_mode;
}

void Ambisonicsvector::setMode(long aMode)
{
    if(aMode == Hoa_Cartesian)
        m_mode = Hoa_Cartesian;
    else
        m_mode = Hoa_Polar;
}

Ambisonicsvector::~Ambisonicsvector()
{
	if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    if(m_abscissa_of_loudspeakers)
        free(m_abscissa_of_loudspeakers);
    if(m_ordinate_of_loudspeakers)
        free(m_ordinate_of_loudspeakers);
}
