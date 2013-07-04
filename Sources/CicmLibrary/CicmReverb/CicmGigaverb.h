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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_GIGAVERB
#define DEF_GIGAVERB

#include "../CicmFilters/CicmFilterDiffuser.h"
#include "../CicmFilters/CicmFilterFixedDelay.h"
#include "../CicmFilters/CicmFilterDamper.h"

#define FDNORDER 4
#define REV_MAXROOMSIZE 300.

class Gigaverb
{
protected:
    long		m_vector_size;
	long		m_sampling_rate;
	double		m_tail_level;
	double		m_early_level;
	double		m_room_size;
	double		m_reverb_time;
	double		m_largest_delay;
	double		m_damping_value;
	double		m_bandwidth;
	
	FilterDamper*	m_input_damper;
	
	FilterFixedDelay* m_tap_delay;
	int			m_tap_times[FDNORDER];
	double		m_tap_gains[FDNORDER];
	
	FilterFixedDelay* m_fdn_delays[FDNORDER];
	int			m_fdn_times[FDNORDER];
	double		m_fdn_gains[FDNORDER];
	
	FilterDamper*		m_fdn_damps[FDNORDER];
	double		m_fdn_damping;
	
	FilterDiffuser*	m_diffusers[FDNORDER];

	double alpha;
public:

	Gigaverb(double aSamplingRate = 44100., double aRoomsize = 50., double revtime = 7., double damping = 0.5, double spread = 15., double inputbandwidth = 0.5, double earlylevel = 1., double taillevel = 1.);
	
	//void	setVectorSize(long aVectorSize);
    //void	setSamplingRate(long aSamplingRate);

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