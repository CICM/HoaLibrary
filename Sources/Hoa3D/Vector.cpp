/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Vector.h"

namespace Hoa3D
{
    Vector::Vector(unsigned int numberOfLoudspeakers) : Planewaves(numberOfLoudspeakers)
    {
        m_loudspeakers_float = new float[m_number_of_loudspeakers];
        m_loudspeakers_double = new double[m_number_of_loudspeakers];
        m_loudspeakers_abscissa_float = new float[m_number_of_loudspeakers];
        m_loudspeakers_abscissa_double = new double[m_number_of_loudspeakers];
        m_loudspeakers_ordinate_float = new float[m_number_of_loudspeakers];
        m_loudspeakers_ordinate_double = new double[m_number_of_loudspeakers];
        m_loudspeakers_height_float = new float[m_number_of_loudspeakers];
        m_loudspeakers_height_double = new double[m_number_of_loudspeakers];
        
        for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
        {
            m_loudspeakers_abscissa_float[i] = m_loudspeakers_abscissa_double[i] = getLoudspeakerAbscissa(i);
            m_loudspeakers_ordinate_float[i] = m_loudspeakers_ordinate_double[i] = getLoudspeakerOrdinate(i);
            m_loudspeakers_height_float[i] = m_loudspeakers_height_double[i] = getLoudspeakerHeight(i);
        }
    }
    
    void Vector::setLoudspeakerPosition(unsigned int index, double azimuth, double elevation)
    {
        Planewaves::setLoudspeakerPosition(index, azimuth, elevation);
        for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
        {
            m_loudspeakers_abscissa_float[i] = m_loudspeakers_abscissa_double[i] = getLoudspeakerAbscissa(i);
            m_loudspeakers_ordinate_float[i] = m_loudspeakers_ordinate_double[i] = getLoudspeakerOrdinate(i);
            m_loudspeakers_height_float[i] = m_loudspeakers_height_double[i] = getLoudspeakerHeight(i);
        }
    }
    
    void Vector::processVelocity(const float* inputs, float* outputs)
    {
        float veclocitySum = 0.f, velocityAbscissa = 0.f, velocityOrdinate = 0.f, velocityElevation = 0.f;
        
        veclocitySum = cblas_sasum(m_number_of_loudspeakers, inputs, 1);
        velocityAbscissa = cblas_sdot(m_number_of_loudspeakers, inputs, 1, m_loudspeakers_abscissa_float, 1);
        velocityOrdinate = cblas_sdot(m_number_of_loudspeakers, inputs, 1, m_loudspeakers_ordinate_float, 1);
        velocityElevation= cblas_sdot(m_number_of_loudspeakers, inputs, 1, m_loudspeakers_height_float, 1);
        if(veclocitySum)
        {
            outputs[0] = velocityAbscissa / veclocitySum;
            outputs[1] = velocityOrdinate / veclocitySum;
            outputs[2] = velocityElevation / veclocitySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;

        }
    }
    
    void Vector::processVelocity(const double* inputs, double* outputs)
    {
        double veclocitySum = 0., velocityAbscissa = 0., velocityOrdinate = 0., velocityElevation = 0.;
        veclocitySum = cblas_dasum(m_number_of_loudspeakers, m_loudspeakers_double, 1);
        velocityAbscissa = cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_abscissa_double, 1);
        velocityOrdinate = cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_ordinate_double, 1);
        velocityElevation= cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_height_double, 1);
        
        if(veclocitySum)
        {
            outputs[0] = velocityAbscissa / veclocitySum;
            outputs[1] = velocityOrdinate / veclocitySum;
            outputs[2] = velocityElevation / veclocitySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;
        }
    }
    
    void Vector::processEnergy(const float* inputs, float* outputs)
    {
        float energySum = 0.f, energyAbscissa = 0.f, energyOrdinate = 0.f, energyElevation = 0.f;
        cblas_scopy(m_number_of_loudspeakers, inputs, 1, m_loudspeakers_float, 1);
        for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            m_loudspeakers_float[i] *= m_loudspeakers_float[i];
        
        energySum = cblas_sasum(m_number_of_loudspeakers, m_loudspeakers_float, 1);
        energyAbscissa = cblas_sdot(m_number_of_loudspeakers, m_loudspeakers_float, 1, m_loudspeakers_abscissa_float, 1);
        energyOrdinate = cblas_sdot(m_number_of_loudspeakers, m_loudspeakers_float, 1, m_loudspeakers_ordinate_float, 1);
        energyElevation = cblas_sdot(m_number_of_loudspeakers, m_loudspeakers_float, 1, m_loudspeakers_height_float, 1);
        
        if(energySum)
        {
            outputs[0] = energyAbscissa / energySum;
            outputs[1] = energyOrdinate / energySum;
            outputs[2] = energyElevation / energySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;
        }
    }
    
    void Vector::processEnergy(const double* inputs, double* outputs)
    {
        double energySum = 0., energyAbscissa = 0., energyOrdinate = 0., energyElevation = 0.;
        
        cblas_dcopy(m_number_of_loudspeakers, inputs, 1, m_loudspeakers_double, 1);
        for(unsigned int i = 0; i < m_number_of_loudspeakers; i++)
            m_loudspeakers_double[i] *= m_loudspeakers_double[i];
        
        energySum = cblas_dasum(m_number_of_loudspeakers, m_loudspeakers_double, 1);
        energyAbscissa = cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_abscissa_double, 1);
        energyOrdinate = cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_ordinate_double, 1);
        energyElevation = cblas_ddot(m_number_of_loudspeakers, m_loudspeakers_double, 1, m_loudspeakers_height_double, 1);
        
        if(energySum)
        {
            outputs[0] = energyAbscissa / energySum;
            outputs[1] = energyOrdinate / energySum;
            outputs[2] = energyElevation / energySum;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;
        }
    }
    
    void Vector::process(const float* inputs, float* outputs)
    {
        processVelocity(inputs, outputs);
        processEnergy(inputs, outputs+3);
    }
    
    void Vector::process(const double* inputs, double* outputs)
    {
        processVelocity(inputs, outputs);
        processEnergy(inputs, outputs+3);
    }
    
    Vector::~Vector()
    {
        delete [] m_loudspeakers_float;
        delete [] m_loudspeakers_double;
        delete [] m_loudspeakers_ordinate_float;
        delete [] m_loudspeakers_ordinate_double;
        delete [] m_loudspeakers_abscissa_float;
        delete [] m_loudspeakers_abscissa_double;
        delete [] m_loudspeakers_height_float;
        delete [] m_loudspeakers_height_double;
    }
}

