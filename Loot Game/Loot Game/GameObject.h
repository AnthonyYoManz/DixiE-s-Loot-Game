#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameInfo.h"
#include "RenderInfo.h"

class GameObject
{
protected:
	std::string name;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	unsigned int m_handle;
public:
	std::string getName();
	virtual void initialise(unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) = 0;
	virtual void update(const GameInfo& _info) = 0;
	virtual void draw(const RenderInfo& _info) = 0;
	virtual void cleanup(const GameInfo& _info) = 0;

	//Getters
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getRotation();
	unsigned int getHandle();

	//Setters
	void lookAt(sf::Vector2f _point);
	void setRotation(float _rotation);
	void setVelocity(sf::Vector2f _velocity);
	void setPosition(sf::Vector2f _position);

};

