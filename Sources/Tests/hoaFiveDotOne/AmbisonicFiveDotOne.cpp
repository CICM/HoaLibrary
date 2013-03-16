/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "AmbisonicFiveDotOne.h"

AmbisonicFiveDotOne::AmbisonicFiveDotOne(long anOrder, double aFrontDelta, double aSurroundDelta, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= 6;
	m_number_of_inputs		= m_number_of_harmonics;
	m_delta_front			= Tools::clip(aFrontDelta, 0., 90.);
	m_delta_surround		= Tools::clip(aSurroundDelta, 90., 180.);

	m_angle_center			= 0.;
	m_angle_left			= m_delta_front;
	m_angle_right			= 360. - m_delta_front;
	m_angle_left_surround	= m_delta_surround;
	m_angle_right_surround	= 360. - m_delta_surround;

	m_fractional_order_center	= computeInPhaseFractionalOrder(m_delta_front);
	m_fractional_order_stereo	= computeInPhaseFractionalOrder((m_delta_front + (m_delta_surround - m_delta_front)) / 2.);
	m_fractional_order_surround = computeInPhaseFractionalOrder(((m_delta_surround - m_delta_front) + (m_angle_right_surround - m_delta_surround)) / 2.);

	m_input_vector_center	= gsl_vector_alloc(m_number_of_harmonics);
	m_input_vector_stereo	= gsl_vector_alloc(m_number_of_harmonics);
	m_input_vector_surround = gsl_vector_alloc(m_number_of_harmonics);

	m_output_vector_center	= gsl_vector_alloc(1);
	m_output_vector_stereo	= gsl_vector_alloc(2);
	m_output_vector_surround= gsl_vector_alloc(2);

	m_optim_vector_center	= gsl_vector_alloc(m_number_of_harmonics);
	m_optim_vector_stereo	= gsl_vector_alloc(m_number_of_harmonics);
	m_optim_vector_surround	= gsl_vector_alloc(m_number_of_harmonics);

	computeIndex();
	computeMicrophones();
	computeFiveDotOneOptim();

	m_scale_factor_center = 1.;
	m_scale_factor_stereo = 1.;
	m_scale_factor_surround = 1;
	m_scale_factor_center = computeScaleFactor(0, m_angle_center);
	m_scale_factor_stereo = computeScaleFactor(1, m_angle_left);
	m_scale_factor_surround = computeScaleFactor(2, m_angle_left_surround);

	m_last_sample = 0.;
	setVectorSize(aVectorSize);
}

long AmbisonicFiveDotOne::getOrder()
{
	return m_order;
}

long AmbisonicFiveDotOne::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicFiveDotOne::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicFiveDotOne::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicFiveDotOne::getVectorSize()
{
	return m_vector_size;
}

double AmbisonicFiveDotOne::getFractionalOrderCenter()
{
	return m_fractional_order_center;
}
double AmbisonicFiveDotOne::getFractionalOrderFront()
{
	return m_fractional_order_stereo;
}
double AmbisonicFiveDotOne::getFractionalOrderSurround()
{
	return m_fractional_order_surround;
}

double AmbisonicFiveDotOne::computeInPhaseFractionalOrder(double aDelta)
{
	aDelta /= 2.;
	aDelta = 90. - aDelta;
	aDelta /= 90.;
	aDelta *= 3.6;
	return exp(aDelta);
}

double AmbisonicFiveDotOne::computeScaleFactor(long anIndex, double anAngle)
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

