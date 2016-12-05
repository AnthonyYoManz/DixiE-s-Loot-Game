#include "InitState.h"
#include "PlayerObject.h"
#include "TestGunObject.h"

InitState::InitState(GameState * _nextState)
{
	m_name = "Init State";
	m_nextState = _nextState;
}

void InitState::initialise(const GameInfo & _info)
{
	_info.m_input->registerInput("exit", sf::Event::Closed);
	_info.m_input->registerInput("exit", sf::Keyboard::Escape);

	_info.m_input->registerInput("p1right", sf::Keyboard::D);
	_info.m_input->registerInput("p1left", sf::Keyboard::A);
	_info.m_input->registerInput("p1up", sf::Keyboard::W);
	_info.m_input->registerInput("p1down", sf::Keyboard::S);
	_info.m_input->registerInput("p1l1", sf::Mouse::Left);
	_info.m_input->registerInput("p1l2", sf::Keyboard::Q);
	_info.m_input->registerInput("p1r1", sf::Mouse::Right);
	_info.m_input->registerInput("p1r2", sf::Keyboard::E);

	_info.m_objectFactory->addCreator("player", 
		[]()
		{
			return (GameObject*)(new PlayerObject);
		}
	);
	_info.m_objectFactory->addCreator("TestGunObject",
		[]()
		{
			return (GameObject*)(new TestGunObject);
		}
	);
}
