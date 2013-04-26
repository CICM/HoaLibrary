/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "AmbisonicBinaural.hpp"


AmbisonicBinaural::AmbisonicBinaural(int aOrder, double aSamplingRate, int aVectorSize, std::string hrtfRootPath, std::string pinnaSize)
{
    
    m_hrtfFullPath = "";
    m_hrtfRootPath = hrtfRootPath;
    m_pinnasize = pinnaSize;
	m_vector_size = 0;
	m_sampling_rate = aSamplingRate;
	m_order = aOrder;	
	m_maximumNumberOfVirtualSpeakers = 72;
	m_numberOfHarmonics = 2 * m_order + 1;
	m_response_size = 200;
	m_isHrtfLoaded = TRUE;
	
	if (m_order > 35) 
		m_order = 35;
	else if (m_order < 1)
		m_order = 1;
	
	m_number_of_inputs = 2 * m_order + 1;
	m_number_of_outputs = 2;
	
	computeNbOfVirtualSpeaker();
	m_impulsesL = new double*[m_numberOfVirtualSpeakers];
	m_impulsesR = new double*[m_numberOfVirtualSpeakers];
	m_angleListInDegree = new double[m_numberOfVirtualSpeakers];
	m_decoder = new ambisonicDecode(m_numberOfVirtualSpeakers, m_order);

	m_harmonicsIndex	= new int[m_numberOfHarmonics];
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < m_numberOfHarmonics; i++)
	{
		m_harmonicsIndex[i] = (int)floor((float)(i-1) / 2.f) + 1;
		if (i % 2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}
	
	m_optimVector = new double[m_numberOfHarmonics];
	setOptimMode("basic");
    
	formatHrtfFilePath(m_hrtfRootPath, aSamplingRate, pinnaSize);
    
	loadImpulses();
	if (m_isHrtfLoaded == TRUE)
	{
		responseInit();
		matrixResize(aVectorSize, "Intialization");
	}
}

void AmbisonicBinaural::setVectorSizeAndSamplingRate(int aVectorSize, double aSamplingRate)
{
    if (m_sampling_rate != aSamplingRate)
    {
        m_sampling_rate = aSamplingRate;
        if (formatHrtfFilePath(m_hrtfRootPath, aSamplingRate, m_pinnasize)) // Path has changed
        {
            loadImpulses();
            if (m_isHrtfLoaded == TRUE)
            {
                responseInit();
                matrixResize(aVectorSize);
            }
        }
    }
    if (m_isHrtfLoaded == TRUE)
        matrixResize(aVectorSize);
}

void AmbisonicBinaural::setPinnaSize(std::string pinnaSize)
{
    if (formatHrtfFilePath(m_hrtfRootPath, m_sampling_rate, pinnaSize)) // Path has changed
    {
        loadImpulses();
        if (m_isHrtfLoaded == TRUE)
        {
            responseInit();
        }
    }
}

bool AmbisonicBinaural::formatHrtfFilePath(std::string hrtfRootPath, int aSamplingRate, std::string pinnaSize)
{
    //m_hrtfFullPath = "";
    std::string tempFullPath = hrtfRootPath;
    m_pinnasize = pinnaSize;
    if (aSamplingRate != 44100 && aSamplingRate != 48000 && aSamplingRate != 88200 && aSamplingRate != 96000) aSamplingRate = 44100;
    if (m_pinnasize != "Small" && m_pinnasize != "Large") m_pinnasize = "Small";
    tempFullPath += intToString(aSamplingRate) + "/" + m_pinnasize + "/";
    if (tempFullPath != m_hrtfFullPath)
    {
        m_hrtfFullPath = tempFullPath;
        return true; 
    }
    m_hrtfFullPath = tempFullPath;
    return false;
}

int	AmbisonicBinaural::getParameters(std::string aParameter) const
{
	int value = 0;

	if (aParameter == "order") 
		value = m_order;
	else if (aParameter == "samplingRate") 
		value =  m_sampling_rate;
	else if (aParameter == "vectorSize") 
		value =  m_vector_size;
	else if (aParameter == "numberOfInputs") 
		value =  m_number_of_inputs;
	else if (aParameter == "numberOfOutputs") 
		value =  m_number_of_outputs;
	
	return value;
}

std::string AmbisonicBinaural::intToString(int aValue)
{
	std::ostringstream oss;
	oss << aValue;
	return oss.str();
}
void AmbisonicBinaural::computeNbOfVirtualSpeaker()
{
	int possiblesConfigurations[10] = {3, 4, 6, 8, 9, 12, 18, 24, 36, 72};
	m_numberOfVirtualSpeakers = possiblesConfigurations[0];
	for (int i = 0; i < 10; i++)
	{
		if (possiblesConfigurations[i] > m_numberOfHarmonics) 
		{
			m_numberOfVirtualSpeakers = possiblesConfigurations[i];
			break;
		}
	}
}
void AmbisonicBinaural::loadImpulses()
{
	std::string leftFilePath;
	std::string rightFilePath;

	for(int i = 0; i < m_numberOfVirtualSpeakers; i++)
	{
		m_angleListInDegree[i] = (5*72/m_numberOfVirtualSpeakers)*i;
        leftFilePath  = m_hrtfFullPath + "left"  + intToString(m_angleListInDegree[i]) + ".wav";
		rightFilePath = m_hrtfFullPath + "right" + intToString(m_angleListInDegree[i]) + ".wav";
		m_impulsesL[i] = Read_Wav(const_cast<char*>(leftFilePath.c_str()) );
		m_impulsesR[i] = Read_Wav(const_cast<char*>(rightFilePath.c_str()));
		if(m_impulsesL[i] == NULL || m_impulsesR[i] == NULL)
			m_isHrtfLoaded = FALSE;
	}

}

