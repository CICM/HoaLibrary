//
//  File.h
//  hoa.encoder3D~
//
//  Created by Guillot Pierre on 03/02/14.
//
//

#ifndef DEF_CICMVECTOR
#define DEF_CICMVECTOR

#include "CicmDefine.h"

namespace Cicm
{
    class SignalVectorFloat
    {
        
    private:
        unsigned long m_size;
        float*        m_vector;
    public:

        SignalVectorFloat(unsigned long size)
        {
            m_size   = size;
            m_vector = new float[m_size];
        };
        
        ~SignalVectorFloat()
        {
            delete [] m_vector;
        };
        
        /*
        SignalVector operator=(SignalVector const& a, SignalVector const& b);
       
        SignalVector operator+(SignalVector const& a, SignalVector const& b);
        SignalVector operator-(SignalVector const& a, SignalVector const& b);
        SignalVector operator*(SignalVector const& a, SignalVector const& b);
        SignalVector operator/(SignalVector const& a, SignalVector const& b);
          */
        
        
        long size()
        {
            return m_size;
        };
        
        void clear()
        {
            int i = m_size;
            while(--i)
                m_vector[i] = 0;
        };
        /*
        void set(const Type value)
        {
            int i = m_size;
            while(--i)
                m_vector[i] = value;
        };
        
        void copy(SignalVector vector);
        void copy(double vector);
        */
        SignalVectorFloat& operator+=(SignalVectorFloat const& other)
        {
            int size;
            if(this->m_size <= other.m_size)
                size = this->m_size;
            else
                size = other.m_size;
            cblas_saxpy(size, 1.f, other.m_vector, 1, this->m_vector, 1);
            return *this;
        };
        
        SignalVectorFloat& operator-=(SignalVectorFloat const& other)
        {
            int size;
            if(this->m_size <= other.m_size)
                size = this->m_size;
            else
                size = other.m_size;
            cblas_saxpy(size, -1.f, other.m_vector, 1, this->m_vector, 1);
            return *this;
        };
        
        SignalVectorFloat& operator*=(SignalVectorFloat const& other)
        {
            int size;
            if(this->m_size <= other.m_size)
                size = this->m_size;
            else
                size = other.m_size;
            catlas_saxpby(size, 1.f, other.m_vector, 1, 1.f, this->m_vector, 1);
            return *this;
        };
        
        SignalVectorFloat& operator/=(SignalVectorFloat const& other)
        {
            int size;
            if(this->m_size <= other.m_size)
                size = this->m_size;
            else
                size = other.m_size;
            while(--size)
                this->m_vector[size] /= other.m_vector[size];
            
            return *this;
        };
    };
}
#endif
