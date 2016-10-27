#include "TestScene.h"
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "StateManager.h"

TestScene::TestScene()
{
	m_layered = true;
}

void TestScene::initialise(const GameInfo & _info)
{
	_info.m_input->registerInput("exit", sf::Event::Closed);
}

void TestScene::update(const GameInfo & _info)
{
	if (_info.m_input->getInputActivated("exit"))
	{
		_info.m_stateManager->popState();
	}
}

void TestScene::draw(const RenderInfo & _info)
{
	sf::RectangleShape rect(sf::Vector2f(250, 250));
	rect.setFillColor(sf::Color(100, 100, 100));
	_info.m_target->draw(rect);
}

void TestScene::cleanup()
{
}
