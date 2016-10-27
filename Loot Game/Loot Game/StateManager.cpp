#include "StateManager.h"
#include "GameState.h"

void StateManager::cleanStates()
{
	for (auto& state : m_states)
	{
		state->cleanup();
		delete state;
	}
	m_states.clear();
	for (auto& state : m_upcomingStates)
	{
		delete state;
	}
	m_upcomingStates.clear();
}

void StateManager::mergeStates(const GameInfo& _info)
{
	for (auto& state : m_upcomingStates)
	{
		state->initialise(_info);
		if (m_states.size() > 0)
		{
			m_states.back()->resume();
		}
		m_states.push_back(state);
	}
	m_upcomingStates.clear();

	if (m_newState)
	{
		cleanStates();
		m_states.push_back(m_newState);
		m_newState->initialise(_info);
		m_newState = nullptr;
	}
}

StateManager::StateManager(GameState* _initialState = nullptr)
{
	swapState(_initialState);
}

StateManager::~StateManager()
{
	cleanStates();
	if (m_newState)
	{
		delete m_newState;
	}
}

void StateManager::update(const GameInfo& _info)
{
	mergeStates(_info);
	m_states.back()->update(_info);
}

void StateManager::draw(const RenderInfo& _info)
{
	int deepestLayer = m_states.size() - 1;
	for (int i = deepestLayer; i >= 0; i--)
	{
		deepestLayer = i;
		if (!m_states.at(i)->getLayered())
		{
			break;
		}
	}
	for (unsigned int i = deepestLayer; i < m_states.size(); i++)
	{
		m_states.at(i)->draw(_info);
	}
}

void StateManager::pushState(GameState* _newState)
{
	m_upcomingStates.push_back(_newState);
}

void StateManager::popState()
{
	if (m_states.size() > 0)
	{
		m_states.back()->cleanup();
		m_states.pop_back();
		if (m_states.size() > 0)
		{
			m_states.back()->resume();
		}
	}
}

void StateManager::swapState(GameState* _newState)
{
	m_newState = _newState;
}

bool StateManager::isEmpty()
{
	return !(m_states.size() > 0 || m_newState || m_upcomingStates.size() > 0);
}