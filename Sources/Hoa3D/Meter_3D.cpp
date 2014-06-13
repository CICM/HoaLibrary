/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter_3D.h"

#define METER_ROW_NUMBER 181
#define METER_COLUMN_NUMBER 360

namespace Hoa3D
{
	int m_meter_matrix[METER_ROW_NUMBER][METER_COLUMN_NUMBER];

    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_channels_peaks		= new double[m_number_of_channels];

		m_channels_number_of_points	= new unsigned int[m_number_of_channels];
		m_channels_points_azimuth	= new double*[m_number_of_channels];
		m_channels_points_elevation	= new double*[m_number_of_channels];

		m_channels_number_of_points_top	= new unsigned int[m_number_of_channels];
		m_channels_points_azimuth_top	= new double*[m_number_of_channels];
		m_channels_points_elevation_top	= new double*[m_number_of_channels];

		m_channels_number_of_points_bottom	= new unsigned int[m_number_of_channels];
		m_channels_points_azimuth_bottom	= new double*[m_number_of_channels];
		m_channels_points_elevation_bottom	= new double*[m_number_of_channels];

		for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_channels_peaks[i] = 0.;
			m_channels_points_azimuth[i]	= new double[m_number_of_channels];
			m_channels_points_elevation[i]	= new double[m_number_of_channels];
			m_channels_points_azimuth_top[i]	= new double[m_number_of_channels];
			m_channels_points_elevation_top[i]	= new double[m_number_of_channels];
			m_channels_points_azimuth_bottom[i]	= new double[m_number_of_channels];
			m_channels_points_elevation_bottom[i]	= new double[m_number_of_channels];
			m_channels_number_of_points[i]	= 0;
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

