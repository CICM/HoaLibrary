/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter.h"

namespace Hoa2D
{
    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_channels_peaks    = new double[m_number_of_channels];
		m_channels_azimuth_width = new double[m_number_of_channels];
		m_channels_azimuth_mapped = new double[m_number_of_channels];
		computeAngles();
    }
    
    void Meter::setVectorSize(unsigned int vectorSize)
    {
        m_vector_size   = vectorSize;
        m_ramp          = 0;
    }
    
    void Meter::setChannelAzimuth(unsigned int index, double azimuth)
	{
        Planewaves::setChannelAzimuth(index, azimuth);
        computeAngles();
	}
	
	void Meter::setChannelsAzimuth(double* azimuth)
	{
        Planewaves::setChannelsAzimuth(azimuth);
		computeAngles();
	}
	
	void Meter::computeAngles()
	{
		double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
        for(int i = 0; i < m_number_of_channels; i++)
        {
			curAngle = getChannelAzimuth(i);
            if (i != 0)
                prevAngle = getChannelAzimuth(i-1);
            else
                prevAngle = getChannelAzimuth(m_number_of_channels-1);
            if (i != m_number_of_channels-1)
                nextAngle = getChannelAzimuth(i+1);
            else
                nextAngle = getChannelAzimuth(0);
            
            prevPortion = (curAngle - prevAngle);
            nextPortion = (nextAngle - curAngle);
            
            if (nextPortion < 0.)
                nextPortion += HOA_2PI;
            if (prevPortion < 0.)
                prevPortion += HOA_2PI;
            
            m_channels_azimuth_width[i] = (prevPortion + nextPortion)*0.5;
            m_channels_azimuth_mapped[i] = (curAngle - prevPortion*0.5) + m_channels_azimuth_width[i]*0.5;
        }
	}
    
    void Meter::process(const float* inputs)
    {
        if(m_ramp++ == m_vector_size)
        {
            m_ramp = 0;
            for(unsigned int i = 0; i < m_number_of_channels; i++)
            {
                m_channels_peaks[i] = fabs(inputs[i]);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_channels; i++)
            {
                if(fabs(inputs[i]) > m_channels_peaks[i])
                    m_channels_peaks[i] = fabs(inputs[i]);
            }
        }
    }
    
    void Meter::process(const double* inputs)
    {
        if(m_ramp++ == m_vector_size)
        {
            m_ramp = 0;
            for(unsigned int i = 0; i < m_number_of_channels; i++)
            {
                m_channels_peaks[i] = fabs(inputs[i]);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_channels; i++)
            {
                if(fabs(inputs[i]) > m_channels_peaks[i])
                    m_channels_peaks[i] = fabs(inputs[i]);
            }
        }
    }
    
    Meter::~Meter()
    {
        delete [] m_channels_peaks;
		delete [] m_channels_azimuth_width;
		delete [] m_channels_azimuth_mapped;
    }
}

