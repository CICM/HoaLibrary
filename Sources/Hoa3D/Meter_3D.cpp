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

		for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_channels_peaks[i] = 0.;			
        }
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

	void vector_sort_coordinates(unsigned int size, double* azimuths, double* elevations, double azymuth, double elevation)
	{
        double* abs	= new double[size];
		double* ord	= new double[size];
		double* azi	= new double[size];
		double* azb	= new double[size];
		double* cpa	= new double[size];
		double* cpe	= new double[size];
		int* index	= new int[size];
		double g_x = abscissa(1, azymuth, elevation), g_y = ordinate(1, azymuth, elevation);
		memcpy(cpa, azimuths, size * sizeof(double));
		memcpy(cpe, elevations, size * sizeof(double));
		//post("********");
		for(unsigned int i = 0; i < size; i++)
		{
			abs[i] = abscissa(1., azimuths[i], elevations[i]);
			ord[i] = ordinate(1., azimuths[i], elevations[i]) - g_y;
			if(elevation >= 0 && elevations[i] < 0.)
			{
				if(abs[i] < 0)
					abs[i] *= -1;
				abs[i] += 2.;
			}
			else if(elevation < 0 && elevations[i] > 0.)
			{
				if(abs[i] > 0)
					abs[i] *= -1;
				abs[i] += 2.;
			}
			abs[i] -= g_x;
			
		}
		double max = -100;
		int inc = size - 1;
		for(unsigned int i = 0; i < size; i++)
		{
			azi[i] = wrap_twopi(azimuth(abs[i], ord[i]));
			if(azi[i] > max)
			{
				max = azi[i];
				index[inc] = i;
			}
			
		}
		memcpy(azb, azi, size * sizeof(double));
		azi[index[inc]] = -100;
		inc--;
		while(inc > -1)
		{
			max = -1;
			for(unsigned int j = 0; j < size; j++)
			{
				if(azi[j] > max)
				{
					max = azi[j];
					index[inc] = j;
				}
			}
			azi[index[inc]] = -100;
			inc--;
		}
		//for(unsigned int i = 0; i < size; i++)
		//	post("abs %f ord %f azi %f", abs[index[i]], ord[index[i]], azb[index[i]]);
		
		for(unsigned int i = 0; i < size; i++)
		{
			azimuths[i] = cpa[index[i]];
			elevations[i] = cpe[index[i]];
		}
		
		delete [] abs;
		delete [] ord;
		delete [] azi;
		delete [] cpa;
		delete [] cpe;
		delete [] index;

	}

    void Meter::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
        Planewaves::setChannelPosition(index, azimuth, elevation);

		m_vertices.clear();
		m_triangles.clear();

		for(int i = 0; i < m_number_of_channels; i++)
		{
			double abs  = abscissa(1., m_channels_azimuth[i], m_channels_elevation[i]);
			double ord  = ordinate(1., m_channels_azimuth[i], m_channels_elevation[i]);
			m_vertices.insert(vertex((float)abs, (float)ord));
		}

		Delaunay d;
		d.Triangulate(m_vertices, m_triangles);
		post("n triangles %i", m_triangles.size());
		for(int i = 0; i < m_triangles.size(); i++)
		{
			post("%i ", i);
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
    }
}

