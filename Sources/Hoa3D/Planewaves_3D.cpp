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
		setChannelsPosition(m_channels_azimuth, m_channels_elevation);
    }

	void Planewaves::setChannelsPosition(double* azimuths, double* elevations)
	{
		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			m_channels_azimuth[i] = wrap_twopi(azimuths[i]);
			m_channels_elevation[i] = wrap(elevations[i], -HOA_PI, HOA_PI);
			if(m_channels_elevation[i] > HOA_PI2)
			{
				m_channels_azimuth[i] = wrap_twopi(m_channels_azimuth[i] + HOA_PI);
				m_channels_elevation[i] -= HOA_PI2;
			}
			else if (m_channels_elevation[i] < -HOA_PI2)
			{
				m_channels_azimuth[i] = wrap_twopi(m_channels_azimuth[i] + HOA_PI);
				m_channels_elevation[i] += HOA_PI2;
			}
		}
	}
	
	void Planewaves::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
		assert(index < m_number_of_channels);
		m_channels_azimuth[index] = wrap_twopi(azimuth);
        m_channels_elevation[index] = wrap(elevation, -HOA_PI, HOA_PI);

		if(m_channels_elevation[index] > HOA_PI2)
		{
			m_channels_azimuth[index] = wrap_twopi(m_channels_azimuth[index] + HOA_PI);
			m_channels_elevation[index] -= HOA_PI2;
		}
		else if (m_channels_elevation[index] < -HOA_PI2)
		{
			m_channels_azimuth[index] = wrap_twopi(m_channels_azimuth[index] + HOA_PI);
			m_channels_elevation[index] += HOA_PI2;
		}
	}
    
    Planewaves::~Planewaves()
    {
		delete [] m_channels_azimuth;
        delete [] m_channels_elevation;
    }
}

