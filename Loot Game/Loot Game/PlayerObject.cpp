#include "PlayerObject.h"
#include "GameInfo.h"
#include "WeaponObject.h"
#include "TestGunObject.h"

void PlayerObject::initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	CharacterObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	m_name = "PlayerObject";
	m_leftTriggerDown = false;
	m_radius = 15;
	m_playerNumber = 1;
	m_moveSpeed = 4.f;
	WeaponObject* gun = (WeaponObject*)_gameInfo.m_objectFactory->createObject("TestGunObject");
	gun->initialise(_gameInfo, _stateInfo, _handle, _position);
	gun->equip(this);
	m_equipment.equip(gun, EquipSlot::LEFT_HAND);
}

void PlayerObject::update(const GameInfo& _gameInfo, const StateInfo& _stateInfo)
{
	handleInputs(_gameInfo, _stateInfo);
	decelerate();
	m_position += getControlledDirection()*m_moveSpeed + m_velocity;
	lookAt(_gameInfo.m_input->getMousePosition());
	WeaponObject* leftHand = m_equipment.getLeftHand();
	WeaponObject* rightHand = m_equipment.getRightHand();
	if (leftHand)
	{
		leftHand->setPosition(m_position);
		leftHand->setRotation(m_rotation);
		leftHand->setTriggerDown(m_leftTriggerDown);
	}
	CharacterObject::update(_gameInfo, _stateInfo);
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
