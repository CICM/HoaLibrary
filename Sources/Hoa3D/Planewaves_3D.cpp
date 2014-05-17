/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Planewaves_3D.h"

namespace Hoa3D
{
    Planewaves::Planewaves(unsigned int numberOfChannels)
    {
		assert(numberOfChannels > 0);
		m_number_of_channels    = numberOfChannels;
        m_channels_azimuth      = new double[m_number_of_channels];
        m_channels_elevation    = new double[m_number_of_channels];
        sphere_discretize(numberOfChannels, m_channels_azimuth, m_channels_elevation);
    }
	
	void Planewaves::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
		assert(index < m_number_of_channels);
		m_channels_azimuth[index] = wrap_twopi(azimuth);
        m_channels_elevation[index] = wrap_twopi(elevation);
	}
    
    Planewaves::~Planewaves()
    {
		delete [] m_channels_azimuth;
        delete [] m_channels_elevation;
    }
}

