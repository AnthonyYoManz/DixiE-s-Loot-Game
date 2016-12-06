#include "CharacterObject.h"
#include "StateInfo.h"

void CharacterObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	m_name = "CharacterObject";
	m_health = 100.f;
}

void CharacterObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	if (m_health <= 0)
	{
		m_health = 0;
		die(_gameInfo, _stateInfo);
		_gameInfo.m_debug->print(m_name + " is ded\n");
	}
}

void CharacterObject::die(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	_stateInfo.m_destroyRequests->push_back(this);
	int ejectPow = 20;
	WeaponObject* leftHand = m_equipment.unequip(EquipSlot::LEFT_HAND);
	WeaponObject* rightHand = m_equipment.unequip(EquipSlot::RIGHT_HAND);
	if (leftHand)
	{
		leftHand->setVelocity({ (float)(rand() % ejectPow) - ejectPow/2.f, (float)(rand() % ejectPow) - ejectPow/2.f });
	}
	if (rightHand)
	{
		rightHand->setVelocity({ (float)(rand() % ejectPow) - ejectPow / 2.f, (float)(rand() % ejectPow) - ejectPow / 2.f });
	}
}
