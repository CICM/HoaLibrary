/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter_3D.h"

#define METER_ROW_NUMBER 361
#define METER_COLUMN_NUMBER 721

namespace Hoa3D
{
    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_channels_peaks		= new double[m_number_of_channels];
		m_delaunay				= new Delaunay();

		for(unsigned int i = 0; i < m_number_of_channels; i++)
            m_channels_peaks[i] = 0.;			
		setChannelPosition(0, m_channels_azimuth[0], m_channels_elevation[0]);
    }
    
    void Meter::setVectorSize(unsigned int vectorSize)
    {
        m_vector_size   = vectorSize;
        m_ramp          = 0;
    }
    
	void Meter::setChannelsPosition(double* azimuths, double* elevations)
	{
		Planewaves::setChannelsPosition(azimuths, elevations);
		setChannelPosition(0, m_channels_azimuth[0], m_channels_elevation[0]);
	}

    void Meter::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
        Planewaves::setChannelPosition(index, azimuth, elevation);
		m_delaunay->clear();
		for(unsigned int i = 0; i < m_number_of_channels; i++)
			m_delaunay->addPoint(m_channels_azimuth[i], m_channels_elevation[i]);
		m_delaunay->perform();
		post("n circles %i", m_delaunay->getNumberOfCircles());
		/*
		
		m_delaunay->perform();
		
		for(unsigned int i = 0; i < m_delaunay->getNumberOfTriangles(); i++)
		{
			post("triangles %i", i);
			for(unsigned int j = 0; j < 3; j++)
			{
				post("point %i abs", m_delaunay->getTrianglePointAbscissa(i, j));
				post("point %i ord",  m_delaunay->getTrianglePointOrdinate(i, j));
			}
		}*/
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
		delete m_delaunay;
    }
}

