/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter_3D.h"

#define METER_ROW_NUMBER 180
#define METER_COLUMN_NUMBER 360

namespace Hoa3D
{
	int m_meter_matrix[METER_ROW_NUMBER * METER_COLUMN_NUMBER];

    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_channels_peaks		= new double[m_number_of_channels];

		m_channels_number_of_points	= new unsigned int[m_number_of_channels];
		m_channels_points_azimuth	= new double*[m_number_of_channels];
		m_channels_points_elevation	= new double*[m_number_of_channels];

		for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_channels_peaks[i] = 0.;
			m_channels_points_azimuth[i]	= new double[m_number_of_channels];
			m_channels_points_elevation[i]	= new double[m_number_of_channels];
			m_channels_number_of_points		= 0;
        }
    }
    
    void Meter::setVectorSize(unsigned int vectorSize)
    {
        m_vector_size   = vectorSize;
        m_ramp          = 0;
    }
    
    void Meter::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
		int indices[8];
		double dist1, dist2, azi, ele;
		int* channels_neighbours = new int[m_number_of_channels * m_number_of_channels];
		
		for(unsigned int i = 0; i < m_number_of_channels * m_number_of_channels; i++)
			channels_neighbours[i] = -1;

        Planewaves::setChannelPosition(index, azimuth, elevation);

		for(unsigned int i = 0; i < METER_ROW_NUMBER; i++)
        {
            for(unsigned int j = 0; j < METER_COLUMN_NUMBER; j++)
            {
                azi = (double)j / (double)METER_COLUMN_NUMBER * HOA_2PI;
                ele = (double)i * HOA_PI / (double)(METER_ROW_NUMBER - 1) - HOA_PI2;
				dist1 = distance_spherical(m_channels_azimuth[0], m_channels_elevation[0], azi, ele);
                m_meter_matrix[i * METER_COLUMN_NUMBER + j] = 0;
                for(unsigned int k = 1; k < m_number_of_channels; k++)
                {
                    dist2 = distance_spherical(m_channels_azimuth[k], m_channels_elevation[k], azi, ele);
                    if(dist2 <= dist1)
                    {
                        dist1 = dist2;
                        m_meter_matrix[i * METER_COLUMN_NUMBER + j] = k;
                    }
                }
            }
		}

		for(unsigned int i = 1; i < METER_ROW_NUMBER - 1; i++)
        {
            for(unsigned int j = 0; j < METER_COLUMN_NUMBER; j++)
            {
				int index_central = m_meter_matrix[i * METER_COLUMN_NUMBER + j];
				if(j == 0)
				{
					indices[0] = m_meter_matrix[(i + 2) * METER_COLUMN_NUMBER- 1];
					indices[1] = m_meter_matrix[(i + 1) * METER_COLUMN_NUMBER - 1];
					indices[2] = m_meter_matrix[i * METER_COLUMN_NUMBER - 1];
				}
				else
				{
					indices[0] = m_meter_matrix[(i + 1) * METER_COLUMN_NUMBER + j - 1];
					indices[1] = m_meter_matrix[i * METER_COLUMN_NUMBER + j - 1];
					indices[2] = m_meter_matrix[(i - 1) * METER_COLUMN_NUMBER + j - 1];
				}
				if(j == METER_COLUMN_NUMBER - 1)
				{
					indices[4] = m_meter_matrix[(i + 1) * METER_COLUMN_NUMBER];
					indices[5] = m_meter_matrix[i * METER_COLUMN_NUMBER];
					indices[6] = m_meter_matrix[(i - 1) * METER_COLUMN_NUMBER];
				}
				else
				{
					indices[4] = m_meter_matrix[(i + 1) * METER_COLUMN_NUMBER + j + 1];
					indices[5] = m_meter_matrix[i * METER_COLUMN_NUMBER + j + 1];
					indices[6] = m_meter_matrix[(i - 1) * METER_COLUMN_NUMBER + j + 1];
				}
				indices[3] = m_meter_matrix[(i - 1) * METER_COLUMN_NUMBER + j];
				indices[7] = m_meter_matrix[(i + 1) * METER_COLUMN_NUMBER + j];

				for(int k = 0; k < 8; k++)
				{
					if(index_central != indices[i])
					{
						for(int l = 0; l < m_number_of_channels; l++)
						{
							if(channels_neighbours[index_central * m_number_of_channels + l] == indices[i])
								break;
							else if(channels_neighbours[index_central * m_number_of_channels + l] == -1)
							{
								channels_neighbours[index_central * m_number_of_channels + l] = indices[i];
							}
						}

						for(int l = 0; l < m_number_of_channels; l++)
						{
							if(channels_neighbours[indices[i] * m_number_of_channels + l] == index_central)
								break;
							else if(channels_neighbours[indices[i] * m_number_of_channels + l] == -1)
							{
								channels_neighbours[indices[i] * m_number_of_channels + l] = index_central;
							}
						}
					}
				}
			}
		}

		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			m_channels_number_of_points[i] = 0;
			for(int j = 0; j < m_number_of_channels; j++)
			{
				if(channels_neighbours[i * m_number_of_channels + j] == -1)
					break;
				m_channels_number_of_points[i]++;
			}
			delete [] m_channels_points_azimuth[i];
			delete [] m_channels_points_elevation[i];
			m_channels_points_azimuth[i]	= new double[m_channels_number_of_points[i]];
			m_channels_points_elevation[i]	= new double[m_channels_number_of_points[i]];

			for(int j = 0; j < m_channels_number_of_points[i]; j++)
			{
				m_channels_points_azimuth[i][j]		= center_azimuth(m_channels_azimuth[channels_neighbours[j]], m_channels_elevation[channels_neighbours[j]],m_channels_azimuth[i], m_channels_elevation[i]);
				m_channels_points_elevation[i][j]	= center_elevation(m_channels_azimuth[channels_neighbours[j]], m_channels_elevation[channels_neighbours[j]],m_channels_azimuth[i], m_channels_elevation[i]);
			}
		}
		
		delete [] channels_neighbours;
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
		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			delete [] m_channels_points_azimuth[i];
			delete [] m_channels_points_elevation[i];
		}
		delete [] m_channels_number_of_points;
		delete [] m_channels_points_azimuth;
		delete [] m_channels_points_elevation;
    }
}

