#include "revGigaverb.h"

Gigaverb::Gigaverb(long anOrder, double aFactor, double aSamplingRate, double aRoomsize, double aReverbTime, double aDamping,
	double spread, double anInputBandwidth, double anEarlyLevel, double aTailLevel)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, 1.);;
	m_largest_delay = m_sampling_rate * m_room_size / 340.;

	m_input_damper = new Damper(1.0 - anInputBandwidth);
	m_tap_delay = new FixedDelay(44100);
	for(int i = 0; i < FDNORDER; i++)
	{
		m_fdn_delays[i] = new FixedDelay((int)(m_sampling_rate * REV_MAXROOMSIZE / 340.) + 1000);
		m_fdn_damps[i]	= new Damper(m_fdn_damping);
	}
	setInputBandwidth(anInputBandwidth);
	setRoomSize(aRoomsize);
	setDamping(aDamping);
	setReverberationTime(aReverbTime);
	setEarlyLevel(anEarlyLevel);
	setTailLevel(aTailLevel);

	/* Diffuser section */
	double diffscale, spread1, spread2;
	double b, r, c, a, cc, d, dd, e;
	diffscale = m_fdn_times[3] / (210+159+562+410);
	spread1 = spread;
	spread2 = 3.0*spread;
    
    b = 210;
    r = aFactor;
    //r = 0.125541;
    a = (int)(spread1*r);
    c = 210+159+a;
    cc = c-b;
    r = aFactor * 2;
    r = fmod(r, 1.);
    //r = 0.854046;
    a = (int)(spread2*r);
    d = 210+159+562+a;
    dd = d-c;
    e = 1341-d;
    
    m_diffusers[0] = new Diffuser((int)(diffscale*b),0.75);
    m_diffusers[1] = new Diffuser((int)(diffscale*cc),0.75);
    m_diffusers[2] = new Diffuser((int)(diffscale*dd),0.625);
    m_diffusers[3] = new Diffuser((int)(diffscale*e),0.625);
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

void Gigaverb::clear()
{
	for(int i = 0; i < FDNORDER; i++)
	{
		for(int k = 0; k < m_fdn_times[i]; k++)
			m_fdn_delays[i]->write(0.f);
	}
}

void Gigaverb :: flush()
{
	m_input_damper->flush();
	m_tap_delay->flush();
	for(int i = 0; i < FDNORDER; i++)
	{
		m_fdn_delays[i]->flush();
		m_fdn_damps[i]->flush();
		m_diffusers[i]->flush();
	}
}

void Gigaverb::setRoomSize(double aRoomSize)
{
	m_room_size = Tools::clip(aRoomSize, 1., REV_MAXROOMSIZE);
	m_largest_delay = m_sampling_rate * m_room_size * 0.00294;

	m_fdn_times[0] = abs(1. * m_largest_delay);
	m_fdn_times[1] = abs(0.816490 * m_largest_delay);
	m_fdn_times[2] = abs(0.707100 * m_largest_delay);
	m_fdn_times[3] = abs(0.632450 * m_largest_delay);
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
	m_input_damper->set(1. - m_bandwidth);
}

double Gigaverb::getInputBandwidth()
{
	return m_bandwidth;
}

void Gigaverb::setDamping(double aValue)
{
	m_damping_value = Tools::clip(aValue, 0., 1.);
	for(int i = 0; i < FDNORDER; i++)
		m_fdn_damps[i]->set(m_damping_value);
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
