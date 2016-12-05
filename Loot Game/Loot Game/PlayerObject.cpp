#include "PlayerObject.h"
#include "GameInfo.h"
#include "WeaponObject.h"
#include "TestGunObject.h"
#include <iostream>

void PlayerObject::initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	m_leftTriggerDown = false;
	m_health = 100;
	m_radius = 15;
	m_playerNumber = 1;
	m_moveSpeed = 4.f;
	m_gun = (TestGunObject*)_gameInfo.m_objectFactory->createObject("TestGunObject");
	m_gun->initialise(_gameInfo, _stateInfo, _handle, _position);
}

void PlayerObject::update(const GameInfo& _gameInfo, const StateInfo& _stateInfo)
{
	handleInputs(_gameInfo, _stateInfo);
	m_position += getControlledDirection()*m_moveSpeed;
	lookAt(_gameInfo.m_input->getMousePosition());
	if (m_gun)
	{
		m_gun->setPosition(m_position);
		m_gun->setRotation(m_rotation);
		m_gun->setTriggerDown(m_leftTriggerDown);
	}
}

void PlayerObject::draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo)
{
	sf::CircleShape circ(m_radius);
	circ.setFillColor(sf::Color(255, 255, 255));
	circ.setPosition(m_position);
	circ.setOrigin({ m_radius, m_radius });
	_renderInfo.m_target->draw(circ);
}

void PlayerObject::cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo)
{
}

void PlayerObject::setPlayerNumber(int _playerNumber)
{
	if (_playerNumber > 0)
	{
		m_playerNumber = _playerNumber;
	}
}

void PlayerObject::handleInputs(const GameInfo& _gameInfo, const StateInfo& _stateInfo)
{
	if (_gameInfo.m_input->getInputActive("p" + std::to_string(m_playerNumber) + "right"))
	{
		m_controlledVelocity.x = 1;
	}
	else if (_gameInfo.m_input->getInputActive("p" + std::to_string(m_playerNumber) + "left"))
	{
		m_controlledVelocity.x = -1;
	}
	else
	{
		m_controlledVelocity.x = 0;
	}
	if (_gameInfo.m_input->getInputActive("p" + std::to_string(m_playerNumber) + "down"))
	{
		m_controlledVelocity.y = 1;
	}
	else if (_gameInfo.m_input->getInputActive("p" + std::to_string(m_playerNumber) + "up"))
	{
		m_controlledVelocity.y = -1;
	}
	else
	{
		m_controlledVelocity.y = 0;
	}
	if (_gameInfo.m_input->getInputActive("p1l1"))
	{
		m_leftTriggerDown = true;
	}
	else
	{
		m_leftTriggerDown = false;
	}
}
