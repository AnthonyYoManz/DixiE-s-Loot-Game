#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "RenderInfo.h"

struct GameInfo;
struct StateInfo;

class GameObject
{
protected:
	bool m_active;
	std::string m_name;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_controlledVelocity;
	float m_moveSpeed;
	float m_rotation;
	unsigned int m_handle;
public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
	virtual void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo) = 0;
	virtual void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;

	//Getters
	bool isActive();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getDirection();
	sf::Vector2f getControlledDirection();
	float getRotation();
	unsigned int getHandle();
	std::string getName();

	//Setters
	void setActive(bool _active);
	void lookAt(sf::Vector2f _point);
	void setRotation(float _rotation);
	void setVelocity(sf::Vector2f _velocity);
	void setVelocityByDirection(sf::Vector2f _direction, float _magnitude);
	void setVelocityByRotation(float _rotation, float _magnitude);
	void setPosition(sf::Vector2f _position);

};

