/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder.h"

namespace Hoa2D
{
    Decoder::Decoder(unsigned int order, unsigned int numberOfLoudspeakers) : Ambisonic(order)
    {
        m_number_of_outputs         = Tools::clip_min(numberOfLoudspeakers, 1);
		m_loudspeakers_azimuth      = new double[m_number_of_outputs];
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_outputs * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_outputs * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        
        for(int i = 0; i < m_number_of_outputs; i++)
        {
            setLoudspeakerPosition(i, (double)i / (double)m_number_of_outputs * CICM_2PI);
        }
    }
    
    void Decoder::setLoudspeakerPosition(unsigned int index, double anAzimuth)
	{
		assert( index < m_number_of_outputs );
		m_loudspeakers_azimuth[index] = Tools::radian_wrap(anAzimuth);
        
        m_encoder->setAzimuth(m_loudspeakers_azimuth[index]);
        m_encoder->process(1., m_harmonics_vector);
        
        m_decoder_matrix[index * m_number_of_harmonics] = 0.5 / (double)(m_order+1.);
        for(int j = 1; j < m_number_of_harmonics; j++)
        {
            m_decoder_matrix_float[index * m_number_of_harmonics + j] = m_decoder_matrix[index * m_number_of_harmonics + j] = m_harmonics_vector[j] / (double)(m_order+1.);
        }
	}
    
    double Decoder::getLoudspeakerAzimuth(unsigned int index) const
	{
		assert( index < m_number_of_outputs );
		return m_loudspeakers_azimuth[index];
	}

    void Decoder::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_outputs, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void Decoder::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_outputs, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	Decoder::~Decoder()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete [] m_loudspeakers_azimuth;
        delete m_encoder;
	}
}

