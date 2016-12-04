#include "gameState.h"

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
