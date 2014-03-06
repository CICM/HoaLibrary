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
		aSouceManagerDestination->setExistence(0);
		if(aSouceManagerSource->getExistence() == 1)
		{
			aSouceManagerDestination->setExistence(1);
			aSouceManagerDestination->setMaximumRadius(aSouceManagerSource->getLimitMaximum());
			
			for(long i = 0; i <= aSouceManagerSource->getMaximumIndexOfSource(); i++)
			{
				if(aSouceManagerSource->sourceGetExistence(i) == 1)
				{
					aSouceManagerDestination->sourceSetRadius(i, aSouceManagerSource->sourceGetRadius(i));
					aSouceManagerDestination->sourceSetAngle(i, aSouceManagerSource->sourceGetAngle(i));
					aSouceManagerDestination->sourceSetColor(i, aSouceManagerSource->sourceGetColor(i).red, aSouceManagerSource->sourceGetColor(i).green, aSouceManagerSource->sourceGetColor(i).blue, aSouceManagerSource->sourceGetColor(i).alpha);
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
					aSouceManagerDestination->groupSetColor(i, aSouceManagerSource->groupGetColor(i).red, aSouceManagerSource->groupGetColor(i).green, aSouceManagerSource->groupGetColor(i).blue, aSouceManagerSource->groupGetColor(i).alpha);
					aSouceManagerDestination->groupSetDescription(i, aSouceManagerSource->groupGetDescription(i));
				}
			}
		}
	}
	
	void SourcesPreset::copySource(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aSourceIndex)
	{
		if(aSouceManagerSource->getExistence() == 1)
		{
			if(aSouceManagerDestination->getExistence() == 0)
				aSouceManagerDestination->setExistence(1);
			
			if(aSouceManagerSource->getMaximumIndexOfSource() >= aSourceIndex && aSourceIndex >= 0 && aSouceManagerSource->sourceGetExistence(aSourceIndex) == 1)
			{
				aSouceManagerDestination->sourceSetRadius(aSourceIndex, aSouceManagerSource->sourceGetRadius(aSourceIndex));
				aSouceManagerDestination->sourceSetAngle(aSourceIndex, aSouceManagerSource->sourceGetAngle(aSourceIndex));
				aSouceManagerDestination->sourceSetColor(aSourceIndex,
														 aSouceManagerSource->sourceGetColor(aSourceIndex).red,
														 aSouceManagerSource->sourceGetColor(aSourceIndex).green,
														 aSouceManagerSource->sourceGetColor(aSourceIndex).blue,
														 aSouceManagerSource->sourceGetColor(aSourceIndex).alpha);
				aSouceManagerDestination->sourceSetDescription(aSourceIndex, aSouceManagerSource->sourceGetDescription(aSourceIndex));
				aSouceManagerDestination->sourceSetMute(aSourceIndex, aSouceManagerSource->sourceGetMute(aSourceIndex));
				for(int i = 0; i < aSouceManagerSource->sourceGetNumberOfGroups(aSourceIndex); i++)
				{
					aSouceManagerDestination->groupSetSource(aSouceManagerSource->sourceGetGroupIndex(aSourceIndex, i), aSourceIndex);
				}
			}
		}
	}
	
	void SourcesPreset::copyGroup(SourcesManager* aSouceManagerSource, SourcesManager* aSouceManagerDestination, long aGroupIndex)
	{
		if(aSouceManagerSource->getExistence() == 1)
		{
			if(aSouceManagerDestination->getExistence() == 0)
				aSouceManagerDestination->setExistence(1);
			if(aSouceManagerSource->getMaximumIndexOfGroup() >= aGroupIndex && aGroupIndex >= 0 && aSouceManagerSource->groupGetExistence(aGroupIndex) == 1)
			{
				for(long j = 0; j < aSouceManagerSource->groupGetNumberOfSources(aGroupIndex); j++)
				{
					copySource(aSouceManagerSource, aSouceManagerDestination, aSouceManagerSource->groupGetSourceIndex(aGroupIndex, j));
					aSouceManagerDestination->groupSetSource(aGroupIndex, aSouceManagerSource->groupGetSourceIndex(aGroupIndex, j));
				}
				aSouceManagerDestination->groupSetColor(aGroupIndex,
														aSouceManagerSource->groupGetColor(aGroupIndex).red,
														aSouceManagerSource->groupGetColor(aGroupIndex).green,
														aSouceManagerSource->groupGetColor(aGroupIndex).blue,
														aSouceManagerSource->groupGetColor(aGroupIndex).alpha);
				aSouceManagerDestination->groupSetDescription(aGroupIndex, aSouceManagerSource->groupGetDescription(aGroupIndex));
			}
		}
	}
	
	long SourcesPreset::interpolationSourceManager(SourcesManager* aSouceManagerSourceOne, SourcesManager* aSouceManagerSourceTwo, SourcesManager* aSouceManagerDestination, double aFrac)
	{
		aSouceManagerDestination->setExistence(0);
		if(aSouceManagerSourceOne->getExistence() == 1 && aSouceManagerSourceTwo->getExistence() == 1)
		{
			aSouceManagerDestination->setExistence(1);
			aSouceManagerDestination->setMaximumRadius(aSouceManagerSourceOne->getLimitMaximum());
			
			for(long i = 0; i <= aSouceManagerSourceOne->getMaximumIndexOfSource(); i++)
			{
				if(aSouceManagerSourceOne->sourceGetExistence(i) == 1 && aSouceManagerSourceTwo->sourceGetExistence(i) == 1)
				{
					aSouceManagerDestination->sourceSetAbscissa(i, aSouceManagerSourceOne->sourceGetAbscissa(i) * (1 - aFrac)
																+ aSouceManagerSourceTwo->sourceGetAbscissa(i) * aFrac);
					aSouceManagerDestination->sourceSetOrdinate(i,  aSouceManagerSourceOne->sourceGetOrdinate(i) * (1 - aFrac)
																+ aSouceManagerSourceTwo->sourceGetOrdinate(i) * aFrac);
					aSouceManagerDestination->sourceSetColor(i,
															 aSouceManagerSourceOne->sourceGetColor(i).red * (1. - aFrac) + aSouceManagerSourceTwo->sourceGetColor(i).red * aFrac,
															 aSouceManagerSourceOne->sourceGetColor(i).green * (1. - aFrac) + aSouceManagerSourceTwo->sourceGetColor(i).green * aFrac,
															 aSouceManagerSourceOne->sourceGetColor(i).blue * (1. - aFrac) + aSouceManagerSourceTwo->sourceGetColor(i).blue * aFrac,
															 aSouceManagerSourceOne->sourceGetColor(i).alpha * (1. - aFrac) + aSouceManagerSourceTwo->sourceGetColor(i).alpha * aFrac);
					
				}
				else if(aSouceManagerSourceOne->sourceGetExistence(i) == 1 && aSouceManagerSourceTwo->sourceGetExistence(i) == 0)
				{
					aSouceManagerDestination->sourceSetRadius(i, aSouceManagerSourceOne->sourceGetRadius(i));
					aSouceManagerDestination->sourceSetAngle(i, aSouceManagerSourceOne->sourceGetAngle(i));
					aSouceManagerDestination->sourceSetColor(i, aSouceManagerSourceOne->sourceGetColor(i).red, aSouceManagerSourceOne->sourceGetColor(i).green, aSouceManagerSourceOne->sourceGetColor(i).blue, aSouceManagerSourceOne->sourceGetColor(i).alpha);
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
					aSouceManagerDestination->groupSetColor(i, aSouceManagerSourceOne->groupGetColor(i).red, aSouceManagerSourceOne->groupGetColor(i).green, aSouceManagerSourceOne->groupGetColor(i).blue, aSouceManagerSourceOne->groupGetColor(i).alpha);
					aSouceManagerDestination->groupSetDescription(i, aSouceManagerSourceOne->groupGetDescription(i));
				}
				if(aSouceManagerSourceOne->groupGetExistence(i) == 1 && aSouceManagerSourceTwo->groupGetExistence(i) == 1 )
				{
					aSouceManagerDestination->groupSetColor(i,
															aSouceManagerSourceOne->groupGetColor(i).red * (1. - aFrac) + aSouceManagerSourceTwo->groupGetColor(i).red * aFrac,
															aSouceManagerSourceOne->groupGetColor(i).green * (1. - aFrac) + aSouceManagerSourceTwo->groupGetColor(i).green * aFrac,
															aSouceManagerSourceOne->groupGetColor(i).blue * (1. - aFrac) + aSouceManagerSourceTwo->groupGetColor(i).blue * aFrac,
															aSouceManagerSourceOne->groupGetColor(i).alpha * (1. - aFrac) + aSouceManagerSourceTwo->groupGetColor(i).alpha * aFrac);
				}
			}
			return 1;
		}
		return 0;
	}
	
	/*************************************************************************************/
	/*************************************************************************************/
	/*************************************************************************************/
	
	void SourcesPreset::storeSouceManagerAtSlot(SourcesManager* aSouceManager, long anIndex)
	{
		if(anIndex >= 0)
		{
			if(anIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= anIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySourceManager(aSouceManager, m_source_managers[anIndex]);
			m_last_slot_stored = anIndex;
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
	
	void SourcesPreset::storeSourceAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long aSourceIndex)
	{
		if(aSlotIndex >= 0 && aSouceManager->sourceGetExistence(aSourceIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copySource(aSouceManager, m_source_managers[aSlotIndex], aSourceIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeSourceAtNextSlot(SourcesManager* aSouceManager, long aSourceIndex)
	{
		storeSourceAtSlot(aSouceManager, m_last_slot_stored+1, aSourceIndex);
	}
	
	void SourcesPreset::storeGroupAtSlot(SourcesManager* aSouceManager, long aSlotIndex, long aGroupIndex)
	{
		if(aGroupIndex >= 0 && aSouceManager->groupGetExistence(aGroupIndex))
		{
			if(aSlotIndex >= m_source_managers.size())
			{
				for(long i = m_source_managers.size(); i <= aSlotIndex; i++)
				{
					m_source_managers.push_back(new SourcesManager(-1, 0));
				}
			}
			copyGroup(aSouceManager, m_source_managers[aSlotIndex], aGroupIndex);
			m_last_slot_stored = aSlotIndex;
		}
	}
	
	void SourcesPreset::storeGroupAtNextSlot(SourcesManager* aSouceManager, long aGroupIndex)
	{
		storeGroupAtSlot(aSouceManager, m_last_slot_stored+1, aGroupIndex);
	}
	
	
	void SourcesPreset::insertSlot(SourcesManager* aSouceManager, long anIndex)
	{
		if(anIndex >= 0)
		{
			if(anIndex >= m_source_managers.size())
			{
				storeSouceManagerAtSlot(aSouceManager, anIndex);
			}
			else
			{
				m_source_managers.push_back(new SourcesManager());
				for(long i = m_source_managers.size() - 1; i > anIndex; i--)
				{
					copySourceManager(m_source_managers[i-1], m_source_managers[i]);
				}
				copySourceManager(aSouceManager, m_source_managers[anIndex]);
				m_last_slot_stored = anIndex;
			}
		}
	}
	
	void SourcesPreset::removeSlot(long anIndex)
	{
		if(anIndex >= 0 && anIndex < m_source_managers.size())
		{
			m_source_managers[anIndex]->setExistence(0);
		}
	}
	
	void SourcesPreset::deleteSlot(long anIndex)
	{
		if(anIndex >= 0 && anIndex < m_source_managers.size())
		{
			if(m_source_managers[anIndex]->getExistence())
			{
				for(long i = anIndex; i < m_source_managers.size() - 1; i++)
				{
					copySourceManager(m_source_managers[anIndex+1], m_source_managers[anIndex]);
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
	
	void SourcesPreset::recallSlot(SourcesManager* aSouceManager, long anIndex)
	{
		if(anIndex >= 0 && anIndex < m_source_managers.size())
		{
			if(m_source_managers[anIndex]->getExistence())
				copySourceManager(m_source_managers[anIndex], aSouceManager);
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
	
	long SourcesPreset::getSlotExistence(long anIndex)
	{
		if(anIndex >= 0 && anIndex < m_source_managers.size())
			return m_source_managers[anIndex]->getExistence();
		else
			return 0;
	}
	
	SourcesPreset::~SourcesPreset()
	{
		clear();
	}
}