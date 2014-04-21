/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Planewaves_3D.h"

namespace Hoa3D
{
    Planewaves::Planewaves(unsigned int numberOfLoudspeakers)
    {
		assert(numberOfLoudspeakers > 0);
		m_number_of_loudspeakers    = numberOfLoudspeakers;
        m_loudspeakers_azimuth      = new double[m_number_of_loudspeakers];
        m_loudspeakers_elevation    = new double[m_number_of_loudspeakers];
    }
	
	void Planewaves::setLoudspeakerPosition(unsigned int index, double azimuth, double elevation)
	{
		assert(index < m_number_of_loudspeakers);
		m_loudspeakers_azimuth[index] = wrap_twopi(azimuth);
        m_loudspeakers_elevation[index] = wrap_twopi(elevation);
	}
    
    Planewaves::~Planewaves()
    {
		delete [] m_loudspeakers_azimuth;
        delete [] m_loudspeakers_elevation;
    }
}

