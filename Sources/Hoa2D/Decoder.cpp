/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder.h"

namespace Hoa2D
{
    Decoder::Decoder(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        setChannelsOffset(0.);
    }
    
    void Decoder::setChannelsOffset(double offset)
	{
        m_offset = wrap_twopi(offset);
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_channels_azimuth[i] = (double)i / (double)m_number_of_channels * CICM_2PI + m_offset;
            m_encoder->setAzimuth(m_channels_azimuth[i]);
            m_encoder->process(1., m_harmonics_vector);
            
            m_decoder_matrix[i * m_number_of_harmonics] = 0.5 / (double)(m_order + 1.);
            for(unsigned int j = 1; j < m_number_of_harmonics; j++)
            {
                m_decoder_matrix_float[i * m_number_of_harmonics + j] = m_decoder_matrix[i * m_number_of_harmonics + j] = m_harmonics_vector[j] / (double)(m_order + 1.);
            }
        }
	}

    void Decoder::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void Decoder::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	Decoder::~Decoder()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete m_encoder;
	}
}

