/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicSourcesManager.h"

SourcesManager::SourcesManager(double aMaximumLimitValue, long deadOrAlive)
{
    setExistence(deadOrAlive);
    setMaximumRadius(aMaximumLimitValue);
    m_zoom = 1.;
}

void SourcesManager::setExistence(long deadOrAlive)
{
    m_existence = Tools::clip(deadOrAlive, (long)0, (long)1);
    if(m_existence == 0)
    {
		m_sources.clear();
		m_groups.clear();
    }
}

void SourcesManager::clearAll()
{
    
    for(int i = 0; i <= getMaximumIndexOfSource(); i++)
        sourceRemove(i);
    for(int i = 0; i <= getMaximumIndexOfGroup(); i++)
        groupRemove(i);
}

long SourcesManager::getExistence()
{
    return m_existence;
}

void SourcesManager::setMaximumRadius(double aLimitValue)
{
    m_maximum_radius = aLimitValue;
    for(int i = 0; i < m_groups.size(); i++)
        m_groups[i]->setMaximumRadius(m_maximum_radius);
}

void SourcesManager::setZoom(double aZoom)
{
    m_zoom = Tools::clip(aZoom, 1. / m_maximum_radius, 1.);
}

double SourcesManager::getZoom()
{
    return m_zoom;
}

double SourcesManager::getLimitMaximum()
{
    return m_maximum_radius;
}

long SourcesManager::getMaximumIndexOfSource()
{
    long index = 0;
    for (int i = 0; i < m_sources.size(); i++)
    {
        if(sourceGetExistence(i))
            index = i;
    }
    return  index;
}

long SourcesManager::getNumberOfSources()
{
    long numberOfSources = 0;
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i]->getExistence())
            numberOfSources++;
    }
    return  numberOfSources;
}

long SourcesManager::getMaximumIndexOfGroup()
{
    return  m_groups.size();
}

long SourcesManager::getNumberOfGroups()
{
    long numberOfGroups = 0;
    for(int i = 0; i < m_groups.size(); i++)
    {
        if (m_groups[i]->getExistence())
            numberOfGroups++;
    }
    return  numberOfGroups;
}

/*******************************************************************************/
/*********************************  SOURCES ************************************/
/*******************************************************************************/

void SourcesManager::sourceRemove(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        int numberOfGroups = m_sources[anIndex]->getNumberOfGroups();
        int indexOfGroup = -1;
        for(int i = 0; i < numberOfGroups; i++)
        {
            indexOfGroup = m_sources[anIndex]->getGroupIndex(i);
            
            if(indexOfGroup >= 0 && indexOfGroup <= getMaximumIndexOfGroup())
            {
                if(groupGetExistence(indexOfGroup))
                    m_groups[indexOfGroup]->removeSource(anIndex);
            }
        }
        m_sources[anIndex]->setExistence(0);
        m_sources[anIndex]->setDescription("");
        m_sources[anIndex]->setColor(0.2, 0.2, 0.2, 1.);
        m_sources[anIndex]->setCoordinatesCartesian(0., 1.);
        m_sources[anIndex]->setMute(0);
    }
}

void SourcesManager::sourceNewPolar(double aRadius, double anAngle)
{
    for (int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetPolar(i, aRadius, anAngle);
            return;
        }
    }
}

void SourcesManager::sourceNewRadius(double aRadius)
{
    for(int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetRadius(i, aRadius);
            return;
        }
    }
}

void SourcesManager::sourceNewAngle(double anAngle)
{
    for(int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetAngle(i, anAngle);
            return;
        }
    }
}

void SourcesManager::sourceNewCartesian(double anAbscissa, double anOrdinate)
{
    for(int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetCartesian(i, anAbscissa, anOrdinate);
            return;
        }
    }
}

void SourcesManager::sourceNewAbscissa(double anAbscissa)
{
    for(int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetAbscissa(i, anAbscissa);
            return;
        }
    }
}

