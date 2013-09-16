/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef DEF_AMBISONICVECTOR
#define DEF_AMBISONICVECTOR

#include "../HoaAmbisonics/Planewaves.h"

class AmbisonicVector : public Planewaves
{	
private:

    cicm_vector_double  m_loudspeakers_double;
    cicm_vector_float   m_loudspeakers_float;
    
    cicm_vector_float	m_vector_float;
    cicm_vector_double	m_vector_double;
    
    double       m_outputs_double[4];
    float        m_outputs_float[4];
    
public:
	AmbisonicVector(long aNumberOfLoudspeakers = 1., long aVectorSize = 0);
	
    std::string  getVectorName(long anIndex);
    void setVectorSize(long aVectorSize);
	~AmbisonicVector();
    
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/

	inline void process(const double* inputs, double* outputs)
	{
        double veclocitySum = 0., velocityAbscissa = 0., velocityOrdinate = 0.;
        double energySum = 0., energyAbscissa = 0., energyOrdinate = 0.;
        
        cicm_copy_vec_vec_d(inputs, m_vector_double, m_number_of_loudspeakers);
        veclocitySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_abscissa_of_loudspeakers_double, velocityAbscissa,m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_ordinate_of_loudspeakers_double, velocityOrdinate,m_number_of_loudspeakers);
        
        
        for(int i = 0; i < m_number_of_loudspeakers; i++)
            m_vector_double[i] *= m_vector_double[i];
        
        energySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_abscissa_of_loudspeakers_double, energyAbscissa, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_ordinate_of_loudspeakers_double, energyOrdinate, m_number_of_loudspeakers);
        
        if(veclocitySum != 0. && energySum != 0.)
        {
            velocityAbscissa /= veclocitySum;
            velocityOrdinate /= veclocitySum;
            energyAbscissa /= energySum;
            energyOrdinate /= energySum;
            outputs[0] = velocityAbscissa;
            outputs[1] = velocityOrdinate;
            outputs[2] = energyAbscissa;
            outputs[3] = energyOrdinate;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;
            outputs[3] = 0.;
        }
	}
    
    inline void processVelocity(const double* inputs, double *outputs)
	{
        double veclocitySum = 0., velocityAbscissa = 0., velocityOrdinate = 0.;
        
        cicm_copy_vec_vec_d(inputs, m_vector_double, m_number_of_loudspeakers);
        veclocitySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_abscissa_of_loudspeakers_double, velocityAbscissa,m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_ordinate_of_loudspeakers_double, velocityOrdinate,m_number_of_loudspeakers);
        
        if(veclocitySum != 0. )
        {
            velocityAbscissa /= veclocitySum;
            velocityOrdinate /= veclocitySum;
            outputs[0] = velocityAbscissa;
            outputs[1] = velocityOrdinate;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
	}
    
    inline void processEnergy(const double* inputs, double *outputs)
	{
        double energySum = 0., energyAbscissa = 0., energyOrdinate = 0.;
        
        cicm_copy_vec_vec_d(inputs, m_vector_double, m_number_of_loudspeakers);
        for(int i = 0; i < m_number_of_loudspeakers; i++)
        {
            m_vector_double[i] *= m_vector_double[i];
        }
        energySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_abscissa_of_loudspeakers_double, energyAbscissa, m_number_of_loudspeakers);
        cicm_dot_product_d(m_vector_double, m_ordinate_of_loudspeakers_double, energyOrdinate, m_number_of_loudspeakers);
        
        if(energySum != 0.)
        {
            energyAbscissa /= energySum;
            energyOrdinate /= energySum;
            outputs[0] = energyAbscissa;
            outputs[1] = energyOrdinate;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
        }
	}
    
    inline void process(float* inputs, float *outputs)
	{
        float veclocitySum = 0.;
        float velocityAbscissa = 0., velocityOrdinate = 0.;
        float energySum = 0.;
        float energyAbscissa = 0., energyOrdinate = 0.;
        
        veclocitySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_f(inputs, m_abscissa_of_loudspeakers_float, velocityAbscissa, m_number_of_loudspeakers);
        cicm_dot_product_f(inputs, m_ordinate_of_loudspeakers_float, velocityOrdinate, m_number_of_loudspeakers);
        
        cicm_product_vec_f(inputs, inputs, m_number_of_loudspeakers);
        energySum = Tools::sum(m_vector_double, m_number_of_loudspeakers);
        cicm_dot_product_f(inputs, m_abscissa_of_loudspeakers_float, energyAbscissa, m_number_of_loudspeakers);
        cicm_dot_product_f(inputs, m_ordinate_of_loudspeakers_float, energyOrdinate, m_number_of_loudspeakers);
        
        if(veclocitySum != 0. && energySum != 0.)
        {
            velocityAbscissa /= veclocitySum;
            velocityOrdinate /= veclocitySum;
            energyAbscissa /= energySum;
            energyAbscissa /= energySum;
            outputs[0] = velocityAbscissa;
            outputs[1] = velocityOrdinate;
            outputs[2] = energyAbscissa;
            outputs[3] = energyOrdinate;
        }
        else
        {
            outputs[0] = 0.;
            outputs[1] = 0.;
            outputs[2] = 0.;
            outputs[3] = 0.;
        }
    }
	
	/************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* const* inputs, double** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_double[i] = inputs[i][j];
            
            process(m_loudspeakers_double, m_outputs_double);
            
            for(int i = 0; i < 4; i++)
                outputs[i][j] = m_outputs_double[i];
        }
	}
    
    inline void processVelocity(const double* const* inputs, double** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_double[i] = inputs[i][j];
            
            processVelocity(m_loudspeakers_double, m_outputs_double);
            
            for(int i = 0; i < 2; i++)
                outputs[i][j] = m_outputs_double[i];
        }
	}
    
    inline void processEnergy(const double* const* inputs, double** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_double[i] = inputs[i][j];
            
            processEnergy(m_loudspeakers_double, m_outputs_double);
            
            for(int i = 0; i < 2; i++)
                outputs[i][j] = m_outputs_double[i];
        }
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_float[i] = inputs[i][j];
            
            process(m_loudspeakers_float, m_outputs_float);
            
            for(int i = 0; i < 4; i++)
                outputs[i][j] = m_outputs_float[i];
        }
	}
    
    inline void processVelocity(const float* const* inputs, float** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_float[i] = inputs[i][j];
            
            process(m_loudspeakers_float, m_outputs_float);
            
            for(int i = 0; i < 2; i++)
                outputs[i][j] = m_outputs_float[i];
        }
	}
    
    inline void processEnergy(const float* const* inputs, float** outputs)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            for(int i = 0; i < m_number_of_loudspeakers; i++)
                m_loudspeakers_float[i] = inputs[i][j];
            
            process(m_loudspeakers_float, m_outputs_float);
            
            for(int i = 0; i < 2; i++)
                outputs[i][j] = m_outputs_float[i];
        }
	}
	
};

#endif