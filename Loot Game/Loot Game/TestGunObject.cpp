#include "TestGunObject.h"

void TestGunObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
}

void TestGunObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}

void TestGunObject::draw(const RenderInfo & _renderInfo, const StateInfo & _stateInfo)
{
	sf::RectangleShape rect(sf::Vector2f(10, 4));
	rect.setPosition(m_position);
	rect.setOrigin(0, 2);
	rect.setFillColor({ 255, 0, 0 });
	rect.setRotation(m_rotation);
	_renderInfo.m_target->draw(rect);
}

void TestGunObject::cleanup(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}

void TestGunObject::attack(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}