void SourcesManager::sourceNewOrdinate(double anOrdinate)
{
    for(int i = 0; i < getMaximumIndexOfSource()+2; i++)
    {
        if(!sourceGetExistence(i))
        {
            sourceSetOrdinate(i, anOrdinate);
            return;
        }
    }
}

void SourcesManager::sourceSetPolar(long anIndex, double aRadius, double anAngle)
{
    sourceSetRadius(anIndex, aRadius);
    sourceSetAngle(anIndex, anAngle);
}

void SourcesManager::sourceSetRadius(long anIndex, double aRadius)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
            m_sources[i]->setMaximumRadius(m_maximum_radius);
            
        }
        m_sources.push_back(new Source(1));
        m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
        m_sources[anIndex]->setRadius(aRadius);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setRadius(aRadius);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetAngle(long anIndex, double anAngle)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
            m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        m_sources.push_back(new Source(1));
        m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
        m_sources[anIndex]->setAngle(anAngle);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAngle(anAngle);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetCartesian(long anIndex, double anAbscissa, double anOrdinate)
{
    sourceSetAbscissa(anIndex, anAbscissa);
    sourceSetOrdinate(anIndex, anOrdinate);
}

void SourcesManager::sourceSetAbscissa(long anIndex, double anAbscissa)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
            m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        m_sources.push_back(new Source(1));
        m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
        m_sources[anIndex]->setAbscissa(anAbscissa);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAbscissa(anAbscissa);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetOrdinate(long anIndex, double anOrdinate)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
            m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        m_sources.push_back(new Source(1));
        m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
        m_sources[anIndex]->setOrdinate(anOrdinate);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setOrdinate(anOrdinate);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetColor(long anIndex, double red, double green, double blue, double alpha)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setColor(red, green, blue, alpha);
    }
}

void SourcesManager::sourceSetDescription(long anIndex, std::string aDescription)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setDescription(aDescription);
    }
}
void SourcesManager::checkMute()
{
    for(int i = 0; i < m_groups.size(); i++)
    {
        m_groups[i]->setMute(1);
        for(int j = 0; j < m_groups[i]->getNumberOfSources(); j++)
        {
            int sourceIndex = m_groups[i]->getSourceIndex(j);
            if(sourceIndex >= 0 && sourceIndex < m_sources.size())
            {
                if(m_sources[sourceIndex]->getMute() != 1)
                {
                    m_groups[i]->setMute(0);
                }
            }
        }
    }
}

void SourcesManager::sourceSetMute(long anIndex, long aValue)
{
    aValue = Tools::clip(aValue, (long)0, (long)1);
    
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setMute(aValue);
        for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
        {
            int groupIndex = m_sources[anIndex]->getGroupIndex(i);
            if(groupIndex >= 0 && groupIndex < m_groups.size())
            {
                m_groups[groupIndex]->setMute(0);
            }
        }
        checkMute();
    }
}

/******************************************************************************/

double SourcesManager::sourceGetRadius(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getRadius();
    
    return NULL;
}

double SourcesManager::sourceGetAngle(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAngle();
    
    return NULL;
}

double SourcesManager::sourceGetAbscissa(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAbscissa();
    
    return NULL;
}

double SourcesManager::sourceGetOrdinate(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getOrdinate();
    
    return NULL;
}

color SourcesManager::sourceGetColor(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getColor();
    
    color sourceColor = {-1, -1, -1, -1};
    return sourceColor;
}

std::string SourcesManager::sourceGetDescription(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getDescription();
    
    return NULL;
}

long SourcesManager::sourceGetExistence(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getExistence();
    }
    return 0;
}

long SourcesManager::sourceGetNumberOfGroups(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getNumberOfGroups();
    }
    return 0;
}

long SourcesManager::sourceGetGroupIndex(long aSourceIndex, long aGroupIndex)
{
    if(aSourceIndex < m_sources.size() && aSourceIndex >= 0)
    {
        return m_sources[aSourceIndex]->getGroupIndex(aGroupIndex);
    }
    return 0;
}

long SourcesManager::sourceGetMute(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getMute();
    }
    return 0;
}

