/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter.h"

namespace Hoa3D
{
    Meter::Meter(unsigned int numberOfLoudspeakers,  unsigned int numberOfRows, unsigned int numberOfColumns) : Planewaves(numberOfLoudspeakers)
    {
        m_ramp                  = 0;
        m_vector_size           = 256;
        m_number_of_rows        = numberOfRows;
        m_number_of_columns     = numberOfColumns;
        m_loudspeakers_peaks    = new double[m_number_of_loudspeakers];
        m_matrix                = new unsigned int[m_number_of_rows * m_number_of_columns];
        for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
        {
            m_loudspeakers_peaks[i] = 0.;
        }
        for(unsigned int i = 0; i < m_number_of_rows; i++)
        {
            for(unsigned int j = 0; j < m_number_of_columns; j++)
            {
                m_matrix[i * m_number_of_columns + j] = 0;
            }
        }
    }
    
    void Meter::setVectorSize(unsigned int vectorSize)
    {
        m_vector_size   = vectorSize;
        m_ramp          = 0;
    }
    
    void Meter::setLoudspeakerPosition(unsigned int index, double azimuth, double elevation)
	{
        double dist1, dist2;
        double x, y, z;
        double azi, ele;
        Planewaves::setLoudspeakerPosition(index, azimuth, elevation);
        
        for(unsigned int i = 0; i < m_number_of_rows; i++)
        {
            for(unsigned int j = 0; j < m_number_of_columns; j++)
            {
                azi = (double)j / (double)m_number_of_columns * CICM_2PI;
                ele = (double)i * CICM_PI / (double)(m_number_of_rows - 1) - CICM_PI2;
                x = abscissa(1., azi, ele);
                y = ordinate(1., azi, ele);
                z = height(1., azi, ele);
                dist1 = distance(x, y, z, getLoudspeakerAbscissa(0), getLoudspeakerOrdinate(0), getLoudspeakerHeight(0));
                m_matrix[i * m_number_of_columns + j] = 0;
                for(unsigned int k = 1; k < m_number_of_loudspeakers; k++)
                {
                    dist2 = distance(x, y, z, getLoudspeakerAbscissa(k), getLoudspeakerOrdinate(k), getLoudspeakerHeight(k));
                    if(dist2 <= dist1)
                    {
                        dist1 = dist2;
                        m_matrix[i * m_number_of_columns + j] = k;
                    }
                }
            }
        }        
	}
    
    void Meter::process(const float* inputs)
    {
        if(m_ramp++ == m_vector_size)
        {
            m_ramp = 0;
            for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            {
                m_loudspeakers_peaks[i] = fabs(inputs[i]);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            {
                if(fabs(inputs[i]) > m_loudspeakers_peaks[i])
                    m_loudspeakers_peaks[i] = fabs(inputs[i]);
            }
        }
    }
    
    void Meter::process(const double* inputs)
    {
        if(m_ramp++ == m_vector_size)
        {
            m_ramp = 0;
            for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            {
                m_loudspeakers_peaks[i] = fabs(inputs[i]);
            }
        }
        else
        {
            for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            {
                if(fabs(inputs[i]) > m_loudspeakers_peaks[i])
                    m_loudspeakers_peaks[i] = fabs(inputs[i]);
            }
        }
    }
    
    Meter::~Meter()
    {
        delete [] m_loudspeakers_peaks;
        delete [] m_matrix;
    }
}

