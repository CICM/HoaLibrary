/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Vector.h"

namespace Hoa2D
{
    Vector::Vector(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        m_loudspeakers_float = new float[m_number_of_channels];
        m_loudspeakers_double = new double[m_number_of_channels];
        m_loudspeakers_abscissa_float = new float[m_number_of_channels];
        m_loudspeakers_abscissa_double = new double[m_number_of_channels];
        m_loudspeakers_ordinate_float = new float[m_number_of_channels];
        m_loudspeakers_ordinate_double = new double[m_number_of_channels];
        
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_loudspeakers_abscissa_float[i] = m_loudspeakers_abscissa_double[i] = getChannelAbscissa(i);
            m_loudspeakers_ordinate_float[i] = m_loudspeakers_ordinate_double[i] = getChannelOrdinate(i);
        }
    }
    
    void Vector::setChannelPosition(unsigned int index, double azimuth)
    {
        Planewaves::setChannelPosition(index, azimuth);
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_loudspeakers_abscissa_float[i] = m_loudspeakers_abscissa_double[i] = getChannelAbscissa(i);
            m_loudspeakers_ordinate_float[i] = m_loudspeakers_ordinate_double[i] = getChannelOrdinate(i);
        }
    }
    
    void Vector::processVelocity(const float* inputs, float* outputs)
    {
        float veclocitySum = 0.f, velocityAbscissa = 0.f, velocityOrdinate = 0.f;
        
        veclocitySum = cblas_sasum(m_number_of_channels, inputs, 1);
        velocityAbscissa = cblas_sdot(m_number_of_channels, inputs, 1, m_loudspeakers_abscissa_float, 1);
        velocityOrdinate = cblas_sdot(m_number_of_channels, inputs, 1, m_loudspeakers_ordinate_float, 1);
        if(veclocitySum)
        {
            outputs[0] = velocityAbscissa / veclocitySum;
            outputs[1] = velocityOrdinate / veclocitySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
    }
    
    void Vector::processVelocity(const double* inputs, double* outputs)
    {
        double veclocitySum = 0., velocityAbscissa = 0., velocityOrdinate = 0.;
        veclocitySum = cblas_dasum(m_number_of_channels, m_loudspeakers_double, 1);
        velocityAbscissa = cblas_ddot(m_number_of_channels, m_loudspeakers_double, 1, m_loudspeakers_abscissa_double, 1);
        velocityOrdinate = cblas_ddot(m_number_of_channels, m_loudspeakers_double, 1, m_loudspeakers_ordinate_double, 1);
        
        if(veclocitySum)
        {
            outputs[0] = velocityAbscissa / veclocitySum;
            outputs[1] = velocityOrdinate / veclocitySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
    }
    
    void Vector::processEnergy(const float* inputs, float* outputs)
    {
        float energySum = 0.f, energyAbscissa = 0.f, energyOrdinate = 0.f;
        cblas_scopy(m_number_of_channels, inputs, 1, m_loudspeakers_float, 1);
        for(int i = 0; i < m_number_of_channels; i++)
            m_loudspeakers_float[i] *= m_loudspeakers_float[i];
        
        energySum = cblas_sasum(m_number_of_channels, m_loudspeakers_float, 1);
        energyAbscissa = cblas_sdot(m_number_of_channels, m_loudspeakers_float, 1, m_loudspeakers_abscissa_float, 1);
        energyOrdinate = cblas_sdot(m_number_of_channels, m_loudspeakers_float, 1, m_loudspeakers_ordinate_float, 1);
        
        if(energySum)
        {
            outputs[0] = energyAbscissa / energySum;
            outputs[1] = energyOrdinate / energySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
    }
    
    void Vector::processEnergy(const double* inputs, double* outputs)
    {
        double energySum = 0., energyAbscissa = 0., energyOrdinate = 0.;
        
        cblas_dcopy(m_number_of_channels, inputs, 1, m_loudspeakers_double, 1);
        for(int i = 0; i < m_number_of_channels; i++)
            m_loudspeakers_double[i] *= m_loudspeakers_double[i];
        
        energySum = cblas_dasum(m_number_of_channels, m_loudspeakers_double, 1);
        energyAbscissa = cblas_ddot(m_number_of_channels, m_loudspeakers_double, 1, m_loudspeakers_abscissa_double, 1);
        energyOrdinate = cblas_ddot(m_number_of_channels, m_loudspeakers_double, 1, m_loudspeakers_ordinate_double, 1);
        
        if(energySum)
        {
            outputs[0] = energyAbscissa / energySum;
            outputs[1] = energyOrdinate / energySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
    }
    
    void Vector::process(const float* inputs, float* outputs)
    {
        processVelocity(inputs, outputs);
        processEnergy(inputs, outputs+2);
    }
    
    void Vector::process(const double* inputs, double* outputs)
    {
        processVelocity(inputs, outputs);
        processEnergy(inputs, outputs+2);
    }
    
    Vector::~Vector()
    {
        delete [] m_loudspeakers_float;
        delete [] m_loudspeakers_double;
        delete [] m_loudspeakers_ordinate_float;
        delete [] m_loudspeakers_ordinate_double;
        delete [] m_loudspeakers_abscissa_float;
        delete [] m_loudspeakers_abscissa_double;
    }
}