/*******************************************************************************/
/**********************************  GROUP  ************************************/
/*******************************************************************************/

void SourcesManager::groupSetSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex >= m_groups.size())
    {
        for(int i = m_groups.size(); i < aGroupIndex; i++)
        {
            m_groups.push_back(new SourcesGroup(this, 0));
            m_groups[i]->setMaximumRadius(m_maximum_radius);
            
        }
        m_groups.push_back(new SourcesGroup(this, 0));
        m_groups[aGroupIndex]->setMaximumRadius(m_maximum_radius);
        if(m_sources.size() > aSourceIndex && m_sources[aSourceIndex]->getExistence())
        {
            m_groups[aGroupIndex]->setExistence(1);
            m_groups[aGroupIndex]->addSource(aSourceIndex);
            m_sources[aSourceIndex]->setGroup(aGroupIndex);
            checkMute();
        }
    }
    else if(aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex && m_sources[aSourceIndex]->getExistence())
        {
            m_groups[aGroupIndex]->addSource(aSourceIndex);
            m_sources[aSourceIndex]->setGroup(aGroupIndex);
            m_groups[aGroupIndex]->setExistence(1);
            checkMute();
        }
    }
}

void SourcesManager::groupRemoveSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex)
        {
            m_groups[aGroupIndex]->removeSource(aSourceIndex);
            m_sources[aSourceIndex]->removeGroup(aGroupIndex);
        }
    }
}

void SourcesManager::groupSetPolar(long aGroupIndex, double aRadius, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesPolar(aRadius, anAngle);
    }
}

void SourcesManager::groupSetRadius(long aGroupIndex, double aRadius)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRadius(aRadius);
    }
}

void SourcesManager::groupSetAngle(long aGroupIndex, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setAngle(anAngle);
    }
}

void SourcesManager::groupSetCartesian(long aGroupIndex, double anAbscissa, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesCartesian(anAbscissa, anOrdinate);
    }
}

void SourcesManager::groupSetAbscissa(long aGroupIndex, double anAbscissa)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setAbscissa(anAbscissa);
    }
}

void SourcesManager::groupSetOrdinate(long aGroupIndex, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setOrdinate(anOrdinate);
    }
}

void SourcesManager::groupSetRelativePolar(long aGroupIndex, double aRadius, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeCoordinatesPolar(aRadius, anAngle);
    }
}

void SourcesManager::groupSetRelativeRadius(long aGroupIndex, double aRadius)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeRadius(aRadius);
    }
}

void SourcesManager::groupSetRelativeAngle(long aGroupIndex, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeAngle(anAngle);
    }
}

void SourcesManager::groupSetColor(long aGroupIndex, double red, double green, double blue, double alpha)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setColor(red, green, blue, alpha);
    }
}

void SourcesManager::groupSetDescription(long aGroupIndex, std::string aDescription)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setDescription(aDescription);
    }
}

void SourcesManager::groupRemove(long aGroupIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        for(int i = 0; i < m_sources.size(); i++)
        {
            m_sources[i]->removeGroup(aGroupIndex);
            
        }
        for(int i = 0; i < m_sources.size(); i++)
        {
            m_groups[aGroupIndex]->removeSource(i);
        }
        m_groups[aGroupIndex]->setColor(0.2, 0.2, 0.2, 1.);
        m_groups[aGroupIndex]->setDescription("");
        m_groups[aGroupIndex]->setExistence(0);
        m_groups[aGroupIndex]->setMute(0);
    }
}

void SourcesManager::groupRemoveWithSources(long aGroupIndex)
{
    for(int i = 0; i < getMaximumIndexOfSource(); i++)
    {
        if (m_sources[i]->isOwnedByGroup(aGroupIndex)) {
            sourceRemove(i);
        }
    }
    groupRemove(aGroupIndex);
}

