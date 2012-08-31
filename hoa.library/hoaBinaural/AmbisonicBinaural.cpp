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

#include "AmbisonicBinaural.h"

AmbisonicBinaural::AmbisonicBinaural(int aOrder, int aSamplingRate, int aVectorSize)
{	
	m_vector_size = 0;
	m_sampling_rate = 0;
	m_order = aOrder;	
	m_maximumNumberOfVirtualSpeakers = 72;
	m_numberOfHarmonics = 2 * m_order + 1;
	m_response_size = 200;
	
	if (m_order > 35) 
		m_order = 35;
	
	computeNbOfVirtualSpeaker();
	m_impulsesL = new double*[m_numberOfVirtualSpeakers];
	m_impulsesR = new double*[m_numberOfVirtualSpeakers];
	m_angleListInDegree = new double[m_numberOfVirtualSpeakers];
	m_decoder = new ambisonicDecode(m_numberOfVirtualSpeakers, m_order);

	loadImpulses();
	responseInit();
	matrixResize(aVectorSize, "Intialization");
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
	std::string preFilePath = "/Users/juliencolafrancesco/Desktop/hrtfDatabase/";
	
	for(int i = 0; i < m_numberOfVirtualSpeakers; i++)
	{
		m_angleListInDegree[i] = (5*72/m_numberOfVirtualSpeakers)*i;
		leftFilePath  = preFilePath + "left"  + intToString(m_angleListInDegree[i]) + ".wav";
		rightFilePath = preFilePath + "right" + intToString(m_angleListInDegree[i]) + ".wav";
		m_impulsesL[i] = Read_Wav(const_cast<char*>(leftFilePath.c_str()) );
		m_impulsesR[i] = Read_Wav(const_cast<char*>(rightFilePath.c_str()));
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
}