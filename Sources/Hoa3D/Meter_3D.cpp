/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter_3D.h"

#define METER_ROW_NUMBER 361
#define METER_COLUMN_NUMBER 180

namespace Hoa3D
{
    int m_meter_matrix[METER_ROW_NUMBER][METER_COLUMN_NUMBER];
    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_channels_peaks		= new double[m_number_of_channels];
        
        m_points_top    = new std::vector<MeterPoint>[m_number_of_channels];
        m_points_bottom = new std::vector<MeterPoint>[m_number_of_channels];
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

    void Meter::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
        int indices[8];
        double azi, ele, dist1, dist2;
        Planewaves::setChannelPosition(index, azimuth, elevation);
        m_channels.clear();
        
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_points_top[i].clear();
            m_points_bottom[i].clear();
            m_channels.push_back(MeterPoint(m_channels_azimuth[i], m_channels_elevation[i]));
        }
        
        for(unsigned int i = METER_ROW_NUMBER; i < METER_ROW_NUMBER; i++)
        {
            for(unsigned int j = 0; j < METER_COLUMN_NUMBER; j++)
            {
                azi = (double)j / (double)METER_COLUMN_NUMBER * HOA_2PI;
                ele = (double)(i) * HOA_PI / (double)(METER_ROW_NUMBER - 1) - HOA_PI2;
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
				}
                
				indices[0] = m_meter_matrix[i0][j0];
				indices[1] = m_meter_matrix[i1][j1];
				indices[2] = m_meter_matrix[i2][j2];
				indices[3] = m_meter_matrix[i3][j3];
				indices[4] = m_meter_matrix[i4][j4];
				indices[5] = m_meter_matrix[i5][j5];
				indices[6] = m_meter_matrix[i6][j6];
				indices[7] = m_meter_matrix[i7][j7];
                
                azi = (double)j / (double)METER_COLUMN_NUMBER * HOA_2PI;
                ele = (double)(i) * HOA_PI / (double)(METER_ROW_NUMBER - 1) - HOA_PI2;
                MeterPoint pt = MeterPoint(azi, ele);
                pt.ref_x = m_channels[index_central].x;
                pt.ref_y = m_channels[index_central].y;
                
                if(i == (int)(METER_ROW_NUMBER * 0.5) - 1)
                {
                    m_points_bottom[index_central].push_back(pt);
                }
                else if(i == (int)(METER_ROW_NUMBER * 0.5))
                {
                    m_points_top[index_central].push_back(pt);
                }
                else
                {
                    for(int k = 0; k < 8; k++)
                    {
                        if(i < (int)(METER_ROW_NUMBER * 0.5) - 1 && index_central != indices[k])
                        {
                            m_points_bottom[index_central].push_back(pt);
                        }
                        else if(i > (int)(METER_ROW_NUMBER * 0.5) && index_central != indices[k])
                        {
                            m_points_top[index_central].push_back(pt);
                            break;
                        }
                    }
                }
				
			}
		}
        
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            int size = m_points_top[i].size();
            std::sort(m_points_top[i].begin(), m_points_top[i].end(), MeterPoint::compare);
            for(int j = 1; j < size - 2; j++)
            {
                if(MeterPoint::isBetween(m_points_top[i][j], m_points_top[i][j-1], m_points_top[i][j+1]))
                {
                    m_points_top[i].erase(m_points_top[i].begin()+j);
                    size--;
                }
            }
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
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_points_top[i].clear();
            m_points_bottom[i].clear();
        }
        delete [] m_points_top;
        delete [] m_points_bottom;
        m_channels.clear();
    }
}

