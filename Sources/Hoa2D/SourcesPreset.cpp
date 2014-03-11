/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "SourcesPreset.h"

namespace Hoa2D
{
	SourcesPreset::SourcesPreset()
	{
		m_last_slot_stored = -1;
	}
	
	void SourcesPreset::copySourceManager(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination)
	{
		double* color;
		sourcesManagerDestination->setExistence(0);
		if(sourcesManagerSource->getExistence() == 1)
		{
			sourcesManagerDestination->setExistence(1);
			sourcesManagerDestination->setMaximumRadius(sourcesManagerSource->getLimitMaximum());
			
			for(long i = 0; i <= sourcesManagerSource->getMaximumIndexOfSource(); i++)
			{
				if(sourcesManagerSource->sourceGetExistence(i) == 1)
				{
					color = sourcesManagerSource->sourceGetColor(i);
					sourcesManagerDestination->sourceSetRadius(i, sourcesManagerSource->sourceGetRadius(i));
					sourcesManagerDestination->sourceSetAzimuth(i, sourcesManagerSource->sourceGetAzimuth(i));
					sourcesManagerDestination->sourceSetColor(i, color[0], color[1], color[2], color[3]);
					sourcesManagerDestination->sourceSetDescription(i, sourcesManagerSource->sourceGetDescription(i));
					sourcesManagerDestination->sourceSetMute(i, sourcesManagerSource->sourceGetMute(i));
				}
			}
			for(long i = 0; i <= sourcesManagerSource->getMaximumIndexOfGroup(); i++)
			{
				if(sourcesManagerSource->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < sourcesManagerSource->groupGetNumberOfSources(i); j++)
					{
						sourcesManagerDestination->groupSetSource(i, sourcesManagerSource->groupGetSourceIndex(i, j));
					}
					color = sourcesManagerSource->groupGetColor(i);
					sourcesManagerDestination->groupSetColor(i, color[0], color[1], color[2], color[3]);
					sourcesManagerDestination->groupSetDescription(i, sourcesManagerSource->groupGetDescription(i));
				}
			}
		}
	}
	
	void SourcesPreset::copySource(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination, long sourceIndex)
	{
		double* color;
		if(sourcesManagerSource->getExistence() == 1)
		{
			if(sourcesManagerDestination->getExistence() == 0)
				sourcesManagerDestination->setExistence(1);
			
			if(sourcesManagerSource->getMaximumIndexOfSource() >= sourceIndex && sourceIndex >= 0 && sourcesManagerSource->sourceGetExistence(sourceIndex) == 1)
			{
				color = sourcesManagerSource->sourceGetColor(sourceIndex);
				sourcesManagerDestination->sourceSetRadius(sourceIndex, sourcesManagerSource->sourceGetRadius(sourceIndex));
				sourcesManagerDestination->sourceSetAzimuth(sourceIndex, sourcesManagerSource->sourceGetAzimuth(sourceIndex));
				sourcesManagerDestination->sourceSetColor(sourceIndex, color[0], color[1], color[2], color[3]);
				sourcesManagerDestination->sourceSetDescription(sourceIndex, sourcesManagerSource->sourceGetDescription(sourceIndex));
				sourcesManagerDestination->sourceSetMute(sourceIndex, sourcesManagerSource->sourceGetMute(sourceIndex));
				for(int i = 0; i < sourcesManagerSource->sourceGetNumberOfGroups(sourceIndex); i++)
				{
					sourcesManagerDestination->groupSetSource(sourcesManagerSource->sourceGetGroupIndex(sourceIndex, i), sourceIndex);
				}
			}
		}
	}
	
	void SourcesPreset::copyGroup(SourcesManager* sourcesManagerSource, SourcesManager* sourcesManagerDestination, long groupIndex)
	{
		double* color;
		if(sourcesManagerSource->getExistence() == 1)
		{
			if(sourcesManagerDestination->getExistence() == 0)
				sourcesManagerDestination->setExistence(1);
			if(sourcesManagerSource->getMaximumIndexOfGroup() >= groupIndex && groupIndex >= 0 && sourcesManagerSource->groupGetExistence(groupIndex) == 1)
			{
				for(long j = 0; j < sourcesManagerSource->groupGetNumberOfSources(groupIndex); j++)
				{
					copySource(sourcesManagerSource, sourcesManagerDestination, sourcesManagerSource->groupGetSourceIndex(groupIndex, j));
					sourcesManagerDestination->groupSetSource(groupIndex, sourcesManagerSource->groupGetSourceIndex(groupIndex, j));
				}
				color = sourcesManagerSource->groupGetColor(groupIndex);
				sourcesManagerDestination->groupSetColor(groupIndex, color[0], color[1], color[2], color[3]);
				sourcesManagerDestination->groupSetDescription(groupIndex, sourcesManagerSource->groupGetDescription(groupIndex));
			}
		}
	}
	
	long SourcesPreset::interpolationSourceManager(SourcesManager* sourcesManagerSourceOne, SourcesManager* sourcesManagerSourceTwo, SourcesManager* sourcesManagerDestination, double aFrac)
	{
		double *color1, *color2;
		sourcesManagerDestination->setExistence(0);
		if(sourcesManagerSourceOne->getExistence() == 1 && sourcesManagerSourceTwo->getExistence() == 1)
		{
			sourcesManagerDestination->setExistence(1);
			sourcesManagerDestination->setMaximumRadius(sourcesManagerSourceOne->getLimitMaximum());
			
			for(long i = 0; i <= sourcesManagerSourceOne->getMaximumIndexOfSource(); i++)
			{
				if(sourcesManagerSourceOne->sourceGetExistence(i) == 1 && sourcesManagerSourceTwo->sourceGetExistence(i) == 1)
				{
					color1 = sourcesManagerSourceOne->sourceGetColor(i);
					color2 = sourcesManagerSourceTwo->sourceGetColor(i);
					sourcesManagerDestination->sourceSetAbscissa(i, sourcesManagerSourceOne->sourceGetAbscissa(i) * (1 - aFrac)
																+ sourcesManagerSourceTwo->sourceGetAbscissa(i) * aFrac);
					sourcesManagerDestination->sourceSetOrdinate(i,  sourcesManagerSourceOne->sourceGetOrdinate(i) * (1 - aFrac)
																+ sourcesManagerSourceTwo->sourceGetOrdinate(i) * aFrac);
					sourcesManagerDestination->sourceSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
																color1[1] * (1. - aFrac) + color2[1] * aFrac,
																color1[2] * (1. - aFrac) + color2[2] * aFrac,
																color1[3] * (1. - aFrac) + color2[3] * aFrac);
					
				}
				else if(sourcesManagerSourceOne->sourceGetExistence(i) == 1 && sourcesManagerSourceTwo->sourceGetExistence(i) == 0)
				{
					color1 = sourcesManagerSourceOne->sourceGetColor(i);
					
					sourcesManagerDestination->sourceSetRadius(i, sourcesManagerSourceOne->sourceGetRadius(i));
					sourcesManagerDestination->sourceSetAzimuth(i, sourcesManagerSourceOne->sourceGetAzimuth(i));
					sourcesManagerDestination->sourceSetColor(i, color1[0], color1[1], color1[2], color1[3]);
				}
				sourcesManagerDestination->sourceSetDescription(i, sourcesManagerSourceOne->sourceGetDescription(i));
				sourcesManagerDestination->sourceSetMute(i, sourcesManagerSourceOne->sourceGetMute(i));
			}
			for(long i = 0; i <= sourcesManagerSourceOne->getMaximumIndexOfGroup(); i++)
			{
				if(sourcesManagerSourceOne->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < sourcesManagerSourceOne->groupGetNumberOfSources(i); j++)
					{
						sourcesManagerDestination->groupSetSource(i, sourcesManagerSourceOne->groupGetSourceIndex(i, j));
					}
					color1 = sourcesManagerSourceOne->groupGetColor(i);
					sourcesManagerDestination->groupSetColor(i, color1[0], color1[1], color1[2], color1[3]);
					sourcesManagerDestination->groupSetDescription(i, sourcesManagerSourceOne->groupGetDescription(i));
				}
				if(sourcesManagerSourceOne->groupGetExistence(i) == 1 && sourcesManagerSourceTwo->groupGetExistence(i) == 1 )
				{
					color1 = sourcesManagerSourceOne->groupGetColor(i);
					color2 = sourcesManagerSourceTwo->groupGetColor(i);
					sourcesManagerDestination->groupSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
															color1[1] * (1. - aFrac) + color2[1] * aFrac,
															color1[2] * (1. - aFrac) + color2[2] * aFrac,
															color1[3] * (1. - aFrac) + color2[3] * aFrac);
				}
			}
			return 1;
		}
		return 0;
	}
	
	/*************************************************************************************/
	/*************************************************************************************/
	/*************************************************************************************/
	
	void SourcesPreset::storeSourceManagerAtSlot(SourcesManager* sourcesManager, long index)
	{
		if(index >= 0)
		{
			if(index >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= index; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySourceManager(sourcesManager, m_source_managers[index]);
			m_last_slot_stored = index;
		}
	}
	
	void SourcesPreset::storeSourceManagerAtFirstEmptySlot(SourcesManager* sourcesManager)
	{
		for(long i = 0; i < m_source_managers.size(); i++)
		{
			if(!m_source_managers[i]->getExistence())
			{
				storeSourceManagerAtSlot(sourcesManager, i);
				return;
			}
		}
		storeSourceManagerAtSlot(sourcesManager, m_source_managers.size());
	}
	
	
	void SourcesPreset::storeSourceManagerAtLastUsedSlot(SourcesManager* sourcesManager)
	{
		storeSourceManagerAtSlot(sourcesManager, m_last_slot_stored);
	}
	
	void SourcesPreset::storeSourceManagerAtNextSlot(SourcesManager* sourcesManager)
	{
		storeSourceManagerAtSlot(sourcesManager, m_last_slot_stored+1);
	}
	
	void SourcesPreset::storeSourceManagerAtNewEndSlot(SourcesManager* sourcesManager)
	{
		storeSourceManagerAtSlot(sourcesManager, m_source_managers.size());
	}
	
	void SourcesPreset::storeSourceAtSlot(SourcesManager* sourcesManager, long slotIndex, long sourceIndex)
	{
		if(slotIndex >= 0 && sourcesManager->sourceGetExistence(sourceIndex))
		{
			if(slotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= slotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySource(sourcesManager, m_source_managers[slotIndex], sourceIndex);
			m_last_slot_stored = slotIndex;
		}
	}
	
	void SourcesPreset::storeSourceAtNextSlot(SourcesManager* sourcesManager, long sourceIndex)
	{
		storeSourceAtSlot(sourcesManager, m_last_slot_stored+1, sourceIndex);
	}
	
	void SourcesPreset::storeGroupAtSlot(SourcesManager* sourcesManager, long slotIndex, long groupIndex)
	{
		if(groupIndex >= 0 && sourcesManager->groupGetExistence(groupIndex))
		{
			if(slotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= slotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copyGroup(sourcesManager, m_source_managers[slotIndex], groupIndex);
			m_last_slot_stored = slotIndex;
		}
	}
	
	void SourcesPreset::storeGroupAtNextSlot(SourcesManager* sourcesManager, long groupIndex)
	{
		storeGroupAtSlot(sourcesManager, m_last_slot_stored+1, groupIndex);
	}
	
	
	void SourcesPreset::insertSlot(SourcesManager* sourcesManager, long index)
	{
		if(index >= 0)
		{
			if(index >= m_source_managers.size())
			{
				storeSourceManagerAtSlot(sourcesManager, index);
			}
			else
			{
				m_source_managers.push_back(new SourcesManager());
				for(long i = m_source_managers.size() - 1; i > index; i--)
				{
					copySourceManager(m_source_managers[i-1], m_source_managers[i]);
				}
				copySourceManager(sourcesManager, m_source_managers[index]);
				m_last_slot_stored = index;
			}
		}
	}
	
	void SourcesPreset::removeSlot(long index)
	{
		if(index >= 0 && index < m_source_managers.size())
		{
			m_source_managers[index]->setExistence(0);
		}
	}
	
	void SourcesPreset::deleteSlot(long index)
	{
		if(index >= 0 && index < m_source_managers.size())
		{
			if(m_source_managers[index]->getExistence())
			{
				for(long i = index; i < m_source_managers.size() - 1; i++)
				{
					copySourceManager(m_source_managers[index+1], m_source_managers[index]);
				}
				m_source_managers.pop_back();
			}
		}
	}
	
	void SourcesPreset::copySlot(long sourceIndex, long destinationIndex)
	{
		if(sourceIndex >= 0 && sourceIndex < m_source_managers.size())
		{
			if(destinationIndex >= 0 && destinationIndex < m_source_managers.size())
				copySourceManager(m_source_managers[sourceIndex], m_source_managers[destinationIndex]);
			else
				storeSourceManagerAtSlot(m_source_managers[sourceIndex], destinationIndex);
		}
	}
	
	void SourcesPreset::renumber()
	{
		for(long i = 0; i < m_source_managers.size(); i++)
		{
			if(!m_source_managers[i]->getExistence())
			{
				for(long j = i; j < m_source_managers.size() - 1; j++)
				{
					copySourceManager(m_source_managers[j+1], m_source_managers[j]);
				}
				m_source_managers.pop_back();
				i--;
			}
		}
	}
	
	void SourcesPreset::clear()
	{
		m_source_managers.clear();
	}
	
	/*************************************************************************************/
	/*************************************************************************************/
	/*************************************************************************************/
	
	void SourcesPreset::recallSlot(SourcesManager* sourcesManager, long index)
	{
		if(index >= 0 && index < m_source_managers.size())
		{
			if(m_source_managers[index]->getExistence())
				copySourceManager(m_source_managers[index], sourcesManager);
		}
	}
	
	void SourcesPreset::recallFractionalSlot(SourcesManager* sourcesManager, long sourceIndex, long destinationIndex, double fractionnalIndex)
	{
		if(sourceIndex >= 0 && sourceIndex < m_source_managers.size() && destinationIndex >= 0 && destinationIndex < m_source_managers.size())
		{
			if(m_source_managers[sourceIndex]->getExistence() && m_source_managers[destinationIndex]->getExistence())
			{
				fractionnalIndex = clip_minmax(fractionnalIndex, 0., 1.);
				interpolationSourceManager(m_source_managers[sourceIndex], m_source_managers[destinationIndex], sourcesManager, fractionnalIndex);
			}
		}
	}
	
	long SourcesPreset::recallFractionalSlot(SourcesManager* sourcesManager, double fractionnalIndex)
	{
		if(m_source_managers.size() == 0)
			return 0;
		else if(m_source_managers.size() == 1)
		{
			for(long i = 0; i < m_source_managers.size(); i++)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourcesManager);
					return 1;
				}
			}
		}
		else if(fractionnalIndex < 0.)
		{
			for(long i = 0; i < m_source_managers.size(); i++)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourcesManager);
					return 1;
				}
			}
		}
		else if(fractionnalIndex > m_source_managers.size() - 1)
		{
			for(long i = m_source_managers.size() - 1; i >= 0; i--)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourcesManager);
					return 1;
				}
			}
		}
		else
		{
			long indexOne  = -1;
			long indexTwo  = -1;
			for(long i = floor(fractionnalIndex); i >= 0 && indexOne == -1; i--)
			{
				if(m_source_managers[i]->getExistence())
					indexOne  = i;
			}
			if(indexOne == -1)
			{
				for(long i = 0; i < m_source_managers.size() && indexOne == -1; i++)
				{
					if(m_source_managers[i]->getExistence())
						indexOne  = i;
				}
				if(indexOne != -1)
				{
					copySourceManager(m_source_managers[indexOne], sourcesManager);
				}
				return 1;
			}
			else
			{
				for(long i = indexOne+1; i < m_source_managers.size() && indexTwo == -1; i++)
				{
					if(m_source_managers[i]->getExistence())
						indexTwo  = i;
				}
				if(indexTwo == -1)
				{
					copySourceManager(m_source_managers[indexOne], sourcesManager);
					return 1;
				}
				else
				{
					double fracPart = clip_minmax((double)(fractionnalIndex - (long)indexOne) / (double)(indexTwo - indexOne), 0., 1.);
					return interpolationSourceManager(m_source_managers[indexOne], m_source_managers[indexTwo], sourcesManager, fracPart);
				}
			}
		}
		return 0;
	}
	
	long SourcesPreset::getMaximumIndexOfSlot()
	{
		return m_source_managers.size() - 1;
	}
	
	long SourcesPreset::getSlotExistence(long index)
	{
		if(index >= 0 && index < m_source_managers.size())
			return m_source_managers[index]->getExistence();
		else
			return 0;
	}
	
	SourcesPreset::~SourcesPreset()
	{
		clear();
	}
}