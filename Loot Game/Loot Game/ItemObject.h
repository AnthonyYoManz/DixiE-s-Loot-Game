#pragma once
#include "GameObject.h"
#include "GameInfo.h"
#include "RenderInfo.h"
#include "StateInfo.h"

class CharacterObject;

enum class ItemType 
{
	ARMOUR,
	RANGED,
	MELEE,
	USABLE
};

class ItemObject : public GameObject 
{
protected:
	CharacterObject* m_holder;
	ItemType m_type;
	unsigned int m_rarity;

public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
	virtual void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo) = 0;
	virtual void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
	//virtual void activate(bool primary) = 0;

	void equip(CharacterObject* _character);
	void unequip();
	unsigned int getRarity();
};