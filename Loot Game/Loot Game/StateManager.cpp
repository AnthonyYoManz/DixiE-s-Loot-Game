#include "StateManager.h"
#include "GameState.h"

void StateManager::cleanStates(const GameInfo& _info)
{
	for (auto& state : m_states)
	{
		state->cleanup(_info);
		delete state;
	}
	m_states.clear();
	for (auto& state : m_upcomingStates)
	{
		delete state;
	}
	m_upcomingStates.clear();
	_info.m_objectFactory->linkList(nullptr);
}

void StateManager::linkListToFactory(const GameInfo & _info)
{
	if (m_states.size() > 0)
	{
		_info.m_objectFactory->linkList(m_states.back()->getObjectList());
		_info.m_debug->print(m_states.back()->getName() + " object list linked\n");
	}
	else
	{
		_info.m_objectFactory->linkList(nullptr);
		_info.m_debug->print("Object list unlinked from factory\n");
	}
}

void StateManager::mergeStates(const GameInfo& _info)
{
	bool stateChange = false;
	if (m_popState)
	{
		m_states.back()->cleanup(_info);
		m_states.pop_back();
		linkListToFactory(_info);
		if (m_states.size() > 0)
		{
			m_states.back()->resume();
		}
		m_popState = false;
	}

	for (auto& state : m_upcomingStates)
	{
		m_states.push_back(state);
		linkListToFactory(_info);
		state->initialise(_info);
		if (m_states.size() > 0)
		{
			m_states.back()->resume();
		}
	}
	m_upcomingStates.clear();

	if (m_newState)
	{
		cleanStates(_info);
		m_states.push_back(m_newState);
		linkListToFactory(_info);
		m_newState->initialise(_info);
		m_newState = nullptr;
	}
}

StateManager::StateManager()
{
	m_newState = nullptr;
}

StateManager::~StateManager()
{
	if (m_newState)
	{
		delete m_newState;
	}
}

void StateManager::initialise(const GameInfo& _info, GameState* _initialState = nullptr)
{
	swapState(_initialState);
	mergeStates(_info);
}

void StateManager::update(const GameInfo& _info)
{
	mergeStates(_info);
	if (m_states.size() > 0)
	{
		m_states.back()->update(_info);
	}
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
		m_popState = true;
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