void AmbisonicBinaural::responseInit()
{
	m_impluse_response_matrix = gsl_matrix_calloc(m_response_size * 2, m_numberOfHarmonics);
	
	double* tmp_outputGains;
	double* tmp_ambisonicBasis = new double[m_numberOfHarmonics];
	memset(tmp_ambisonicBasis, 0, (m_numberOfHarmonics) * sizeof(double));
	
	double tmpValueL;
	double tmpValueR;
	
	tmp_ambisonicBasis[0]=1;
	for(int harmonicIndex = 0; harmonicIndex < m_numberOfHarmonics; harmonicIndex++)
	{
		if(harmonicIndex != 0)
		{
			tmp_ambisonicBasis[harmonicIndex-1] = 0;
			tmp_ambisonicBasis[harmonicIndex]= 1;
		}
		tmp_outputGains = m_decoder->process(tmp_ambisonicBasis);
		
		for(int sampleIndex = 0; sampleIndex < 200; sampleIndex++)
		{
			tmpValueL = 0;
			tmpValueR = 0;
			for (int virtualSpeakerIndex = 0; virtualSpeakerIndex < m_numberOfVirtualSpeakers; virtualSpeakerIndex++)
			{
				tmpValueL += tmp_outputGains[virtualSpeakerIndex] * m_impulsesL[virtualSpeakerIndex][sampleIndex];
				tmpValueR += tmp_outputGains[virtualSpeakerIndex] * m_impulsesR[virtualSpeakerIndex][sampleIndex];
			}
			gsl_matrix_set(m_impluse_response_matrix, sampleIndex	  , harmonicIndex, tmpValueL);
			gsl_matrix_set(m_impluse_response_matrix, sampleIndex+200 , harmonicIndex, tmpValueR);
		}
	}
}


void AmbisonicBinaural::matrixResize(int aVectorSize, std::string aMode)
{
	if(aVectorSize != m_vector_size)
	{	
		if(aMode == "resize")
			free();
		
		m_vector_size = aVectorSize;
		
		m_input_matrix	= gsl_matrix_calloc(m_numberOfHarmonics, m_vector_size);
		m_result_matrix = gsl_matrix_calloc(m_response_size * 2, m_vector_size);
		
		m_linear_vector_left	= gsl_vector_calloc(m_vector_size + m_response_size - 1);
		m_linear_vector_right	= gsl_vector_calloc(m_vector_size + m_response_size - 1);
		
		m_result_vector_view_left	= new gsl_vector_view[m_vector_size];
		m_result_vector_view_right	= new gsl_vector_view[m_vector_size];
		m_linear_vector_view_left	= new gsl_vector_view[m_vector_size];
		m_linear_vector_view_right	= new gsl_vector_view[m_vector_size];
		
		for (int j = 0; j < m_vector_size; j++)
		{
			m_result_vector_view_left[j]	= gsl_vector_subvector(&(gsl_matrix_column(m_result_matrix, j)).vector, 0, 200);
			m_result_vector_view_right[j]	= gsl_vector_subvector(&(gsl_matrix_column(m_result_matrix, j)).vector, 200, 200);
			
			m_linear_vector_view_left[j]	= gsl_vector_subvector(m_linear_vector_left, j, 200);
			m_linear_vector_view_right[j]	= gsl_vector_subvector(m_linear_vector_right, j, 200);
		}
		
		m_vectorSize_end_left = gsl_vector_subvector(m_linear_vector_left, m_response_size - 1, m_vector_size);
		m_responseSize_begin_left = gsl_vector_subvector(m_linear_vector_left, 0, m_response_size - 1);
		m_responseSize_end_left = gsl_vector_subvector(m_linear_vector_left, m_vector_size, m_response_size - 1);
		
		m_vectorSize_end_right = gsl_vector_subvector(m_linear_vector_right, m_response_size - 1, m_vector_size);
		m_responseSize_begin_right = gsl_vector_subvector(m_linear_vector_right, 0, m_response_size - 1);
		m_responseSize_end_right = gsl_vector_subvector(m_linear_vector_right, m_vector_size, m_response_size - 1);
		
	}
}

void AmbisonicBinaural::setOptimMode(std::string anOptim)
{
	if(anOptim != m_optimMode)
	{
		if(anOptim == "inPhase")
			computeInPhaseOptim();
		else if(anOptim == "maxRe")
			computeReOptim();
		else
			computeBasicOptim();
	}
}

void AmbisonicBinaural::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_numberOfHarmonics; i++) 
		m_optimVector[i] = 1.;
}

void AmbisonicBinaural::computeInPhaseOptim()
{
	m_optimMode = "inPhase"; 
	for (int i = 0; i < m_numberOfHarmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_harmonicsIndex[i])) * gsl_sf_fact(m_order-abs(m_harmonicsIndex[i])));
	}
}

void AmbisonicBinaural::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_numberOfHarmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = cos(abs(m_harmonicsIndex[i]) * PI / (2*m_order+2));
	}
	
}

void AmbisonicBinaural::free()
{
	gsl_matrix_free(m_input_matrix);
	gsl_matrix_free(m_result_matrix);
	
	gsl_vector_free(m_linear_vector_left);
	gsl_vector_free(m_linear_vector_right);
	
	delete m_result_vector_view_left;
	delete m_result_vector_view_right;
	delete m_linear_vector_view_left;
	delete m_linear_vector_view_right;
}

AmbisonicBinaural::~AmbisonicBinaural()
{
	free();
	gsl_matrix_free(m_impluse_response_matrix);
	delete m_optimVector;
}