    void Meter::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
		int indices[8];
		double dist1, dist2, azi, ele;
		int** channels_neighbours = new int*[m_number_of_channels];
		double* channels_abscissa = new double[m_number_of_channels];
		double* channels_ordinate = new double[m_number_of_channels];
		double* channels_azimuth = new double[m_number_of_channels];
		double* channels_elevation = new double[m_number_of_channels];

		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			channels_neighbours[i] = new int[m_number_of_channels];
			for(unsigned int j = 0; j < m_number_of_channels; j++)
				channels_neighbours[i][j] = -1;
		}

        Planewaves::setChannelPosition(index, azimuth, elevation);

		for(unsigned int i = 0; i < METER_ROW_NUMBER; i++)
        {
            for(unsigned int j = 0; j < METER_COLUMN_NUMBER; j++)
            {
                azi = (double)j / (double)METER_COLUMN_NUMBER * HOA_2PI;
                ele = (double)(i + 0.5) * HOA_PI / (double)(METER_ROW_NUMBER) - HOA_PI2;
				dist1 = distance_spherical(m_channels_azimuth[0], m_channels_elevation[0], azi, ele);
                m_meter_matrix[i][j] = 0;
                for(unsigned int k = 1; k < m_number_of_channels; k++)
                {
                    dist2 = distance_spherical(m_channels_azimuth[k], m_channels_elevation[k], azi, ele);
                    if(dist2 <= dist1)
                    {
                        dist1 = dist2;
                        m_meter_matrix[i][j] = k;
                    }
                }
            }
		}
		
		for(unsigned int i = 0; i < METER_ROW_NUMBER; i++)
        {
            for(unsigned int j = 0; j < METER_COLUMN_NUMBER; j++)
            {
				int index_central = m_meter_matrix[i][j];
				int j0 = j-1, j1 = j - 1, j2 = j -1, j3 = j, j4 = j + 1, j5 = j + 1, j6 = j + 1, j7 = j;
				int i0 = i + 1, i1 = i, i2 = i - 1, i3 = i - 1, i4 = i - 1, i5 = i, i6 = i + 1, i7 = i + 1;

				if(j == 0)
					j0 = j1 = j2 = METER_COLUMN_NUMBER-1;
				else if(j == METER_COLUMN_NUMBER - 1)
					j4 = j5 = j6 = 0;
				if(i == 0)
				{
					i2 = 0; i3 = 0; i4 = 0;
					j2 += METER_COLUMN_NUMBER * 0.5;
					j3 += METER_COLUMN_NUMBER * 0.5;
					j4 += METER_COLUMN_NUMBER * 0.5;
					if(j2 > METER_COLUMN_NUMBER - 1)
						j2 -= METER_COLUMN_NUMBER;
					if(j3 > METER_COLUMN_NUMBER - 1)
						j3 -= METER_COLUMN_NUMBER;
					if(j4 > METER_COLUMN_NUMBER - 1)
						j4 -= METER_COLUMN_NUMBER;
					//post("j2 %i, j3 %i , j4 %i", j2, j3, j4);
				}
				else if(i == METER_ROW_NUMBER - 1)
				{
					i0 = i; i6 = i; i7 = i;
					j0 += METER_COLUMN_NUMBER * 0.5;
					j6 += METER_COLUMN_NUMBER * 0.5;
					j7 += METER_COLUMN_NUMBER * 0.5;
					if(j0 > METER_COLUMN_NUMBER - 1)
						j0 -= METER_COLUMN_NUMBER;
					if(j6 > METER_COLUMN_NUMBER - 1)
						j6 -= METER_COLUMN_NUMBER;
					if(j7 > METER_COLUMN_NUMBER - 1)
						j7 -= METER_COLUMN_NUMBER;
					//post("j1 %i, j6 %i , j7 %i", j1, j6, j7);
				}
				
				indices[0] = m_meter_matrix[i0][j0];
				indices[1] = m_meter_matrix[i1][j1];
				indices[2] = m_meter_matrix[i2][j2];
				indices[3] = m_meter_matrix[i3][j3];
				indices[4] = m_meter_matrix[i4][j4];
				indices[5] = m_meter_matrix[i5][j5];
				indices[6] = m_meter_matrix[i6][j6];
				indices[7] = m_meter_matrix[i7][j7];
				
				for(int k = 0; k < 8; k++)
				{
					if(index_central != indices[k])
					{
						for(int l = 0; l < m_number_of_channels && channels_neighbours[index_central][l] != indices[k]; l++)
						{
							if(channels_neighbours[index_central][l] == -1)
							{
								channels_neighbours[index_central][l] = indices[k];
								break;
							}
						}

						for(int l = 0; l < m_number_of_channels && channels_neighbours[indices[k]][l] != index_central; l++)
						{
							if(channels_neighbours[indices[k]][l] == -1)
							{
								channels_neighbours[indices[k]][l] = index_central;
								break;
							}
						}
					}
				}
			}
		}
		
		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			m_channels_number_of_points[i] = 0;
			
			for(int j = 0; j < m_number_of_channels && channels_neighbours[i][j] != -1; j++, m_channels_number_of_points[i]++)
			{
				//if(i == 0)
				//post("neiborg %i %i",j, channels_neighbours[i][j]);
			}	
			//post("%i %i", (int)i, (int)m_channels_number_of_points[i]);
			
			for(int j = 0; j < m_channels_number_of_points[i]; j++)
			{
				channels_azimuth[j]	= center_azimuth(m_channels_azimuth[channels_neighbours[i][j]], m_channels_elevation[channels_neighbours[i][j]],m_channels_azimuth[i], m_channels_elevation[i]);
				channels_elevation[j]= center_elevation(m_channels_azimuth[channels_neighbours[i][j]], m_channels_elevation[channels_neighbours[i][j]],m_channels_azimuth[i], m_channels_elevation[i]);
				channels_abscissa[j] = abscissa(1., channels_azimuth[j], channels_elevation[j]);
				channels_ordinate[j] = ordinate(1., channels_azimuth[j], channels_elevation[j]);
			}
			
			memcpy(m_channels_points_azimuth[i], channels_azimuth, m_channels_number_of_points[i] * sizeof(double));
			vector_sort(m_channels_number_of_points[i], m_channels_points_azimuth[i]);
			for(int j = 0; j < m_channels_number_of_points[i]; j++)
			{

			}

			m_channels_points_azimuth[i][j];
			m_channels_points_elevation[i][j];
		}
		for(unsigned int i = 0; i < m_number_of_channels; i++)
		{
			delete [] channels_neighbours[i];
		}
		delete [] channels_neighbours;
		delete [] channels_abscissa;
		delete [] channels_ordinate;
		delete [] channels_azimuth;
		delete [] channels_elevation;
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
			delete [] m_channels_points_azimuth_top[i];
			delete [] m_channels_points_elevation_top[i];
			delete [] m_channels_points_azimuth_bottom[i];
			delete [] m_channels_points_elevation_bottom[i];
		}
		delete [] m_channels_number_of_points;
		delete [] m_channels_points_azimuth;
		delete [] m_channels_points_elevation;
		delete [] m_channels_points_azimuth_top;
		delete [] m_channels_points_elevation_top;
		delete [] m_channels_points_azimuth_bottom;
		delete [] m_channels_points_elevation_bottom;
    }
}

