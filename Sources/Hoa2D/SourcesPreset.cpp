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
	
	void SourcesPreset::copySourceManager(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination)
	{
		double* color;
		aSouceManagerDestination->setExistence(0);
		if(aSouceManagerSource->getExistence() == 1)
		{
			aSouceManagerDestination->setExistence(1);
			aSouceManagerDestination->setMaximumRadius(aSouceManagerSource->getLimitMaximum());
			
			for(long i = 0; i <= aSouceManagerSource->getMaximumIndexOfSource(); i++)
			{
				if(aSouceManagerSource->sourceGetExistence(i) == 1)
				{
					color = aSouceManagerSource->sourceGetColor(i);
					aSouceManagerDestination->sourceSetRadius(i, aSouceManagerSource->sourceGetRadius(i));
					aSouceManagerDestination->sourceSetAngle(i, aSouceManagerSource->sourceGetAzimuth(i));
					aSouceManagerDestination->sourceSetColor(i, color[0], color[1], color[2], color[3]);
					aSouceManagerDestination->sourceSetDescription(i, aSouceManagerSource->sourceGetDescription(i));
					aSouceManagerDestination->sourceSetMute(i, aSouceManagerSource->sourceGetMute(i));
				}
			}
			for(long i = 0; i <= aSouceManagerSource->getMaximumIndexOfGroup(); i++)
			{
				if(aSouceManagerSource->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < aSouceManagerSource->groupGetNumberOfSources(i); j++)
					{
						aSouceManagerDestination->groupSetSource(i, aSouceManagerSource->groupGetSourceIndex(i, j));
					}
					color = aSouceManagerSource->groupGetColor(i);
					aSouceManagerDestination->groupSetColor(i, color[0], color[1], color[2], color[3]);
					aSouceManagerDestination->groupSetDescription(i, aSouceManagerSource->groupGetDescription(i));
				}
			}
		}
	}
	
	void SourcesPreset::copySource(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long sourceIndex)
	{
		double* color;
		if(aSouceManagerSource->getExistence() == 1)
		{
			if(aSouceManagerDestination->getExistence() == 0)
				aSouceManagerDestination->setExistence(1);
			
			if(aSouceManagerSource->getMaximumIndexOfSource() >= sourceIndex && sourceIndex >= 0 && aSouceManagerSource->sourceGetExistence(sourceIndex) == 1)
			{
				color = aSouceManagerSource->sourceGetColor(sourceIndex);
				aSouceManagerDestination->sourceSetRadius(sourceIndex, aSouceManagerSource->sourceGetRadius(sourceIndex));
				aSouceManagerDestination->sourceSetAngle(sourceIndex, aSouceManagerSource->sourceGetAzimuth(sourceIndex));
				aSouceManagerDestination->sourceSetColor(sourceIndex, color[0], color[1], color[2], color[3]);
				aSouceManagerDestination->sourceSetDescription(sourceIndex, aSouceManagerSource->sourceGetDescription(sourceIndex));
				aSouceManagerDestination->sourceSetMute(sourceIndex, aSouceManagerSource->sourceGetMute(sourceIndex));
				for(int i = 0; i < aSouceManagerSource->sourceGetNumberOfGroups(sourceIndex); i++)
				{
					aSouceManagerDestination->groupSetSource(aSouceManagerSource->sourceGetGroupIndex(sourceIndex, i), sourceIndex);
				}
			}
		}
	}
	
	void SourcesPreset::copyGroup(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long groupeIndex)
	{
		double* color;
		if(aSouceManagerSource->getExistence() == 1)
		{
			if(aSouceManagerDestination->getExistence() == 0)
				aSouceManagerDestination->setExistence(1);
			if(aSouceManagerSource->getMaximumIndexOfGroup() >= groupeIndex && groupeIndex >= 0 && aSouceManagerSource->groupGetExistence(groupeIndex) == 1)
			{
				for(long j = 0; j < aSouceManagerSource->groupGetNumberOfSources(groupeIndex); j++)
				{
					copySource(aSouceManagerSource, aSouceManagerDestination, aSouceManagerSource->groupGetSourceIndex(groupeIndex, j));
					aSouceManagerDestination->groupSetSource(groupeIndex, aSouceManagerSource->groupGetSourceIndex(groupeIndex, j));
				}
				color = aSouceManagerSource->groupGetColor(groupeIndex);
				aSouceManagerDestination->groupSetColor(groupeIndex, color[0], color[1], color[2], color[3]);
				aSouceManagerDestination->groupSetDescription(groupeIndex, aSouceManagerSource->groupGetDescription(groupeIndex));
			}
		}
	}
	
	long SourcesPreset::interpolationSourceManager(SourcesManager* aSouceManagerSourceOne, SourcesManager* aSouceManagerSourceTwo, SourcesManager* aSouceManagerDestination, double aFrac)
	{
		double *color1, *color2;
		aSouceManagerDestination->setExistence(0);
		if(aSouceManagerSourceOne->getExistence() == 1 && aSouceManagerSourceTwo->getExistence() == 1)
		{
			aSouceManagerDestination->setExistence(1);
			aSouceManagerDestination->setMaximumRadius(aSouceManagerSourceOne->getLimitMaximum());
			
			for(long i = 0; i <= aSouceManagerSourceOne->getMaximumIndexOfSource(); i++)
			{
				if(aSouceManagerSourceOne->sourceGetExistence(i) == 1 && aSouceManagerSourceTwo->sourceGetExistence(i) == 1)
				{
					color1 = aSouceManagerSourceOne->sourceGetColor(i);
					color2 = aSouceManagerSourceTwo->sourceGetColor(i);
					aSouceManagerDestination->sourceSetAbscissa(i, aSouceManagerSourceOne->sourceGetAbscissa(i) * (1 - aFrac)
																+ aSouceManagerSourceTwo->sourceGetAbscissa(i) * aFrac);
					aSouceManagerDestination->sourceSetOrdinate(i,  aSouceManagerSourceOne->sourceGetOrdinate(i) * (1 - aFrac)
																+ aSouceManagerSourceTwo->sourceGetOrdinate(i) * aFrac);
					aSouceManagerDestination->sourceSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
																color1[1] * (1. - aFrac) + color2[1] * aFrac,
																color1[2] * (1. - aFrac) + color2[2] * aFrac,
																color1[3] * (1. - aFrac) + color2[3] * aFrac);
					
				}
				else if(aSouceManagerSourceOne->sourceGetExistence(i) == 1 && aSouceManagerSourceTwo->sourceGetExistence(i) == 0)
				{
					color1 = aSouceManagerSourceOne->sourceGetColor(i);
					
					aSouceManagerDestination->sourceSetRadius(i, aSouceManagerSourceOne->sourceGetRadius(i));
					aSouceManagerDestination->sourceSetAngle(i, aSouceManagerSourceOne->sourceGetAzimuth(i));
					aSouceManagerDestination->sourceSetColor(i, color1[0], color1[1], color1[2], color1[3]);
				}
				aSouceManagerDestination->sourceSetDescription(i, aSouceManagerSourceOne->sourceGetDescription(i));
				aSouceManagerDestination->sourceSetMute(i, aSouceManagerSourceOne->sourceGetMute(i));
			}
			for(long i = 0; i <= aSouceManagerSourceOne->getMaximumIndexOfGroup(); i++)
			{
				if(aSouceManagerSourceOne->groupGetExistence(i) == 1)
				{
					for(long j = 0; j < aSouceManagerSourceOne->groupGetNumberOfSources(i); j++)
					{
						aSouceManagerDestination->groupSetSource(i, aSouceManagerSourceOne->groupGetSourceIndex(i, j));
					}
					color1 = aSouceManagerSourceOne->groupGetColor(i);
					aSouceManagerDestination->groupSetColor(i, color1[0], color1[1], color1[2], color1[3]);
					aSouceManagerDestination->groupSetDescription(i, aSouceManagerSourceOne->groupGetDescription(i));
				}
				if(aSouceManagerSourceOne->groupGetExistence(i) == 1 && aSouceManagerSourceTwo->groupGetExistence(i) == 1 )
				{
					color1 = aSouceManagerSourceOne->groupGetColor(i);
					color2 = aSouceManagerSourceTwo->groupGetColor(i);
					aSouceManagerDestination->groupSetColor(i, color1[0] * (1. - aFrac) + color2[0] * aFrac,
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
	
	void SourcesPreset::storeSouceManagerAtSlot(SourcesManager* aSouceManager, long index)
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
			copySourceManager(aSouceManager, m_source_managers[index]);
			m_last_slot_stored = index;
		}
	}
	
	void SourcesPreset::storeSouceManagerAtFirstEmptySlot(SourcesManager* aSouceManager)
	{
		for(long i = 0; i < m_source_managers.size(); i++)
		{
			if(!m_source_managers[i]->getExistence())
			{
				storeSouceManagerAtSlot(aSouceManager, i);
				return;
			}
		}
		storeSouceManagerAtSlot(aSouceManager, m_source_managers.size());
	}
	
	
	void SourcesPreset::storeSouceManagerAtLastUsedSlot(SourcesManager* aSouceManager)
	{
		storeSouceManagerAtSlot(aSouceManager, m_last_slot_stored);
	}
	
	void SourcesPreset::storeSouceManagerAtNextSlot(SourcesManager* aSouceManager)
	{
		storeSouceManagerAtSlot(aSouceManager, m_last_slot_stored+1);
	}
	
	void SourcesPreset::storeSouceManagerAtNewEndSlot(SourcesManager* aSouceManager)
	{
		storeSouceManagerAtSlot(aSouceManager, m_source_managers.size());
	}
	
	void SourcesPreset::storeSourceAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long sourceIndex)
	{
		if(aSlotIndex >= 0 && aSouceManager->sourceGetExistence(sourceIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySource(aSouceManager, m_source_managers[aSlotIndex], sourceIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeSourceAtNextSlot(SourcesManager* aSouceManager, long sourceIndex)
	{
		storeSourceAtSlot(aSouceManager, m_last_slot_stored+1, sourceIndex);
	}
	
	void SourcesPreset::storeGroupAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long groupeIndex)
	{
		if(groupeIndex >= 0 && aSouceManager->groupGetExistence(groupeIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copyGroup(aSouceManager, m_source_managers[aSlotIndex], groupeIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeGroupAtNextSlot(SourcesManager* aSouceManager, long groupeIndex)
	{
		storeGroupAtSlot(aSouceManager, m_last_slot_stored+1, groupeIndex);
	}
	
	
	void SourcesPreset::insertSlot(SourcesManager* aSouceManager, long index)
	{
		if(index >= 0)
		{
			if(index >= m_source_managers.size())
			{
				storeSouceManagerAtSlot(aSouceManager, index);
			}
			else
			{
				m_source_managers.push_back(new SourcesManager());
				for(long i = m_source_managers.size() - 1; i > index; i--)
				{
					copySourceManager(m_source_managers[i-1], m_source_managers[i]);
				}
				copySourceManager(aSouceManager, m_source_managers[index]);
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
				storeSouceManagerAtSlot(m_source_managers[anIndexSouce], anIndexDestination);
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
	
	void SourcesPreset::recallSlot(SourcesManager* aSouceManager, long index)
	{
		if(index >= 0 && index < m_source_managers.size())
		{
			if(m_source_managers[index]->getExistence())
				copySourceManager(m_source_managers[index], aSouceManager);
		}
	}
	
	void SourcesPreset::recallFractionalSlot(SourcesManager* aSouceManager, long anIndexSource, long anIndexDestination, double aFractionnalIndex)
	{
		if(anIndexSource >= 0 && anIndexSource < m_source_managers.size() && anIndexDestination >= 0 && anIndexDestination < m_source_managers.size())
		{
			if(m_source_managers[anIndexSource]->getExistence() && m_source_managers[anIndexDestination]->getExistence())
			{
				aFractionnalIndex = clip_minmax(aFractionnalIndex, 0., 1.);
				interpolationSourceManager(m_source_managers[anIndexSource], m_source_managers[anIndexDestination], aSouceManager, aFractionnalIndex);
			}
		}
	}
	
	long SourcesPreset::recallFractionalSlot(SourcesManager* aSouceManager, double aFractionnalIndex)
	{
		if(m_source_managers.size() == 0)
			return 0;
		else if(m_source_managers.size() == 1)
		{
			for(long i = 0; i < m_source_managers.size(); i++)
			{
				if(m_source_managers[i]->getExistence())
				{
					copySourceManager(m_source_managers[i], aSouceManager);
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
					copySourceManager(m_source_managers[i], aSouceManager);
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
					copySourceManager(m_source_managers[i], aSouceManager);
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
					copySourceManager(m_source_managers[indexOne], aSouceManager);
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
					copySourceManager(m_source_managers[indexOne], aSouceManager);
					return 1;
				}
				else
				{
					double fracPart = clip_minmax((double)(aFractionnalIndex - (long)indexOne) / (double)(indexTwo - indexOne), 0., 1.);
					return interpolationSourceManager(m_source_managers[indexOne], m_source_managers[indexTwo], aSouceManager, fracPart);
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