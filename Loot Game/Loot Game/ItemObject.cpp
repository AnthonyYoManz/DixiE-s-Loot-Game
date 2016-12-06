#include "ItemObject.h"
#include "CharacterObject.h"

void ItemObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	m_holder = nullptr;
	m_name = "ItemObject";
	m_type = ItemType::USABLE;
	m_rarity = 0;
}

void ItemObject::equip(CharacterObject* _character)
{
	m_holder = _character;
	m_velocity = { 0, 0 };
	m_controlledVelocity = { 0, 0 };
}

void ItemObject::unequip()
{
	m_holder = nullptr;
}

unsigned int ItemObject::getRarity()
{
	return m_rarity;
}
