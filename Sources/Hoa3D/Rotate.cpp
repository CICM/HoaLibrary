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
        m_number_of_inputs	= m_number_of_harmonics + 3;
		m_roll = m_pitch = m_yaw = 0.0f;
		
		// square matrix (ignoring harmonic 0);
		m_rZ_matrix = new double[(m_number_of_harmonics-1)*(m_number_of_harmonics-1)];
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
		
		long matrixSize = (m_number_of_harmonics-1)*(m_number_of_harmonics-1);
		
		// clear matrix
		for (int i = 0; i < matrixSize; i++)
			m_rZ_matrix[i] = 0.0f;
		
		double angle = m_yaw;
		double dcos, dsin, factor;
		long arg, matrixRow;
		matrixRow = m_number_of_harmonics-1;
		
		for (int i=0; i < matrixRow; i++)
		{
			arg = getHarmonicArgument(i+1);
			if (arg == 0)
			{
				m_rZ_matrix[i * matrixRow + i] = 1.0f;
			}
			else if (arg < 0)
			{
				factor = abs(arg) * angle;
				dcos = cos(factor);
				dsin = sin(factor);
				
				// neg harmo
				m_rZ_matrix[i * matrixRow + i] = dcos;
				m_rZ_matrix[(i+1) * matrixRow + i] = -dsin;
				
				// pos harmo
				m_rZ_matrix[i * matrixRow + i+1] = dsin;
				m_rZ_matrix[(i+1) * matrixRow + i+1] = dcos;
			}
		}
    }
    
	// not implemented
    void Rotate::process(const float* inputs, float* outputs)
    {
		// copy inputs in outputs
		cblas_scopy(m_number_of_harmonics, inputs, 1, outputs, 1);
    }
    
    void Rotate::process(const double* inputs, double* outputs)
    {
		// R(roll, pitch, yaw) = Rz(roll + CICM_PI4) Ry90 Rz(pitch + CICM_PI) Ry90 Rz(yaw + CICM_PI4)
		
		// copy inputs in outputs
		cblas_dcopy(m_number_of_harmonics, inputs, 1, outputs, 1);
		
		// compute yaw rotation : 
		cicm_product_mat_vec_d(m_rZ_matrix, inputs+1, outputs+1, m_number_of_harmonics-1, m_number_of_harmonics-1);
		
		//const double* rY = MatrixRy90::getMatrix();
		//cicm_product_mat_vec_d(rY, inputs+1, outputs+1, 3, 3);
    }
    
    Rotate::~Rotate()
    {
		delete [] m_rZ_matrix;
    }
	
} // end of namespace Hoa3D

