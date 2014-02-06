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
        
        for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
        {
            m_rotation_matrix[j]    = new double[m_number_of_harmonics];
        }
    }
	
	void Rotate::setRotations(const double roll, const double pitch, const double yaw)
    {
		;
    }
	
	void Rotate::setRoll(const double value)
    {
		;
    }

	void Rotate::setPitch(const double value)
    {
		;
    }
	
	void Rotate::setYaw(const double value)
    {
		;
    }
    
    void Rotate::process(const float* inputs, float* outputs)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
            outputs[i] = inputs[i] * m_rotation_matrix[m_rotation][i];
    }
    
    void Rotate::process(const double* inputs, double* outputs)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
            outputs[i] = inputs[i] * m_rotation_matrix[m_rotation][i];
    }
    
    Rotate::~Rotate()
    {
        delete [] m_rotation_matrix;
    }
	
} // end of namespace Hoa3D

