#pragma once
#include "GameObject.h"

class WeaponObject;

class PlayerObject : public GameObject
{
private:
	float m_radius;
	float m_health;
	int m_playerNumber;
	WeaponObject* m_gun;
	bool m_leftTriggerDown;
public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo);
	virtual void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void setPlayerNumber(int _playerNumber);
	void handleInputs(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
};

