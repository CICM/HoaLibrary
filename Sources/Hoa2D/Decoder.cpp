/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder.h"

namespace Hoa2D
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Regular //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DecoderRegular::DecoderRegular(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        assert(numberOfChannels >= m_number_of_harmonics);
        
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        setChannelsOffset(0.);
    }
    
    void DecoderRegular::setChannelsOffset(double offset)
	{
        m_offset = wrap_twopi(offset);
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_encoder->setAzimuth(m_channels_azimuth[i] + m_offset);
            m_encoder->process(1., m_harmonics_vector);
            
            m_decoder_matrix_float[i * m_number_of_harmonics] = m_decoder_matrix[i * m_number_of_harmonics] = 0.5 / (double)(m_order + 1.);
            for(unsigned int j = 1; j < m_number_of_harmonics; j++)
            {
                m_decoder_matrix_float[i * m_number_of_harmonics + j] = m_decoder_matrix[i * m_number_of_harmonics + j] = m_harmonics_vector[j] / (double)(m_order + 1.);
            }
        }
	}

    void DecoderRegular::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderRegular::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	DecoderRegular::~DecoderRegular()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete m_encoder;
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Irregular //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DecoderIrregular::DecoderIrregular(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_sorted     = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_channels_azimuth_sorted   = new double[m_number_of_channels];
        m_encoder                   = new Encoder(m_order);
        setChannelPosition(0, 0.);
    }
    
    void DecoderIrregular::setChannelsPosition(double* azimuths)
    {
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            Planewaves::setChannelPosition(i, azimuths[i]);
        }
        setChannelPosition(0, azimuths[0]);
    }
    
    void DecoderIrregular::setChannelPosition(unsigned int index, double azimuth)
    {
        long    number_of_virutal_channels, channel_index1, channel_index2;
        double  current_distance, minimum_distance, angle, factor_index1, factor_index2, distance_index1, distance_index2;
        
        Planewaves::setChannelPosition(index, azimuth);
        
        // Sort the channels azimuth
        memcpy(m_channels_azimuth_sorted, m_channels_azimuth, m_number_of_channels * sizeof(double));
        std::sort(m_channels_azimuth_sorted, m_channels_azimuth_sorted+m_number_of_channels);
        
        // Get the minimum distance between the channels
        minimum_distance    = CICM_2PI + 1;
        current_distance    = distance_radian(m_channels_azimuth_sorted[0], m_channels_azimuth_sorted[m_number_of_channels-1]);
        if(current_distance < minimum_distance)
            minimum_distance    = current_distance;
        for(unsigned int i = 1; i < m_number_of_channels; i++)
        {
            current_distance  = distance_radian(m_channels_azimuth_sorted[i], m_channels_azimuth_sorted[i-1]);
            if(current_distance < minimum_distance)
                minimum_distance = current_distance;
        }
        
        // Get the optimal number of virtual channels
        // Always prefer the minimum number of channels + 1
        number_of_virutal_channels = (CICM_2PI / minimum_distance) + 1;
        if(number_of_virutal_channels < m_number_of_harmonics + 1)
        {
            number_of_virutal_channels = m_number_of_harmonics + 1;
        }
        
        // Compute the decoding matrix for sorted channels
        for(unsigned int i = 0; i < number_of_virutal_channels; i++)
        {
            // Get the pair of real channels corresponding to the virtual channel
            angle = (double)i / (double)number_of_virutal_channels * CICM_2PI;
            minimum_distance    = CICM_2PI + 1;
            for(unsigned int j = 0; j < m_number_of_channels; j++)
            {
                current_distance  = distance_radian(m_channels_azimuth_sorted[j], angle);
                if(current_distance < minimum_distance)
                {
                    minimum_distance = current_distance;
                    if(angle < m_channels_azimuth_sorted[j] && current_distance < CICM_2PI)
                    {
                        channel_index1 = j;
                        channel_index2 = j+1;
                        if(channel_index2 >= m_number_of_channels)
                            channel_index2 = 0;
                    }
                    else
                    {
                        channel_index1 = j;
                        channel_index2 = j-1;
                        if(channel_index2 < 0)
                            channel_index2 = m_number_of_channels - 1;
                    }
                }
            }
            
            // Get the factor for the pair of real channels
            distance_index1 = distance_radian(m_channels_azimuth_sorted[channel_index1], angle);
            distance_index2 = distance_radian(m_channels_azimuth_sorted[channel_index2], angle);
            factor_index1   = cos(distance_index1 / (distance_index1 + distance_index2) * CICM_PI);
            factor_index2   = cos(distance_index2 / (distance_index1 + distance_index2) * CICM_PI);
            
            // Get the harmonics coefficients for virtual channel
            m_encoder->setAzimuth(angle);
            m_encoder->process(1., m_harmonics_vector);
            
            m_decoder_matrix_sorted[channel_index1 * m_number_of_harmonics] = (0.5 / (double)(m_order + 1.)) * factor_index1;
            m_decoder_matrix_sorted[channel_index2 * m_number_of_harmonics] = (0.5 / (double)(m_order + 1.)) * factor_index2;
            for(unsigned int j = 1; j < m_number_of_harmonics; j++)
            {
                m_decoder_matrix_sorted[channel_index1 * m_number_of_harmonics + j] = (m_harmonics_vector[j] / (double)(m_order + 1.)) * factor_index1;
                m_decoder_matrix_sorted[channel_index2 * m_number_of_harmonics + j] = (m_harmonics_vector[j] / (double)(m_order + 1.)) * factor_index2;
            }
        }
        
        // Copy the decoding matrix for sorted channels to the decoding matrix for unsorted channels
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            for(unsigned int j = 0; j < m_number_of_channels; j++)
            {
                if(m_channels_azimuth[i] == m_channels_azimuth_sorted[j])
                {
                    for(unsigned int k = 0; k < m_number_of_harmonics; k++)
                    {
                        m_decoder_matrix_float[i * m_number_of_harmonics + k] = m_decoder_matrix[i * m_number_of_harmonics + k] = m_decoder_matrix_sorted[j * m_number_of_harmonics + k];
                    }
                }
            }
        }
    }
    
    void DecoderIrregular::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderIrregular::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	DecoderIrregular::~DecoderIrregular()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete [] m_decoder_matrix_sorted;
        delete [] m_channels_azimuth_sorted;
        delete m_encoder;
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Binaural //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

