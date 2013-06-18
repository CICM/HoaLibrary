/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

#include "CicmGigaverb.h"

Gigaverb::Gigaverb(long aVectorSize, double aSamplingRate, double aRoomsize, double revtime, double damping, double spread, double inputbandwidth, double earlylevel, double taillevel)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, 0.);
	m_largest_delay = m_sampling_rate * m_room_size / 340.;

	m_input_damper = new FilterDamper(1.0 - inputbandwidth);
	m_tap_delay = new FilterFixedDelay(44100);
	for(int i = 0; i < FDNORDER; i++)
	{
		m_fdn_delays[i] = new FilterFixedDelay((int)(m_sampling_rate * REV_MAXROOMSIZE / 340.) + 1000);
		m_fdn_damps[i]	= new FilterDamper(m_fdn_damping);
	}

	/* Diffuser section */
	double diffscale, spread1, spread2;
	double b, r, c, a, cc, d, dd, e;
	diffscale = m_fdn_times[3] / (210+159+562+410);
	spread1 = spread;
	spread2 = 3.0*spread;
    
    b = 210;
    r = 0.125541;
    a = (int)(spread1*r);
    c = 210+159+a;
    cc = c-b;
    r = 0.854046;
    a = (int)(spread2*r);
    d = 210+159+562+a;
    dd = d-c;
    e = 1341-d;
    
    m_diffusers[0] = new FilterDiffuser((int)(diffscale*b),0.75);
    m_diffusers[1] = new FilterDiffuser((int)(diffscale*cc),0.75);
    m_diffusers[2] = new FilterDiffuser((int)(diffscale*dd),0.625);
    m_diffusers[3] = new FilterDiffuser((int)(diffscale*e),0.625);
    
    setInputBandwidth(inputbandwidth);
	setRoomSize(aRoomsize);
	setDamping(damping);
	setReverberationTime(revtime);
	setEarlyLevel(earlylevel);
	setTailLevel(taillevel);
    setVectorSize(aVectorSize);
	setSamplingRate(aSamplingRate);
}

void Gigaverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void Gigaverb::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
    setInputBandwidth(m_bandwidth);
	setRoomSize(m_room_size);
	setDamping(m_damping_value);
	setReverberationTime(m_reverb_time);
	setEarlyLevel(m_early_level);
	setTailLevel(m_tail_level);
}


void Gigaverb::setReverberationTime(double aValue)
{
	m_reverb_time = Tools::clip(aValue, 0.1, 360.);
	alpha = pow(pow(10.0,-3.), 1. / (m_sampling_rate * m_reverb_time));

	for(int i = 0; i < FDNORDER; i++)
		m_fdn_gains[i] = -pow(alpha, m_fdn_times[i]);
}

double Gigaverb::getReverberationTime()
{
	return m_reverb_time;
}

void Gigaverb::setRoomSize(double aRoomSize)
{
	m_room_size = Tools::clip(aRoomSize, 1., REV_MAXROOMSIZE);
	m_largest_delay = m_sampling_rate * m_room_size * 0.00294;

	m_fdn_times[0] = fabs(1. * m_largest_delay);
	m_fdn_times[1] = fabs(0.816490 * m_largest_delay);
	m_fdn_times[2] = fabs(0.707100 * m_largest_delay);
	m_fdn_times[3] = fabs(0.632450 * m_largest_delay);
	for(int i = 0; i < FDNORDER; i++)
		m_fdn_gains[i] = -pow(alpha, m_fdn_times[i]);

	m_tap_times[0] = (int)(5+0.410 * m_largest_delay);
	m_tap_times[1] = (int)(5+0.300 * m_largest_delay);
	m_tap_times[2] = (int)(5+0.155 * m_largest_delay);
	m_tap_times[3] = (int)(5);
    
	for(int i = 0; i < FDNORDER; i++)
		m_tap_gains[i] = pow(alpha,(double)m_tap_times[i]);
}

double Gigaverb::getRoomSize()
{
	return m_room_size;
}

void Gigaverb::setEarlyLevel(double aValue)
{
	m_early_level = Tools::clip(aValue, 0., 1.);
}

double Gigaverb::getEarlyLevel()
{
	return m_early_level;
}

void Gigaverb::setTailLevel(double aValue)
{
	m_tail_level = Tools::clip(aValue, 0., 1.);
}

double Gigaverb::getTailLevel()
{
	return m_tail_level;
}

void Gigaverb::setInputBandwidth(double aValue)
{
	m_bandwidth = Tools::clip(aValue, 0., 1.);
	m_input_damper->setCoefficient(1. - m_bandwidth);
}

double Gigaverb::getInputBandwidth()
{
	return m_bandwidth;
}

void Gigaverb::setDamping(double aValue)
{
	m_damping_value = Tools::clip(aValue, 0., 1.);
	for(int i = 0; i < FDNORDER; i++)
		m_fdn_damps[i]->setCoefficient(m_damping_value);
}

double Gigaverb::getDamping()
{
	return m_damping_value;
}

Gigaverb::~Gigaverb()
{
	delete m_input_damper;
	delete m_tap_delay;
	for(int i = 0; i < FDNORDER; i++)
    {
        delete m_fdn_delays[i];
        delete m_fdn_damps[i];
        delete m_diffusers[i];
    }
}
