#pragma once

#include <SFML/Graphics.hpp>
#include "GameInfo.h"
#include "RenderInfo.h"
#include "GameObject.h"
#include "Hitbox.h"

enum class ObjectTag
{
    PLAYER = 1 << 0,
    ENEMY = 1 << 1,
    BULLET = 1 << 2,
    ITEM = 1 << 3,
    TERRAIN = 1 << 4
};

class SceneObject : public GameObject
{
protected:
	int m_tags;
	int m_wantedTags; //tags used to filter collisions
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_cVelocity; //controlled velocity
	static const float m_maxVelocity;
	float m_rotation;
	float m_deceleration;
	unsigned int m_handle;
	Hitbox m_hitbox;
	void decelerate(float _dt);
public:
	virtual void initialise(unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) = 0;
	virtual void handleEvents() = 0;
	virtual void update(const GameInfo& _info) = 0;
	virtual void handleCollision(SceneObject* _other, Collision _collision) {}
	virtual void draw(const RenderInfo& _info) = 0;
	virtual void cleanup(const GameInfo& _info) = 0;
	virtual bool onScreen() = 0;

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getRotation();
	unsigned int getHandle();

	int getTags();
	int getWantedTags();
	Collision checkCollision(SceneObject* other);
	Hitbox getHitbox();
	void lookAt(sf::Vector2f point);
	void setVelocity(float x, float y);
	void changeVelocity(float x, float y);
};

