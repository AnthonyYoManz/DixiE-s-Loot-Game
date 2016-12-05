#include "OtherTestState.h"
#include <SFML/Graphics.hpp>
#include "TestState.h"
#include "StateManager.h"
#include "Input.h"

OtherTestState::OtherTestState()
{
}

void OtherTestState::initialise(const GameInfo & _info)
{
	_info.m_stateManager->pushState(new TestState);
}

void OtherTestState::update(const GameInfo & _info)
{
	if (_info.m_input->getInputActivated("exit"))
	{
		_info.m_stateManager->popState();
	}
}

void OtherTestState::draw(const RenderInfo & _info)
{
	sf::RectangleShape rect(sf::Vector2f(290, 290));
	rect.setFillColor(sf::Color(100, 0, 0));
	_info.m_target->draw(rect);
}

void OtherTestState::cleanup(const GameInfo& _info)
{
}
