/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Rotate.h"

namespace Hoa3D
{
    Rotate::Rotate(unsigned int order) : Ambisonic(order)
    {
        m_number_of_inputs		= m_number_of_harmonics + 3;
        m_rotation              = NUMBEROFCIRCLEPOINTS - 1;
        m_rotation_matrix       = new double*[NUMBEROFCIRCLEPOINTS];
		
		m_harmonicCos   = new double[m_order];
		m_harmonicSin   = new double[m_order];
		m_cosLookUp     = new double[NUMBEROFCIRCLEPOINTS];
		m_sinLookUp     = new double[NUMBEROFCIRCLEPOINTS];
		
		for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
		{
			// set cos and sin tables
			m_cosLookUp[i] = cos((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
			m_sinLookUp[i] = sin((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
			
			m_rotation_matrix[i] = new double[m_number_of_harmonics];
		}
    }
	
	void Rotate::setRotations(const double roll, const double pitch, const double yaw)
    {
		setRoll(roll);
		setPitch(pitch);
		setYaw(yaw);
    }
	
	void Rotate::setRoll(const double value)
    {
		m_roll  = Tools::radian_wrap(value);
    }

	void Rotate::setPitch(const double value)
    {
		m_pitch = Tools::radian_wrap(value);
    }
	
	void Rotate::setYaw(const double value)
    {
		m_yaw = Tools::radian_wrap(value);
		long tmpAngle;
        double tmpTheta = m_yaw;
        for(int i = 0; i < m_order; i++)
        {
            double angleFactor = tmpTheta*NUMBEROFCIRCLEPOINTS/(CICM_2PI);
			
            tmpAngle = (long)(angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
            m_harmonicSin[i] = m_sinLookUp[tmpAngle];
            m_harmonicCos[i] = m_cosLookUp[tmpAngle];
            
            tmpTheta += m_yaw;
        }
    }
    
    void Rotate::process(const float* inputs, float* outputs)
    {
		// copy inputs in outputs
		cblas_scopy(m_number_of_harmonics, inputs, 1, outputs, 1);
		
		// compute only z-axis rotation
		int h;
		double _cos, _sin, harmoNeg, harmoPos;
		for (int i = 1; i <= m_order; i++)
		{
			h = (i+1)*(i+1);
			_cos = m_harmonicCos[i-1];
			_sin = m_harmonicSin[i-1];
			harmoNeg = inputs[h-2];
			harmoPos = inputs[h-1];
			outputs[h-1] = _cos * harmoPos - _sin * harmoNeg;
			outputs[h-2] = _sin * harmoPos + _cos * harmoNeg;
		}
    }
    
    void Rotate::process(const double* inputs, double* outputs)
    {
		// copy inputs in outputs
		cblas_dcopy(m_number_of_harmonics, inputs, 1, outputs, 1);
		
		// compute only z-axis rotation
		int h;
		double _cos, _sin, harmoNeg, harmoPos;
		for (int i = 1; i <= m_order; i++)
		{
			h = (i+1)*(i+1);
			_cos = m_harmonicCos[i-1];
			_sin = m_harmonicSin[i-1];
			harmoNeg = inputs[h-2];
			harmoPos = inputs[h-1];
			outputs[h-1] = _cos * harmoPos - _sin * harmoNeg;
			outputs[h-2] = _sin * harmoPos + _cos * harmoNeg;
		}
    }
    
    Rotate::~Rotate()
    {
        delete [] m_rotation_matrix;
    }
	
} // end of namespace Hoa3D

