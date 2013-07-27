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

#include "AmbisonicEncoder3D.h"

AmbisonicEncoder3D::AmbisonicEncoder3D(long anOrder, long aVectorSize, long aSamlingRate) : Ambisonic3D(anOrder, aVectorSize, aSamlingRate)
{
    m_number_of_inputs = 3;
    
    Cicm_Vector_Float_Malloc(m_normalization_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_normalization_double, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_azimuth_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_azimuth_double, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_elevation_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_elevation_double, m_number_of_harmonics);
    
    computeNormalization();
    setCoordinates(0. , 0.);
}

void AmbisonicEncoder3D::computeNormalization()
{
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        double factor = (2 * getHarmonicOrder(i) + 1) / (CICM_2PI * 2);
        m_normalization_double[i] = factor * Tools::factoriel(getHarmonicOrder(i) - getHarmonicIndex(i)) / Tools::factoriel(getHarmonicOrder(i) + getHarmonicIndex(i));
        if (getHarmonicIndex(i) != 0)
        {
            m_normalization_double[i] *= sqrt(2.);
        }
        m_normalization_float[i] = m_normalization_double[i];
    }
}

void AmbisonicEncoder3D::setCoordinates(double anAzimuth, double anElevation)
{
    setAzimuth(anAzimuth);
    setElevation(anElevation);
}

void AmbisonicEncoder3D::setAzimuth(double anAzimuth)
{
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        if(getHarmonicIndex(i) == 0)
            m_azimuth_double[i] = 1;
        else if(getHarmonicIndex(i) < 0)
            m_azimuth_double[i] = sin(-getHarmonicIndex(i) * anAzimuth);
        else
            m_azimuth_double[i] = cos(getHarmonicIndex(i) * anAzimuth);
        
        m_azimuth_float[i] = m_azimuth_double[i];
    }
}

void AmbisonicEncoder3D::setElevation(double anElevation)
{
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        double pmm = 1.0;
        if(abs(getHarmonicIndex(i)) > 0)
        {
            double somx2 = sqrt((1. - cos(anElevation)) * (1. + cos(anElevation)));
            double fact = 1.;
            for(int i = 1; i <= getHarmonicIndex(i); ++i)
            {
                pmm*= (-fact)*somx2;
                fact+= 2.0;
            }
        }
        if(getHarmonicOrder(i) == abs(getHarmonicIndex(i)))
        {
            m_elevation_double[i] = pmm;
        }
        else
        {
            double pmmpl = cos(anElevation) * (2. * abs(getHarmonicIndex(i)) + 1.) * pmm;
            if(getHarmonicOrder(i) == abs(getHarmonicIndex(i))+1)
                m_elevation_double[i] = pmmpl;
            else
            {
                double pll = 0.0;
                for(int ll = abs(getHarmonicIndex(i))+2; ll <= getHarmonicOrder(i); ++ll)
                {
                    pll = ((2. * ll - 1.) * cos(anElevation) * pmmpl - (ll + getHarmonicIndex(i) - 1.) * pmm) / (ll - abs(getHarmonicIndex(i)));
                    pmm = pmmpl;
                    pmmpl = pll;
                }
                m_elevation_double[i] = pll;
            }
            
        }
        m_elevation_float[i] = m_elevation_double[i];
	}
	
}


AmbisonicEncoder3D::~AmbisonicEncoder3D()
{
	Cicm_Free(m_normalization_float);
    Cicm_Free(m_normalization_double);
}