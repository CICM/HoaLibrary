/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Planewaves.h"

namespace Hoa2D
{
    Planewaves::Planewaves(unsigned int numberOfChannels)
    {
		assert(numberOfChannels > 0);
		m_number_of_channels    = numberOfChannels;
        m_channels_azimuth      = new double[m_number_of_channels];
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_channels_azimuth[i] = (double)i / (double)m_number_of_channels * CICM_2PI;
        }
    }
	
	void Planewaves::setChannelPosition(unsigned int index, double azimuth)
	{
		assert(index < m_number_of_channels);
		m_channels_azimuth[index] = wrap_twopi(azimuth);
	}
    
    Planewaves::~Planewaves()
    {
		delete [] m_channels_azimuth;
    }
}