void SourcesManager::groupSetMute(long aGroupIndex, long aValue)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setMute(aValue);
        for(int i = 0; i < m_groups[aGroupIndex]->getNumberOfSources(); i++)
        {
            int sourceIndex = m_groups[aGroupIndex]->getSourceIndex(i);
            if(sourceIndex >= 0 && sourceIndex < m_sources.size())
                m_sources[sourceIndex]->setMute(aValue);
        }
    }
    checkMute();
}


/******************************************************************************/

double SourcesManager::groupGetRadius(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getRadius();
    
    return NULL;
}

double SourcesManager::groupGetAngle(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getAngle();
    
    return NULL;
}

double SourcesManager::groupGetAbscissa(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getAbscissa();
    
    return NULL;
}

double SourcesManager::groupGetOrdinate(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getOrdinate();
    
    return NULL;
}

color SourcesManager::groupGetColor(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getColor();
    
    color groupColor = {-1, -1, -1 -1};
    return groupColor;
}

std::string SourcesManager::groupGetDescription(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getDescription();
    
    return NULL;
}

long SourcesManager::groupGetExistence(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
    {
        return m_groups[anIndex]->getExistence();
    }
    return 0;
}

long SourcesManager::groupGetNumberOfSources(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
    {
        return m_groups[anIndex]->getNumberOfSources();
    }
    return 0;
}

long SourcesManager::groupGetSourceIndex(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        return m_groups[aGroupIndex]->getSourceIndex(aSourceIndex);
    }
    return 0;
}

long SourcesManager::groupGetMute(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
    {
        return m_groups[anIndex]->getMute();
    }
    return 0;
}

long SourcesManager::groupGetIfSourceMuted(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
    {
        for(long i = 0; i < groupGetNumberOfSources(anIndex); i++)
        {
            if(sourceGetMute(groupGetSourceIndex(anIndex, i)))
            {
                return 1;
            }
        }
    }
    return 0;
}

long SourcesManager::groupGetNextIndex()
{
    if(getNumberOfGroups() != 0)
    {
        for(int i = 0; i < getMaximumIndexOfGroup()+2; i++)
        {
            if(!groupGetExistence(i))
            {
                return i;
            }
        }
    }
    return getMaximumIndexOfGroup();
}

void SourcesManager::groupClean()
{
    for(int i = 0; i < getNumberOfGroups(); i++)
    {
        if(groupGetExistence(i))
        {
            for(int j = 0; j < getNumberOfGroups(); j++)
            {
                if (i != j && groupGetExistence(j))
                {
                    if(groupGetNumberOfSources(i) == groupGetNumberOfSources(j))
                    {
                        int check = 0;
                        for(int k = 0; k < groupGetNumberOfSources(i); k++)
                        {
                            for(int l = 0; l < groupGetNumberOfSources(i); l++)
                            {
                                if(groupGetSourceIndex(i, k) == groupGetSourceIndex(j, l))
                                    check++;
                            }
                        }
                        if(check == groupGetNumberOfSources(j))
                            groupRemove(j);
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < getNumberOfGroups(); i++)
    {
        if(groupGetExistence(i))
        {
            if(groupGetNumberOfSources(i) < 2)
            {
                groupRemove(i);
            }
        }
    }
}

int SourcesManager::SourcesGroup::compare(const SourcesGroup* a, const SourcesGroup *b)
{
    auto leftIt = a->m_sources.begin();
    auto rightIt = b->m_sources.begin();
    auto diff = 0;
    while (leftIt != a->m_sources.end() && rightIt != b->m_sources.end())
    {
        if (*leftIt != *rightIt)
        {
            diff++;
        }
        leftIt++;
        rightIt++;
    }
    
    if (0 == diff && (leftIt != a->m_sources.end() || rightIt != b->m_sources.end()))
    {
        diff = 1;
    }
    
    return diff;
}

int SourcesManager::groupCompare(long groupIndexA, const long groupIndexB)
{
    
    return m_groups[groupIndexA]->compare(m_groups[groupIndexA], m_groups[groupIndexB]);
}

/************************************/

SourcesManager::~SourcesManager()
{
    m_sources.clear();
    m_groups.clear();
}