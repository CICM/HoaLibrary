/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_CICMLINE
#define DEF_CICMLINE

#include "../../Hoa2D/Tools.h"

namespace Cicm
{
	class Line{
		
	private:
		long        m_vector_size;
		long        m_sampling_rate;
		
		double      m_value_old;
		double      m_value_new;
		double      m_value_step;
		long        m_counter;
		long        m_ramp;
		
	public:
		Line(long aTimeInSample = 4410, long aVectorSize = 0, long aSamplingRate = 44100);
		Line(double aTimeInMs = 100., long aVectorSize = 0, long aSamplingRate = 44100);
		
		long    getVectorSize();
		long    getSamplingRate();
		long    getRampInSample();
		double  getRampInMs();
		double  getCoefficient();
		
		void setSamplingRate(long aSamplingRate);
		void setVectorSize(long aVectorSize);
		
		void setRampInSample(long aTimeInSample);
		void setRampInMs(double aTimeInMs);
		void setCoefficientDirect(double aCoefficient);
		void setCoefficient(double aCoefficient);
		void setCoefficientAngleDirect(double anAngle);
		void setCoefficientAngle(double anAngle);
		
		~Line();
		
		/* Perform sample by sample */
		double process();
	};
}
#endif