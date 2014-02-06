/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa3DDecoderB.h"

namespace Hoa3D
{
	DecoderB::DecoderB(unsigned int order, unsigned int numberOfLoudspeakers) : Ambisonic(order)
	{
        m_number_of_outputs         = Tools::clip_min(numberOfLoudspeakers, 4);
		m_loudspeakers_azimuth      = new double[m_number_of_outputs];
		m_loudspeakers_elevation    = new double[m_number_of_outputs];
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_outputs * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_outputs * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
	}
	
	void DecoderB::setLoudspeakerPosition(unsigned int index, double anAzimuth, double anElevation)
	{
		assert( index < m_number_of_outputs );
		m_loudspeakers_azimuth[index] = anAzimuth;
		m_loudspeakers_elevation[index] = anElevation;
        
        m_encoder->setAzimuth(m_loudspeakers_azimuth[index]);
        m_encoder->setElevation(m_loudspeakers_elevation[index]);
        m_encoder->process(0.5, m_harmonics_vector);
        
        m_decoder_matrix[index * m_number_of_harmonics] = 0.5 / (double)(m_order+1.);
        for(int j = 1; j < m_number_of_harmonics; j++)
        {
            m_decoder_matrix_float[index * m_number_of_harmonics + j] = m_decoder_matrix[index * m_number_of_harmonics + j] = m_harmonics_vector[j];
        }
	}
	
	double DecoderB::getLoudspeakerAzimuth(unsigned int index) const
	{
		assert( index < m_number_of_outputs );
		return m_loudspeakers_azimuth[index];
	}
	
	double DecoderB::getLoudspeakerElevation(unsigned int index) const
	{
		assert( index < m_number_of_outputs );
		return m_loudspeakers_elevation[index];
	}
	
	void DecoderB::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_outputs, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderB::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_outputs, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	DecoderB::~DecoderB()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete [] m_loudspeakers_azimuth;
		delete [] m_loudspeakers_elevation;
        delete m_encoder;
	}
	
}

