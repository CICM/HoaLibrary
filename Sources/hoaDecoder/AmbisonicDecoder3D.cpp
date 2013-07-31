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

AmbisonicDecoder3D::AmbisonicDecoder3D(long anOrder, long aNumberOfLoudspeakers, long aVectorSize, long aSamlingRate) : Ambisonic3D(anOrder, aVectorSize, aSamlingRate)
{
    if (aNumberOfLoudspeakers < m_number_of_harmonics)
        aNumberOfLoudspeakers = m_number_of_harmonics;
    m_number_of_outputs = m_number_of_harmonics;
    
    m_decoder_matrix = NULL;
    
    computeMatrices();
}

void AmbisonicDecoder3D::computeMatrices()
{
    AmbisonicEncoder3D* encoder  = new AmbisonicEncoder3D(m_order);
    double* harmonics_vector = new double[m_number_of_harmonics];
    if(m_decoder_matrix)
        Cicm_Free(m_decoder_matrix);
    Cicm_Matrix_Double_Malloc(m_decoder_matrix, m_number_of_outputs, m_number_of_harmonics);
    for(int  i = 0; i < m_number_of_outputs; i++)
    {
        double azimuth  = 0;
        double elevation = 0;
        encoder->processAzimtuhElevation(harmonics_vector, azimuth, elevation);
        for(int j = 0; j < m_number_of_harmonics; j++)
        {
            Cicm_Matrix_Double_Set(m_decoder_matrix, i, j, m_number_of_harmonics, harmonics_vector[j]);
        }
    }
}

AmbisonicDecoder3D::~AmbisonicDecoder3D()
{
    Cicm_Free(m_decoder_matrix);
}