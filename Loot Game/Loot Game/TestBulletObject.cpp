#include "TestBulletObject.h"
#include "StateInfo.h"

void TestBulletObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
}

void TestBulletObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	m_rangeCounter.add(m_speed);
	if (m_rangeCounter.check() && m_range > 0)
	{
		_stateInfo.m_destroyRequests->push_back(this);
	}
	m_position += m_velocity;
}

void TestBulletObject::draw(const RenderInfo & _renderInfo, const StateInfo & _stateInfo)
{
	sf::CircleShape circ(4, 8);
	circ.setFillColor({ 255,0, 255 });
	circ.setPosition(m_position);
	circ.setOrigin({ 4,4 });
	circ.setRotation(m_rotation);
	_renderInfo.m_target->draw(circ);
}

void TestBulletObject::cleanup(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}

void TestBulletObject::setRange(int _range)
{
	m_rangeCounter.setTarget(_range);
	m_range = _range;
}

void TestBulletObject::setSpeed(int _speed)
{
	m_speed = _speed;
}
