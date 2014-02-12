/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Scope.h"

namespace Hoa3D
{
    Scope::Scope(unsigned int order, unsigned int numberOfRows, unsigned int numberOfColumns) : Ambisonic(order)
    {
        m_number_of_rows = numberOfRows;
        m_number_of_columns = numberOfColumns;
		m_decoder   = new Decoder(order, m_number_of_rows * m_number_of_columns);
        m_matrix    = new double[m_number_of_rows * m_number_of_columns];
        m_harmonics = new double[m_number_of_harmonics];
        
        for(int i = 0; i < m_number_of_rows; i++)
        {
            for(int j = 0; j < m_number_of_columns; j++)
            {
                m_decoder->setLoudspeakerPosition(i * m_number_of_columns + j, (double)j * CICM_PI / (double)(m_number_of_rows - 1) - CICM_PI2, (double)i * CICM_2PI / (double)m_number_of_columns);
            }
        }
        
    }
	
    void Scope::process(const float* inputs)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_harmonics[i] = inputs[i];
        }
		m_decoder->process(m_harmonics, m_matrix);
    }
    
    void Scope::process(const double* inputs)
    {
        m_decoder->process(inputs, m_matrix);
    }
    
    Scope::~Scope()
    {
		delete [] m_matrix;
        delete [] m_harmonics;
        delete m_decoder;
    }
	
}

