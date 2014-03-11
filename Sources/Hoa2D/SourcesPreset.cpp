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
	
	void SourcesPreset::copySourceManager(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination)
	{
		double* color;
		sourceManagerDestination->setExistence(0);
		if(sourceManagerSource->getExistence() == 1)
		{
			sourceManagerDestination->setExistence(1);
			sourceManagerDestination->setMaximumRadius(sourceManagerSource->getLimitMaximum());
			
			for(long i = 0; i <= sourceManagerSource->getMaximumIndexOfSource(); i++)
			{
				if(sourceManagerSource->sourceGetExistence(i) == 1)
				{
					color = sourceManagerSource->sourceGetColor(i);
					sourceManagerDestination->sourceSetRadius(i, sourceManagerSource->sourceGetRadius(i));
					sourceManagerDestination->sourceSetAzimuth(i, sourceManagerSource->sourceGetAzimuth(i));
					sourceManagerDestination->sourceSetColor(i, color[0], color[1], color[2], color[3]);
					sourceManagerDestination->sourceSetDescription(i, sourceManagerSource->sourceGetDescription(i));
					sourceManagerDestination->sourceSetMute(i, sourceManagerSource->sourceGetMute(i));
				}
			}
			for(long i = 0; i <= sourceManagerSource->getMaximumIndexOfGroup(); i++)
			{
				if(sourceManagerSource->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < sourceManagerSource->groupGetNumberOfSources(i); j++)
					{
						sourceManagerDestination->groupSetSource(i, sourceManagerSource->groupGetSourceIndex(i, j));
					}
					color = sourceManagerSource->groupGetColor(i);
					sourceManagerDestination->groupSetColor(i, color[0], color[1], color[2], color[3]);
					sourceManagerDestination->groupSetDescription(i, sourceManagerSource->groupGetDescription(i));
				}
			}
		}
	}
	
	void SourcesPreset::copySource(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination, long sourceIndex)
	{
		double* color;
		if(sourceManagerSource->getExistence() == 1)
		{
			if(sourceManagerDestination->getExistence() == 0)
				sourceManagerDestination->setExistence(1);
			
			if(sourceManagerSource->getMaximumIndexOfSource() >= sourceIndex && sourceIndex >= 0 && sourceManagerSource->sourceGetExistence(sourceIndex) == 1)
			{
				color = sourceManagerSource->sourceGetColor(sourceIndex);
				sourceManagerDestination->sourceSetRadius(sourceIndex, sourceManagerSource->sourceGetRadius(sourceIndex));
				sourceManagerDestination->sourceSetAzimuth(sourceIndex, sourceManagerSource->sourceGetAzimuth(sourceIndex));
				sourceManagerDestination->sourceSetColor(sourceIndex, color[0], color[1], color[2], color[3]);
				sourceManagerDestination->sourceSetDescription(sourceIndex, sourceManagerSource->sourceGetDescription(sourceIndex));
				sourceManagerDestination->sourceSetMute(sourceIndex, sourceManagerSource->sourceGetMute(sourceIndex));
				for(int i = 0; i < sourceManagerSource->sourceGetNumberOfGroups(sourceIndex); i++)
				{
					sourceManagerDestination->groupSetSource(sourceManagerSource->sourceGetGroupIndex(sourceIndex, i), sourceIndex);
				}
			}
		}
	}
	
	void SourcesPreset::copyGroup(SourcesManager* sourceManagerSource, SourcesManager* sourceManagerDestination, long groupIndex)
	{
		double* color;
		if(sourceManagerSource->getExistence() == 1)
		{
			if(sourceManagerDestination->getExistence() == 0)
				sourceManagerDestination->setExistence(1);
			if(sourceManagerSource->getMaximumIndexOfGroup() >= groupIndex && groupIndex >= 0 && sourceManagerSource->groupGetExistence(groupIndex) == 1)
			{
				for(long j = 0; j < sourceManagerSource->groupGetNumberOfSources(groupIndex); j++)
				{
					copySource(sourceManagerSource, sourceManagerDestination, sourceManagerSource->groupGetSourceIndex(groupIndex, j));
					sourceManagerDestination->groupSetSource(groupIndex, sourceManagerSource->groupGetSourceIndex(groupIndex, j));
				}
				color = sourceManagerSource->groupGetColor(groupIndex);
				sourceManagerDestination->groupSetColor(groupIndex, color[0], color[1], color[2], color[3]);
				sourceManagerDestination->groupSetDescription(groupIndex, sourceManagerSource->groupGetDescription(groupIndex));
			}
		}
	}
	
	long SourcesPreset::interpolationSourceManager(SourcesManager* sourceManagerSourceOne, SourcesManager* sourceManagerSourceTwo, SourcesManager* sourceManagerDestination, double aFrac)
	{
		double *color1, *color2;
		sourceManagerDestination->setExistence(0);
		if(sourceManagerSourceOne->getExistence() == 1 && sourceManagerSourceTwo->getExistence() == 1)
		{
			sourceManagerDestination->setExistence(1);
			sourceManagerDestination->setMaximumRadius(sourceManagerSourceOne->getLimitMaximum());
			
			for(long i = 0; i <= sourceManagerSourceOne->getMaximumIndexOfSource(); i++)
			{
				if(sourceManagerSourceOne->sourceGetExistence(i) == 1 && sourceManagerSourceTwo->sourceGetExistence(i) == 1)
				{
					color1 = sourceManagerSourceOne->sourceGetColor(i);
					color2 = sourceManagerSourceTwo->sourceGetColor(i);
					sourceManagerDestination->sourceSetAbscissa(i, sourceManagerSourceOne->sourceGetAbscissa(i) * (1 - aFrac)
																+ sourceManagerSourceTwo->sourceGetAbscissa(i) * aFrac);
					sourceManagerDestination->sourceSetOrdinate(i,  sourceManagerSourceOne->sourceGetOrdinate(i) * (1 - aFrac)
																+ sourceManagerSourceTwo->sourceGetOrdinate(i) * aFrac);
					sourceManagerDestination->sourceSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
																color1[1] * (1. - aFrac) + color2[1] * aFrac,
																color1[2] * (1. - aFrac) + color2[2] * aFrac,
																color1[3] * (1. - aFrac) + color2[3] * aFrac);
					
				}
				else if(sourceManagerSourceOne->sourceGetExistence(i) == 1 && sourceManagerSourceTwo->sourceGetExistence(i) == 0)
				{
					color1 = sourceManagerSourceOne->sourceGetColor(i);
					
					sourceManagerDestination->sourceSetRadius(i, sourceManagerSourceOne->sourceGetRadius(i));
					sourceManagerDestination->sourceSetAzimuth(i, sourceManagerSourceOne->sourceGetAzimuth(i));
					sourceManagerDestination->sourceSetColor(i, color1[0], color1[1], color1[2], color1[3]);
				}
				sourceManagerDestination->sourceSetDescription(i, sourceManagerSourceOne->sourceGetDescription(i));
				sourceManagerDestination->sourceSetMute(i, sourceManagerSourceOne->sourceGetMute(i));
			}
			for(long i = 0; i <= sourceManagerSourceOne->getMaximumIndexOfGroup(); i++)
			{
				if(sourceManagerSourceOne->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < sourceManagerSourceOne->groupGetNumberOfSources(i); j++)
					{
						sourceManagerDestination->groupSetSource(i, sourceManagerSourceOne->groupGetSourceIndex(i, j));
					}
					color1 = sourceManagerSourceOne->groupGetColor(i);
					sourceManagerDestination->groupSetColor(i, color1[0], color1[1], color1[2], color1[3]);
					sourceManagerDestination->groupSetDescription(i, sourceManagerSourceOne->groupGetDescription(i));
				}
				if(sourceManagerSourceOne->groupGetExistence(i) == 1 && sourceManagerSourceTwo->groupGetExistence(i) == 1 )
				{
					color1 = sourceManagerSourceOne->groupGetColor(i);
					color2 = sourceManagerSourceTwo->groupGetColor(i);
					sourceManagerDestination->groupSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
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
	
	void SourcesPreset::storeSourceManagerAtSlot(SourcesManager* sourceManager, long index)
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
			copySourceManager(sourceManager, m_source_managers[index]);
			m_last_slot_stored = index;
		}
	}
	
	void SourcesPreset::storeSourceManagerAtFirstEmptySlot(SourcesManager* sourceManager)
	{
		for(long i = 0; i < m_source_managers.size(); i++)
		{
			if(!m_source_managers[i]->getExistence())
			{
				storeSourceManagerAtSlot(sourceManager, i);
				return;
			}
		}
		storeSourceManagerAtSlot(sourceManager, m_source_managers.size());
	}
	
	
	void SourcesPreset::storeSourceManagerAtLastUsedSlot(SourcesManager* sourceManager)
	{
		storeSourceManagerAtSlot(sourceManager, m_last_slot_stored);
	}
	
	void SourcesPreset::storeSourceManagerAtNextSlot(SourcesManager* sourceManager)
	{
		storeSourceManagerAtSlot(sourceManager, m_last_slot_stored+1);
	}
	
	void SourcesPreset::storeSourceManagerAtNewEndSlot(SourcesManager* sourceManager)
	{
		storeSourceManagerAtSlot(sourceManager, m_source_managers.size());
	}
	
	void SourcesPreset::storeSourceAtSlot(SourcesManager* sourceManager, long aSlotIndex, long sourceIndex)
	{
		if(aSlotIndex >= 0 && sourceManager->sourceGetExistence(sourceIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySource(sourceManager, m_source_managers[aSlotIndex], sourceIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeSourceAtNextSlot(SourcesManager* sourceManager, long sourceIndex)
	{
		storeSourceAtSlot(sourceManager, m_last_slot_stored+1, sourceIndex);
	}
	
	void SourcesPreset::storeGroupAtSlot(SourcesManager* sourceManager, long aSlotIndex, long groupIndex)
	{
		if(groupIndex >= 0 && sourceManager->groupGetExistence(groupIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copyGroup(sourceManager, m_source_managers[aSlotIndex], groupIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeGroupAtNextSlot(SourcesManager* sourceManager, long groupIndex)
	{
		storeGroupAtSlot(sourceManager, m_last_slot_stored+1, groupIndex);
	}
	
	
	void SourcesPreset::insertSlot(SourcesManager* sourceManager, long index)
	{
		if(index >= 0)
		{
			if(index >= m_source_managers.size())
			{
				storeSourceManagerAtSlot(sourceManager, index);
			}
			else
			{
				m_source_managers.push_back(new SourcesManager());
				for(long i = m_source_managers.size() - 1; i > index; i--)
				{
					copySourceManager(m_source_managers[i-1], m_source_managers[i]);
				}
				copySourceManager(sourceManager, m_source_managers[index]);
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
	
	void SourcesPreset::copySlot(long anIndexSouce, long anIndexDestination)
	{
		if(anIndexSouce >= 0 && anIndexSouce < m_source_managers.size())
		{
			if(anIndexDestination >= 0 && anIndexDestination < m_source_managers.size())
				copySourceManager(m_source_managers[anIndexSouce], m_source_managers[anIndexDestination]);
			else
				storeSourceManagerAtSlot(m_source_managers[anIndexSouce], anIndexDestination);
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
	
	void SourcesPreset::recallSlot(SourcesManager* sourceManager, long index)
	{
		if(index >= 0 && index < m_source_managers.size())
		{
			if(m_source_managers[index]->getExistence())
				copySourceManager(m_source_managers[index], sourceManager);
		}
	}
	
	void SourcesPreset::recallFractionalSlot(SourcesManager* sourceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex)
	{
		if(anIndexSource >= 0 && anIndexSource < m_source_managers.size() && anIndexDestination >= 0 && anIndexDestination < m_source_managers.size())
		{
			if(m_source_managers[anIndexSource]->getExistence() && m_source_managers[anIndexDestination]->getExistence())
			{
				aFractionnalIndex = clip_minmax(aFractionnalIndex, 0., 1.);
				interpolationSourceManager(m_source_managers[anIndexSource], m_source_managers[anIndexDestination], sourceManager, aFractionnalIndex);
			}
		}
	}
	
	long SourcesPreset::recallFractionalSlot(SourcesManager* sourceManager, double aFractionnalIndex)
	{
		if(m_source_managers.size() == 0)
			return 0;
		else if(m_source_managers.size() == 1)
		{
			for(long i = 0; i < m_source_managers.size(); i++)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourceManager);
					return 1;
				}
			}
		}
		else if(aFractionnalIndex < 0.)
		{
			for(long i = 0; i < m_source_managers.size(); i++)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourceManager);
					return 1;
				}
			}
		}
		else if(aFractionnalIndex > m_source_managers.size() - 1)
		{
			for(long i = m_source_managers.size() - 1; i >= 0; i--)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], sourceManager);
					return 1;
				}
			}
		}
		else
		{
			long indexOne  = -1;
			long indexTwo  = -1;
			for(long i = floor(aFractionnalIndex); i >= 0 && indexOne == -1; i--)
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
					copySourceManager(m_source_managers[indexOne], sourceManager);
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
					copySourceManager(m_source_managers[indexOne], sourceManager);
					return 1;
				}
				else
				{
					double fracPart = clip_minmax((double)(aFractionnalIndex - (long)indexOne) / (double)(indexTwo - indexOne), 0., 1.);
					return interpolationSourceManager(m_source_managers[indexOne], m_source_managers[indexTwo], sourceManager, fracPart);
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