#pragma once

#include "GameObject.h"
#include "Counter.h"

class TestBulletObject : public GameObject
{
private:
	int m_range;
	int m_speed;
	Counter m_rangeCounter;
public:
	void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo);
	void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo);

	void setRange(int _range);
	void setSpeed(int _speed);
};