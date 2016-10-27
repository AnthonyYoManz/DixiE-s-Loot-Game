#include "SceneObject.h"
#include <math.h>

//Play with this?
const float SceneObject::m_maxVelocity = 1000.f;

int SceneObject::getTags()
{
    return m_tags;
}

int SceneObject::getWantedTags(){
    return m_wantedTags;
}

sf::Vector2f SceneObject::getPosition()
{
    return m_position;
}
sf::Vector2f SceneObject::getVelocity()
{
    return m_velocity;
}
float SceneObject::getRotation()
{
    return m_rotation;
}
unsigned int SceneObject::getHandle()
{
    return m_handle;
}

Collision SceneObject::checkCollision(SceneObject* other)
{
    return m_hitbox.checkSweptSAT(other->getHitbox());
}

Hitbox SceneObject::getHitbox()
{
    return m_hitbox;
}

void SceneObject::lookAt(sf::Vector2f point)
{
    m_rotation = (float)atan2((m_position.y - point.y), (point.x - m_position.x)) * 180.f / 3.14f;
}
void SceneObject::setVelocity(float x, float y)
{
    m_velocity.x = x;
    m_velocity.y = y;
    if(m_velocity.x > m_maxVelocity)
	{
        m_velocity.x = m_maxVelocity;
    }
    else if(m_velocity.x < -m_maxVelocity)
	{
        m_velocity.x = -m_maxVelocity;
    }
    else if(m_velocity.y > m_maxVelocity)
	{
        m_velocity.y = m_maxVelocity;
    }
    else if(m_velocity.y < -m_maxVelocity)
	{
        m_velocity.y = -m_maxVelocity;
    }
}
void SceneObject::changeVelocity(float x, float y)
{
    m_velocity.x += x;
    m_velocity.y += y;
    if(m_velocity.x > m_maxVelocity)
	{
        m_velocity.x = m_maxVelocity;
    }
    else if(m_velocity.x < -m_maxVelocity)
	{
        m_velocity.x = -m_maxVelocity;
    }
    else if(m_velocity.y > m_maxVelocity)
	{
        m_velocity.y = m_maxVelocity;
    }
    else if(m_velocity.y < -m_maxVelocity)
	{
        m_velocity.y = -m_maxVelocity;
    }
}

void SceneObject::decelerate(float _dt)
{
    if(m_velocity.x > 0)
	{
        if(m_velocity.x > m_maxVelocity)
		{
            m_velocity.x = m_maxVelocity;
        }
        m_velocity.x -= m_deceleration * _dt;
        if(m_velocity.x < 0)
		{
            m_velocity.x = 0;
        }
    }
    else if(m_velocity.x < 0)
	{
        if(m_velocity.x < -m_maxVelocity)
		{
            m_velocity.x = -m_maxVelocity;
        }
        m_velocity.x += m_deceleration * _dt;
        if(m_velocity.x > 0)
		{
            m_velocity.x = 0;
        }
    }
    if(m_velocity.y > 0)
	{
        if(m_velocity.y > m_maxVelocity)
		{
            m_velocity.y = m_maxVelocity;
        }
        m_velocity.y -= m_deceleration * _dt;
        if(m_velocity.y < 0)
		{
            m_velocity.y = 0;
        }
    }
    else if(m_velocity.y < 0)
	{
        if(m_velocity.y < -m_maxVelocity)
		{
            m_velocity.y = -m_maxVelocity;
        }
        m_velocity.y += m_deceleration * _dt;
        if(m_velocity.y > 0)
		{
            m_velocity.y = 0;
        }
    }
}
