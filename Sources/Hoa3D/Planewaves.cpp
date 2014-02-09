/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Planewaves.h"

namespace Hoa3D
{
    Planewaves::Planewaves(unsigned int numberOfLoudspeakers)
    {
		setNumberOfLoudspeakers(numberOfLoudspeakers);
    }
	
	void Planewaves::setNumberOfLoudspeakers( unsigned int numberOfLoudspeakers)
	{
		assert(numberOfLoudspeakers > 0);
		m_number_of_loudspeakers = numberOfLoudspeakers;
	}
    
    std::string Planewaves::getLoudspeakerName(unsigned int index)
    {
        assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getName();
    }
	
	void Planewaves::setLoudspeakerPosition(unsigned int index, double azimuth, double elevation)
	{
		
	}
    
    Planewaves::~Planewaves()
    {
		delete [] m_speakerList;
    }
}

