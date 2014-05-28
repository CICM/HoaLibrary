/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_MAP_POLAR_LINES_3D__
#define __DEF_MAP_POLAR_LINES_3D__

#include "../Hoa3D.max.h"

class MapPolarLines3D
{
    
private:
    float*      m_values_old;
    float*      m_values_new;
    float*      m_values_step;
    unsigned int m_counter;
    unsigned int m_ramp;
    unsigned int m_number_of_sources;
    
public:
    MapPolarLines3D(unsigned int numberOfSources);
    ~MapPolarLines3D();
    
    inline unsigned int getNumberOfSources() const
    {
        return m_number_of_sources;
    }
    
    inline unsigned int getRamp() const
    {
        return m_ramp;
    }
    
    inline double getRadius(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[index];
    }
    
    inline double getAzimuth(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[m_number_of_sources +index];
    }
    
    inline double getElevation(unsigned int index) const
    {
        assert(index < m_number_of_sources);
        return m_values_new[m_number_of_sources * 2 +index];
    }
    
    void setRamp(unsigned int ramp);
    void setRadius(unsigned int index, double radius);
    void setAzimuth(unsigned int index, double azimuth);
    void setElevation(unsigned int index, double elevation);
    void setRadiusDirect(unsigned int index, double radius);
    void setAzimuthDirect(unsigned int index, double azimuth);
    void setElevationDirect(unsigned int index, double elevation);
    
    void process(float* vector);
};


#endif


