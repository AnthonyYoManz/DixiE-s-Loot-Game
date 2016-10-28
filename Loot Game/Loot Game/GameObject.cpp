#include "GameObject.h"

std::string GameObject::getName(){
    return name;
}

sf::Vector2f GameObject::getPosition()
{
	return m_position;
}

sf::Vector2f GameObject::getVelocity()
{
	return m_velocity;
}

float GameObject::getRotation()
{
	return m_rotation;
}

unsigned int GameObject::getHandle()
{
	return m_handle;
}

void GameObject::lookAt(sf::Vector2f point)
{
	m_rotation = (float)atan2((m_position.y - point.y), (point.x - m_position.x)) * 180.f / 3.14f;
}

void GameObject::setRotation(float _rotation)
{
	m_rotation = _rotation;
}

void GameObject::setVelocity(sf::Vector2f _velocity)
{
	m_velocity = _velocity;
}

void GameObject::setPosition(sf::Vector2f _position)
{
	m_position = _position;
}
