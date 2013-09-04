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

#include "AmbisonicDecoder3D.h"

AmbisonicDecoder3D::AmbisonicDecoder3D(long anOrder, long aNumberOfLoudspeakers, bool aShape, long aVectorSize, long aSamlingRate) : Ambisonic3D(anOrder, aVectorSize, aSamlingRate)
{    
    m_decoder_matrix_double = NULL;
    m_decoder_matrix_float = NULL;
    m_outputs_vector_double = NULL;
    m_outputs_vector_float = NULL;
    
    cicm_malloc_vec_d(m_harmonics_vector_double, m_number_of_harmonics);
    cicm_malloc_vec_f(m_harmonics_vector_float, m_number_of_harmonics);

    setNumberOfLoudspeakers(aNumberOfLoudspeakers, aShape);
}

void AmbisonicDecoder3D::computeMatrices()
{
    AmbisonicEncoder3D* encoder  = new AmbisonicEncoder3D(m_order);
    double* harmonics_vector = new double[m_number_of_harmonics];
    
    if(m_decoder_matrix_double)
        cicm_free(m_decoder_matrix_double);
    if(m_decoder_matrix_float)
        cicm_free(m_decoder_matrix_float);
    
    cicm_malloc_mat_d(m_decoder_matrix_double, m_number_of_outputs, m_number_of_harmonics);
    cicm_malloc_mat_f(m_decoder_matrix_float, m_number_of_outputs, m_number_of_harmonics);
    
    for(int i = 0; i < m_number_of_outputs; i++)
    {
        double azimuth  = (double)i / (double)m_number_of_outputs * CICM_2PI;
        double elevation = (double)i / (double)m_number_of_outputs * CICM_2PI;
        encoder->processAzimtuhElevation(0.5, harmonics_vector, azimuth, elevation);
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
            if(getHarmonicIndex(i) == 0)
            {
                cicm_set_mat_d(m_decoder_matrix_double, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
                cicm_set_mat_f(m_decoder_matrix_float, i, j, m_number_of_harmonics, 0.5 / (double)(m_order+1.));
            }
            else
            {
                cicm_set_mat_d(m_decoder_matrix_double, i, j, m_number_of_harmonics, harmonics_vector[j]);
                cicm_set_mat_f(m_decoder_matrix_float, i, j, m_number_of_harmonics, harmonics_vector[j]);
            }
        }
    }
}

void AmbisonicDecoder3D::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool aShape)
{
    m_shape = Tools::clip(aShape, Hoa_Half_Sphere, Hoa_Full_Sphere);
    aNumberOfLoudspeakers = Tools::clip_min(aNumberOfLoudspeakers, 4);
    if(m_shape == Hoa_Full_Sphere)
    {
        if(aNumberOfLoudspeakers < m_number_of_harmonics)
            aNumberOfLoudspeakers = m_number_of_harmonics;
    }
    else
    {
        if(aNumberOfLoudspeakers < m_number_of_harmonics / 2)
            aNumberOfLoudspeakers = m_number_of_harmonics / 2;
    }
    m_number_of_outputs = m_number_of_harmonics;
    if(m_outputs_vector_double)
        cicm_free(m_outputs_vector_double);
    if(m_outputs_vector_float)
        cicm_free(m_outputs_vector_float);
    
    cicm_malloc_vec_d(m_outputs_vector_double, m_number_of_outputs);
    cicm_malloc_vec_f(m_outputs_vector_float, m_number_of_outputs);
    computeMatrices();
}

void AmbisonicDecoder3D::setLoudspeakerPosition(long anIndex, double anAzimuth, double anElevation)
{
    ;
}

AmbisonicDecoder3D::~AmbisonicDecoder3D()
{
    cicm_free(m_decoder_matrix_double);
    cicm_free(m_decoder_matrix_float);
    cicm_free(m_harmonics_vector_double);
    cicm_free(m_harmonics_vector_float);
    cicm_free(m_outputs_vector_double);
    cicm_free(m_outputs_vector_float);
    
}



