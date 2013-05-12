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
    m_configuration  = (long)Tools::clip_min(aConfiguration, 0.);
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
