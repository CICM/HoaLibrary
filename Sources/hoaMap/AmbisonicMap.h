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

#ifndef DEF_AMBISONICMAP
#define DEF_AMBISONICMAP

#include "../HoaAmbisonics/Ambisonics.h"
#include "../hoaEncoder/AmbisonicEncoder.h"
#include "../hoaWider/AmbisonicWider.h"

class AmbisonicMap : public Ambisonics
{
private:
    AmbisonicEncoder*  m_encoder;
    AmbisonicWider*    m_wider;
    
    CicmLine*           m_line_one;
    CicmLine*           m_line_two;
    
    CicmLine*           m_line_thr;
    CicmLine*           m_line_fou;
    
    double              m_azimuth;
    double              m_radius;
    double              m_abscissa;
    double              m_ordinate;
    
    double              m_wide;
    double              m_gain;
    
    Cicm_Vector_Double  m_gains_double;
    Cicm_Vector_Float   m_gains_float;
    
    Cicm_Vector_Double  m_harmonics_double;
    Cicm_Vector_Float   m_harmonics_float;
    
    Cicm_Vector_Double*  m_harmonics_matrix_double;
    Cicm_Vector_Float*   m_harmonics_matrix_float;
    
    Cicm_Vector_Double  m_radius_double;
    Cicm_Vector_Float   m_radius_float;
    Cicm_Vector_Double  m_azimuth_double;
    Cicm_Vector_Float   m_azimuth_float;
    Cicm_Vector_Double  m_abscissa_double;
    Cicm_Vector_Float   m_abscissa_float;
    Cicm_Vector_Double  m_ordinate_double;
    Cicm_Vector_Float   m_ordinate_float;
    
    Cicm_Vector_Float	m_vector_float;
    Cicm_Vector_Double	m_vector_double;
    
public:
	AmbisonicMap(long anOrder = 1, long aRampSample = 4410, long aVectorSize = 0, long aSamplingRate = 44100);
    
    void setCoordinatesPolar(double aRadius, double anAzimuth);
    void setCoordinatesRadius(double aRadius);
    void setCoordinatesAzimuth(double anAzimuth);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
    void setCoordinatesAbscissa(double anAbscissa);
    void setCoordinatesOrdinate(double anOrdinate);
    
    void setCoordinatesPolarLine(double aRadius, double anAzimuth);
    void setCoordinatesRadiusLine(double aRadius);
    void setCoordinatesAzimuthLine(double anAzimuth);
    void setCoordinatesCartesianLine(double anAbscissa, double anOrdinate);
    void setCoordinatesAbscissaLine(double anAbscissa);
    void setCoordinatesOrdinateLine(double anOrdinate);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    void setRamp(long aNumberOfSample);
    long getRamp();
    
	~AmbisonicMap();
    
