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

#ifndef DEF_GIGAVERB
#define DEF_GIGAVERB

#include "cicmTools.h"
#include "revDamper.h"
#include "revDiffuser.h"
#include "revFixedDelay.h"

#define FDNORDER 4
#define REV_MAXROOMSIZE 300.

class Gigaverb
{
protected:

	long		m_sampling_rate;
	double		m_tail_level;
	double		m_early_level;
	double		m_room_size;
	double		m_reverb_time;
	double		m_largest_delay;
	double		m_damping_value;
	double		m_bandwidth;
	
	Damper*		m_input_damper;
	
	FixedDelay* m_tap_delay;
	int			m_tap_times[FDNORDER];
	double		m_tap_gains[FDNORDER];
	
	FixedDelay* m_fdn_delays[FDNORDER];
	int			m_fdn_times[FDNORDER];
	double		m_fdn_gains[FDNORDER];
	
	Damper*		m_fdn_damps[FDNORDER]; 
	double		m_fdn_damping;
	
	Diffuser*	m_diffusers[FDNORDER];

	double alpha;
public:

	Gigaverb(long aMode = 0, double aFactor = 0.854046, double aSamplingRate = 44100., double aRoomsize = 50., double revtime = 7., double damping = 0.5, double spread = 15., double inputbandwidth = 0.5, double earlylevel = 1., double taillevel = 1.);
	
	void flush();
	void clear();

	void setRoomSize(double aRoomSize);
	double getRoomSize();
	void setReverberationTime(double aValue);
	double getReverberationTime();
	void setDamping(double aValue);
	double getDamping();
	void setInputBandwidth(double aValue);
	double getInputBandwidth();
	void setEarlyLevel(double aValue);
	double getEarlyLevel();
	void setTailLevel(double aValue);
	double getTailLevel();
    
    inline double perform(double anInput)
    {
        double lsum, sum, sign;
        
        double d[FDNORDER];
        double u[FDNORDER];
        double f[FDNORDER];
        
        double z = m_input_damper->process(anInput);
        
        z = m_diffusers[0]->process(z);
        
        for(int i = 0; i < 4; i++)
            u[i] = m_tap_gains[i] * m_tap_delay->read(m_tap_times[i]);
        
        m_tap_delay->write(z);
        
        for(int i = 0; i < 4; i++)
            d[0] = m_fdn_damps[i]->process( m_fdn_gains[i] * m_fdn_delays[i]->read(m_fdn_times[i]) );
        
        sum = 0.0;
        sign = 1.0;
        
        for(int i = 0; i < 4; i++)
        {
            sum += sign*(m_tail_level * d[i] + m_early_level * u[i]);
            sign = -sign;
        }
        
        lsum = sum + anInput * m_early_level;
        
        f[0] = 0.5f*(+d[0] + d[1] - d[2] - d[3]);
        f[1] = 0.5f*(+d[0] - d[1] - d[2] + d[3]);
        f[2] = 0.5f*(-d[0] + d[1] - d[2] + d[3]);
        f[3] = 0.5f*(+d[0] + d[1] + d[2] + d[3]);
        
        m_fdn_delays[0]->write(u[0]+f[0]);
        m_fdn_delays[1]->write(u[1]+f[1]);
        m_fdn_delays[2]->write(u[2]+f[2]);
        m_fdn_delays[3]->write(u[3]+f[3]);
        
        lsum = m_diffusers[1]->process(lsum);
        lsum = m_diffusers[2]->process(lsum);
        lsum = m_diffusers[3]->process(lsum);
        
        return lsum;
    }
    
	~Gigaverb();

};

#endif