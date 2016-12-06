#pragma once
#include "CharacterObject.h"

class WeaponObject;

class PlayerObject : public CharacterObject
{
private:
	float m_radius;
	int m_playerNumber;
	bool m_leftTriggerDown;
public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo);
	virtual void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void setPlayerNumber(int _playerNumber);
	void handleInputs(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
};