    /************************************************************************************/
    /*********************************** MULTISOURCES ***********************************/
    /************************************************************************************/
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const float input, float* outputs)
	{
        setCoordinatesPolar(m_line_one->process(), m_line_two->process());        
		m_encoder->process(input * m_gain, outputs, m_azimuth);
        m_wider->process(outputs);
	}
    
    inline void process(const double input, double* outputs)
	{
        setCoordinatesPolar(m_line_one->process(), m_line_two->process());
		m_encoder->process(input * m_gain, outputs, m_azimuth);
        m_wider->process(outputs);
	}
    
    inline void processAdd(const float input, float* outputs)
	{
        setCoordinatesPolar(m_line_one->process(), m_line_two->process());  
		m_encoder->process(input * m_gain, m_harmonics_float, m_azimuth);
        m_wider->process(m_harmonics_float);
        Cicm_Vector_Float_Add(m_harmonics_float, outputs, m_number_of_harmonics);
	}
    
    inline void processAdd(const double input, double* outputs)
	{
        setCoordinatesPolar(m_line_one->process(), m_line_two->process());
        m_encoder->process(input * m_gain, m_harmonics_float, m_azimuth);
        m_wider->process(m_harmonics_float);
        Cicm_Vector_Double_Add(m_harmonics_double, outputs, m_number_of_harmonics);
	}
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const float* inputs, float** outputs)
	{
        m_line_one->process(m_radius_float);
        m_line_two->process(m_azimuth_float);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_float[i] > 1.)
                m_vector_float[i] = inputs[i] / (m_radius_float[i] * m_radius_float[i]);
            else
                m_vector_float[i] = inputs[i];
        }
		m_encoder->process(m_vector_float, outputs, m_azimuth_float);
        m_wider->process(outputs, m_radius_float);
	}
    
    inline void process(const double* inputs, double** outputs)
	{
        
        m_line_one->process(m_radius_double);
        m_line_two->process(m_azimuth_double);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_double[i] > 1.)
                m_vector_double[i] = inputs[i] / (m_radius_double[i] * m_radius_double[i]);
            else
                m_vector_double[i] = inputs[i];
        }
        
		m_encoder->process(m_vector_double, outputs, m_azimuth_double);
        m_wider->process(outputs, m_radius_double);
	}
    
    inline void processAdd(const float* inputs, float** outputs)
	{
        m_line_one->process(m_radius_float);
        m_line_two->process(m_azimuth_float);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_float[i] > 1.)
                m_vector_float[i] = inputs[i] / (m_radius_float[i] * m_radius_float[i]);
            else
                m_vector_float[i] = inputs[i];
        }
		m_encoder->process(m_vector_float, m_harmonics_matrix_float, m_azimuth_float);
        m_wider->process(m_harmonics_matrix_float, m_radius_float);
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Float_Add(m_harmonics_matrix_float[i], outputs[i], m_vector_size);
        }
	}
    
    inline void processAdd(const double* inputs, double** outputs)
	{
        m_line_one->process(m_radius_double);
        m_line_two->process(m_azimuth_double);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_double[i] > 1.)
                m_vector_double[i] = inputs[i] / (m_radius_double[i] * m_radius_double[i]);
            else
                m_vector_double[i] = inputs[i];
        }
		m_encoder->process(m_vector_double, m_harmonics_matrix_double, m_azimuth_double);
        m_wider->process(m_harmonics_matrix_double, m_radius_double);
        
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            Cicm_Vector_Double_Add(m_harmonics_matrix_double[i], outputs[i], m_vector_size);
        }
	}
    
    /************************************************************************************/
    /************************************ ONESOURCES ************************************/
    /************************************************************************************/
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void processPolar(float* aInputs, float** aOutputs, float* aRadius, float* anAnzimuth)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(aRadius[i] > 1.)
                aInputs[i] /= aRadius[i] * aRadius[i];
        }
		m_encoder->process(aInputs, aOutputs, anAnzimuth);
        m_wider->process(aOutputs, aOutputs, aRadius);
        m_line_one->setCoefficientDirect(aRadius[m_vector_size-1]);
        m_line_two->setCoefficientAngleDirect(anAnzimuth[m_vector_size-1]);
	}
    
    inline void processRadius(float* aInputs, float** aOutputs, float* aRadius)
	{
        m_line_two->process(m_azimuth_float);
		for(int i = 0; i < m_vector_size; i++)
        {
            if(aRadius[i] > 1.)
                aInputs[i] /= aRadius[i] * aRadius[i];
        }
        m_encoder->process(aInputs, aOutputs, m_azimuth_float);
        m_wider->process(aOutputs, aOutputs, aRadius);
        m_line_one->setCoefficientDirect(aRadius[m_vector_size-1]);
	}
    
    inline void processAzimuth(float* aInputs, float** aOutputs, float* anAnzimuth)
	{
        m_line_one->process(m_radius_float);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_float[i] > 1.)
                aInputs[i] /= m_radius_float[i] * m_radius_float[i];
        }
		m_encoder->process(aInputs, aOutputs, anAnzimuth);
        m_wider->process(aOutputs, aOutputs, m_radius_float);
        m_line_two->setCoefficientAngleDirect(anAnzimuth[m_vector_size-1]);
	}
    
    inline void processCartesian(float* aInputs, float** aOutputs, float* anAbscissa, float* anOrdinate)
	{
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_float[i] = Tools::radius(anAbscissa[i], anOrdinate[i]);
            m_azimuth_float[i] = Tools::angle(anAbscissa[i], anAbscissa[i]);
        }
        processPolar(aInputs, aOutputs, m_radius_float, m_azimuth_float);
        m_line_thr->setCoefficientDirect(anAbscissa[m_vector_size-1]);
        m_line_fou->setCoefficientDirect(anOrdinate[m_vector_size-1]);
	}
    
    inline void processAbscissa(float* aInputs, float** aOutputs, float* anAbscissa)
	{
        m_line_fou->process(m_ordinate_float);
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_float[i] = Tools::radius(anAbscissa[i], m_ordinate_float[i]);
            m_azimuth_float[i] = Tools::angle(anAbscissa[i], m_ordinate_float[i]);
        }
        processPolar(aInputs, aOutputs, m_radius_float, m_azimuth_float);
        m_line_thr->setCoefficientDirect(anAbscissa[m_vector_size-1]);
	}
    
    inline void processOrdinate(float* aInputs, float** aOutputs, float* anOrdinate)
	{
        m_line_thr->process(m_abscissa_float);
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_float[i] = Tools::radius(m_abscissa_float[i], anOrdinate[i]);
            m_azimuth_float[i] = Tools::angle(m_abscissa_float[i], anOrdinate[i]);
        }
        processPolar(aInputs, aOutputs, m_radius_float, m_azimuth_float);
        m_line_fou->setCoefficientDirect(anOrdinate[m_vector_size-1]);
	}
    
    
    inline void processPolar(double* aInputs, double** aOutputs, double* aRadius, double* anAnzimuth)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(aRadius[i] > 1.)
                aInputs[i] /= aRadius[i] * aRadius[i];
        }
		m_encoder->process(aInputs, aOutputs, anAnzimuth);
        m_wider->process(aOutputs, aOutputs, aRadius);
        m_line_one->setCoefficientDirect(aRadius[m_vector_size-1]);
        m_line_two->setCoefficientAngleDirect(anAnzimuth[m_vector_size-1]);
	}
    
    inline void processRadius(double* aInputs, double** aOutputs, double* aRadius)
	{
        m_line_two->process(m_azimuth_double);
		for(int i = 0; i < m_vector_size; i++)
        {
            if(aRadius[i] > 1.)
                aInputs[i] /= aRadius[i] * aRadius[i];
        }
        m_encoder->process(aInputs, aOutputs, m_azimuth_double);
        m_wider->process(aOutputs, aOutputs, aRadius);
        m_line_one->setCoefficientDirect(aRadius[m_vector_size-1]);
	}
    
    inline void processAzimuth(double* aInputs, double** aOutputs, double* anAnzimuth)
	{
        m_line_one->process(m_radius_double);
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_radius_double[i] > 1.)
                aInputs[i] /= m_radius_double[i] * m_radius_double[i];
        }
		m_encoder->process(aInputs, aOutputs, anAnzimuth);
        m_wider->process(aOutputs, aOutputs, m_radius_double);
        m_line_two->setCoefficientAngleDirect(anAnzimuth[m_vector_size-1]);
	}
    
    inline void processCartesian(double* aInputs, double** aOutputs, double* anAbscissa, double* anOrdinate)
	{
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_double[i] = Tools::radius(anAbscissa[i], anOrdinate[i]);
            m_azimuth_double[i] = Tools::angle(anAbscissa[i], anOrdinate[i]) - CICM_PI2;
        }
        processPolar(aInputs, aOutputs, m_radius_double, m_azimuth_double);
        m_line_thr->setCoefficientDirect(anAbscissa[m_vector_size-1]);
        m_line_fou->setCoefficientDirect(anOrdinate[m_vector_size-1]);
	}
    
    inline void processAbscissa(double* aInputs, double** aOutputs, double* anAbscissa)
	{
        m_line_fou->process(m_ordinate_double);
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_double[i] = Tools::radius(anAbscissa[i], m_ordinate_double[i]);
            m_azimuth_double[i] = Tools::angle(anAbscissa[i], m_ordinate_double[i]) - CICM_PI2;
        }
        processPolar(aInputs, aOutputs, m_radius_double, m_azimuth_double);
        m_line_thr->setCoefficientDirect(anAbscissa[m_vector_size-1]);
	}
    
    inline void processOrdinate(double* aInputs, double** aOutputs, double* anOrdinate)
	{
        m_line_thr->process(m_abscissa_double);
		for(int i = 0; i < m_vector_size; i++)
        {
            m_radius_double[i] = Tools::radius(m_abscissa_double[i], anOrdinate[i]);
            m_azimuth_double[i] = Tools::angle(m_abscissa_double[i], anOrdinate[i]) - CICM_PI2;
        }
        processPolar(aInputs, aOutputs, m_radius_double, m_azimuth_double);
        m_line_fou->setCoefficientDirect(anOrdinate[m_vector_size-1]);
	}

};



#endif


