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

#include "AmbisonicStereo.h"

AmbisonicStereo::AmbisonicStereo(long anOrder, double aDelta, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= 2;
	m_number_of_inputs		= m_number_of_harmonics;
	m_delta					= Tools::clip(aDelta, 0., 180.);

	m_loudspeakers_angle_left	= m_delta / 2.;
	m_loudspeakers_angle_right	= 360. - m_loudspeakers_angle_left;

	m_fractional_order		= computeInPhaseFractionalOrder(m_delta);

	m_output_vector	= gsl_vector_alloc (m_number_of_outputs);
	m_input_vector	= gsl_vector_alloc (m_number_of_harmonics);
	m_optim_vector	= gsl_vector_alloc (m_number_of_harmonics);
	computeIndex();
	computeMicrophones();
	computeStereoOptim();

	m_scale_factor = 1.;
	m_scale_factor = computeScaleFactor(0, m_loudspeakers_angle_left);
	
	setVectorSize(aVectorSize);
}

long AmbisonicStereo::getOrder()
{
	return m_order;
}

long AmbisonicStereo::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicStereo::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicStereo::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicStereo::getVectorSize()
{
	return m_vector_size;
}

double AmbisonicStereo::getFractionalOrder()
{
	return m_fractional_order;
}

double AmbisonicStereo::getAngle1()
{
	return m_loudspeakers_angle_left;
}

double AmbisonicStereo::getAngle2()
{
	return m_loudspeakers_angle_right;
}

double AmbisonicStereo::computeInPhaseFractionalOrder(double aDelta)
{
	aDelta /= 2.;
	aDelta = 90. - aDelta;
	aDelta /= 90.;
	aDelta *= 3.6;
	return exp(aDelta);
}

double AmbisonicStereo::computeScaleFactor(long anIndex, double anAngle)
{
	AmbisonicEncode* encoder	= new AmbisonicEncode(m_order);
	double* inputs				= new double[m_number_of_inputs];
	double* outputs				= new double[m_number_of_outputs];
	double result				= 1.;
	double aTheta				= (anAngle / 360.) * CICM_2PI;

	encoder->process(1., inputs, aTheta);
	process(inputs, outputs);
	result = 1. / outputs[anIndex];
	free(inputs);
	free(outputs);
	delete encoder;
	return result;
}

void AmbisonicStereo::computeIndex()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void AmbisonicStereo::computeStereoOptim()
{
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		/* InPhase optimization */
		if(abs(m_index_of_harmonics[i]) <= abs(m_fractional_order) + 1)
		{
			double optim = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
			if (i == 0) 
				gsl_vector_set(m_optim_vector, i, 1.);
			else if(i < 20) 
				gsl_vector_set(m_optim_vector, i, optim);
			else 
				gsl_vector_set(m_optim_vector, i, 0.);
		}
		/* Except for order higher than the fractional order  */
		else
		{
			gsl_vector_set(m_optim_vector, i, 0.);
		}
		/* Weight of the fractional order */
		if(abs(m_index_of_harmonics[i]) == abs(m_fractional_order) + 1)
		{
			double value = gsl_vector_get(m_optim_vector, i) * m_fractional_order - abs(m_fractional_order);
			gsl_vector_set(m_optim_vector, i, value);
		}
	}
}

void AmbisonicStereo::computeMicrophones()
{
	m_microphones_matrix = gsl_matrix_alloc(m_number_of_harmonics, m_number_of_outputs); 
	double aThetaLeft, aThetaRight;
	int aIndex;
	
	aThetaLeft = (m_loudspeakers_angle_left / 360.) * CICM_2PI;
	aThetaRight = (m_loudspeakers_angle_right / 360.) * CICM_2PI;
	
	for (int j = 0; j < m_number_of_harmonics; j++) 
	{
		aIndex = (int)((((double)j - 1.) / 2.) + 1.);
		if (j % 2 == 1)
			aIndex = -aIndex;
			
		if (aIndex < 0)
		{
			gsl_matrix_set(m_microphones_matrix, j, 0,sin((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix, j, 1,sin((double)abs(aIndex) * aThetaRight));
		}
		else
		{
			gsl_matrix_set(m_microphones_matrix, j, 0,cos((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix, j, 1,cos((double)abs(aIndex) * aThetaRight));
		}
	}
}

void AmbisonicStereo::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

AmbisonicStereo::~AmbisonicStereo()
{
	gsl_matrix_free(m_microphones_matrix);
	gsl_vector_free(m_input_vector);
	gsl_vector_free(m_output_vector);
	delete m_index_of_harmonics;
}

