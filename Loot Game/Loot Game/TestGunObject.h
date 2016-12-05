#pragma once
#include "WeaponObject.h"

class TestGunObject : public WeaponObject
{
private:

public:
	void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo);
	void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void attack(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
};