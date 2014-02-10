/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Planewaves.h"

namespace Hoa3D
{
    Planewaves::Planewaves(unsigned int numberOfLoudspeakers, bool autoName)
    {
		m_autoName = autoName;
		setNumberOfLoudspeakers(numberOfLoudspeakers);
    }
	
	void Planewaves::updateSpeakerName(unsigned int index)
	{
		if (!m_autoName) return;
		std::string name;
		name = "Channel " + Tools::intToString(index) + " : " +
		Tools::floatToStringOneDecimal(Tools::radToDeg(m_speakerList[index].getAzimuth())) + "° " +
		Tools::floatToStringOneDecimal(Tools::radToDeg(m_speakerList[index].getElevation())) + "°";
		setLoudspeakerName(index, name);
	}
	
	void Planewaves::setNumberOfLoudspeakers( unsigned int numberOfLoudspeakers)
	{
		assert(numberOfLoudspeakers > 0);
		m_number_of_loudspeakers = numberOfLoudspeakers;
	}
	
	void Planewaves::setLoudspeakerPosition(unsigned int index, double azimuth, double elevation)
	{
		assert(index < m_number_of_loudspeakers);
		m_speakerList[index].setAzimuth(azimuth);
		m_speakerList[index].setElevation(elevation);
	}
	
	void Planewaves::setLoudspeakerName(unsigned int index, std::string name)
    {
        assert(index < m_number_of_loudspeakers);
		m_speakerList[index].setName(name);
    }
	
	double Planewaves::getLoudspeakerAbscissa(unsigned int index) const
	{
		assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getX();
	}
	
	double Planewaves::getLoudspeakerOrdinate(unsigned int index) const
	{
		assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getY();
	}
	
	double Planewaves::getLoudspeakerAzimuth(unsigned int index) const
	{
		assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getAzimuth();
	}
	
	double Planewaves::getLoudspeakerElevation(unsigned int index) const
	{
		assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getElevation();
	}
	
	double Planewaves::getLoudspeakerDistance(unsigned int index) const
	{
		assert(index < m_number_of_loudspeakers);
		return m_speakerList[index].getDistance();
	}
	
	std::string Planewaves::getLoudspeakerName(unsigned int index)
    {
        assert(index < m_number_of_loudspeakers);
		updateSpeakerName(index);
		return m_speakerList[index].getName();
    }
    
    Planewaves::~Planewaves()
    {
		delete [] m_speakerList;
    }
}