void AmbisonicFiveDotOne::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void AmbisonicFiveDotOne::computeFiveDotOneOptim()
{
	gsl_vector_set(m_optim_vector_center, 0, 1.);
	gsl_vector_set(m_optim_vector_stereo, 0, 1.);
	gsl_vector_set(m_optim_vector_surround, 0, 1.);
	for (int i = 1; i < m_number_of_harmonics; i++) 
	{
		/* InPhase optimization */
		/* Except for order higher than the fractional order  */
		double optim = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
		if(abs(m_index_of_harmonics[i]) <= abs(m_fractional_order_center) + 1)
				gsl_vector_set(m_optim_vector_center, i, optim);
		else
			gsl_vector_set(m_optim_vector_center, i, 0.);
		if(abs(m_index_of_harmonics[i]) <= abs(m_fractional_order_stereo) + 1)
				gsl_vector_set(m_optim_vector_stereo, i, optim);
		else
			gsl_vector_set(m_optim_vector_stereo, i, 0.);
		if(abs(m_index_of_harmonics[i]) <= abs(m_fractional_order_surround) + 1)
				gsl_vector_set(m_optim_vector_surround, i, optim);
		else
			gsl_vector_set(m_optim_vector_surround, i, 0.);

		/* Weight of the fractional order */
		if(abs(m_index_of_harmonics[i]) == abs(m_fractional_order_center) + 1)
		{
			double value = gsl_vector_get(m_optim_vector_center, i) * m_fractional_order_center - abs(m_fractional_order_center);
			gsl_vector_set(m_optim_vector_center, i, value);
		}
		if(abs(m_index_of_harmonics[i]) == abs(m_fractional_order_stereo) + 1)
		{
			double value = gsl_vector_get(m_optim_vector_stereo, i) * m_fractional_order_stereo - abs(m_fractional_order_stereo);
			gsl_vector_set(m_optim_vector_stereo, i, value);
		}
		if(abs(m_index_of_harmonics[i]) == abs(m_fractional_order_surround) + 1)
		{
			double value = gsl_vector_get(m_optim_vector_surround, i) * m_fractional_order_surround - abs(m_fractional_order_surround);
			gsl_vector_set(m_optim_vector_surround, i, value);
		}
	}
}

void AmbisonicFiveDotOne::computeMicrophones()
{
	m_microphones_matrix_center		= gsl_matrix_alloc(m_number_of_harmonics, 1);
	m_microphones_matrix_stereo		= gsl_matrix_alloc(m_number_of_harmonics, 2); 
	m_microphones_matrix_surround	= gsl_matrix_alloc(m_number_of_harmonics, 2); 

	int aIndex;
	double aThetaLeftSurround	= (m_angle_left_surround / 360.) * CICM_2PI;
	double aThetaRightSurround	= (m_angle_right_surround / 360.) * CICM_2PI;
	double aThetaLeft			= (m_angle_left / 360.) * CICM_2PI;
	double aThetaRight			= (m_angle_right / 360.) * CICM_2PI;
	double aThetaCenter			= (m_angle_center / 360.) * CICM_2PI;

	for (int j = 0; j < m_number_of_harmonics; j++) 
	{
		aIndex = (int)((((double)j - 1.) / 2.) + 1.);
		if (j % 2 == 1)
			aIndex = -aIndex;
			
		if (aIndex < 0)
		{
			gsl_matrix_set(m_microphones_matrix_center, j, 0,sin(0.));
			gsl_matrix_set(m_microphones_matrix_stereo, j, 0,sin((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix_stereo, j, 1,sin((double)abs(aIndex) * aThetaRight));
			gsl_matrix_set(m_microphones_matrix_surround, j, 0,sin((double)abs(aIndex) * aThetaLeftSurround));
			gsl_matrix_set(m_microphones_matrix_surround, j, 1,sin((double)abs(aIndex) * aThetaRightSurround));
		}
		else
		{
			gsl_matrix_set(m_microphones_matrix_center, j, 0,cos(0.));
			gsl_matrix_set(m_microphones_matrix_stereo, j, 0,cos((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix_stereo, j, 1,cos((double)abs(aIndex) * aThetaRight));
			gsl_matrix_set(m_microphones_matrix_surround, j, 0,cos((double)abs(aIndex) * aThetaLeftSurround));
			gsl_matrix_set(m_microphones_matrix_surround, j, 1,cos((double)abs(aIndex) * aThetaRightSurround));
		}
	}
}

void AmbisonicFiveDotOne::setVectorSize(int aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

AmbisonicFiveDotOne::~AmbisonicFiveDotOne()
{
	gsl_matrix_free(m_microphones_matrix_center);
	gsl_matrix_free(m_microphones_matrix_stereo);
	gsl_matrix_free(m_microphones_matrix_surround);

	gsl_vector_free(m_input_vector_center);
	gsl_vector_free(m_input_vector_stereo);
	gsl_vector_free(m_input_vector_surround);

	gsl_vector_free(m_output_vector_center);
	gsl_vector_free(m_output_vector_stereo);
	gsl_vector_free(m_output_vector_surround);

	gsl_vector_free(m_optim_vector_center);
	gsl_vector_free(m_optim_vector_stereo);
	gsl_vector_free(m_optim_vector_surround);

	delete m_index_of_harmonics;
}

