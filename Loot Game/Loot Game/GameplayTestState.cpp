#include "GameplayTestState.h"


GameplayTestState::GameplayTestState()
{
	m_name = "GameplayTestState";
}

void GameplayTestState::initialise(const GameInfo& _info)
{
	GameState::initialise(_info);
	PlayerObject* player1 = (PlayerObject*)(_info.m_objectFactory->createObject("player"));
	if (player1)
	{
		player1->initialise(_info, m_stateInfo, m_objects.size(), { 0, 0 });
		player1->setPlayerNumber(1);
	}
}

void GameplayTestState::update(const GameInfo& _info)
{
	if (_info.m_input->getInputActivated("exit"))
	{
		_info.m_stateManager->popState();
	}
	
	unsigned int objCount = m_objects.size();
	//range based loop suffers when the list changes size mid-loop
	for (unsigned int i=0; i<objCount;i++)
	{
		if (m_objects.at(i)->isActive())
		{
			m_objects.at(i)->update(_info, m_stateInfo);
		}
	}

	handleDestroyRequests(_info);
}

void GameplayTestState::draw(const RenderInfo& _info)
{
	for (auto* object : m_objects)
	{
		if (object->isActive())
		{
			object->draw(_info, m_stateInfo);
		}
	}
}

void GameplayTestState::cleanup(const GameInfo& _info)
{
	for (auto* object : m_objects)
	{
		if (object->isActive())
		{
			object->cleanup(_info, m_stateInfo);
		}
	}
}
