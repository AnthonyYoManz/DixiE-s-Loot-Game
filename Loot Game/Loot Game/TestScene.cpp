#include "TestState.h"
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "StateManager.h"

TestState::TestState()
{
	m_layered = true;
}

void TestState::initialise(const GameInfo & _info)
{
	_info.m_input->registerInput("exit", sf::Event::Closed);
}

void TestState::update(const GameInfo & _info)
{
	if (_info.m_input->getInputActivated("exit"))
	{
		_info.m_stateManager->popState();
	}
}

void TestState::draw(const RenderInfo & _info)
{
	sf::RectangleShape rect(sf::Vector2f(250, 250));
	rect.setFillColor(sf::Color(100, 100, 100));
	_info.m_target->draw(rect);
}

void TestState::cleanup(const GameInfo& _info)
{
}
