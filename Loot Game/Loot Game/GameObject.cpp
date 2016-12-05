#include "GameObject.h"

std::string GameObject::getName(){
    return m_name;
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

bool GameObject::isActive()
{
	return m_active;
}

sf::Vector2f GameObject::getPosition()
{
	return m_position;
}

sf::Vector2f GameObject::getVelocity()
{
	return m_velocity;
}

sf::Vector2f GameObject::getDirection()
{
	sf::Vector2f dir = m_velocity;
	float velMag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;
	velMag = sqrt(velMag);
	if (velMag == 0)
	{
		dir = sf::Vector2f(0, 0);
	}
	else
	{
		dir.x = m_velocity.x / velMag;
		dir.y = m_velocity.y / velMag;
	}
	return dir;
}

sf::Vector2f GameObject::getControlledDirection()
{
	sf::Vector2f dir = m_controlledVelocity;
	float velMag = m_controlledVelocity.x * m_controlledVelocity.x + m_controlledVelocity.y * m_controlledVelocity.y;
	velMag = sqrt(velMag);
	if (velMag == 0)
	{
		dir = sf::Vector2f(0, 0);
	}
	else
	{
		dir.x = m_controlledVelocity.x / velMag;
		dir.y = m_controlledVelocity.y / velMag;
	}
	return dir;
}

float GameObject::getRotation()
{
	return m_rotation;
}

unsigned int GameObject::getHandle()
{
	return m_handle;
}

void GameObject::setActive(bool _active)
{
	m_active = _active;
}

void GameObject::lookAt(sf::Vector2f point)
{
	m_rotation = -(float)atan2((m_position.y - point.y), (point.x - m_position.x)) * 180.f / 3.14f;
}

void GameObject::setRotation(float _rotation)
{
	m_rotation = _rotation;
}

void GameObject::setVelocity(sf::Vector2f _velocity)
{
	m_velocity = _velocity;
}

void GameObject::setVelocityByDirection(sf::Vector2f _direction, float _magnitude)
{
	sf::Vector2f dir =_direction;
	float dirMag = _direction.x * _direction.x + _direction.y * _direction.y;
	dirMag = sqrt(dirMag);
	if (dirMag == 0)
	{
		dir = sf::Vector2f(0, 0);
	}
	else
	{
		dir.x = _direction.x / dirMag;
		dir.y = _direction.y / dirMag;
	}
	m_velocity = dir * _magnitude;
}

void GameObject::setVelocityByRotation(float _rotation, float _magnitude)
{
	m_velocity.x = cos(_rotation * 3.14f / 180.f) * _magnitude;
	m_velocity.y = -sin(_rotation * 3.14f / 180.f) * _magnitude;
}

void GameObject::setPosition(sf::Vector2f _position)
{
	m_position = _position;
}
