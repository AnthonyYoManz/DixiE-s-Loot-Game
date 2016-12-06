#pragma once
#include "GameObject.h"
#include "Equipment.h"

//base class for players and NPCs
class CharacterObject : public GameObject
{
protected:
	float m_health;
	Equipment m_equipment;
public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void die(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
};