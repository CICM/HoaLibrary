/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_CICMLINE
#define DEF_CICMLINE

#include "../Hoa2D.max.h"

class Line
{
	
private:
	long        m_vector_size;
	long        m_sampling_rate;
	
	double      m_value_old;
	double      m_value_new;
	double      m_value_step;
	long        m_counter;
	long        m_ramp;
	
	void init(long vector_size = 0, long sampling_rate = 44100);
	
public:
	Line(long samps = 4410, long vector_size = 0, long sampling_rate = 44100);
	Line(double ms = 100., long vector_size = 0, long sampling_rate = 44100);
	
	inline long		getVectorSize()		const {return m_vector_size;}
	inline long		getSamplingRate()	const {return m_sampling_rate;}
	inline long		getRampInSample()	const {return m_ramp;}
	inline double	getRampInMs()		const {return ((double)m_ramp / (double)m_sampling_rate) * 1000.;}
	inline double	getValue()			const {return m_value_new;}
	
	inline void setSamplingRate(const long sampling_rate) {m_sampling_rate = clip_min(sampling_rate, 1);}
	inline void setVectorSize(const long vector_size)		{m_vector_size = vector_size;}
	
	void setRampInSample(const long samps);
	void setRampInMs(const double ms);
	void setValueDirect(const double value);
	void setValue(const double value);
	void setValueAngleDirect(const double angle);
	void setValueAngle(const double angle);
	
	~Line() {};
	
	/* Perform sample by sample */
	double process();
};

#endif