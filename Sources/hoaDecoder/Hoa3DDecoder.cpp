/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
		{
			for (int i=0; i<m_number_of_outputs; i++)
			{
				delete [] m_decoder_matrix[i];
				m_decoder_matrix[i] = NULL;
			}
			delete [] m_decoder_matrix;
			m_decoder_matrix = NULL;
		}
		
		m_decoder_matrix = new double*[m_number_of_outputs];
		for (int i=0; i<m_number_of_outputs; i++)
			m_decoder_matrix[i] = new double[m_number_of_harmonics];
		
		for (int i = 0; i < m_number_of_outputs; i++)
		{
			encoder->setAzimuth(m_loudspeakers_azimuth[i]);
			encoder->setElevation(m_loudspeakers_elevation[i]);
			encoder->process(0.5, harmonics_vector);
		}
		
		//cicm_malloc_mat_d(m_decoder_matrix, m_number_of_outputs, m_number_of_harmonics);
		/*
		 for(int i = 0; i < m_number_of_outputs; i++)
		 {
		 encoder->setAzimuth(m_loudspeakers_azimuth[i]);
		 encoder->setElevation(m_loudspeakers_elevation[i]);
		 encoder->process(0.5, harmonics_vector);
		 for(int j = 0; j < m_number_of_harmonics; j++)
		 {
		 if(getHarmonicIndex(i) == 0)
		 {
		 cicm_set_mat_d(m_decoder_matrix_double, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
		 }
		 else
		 {
		 cicm_set_mat_d(m_decoder_matrix_double, i, j, m_number_of_harmonics, harmonics_vector[j]);
		 }
		 }
		 }*/
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
	
	void Decoder::setLoudspeakerPosition(long anIndex, double anAzimuth, double anElevation)
	{
		m_loudspeakers_azimuth[(int)Tools::clip(anIndex, 0, m_number_of_outputs-1)] = anAzimuth;
		m_loudspeakers_elevation[(int)Tools::clip(anIndex, 0, m_number_of_outputs-1)] = anElevation;
		computeMatrices();
	}
	
	double Decoder::getLoudspeakerAzimuth(long anIndex)
	{
		return m_loudspeakers_azimuth[(int)Tools::clip(anIndex, 0, m_number_of_outputs-1)];
	}
	
	double Decoder::getLoudspeakerElevation(long anIndex)
	{
		return m_loudspeakers_elevation[(int)Tools::clip(anIndex, 0, m_number_of_outputs-1)];
	}
	
	void Decoder::process(const float input, float* output)
	{
		//cicm_product_mat_vec_f(m_decoder_matrix_float, input, output, m_number_of_outputs, m_number_of_harmonics);
	}
	
	void Decoder::process(const double input, double* output)
	{
		//cicm_product_mat_vec_d(m_decoder_matrix_double, anInput, output, m_number_of_outputs, m_number_of_harmonics);
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

