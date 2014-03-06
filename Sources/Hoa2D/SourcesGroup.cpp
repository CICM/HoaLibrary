/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#include "SourcesManager.h"

SourcesManager::SourcesGroup::SourcesGroup(SourcesManager* aSourceManager, long deadOrAlive)
{
    m_source_manager = aSourceManager;
    setExistence(deadOrAlive);
    setColor(0.2, 0.2, 0.2, 1.);
    setDescription("");
    computeCentroid();
    m_maximum_radius = -1;
    m_mute = 0;
}

void SourcesManager::SourcesGroup::setExistence(long deadOrAlive)
{
    m_exist = clip_minmax(deadOrAlive, (long)0, (long)1);
}

void SourcesManager::SourcesGroup::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void SourcesManager::SourcesGroup::setColor(double red, double green, double blue, double alpha)
{
    m_color.red		=  clip_minmax(red, 0., 1.);
    m_color.green	=  clip_minmax(green, 0., 1.);
    m_color.blue	=  clip_minmax(blue, 0., 1.);
    m_color.alpha	=  clip_minmax(alpha, 0., 1.);
}

void SourcesManager::SourcesGroup::setMaximumRadius(double aLimitValue)
{
    m_maximum_radius = aLimitValue;
}

void SourcesManager::SourcesGroup::computeCentroid()
{
    m_centroid.x = 0.;
    m_centroid.y = 0.;
    if(m_sources.size())
    {
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_source_manager->sourceGetExistence(m_sources[i]))
            {
                m_centroid.x += m_source_manager->sourceGetAbscissa(m_sources[i]);
                m_centroid.y += m_source_manager->sourceGetOrdinate(m_sources[i]);
            }
        }
        m_centroid.x /= m_sources.size();
        m_centroid.y /= m_sources.size();
    }
}

void SourcesManager::SourcesGroup::addSource(long aSourceIndex)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] == aSourceIndex)
            return;
    }
    m_sources.push_back(aSourceIndex);
    
    computeCentroid();
}

void SourcesManager::SourcesGroup::sourceHasMoved()
{
    computeCentroid();
}

void SourcesManager::SourcesGroup::removeSource(long aSourceIndex)
{
    if(m_sources.size() > 0)
    {
        int size = m_sources.size();
        
        for(int i = 0; i < size; i++)
        {
            if(m_sources[i] == aSourceIndex)
            {
                for(int j = i; j < size - 1; j++)
                {
                    m_sources[j] = m_sources[j+1];
                }
                m_sources.pop_back();
            }
        }
    }
    computeCentroid();
}

void SourcesManager::SourcesGroup::shiftPolar(double aRadius, double anAngle)
{
    shiftRadius(aRadius);
    shiftAngle(anAngle);
}

