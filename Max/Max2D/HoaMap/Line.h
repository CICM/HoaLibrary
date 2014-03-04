/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_CICMLINE
#define DEF_CICMLINE

#include "../Hoa2D.max.h"

class Line{
	
private:
	long        m_vector_size;
	long        m_sampling_rate;
	
	double      m_value_old;
	double      m_value_new;
	double      m_value_step;
	long        m_counter;
	long        m_ramp;
	
	void init(long aVectorSize = 0, long aSamplingRate = 44100);
	
public:
	Line(long aTimeInSample = 4410, long aVectorSize = 0, long aSamplingRate = 44100);
	Line(double aTimeInMs = 100., long aVectorSize = 0, long aSamplingRate = 44100);
	
	inline long		getVectorSize()		const {return m_vector_size;}
	inline long		getSamplingRate()	const {return m_sampling_rate;}
	inline long		getRampInSample()	const {return m_ramp;}
	inline double	getRampInMs()		const {return ((double)m_ramp / (double)m_sampling_rate) * 1000.;}
	inline double	getValue()			const {return m_value_new;}
	
	inline void setSamplingRate(long aSamplingRate) {m_sampling_rate = Hoa2D::clip_min(aSamplingRate, 1);}
	inline void setVectorSize(long aVectorSize)		{m_vector_size = aVectorSize;}
	
	void setRampInSample(long aTimeInSample);
	void setRampInMs(double aTimeInMs);
	void setValueDirect(double aCoefficient);
	void setValue(double aCoefficient);
	void setValueAngleDirect(double anAngle);
	void setValueAngle(double anAngle);
	
	~Line() {};
	
	/* Perform sample by sample */
	double process();
};

#endif