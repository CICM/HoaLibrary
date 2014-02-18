/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder.h"

namespace Hoa3D
{
	Decoder::Decoder(unsigned int order, unsigned int numberOfLoudspeakers) : Ambisonic(order)
	{
        m_number_of_loudspeakers    = clip_min(numberOfLoudspeakers, 4);
		m_loudspeakers_azimuth      = new double[m_number_of_loudspeakers];
		m_loudspeakers_elevation    = new double[m_number_of_loudspeakers];
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_loudspeakers * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_loudspeakers * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
	}
	
	void Decoder::setLoudspeakerPosition(unsigned int index, double anAzimuth, double anElevation)
	{
		assert( index < m_number_of_loudspeakers );
		m_loudspeakers_azimuth[index] = anAzimuth;
		m_loudspeakers_elevation[index] = anElevation;
        
        m_encoder->setAzimuth(m_loudspeakers_azimuth[index]);
        m_encoder->setElevation(m_loudspeakers_elevation[index]);
        m_encoder->process(1., m_harmonics_vector);
        
        //m_decoder_matrix[index * m_number_of_harmonics] = 1. / (double)(m_order+1.);
		//m_decoder_matrix[index * m_number_of_harmonics] = 1. / (double)((m_order+1.)*(m_order+1.));
        for(unsigned int j = 0; j < m_number_of_harmonics; j++)
        {
            m_decoder_matrix_float[index * m_number_of_harmonics + j] = m_decoder_matrix[index * m_number_of_harmonics + j] = m_harmonics_vector[j];
        }
	}
	
	double Decoder::getLoudspeakerAzimuth(unsigned int index) const
	{
		assert( index < m_number_of_loudspeakers );
		return m_loudspeakers_azimuth[index];
	}
	
	double Decoder::getLoudspeakerElevation(unsigned int index) const
	{
		assert( index < m_number_of_loudspeakers );
		return m_loudspeakers_elevation[index];
	}
	
	void Decoder::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_loudspeakers, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void Decoder::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_loudspeakers, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	Decoder::~Decoder()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete [] m_loudspeakers_azimuth;
		delete [] m_loudspeakers_elevation;
        delete m_encoder;
	}
	
}