void SourcesManager::SourcesGroup::shiftRadius(double aRadius)
{
    if(m_maximum_radius >= 0)
    {
        if(aRadius < 0.)
        {
            double refRadius = m_maximum_radius;
            for(int i = 0; i < m_sources.size(); i++)
            {
                if(m_source_manager->sourceGetRadius(m_sources[i]) < refRadius)
                {
                    refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                }
            }
            if(aRadius + refRadius < 0.)
            {
                aRadius = - refRadius;
            }
        }
        else if(aRadius >= 0.)
        {
            double refRadius = -m_maximum_radius;
            for(int i = 0; i < m_sources.size(); i++)
            {
                if(m_source_manager->sourceGetRadius(m_sources[i]) > refRadius)
                {
                    refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                }
            }
            if(aRadius + refRadius > m_maximum_radius)
            {
                aRadius = m_maximum_radius - refRadius;
            }
        }
    }
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetRadius(m_sources[i], aRadius + m_source_manager->sourceGetRadius(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftAngle(double anAngle)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAngle(m_sources[i], anAngle + m_source_manager->sourceGetAngle(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftAbscissa(double anAbscissa)
{
    if(m_maximum_radius >= 0)
    {
        if(anAbscissa < 0.)
        {
            double refAbcsissa = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) > refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa < refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
        else if(anAbscissa >= 0.)
        {
            double refAbcsissa = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) < refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa > refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
    }

    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftOrdinate(double anOrdinate)
{
    if(m_maximum_radius >= 0)
    {
        if(anOrdinate < 0.)
        {
            double refOrdinate = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleOrdinate = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) > refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anOrdinate < refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
        else if(anOrdinate >= 0.)
        {
            double refOrdinate = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleOrdinate = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) < refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anOrdinate > refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
    }
    
    for(int i = 0; i < m_sources.size(); i++)
    {
       m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftCartesian(double anAbscissa, double anOrdinate)
{
    if(m_maximum_radius >= 0)
    {
        if(anAbscissa < 0. &&  anOrdinate < 0.)
        {
            double refAbcsissa = -m_maximum_radius * 2.;
            double refOrdinate = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                double circleOrdinate = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) > refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) > refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anAbscissa < refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
            if(anOrdinate < refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
        else if(anAbscissa >= 0.)
        {
            double refAbcsissa = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) < refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa > refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
    }
    
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
        m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::setCoordinatesPolar(double aRadius, double anAngle)
{
    setCoordinatesCartesian(abscissa(aRadius, anAngle), ordinate(aRadius, anAngle));
}

void SourcesManager::SourcesGroup::setRadius(double aRadius)
{
    setCoordinatesCartesian(abscissa(aRadius, getAngle()), ordinate(aRadius, getAngle()));
}

void SourcesManager::SourcesGroup::setAngle(double anAngle)
{
    setCoordinatesCartesian(abscissa(getRadius(), anAngle), ordinate(getRadius(), anAngle));
}

void SourcesManager::SourcesGroup::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    anAbscissa = anAbscissa - getAbscissa();
    anOrdinate = anOrdinate - getOrdinate();
    shiftAbscissa(anAbscissa);
    shiftOrdinate(anOrdinate);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setAbscissa(double anAbscissa)
{
    double aAbscissaOffset = anAbscissa - getAbscissa();
    shiftAbscissa(aAbscissaOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setOrdinate(double anOrdinate)
{
    double aOrdinateOffset = anOrdinate - getOrdinate();
    shiftOrdinate(aOrdinateOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setRelativeCoordinatesPolar(double aRadius, double anAngle)
{
    setRelativeRadius(aRadius);
    setRelativeAngle(anAngle);
}

void SourcesManager::SourcesGroup::setRelativeRadius(double aRadius)
{
    double aRadiusOffset = clip_min(aRadius, 0.) - getRadius();
    shiftRadius(aRadiusOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setRelativeAngle(double anAngle)
{
    anAngle +=  HOA_PI2;
    while (anAngle > HOA_2PI)
        anAngle -= HOA_2PI;
    while (anAngle < 0.)
        anAngle += HOA_2PI;
    
    double aAngleOffset = anAngle  - getAngle();
    shiftAngle(aAngleOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setMute(long aValue)
{
    m_mute = clip_minmax(aValue, (long)0, (long)1);
}

double SourcesManager::SourcesGroup::getRadius()
{
    return radius(m_centroid.x, m_centroid.y);
}

double SourcesManager::SourcesGroup::getAngle()
{
    return azimuth(m_centroid.x, m_centroid.y) + HOA_PI2;
}

double SourcesManager::SourcesGroup::getAbscissa()
{
    return m_centroid.x;
}

double SourcesManager::SourcesGroup::getOrdinate()
{
    return m_centroid.y;
}

long SourcesManager::SourcesGroup::getNumberOfSources()
{
    return m_sources.size();
}


long SourcesManager::SourcesGroup::getSourceIndex(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex];
    else
        return -1;
}


t_hoa_rgba SourcesManager::SourcesGroup::getColor()
{
    return m_color;
}

long SourcesManager::SourcesGroup::getExistence()
{
    return m_exist;
}

std::string SourcesManager::SourcesGroup::getDescription()
{
    return m_description;
}

long SourcesManager::SourcesGroup::getMute()
{
    return m_mute;
}


SourcesManager::SourcesGroup::~SourcesGroup()
{
    m_sources.clear();
}