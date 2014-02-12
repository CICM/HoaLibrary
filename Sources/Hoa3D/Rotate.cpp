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
		m_roll = m_pitch = m_yaw = 0.0f;
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
        m_cos_roll = cos(m_roll);
        m_sin_roll = sin(m_roll);
    }

	void Rotate::setPitch(const double value)
    {
		m_pitch = Tools::radian_wrap(value);
    }
	
	void Rotate::setYaw(const double value)
    {
		m_yaw = Tools::radian_wrap(value);
		m_cos_yaw = cos(m_yaw);
        m_sin_yaw = sin(m_yaw);
    }
    
	// not implemented
    void Rotate::process(const float* inputs, float* outputs)
    {
		float cos_x, sin_x, tcos_x, sig;
		
        // Copy Harmonics Args(0)
        for(int i = 0, j = 0; i < m_number_of_harmonics; i += i * 2 + 1, j++)
        {
            outputs[i] = inputs[i];
        }
        
        tcos_x = cos_x = m_cos_yaw;
        sin_x = m_sin_yaw;
        // Perform Yaw Rotation
        for(int i = 1; i <= m_order; i++)
		{
            for(int j = (i + 1) * (i + 1) - 1, k = i; j < m_number_of_harmonics; k++, j += k * 2 + 1)
            {
                sig = inputs[j-1];
                outputs[j-1] = sin_x * inputs[j] + cos_x * sig;
                outputs[j] = cos_x * inputs[j] - sin_x * sig;
            }
            cos_x = tcos_x * m_cos_yaw - sin_x * m_sin_yaw; // cos(x + b) = cos(x) * cos(b) - sin(x) * sin(b)
            sin_x = tcos_x * m_sin_yaw + sin_x * m_cos_yaw; // sin(x + b) = cos(x) * sin(b) + sin(x) * cos(b)
            tcos_x = cos_x;
        }
    }
    
    void Rotate::process(const double* inputs, double* outputs)
    {
        double cos_x, sin_x, tcos_x, sig;
		
        // Copy Harmonics Args(0)
        for(int i = 0, j = 0; i < m_number_of_harmonics; i += i * 2 + 1, j++)
        {
            outputs[i] = inputs[i];
        }
        
        tcos_x = cos_x = m_cos_yaw;
        sin_x = m_sin_yaw;
        // Perform Yaw Rotation
        for(int i = 1; i <= m_order; i++)
		{
            for(int j = (i + 1) * (i + 1) - 1, k = i; j < m_number_of_harmonics; k++, j += k * 2 + 1)
            {
                sig = inputs[j-1];
                outputs[j-1] = sin_x * inputs[j] + cos_x * sig;
                outputs[j] = cos_x * inputs[j] - sin_x * sig;
            }
            cos_x = tcos_x * m_cos_yaw - sin_x * m_sin_yaw; // cos(x + b) = cos(x) * cos(b) - sin(x) * sin(b)
            sin_x = tcos_x * m_sin_yaw + sin_x * m_cos_yaw; // sin(x + b) = cos(x) * sin(b) + sin(x) * cos(b)
            tcos_x = cos_x;
        }
        
        // Perform Roll Rotation
        tcos_x = cos_x = m_cos_roll;
        sin_x = m_sin_roll;
		
    }
    
    Rotate::~Rotate()
    {
		;
    }
	
}

