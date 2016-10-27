#include "OtherTestScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TestScene.h"
#include "StateManager.h"
#include "Input.h"

OtherTestScene::OtherTestScene()
{
}

void OtherTestScene::initialise(const GameInfo & _info)
{
	_info.m_stateManager->pushState(new TestScene);
}

void OtherTestScene::update(const GameInfo & _info)
{
	if (_info.m_input->getInputActivated("exit"))
	{
		_info.m_stateManager->popState();
	}
}

void OtherTestScene::draw(const RenderInfo & _info)
{
	sf::RectangleShape rect(sf::Vector2f(290, 290));
	rect.setFillColor(sf::Color(100, 0, 0));
	_info.m_target->draw(rect);
}

void OtherTestScene::cleanup(const GameInfo& _info)
{
}
