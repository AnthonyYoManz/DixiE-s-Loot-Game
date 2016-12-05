#include "GameState.h"

void GameState::initialise(const GameInfo & _info)
{
	m_stateInfo.m_destroyRequests = &m_destroyRequests;
	m_layered = false;
}

void GameState::pause()
{
}

void GameState::resume()
{
}

void GameState::setLayered(bool _layered)
{
	m_layered = _layered;
}

bool GameState::getLayered()
{
	return m_layered;
}

std::string GameState::getName()
{
	return m_name;
}

std::vector<GameObject*>* GameState::getObjectList()
{
	return &m_objects;
}

void GameState::handleDestroyRequests(const GameInfo& _info)
{
	for (auto* reqObject : m_destroyRequests)
	{
		for (int i = 0; i<m_objects.size(); i++)
		{
			if (m_objects.at(i) == reqObject)
			{
				m_objects.at(i)->cleanup(_info, m_stateInfo);
				delete m_objects.at(i);
				m_objects.erase(m_objects.begin() + i);
				break;
			}
		}
	}
	m_destroyRequests.clear();
}
