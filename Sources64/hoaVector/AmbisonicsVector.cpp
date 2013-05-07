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

Ambisonicsvector::Ambisonicsvector(double aConfiguration, std::string aMode, long aVectorSize) : Ambisonics()
{
	m_number_of_outputs        = 4;
    m_angles_of_loudspeakers   = NULL;
    m_abscissa_of_loudspeakers = NULL;
    m_ordinate_of_loudspeakers = NULL;
    setConfiguration(aConfiguration);
    setMode("aMode");
}

void Ambisonicsvector::setConfiguration(double aConfiguration)
{
    /* Initialize the configuration */
    m_number_of_loudspeakers    = Tools::clip_min((long)aConfiguration, (long)1);
    m_number_of_inputs          = m_number_of_loudspeakers;
    m_configuation              = m_number_of_loudspeakers;
    

    if(aConfiguration - (long)aConfiguration != 0.)
    {
        m_low_frequency_effect = 1;
        m_configuation += 0.1;
    }
    else
        m_low_frequency_effect = 0;
    
    if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    if(m_abscissa_of_loudspeakers)
        free(m_abscissa_of_loudspeakers);
    if(m_ordinate_of_loudspeakers)
        free(m_ordinate_of_loudspeakers);
    
    m_angles_of_loudspeakers = new double[m_number_of_loudspeakers];
    m_abscissa_of_loudspeakers = new double[m_number_of_loudspeakers];
    m_ordinate_of_loudspeakers = new double[m_number_of_loudspeakers];
    
    /* Define standard configuration */
    if(m_number_of_loudspeakers == 1)          // Mono //
    {
        m_angles_of_loudspeakers[0] = 0.;
    }
    else if(m_number_of_loudspeakers == 2)     // Stereo //
    {
        m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 330. / 360. * CICM_2PI;
    }
    else if(m_number_of_loudspeakers == 3)     // Dolby Surround //
    {
        m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 180. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[2] = 330. / 360. * CICM_2PI;
    }
    else if(m_number_of_loudspeakers == 4)     // Quadriphonic //
    {
        m_angles_of_loudspeakers[0] = 45. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 135. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[2] = 225. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[3] = 315. / 360. * CICM_2PI;
    }
    else if(m_number_of_loudspeakers == 5)     // Surround 5.1 //
    {
        m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[3] = 250. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[4] = 330. / 360. * CICM_2PI;
    }
    else if(m_number_of_loudspeakers == 6)     // Surround 6.1 //
    {
        m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[3] = 180. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[4] = 250. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[5] = 330. / 360. * CICM_2PI;
    }
    else if(m_number_of_loudspeakers == 7)     // Surround 7.1 //
    {
        m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[3] = 135 / 360. * CICM_2PI;
        m_angles_of_loudspeakers[4] = 225 / 360. * CICM_2PI;
        m_angles_of_loudspeakers[5] = 250. / 360. * CICM_2PI;
        m_angles_of_loudspeakers[6] = 330. / 360. * CICM_2PI;
    }
    else                                          // Ambisonics base //
    {
        for (int i = 0; i < m_number_of_loudspeakers; i++)
            m_angles_of_loudspeakers[i] = (double)i / (double)m_number_of_loudspeakers * CICM_2PI;
    }
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_abscissa_of_loudspeakers[i] = cos(Tools::degToRad(m_angles_of_loudspeakers[i]));
        m_ordinate_of_loudspeakers[i] = sin(Tools::degToRad(m_angles_of_loudspeakers[i]));
    }
    
    m_number_of_inputs = m_number_of_loudspeakers + m_low_frequency_effect;
}

long Ambisonicsvector::getNumberOfLoudspeakers()
{
	return m_number_of_loudspeakers;
}

void Ambisonicsvector::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        anAngle = Tools::radianWrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, m_number_of_loudspeakers);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_abscissa_of_loudspeakers[i] = cos(Tools::degToRad(m_angles_of_loudspeakers[i]));
        m_ordinate_of_loudspeakers[i] = sin(Tools::degToRad(m_angles_of_loudspeakers[i]));
    }
    
}

double Ambisonicsvector::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_angles_of_loudspeakers[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

std::string Ambisonicsvector::getLoudspeakerName(long anIndex)
{
    if(m_number_of_loudspeakers == 1)          // Mono //
    {
        return "Omnidirectionnal Channel";
    }
    else if(m_number_of_loudspeakers == 2)     // Stereo //
    {
        if(anIndex == 0)
            return "Left channel";
        else if(anIndex == 1)
            return "Right channel";
        else if(anIndex == 2)
            return "Lfe channel";
    }
    else if(m_number_of_loudspeakers == 3)     // Dolby Surround //
    {
        if(anIndex == 0)
            return "Left channel";
        else if(anIndex == 1)
            return "Right channel";
        else if(anIndex == 2)
            return "Back channel";
        else if(anIndex == 3)
            return "Lfe channel";
    }
    else if(m_number_of_loudspeakers == 5)     // Surround 5.1 //
    {
        if(anIndex == 0)
            return "Center channel";
        else if(anIndex == 1)
            return "Front left channel";
        else if(anIndex == 2)
            return "Surround left channel";
        else if(anIndex == 3)
            return "Surround right channel";
        else if(anIndex == 4)
            return "Front right channel";
        else if(anIndex == 5)
            return "Lfe channel";
    }
    else if(m_number_of_loudspeakers == 6)     // Surround 6.1 //
    {
        if(anIndex == 0)
            return "Front center channel";
        else if(anIndex == 1)
            return "Front left channel";
        else if(anIndex == 2)
            return "Surround left channel";
        else if(anIndex == 3)
            return "Back center channel";
        else if(anIndex == 4)
            return "Surround right channel";
        else if(anIndex == 5)
            return "Front right channel";
        else if(anIndex == 6)
            return "Lfe channel";
    }
    else if(m_number_of_loudspeakers == 7)     // Surround 7.1 //
    {
        if(anIndex == 0)
            return "Front center channel";
        else if(anIndex == 1)
            return "Front left channel";
        else if(anIndex == 2)
            return "Surround left channel";
        else if(anIndex == 3)
            return "Back left channel";
        else if(anIndex == 4)
            return "Back right channel";
        else if(anIndex == 5)
            return "Surround right channel";
        else if(anIndex == 6)
            return "Front right channel";
        else if(anIndex == 7)
            return "Lfe channel";
    }
    else                                           // Ambisonics base //
    {
        if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
            return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(m_angles_of_loudspeakers[anIndex]/ CICM_2PI * 360.) + "°";
        
    }
    return "No channel";
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

std::string Ambisonicsvector::getMode()
{
    if(!m_mode)
        return "polar";
    else
        return "cartesian";
}

void Ambisonicsvector::setMode(std::string aMode)
{
    if(aMode == "cartesian")
        m_mode = 1;
    else
        m_mode = 0;        
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
