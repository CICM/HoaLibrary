/*
// Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa3DDecoder.h"

namespace Hoa3D
{
	Decoder::Decoder(long order, long numberOfLoudspeakers, bool shape) : Ambisonic(order)
	{
		m_decoder_matrix = NULL;
		m_loudspeakers_azimuth = NULL;
		m_loudspeakers_elevation = NULL;
		setNumberOfLoudspeakers(numberOfLoudspeakers, shape);
	}
	
	void Decoder::computeMatrices()
	{
		Encoder* encoder  = new Encoder(m_order);
		double* harmonics_vector = new double[m_number_of_harmonics];
		
		if(m_decoder_matrix)
			delete [] m_decoder_matrix;
		
		m_decoder_matrix = new double[m_number_of_outputs * m_number_of_harmonics];
		
		for (int i = 0; i < m_number_of_outputs; i++)
		{
			encoder->setAzimuth(m_loudspeakers_azimuth[i]);
			encoder->setElevation(m_loudspeakers_elevation[i]);
			encoder->process(0.5, harmonics_vector);
			
			for(int j = 0; j < m_number_of_harmonics; j++)
			{
				if(getHarmonicArgument(j) == 0)
				{
					cicm_set_mat_d(m_decoder_matrix, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
				}
				else
				{
					cicm_set_mat_d(m_decoder_matrix, i, j, m_number_of_harmonics, harmonics_vector[j]);
				}
			}
		}
	}
	
	void Decoder::setNumberOfLoudspeakers(long numberOfLoudspeakers, bool shape)
	{
		m_shape = shape;
		m_number_of_outputs = Tools::clip_min(numberOfLoudspeakers, 4);
		if(m_shape == Hoa_Full_Sphere)
		{
			if(numberOfLoudspeakers < m_number_of_harmonics)
				numberOfLoudspeakers = m_number_of_harmonics;
		}
		else
		{
			if(numberOfLoudspeakers < m_number_of_harmonics / 2)
				numberOfLoudspeakers = m_number_of_harmonics / 2;
		}
		
		if(m_loudspeakers_azimuth)
			delete [] m_loudspeakers_azimuth;
		if(m_loudspeakers_elevation)
			delete [] m_loudspeakers_elevation;
		
		m_loudspeakers_azimuth = new double[m_number_of_outputs];
		m_loudspeakers_elevation = new double[m_number_of_outputs];
		computeMatrices();
	}
	
	void Decoder::setLoudspeakerPosition(unsigned int index, double anAzimuth, double anElevation)
	{
		assert( index < m_number_of_outputs );
		m_loudspeakers_azimuth[index] = anAzimuth;
		m_loudspeakers_elevation[index] = anElevation;
		computeMatrices();
	}
	
	double Decoder::getLoudspeakerAzimuth(unsigned int index) const
	{
		assert( index < m_number_of_outputs );
		return m_loudspeakers_azimuth[index];
	}
	
	double Decoder::getLoudspeakerElevation(unsigned int index) const
	{
		assert( index < m_number_of_outputs );
		return m_loudspeakers_elevation[index];
	}
	
	void Decoder::process(const float* input, float* output)
	{
		//cicm_product_mat_vec_f(m_decoder_matrix_float, input, output, m_number_of_outputs, m_number_of_harmonics);
	}
	
	void Decoder::process(const double* input, double* output)
	{
		//cicm_product_mat_vec_d(m_decoder_matrix, input, output, m_number_of_outputs, m_number_of_harmonics);
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_outputs, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	Decoder::~Decoder()
	{
		cicm_free(m_decoder_matrix);
		
		if(m_loudspeakers_azimuth)
			delete [] m_loudspeakers_azimuth;
		if(m_loudspeakers_elevation)
			delete [] m_loudspeakers_elevation;
		
	}
	
} // end of namespace Hoa3D

