#include "GameObject.h"

std::string GameObject::getName() const
{
    return m_name;
}

sf::Vector2f GameObject::normalise(sf::Vector2f _src) const
{
	sf::Vector2f norm = _src;
	float srcMag = _src.x * _src.x + _src.y * _src.y;
	srcMag = sqrt(srcMag);
	if (srcMag == 0)
	{
		norm = sf::Vector2f(0, 0);
	}
	else
	{
		norm.x = _src.x / srcMag;
		norm.y = _src.y / srcMag;
	}
	return norm;
}

void GameObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	m_active = true;
	m_handle = _handle;
	m_position = _position;
	m_velocity = { 0, 0 };
	m_controlledVelocity = { 0, 0 };
	m_moveSpeed = 0.f;
}

bool GameObject::isActive() const
{
	return m_active;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Vector2f GameObject::getVelocity() const
{
	return m_velocity;
}

sf::Vector2f GameObject::getDirection() const
{
	return normalise(m_velocity);
}

sf::Vector2f GameObject::getControlledDirection() const
{
	return normalise(m_controlledVelocity);
}

float GameObject::getRotation() const 
{
	return m_rotation;
}

unsigned int GameObject::getHandle() const
{
	return m_handle;
}

void GameObject::setActive(bool _active)
{
	m_active = _active;
}

void GameObject::setRotation(float _rotation)
{
	m_rotation = _rotation;
}

void GameObject::setVelocity(sf::Vector2f _velocity)
{
	m_velocity = _velocity;
}

void GameObject::setVelocity(sf::Vector2f _direction, float _magnitude)
{
	sf::Vector2f dir = normalise(_direction);
	m_velocity = dir * _magnitude;
}

void GameObject::setVelocity(float _rotation, float _magnitude)
{
	m_velocity.x = cos(_rotation * 3.14f / 180.f) * _magnitude;
	m_velocity.y = -sin(_rotation * 3.14f / 180.f) * _magnitude;
}

void GameObject::setPosition(sf::Vector2f _position)
{
	m_position = _position;
}

void GameObject::lookAt(sf::Vector2f point)
{
	m_rotation = -(float)atan2((m_position.y - point.y), (point.x - m_position.x)) * 180.f / 3.14f;
}

void GameObject::translate(sf::Vector2f _translation)
{
	m_position += _translation;
}

void GameObject::translate(float _angle, float _magnitude)
{
	sf::Vector2f disp = { 0, 0 };
	disp.x = cos(_angle * 3.14f / 180.f) * _magnitude;
	disp.y = -sin(_angle * 3.14f / 180.f) * _magnitude;
	translate(disp);
}

void GameObject::translate(sf::Vector2f _direction, float _magnitude)
{
	sf::Vector2f dir = normalise(_direction);
	translate(dir * _magnitude);
}

void GameObject::changeVelocity(sf::Vector2f _change)
{
	m_velocity += _change;
}

void GameObject::changeVelocity(sf::Vector2f _direction, float _magnitude)
{
	sf::Vector2f dir = normalise(_direction);
	changeVelocity(dir * _magnitude);
}

void GameObject::changeVelocity(float _angle, float _magnitude)
{
	sf::Vector2f change = { 0, 0 };
	change.x = cos(_angle * 3.14f / 180.f) * _magnitude;
	change.y = -sin(_angle * 3.14f / 180.f) * _magnitude;
	changeVelocity(change);
}
