#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "RenderInfo.h"

struct GameInfo;
struct StateInfo;

class GameObject
{
private:
	sf::Vector2f normalise(sf::Vector2f _src) const;
	float getMagnitude(sf::Vector2f _src) const;
protected:
	bool m_active;
	bool m_static;
	std::string m_name;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_controlledVelocity;
	float m_moveSpeed;
	float m_deceleration;
	float m_rotation;
	unsigned int m_handle;
public:
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
	virtual void draw(const RenderInfo& _renderInfo, const StateInfo& _stateInfo) = 0;
	virtual void cleanup(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;

	//Getters
	bool isActive() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getDirection() const;
	sf::Vector2f getControlledDirection() const;
	float getRotation() const;
	float getDeceleration() const;
	unsigned int getHandle() const;
	std::string getName() const;

	//Setters
	void setActive(bool _active);
	void setStatic(bool _static);
	void setRotation(float _rotation);
	void setVelocity(sf::Vector2f _velocity);
	void setVelocity(sf::Vector2f _direction, float _magnitude);
	void setVelocity(float _rotation, float _magnitude);
	void setDeceleration(float _deceleration);
	void setPosition(sf::Vector2f _position);

	void lookAt(sf::Vector2f _point);
	void translate(sf::Vector2f _translation);
	void translate(float _angle, float _magnitude);
	void translate(sf::Vector2f _direction, float _magnitude);
	void changeVelocity(sf::Vector2f _change);
	void changeVelocity(sf::Vector2f _direction, float _magnitude);
	void changeVelocity(float _angle, float _magnitude);
	void decelerate(float _dt = 1);
};

