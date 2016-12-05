#include "TestGunObject.h"
#include <iostream>
#include "GameInfo.h"
#include "TestBulletObject.h"

void TestGunObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	GameObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	WeaponStats stats;
	stats.m_automatic = true;
	stats.m_damage = 6;
	stats.m_attackCooldown = 0;
	stats.m_maxSpread = 30;
	stats.m_minSpread = 0;
	stats.m_spreadRate = 0.1;
	stats.m_despreadRate = 0.3;
	stats.m_projectilesPerShot = 1;
	stats.m_range = 400;
	stats.m_projectileSpeed = 15;
	stats.m_aimGuide = true;
	m_baseStats = stats;
	m_perkedStats = stats;
	m_triggerDown = false;
	m_spread = m_perkedStats.m_minSpread;
	m_cooldownCounter.setTarget(stats.m_attackCooldown);
}

void TestGunObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	WeaponObject::update(_gameInfo, _stateInfo);
}

void TestGunObject::draw(const RenderInfo & _renderInfo, const StateInfo & _stateInfo)
{
	sf::RectangleShape rect(sf::Vector2f(10, 5));
	rect.setPosition(m_position);
	rect.setOrigin(0, 2.5);
	rect.setFillColor({ 255, 0, 0 });
	rect.setRotation(m_rotation);

	if (m_perkedStats.m_aimGuide)
	{
		sf::RectangleShape line1(sf::Vector2f(m_perkedStats.m_range, 1));
		line1.setPosition(m_position);
		line1.setOrigin(0, 0);
		line1.setFillColor({ 140,255,140, 150 });
		line1.setRotation(m_rotation - m_spread / 2.f);
		sf::RectangleShape line2(sf::Vector2f(m_perkedStats.m_range, 1));
		line2.setPosition(m_position);
		line2.setOrigin(0, 0);
		line2.setFillColor({ 140,255,140, 150 });
		line2.setRotation(m_rotation + m_spread / 2.f);
		sf::RectangleShape line3(sf::Vector2f(m_perkedStats.m_range, 1));
		line3.setPosition(m_position);
		line3.setOrigin(0, 0);
		line3.setFillColor({ 0, 255, 0, 150 });
		line3.setRotation(m_rotation);
		_renderInfo.m_target->draw(line1);
		_renderInfo.m_target->draw(line2);
		_renderInfo.m_target->draw(line3);
	}

	_renderInfo.m_target->draw(rect);
}

void TestGunObject::cleanup(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}

void TestGunObject::attack(const GameInfo& _gameInfo, const StateInfo & _stateInfo)
{
	if (m_cooldownCounter.check())
	{
		m_cooldownCounter.restart();
		TestBulletObject* bullet = (TestBulletObject*)_gameInfo.m_objectFactory->createObject("TestBulletObject");
		bullet->initialise(_gameInfo, _stateInfo, 0, m_position);
		bullet->setRange(m_perkedStats.m_range);
		bullet->setSpeed(m_perkedStats.m_projectileSpeed);
		float angle = -m_rotation;
		if ((int)m_spread != 0)
		{
			angle += -m_spread / 2.f + rand() % (int)m_spread;
		}
		bullet->setVelocityByRotation(angle, m_perkedStats.m_projectileSpeed);
		m_spread += m_perkedStats.m_spreadRate;
	}
}
