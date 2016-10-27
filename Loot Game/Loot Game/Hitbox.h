#pragma once

#include <SFML/Graphics.hpp>

struct Collision
{
    bool m_colliding;
    bool m_willCollide;
    sf::Vector2f m_translation;
};

class Hitbox
{
protected:
	void getMinMaxProjectionsOnAxis(sf::Vector2f _axis,
									sf::Vector2f* _verts, float& _minPos, float& _maxPos,
									sf::Vector2f* _otherVerts, float& _otherMinPos, float& _otherMaxPos);
	float getMinMaxDistance(float _minPos, float _maxPos, float _otherMinPos, float _otherMaxPos);
public:
	sf::Vector2f m_position;
	sf::Vector2f m_origin;
	sf::Vector2f m_dimensions;
	sf::Vector2f m_velocity;
	float m_rotation;

	void update(sf::Vector2f _position, float _rotation = 0, sf::Vector2f _velocity = sf::Vector2f(0, 0));
	bool checkAABB(Hitbox _other);
	sf::Vector2f* getVertices();
	sf::Vector2f getCenter();
	bool checkSAT(Hitbox _other);
	Collision checkSweptSAT(Hitbox _other);
	void draw(sf::RenderTarget& target);
};
