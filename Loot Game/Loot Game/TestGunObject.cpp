#include "TestGunObject.h"
#include "GameInfo.h"
#include "TestBulletObject.h"
#include "CharacterObject.h"

void TestGunObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	ItemObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	WeaponStats stats;
	stats.m_automatic = true;
	stats.m_damage = 6;
	stats.m_attackCooldown = 8;
	stats.m_maxSpread = 35;
	stats.m_minSpread = 3;
	stats.m_spreadRate = 1;
	stats.m_despreadRate = 1;
	stats.m_projectilesPerShot = 1;
	stats.m_range = 400;
	stats.m_projectileSpeed = 15;
	stats.m_aimGuide = true;
	stats.m_ammoPerProjectile = 1;
	stats.m_reloadTime = 45;
	stats.m_clipSize = 12;
	stats.m_recoil = 0.4f;
	
	m_baseStats = stats;
	m_perkedStats = stats;
	
	m_triggerDown = false;
	m_spread = m_perkedStats.m_minSpread;
	m_currentAmmo = 0;
	m_cooldownCounter.setTarget(stats.m_attackCooldown);
	m_reloadCounter.setTarget(stats.m_reloadTime);
}

void TestGunObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	WeaponObject::update(_gameInfo, _stateInfo);
}

void TestGunObject::draw(const RenderInfo & _renderInfo, const StateInfo & _stateInfo)
{
	sf::RectangleShape rect(sf::Vector2f(15, 5));
	rect.setPosition(m_position);
	rect.setOrigin(-4, 2.5);
	rect.setFillColor({ 255, 0, 0 });
	rect.setRotation(m_rotation);

	if (m_perkedStats.m_aimGuide && m_holder)
	{
		sf::Vector2f gunTipOffset = { 0, 0 };
		gunTipOffset.x = cos(-m_rotation * 3.14f / 180.f) * 19;
		gunTipOffset.y = -sin(-m_rotation * 3.14f / 180.f) * 19;
		sf::RectangleShape lines[2];
		for (int i = 0; i < 2; i++)
		{
			lines[i].setSize({ (float)m_perkedStats.m_range, 1.f });
			lines[i].setPosition(m_position + gunTipOffset);
			lines[i].setFillColor({ 140,255,140, 150 });
			lines[i].setOrigin(0.5, 0.5);
		}
		lines[0].setRotation(m_rotation - m_spread / 2.f);
		lines[1].setRotation(m_rotation + m_spread / 2.f);
		for (int i = 0; i < 2; i++)
		{
			_renderInfo.m_target->draw(lines[i]);
		}
	}

	_renderInfo.m_target->draw(rect);
}

void TestGunObject::cleanup(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
}

void TestGunObject::attack(const GameInfo& _gameInfo, const StateInfo & _stateInfo)
{
	if (m_cooldownCounter.check() && m_currentAmmo > 0)
	{
		m_cooldownCounter.restart(m_perkedStats.m_attackCooldown);
		m_reloadCounter.restart(m_perkedStats.m_reloadTime);
		unsigned int projectiles = m_perkedStats.m_projectilesPerShot;
		if (projectiles > m_currentAmmo)
		{
			projectiles = m_currentAmmo;
		}
		for (int i = 0; i < projectiles; i++)
		{
			TestBulletObject* bullet = (TestBulletObject*)_gameInfo.m_objectFactory->createObject("TestBulletObject");
			bullet->initialise(_gameInfo, _stateInfo, 0, m_position);
			bullet->setRange(m_perkedStats.m_range);
			bullet->setSpeed(m_perkedStats.m_projectileSpeed);
			float angle = -m_rotation;
			if ((int)m_spread != 0)
			{
				angle += -m_spread / 2.f + rand() % (int)m_spread;
			}
			bullet->setVelocity(angle, m_perkedStats.m_projectileSpeed);
			bullet->translate(-m_rotation, 18);
			if (m_holder)
			{
				m_holder->changeVelocity(angle, -m_perkedStats.m_recoil);
			}
		}
		m_spread += m_perkedStats.m_spreadRate;
		m_currentAmmo -= projectiles * m_perkedStats.m_ammoPerProjectile;
	}
}
