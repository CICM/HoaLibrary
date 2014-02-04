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

#ifndef DEF_AMBISONICDECODER3D
#define DEF_AMBISONICDECODER3D

#include "../hoaEncoder/AmbisonicEncoder3D.h"
#include "../HoaAmbisonics/Ambisonic3D.h"

enum
{
    Hoa_Half_Sphere = 0,
    Hoa_Full_Sphere,
};

class AmbisonicDecoder3D : public Ambisonic3D
{
	
private:
    bool                m_shape;
    cicm_matrix_double  m_decoder_matrix_double;
    cicm_matrix_float   m_decoder_matrix_float;
    
    cicm_matrix_double  m_harmonics_vector_double;
    cicm_vector_float   m_harmonics_vector_float;
    
    cicm_matrix_double  m_outputs_vector_double;
    cicm_vector_float   m_outputs_vector_float;
    
    cicm_matrix_double  m_loudspeakers_azimuth;
    cicm_matrix_double  m_loudspeakers_elevation;
    void computeMatrices();
public:
	AmbisonicDecoder3D(long anOrder = 1, long aNumberOfLoudspeakers = 8, bool aShape = Hoa_Full_Sphere, long aVectorSize = 2, long aSamlingRate = 44100);
    
    void setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool aShape = Hoa_Full_Sphere);
    void setLoudspeakerPosition(long anIndex, double anAzimuth, double anElevation);
    double getLoudspeakerAzimuth(long anIndex);
    double getLoudspeakerElevation(long anIndex);
    
	~AmbisonicDecoder3D();
    
    inline void process(const float* anInput, float* anOutput)
    {
       cicm_product_mat_vec_f(m_decoder_matrix_float, anInput, anOutput, m_number_of_outputs, m_number_of_harmonics);
    }
    
    inline void process(const double* anInput, double* anOutput)
    {
        cicm_product_mat_vec_d(m_decoder_matrix_double, anInput, anOutput, m_number_of_outputs, m_number_of_harmonics);
    }
};
#endif